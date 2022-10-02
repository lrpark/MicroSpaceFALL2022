#!/bin/bash
docker run -v /home/admin/MicroSpaceFALL2022/client_system/main_service/config.yaml:/usr/src/app/config.yaml:ro --network=host client.main_service