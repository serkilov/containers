#!/bin/sh

logfile="run.log"

echo "[`date`] begin to run test"
echo "Mem: "$MEMORY_NUM
echo "CPU: "$CPU_PERCENT
if [ "X$MEMORY_NUM" = "X" ] ; then
    MEMORY_NUM=100
fi

if [ "X$CPU_PERCENT" = "X" ] ; then
    CPU_PERCENT=10
fi


cpumembin=cpumembin

gcc cpumem.c -o $cpumembin
chmod +x $cpumembin
echo "Mem: "$MEMORY_NUM
echo "CPU: "$CPU_PERCENT
./$cpumembin $CPU_PERCENT $MEMORY_NUM | tee $logfile

echo "[`date`] end of running"
exit 0

