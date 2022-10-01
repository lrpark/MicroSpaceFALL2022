#!/bin/bash
set -e
set -o pipefail

# Build the critical infrastructure (i.e. any service)
cd ./main_service/ # order important here, goes first, then rest of files copy
./build.sh
cd ../hal_service/
./build.sh
cd ../logger_service/
./build.sh
cd ../sdr_app/
./build.sh

# Build the custom apps
cd ../autonomy_app/
./build.sh
cd ../demo_app/
./build.sh

# Remove the old dangling images to reduce disk usage (TODO: Make this work)
# docker rmi $(docker images -qa -f 'dangling=true') 