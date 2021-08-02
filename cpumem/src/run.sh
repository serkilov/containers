#!/bin/sh

logfile="run.log"

echo "[`date`] begin to run test"
if [ "X$MEMORY_NUM" = "X" ] ; then
    MEMORY_NUM=100
fi

if [ "X$CPU_PERCENT" = "X" ] ; then
    CPU_PERCENT=10
fi


cpubin=cpubin
memorybin=membin

gcc cpu.c -o $cpubin
gcc nummem.c -o $memorybin
chmod +x $cpubin
chmod +x $memorybin
./$memorybin $MEMORY_NUM | tee $logfile
./$cpubin $CPU_PERCENT | tee $logfile

echo "[`date`] end of running"
exit 0

