CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
CMAKE_POLICY(SET CMP0054 NEW)

# Project name
project(Bolt C CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_BOLT "help string describing option" ON)
option(BUILD_EDITOR "help string describing option" ON)
option(USE_BOLTEXTLIBS "help string describing option" OFF)
option(COPY_PROJECT_SAMPLES "help string describing option" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#basic conf

include(${CMAKE_CURRENT_LIST_DIR}/cmake/utils.cmake)

IF( WIN32 )
    SET( WINDOWS 1 )
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/platform/windows.cmake)
ELSEIF( APPLE )
    SET(MACOSX 1)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/platform/macos.cmake)
ELSEIF( UNIX )
    SET(LINUX 1)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/platform/linux.cmake)
ELSEIF( MINGW )
    SET(WINDOWS 1)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/platform/windows.cmake)
ELSEIF( CYGWIN )
    SET(WINDOWS 1)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/platform/windows.cmake)
ELSE()
    MESSAGE("WHAT IS THIS PLATFORM ?")
    RETURN()
ENDIF()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if( USE_BOLTEXTLIBS )
    set(BOLT_EXTLIBS_DIR "${CMAKE_CURRENT_LIST_DIR}/BoltExtlibs")
    bolt_exec_process( git "${CMAKE_CURRENT_LIST_DIR}" submodule update --init )
    bolt_exec_process( git "${BOLT_EXTLIBS_DIR}" submodule update --init )
    set(BOLT_EXTLIBS_INSTALLDIR "${CMAKE_CURRENT_BINARY_DIR}/_install/release-64")
    if( WINDOWS AND "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
        set(BOLT_EXTLIBS_INSTALLDIR "${CMAKE_CURRENT_BINARY_DIR}/_install/debug-64")
    endif()
    
    message("${BOLT_EXTLIBS_INSTALLDIR}")
    bolt_build_ext_libs( "${BOLT_EXTLIBS_DIR}" "${BOLT_EXTLIBS_INSTALLDIR}")
    message("${CMAKE_PREFIX_PATH}")
endif()


set(INCLUDE_DIRECTORIES "")
set(LINK_LIBS "")

bolt_find_libs()

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

list(FILTER COMMON_SRC_FILES EXCLUDE REGEX ".*(Editor.*|GameMockup.*|Core.main.cpp)")
list(FILTER COMMON_HEADER_FILES EXCLUDE REGEX ".*(Editor|GameMockup).*")

bolt_extract_include_dirs("${COMMON_HEADER_FILES}" COMMON_INCLUDE_DIRECTORIES)

set( COMMON_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${COMMON_INCLUDE_DIRECTORIES})

set_source_files_properties(COMMON_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
add_library(${PROJECT_NAME}Common STATIC ${COMMON_SRC_FILES} ${COMMON_HEADER_FILES})
target_compile_definitions(${PROJECT_NAME}Common PUBLIC ${BOLT_DEFINITIONS})
target_compile_options(${PROJECT_NAME}Common PUBLIC "-std=c++17")
target_include_directories(${PROJECT_NAME}Common PUBLIC ${COMMON_INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME}Common ${LINK_LIBS} ${EXTLIBS_DEPENDENCIES})

set( CORE_SRC_FILES ${ALL_SRC_FILES})
list(FILTER CORE_SRC_FILES INCLUDE REGEX ".*Core.main.cpp")

add_executable(${PROJECT_NAME}Core ${CORE_SRC_FILES})
target_compile_definitions(${PROJECT_NAME}Core PUBLIC ${BOLT_DEFINITIONS})
target_compile_options(${PROJECT_NAME}Core PUBLIC "-std=c++17")
target_include_directories(${PROJECT_NAME}Core PRIVATE $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
target_link_libraries(${PROJECT_NAME}Core ${PROJECT_NAME}Common)
set_target_properties(${PROJECT_NAME}Core PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}Core>)

if( BUILD_BOLT )
    set( GAME_SRC_FILES ${ALL_SRC_FILES})
    set( GAME_HEADER_FILES ${ALL_HEADER_FILES})

    list(FILTER GAME_SRC_FILES INCLUDE REGEX ".*(GameMockup.*|Core.main.cpp)")
    list(FILTER GAME_HEADER_FILES INCLUDE REGEX ".*GameMockup.*")

    bolt_extract_include_dirs("${GAME_HEADER_FILES}" GAME_INCLUDE_DIRECTORIES)

    set( GAME_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${GAME_INCLUDE_DIRECTORIES})

    set_source_files_properties(GAME_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME}Game ${GAME_SRC_FILES})
    target_compile_definitions(${PROJECT_NAME}Game PUBLIC ${BOLT_DEFINITIONS} OVERRIDE_APPLICATION=1)
    target_compile_options(${PROJECT_NAME}Game PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME}Game PRIVATE ${GAME_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME}Game ${PROJECT_NAME}Common)
    set_target_properties(${PROJECT_NAME}Game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}Game>)
endif( BUILD_BOLT )

if( BUILD_EDITOR )
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt5Widgets 5.10)
    find_package(Qt5Core 5.10)

    add_library(${PROJECT_NAME}Common_tmp STATIC ${COMMON_SRC_FILES} ${COMMON_HEADER_FILES})
    target_compile_definitions(${PROJECT_NAME}Common_tmp PUBLIC ${BOLT_DEFINITIONS} EDITOR)
    target_compile_options(${PROJECT_NAME}Common_tmp PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME}Common_tmp PUBLIC ${COMMON_INCLUDE_DIRECTORIES})
    target_link_libraries(${PROJECT_NAME}Common_tmp ${LINK_LIBS} ${EXTLIBS_DEPENDENCIES})

    set( EDITOR_SRC_FILES ${ALL_SRC_FILES})
    set( EDITOR_HEADER_FILES ${ALL_HEADER_FILES})

    list(FILTER EDITOR_SRC_FILES INCLUDE REGEX ".*Editor.*")
    list(FILTER EDITOR_HEADER_FILES INCLUDE REGEX ".*Editor.*")

    bolt_extract_include_dirs("${EDITOR_HEADER_FILES}" EDITOR_INCLUDE_DIRECTORIES)

    set( EDITOR_INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${EDITOR_INCLUDE_DIRECTORIES})

    set_source_files_properties(EDITOR_HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
    add_executable(${PROJECT_NAME}Editor ${EDITOR_SRC_FILES} ${EDITOR_HEADER_FILES})
    target_compile_definitions(${PROJECT_NAME}Editor PUBLIC ${BOLT_DEFINITIONS} EDITOR)
    target_compile_options(${PROJECT_NAME}Editor PUBLIC "-std=c++17")
    target_include_directories(${PROJECT_NAME}Editor PRIVATE ${EDITOR_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${PROJECT_NAME}Common,INCLUDE_DIRECTORIES>)
    target_link_libraries(${PROJECT_NAME}Editor Qt5::Core Qt5::Widgets ${PROJECT_NAME}Common_tmp)
    set_target_properties(${PROJECT_NAME}Editor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}Editor>)

    if(WINDOWS)
        set(DLL_TO_COPY "")
        get_target_property(qt_core_dlls Qt5::Core IMPORTED_LOCATION_DEBUG)
        
        get_target_property(qt_widgets_dlls Qt5::Widgets IMPORTED_LOCATION_DEBUG)
        get_target_property(qt_widgets_dependencies Qt5::Widgets IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG)
        foreach( d IN LISTS qt_widgets_dependencies)
            get_target_property(qt_widgets_dependencies_dlls ${d} IMPORTED_LOCATION_DEBUG)
            set(DLL_TO_COPY ${DLL_TO_COPY} ${qt_widgets_dependencies_dlls})
        endforeach()
        # get_target_property(qt_core_dlls Qt5::Core IMPORTED_LOCATION_DEBUG)
        set(DLL_TO_COPY ${DLL_TO_COPY} ${qt_core_dlls} ${qt_widgets_dlls})

        LIST(REMOVE_DUPLICATES DLL_TO_COPY)
        foreach( dll IN LISTS DLL_TO_COPY )
            message("${dll}")
            ADD_CUSTOM_COMMAND(TARGET  ${PROJECT_NAME}Editor POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                    "${dll}" $<TARGET_FILE_DIR:${PROJECT_NAME}Editor>/)
        endforeach()
    endif()

endif( BUILD_EDITOR )

if( COPY_PROJECT_SAMPLES )
    ADD_CUSTOM_COMMAND(TARGET  ${PROJECT_NAME}Core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}Core>/resources)
endif()
