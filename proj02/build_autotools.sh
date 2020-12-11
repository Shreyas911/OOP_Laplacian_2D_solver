#!/bin/bash
# Add to path variable for make check - export  PATH=/work/00161/karl/stampede2/public/bats/bin/:$PATH
autoreconf -f -i
export PKGPATH=/work/00161/karl/stampede2/public

### Option for petsc
./configure CC=mpicc CXX=mpicxx --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34 --with-hdf5=$TACC_HDF5_DIR --with-petsc=$TACC_PETSC_DIR

### Option for disabled petsc and make coverage
#./configure --with-petsc=$TACC_PETSC_DIR --with-masa=$PKGPATH/masa-gnu7-0.50 --with-grvy=$PKGPATH/grvy-gnu7-0.34 --with-hdf5=$TACC_HDF5_DIR --enable-coverage
