#include <time.h>

#ifdef _MSC_VER
	/* the VS compiler doesn't seem to have its own copy of inttypes.h */
	#include "inttypes.h"
	#define inline __inline
#else
	#include <inttypes.h>
#endif

/* BuildDate release */
extern const char *version_string;

/* print the documentation */
static void print_help();

/* retrieve the timestamp of a linked dll */
static time_t get_linker_timestamp(FILE *file);

/* seek relative to the beginning of a file, with error checking */
static void file_seek(FILE *file, const long int offset);

/* read n bytes from a file into bytes */
static void read_bytes(FILE *file, const size_t n, unsigned char *bytes);

/* turn an array of 4 bytes into its 32-bit signed integer equivalent */
static inline int32_t get_int32_t(const unsigned char *bytes);

/* format a time into a human-readable string */
static char *format_build_date(const struct tm *time);

/* print an error to stderr and exit */
static void fatal(const char *format, ...);
