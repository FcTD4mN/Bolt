CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
CMAKE_POLICY(SET CMP0054 NEW)

# Project name
project(Bolt C CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_BOLT "help string describing option" ON)
option(BUILD_EDITOR "help string describing option" ON)
option(USE_BOLTEXTLIBS "help string describing option" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#basic conf

IF( WIN32 )
    SET( WINDOWS 1 )
ELSEIF( APPLE )
    SET(MACOSX 1)
ELSEIF( UNIX )
    SET(LINUX 1)
ELSEIF( MINGW )
    SET(WINDOWS 1)
ELSEIF( CYGWIN )
    SET(WINDOWS 1)
ELSE()
    MESSAGE("WHAT IS THIS PLATFORM ?")
    RETURN()
ENDIF()

function(bolt_print_output imessage)
    message(STATUS "${imessage}")
endfunction(bolt_print_output)

function(bolt_print_error imessage)
    message(FATAL_ERROR "${imessage}")
endfunction(bolt_print_error)

function(bolt_extract_include_dirs header_files result_varname)
    set(header_directories "")
    foreach(header in ${header_files})
        get_filename_component(tmp ${header} DIRECTORY)
        list( APPEND header_directories ${tmp})
    endforeach(header in ${header_files})
    list(REMOVE_DUPLICATES header_directories)

    set(${result_varname} ${header_directories} PARENT_SCOPE)
endfunction(bolt_extract_include_dirs)

function(bolt_exec_process CMD WORKING_DIRECTORY)
    execute_process(COMMAND ${CMD} ${ARGN}
                    WORKING_DIRECTORY "${WORKING_DIRECTORY}"
                    OUTPUT_QUIET
                    ERROR_QUIET
                    RESULT_VARIABLE R
                    OUTPUT_VARIABLE O
                    ERROR_VARIABLE E)
    if(NOT R EQUAL 0)
        bolt_print_output("${O}")
        bolt_print_error("${E}")
    endif()
endfunction(bolt_exec_process)

function(bolt_build_extlib extlib_name extlib_dir extlib_install_path)
    if( NOT ${extlib_name}_ALREADY_BUILT )
        set(${extlib_name}_BUILD_DIR "${extlib_dir}/_build_release_64")
        if( NOT IS_DIRECTORY "${${extlib_name}_BUILD_DIR}")
            file(MAKE_DIRECTORY "${${extlib_name}_BUILD_DIR}")
        endif()

        if( EXISTS "${extlib_dir}/CMakeLists.txt" )
            bolt_exec_process( cmake "${${extlib_name}_BUILD_DIR}" .. -DCMAKE_INSTALL_PREFIX=${extlib_install_path} -DCMAKE_BUILD_TYPE=Release "${ARGN}" )
        elseif(EXISTS "${extlib_dir}/configure")
            bolt_exec_process( ../configure "${${extlib_name}_BUILD_DIR}" --prefix=${extlib_install_path} "${ARGN}")
        endif()
        bolt_exec_process( make "${${extlib_name}_BUILD_DIR}" install -j 10 )
        
        set( ${extlib_name}_ALREADY_BUILT ON CACHE INTERNAL "${extlib_name} already built")
    else()
        bolt_print_output("${extlib_name} already built")
    endif()
endfunction(bolt_build_extlib)


if( USE_BOLTEXTLIBS )
    set(BOLT_EXTLIBS_DIR "${CMAKE_CURRENT_LIST_DIR}/BoltExtlibs")
    bolt_exec_process( git "${CMAKE_CURRENT_LIST_DIR}" submodule update --init )
    bolt_exec_process( git "${BOLT_EXTLIBS_DIR}" submodule update --init )
    set(BOLT_EXTLIBS_INSTALLDIR "${BOLT_EXTLIBS_DIR}/_install/release-64")
    
    bolt_build_extlib(SFML "${BOLT_EXTLIBS_DIR}/SFML" "${BOLT_EXTLIBS_INSTALLDIR}")
    bolt_build_extlib(GLM "${BOLT_EXTLIBS_DIR}/glm" "${BOLT_EXTLIBS_INSTALLDIR}")
    bolt_build_extlib(TINYXML2 "${BOLT_EXTLIBS_DIR}/tinyxml2" "${BOLT_EXTLIBS_INSTALLDIR}")
    bolt_build_extlib(CPYTHON "${BOLT_EXTLIBS_DIR}/cpython" "${BOLT_EXTLIBS_INSTALLDIR}" --enable-optimizations)
    
    set(EXTLIBS_DEPENDENCIES ${CMAKE_DL_LIBS} -lutil)

    set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/BoltExtlibs/_install/release-64 ${CMAKE_PREFIX_PATH})
endif()


set(INCLUDE_DIRECTORIES "")
set(LINK_LIBS "")

find_package(Threads REQUIRED)
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${Threads_INCLUDE_DIRS})
set(LINK_LIBS ${LINK_LIBS} ${CMAKE_THREAD_LIBS_INIT})

find_package(GLM REQUIRED)
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GLM_INCLUDE_DIRS})

set(OpenGL_GL_PREFERENCE "GLVND")
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

set( LINK_LIBS ${LINK_LIBS} stdc++fs)

if( LINUX )
    set(BOLT_DEFINITIONS LINUX)
elseif(WINDOWS)
    set(BOLT_DEFINITIONS WINDOWS)
endif()

##################################################

file(GLOB_RECURSE ALL_SRC_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE ALL_HEADER_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src/*.h*")

set( COMMON_SRC_FILES ${ALL_SRC_FILES})
set( COMMON_HEADER_FILES ${ALL_HEADER_FILES})

list(FILTER COMMON_SRC_FILES EXCLUDE REGEX ".*(Editor.*|Core.main.cpp)")
list(FILTER COMMON_HEADER_FILES EXCLUDE REGEX ".*Editor.*")

bolt_extract_include_dirs("${COMMON_HEADER_FILES}" COMMON_INCLUDE_DIRECTORIES)

set( COMMON_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${COMMON_INCLUDE_DIRECTORIES})

set_source_files_properties(COMMON_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
add_library(${PROJECT_NAME}Common STATIC ${COMMON_SRC_FILES} ${COMMON_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME}Common PUBLIC ${BOLT_DEFINITIONS})
target_compile_options(${PROJECT_NAME}Common PUBLIC "-std=c++17")
target_include_directories(${PROJECT_NAME}Common PUBLIC ${COMMON_INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME}Common ${LINK_LIBS} ${EXTLIBS_DEPENDENCIES})

if( BUILD_BOLT )
    set( GAME_SRC_FILES ${ALL_SRC_FILES})

    list(FILTER GAME_SRC_FILES INCLUDE REGEX ".*Core.main.cpp")

    set( GAME_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GAME_INCLUDE_DIRECTORIES})

    set_source_files_properties(GAME_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME} ${GAME_SRC_FILES})
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${BOLT_DEFINITIONS})
    target_compile_options(${PROJECT_NAME} PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Common)
endif( BUILD_BOLT )

if( BUILD_EDITOR )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt5Widgets 5.10)
    find_package(Qt5Core 5.10)

    set( EDITOR_SRC_FILES ${ALL_SRC_FILES})
    set( EDITOR_HEADER_FILES ${ALL_HEADER_FILES})

    list(FILTER EDITOR_SRC_FILES INCLUDE REGEX ".*Editor.*")
    list(FILTER EDITOR_HEADER_FILES INCLUDE REGEX ".*Editor.*")

    bolt_extract_include_dirs("${EDITOR_HEADER_FILES}" EDITOR_INCLUDE_DIRECTORIES)

    set( EDITOR_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${EDITOR_INCLUDE_DIRECTORIES})

    set_source_files_properties(EDITOR_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME}Editor ${EDITOR_SRC_FILES} ${EDITOR_HEADER_FILES})
    target_compile_definitions(${PROJECT_NAME}Editor PUBLIC ${BOLT_DEFINITIONS})
    target_compile_options(${PROJECT_NAME}Editor PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME}Editor PRIVATE ${EDITOR_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME}Editor Qt5::Core Qt5::Widgets ${PROJECT_NAME}Common)
endif( BUILD_EDITOR )
