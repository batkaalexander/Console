// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include <string>

#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

extern LIBRARY_API int optind;
extern LIBRARY_API char *optarg;

LIBRARY_API int getopt(int argc, char *argv[], char *optstring);
LIBRARY_API std::string GetLastXChars(std::istream& input, int numberOf);
LIBRARY_API std::string GetLastXLines(std::istream& input, int numberOf);
