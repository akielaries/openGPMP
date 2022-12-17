#! /bin/sh
#                        ___  ______________ _   __
#                        |  \/  |_   _| ___ \ | / /
#   ___  _ __   ___ _ __ | .  . | | | | |_/ / |/ / 
#  / _ \| '_ \ / _ \ '_ \| |\/| | | | |  __/|    \ 
# | (_) | |_) |  __/ | | | |  | | | | | |   | |\  \
#  \___/| .__/ \___|_| |_\_|  |_/ \_/ \_|   \_| \_/
#       | |                                        
#       |_|                                        
#
# Install dependencies for some of the modules 

# home directory of your filesystem
cd ~
# install graphic library from libxbgi
# fetch the src file
wget https://sourceforge.net/projects/libxbgi/files/xbgi-365.tar.gz
# extract package
tar zxvf xbgi-365.tar.gz
# enter the package and the src directory
cd xbgi-365/src
# configure
make
# install
sudo make install

