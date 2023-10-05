file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")
file(GLOB_RECURSE SRC_SCREEN ${CMAKE_SOURCE_DIR} "screen/*.c")
file(GLOB_RECURSE SRC_UTIL ${CMAKE_SOURCE_DIR} "utils/*.c")
file(GLOB_RECURSE SRC_AWS ${CMAKE_SOURCE_DIR} "aws/*.c")

idf_component_register(SRCS "main.c" ${SRC_UI} ${SRC_SCREEN} ${SRC_UTIL} ${SRC_AWS}
                    INCLUDE_DIRS "." ".secret" "ui" "screen" "utils" "aws"
                    )
