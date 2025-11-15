#!/bin/bash

NAME=dev-life-f43

toolbox run -c "${NAME}" cmake -B build -S .
toolbox run -c "${NAME}" cmake --build build
