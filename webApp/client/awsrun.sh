#!/bin/bash

options="--v=3"
options="$optihns --threadNum=12"
options="$options --host=http://52.34.66.11:28080"
options="$options --kind=memory --memory=120 --delay=550"
#options="$options --kind=cpu --cpu=100"
options="$options --time=100"
echo "$options"
./_output/webclient $options
