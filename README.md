# Arbitrary Precision Calculator

Arbitrary-precision arithmetic or sometimes infinite-precision arithmetic, indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system. This contrasts with the faster fixed-precision arithmetic found in most arithmetic logic unit (ALU) hardware, which typically offers between 8 and 64 bits of precision.

Some example applications include: 
 - A common application is public-key cryptography, whose algorithms commonly employ arithmetic with integers having hundreds of digits.
 - Arbitrary precision arithmetic is also used to compute fundamental mathematical constants such as π to millions or more digits.

The goal of this project is to implement various mathematical operations of given two big numbers by storing the digits in a linked list. For my implementation following mathematical operations are considered:
 - Addition (+)
 - Subtraction (-)
 - Multiplication (x)
 - Division (/)

The number of digits in the resulting arithmetic operation for addition, subtraction and multiplication consists of as many digits required to represent the result without loss of precision. For division, because it may go on infinitely, the precision is capped to 200 digits after the decimal.

Usage:
| Operation | Syntax |
| ---- | ---- |
| Build Project | `make` |
| Addition | `./apcalc 3.34 + 56.23` |
| Subtraction | `./apcalc 45.32 - 5.23` |
| Multiplication | `./apcalc 32.435 x 3.45` |
| Division | `./apcalc 65.132 / 5.12` |
