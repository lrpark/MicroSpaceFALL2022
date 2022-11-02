#!/bin/bash
docker run -it -v /home/admin/MicroSpaceFALL2022/ground_system/main_service/config.yaml:/usr/src/app/config.yaml:ro --network=host ground.main_service
