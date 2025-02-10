cmake_minimum_required(VERSION 3.10)
project(MINDROVE_GET_DATA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

macro(configure_msvc_runtime)
    if(MSVC)
        if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
            set(MSVC_RUNTIME "static_debug")
        else()
            set(MSVC_RUNTIME "static")
        endif()

        # Set compiler options.
        set(variables
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )

        if(${MSVC_RUNTIME} STREQUAL "static")
            message(STATUS "MSVC -> forcing use of statically-linked runtime (Release).")
            foreach(variable ${variables})
                if(${variable} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
                endif()
            endforeach()
        elseif(${MSVC_RUNTIME} STREQUAL "static_debug")
            message(STATUS "MSVC -> forcing use of statically-linked debug runtime.")
            foreach(variable ${variables})
                if(${variable} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MTd" ${variable} "${${variable}}")
                endif()
            endforeach()
        endif()
    endif()
endmacro()

# Link MSVC runtime statically
configure_msvc_runtime()

set(SDK_RELEASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/mindrovesdk-5.1.4-win-x64" CACHE PATH "Path to the Mindrove SDK release directory")

set(mindrove_INCLUDE_DIRS "${SDK_RELEASE_DIR}/inc")
set(MindrovePath "${SDK_RELEASE_DIR}/lib/Mindrove${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(MLModulePath "${SDK_RELEASE_DIR}/lib/MLModule${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(DataHandlerPath "${SDK_RELEASE_DIR}/lib/DataHandler${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(BoardControllerPath "${SDK_RELEASE_DIR}/lib/BoardController${CMAKE_STATIC_LIBRARY_SUFFIX}")

# Install directory
set(INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Function to add executables and install them
function(add_and_install_executable target_name source_file)
    add_executable(${target_name} ${source_file})

    target_include_directories(${target_name} PUBLIC ${mindrove_INCLUDE_DIRS})

    target_link_libraries(${target_name} PUBLIC
        ${MindrovePath}
        ${MLModulePath}
        ${DataHandlerPath}
        ${BoardControllerPath}
    )

    set(INSTALL_DIR_SPEC "${INSTALL_DIR}/${target_name}")

    install(TARGETS ${target_name} RUNTIME DESTINATION ${INSTALL_DIR_SPEC})
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory \"${SDK_RELEASE_DIR}/lib\" \"${INSTALL_DIR_SPEC}\")")

endfunction()

# Adding executables
add_and_install_executable(get_data get_data/src/get_data.cpp)
add_and_install_executable(markers get_data/src/markers.cpp)
add_and_install_executable(get_data_twice get_data/src/get_data_twice.cpp)
add_and_install_executable(multiple_streamers get_data/src/multiple_streamers.cpp)
add_and_install_executable(syncbox_get_data get_data/src/syncbox_get_data.cpp)
add_and_install_executable(eeg_metrics ml/src/eeg_metrics.cpp)
add_and_install_executable(eeg_metrics_ci ml/src/eeg_metrics_ci.cpp)
add_and_install_executable(band_power_all signal_processing/src/band_power_all.cpp)
add_and_install_executable(band_power signal_processing/src/band_power.cpp)
add_and_install_executable(csp signal_processing/src/csp.cpp)
add_and_install_executable(denoising signal_processing/src/denoising.cpp)
add_and_install_executable(downsampling signal_processing/src/downsampling.cpp)
add_and_install_executable(ica signal_processing/src/ica.cpp)
add_and_install_executable(peaks_detection signal_processing/src/peaks_detection.cpp)
add_and_install_executable(serialization signal_processing/src/serialization.cpp)
add_and_install_executable(signal_filtering signal_processing/src/signal_filtering.cpp)
add_and_install_executable(transforms signal_processing/src/transforms.cpp)
add_and_install_executable(windowing signal_processing/src/windowing.cpp)

# Custom command to copy release/lib contents to the bin directory
