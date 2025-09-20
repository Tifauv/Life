
qt_add_executable( Life
    WorldView.cpp
    MainWindow.cpp
    main.cpp
)

target_link_libraries( Life
    PRIVATE
        Qt6::Core
        Qt6::Concurrent
        Qt6::Gui
        Qt6::Widgets
        LifeCore )

set_target_properties( Life PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE    ON
)
