cmake_minimum_required(VERSION 3.16)
project(CircuitSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Precompiled Headers
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts Network Svg)

add_executable(CircuitSimulator
resources.qrc
src/Core/pch.h
src/Core/main.cpp

# --- View Files ---
src/View/mainwindow.cpp
src/View/plotter.cpp
src/View/simulationdialog.cpp
src/View/componentdialog.cpp
src/View/graphicsview.cpp         # <-- Core functions only
src/View/graphicsview_placement.cpp  # <-- Component placement functions
src/View/graphicsview_wire.cpp       # <-- Wire drawing functions
src/View/graphicsview_editing.cpp    # <-- Component editing functions
src/View/circuitcomponent.cpp    # <-- New
src/View/resistor.cpp            # <-- New
src/View/capacitor.cpp           # <-- New
src/View/inductor.cpp            # <-- New
src/View/voltagesource.cpp       # <-- New
src/View/diode.cpp
src/View/zenerdiode.cpp          # <-- New Zener diode
src/View/wire.cpp
src/View/ground.cpp
src/View/currentsource.cpp
src/View/subcircuitview.cpp

# --- Model, Controller, Network ---
src/Model/circuitmodel.cpp
src/Model/analysis_engine.cpp
src/Controller/applicationcontroller.cpp
src/Network/networkmanager.cpp
)

target_include_directories(CircuitSimulator PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src/Core
${CMAKE_CURRENT_SOURCE_DIR}/src/View
${CMAKE_CURRENT_SOURCE_DIR}/src/Model
${CMAKE_CURRENT_SOURCE_DIR}/src/Controller
${CMAKE_CURRENT_SOURCE_DIR}/src/Network
${CMAKE_CURRENT_SOURCE_DIR}/libs
)

# Precompiled Headers
target_precompile_headers(CircuitSimulator PRIVATE src/Core/pch.h)

target_link_libraries(CircuitSimulator PRIVATE
Qt6::Core
Qt6::Gui
Qt6::Widgets
Qt6::Charts
Qt6::Network
Qt6::Svg
)

