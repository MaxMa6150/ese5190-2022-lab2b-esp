### TODO:

Create a REPL to let you read and write RP2040 registers from a console. You should be able to:
- select any 32-bit address to read/write (even if not a valid RP2020 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask


### Introduction:

In this part, we will basically use RP2040 and GPIO peripheral. The ideal program should be that when the program starts, it will ask the user to select/input a register address then choose to read/write. Once it finished expected reading/writing, it will print a success message from the console.



