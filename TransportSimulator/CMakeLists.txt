include_directories(${CMAKE_SOURCE_DIR}/Utilities/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB transport_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB transport_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)



#---Create  a main program using the library
add_executable(main main.cc ${transport_sources} ${transport_headers})
target_link_libraries(main utils)
target_link_libraries(main SimEvent)


