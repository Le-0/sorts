cmake_minimum_required(VERSION 3.10)

project(sorts_comparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE ./source/main.cpp ./source/sorts/sorts.hpp ./source/benchmark/TimeTest.hpp ./source/benchmark/test_thread.hpp
	./source/display/HtmlTable.hpp ./source/display/write_table.hpp ./source/display/draw_graphic.hpp
       	./source/utils/getCPUTime.h ./source/utils/sequence_type.hpp)
set(SORTS ./source/sorts/bitonic_sort.hpp ./source/sorts/bubble_sort.hpp
	./source/sorts/comb_sort.hpp ./source/sorts/gnome_sort.hpp
	./source/sorts/insertion_sort.hpp ./source/sorts/lsd_sort.hpp
	./source/sorts/merge_sort.hpp ./source/sorts/quick_sort.hpp
	./source/sorts/selection_sort.hpp ./source/sorts/shaker_sort.hpp)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

add_executable(main ${SOURCE} ${SORTS})

target_link_libraries(main Threads::Threads)

file(MAKE_DIRECTORY ./bin/results)
file(MAKE_DIRECTORY ./bin/data)
