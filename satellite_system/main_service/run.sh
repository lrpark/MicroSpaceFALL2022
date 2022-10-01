#!/bin/bash
docker run -v /home/antoinebichara/workspace/MicroSpaceFALL2022/satellite_system/main_service/config.yaml:/user/src/app/config.yaml:ro --network=host vehicle.main_service