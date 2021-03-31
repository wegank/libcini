set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${cini_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/data)

file(GLOB cini_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB cini_HEADER CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB cini_DATA CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/include/data/font.h)

add_library(cini SHARED ${cini_SRC} ${cini_HEADER} ${cini_DATA})
target_link_libraries(cini ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS cini TYPE LIBRARY)
install(FILES ${cini_HEADER} TYPE INCLUDE)
