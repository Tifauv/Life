#!/bin/bash

NAME=dev-life-fc42

toolbox run -c "${NAME}" cmake -B build -S .
toolbox run -c "${NAME}" cmake --build build
