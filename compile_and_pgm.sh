#!/bin/bash

# This scripts compiles a binary, then executes
# uses st-link to program the mcu

# port settings currently set to SWD
# can also change port to jtag by setting it as
# port=JTAG

# make sure to copy this script into your project
# directory. Also this script assumes ST-LINK_CLI.exe
# is in the project directory. Will need to edit 
# the command in line 20 if this isn't the case.
# to run this open command prompt and run
# bash compile_and_pgm.sh <hex_file>


cd Debug
make -j4 all
ST-LINK_CLI.exe -c SN=0049002C3137510B39383538 SWD -ME -P $1 -Run 0x08000000
