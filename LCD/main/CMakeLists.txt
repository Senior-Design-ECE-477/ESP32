file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")

file(GLOB_RECURSE SRC_SCREEN ${CMAKE_SOURCE_DIR} "screen/*.c")

idf_component_register(SRCS "main.c" ${SRC_UI} ${SRC_SCREEN}
                    INCLUDE_DIRS "." "ui" "screen")
