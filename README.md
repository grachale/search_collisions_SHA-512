#  Zero-Bit Prefix Hash of SHA-512 Finder
The provided task is to implement a function or a set of functions for a program designed to find any message whose SHA-512 hash begins with a sequence of zero bits when represented from the leftmost side. In other words, the goal is to locate a message that produces a SHA-512 hash with a leading sequence of zeros.

## Details

This repository contains an implementation of a program to find a message whose SHA-512 hash begins with a sequence of zero bits when represented in big-endian format. In big-endian representation, the bits are ordered from most significant bit (MSB) to least significant bit (LSB), where Byte 0 starts with MSB and ends with LSB, Byte 1 starts with MSB and ends with LSB, and so on until the last byte.

For example, if two leading zero bits are required, the corresponding byte would be 0010 0111 (0x27).

### Function Parameters

int findHash(int bits, char **message, char **hash)

*bits: The desired number of zero bits in the hash.
message: An output parameter containing data for which the corresponding hash was found. The result is stored as a dynamically allocated hexadecimal C string (terminated with \0).
hash: An output parameter representing the hash of the message from the previous parameter. It is also a dynamically allocated hexadecimal C string.
Return Value: The function returns 1 on success, 0 on failure or incorrect parameters (e.g., an invalid number of zero bits).
