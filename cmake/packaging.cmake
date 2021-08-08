##### set CPack properties #####

set(CPACK_PACKAGE_NAME libcini)
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_CONTACT "Weijia Wang")
set(CPACK_PACKAGE_VENDOR "Weijia Wang")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple and easy-to-use C initiation library")
set(CPACK_PACKAGE_DESCRIPTION "libcini is a simple and easy-to-use library for learning the C language.
 .
 - Easy-to-use standard input and output functions
 .
 - Simple debug function to trace program execution
 .
 - Simple pseudo-random functions
 .
 - Minimal graphic library based on SDL2
 .")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

# Variables specific to CPack DEB generator
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.24), libsdl2-ttf-2.0-0, libsdl2-2.0-0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Weijia Wang <weijia.wang2@etu.upmc.fr>")

# Variables specific to CPack NSIS generator
set(CPACK_NSIS_PACKAGE_NAME libcini)
set(CPACK_NSIS_DISPLAY_NAME libcini)
set(CPACK_NSIS_INSTALL_ROOT "C:\\\\msys64")

if (WIN32)
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "mingw64")
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif (APPLE)
    set(CPACK_SYSTEM_NAME "mac")
    set(CPACK_GENERATOR "ZIP")
elseif (UNIX)
    set(CPACK_SYSTEM_NAME "linux")
    execute_process(COMMAND lsb_release -si OUTPUT_VARIABLE distribution OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (distribution STREQUAL "Debian" OR distribution STREQUAL "Ubuntu")
        set(CPACK_GENERATOR "ZIP;DEB")
    endif ()
else ()
endif ()
