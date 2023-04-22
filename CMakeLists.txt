cmake_minimum_required(VERSION 3.0)

project(LasDemo)

# LASLib include directory
set( LASLIB_INCLUDE_DIR "" CACHE PATH "LASLib include directory" )
set( LASLIB_RELEASE_LIBRARY "" CACHE FILEPATH "LASLib release library file" )
set( LASLIB_DEBUG_LIBRARY "" CACHE FILEPATH "LASLib debug library file" )

if ( NOT LASLIB_INCLUDE_DIR )
	message( SEND_ERROR "No LASLib include directories specified (LASLIB_INCLUDE_DIR)" )
endif()

include_directories(${LASLIB_INCLUDE_DIR} ./include)

# Add the source files
set(SOURCE_FILES main.cpp)

# Create the executable
add_executable(LasDemo ${SOURCE_FILES})


# link project with LASLib

if( LASLIB_RELEASE_LIBRARY )
target_link_libraries(${PROJECT_NAME} optimized ${LASLIB_RELEASE_LIBRARY} )
endif()

if( CMAKE_CONFIGURATION_TYPES AND LASLIB_DEBUG_LIBRARY )
target_link_libraries(${PROJECT_NAME} debug ${LASLIB_DEBUG_LIBRARY} )
endif()


