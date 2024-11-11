#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Cleaning up previous builds..."
make maintainer-clean >/dev/null 2>&1 || true  # Ignore errors if Makefile isn't generated yet

echo "Running autoreconf to generate configuration files..."
autoreconf -i  # Generate configure and other files

echo "Running configure script..."
./configure

echo "Building the project with make..."
make

echo "Build completed successfully."

