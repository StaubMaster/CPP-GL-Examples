#!/bin/bash

EXE_FILE=./Multi.exe
TEMP_FILE=temp
LIMIT=100

COUNT=0
RET_0=0
RET_1=0
while [ $COUNT -lt $LIMIT ]
do
	$EXE_FILE &
#	$EXE_FILE > $TEMP_FILE &
	EXE_PID=$!

#	check output to see if it loaded
#	also
#	direct output to file

	sleep 1
	kill -s SIGINT $EXE_PID

	wait $EXE_PID
	EXE_RET=$?

	echo '################################################'
	COUNT=$(( $COUNT + 1 ))
	if [ $EXE_RET -eq 0 ];
	then
		RET_0=$(( $RET_0 + 1 ))
	else
		RET_1=$(( $RET_1 + 1 ))
		cat $TEMP_FILE
	fi
	echo '################################################'

	echo '(ID|RET)' '('$EXE_PID'|'$EXE_RET')'
	echo 'Count/Limit (0|1)' $COUNT'/'$LIMIT '('$RET_0'|'$RET_1')'
done
