add_executable( Life
    WorldView.cpp
    MainWindow.cpp
    main.cpp
)

target_link_libraries( Life
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    LifeCore
)

install( TARGETS Life ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
