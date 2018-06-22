#!/bin/bash

set -x
url=http://10.10.200.97:28080/memwork.php

curl -H "Content-Type: application/x-www-form-urlencoded" -X POST -d "value=100&memory=20" $url

#curl -H "Content-Type: application/x-www-form-urlencoded" -X PUT -d "value=100&memory=20" $url
