include_directories(${CMAKE_SOURCE_DIR}/Utilities/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB transport_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB transport_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.xml ${CMAKE_CURRENT_BINARY_DIR}/config.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run.sh ${CMAKE_CURRENT_BINARY_DIR}/run.sh COPYONLY)


#---Create  a main program using the library
add_executable(main main.cc ${transport_sources} ${transport_headers})
add_executable(MT MT.cc ${transport_sources} ${transport_headers})
add_executable(synthetic synthetic.cc ${transport_sources} ${transport_headers})
add_executable(test1 test.cc ${transport_sources} ${transport_headers})


target_link_libraries(main utils)
target_link_libraries(main SimEvent)

target_link_libraries(MT utils)
target_link_libraries(MT SimEvent)

target_link_libraries(synthetic utils)
target_link_libraries(synthetic SimEvent)

target_link_libraries(test1 utils)
target_link_libraries(test1 SimEvent)
