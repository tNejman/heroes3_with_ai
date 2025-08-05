cmake_minimum_required(VERSION 3.16.0)
project(Heroes3App LANGUAGES CXX)
set(APP_NAME Heroes3App)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJ_HEADER_FILTER "^${CMAKE_SOURCE_DIR}/(include/src)/")
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy-19
    -p=${CMAKE_BINARY_DIR}
    -header-filter=${PROJ_HEADER_FILTER}
    --warnings-as-errors=*
)

# set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# GTest - flags must be declared prior to Fetch because Fetch automatically builds target
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Windows ONLY
# set(gtest_disable_pthreads ON CACHE BOOL "" FORCE) # optional

# Flags must be set here and used for targets GTest and SFML to leave markers-
# that will be used in compilation of /src
# set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=undefined -g")
# set(CMAKE_CXX_FLAGS "-fsanitize=address -g")
# set(CMAKE_CXX_FLAGS "-fsanitize=undefined -g")

# SFML - flags must be declared prior to Fetch because Fetch automatically builds target
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_USE_SYSTEM_DEPS OFF CACHE BOOL "" FORCE)
set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)

# === Dependencies ===
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(SFML)

foreach(t 
        gtest gtest_main gmock gmock_main
        sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
    if(TARGET ${t})
        set_target_properties(${t} PROPERTIES CXX_CLANG_TIDY "")
    endif()
endforeach()

# === Modules ===
set(MODULES
    Algorithms
    Artifacts
    Battle
    Characters
    Game
    Graphic
    LoadAndSaveTools
    Magic
    Miscellaneous
    Player
    Resource
    Units
    WorldMap
    CACHE INTERNAL "List of module targets"
)

# === Compilation flags ===
option(CODE_COVERAGE "Enable code coverage" ON)

function(enable_compiler_flags_debug target)
    if(TARGET ${target})
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE
                -std=c++${CMAKE_CXX_STANDARD} -g -O0
                -Wall -Wextra -Wpedantic -Werror
                -Wcast-align=strict # warn whenever a pointer is cast such that the required aligmnent of the target is increased, e.g. char* to int*
                -Wcast-qual # warn whever a pointer is cast so as to remove a type qualifier from the target, e.g. const char * to char *

                # OR when making a cast that introduces a type qualifier in an unsafe way, e.g. char ** to const char **
                -Wconversion -Wsign-conversion
                -Wshadow
                -Wdouble-promotion -Wnull-dereference
                -Wformat=2 -Wduplicated-cond -Wduplicated-branches
                -Wlogical-op -Wuseless-cast -Wzero-as-null-pointer-constant
                -Wvla -Wshift-overflow=2 -Wstringop-overflow=4
                -Wnarrowing -Wuninitialized

                # -fanalyzer
                # -D_GLIBCXX_DEBUG
                # -D_FORTIFY_SOURCE=3
                # -fstack-protector-strong -fstack-clash-protection
                # -fcf-protection

                # -fsanitize=address
                # -fsanitize=undefined
            )
            target_link_libraries(${target} PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${target} PRIVATE
                -std=c++${CMAKE_CXX_STANDARD} -g -O0
                -Wall -Wextra -Wpedantic -Werror
                -Wcast-align -Wcast-qual
                -Wconversion -Wsign-conversion
                -Wshadow
                -Wdouble-promotion -Wnull-dereference
                -Wformat -Wformat-pedantic
                -Wzero-as-null-pointer-constant
                -Wvla -Wshift-overflow -Wnarrowing -Wuninitialized
            )
        else()
            message(WARNING "Unexpected compiler used: ${CMAKE_CXX_COMPILER_ID}")
        endif()

        if(CODE_COVERAGE)
            target_compile_options(${target} PRIVATE
                --coverage
            )
            target_link_libraries(${target} PRIVATE
                --coverage
            )
        endif()
    else()
        message(WARNING "Target '${target}' not found - skipping compiler flags")
    endif()
endfunction()

function(enable_compiler_flags_release target)
    if(TARGET ${target})
        target_compile_options(${target} PRIVATE
            -std=c++${CMAKE_CXX_STANDARD}
            -O2
            -fno-omit-frame-pointer # do not use frame pointer for functions that don't need one
        )
    else()
        message(WARNING "Target '${target}' not found - skipping compiler flags")
    endif()
endfunction()

foreach(module ${MODULES})
    add_subdirectory(src/${module})
    target_link_libraries(${module} PRIVATE sfml-system)

    # enable_compiler_flags_debug(${module})

    enable_compiler_flags_release(${module})
endforeach()

# === Executable ===
add_subdirectory(app)
enable_compiler_flags_debug(${APP_NAME})

# === Tests ===
enable_testing()
add_subdirectory(tests)