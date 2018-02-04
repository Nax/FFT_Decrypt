find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "*.cpp" "*.h")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/data/fftdecrypt-gui/fftdecrypt.qrc")

if (APPLE)
    set(ICON "${CMAKE_SOURCE_DIR}/data/fftdecrypt-gui/icon.icns")
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set_source_files_properties(${ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    list(APPEND SOURCES ${ICON})
elseif(WIN32)
	list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/data/fftdecrypt-gui/fftdecrypt.rc")
endif()

add_executable(fftdecrypt-gui WIN32 MACOSX_BUNDLE ${SOURCES})
target_include_directories(fftdecrypt-gui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(fftdecrypt-gui Qt5::Core Qt5::Widgets libfftdecrypt)

if (APPLE)
    set(NAME "FFT Decrypt")
else()
    set(NAME "fftdecrypt-qt")
endif()

set_target_properties(fftdecrypt-gui PROPERTIES OUTPUT_NAME "${NAME}")

if (APPLE)
    install(CODE "execute_process(COMMAND macdeployqt \"${CMAKE_BINARY_DIR}/bin/FFT Decrypt.app\")" COMPONENT RUNTIME)

    install(TARGETS fftdecrypt-gui BUNDLE DESTINATION .)
endif()
