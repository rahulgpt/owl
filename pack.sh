#!/bin/bash

# create a new directory called "include"
mkdir include

# copy all the .h files from collections, systems, and utils to the corresponding subdirectory of "include"
mkdir -p include/collections && cp collections/*.h include/collections/
mkdir -p include/systems && cp systems/*.h include/systems/
mkdir -p include/utils && cp utils/*.h include/utils/
cp owl.h include/

# run the make file to create the lib

# static lib
make
# shared lib
make -e SHARED=1

# create a new tar file for the release
tar cvzf libowl-v0.1.0-amd64.tar.gz lib/*.so lib/*.a include

# remove the include dir
rm -rf include