#!/bin/bash

# Checks for dependencies
if ! [ "$(which arduino-cli 2>/dev/null)" ]; then
    echo "arduino-cli Not Found! Please install arduino-cli"
    DEPENDENCY_ERROR=true
fi

# Exits program if not all dependencies are ready
if [ "$DEPENDENCY_ERROR" = true ]; then
    exit -1
fi

# Parsing Environment Variables
while [ $# -gt 0 ]
do
    case $1 in
	-p|--port)
	    PORT="$2"
	    shift
	    shift
	    ;;
	-f|--file-location)
	    FILE_LOC="$2"
	    shift
	    shift
	    ;;
    esac
done


# Checks if Port and File Location has been set
if [ -z "$PORT" ]; then
    echo "Port not provided. Please provide a port by using -p <PORT> or --port <PORT>"
    MISSING_ARGUMENT=true
fi

if [ -z "$FILE_LOC" ]; then
    echo "The location of the Arduino Repository not provided. Please provide a location by using -f <LOCATION> or --file-location <LOCATION>"
    MISSING_ARGUMENT=true
fi

# Exits program if not all argument is provided
if [ "$MISSING_ARGUMENT" = true ]; then
    exit -1
fi


# Adds a '/' to the file location string (if needed) and re-assign as HEADER_FILE_NAME
if ! [ "${FILE_LOC: -1}" = "/" ]; then
    HEADER_FILE_NAME="${FILE_LOC}/"
else
    HEADER_FILE_NAME="${FILE_LOC}"
fi


# Defining the header file location
HEADER_FILE_NAME="${HEADER_FILE_NAME}uuid.h"
echo "Creating ${HEADER_FILE_NAME}..."

# Create the new header file in target directory
echo "#define EEPROM_SIZE 128

extern const String uuid_1 = \"$(uuidgen)\";
extern const String uuid_2 = \"$(uuidgen)\";
" > ${HEADER_FILE_NAME}


# Running the Arduino Cli to compile and run the program
arduino-cli compile --fqbn esp32:esp32:nodemcu-32s ${FILE_LOC}
arduino-cli upload -p ${PORT} --fqbn esp32:esp32:nodemcu-32s ${FILE_LOC}
