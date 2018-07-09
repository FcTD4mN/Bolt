CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
CMAKE_POLICY(SET CMP0054 NEW)

# Project name
project(Bolt C CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_BOLT "help string describing option" ON)
option(BUILD_EDITOR "help string describing option" ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

set(INCLUDE_DIRECTORIES "")
set(LINK_LIBS "")

find_package(Threads REQUIRED)
SET(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${Threads_INCLUDE_DIRS})
SET(LINK_LIBS ${LINK_LIBS} ${CMAKE_THREAD_LIBS_INIT})

find_package(GLM REQUIRED)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GLM_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${OPENGL_INCLUDE_DIR})
set( LINK_LIBS ${LINK_LIBS} ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GLEW_INCLUDE_DIR})
set( LINK_LIBS ${LINK_LIBS} ${GLEW_LIBRARIES})

find_package(PythonLibs REQUIRED)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${PYTHON_INCLUDE_DIR})
set( LINK_LIBS ${LINK_LIBS} ${PYTHON_LIBRARIES})

find_package(TinyXML2 REQUIRED)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${TINYXML2_INCLUDE_DIR})
set( LINK_LIBS ${LINK_LIBS} ${TINYXML2_LIBRARIES})

find_package(SFML REQUIRED network audio graphics window system)
set( INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${SFML_INCLUDE_DIR})
set( LINK_LIBS ${LINK_LIBS} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Editor dependencies
if( BUILD_EDITOR )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt5Widgets 5.10)
    find_package(Qt5Core 5.10)
endif()

file(GLOB_RECURSE ALL_SRC_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE ALL_HEADER_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*.h*")

function(bolt_extract_include_dirs header_files result_varname)
    set(header_directories "")
    foreach(header in ${header_files})
        get_filename_component(tmp ${header} DIRECTORY)
        list( APPEND header_directories ${tmp})
    endforeach(header in ${header_files})
    list(REMOVE_DUPLICATES header_directories)

    set(${result_varname} ${header_directories} PARENT_SCOPE)
endfunction(bolt_extract_include_dirs)

set( COMMON_SRC_FILES ${ALL_SRC_FILES})
set( COMMON_HEADER_FILES ${ALL_HEADER_FILES})

list(FILTER COMMON_SRC_FILES EXCLUDE REGEX ".*(Editor.*|Core.main.cpp)")
list(FILTER COMMON_HEADER_FILES EXCLUDE REGEX ".*Editor.*")

bolt_extract_include_dirs("${COMMON_HEADER_FILES}" COMMON_INCLUDE_DIRECTORIES)

set( COMMON_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${COMMON_INCLUDE_DIRECTORIES})

set_source_files_properties(COMMON_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
add_library(${PROJECT_NAME}Common OBJECT ${COMMON_SRC_FILES} ${COMMON_HEADER_FILES})
target_compile_options(${PROJECT_NAME}Common PUBLIC "-std=c++17")
target_include_directories(${PROJECT_NAME}Common PUBLIC ${COMMON_INCLUDE_DIRECTORIES})

if( BUILD_BOLT )
    set( GAME_SRC_FILES ${ALL_SRC_FILES})
    
    list(FILTER GAME_SRC_FILES INCLUDE REGEX ".*Core.main.cpp")

    set( GAME_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GAME_INCLUDE_DIRECTORIES})

    set_source_files_properties(GAME_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME} ${GAME_SRC_FILES} $<TARGET_OBJECTS:${PROJECT_NAME}Common>)
    target_compile_options(${PROJECT_NAME} PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME} ${LINK_LIBS} "stdc++fs")
endif( BUILD_BOLT )

if( BUILD_EDITOR )
    set( EDITOR_SRC_FILES ${ALL_SRC_FILES})
    set( EDITOR_HEADER_FILES ${ALL_HEADER_FILES})

    list(FILTER EDITOR_SRC_FILES INCLUDE REGEX ".*Editor.*")
    list(FILTER EDITOR_HEADER_FILES INCLUDE REGEX ".*Editor.*")

    bolt_extract_include_dirs("${EDITOR_HEADER_FILES}" EDITOR_INCLUDE_DIRECTORIES)

    message("EDITOR_INCLUDE_DIRECTORIES: ${EDITOR_INCLUDE_DIRECTORIES}")

    set( EDITOR_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${EDITOR_INCLUDE_DIRECTORIES})

    set_source_files_properties(EDITOR_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME}Editor ${EDITOR_SRC_FILES} ${EDITOR_HEADER_FILES} $<TARGET_OBJECTS:${PROJECT_NAME}Common>)
    target_compile_options(${PROJECT_NAME}Editor PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME}Editor PRIVATE ${EDITOR_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME}Editor ${LINK_LIBS} "stdc++fs" Qt5::Core Qt5::Widgets)
endif( BUILD_EDITOR )
