# hexic_hd - ReXGlue Recompiled Project
#
# SDK boilerplate lives in generated/rexglue.cmake.

cmake_minimum_required(VERSION 3.25)
project(hexic_hd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)

# Sources
set(HEXICHD_SOURCES
    src/main.cpp
)

if(WIN32)
    add_executable(hexic_hd WIN32 ${HEXICHD_SOURCES})
else()
    add_executable(hexic_hd ${HEXICHD_SOURCES})
endif()

rexglue_setup_target(hexic_hd GPU_PLUGINS xenos)

if(WIN32)
    # Direct XInput polling for the Settings panel's controller navigation.
    target_link_libraries(hexic_hd PRIVATE Xinput9_1_0.lib)
endif()

# Diagnostic-only: per-guest-function Tracy zones for reverse-engineering
# which recompiled functions run when a given menu screen is reached. Not
# for shipping builds (adds a Tracy zone to every single guest call).
option(HEXICHD_PROFILE_GUEST_FUNCTIONS "Enable per-guest-function Tracy zones" OFF)
if(HEXICHD_PROFILE_GUEST_FUNCTIONS)
    target_compile_definitions(hexic_hd PRIVATE
        REXGLUE_PROFILE_GUEST_FUNCTIONS
        REXGLUE_ENABLE_PROFILING)
endif()
