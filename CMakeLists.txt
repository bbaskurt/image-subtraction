cmake_minimum_required(VERSION 2.8.9)

set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "Install path prefix" FORCE)

project (image_subtraction)

set(subtraction_sources
	main.cpp
	image_subtraction.h
	image_subtraction.cpp
	file_operations.h
	file_operations.cpp
	image.h
	image.cpp
	test.h
	test.cpp
	)	

add_executable(${PROJECT_NAME}
	${subtraction_sources}
)

#add_executable(payment_system main.cpp)
#target_link_libraries(payment_system ${PROJECT_LINK_LIBS} )