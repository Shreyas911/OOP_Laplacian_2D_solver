#!/bin/bash
# Add to path variable for make check - export  PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH
autoreconf -f -i
export PKGPATH=/work/00161/karl/stampede2/public
./configure --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34
