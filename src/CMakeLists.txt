
qt_add_executable( Life
    World.cpp
    PatternsLibrary.cpp
    Engine.cpp
    StandardEngine.cpp
    WorldView.cpp
    MainWindow.cpp
    main.cpp
)

target_link_libraries( Life PRIVATE Qt6::Gui Qt6::Widgets )

set_target_properties( Life PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE    ON
)
