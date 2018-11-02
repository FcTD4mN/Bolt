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

