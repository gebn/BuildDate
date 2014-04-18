# BuildDate

This is a simple, fast program for retrieving the build date of a .NET assembly using its PE header.

## Usage

	$ ./builddate FILE
	Build date: 2013-11-16 15:32:29 UTC

## Compilation

### GCC

	$ gcc builddate.c -Wall -Wextra -Werror -std=c99 -pedantic -O3 -o builddate

### MSVC

MSVC doesn't seem to have its own copy of the fixed size integer types, so the included `inttypes.h` must be present.

	>cl builddate.c
