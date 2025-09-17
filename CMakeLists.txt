cmake_minimum_required( VERSION 3.16 )

project( Life VERSION 0.1.0 LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED on )

find_package( Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_subdirectory( src )
