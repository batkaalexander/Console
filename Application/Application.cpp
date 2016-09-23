// Application.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "..\Library\Library.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void DisplayUsage(char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help" << std::endl;
	std::cout << "\t-n \"Filename\" k - vypis k poslednych riadkov filu" << std::endl;
	std::cout << "\t-c \"Filename\" k - vypis k poslednych charakterov filu" << std::endl;
}

std::string GetLastXChars(char* filename, char* numberOf)
{
	std::string temp = numberOf;
	std::stringstream convert(temp);
	int number;
	convert >> number;
	std::vector<char> LastX;
	std::ifstream infile(filename, std::ios::in);
	char c = infile.get();
	while (infile.good())
	{
		if (LastX.size() < number)
		{
			LastX.push_back(c);
		}
		else
		{
			LastX.push_back(c);
			LastX.erase(LastX.begin());
		}
		c = infile.get();
	}
	if (LastX.size() == 0 && number != 0)
	{
		std::cout << "File " << filename << " nemohol byt otvoreny" << std::endl;
		return "";
	}
	else
	{
		std::string returning(LastX.begin(), LastX.end());
		return returning;
	}

}

std::vector<std::string> GetLastXLines(char* filename, char* numberOf)
{
	std::string temp = numberOf;
	std::stringstream convert(temp);
	int number;
	convert >> number;
	std::vector<std::string> LastX;
	std::ifstream infile(filename, std::ios::in);
	std::string line;
	while (std::getline(infile, line))
	{
		if (LastX.size() < number)
		{
			LastX.push_back(line);
		}
		else
		{
			LastX.push_back(line);
			LastX.erase(LastX.begin());
		}
	}
	if (LastX.size() == 0 && number != 0)
	{
		std::cout << "File " << filename << " nemohol byt otvoreny" << std::endl;
	}
	return LastX;

}
int main(int argc, char **argv)
{
	int c;
	std::vector<std::string> vec;
	if (argc == 1)
	{
		DisplayUsage(argv[0]);
	}
	else
	{
		while ((c = getopt(argc, argv, "hn:c:")) != EOF)
		{
			switch (c)
			{
			case 'h':
				DisplayUsage(argv[0]);
				break;
			case 'c':
				std::cout << GetLastXChars(optarg, argv[optind]) << std::endl;
				break;
			case 'n':
				vec = GetLastXLines(optarg, argv[optind]);
				for (int i = 0; i < vec.size(); i++)
				{
					std::cout << vec[i] << std::endl;
				}
				break;
			case '?':
				std::wcout << "Chybny parameter '" << argv[optind - 1] << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			}
		}
	}
	std::cout << "Press any key to continue" << std::endl;
	getchar();
	return 0;
}

