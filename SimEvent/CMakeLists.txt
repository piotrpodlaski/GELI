
ROOT_GENERATE_DICTIONARY(SimEventDict SimEvent.hh LINKDEF LinkDef.h)

#---Create a shared library with geneated dictionary
add_library(SimEvent SHARED SimEvent.cc SimEventDict.cxx)
target_link_libraries(SimEvent ${ROOT_LIBRARIES})

#---Create  a main program using the library

add_executable(read read.cc SimEvent.hh)
target_link_libraries(read SimEvent)
#target_link_libraries(read ${ROOT_LIBRARIES})

#ROOT_GENERATE_DICTIONARY(SimEventDictoo.cxx SimEvent.hh LINKDEF LinkDef.h)

