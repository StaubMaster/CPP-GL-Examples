#!/bin/bash

./Multi.exe &
EXE_PID=$!

wait $EXE_PID
EXE_RET=$?

echo '(ID|RET)' '('$EXE_PID'|'$EXE_RET')'
