FUNCTION( SetDefinitions )

    SET(DEFINITIONS
        ${DEFINITIONS}
        -DWINDOWS
        -DNOMINMAX
        -D_CRT_SECURE_NO_WARNINGS
        -D_CRT_NON_CONFORMING_SWPRINTFS)


    IF(MSVC)
        SET(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE)

        FOREACH(CompilerFlag ${CompilerFlags})
            STRING(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        ENDFOREACH()

        SET(STATIC_POSTFIX "mt" CACHE STRING "Set static library postfix" FORCE)
        IF (ENABLE_MSVC_MP)
            ADD_DEFINITIONS(/MP)
        ENDIF()

    ELSE(MSVC)

        # Other compilers then MSVC don't have a static STATIC_POSTFIX at the moment
        SET(STATIC_POSTFIX "" CACHE STRING "Set static library postfix" FORCE)
        SET(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG}   -D_DEBUG")
        SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

    ENDIF(MSVC)

   #BUILD TYPES
    IF( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
    SET(DEFINITIONS
        ${DEFINITIONS}
        -DDEBUG

    ELSEIF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    SET( DEFINITIONS
        ${DEFINITIONS}
        -DRELEASE

    ENDIF()

    #COMPILERS
    IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    MESSAGE( "Using Clang as compiler" )
    SET( DEFINITIONS
        ${DEFINITIONS}
        -Wall
        -Wextra
        -Wconversion
        -Wno-multichar
        -Wno-deprecated-register
        -Werror=return-type
        -Werror=unicode-whitespace
        -Qunused-arguments
        #  -fcolor-diagnostics
        -Wno-pragma-once-outside-header
        -Werror=trigraphs
        -Wno-unused-parameter
        -ferror-limit=0)

    ELSEIF(CMAKE_COMPILER_IS_GNUCXX)
        MESSAGE( "Using GNU as compiler" )
        SET( DEFINITIONS
            ${DEFINITIONS}
            -Wall
            -Wno-multichar
            -Werror=return-type
            -fdiagnostics-color=always)

    ELSEIF(MSVC)
        MESSAGE( "Using MSVC as compiler" )
    ELSE()
        MESSAGE( "Unknown compiler : ${CMAKE_CXX_COMPILER_ID}" )
    ENDIF()

    ADD_DEFINITIONS(${DEFINITIONS})

    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE )
    SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} PARENT_SCOPE )
    SET(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} PARENT_SCOPE )
    SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE )
    SET(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} PARENT_SCOPE )
    SET(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} PARENT_SCOPE )
    SET(STATIC_POSTFIX ${STATIC_POSTFIX} PARENT_SCOPE )

ENDFUNCTION( SetDefinitions )

# CompileOptions
FUNCTION( SetCompileOptions iTargetName )

    SET_TARGET_PROPERTIES(${iTargetName} PROPERTIES LINK_FLAGS_DEBUG   "/SUBSYSTEM:WINDOWS")
    SET_TARGET_PROPERTIES(${iTargetName} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

ENDFUNCTION( SetCompileOptions )