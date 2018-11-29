


include_directories(${CMAKE_SOURCE_DIR}/Utilities/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)

#Find and include Gean4 package:

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})



#include GammaBeam simulator in the project
if(DEFINED GAMMA_PATH)
	include_directories(${GAMMA_PATH}/include)
	add_definitions(-DUSE_GAMMA_BEAM_GENERATOR)
	if(DEFINED GAMMA_BIN_PATH)
		LINK_DIRECTORIES(${GAMMA_BIN_PATH})
	else()
		LINK_DIRECTORIES(${GAMMA_PATH}/build)
	endif()
endif()

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(GELI GELI.cc ${sources} ${headers})
target_link_libraries(GELI ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${cadmesh_LIBRARIES})
target_link_libraries(GELI cadmesh)
target_link_libraries(GELI utils)
target_link_libraries(GELI SimEvent)
if(DEFINED GAMMA_PATH)
	target_link_libraries(GELI GammaBeam)
endif()

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build purging_magnet. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(purging_magnet_SCRIPTS
    MacroTesting.mac vis.mac PurgMag3D.TABLE config.xml gps.mac geometry.xml gamma.mac
  )

foreach(_script ${purging_magnet_SCRIPTS})
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${_script}
    ${CMAKE_CURRENT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Add program to the project targets
# (this avoids the need of typing the program name after make)
#
add_custom_target(geli DEPENDS GELI)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS PurgMag DESTINATION bin)ADD_SUBDIRECTORY(src)
