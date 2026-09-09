# Power Digit Sum Generator

## Description

This program calculates a user-defined number raised to a user-defined power and then calculates the sum of the digits of the result.

The program takes two command-line arguments:
- 'a': the base
- 'b': the exponent

It then calculates 'a^b' using a custom 'power()' function and calculates the sum of the digits of the result.

## How to Compile

Use the Makefile by running:

make

## How to Run 

In the terminal, run:

./pds <a> <b>

## Input Validation

The program checks that the inputs contain only digits and that they fit within the required unsigned short range.
Invalid inputs such as letters or values that are too large produce an error message.