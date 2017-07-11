#!/bin/sh

ARCH=$(echo "$2" | tr [a-z] [A-Z])

UPPER_CASE_BUILD_TYPE=$(echo "$1" | tr [a-z] [A-Z])

LOWER_CASE_BUILD_TYPE=$(echo "$1" | tr [A-Z] [a-z])

VERSION=$(git describe --tags HEAD | cut -c2-)-${LOWER_CASE_BUILD_TYPE}


echo  "#ifndef DUX_BUILD_INFO_H"
echo  "#define DUX_BUILD_INFO_H"
echo  "#define DUX_SCM_REV \"$(git show | head -n1 | cut -c8-)\""
echo  "#define DUX_BUILD_TYPE \"${UPPER_CASE_BUILD_TYPE}\""
echo  "#define DUX_VERSION \"${VERSION}\""
echo  "#define DUX_ARCH \"${ARCH}\""
echo  "#define DUX_${ARCH}"
echo  "#define DUX_FULL_NAME \"Dux ${ARCH} ${VERSION}\""
echo  "#endif"
