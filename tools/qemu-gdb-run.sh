#!/bin/sh

qemu -s -S -fda $1 & disown
sleep 1
gdb -x tools/qemutarget.gdb $2

