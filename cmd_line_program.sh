#!/bin/bash

# Execute script with binary file argument to 
# program stm32 through st link device
# port settings currently set to SWD
# can also change port to jtag by setting it as
# port=JTAG

# to run this on, open command prompt and run
# bash cmd_line_program.sh <hex_file>

echo GO
ST-LINK_CLI.exe -c SN=0049002C3137510B39383538 SWD -ME -P $1 -Run 0x08000000
