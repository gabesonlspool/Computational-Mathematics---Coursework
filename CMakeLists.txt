cmake_minimum_required(VERSION 3.8)

project(Coursework)

SET(SRC ${CMAKE_CURRENT_LIST_DIR}/sources)
SET(HDR ${CMAKE_CURRENT_LIST_DIR}/headers)
SET(GCC_COMPILE_FLAGS "-Wall -o2 -I${HDR}") 
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")


add_executable(main ${SRC}/main.cpp)
target_link_libraries(main explicit implicit crunk_nickelson)
set_target_properties(main PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(main PUBLIC ${SRC})
target_include_directories(main PUBLIC ${HDR})


add_library(explicit STATIC ${HDR}/explicit.h ${SRC}/explicit.cpp)
target_link_libraries(explicit solver)

add_library(implicit STATIC ${HDR}/implicit.h ${SRC}/implicit.cpp)
target_link_libraries(implicit solver)

add_library(crunk_nickelson STATIC ${HDR}/crunk_nickelson.h ${SRC}/crunk_nickelson.cpp)
target_link_libraries(crunk_nickelson solver)

add_library(solver STATIC ${HDR}/solver.h ${SRC}/solver.cpp ${HDR}/problem_statement.h ${SRC}/problem_statement.cpp) 


