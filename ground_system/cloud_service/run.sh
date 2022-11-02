#!/bin/bash
docker run -it -v /home/admin/.aws/credentials:/root/.aws/credentials:ro --network=host ground.cloud_service
