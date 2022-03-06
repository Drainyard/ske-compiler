#!/bin/bash

ASSEMBLY=$1
OUT_FILE=$2

echo "${ASSEMBLY}" | as -o $OUT_FILE
retval=$?
if [ $retval -ne 0 ]; then
    echo "Assembler failed with error code: $retval"
	exit 1
fi


exit 0
