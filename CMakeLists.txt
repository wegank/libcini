cmake_minimum_required(VERSION 3.16)
project(cini C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cini_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR} "include")

file(GLOB cini_SRC CONFIGURE_DEPENDS "src/*.c")
file(GLOB cini_HEADER CONFIGURE_DEPENDS "include/*.h")

add_library(cini SHARED ${cini_SRC} ${cini_HEADER})
target_link_libraries(cini ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS cini TYPE LIBRARY)
install(FILES ${cini_HEADER} TYPE INCLUDE)
install(FILES "data/font.ttf" DESTINATION ${CMAKE_INSTALL_DATADIR}/libcini)

include(cmake/packaging.cmake)
include(CPack)
