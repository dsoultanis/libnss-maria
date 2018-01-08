#!/bin/sh
rm -rf Debug
mkdir Debug
sleep 2
docker exec -it libnssmaria_build_1 sh -c 'cd /home/libnss-maria/Debug && cmake -D CMAKE_BUILD_TYPE=Debug .. && make && ctest --verbose'