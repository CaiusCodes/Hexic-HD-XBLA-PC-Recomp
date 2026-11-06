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
    # Window and taskbar icon (src/hexic_hd.rc -> packaging/hexic_hd.ico).
    enable_language(RC)
    list(APPEND HEXICHD_SOURCES src/hexic_hd.rc)
    add_executable(hexic_hd WIN32 ${HEXICHD_SOURCES})
else()
    add_executable(hexic_hd ${HEXICHD_SOURCES})
endif()

rexglue_setup_target(hexic_hd GPU_PLUGINS xenos)

if(WIN32)
    # Direct XInput polling for the Settings panel's controller navigation;
    # WinHTTP and CNG (SHA-256) for Settings > Updates (src/hexic_update.h).
    target_link_libraries(hexic_hd PRIVATE Xinput9_1_0.lib winhttp.lib bcrypt.lib)
endif()

# The version (Check for Updates compares it with GitHub's latest release) comes
# from the VERSION file, as the launcher's and the release ZIP's do. It goes into
# a generated header that only src/hexic_hd_app.h includes, so a new version
# rebuilds main.cpp alone, not the recompiled game code.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" HEXIC_VERSION LIMIT_COUNT 1)
string(STRIP "${HEXIC_VERSION}" HEXIC_VERSION)
file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/hexic_version/hexic_version.h"
     CONTENT "#pragma once\n// Generated from VERSION by CMakeLists.txt.\n#define HEXIC_VERSION \"${HEXIC_VERSION}\"\n")
# (On main.cpp only: a target-wide include path would change every generated
# file's compile command and rebuild them all.)
set_source_files_properties(src/main.cpp PROPERTIES
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/hexic_version")

# Diagnostic-only: per-guest-function Tracy zones for reverse-engineering
# which recompiled functions run when a given menu screen is reached. Not
# for shipping builds (adds a Tracy zone to every single guest call).
option(HEXICHD_PROFILE_GUEST_FUNCTIONS "Enable per-guest-function Tracy zones" OFF)
if(HEXICHD_PROFILE_GUEST_FUNCTIONS)
    target_compile_definitions(hexic_hd PRIVATE
        REXGLUE_PROFILE_GUEST_FUNCTIONS
        REXGLUE_ENABLE_PROFILING)
endif()
