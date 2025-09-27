
qt_add_library( LifeCore SHARED
    World.cpp
    PatternsLibrary.cpp
    CellRules.cpp
    StandardCellRules.cpp
    Engine.cpp
    BasicEngine.cpp
    TiledEngine.cpp

    MapReduceEngine.cpp
)

target_include_directories( LifeCore PUBLIC . )

target_link_libraries( LifeCore
    PRIVATE
        Qt6::Core
        Qt6::Concurrent
        Qt6::Gui
        Qt6::Widgets
)

set_target_properties( LifeCore PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE    ON
)
