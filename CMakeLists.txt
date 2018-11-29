#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(GELI)



set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -O3")


#----------------------------------------------------------------------------
# Find root (required package)
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
#----------------------------------------------------------------------------
# Include CADMesh in your project.
find_package(cadmesh)
include_directories(${CADMESH_INCLUDE_DIRS})



#

#----------------------------------------------------------------------------
# Add option to debug
#
# option(DEBUG_INTERPOLATING_FIELD "Debug setting" OFF)
# if(DEBUG_INTERPOLATING_FIELD)
#   add_definitions(-DDEBUG_INTERPOLATING_FIELD)
# endif()

option(BUILD_GEANT_MODULE "Build Geant4 simulation" ON)
option(BUILD_TRANSPORT_MODULE "Build TransportSimulator" ON)


#utilities are build by default
ADD_SUBDIRECTORY(Utilities)

if(BUILD_GEANT_MODULE)
	ADD_SUBDIRECTORY(Geant4)
endif()

if(BUILD_TRANSPORT_MODULE)
	ADD_SUBDIRECTORY(TransportSimulator)
endif()

