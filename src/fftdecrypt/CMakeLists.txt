file(GLOB_RECURSE SOURCES "*.c")
add_executable(fftdecrypt ${SOURCES})
target_link_libraries(fftdecrypt libfftdecrypt)
install(TARGETS fftdecrypt RUNTIME DESTINATION bin)
