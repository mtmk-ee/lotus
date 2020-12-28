cmake_minimum_required(VERSION 3.1.2)
project(lotus VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include(CTest)
enable_testing()

link_directories(lib)


file(GLOB LOTUS_SRC
    "src/lotus/**/*.c"
    "src/lotus/**/*.cpp"
)
file(GLOB LOTUS_INCLUDE
    "include/lotus/**/*.h"
    "include/lotus/**/*.hpp"
)

add_library(LOTUS_LIB ${LOTUS_SRC} ${LOTUS_INCLUDE})
target_include_directories(LOTUS_LIB PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(LOTUS_LIB glfw3)




add_executable(engine_test "src/test/main.cpp" ${LOTUS_SRC} ${LOTUS_INCLUDE})
target_include_directories(engine_test PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(engine_test glfw3 LOTUS_LIB ${OPENGL_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
