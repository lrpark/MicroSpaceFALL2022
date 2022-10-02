#!/bin/bash
docker run -v /home/admin/MicroSpaceFALL2022/depot_system/main_service/config.yaml:/usr/src/app/config.yaml:ro --network=host depot.main_service