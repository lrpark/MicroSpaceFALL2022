#!/bin/bash

echo "[cloud_service] Building..."
# Copy in the latest protobuf messages 
echo "[cloud_service] Copying dependencies"
cp ../main_service/message_pb2.py .
cp ../main_service/config_pb2.py .
cp ../../common/BaseApp.py .
cp ../../common/TCPClient.py .
cp ../../common/TCPServer.py .
cp ../../common/UDPClient.py .

# Build the docker image and tag it
docker build -t ground.cloud_service .
echo "[cloud_service] Done!"