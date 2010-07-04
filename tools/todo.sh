#!/bin/sh

DIR=$(dirname $(readlink -f $0))
cd $DIR/..
grep -EHnr 'TODO|FIXME' src include
