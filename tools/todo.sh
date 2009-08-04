#!/bin/sh

grep -Hnr 'TODO|FIXME' `find -name '*.c'`
