MACRO(HEADER_DIRECTORIES return_list dir)
    FILE(GLOB_RECURSE new_list ${dir}/*.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

#HEADER_DIRECTORIES(MODEL_INCLUDE_DIRECTORIES ./)

#include_directories(/usr/X11R6/include/)
#link_directories(/usr/X11R6/lib)
#SET(EXTRA_LIBS GL X11 GLU glut)

########################### build core  ##################################

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(./)
link_directories(./)

FILE(GLOB_RECURSE MODEL_SRCS core/*.cxx)

add_library(ModelCore SHARED ${MODEL_SRCS})

#TARGET_LINK_LIBRARIES(ModelCore)
