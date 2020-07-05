cmake_minimum_required(VERSION 3.17)

project(sorts_comparison)

set(SOURCE ./source/main.cpp ./source/sorts.hpp ./source/TimeTest.hpp ./source/test_thread.hpp)
set(SORTS ./source/sorts/bitonic_sort.hpp ./source/sorts/bubble_sort.hpp
	./source/sorts/comb_sort.hpp ./source/sorts/gnome_sort.hpp
	./source/sorts/insertion_sort.hpp ./source/sorts/lsd_sort.hpp
	./source/sorts/merge_sort.hpp ./source/sorts/quick_sort.hpp
	./source/sorts/selection_sort.hpp ./source/sorts/shaker_sort.hpp)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

add_executable(main ${SOURCE} ${SORTS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(main Threads::Threads)

file(MAKE_DIRECTORY ./bin/results)
