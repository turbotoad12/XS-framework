#!/bin/bash
set -e

DEVKITPRO=${DEVKITPRO:-/opt/devkitpro}
PORTLIBS="${PORTLIBS:-$DEVKITPRO/portlibs/3ds}"

echo "Building XS Framework..."
make

echo "Installing XS Framework to $PORTLIBS"

# Create dirs
mkdir -p "$PORTLIBS/include"
mkdir -p "$PORTLIBS/lib"

# Iterate all files and directories under include/ and remove any existing
# matching files from $PORTLIBS/include before copying the new ones.
while IFS= read -r -d '' src; do
	# Get relative path under include/
	rel=${src#include/}
	dest="$PORTLIBS/include/$rel"

	if [ -e "$dest" ] || [ -L "$dest" ]; then
		echo "Removing existing: $dest"
		sudo rm -rf "$dest"
	fi

	# Ensure destination directory exists
	destdir=$(dirname "$dest")
	mkdir -p "$destdir"

	echo "Copying $src -> $dest"
	sudo cp -r "$src" "$dest"
done < <(find include -mindepth 1 -print0)

# Copy your static library
echo "Copying library to $PORTLIBS/lib/"
sudo cp lib/libxs-framework.a "$PORTLIBS/lib/"

echo "XS Framework installed!"
echo "Make sure to use the provided templates!"
