#!/bin/sh

ARCH=$(echo "$2" | tr [a-z] [A-Z])

echo  "#define SCM_REV \"$(git show | head -n1 | cut -b9-)\""
echo  "#define DUX_BUILDTYPE \"$1\""
echo  "#define DUX_ARCH \"$2\""
echo  "#define $2"
echo  "#define $ARCH"
