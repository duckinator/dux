#!/bin/sh

for x in `find src/modules -name '*.exe'`; do
  echo "Copying $x"
  cp $x isofs/modules
done
