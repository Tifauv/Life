#!/bin/bash

NAME=dev-life-f43
PKGS="cmake
    extra-cmake-modules
    qt6-qtbase-devel
    qt6-qtdeclarative-devel
    qt6-qtquickcontrols2-devel
    kf6-kirigami2-devel
    kf6-ki18n-devel
    kf6-kcoreaddons-devel
    kf6-kiconthemes-devel
    kf6-qqc2-desktop-style"

toolbox create "${NAME}" --distro fedora --release 43
toolbox run -c "${NAME}" sudo dnf --assumeyes update
toolbox run -c "${NAME}" sudo dnf --assumeyes install ${PKGS}

