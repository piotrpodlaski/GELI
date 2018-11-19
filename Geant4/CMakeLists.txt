include_directories(${CMAKE_SOURCE_DIR}/SimEvent)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(GELI GELI.cc ${sources} ${headers})
target_link_libraries(GELI ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${cadmesh_LIBRARIES})
target_link_libraries(GELI cadmesh)
target_link_libraries(GELI SimEvent)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build purging_magnet. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(purging_magnet_SCRIPTS
    MacroTesting.mac vis.mac PurgMag3D.TABLE config.xml gps.mac
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
