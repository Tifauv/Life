
qt_add_executable( Life
    World.cpp
    PatternsLibrary.cpp
    CellRules.cpp
    StandardCellRules.cpp
    Engine.cpp
    BasicEngine.cpp
    TiledEngine.cpp
    ThreadedEngine.cpp
    MapReduceEngine.cpp
    WorldView.cpp
    MainWindow.cpp
    main.cpp
)

target_link_libraries( Life PRIVATE Qt6::Core Qt6::Concurrent Qt6::Gui Qt6::Widgets )

set_target_properties( Life PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE    ON
)
