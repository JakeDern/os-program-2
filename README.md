# prodcomm
prodcomm: Synchronized string processing

# Description
This program uses parallel processing to efficiently process strings from stdin and log them to stdout. When a string exceeding the length limit of 1024 characters is detected, an error message will be logged, the string is ignored, and stdin is flushed.

# Usage 
1. Compile with make
$```make```
2. Run prodcomm choosing to either pipe to stdin or input strings manually
$```./prodcomm < example_input.txt```
$```./prodcomm```

# Architecture
This program is divided into four main modules for processing and makes use of the synchronized_queue type to pass information back and forth. 

1. reader: This module reads strings from stdin and starts to feed them to munch1. Additionally it will handle any lines exceeding maximum lengths (currently 1024)

2. munch1: This module will replace all space characters with '*' characters

3. munch2: This module will replace all lower case letters with uppercase letters

4. writer: This module will write the resulting strings to stdout

5. synchronized_queue: This structure and its associated class is the heart of the program, utilizes monitor style synchronization to allow the other modules to work in tandem. 
