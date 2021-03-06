Chapter 9 Programming Project - Contiguous Memory Allocation

1. Do only the Best Fit Strategy.

2. As in past projects you must submit your souce code (a) in one file and (b,c,d) together in another file.
   No zip files to be submitted.

   Source code file name should be allocator_Initial of First Name_Last Name.c or cpp
   For example: allocator_JSvadlenka.c

   a) Well-documented source code
   b) Compilation instructions
   c) Write-up of your program design and issues enountered and resolved.
   d) Output according to format in (3) below of the script you executed in (4) below.

3) Please provide output as shown in the sample format below. This sample output is similar
   to that in the textbook for the Chapter 9 Programming Project - Contiguous Memory Allocation:

   allocator>STAT

   Addresses [0 : 315000] Process P1

   Addresses [315001 : 512500] Process P3

   Addresses [512501 : 625575] Free

   Addresses [625575 : 725100] Process P6

   Addresses [725001 : END ] Free

4. You must run the following script of RQ, RL, C, STAT commands as test input on your own computer
   and submit the output of execution of the 4 STAT commands. The memory size as input is 1 MB (1048576).
   Remember that Compaction moves processes towards the low end of addresses and free space to the high
   end of memory addresses. Memory addresses start at 0.

```
./allocator_JSvadlenka 1048576

RQ P0 262144 B
RQ P1 262144 B
RQ P2 262200 B
STAT

RL P1
RQ P3 200000 B
STAT

RQ P4 200000 B
STAT

C
STAT

QUIT
```
