#!/bin/bash

echo "[depot_autonomy_app] Building..."
# Copy in the latest protobuf messages 
echo "[depot_autonomy_app] Copying dependencies"
cp ../main_service/message_pb2.py .
cp ../main_service/config_pb2.py .
cp ../../common/BaseApp.py .
cp ../../common/TCPClient.py .
cp ../../common/TCPServer.py .
cp ../../common/UDPClient.py .

# Build the docker image and tag it
docker build -t vehicle.depot_autonomy_app .
echo "[depot_autonomy_app] Done!"