cmake_minimum_required(VERSION 3.0)
project(DIFFERENTIATOR)

set(SOURCES_FILE_NAME_LIB
    sources/filename/filename.cpp
)

set(SOURCES_TREE_LIB
    sources/tree/tree.cpp
)

set(SOURCES_REC_READ_LIB
    sources/rec_read/Rec_read.cpp
)

set(SOURCES_DUMP_LIB
    sources/dump/dump.cpp
)

set(SOURCES_DIFFER_LIB
    sources/differ/differ.cpp
)

# Создание статической библиотеки
add_library(Tree STATIC ${SOURCES_TREE_LIB})
add_library(Rec_read STATIC ${SOURCES_REC_READ_LIB})
add_library(Dump STATIC ${SOURCES_DUMP_LIB})
add_library(Differ STATIC ${SOURCES_DIFFER_LIB})
add_library(FileName STATIC ${SOURCES_FILE_NAME_LIB})

# Указываем директорию, где находятся заголовочные файлы библиотеки
target_include_directories(FileName PUBLIC ${PROJECT_SOURCE_DIR}/sources/filename)
target_include_directories(Tree PUBLIC ${PROJECT_SOURCE_DIR}/sources/tree)
target_include_directories(Rec_read PUBLIC ${PROJECT_SOURCE_DIR}/sources/rec_read)
target_include_directories(Dump PUBLIC ${PROJECT_SOURCE_DIR}/sources/dump)
target_include_directories(Differ PUBLIC ${PROJECT_SOURCE_DIR}/sources/differ)

target_link_libraries(Rec_read PUBLIC Tree)
target_link_libraries(Dump PUBLIC Tree)
target_link_libraries(Differ PUBLIC Dump Tree)

set(SOURCES_MAIN
    sources/main/exemple.cpp
)

add_executable(main ${SOURCES_MAIN})

target_link_libraries(main PRIVATE Differ Rec_read FileName) 

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})