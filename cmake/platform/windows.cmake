function(bolt_build_extlib extlib_name extlib_dir extlib_install_path)
    if( NOT ${extlib_name}_ALREADY_BUILT )
        set(${extlib_name}_BUILD_DIR "${extlib_dir}/_build_release_64")
        if( NOT IS_DIRECTORY "${${extlib_name}_BUILD_DIR}")
            file(MAKE_DIRECTORY "${${extlib_name}_BUILD_DIR}")
        endif()

        # if( EXISTS "${extlib_dir}/CMakeLists.txt" )
        #     bolt_exec_process( cmake "${${extlib_name}_BUILD_DIR}" .. -DCMAKE_INSTALL_PREFIX=${extlib_install_path} -DCMAKE_BUILD_TYPE=Release "${ARGN}" )
        # elseif(EXISTS "${extlib_dir}/configure")
        #     bolt_exec_process( ../configure "${${extlib_name}_BUILD_DIR}" --prefix=${extlib_install_path} "${ARGN}")
        # endif()
        # bolt_exec_process( make "${${extlib_name}_BUILD_DIR}" install -j 10 )
        
        set( ${extlib_name}_ALREADY_BUILT ON CACHE INTERNAL "${extlib_name} already built")
    else()
        bolt_print_output("${extlib_name} already built")
    endif()
endfunction(bolt_build_extlib)

function(bolt_build_ext_libs extlib_dir extlib_install_path )
    bolt_build_extlib(SFML "${extlib_dir}/SFML" "${extlib_install_path}")
    bolt_build_extlib(GLM "${extlib_dir}/glm" "${extlib_install_path}")
    bolt_build_extlib(TINYXML2 "${extlib_dir}/tinyxml2" "${extlib_install_path}")
    bolt_build_extlib(CPYTHON "${extlib_dir}/cpython" "${extlib_install_path}")

    set(CMAKE_PREFIX_PATH  "C:/Qt/5.10.1/msvc2017_64/lib/cmake/" ${extlib_install_path} ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
endfunction(bolt_build_ext_libs)

function(bolt_find_libs)
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

    set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)
    set( LINK_LIBS ${LINK_LIBS} PARENT_SCOPE)
endfunction(bolt_find_libs)