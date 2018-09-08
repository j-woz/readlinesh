#!/bin/bash
set -eu

# Make the Debian package

DEB=$1
ORIG_TGZ=$2
VERSION=$3

TOP=$PWD

BUILD_DIR=$( mktemp -d debian-XXX )
echo $BUILD_DIR
cd $BUILD_DIR

ln ../$ORIG_TGZ
tar xfz $ORIG_TGZ
pushd readlinesh-$VERSION > /dev/null

set -x
debuild -us -uc

popd
mv $DEB $TOP

pwd
cd $TOP
# rm -r $BUILD_DIR
