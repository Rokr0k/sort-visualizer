CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

PROJECT(sort-visualizer)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

ADD_EXECUTABLE(sort-visualizer WIN32 MACOSX_BUNDLE "src/main.cpp" "src/window.cpp" "src/container.cpp" "src/algorithm.cpp" "src/render.cpp")

TARGET_LINK_LIBRARIES(sort-visualizer PRIVATE SDL2::SDL2main SDL2::SDL2 OpenGL::GL)