add_executable( Life
    StatsGraph.hpp
    StatsGraph.cpp
    WorldView.hpp
    WorldView.cpp
    MainWindow.hpp
    MainWindow.cpp
    main.cpp
)

ecm_add_qml_module( Life
    URI eu.catwitch.life
    VERSION 1.0
)

ecm_target_qml_sources( Life
    SOURCES
    StatsGraph.qml
)

target_link_libraries( Life
    PRIVATE
    Qt6::Core
    Qt6::Graphs
    Qt6::Gui
    Qt6::QuickWidgets
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    LifeCore
)

install( TARGETS Life ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
