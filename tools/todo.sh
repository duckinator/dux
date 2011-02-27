#!/bin/sh

DIR=$(dirname $(readlink -f $0))
cd $DIR/..
grep -EHnr 'TODO:' src include
echo
echo
grep -EHnr 'FIXME:' src include
