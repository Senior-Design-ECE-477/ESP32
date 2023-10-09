file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")
# file(GLOB_RECURSE SRC_CAFS ${CMAKE_SOURCE_DIR} "cafs/*.c")
file(GLOB_RECURSE SRC_UTIL ${CMAKE_SOURCE_DIR} "utils/*.c")
file(GLOB_RECURSE SRC_AWS ${CMAKE_SOURCE_DIR} "aws/*.c")

idf_component_register(SRCS "main.c" "cafs.c" ${SRC_UI} ${SRC_UTIL} ${SRC_AWS} #${SRC_CAFS}
                    INCLUDE_DIRS "." "secret" "ui" "utils" "aws" #"cafs"
                    )
