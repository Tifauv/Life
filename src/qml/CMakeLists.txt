add_executable( Life_qml
    main.cpp
)

ecm_add_qml_module( Life_qml URI eu.catwitch.life )
ecm_target_qml_sources( Life_qml
    SOURCES
    MainWindow.qml
)

target_link_libraries( Life_qml
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    LifeCore
)

install( TARGETS Life_qml ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
