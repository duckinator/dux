#!/bin/sh
echo  "#define SCM_REV \"$(git show | head -n1 | cut -b9-)\""
