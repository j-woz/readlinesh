#!/bin/sh
set -eu

# For Debian package: Make the upstream TGZ

TGZ=$1
VERSION=$2
shift 2
FILES=$*

D=$( mktemp -d /tmp/readlinesh-XXX )
mkdir $D/readlinesh-$VERSION
cp -v --parents $FILES $D/readlinesh-$VERSION
tar cfz $TGZ -C $D readlinesh-$VERSION
rm -r $D
