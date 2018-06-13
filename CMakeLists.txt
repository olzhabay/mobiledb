cmake_minimum_required(VERSION 3.0)
project(mobiledb C CXX)

set(CMAKE_CXX_STANDARD 11)
find_library(Pthread_LIBRARY pthread)

set(DB_FILES
        common/db.h
        common/env.h
        common/slice.h
        common/status.h common/random.h common/port.h common/thread_annotations.h)

add_library(mobiledb ${DB_FILES})
set_target_properties(mobiledb PROPERTIES LINKER_LANGUAGE CXX)

add_executable(db_bench db_bench.cpp)
target_link_libraries(db_bench PUBLIC mobiledb)