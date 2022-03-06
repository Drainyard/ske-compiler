INPUT_FILE=$1
EXECUTABLE=$2

gcc -o $EXECUTABLE $INPUT_FILE -lm
retval=$?
if [ $retval -ne 0 ]; then
    echo "Linking failed with error code: $retval"
	exit 1
fi

rm $OUT_FILE 2> /dev/null
