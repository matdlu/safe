#!/bin/sh
# $1 - path to fltk config
grep -m 1 'LDLIBS=".*"' "$1" | sed -e 's/LDLIBS="//' -e 's/\"/ /'
