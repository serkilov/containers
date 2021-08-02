#!/bin/bash

img=serkilov/cpumemload:latest
env="-e MEMORY_NUM=50 -e CPU_PERCENT=1"
docker run $env $img 
