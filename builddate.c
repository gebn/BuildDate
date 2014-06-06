#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "builddate.h"

const char *version_string = "0.1";

int main(int argc, char *argv[])
{
	FILE *file; /* the dll to examine */
	time_t timestamp; /* the build date of the above file */
	char *formatted; /* the formatted build date */

	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		print_help();
		return EXIT_SUCCESS;
	}

	file = fopen(argv[1], "r");
	if (!file) {
		fatal("Failed to open file '%s'.", argv[1]);
	}

	timestamp = get_linker_timestamp(file);
	if (timestamp == -1) {
		fatal("Failed to read linker timestamp.");
	}
	fclose(file);

	formatted = format_build_date(gmtime(&timestamp));
	printf("Build date: %s\n", formatted);
	free(formatted);

	return EXIT_SUCCESS;
}

static void print_help()
{
	printf("BuildDate %s\n", version_string);
	printf("Retrieve the build date of a .NET assembly.\n");
	printf("Available at https://github.com/gebn/BuildDate\n");
	printf("Copyright (c) 2014 George Brighton\n\n");
	printf("Usage: builddate FILE\n\n");
	printf("Options:\n");
	printf("  --help	Display this help\n\n");
}

static time_t get_linker_timestamp(FILE *file)
{
	const long int peOffset = 60; /* start of the Portable Executable header */
	const long int linkerTimestampOffset = 8; /* start of the IMAGE_FILE_HEADER section within the PE header */

	unsigned char bytes[4];

	if (!file) {
		return -1;
	}

	fseek(file, peOffset, SEEK_SET);
	read_bytes(file, 4, bytes); /* read 4 bytes - a 32 bit int */

	fseek(file, get_int32_t(bytes) + linkerTimestampOffset, SEEK_SET);
	read_bytes(file, 4, bytes);

	return (time_t)get_int32_t(bytes);
}

static void read_bytes(FILE *file, const size_t n, unsigned char *bytes)
{
	if (!fread(bytes, n, 1, file)) {
		fatal("Error reading from file.");
	}
}

static inline int32_t get_int32_t(const unsigned char *bytes)
{
	return bytes[0] | ((int32_t)bytes[1] << 8) | ((int32_t)bytes[2] << 16) | ((int32_t)bytes[3] << 24);
}

static char *format_build_date(const struct tm *time)
{
	const size_t length = 24;

	char *buffer = malloc(length * sizeof(char));
	strftime(buffer, length, "%Y-%m-%d %H:%M:%S UTC", time);
	return buffer;
}

static void fatal(const char *format, ...)
{
	va_list list;
	va_start(list, format);
	vfprintf(stderr, format, list);
	va_end(list);
	printf("\n");
	exit(EXIT_FAILURE);
}
