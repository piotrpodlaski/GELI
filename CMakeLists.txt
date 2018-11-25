#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Geli4)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra -g -O3")

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

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
option(DEBUG_INTERPOLATING_FIELD "Debug setting" OFF)
if(DEBUG_INTERPOLATING_FIELD)
  add_definitions(-DDEBUG_INTERPOLATING_FIELD)
endif()

ADD_SUBDIRECTORY(Utilities)
ADD_SUBDIRECTORY(Geant4)
ADD_SUBDIRECTORY(TransportSimulator)

