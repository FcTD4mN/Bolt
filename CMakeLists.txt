CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
CMAKE_POLICY(SET CMP0054 NEW)

# Project name
PROJECT(Bolt C CXX)
MESSAGE( "CMAKE PROJECT : ${PROJECT_NAME}")

# Utilities functions
include(${CMAKE_SOURCE_DIR}/../CMake/Configurations/UtilityFunctions.cmake)

# Basic configurations (OS, Arch, Target, CmakeModules, BuildTypes etc... )
include(${CMAKE_SOURCE_DIR}/../CMake/Configurations/BasicConfiguration.cmake)

# Loading right OS Module
IF( LINUX )
    include(${CMAKE_SOURCE_DIR}/../CMake/Configurations/LinuxConfig.cmake)
ELSEIF( WINDOWS )
    include(${CMAKE_SOURCE_DIR}/../CMake/Configurations/WindowsConfig.cmake)
ELSEIF( MACOSX )
    include(${CMAKE_SOURCE_DIR}/../CMake/Configurations/MacOSXConfig.cmake)
ENDIF()

# DEFINITIONS
SetDefinitions()
ADD_SUBDIRECTORY( ../src CMAKE_OutputFiles/src )

# RESOURCES
FILE(GLOB_RECURSE RESOURCE_FILES RELATIVE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/resources/*")

SET_SOURCE_FILES_PROPERTIES(HEADER_FILES PROPERTIES HEADER_FILE_ONLY TRUE)
ADD_EXECUTABLE(${PROJECT_NAME}
                ${SRC_FILES} ${HEADER_FILES}
                ${MAIN_SRC_FILES}
                ${MAIN_HEADER_FILES}
                ${RESOURCE_FILES})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LINK_LIBS})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_BUILD_TYPE}${ARCH}")


# TARGETS options
SetCompileOptions( ${PROJECT_NAME} )


IF(LINUX OR WINDOWS)
    ADD_CUSTOM_COMMAND(TARGET  ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                               ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
ELSEIF(MACOSX)
    ADD_CUSTOM_COMMAND(TARGET  ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                               ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources)
ENDIF()

MESSAGE( "CMAKE PROJECT : ${PROJECT_NAME} configured")
