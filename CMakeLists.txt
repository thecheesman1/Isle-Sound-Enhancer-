cmake_minimum_required(VERSION 3.20)
project(isle_sound_enhancer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows static runtime, x64 by default
if(WIN32)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_executable(isle_sound_enhancer WIN32
  src/main.cpp
)

target_include_directories(isle_sound_enhancer PRIVATE src)

# Sources under these dirs are wired in by their owning pieces
# (webui_client / dsp / audio_hook implementations land as design doc gates).
