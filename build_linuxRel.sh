#!/bin/sh
#
#To make this script executable type:
#chmod +x ./build_linuxRel.sh
#
#Place this shell script in the root of your Module
#and execute it to start the linux build process.
#Linux Release using ccmake (console-based cmake)
#This script assumes you have *already* setup the
#prerequisites described in 
echo "This script expects to be run from ..../repos/aburn/engine/\n"
echo "For detailed into on compiling engine and modules,"
echo "aburn/engine/LINUX_apt_install_pkgs_for_aburn.txt"
echo "Even more detailed (but slightly outdated packge info\n"
echo "Can be found in aburn/engine/docker/Dockerfile_aburn_dev\n"

mkdir br ; cd br
ccmake ../src/aftr
cd br

echo "After ccmake exits with a generate Makefile, type:"
echo "cd br ; make -j32\n"
echo "\n"
echo "Once compiled, run 'make install'"
