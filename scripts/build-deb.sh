#!/bin/bash

set -e

PKG_NAME="xs-framework"
PKG_VERSION="2.0"
PKG_ARCH="amd64"
PKG_MAINTAINER="TurboToad12 <me@turbotoad.space>"
PKG_DESCRIPTION="XS Framework - A simple C++ framework for 3DS homebrew development."
PKG_DEPENDS="devkitpro-pacman"


DEVKITPRO=${DEVKITPRO:-/opt/devkitpro}
PORTLIBS="${PORTLIBS:-$DEVKITPRO/portlibs/3ds}"


BUILD_DIR="build/${PKG_NAME}"
DEBIAN_DIR="${BUILD_DIR}/DEBIAN"

rm -rf "${BUILD_DIR}"
install -d -m 0755 "${DEBIAN_DIR}"

# Verify that permissions were applied correctly. On filesystems like WSL's /mnt/c (NTFS)
# chmod may appear to succeed but permissions are not enforced; dpkg-deb will fail.
actual_mode=$(stat -c%a "${DEBIAN_DIR}") || actual_mode=""
if [ "${actual_mode}" != "755" ]; then
	echo "WARNING: Failed to set correct permissions on ${DEBIAN_DIR} (mode=${actual_mode})."
	echo "Falling back to packaging in a temporary Linux filesystem directory so the .deb can be built."
	TMP_BASE=$(mktemp -d)
	PACK_ROOT="${TMP_BASE}/${PKG_NAME}_${PKG_VERSION}"
	mkdir -p "${PACK_ROOT}/DEBIAN"
	DEBIAN_DIR="${PACK_ROOT}/DEBIAN"
	echo "Packaging will use temporary directory: ${PACK_ROOT}"
else
	PACK_ROOT="${BUILD_DIR}"
fi

mkdir -p "${PACK_ROOT}/${PORTLIBS}/include"
mkdir -p "${PACK_ROOT}/${PORTLIBS}/lib"

# Create control file
mkdir -p "${DEBIAN_DIR}"
cat > "${DEBIAN_DIR}/control" <<EOF
Package: ${PKG_NAME}
Version: ${PKG_VERSION}
Section: base
Priority: optional
Architecture: ${PKG_ARCH}
Maintainer: ${PKG_MAINTAINER}
Depends: ${PKG_DEPENDS}
Description: ${PKG_DESCRIPTION}
EOF

# Build project
echo "Building XS Framework..."
make
# Copy files
cp -r include/* "${PACK_ROOT}/${PORTLIBS}/include/"
cp -r lib/* "${PACK_ROOT}/${PORTLIBS}/lib/"


# Set correct permissions for packaging
chmod -R go-w "${PACK_ROOT}"
chmod 0755 "${DEBIAN_DIR}"

# Build the .deb package
dpkg-deb --build "${PACK_ROOT}"

OUT_DEB="${PACK_ROOT}.deb"
if [ "${PACK_ROOT}" != "${BUILD_DIR}" ]; then
	mkdir -p "${BUILD_DIR}"
	mv "${OUT_DEB}" "${BUILD_DIR}/"
	echo "Debian package created and moved to: ${BUILD_DIR}/$(basename "${OUT_DEB}")"
	# clean up temporary packaging root
	rm -rf "${TMP_BASE}"
else
	echo "Debian package created: ${OUT_DEB}"
fi