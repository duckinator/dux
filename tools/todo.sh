#!/bin/sh

DIR=$(dirname $(readlink -f $0))
cd $DIR/..
grep -EHnir 'TODO:|FIXME:' src include
