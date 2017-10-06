cmake_minimum_required(VERSION 3.8)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Source/Utils/StringUtils.cpp Source/Utils/StringUtils.h Source/main.cpp Source/Graphics/EngineWindow.cpp Source/Graphics/EngineWindow.h Source/Graphics/Color.h Source/Common.h ../m3dcpp/m3dcpp.h Source/Graphics/Renderer.cpp Source/Graphics/Renderer.h Source/Utils/ScopeTimer.cpp Source/Utils/ScopeTimer.h Source/Application/Application.cpp Source/Application/Application.h Source/Application/Game.cpp Source/Application/Game.h Source/Graphics/UI/UI_Element.cpp Source/Graphics/UI/UI_Element.h Source/Graphics/SubWindow.cpp Source/Graphics/SubWindow.h Source/Input/InputHandler.cpp Source/Input/InputHandler.h Source/Utils/Timer.cpp Source/Utils/Timer.h Source/Graphics/SoftwareRenderer.cpp Source/Graphics/SoftwareRenderer.h)
link_directories(/home/genkinger/CLionProjects/m3dcpp/cmake-build-release)
add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine SDL2 m m3dcpp GLEW GL GLU)
