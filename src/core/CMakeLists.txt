add_library( LifeCore SHARED
    World.cpp
    PatternsLibrary.cpp
    CellRules.cpp
    StandardCellRules.cpp
    Engine.cpp
    BasicEngine.cpp
    TiledEngine.cpp
    MapReduceEngine.cpp
)
generate_export_header( LifeCore )

target_include_directories( LifeCore PUBLIC . )

target_link_libraries( LifeCore
    PRIVATE
    Qt6::Core
    Qt6::Concurrent
    Qt6::Gui
)

install( TARGETS LifeCore ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )
