##### set CPack properties #####

set(CPACK_PACKAGE_NAME libcini)
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
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

set(CPACK_RESOURCE_FILE_LICENCE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.24), libsdl2-ttf-2.0-0, libsdl2-2.0-0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Weijia Wang <weijia.wang2@etu.upmc.fr>")

set(CPACK_GENERATOR "DEB")
