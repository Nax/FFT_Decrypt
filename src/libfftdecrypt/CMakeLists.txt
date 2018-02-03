file(GLOB_RECURSE SOURCES "*.c")
add_library(libfftdecrypt STATIC ${SOURCES})
set_target_properties(libfftdecrypt PROPERTIES OUTPUT_NAME fftdecrypt)
