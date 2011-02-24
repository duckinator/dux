#!/bin/sh

ARCH=$(echo "$2" | tr [a-z] [A-Z])
BUILDTYPE=$(echo "$1" | tr [a-z] [A-Z])

LBUILDTYPE=$(echo "$1" | tr [A-Z] [a-z])

VERSION=$(git describe --tags HEAD | cut -c2-)-${LBUILDTYPE}


echo  "#ifndef DUX_BUILDINFO_H"
echo  "#define DUX_BUILDINFO_H"
echo  "#define SCM_REV \"$(git show | head -n1 | cut -c8-)\""
echo  "#define DUX_BUILDTYPE \"${BUILDTYPE}\""
echo  "#define DUX_VERSION \"${VERSION}\""
echo  "#define DUX_ARCH \"$2\""
echo  "#define DUX_${ARCH}"
echo  "#define DUX_FULLNAME \"Dux $2 ${VERSION}\" "
echo  "#endif"
