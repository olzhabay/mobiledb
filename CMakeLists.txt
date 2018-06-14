cmake_minimum_required(VERSION 3.0)
project(mobiledb C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_library(Pthread_LIBRARY pthread)
find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
find_package (SQLite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
endif (SQLITE3_FOUND)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

add_compile_options(
        -O2
        -DNDEBUG
)

set(DB_FILES
        db/kv_store.hh
        db/kv_store.cc
        db/btree.cc
        db/btree.hh
        common/env.hh
        common/slice.hh
        common/status.hh
        common/random.hh
        common/port.hh
        common/thread_annotations.hh
        common/testutil.hh
        common/persist.hh
        parser/location.hh
        parser/position.hh
        parser/sql_driver.hh
        parser/sql_driver.cc
        parser/sql_parser.hh
        parser/sql_parser.cc
        parser/sql_scanner.hh
        parser/sql_scanner.cc
        parser/sql_scanner.hpp
        parser/stack.hh
        parser/statements/create_statement.cc
        parser/statements/create_statement.hh
        parser/statements/delete_statement.cc
        parser/statements/delete_statement.hh
        parser/statements/drop_statement.cc
        parser/statements/drop_statement.hh
        parser/statements/insert_statement.cc
        parser/statements/insert_statement.hh
        parser/statements/select_statement.cc
        parser/statements/select_statement.hh
        parser/statements/sql_statement.cc
        parser/statements/sql_statement.hh
        parser/statements/sql_table.cc
        parser/statements/sql_table.hh
        parser/statements/update_statement.cc
        parser/statements/update_statement.hh
        parser/sql_message.hh
        common/iterator.hh db/storage_manager.cc db/storage_manager.hh db/btree_iterator.cc db/btree_iterator.hh db/kv_store_iterator.cc db/kv_store_iterator.hh)

add_library(mobiledblib ${DB_FILES})
set_target_properties(mobiledblib PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(mobiledblib PRIVATE ${Pthread_LIBRARY} )

add_executable(db_bench db_bench.cpp)
target_link_libraries(db_bench PUBLIC mobiledblib)

add_executable(db_bench_sqlite3 db_bench_sqlite3.cc)
target_link_libraries(db_bench_sqlite3 PUBLIC sqlite3)