#!/bin/sh
echo  "#define SCM_REV \"$(git show | head -n1 | cut -b9-)\""
echo  "#define DUX_BUILDTYPE \"$1\""
echo  "#define DUX_ARCH \"$2\""
