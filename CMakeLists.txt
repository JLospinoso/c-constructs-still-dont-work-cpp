cmake_minimum_required(VERSION 3.16)
project(c_constructs_still_dont_work LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(void_pointer_malloc_c examples/01_void_pointer_malloc.c)
add_executable(void_pointer_malloc_cpp examples/01_void_pointer_malloc.cpp)
add_executable(malloc_object_lifetime_cpp examples/02_malloc_object_lifetime.cpp)
add_executable(const_cast_cpp examples/03_const_cast.cpp)
add_executable(enums_c examples/04_enums.c)
add_executable(enums_cpp examples/04_enums.cpp)
add_executable(empty_parameter_lists_c examples/05_empty_parameter_lists.c)
add_executable(empty_parameter_lists_cpp examples/05_empty_parameter_lists.cpp)
add_executable(designated_initializers_c examples/06_designated_initializers.c)
add_executable(designated_initializers_cpp examples/06_designated_initializers.cpp)
add_executable(restrict_c examples/07_restrict.c)
add_executable(restrict_cpp_extension examples/07_restrict_cpp_extension.cpp)
add_executable(flexible_array_member_c examples/08_flexible_array_member.c)
add_executable(flexible_array_member_cpp_alternative examples/08_flexible_array_member_cpp_alternative.cpp)

foreach(target
  void_pointer_malloc_c
  void_pointer_malloc_cpp
  malloc_object_lifetime_cpp
  const_cast_cpp
  enums_c
  enums_cpp
  empty_parameter_lists_c
  empty_parameter_lists_cpp
  designated_initializers_c
  designated_initializers_cpp
  restrict_c
  restrict_cpp_extension
  flexible_array_member_c
  flexible_array_member_cpp_alternative)
  target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
endforeach()
