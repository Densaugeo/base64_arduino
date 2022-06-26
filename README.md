# base64_arduino

Base64 encoder/decoder for arduino repo

[![npm](https://img.shields.io/npm/l/express.svg)]()
[![Build Status](https://travis-ci.com/Densaugeo/base64_arduino.svg?branch=master)](https://travis-ci.com/github/Densaugeo/base64_arduino)

## Installation

Add base64.cpp and base64.hpp to your project folder or library search path, put `#include "base64.hpp"` in your source, and pass base64.cpp to your compiler

## Usage (Arduino)

There is an example Arduino sketch in the `arduino-test` folder.

## Usage (libc)

Binary to base64 example:
~~~C++
unsigned char binary[] = {133, 244, 117, 206, 178, 195};
unsigned char base64[9]; // 8 bytes for output + 1 for null terminator

unsigned int base64_length = encode_base64(binary, 6, base64);

printf("%d\n", base64_length); // Prints "8"
printf((char *) base64); // Prints "hfR1zrLD"
~~~

Base64 to binary example:
~~~C++
unsigned char base64[] = "hfR1zrLD";
unsigned char binary[6];

unsigned int binary_length = decode_base64(base64, binary);

printf("%d\n", binary_length); // Prints "6"
printf("[%d, %d, %d, %d, %d, %d]\n", // Prints "[133, 244, 117, 206, 178, 195]"
       binary[0], binary[1], binary[2],
       binary[3], binary[4], binary[5]);
~~~

String to base64 example:
~~~C++
unsigned char string[] = "String example";
unsigned char base64[21]; // 20 bytes for output + 1 for null terminator

// encode_base64() places a null terminator automatically, because the output is a string
unsigned int base64_length = encode_base64(string, strlen((char *) string), base64);

printf("%d\n", base64_length); // Prints "20"
printf((char *) base64); // Prints "U3RyaW5nIGV4YW1wbGU="
~~~

Base64 to string example:
~~~C++
unsigned char base64[] = "U3RyaW5nIGV4YW1wbGU=";
unsigned char string[15]; // 14 bytes for output + 1 for null terminator

// decode_base64() does not place a null terminator, because the output is not always a string
unsigned int string_length = decode_base64(base64, string);
string[string_length] = '\0';

printf("%d\n", string_length); // Prints "14"
printf((char *) string); // Prints "String example"
~~~

## Details

By default, uses common web conventions - '+' for 62, '/' for 63, '=' for padding. Optionally, define the `BASE64_URL` macro to follow RFC 4648 §5 for filesystem/URL safe output ('-' for 62 and '_' for 63). Note that invalid base64 characters are interpreted as padding.

Can be compiled as C, uses .*pp extensions because it is usually used in C++ projects and is tested for C++.

## License

MIT
