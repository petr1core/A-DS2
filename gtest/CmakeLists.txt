set(target "gtest")
set (CMAKE_CXX_STANDARD 14)

add_library(${target} STATIC gtest-all.cc)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_compile_options(${target} PUBLIC /wd"4996" /wd"4002")
target_link_libraries(${target} ${pthread})
