#!/bin/bash

# Name of the development container
NAME=dev-life

# Name of the build directory inside the projet directory.
# It will be created if needed.
BUILD_DIR=build


# Generate the directory names
project_dir=$(dirname $(realpath $0))
build_path="${project_dir}/${BUILD_DIR}"

# Prepare or refresh the build directory
toolbox run -c "${NAME}" cmake -B "${build_path}" -S "${project_dir}"

# Build the project
toolbox run -c "${NAME}" cmake --build "${build_path}"

echo "The binaries are ready in ${build_path}/bin."
