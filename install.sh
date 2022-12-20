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
# UNINSTALL openMTPK-related binaries/files created from installation

cd /usr/local/lib
sudo rm -f libopenMTPK.so*
echo "removing openMTPK shared object"

cd /usr/local/include/
sudo rm -rf openMTPK
echo "removing openMTPK includes"

cd /usr/local/share/
sudo rm -rf openMTPK/
echo "removing openMTPK shared folder"

