include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB util_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
file(GLOB util_headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh)


ROOT_GENERATE_DICTIONARY(SimEventDict ${CMAKE_CURRENT_SOURCE_DIR}/include/SimEvent.hh LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/include/LinkDef.h)

#---Create a shared library with geneated dictionary
add_library(SimEvent SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/SimEvent.cc SimEventDict.cxx)
add_library(utils SHARED ${util_sources} ${util_headers})
target_link_libraries(SimEvent ${ROOT_LIBRARIES})


#---Create  a main program using the library

add_executable(read read.cc ${util_sources} ${util_headers})
target_link_libraries(read utils)
target_link_libraries(read SimEvent)


