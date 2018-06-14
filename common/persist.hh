#ifndef MOBILEDB_PERSIST_HH
#define MOBILEDB_PERSIST_HH


#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <atomic>

#define CPU_FREQ_MHZ (994) // cat /proc/cpuinfo
#define CACHE_LINE_SIZE (64)
#define PAGESIZE 512

#define start_timer()    *((volatile uint32_t*)0xE0001000) = 0x40000001  // Enable CYCCNT register
#define stop_timer()   *((volatile uint32_t*)0xE0001000) = 0x40000000  // Disable CYCCNT register
#define get_timer()   *((volatile uint32_t*)0xE0001004)               // Get value from CYCCNT register


static uint64_t WRITE_LATENCY_IN_NS = 500;

static inline void cpu_pause() {
#if defined(__ARM_ARCH)
  asm volatile("" ::: "memory");
#else
  __asm__ volatile ("pause" ::: "memory");
#endif
}

static inline unsigned long read_tsc(void) {
#if defined(__ARM_ARCH)
  uint32_t it;
  start_timer();
  it = get_timer();
  stop_timer();
  return it;
#else
  uint64_t low, high;
  __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
  return (high << 32) | low;
#endif
}

inline void mfence() {
#if defined(__ARM_ARCH)
  std::atomic_signal_fence(std::memory_order_release);
#else
  asm volatile("mfence":::"memory");
#endif
}

inline void clflush(char *data, size_t len) {
  if (data == NULL) return;
  char *ptr = (char *)((unsigned long)data &~(CACHE_LINE_SIZE-1));
  mfence();
  for (; ptr<data+len; ptr+=CACHE_LINE_SIZE) {
    unsigned long etsc = read_tsc() + (unsigned long)(WRITE_LATENCY_IN_NS*CPU_FREQ_MHZ/1000);
#if defined(__ARM_ARCH)
    __builtin___clear_cache(ptr, ptr+len);
#else
    asm volatile("clflush %0" : "+m" (*(volatile char *)ptr));
#endif
    while (read_tsc() < etsc)
      cpu_pause();
  }
  mfence();
}

#endif //MOBILEDB_PERSIST_HH
