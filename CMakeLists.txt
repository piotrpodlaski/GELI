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

ADD_SUBDIRECTORY(Utilities)
ADD_SUBDIRECTORY(Geant4)
ADD_SUBDIRECTORY(TransportSimulator)

