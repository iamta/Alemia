#!/bin/bash

ui_path="user-interface"
server_path="backend"

rm -rf production

# Create directory structure to gather all files
mkdir production 2>/dev/null
mkdir production/ui 2>/dev/null
mkdir production/server 2>/dev/null

# Get backend dependencies
python3 -m pip install pipreqs --quiet
pipreqs --force ./${server_path}/

# Copy to production directory
cp -r ./${server_path} ./production/server/
cp -r ./data ./production/server/
cp -r ./others ./production/server/

# Move Dockerfile
mv ./production/server/${server_path}/Dockerfile ./production/server/



# Get frontend dependencies
npm --prefix ./$ui_path install

# Build frontend sources
npm --prefix ./$ui_path run build

# Move the built files
mv ./${ui_path}/build/ ./production/ui/

# Move Dockerfile
cp ./${ui_path}/Dockerfile ./production/ui/

# Move nginx config file
cp ./${ui_path}/config.conf ./production/ui/

# Move docker-compose config
cp ./docker-compose.yml ./production

