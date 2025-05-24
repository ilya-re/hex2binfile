#include <io.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	// Parse command line arguments.
	char const *InputFilename = NULL, *OutputFilename = NULL;
	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-i") && strlen(argv[i + 1])) {InputFilename  = argv[i + 1];}
		if (!strcmp(argv[i], "-o") && strlen(argv[i + 1])) {OutputFilename = argv[i + 1];}
	}
	// If no filenames provided, print help and exit.
	if (!(InputFilename && OutputFilename)) {
		puts("Convert a text file containing hex data to a binary file\n"
			 "The input file is case-insensitive, any non-hex characters are skipped\n"
			 "-i <filename>  input file\n"
			 "-o <filename> output file\n");
		return 0;
	}
	// Open the input and output files.
	FILE *InputFile = NULL, *OutputFile = NULL;
	InputFile = fopen(InputFilename, "rt");
	if (!InputFile) {
		perror("Failed to open the input file");
		return errno;
	}
	OutputFile = fopen(OutputFilename, "wb");
	if (!OutputFile) {
		perror("Failed to create the output file");
		return errno;
	}
	// Convert the text file to a binary one.
	unsigned int BytesWritten = 0;
	bool IsFirstDigit = true;
	char ConvertBuf[3] = {0, 0, 0};
	for (int InputChar = fgetc(InputFile); InputChar != EOF; InputChar = fgetc(InputFile)) {
		if (!isxdigit(InputChar)) { continue; }				// Skip over non-hex characters.
		if (IsFirstDigit) {ConvertBuf[0] = InputChar;}		// Put the first hex digit into the buffer.
		else {
			ConvertBuf[1] = InputChar;						// Put the second hex digit into the buffer.
			uint8_t Byte = strtol(ConvertBuf, NULL, 16);	// Convert the hex string to a byte.
			fwrite(&Byte, 1, 1, OutputFile);				// Write the byte into the output file.
			BytesWritten++;
		}
		IsFirstDigit = !IsFirstDigit;
	}
	fclose(InputFile);
	fclose(OutputFile);
	printf("%u bytes written\n", BytesWritten);
	return 0;
}
