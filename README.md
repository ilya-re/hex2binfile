# hex2binfile
Command-line hex text to binary file converter

Usage: hex2binfile -i <input filename> -o <output filename>
The input (text) file is case-insensitive, any non-hex characters are skipped.
The output file is a binary file generated from the text file.

hex2binfile.c is the multibyte version, for Linux and newer Windows that can work with UTF-8.
hex2binfile-unicode.c is the wide-character version, for older Windows that don't work with UTF-8. When compiling it with GCC, specify the -municode parameter.
