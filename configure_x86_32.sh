#!/bin/bash
# this script should install everything you need to build for ubuntu (32bit)
curl -sL https://deb.nodesource.com/setup_4.x | sudo -E bash -
sudo apt-get install -y build-essential nodejs node-gyp libc6-dev libc6-dev-i386 gcc-4.8-multilib g++-4.8-multilib gcc-4.9-multilib g++-4.9-multilib libv8
sudo npm install -g npm
sudo npm upgrade

# 32bit libjpegturbo
wget http://downloads.sourceforge.net/project/libjpeg-turbo/1.4.2/libjpeg-turbo-official_1.4.2_i386.deb
sudo dpkg -i libjpeg-turbo-official_1.4.2_i386.deb
