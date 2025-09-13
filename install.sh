#!/bin/bash
set -e

DEVKITPRO=${DEVKITPRO:-/opt/devkitpro}
PORTLIBS="$DEVKITPRO/portlibs/3ds"


echo "Building XS Framework..."
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM
make clean
make

echo "Installing XS Framework to $PORTLIBS"

# Create dirs
mkdir -p "$PORTLIBS/include"
mkdir -p "$PORTLIBS/lib"

# Copy headers into the portlibs include folder
sudo cp -r include/* /opt/devkitpro/portlibs/3ds/include/

# Copy your static library
sudo cp lib/libxs-framework.a /opt/devkitpro/portlibs/3ds/lib/


echo "XS Framework installed!"
echo "Make sure to use the provided templates!"
