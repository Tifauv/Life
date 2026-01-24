#!/bin/bash

# Name of the development container
NAME=dev-life

# List of packages required in the container
PKGS="cmake
    extra-cmake-modules
    qt6-qtbase-devel
    qt6-qtdeclarative-devel
    qt6-qtquickcontrols2-devel
    qt6-qtgraphs-devel
    kf6-kirigami2-devel
    kf6-ki18n-devel
    kf6-kcoreaddons-devel
    kf6-kiconthemes-devel
    kf6-qqc2-desktop-style"

# Create the container only if it does not already exist
exists=$(toolbox list --containers | awk '$2 == "dev-life"' | wc -l)
if [[ $exists -eq 0 ]]
then # Create the toolbox container
    toolbox create "${NAME}" --distro fedora --release 43
fi

# Update and initialize the container
toolbox run -c "${NAME}" sudo dnf --assumeyes update
toolbox run -c "${NAME}" sudo dnf --assumeyes install ${PKGS}
