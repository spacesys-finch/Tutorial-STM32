# H7 I2C Tutorial
This project demonstates how to use the I2C (Inter-Integrated Circuit) protocol to communicate with the DS1307 real time clock module.

As you will see in the code, the RTC's time registers are set to Monday, October 25th 2021, 00:00:00 and 24h mode is used. Every second, the date and time are read from the RTC's registers and following conversions from BCD to decimal, are output through USART3.

The DS1307 used Binary Coded Decimals (BCDs) to store the date and time. This means it uses 4 bits to represent the decimal units digit and anywhere from 1 to 3 bits for the tens digit, depending on the register (see documentation below). For example, 25 minutes in decimal would be represented in the BCD format as 0x25 in hex or 010 0101 in binary. Therefore, you need to do the appropriate conversions before writing the DS1307's registers and after reading them.

Some useful documentation about I2C and the DS1307 can be found in the following links: https://forum.digikey.com/t/using-the-stm32cube-hal-i2c-driver-in-master-mode/15122 and https://datasheets.maximintegrated.com/en/ds/DS1307.pdf
