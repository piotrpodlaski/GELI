#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(GELI)

#cmake magic to link libraries when installing
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")


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
option(BUILD_DOC "Build documentation" ON)


#utilities are build by default
ADD_SUBDIRECTORY(Utilities)

if(BUILD_GEANT_MODULE)
	ADD_SUBDIRECTORY(Geant4)
endif()

if(BUILD_TRANSPORT_MODULE)
	ADD_SUBDIRECTORY(TransportSimulator)
endif()

if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
      message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(BUILD_DOC)

