cmake_minimum_required(VERSION 3.0.0)
project(fffrenderer VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCES *.h *.cpp)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
