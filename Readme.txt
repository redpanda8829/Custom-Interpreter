This project involves writing an interpreter in C for a language that allows small arithmetic calculations. The limited number of allowed functions are:
set
print
add
subtract
multiply
divide


I approached this problem by creating two helper functions: setVariable and findVariable to set values for the variables and access them for the arithmetic operations.
For everything else I am using a switch statement after parsing through the lines of an executable file, .txt file or a line entered through stdin. Parsing is being done through the sscanf function.

The code utilizes the ascii values associated with chars 'a'-'z' and uses that to dynamically allocate values in the vars array, access them and update them as required. For printing purposes I am simply using the printf function from the C standard library.

I am calling my interpreter sam, hence the file is called sam.c