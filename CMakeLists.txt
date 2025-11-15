cmake_minimum_required( VERSION 3.20 )

project( Life VERSION 0.1.0 LANGUAGES CXX )

find_package( ECM 6.0.0 REQUIRED NO_MODULE )
set( CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )

include( GenerateExportHeader )
include( KDEInstallDirs6 )
include( KDECMakeSettings    NO_POLICY_SCOPE )
include( KDECompilerSettings NO_POLICY_SCOPE )
include( ECMFindQmlModule )
include( ECMQmlModule )

find_package( Qt6 REQUIRED
    COMPONENTS
    Core
    Concurrent
    Gui
    Graphs
    Quick
    QuickControls2
    QuickWidgets
    Widgets
)

find_package( KF6 REQUIRED
    COMPONENTS
    Kirigami
    I18n
    CoreAddons
    QQC2DesktopStyle
    IconThemes
)
ecm_find_qmlmodule( org.kde.kirigami REQUIRED )

add_subdirectory( src )

install( PROGRAMS eu.catwitch.life.desktop DESTINATION ${KDE_INSTALL_APPDIR} )

feature_summary( WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES )
