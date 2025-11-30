#!/bin/bash

./Multi.exe > temp &
EXE_PID=$!

sleep 1

kill -s SIGINT $EXE_PID
wait $EXE_PID
EXE_RET=$?

echo '(ID|RET)' '('$EXE_PID'|'$EXE_RET')'
