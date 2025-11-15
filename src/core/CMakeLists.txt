add_library( LifeCore SHARED
    World.hpp
    World.cpp
    PatternsLibrary.hpp
    PatternsLibrary.cpp
    CellRules.hpp
    CellRules.cpp
    StandardCellRules.hpp
    StandardCellRules.cpp
    Engine.hpp
    Engine.cpp
    BasicEngine.hpp
    BasicEngine.cpp
    TiledEngine.hpp
    TiledEngine.cpp
    MapReduceEngine.hpp
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
