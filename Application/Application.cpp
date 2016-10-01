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
	std::cout << "\t-f \"Filename\" subor na otvorenie" << std::endl;
}

std::string GetLastXChars(std::istream& input, int numberOf)
{
	std::string LastX;
	char c;
	while (input.get(c))
	{
		if (LastX.size() < numberOf)
		{
			LastX += c;
		}
		else
		{
			LastX += c;
			LastX.erase(LastX.begin());
		}
	}
	if (LastX.size() == 0 && numberOf != 0)
	{
		std::cout << "Zly vstup" << std::endl;
		return "";
	}
	else
	{
		return LastX;
	}

}

std::string GetLastXLines(std::istream& input, int numberOf)
{
	std::string line;
	std::string vystup;
	std::vector<std::string> LastX;
	while (std::getline(input, line))
	{
		if (LastX.size() < numberOf)
		{
			LastX.push_back(line);
		}
		else
		{
			LastX.push_back(line);
			LastX.erase(LastX.begin());
		}
	}
	if (LastX.size() == 0 && numberOf != 0)
	{
		std::cout << "Zly vstup" << std::endl;
		return "";
	}
	else
	{
		for each (std::string var in LastX)
		{
			vystup += var + "\n";
		}
	}
	return vystup;

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
		while ((c = getopt(argc, argv, "hn:c:f:")) != EOF)
		{
			switch (c)
			{
				case 'h':
				{
					DisplayUsage(argv[0]);
					break;
				}
				case 'f':
				{
					std::fstream file(optarg, std::fstream::in);
					if (file.is_open())
					{
						if (std::string(argv[optind - 2]) == "-c")
						{
							std::cout << GetLastXChars(file, atoi(argv[optind - 1]));
							file.close();
							break;
						}
						if (std::string(argv[optind - 2]) == "-n")
						{
							std::cout << GetLastXLines(file, atoi(argv[optind - 1]));
							file.close();
							break;
						}
						file.close();
						break;
					}
					else
					{
						std::cout << "Subor nemohol by otvoreny" << std::endl;
						std::cout << "Press any key to continue" << std::endl;
						getchar();
						return -1;
					}
					break;
				}
				case 'c':
				{
					if (argc == 3)
					{
						std::cout << GetLastXChars(std::cin, atoi(optarg));
						break;
					}

					if (argc == 4 && "-f" != argv[3])
					{
						std::string str(argv[3]);
						size_t pos = 0;
						while ((pos = str.find("\\n", pos)) != std::string::npos)
						{
							str.replace(pos, 2, "\n");
							pos += 2;
						};
						std::istringstream tmp(str);
						std::cout << GetLastXChars(tmp, atoi(optarg)) << std::endl;
						break;
					}

					std::fstream file(argv[optind + 1], std::fstream::in);
					if (!file.is_open())
					{
						std::cout << "Chyba suboru" << std::endl;
						std::cout << "Press any key to continue" << std::endl;
						getchar();
						return -1;
					}
					std::cout << GetLastXChars(file, atoi(optarg));
					file.close();
					std::cout << std::endl;
					optind = optind + 2;
					break;
				}
				case 'n':
				{
					if (argc == 3)
					{
						std::cout << GetLastXLines(std::cin, atoi(optarg));
					}

					if (argc == 4 && "-f" != argv[3])
					{
						std::string str(argv[3]);
						size_t pos = 0;
						while ((pos = str.find("\\n", pos)) != std::string::npos)
						{
							str.replace(pos, 2, "\n");
							pos += 2;
						};
						std::istringstream tmp(str);
						std::cout << GetLastXLines(tmp, atoi(optarg));
						break;
					}
					std::fstream file(argv[optind + 1], std::fstream::in);
					if (!file.is_open())
					{
						std::cout << "Chyba suboru" << std::endl;
						std::cout << "Press any key to continue" << std::endl;
						getchar();
						return -1;
					}
					std::cout << GetLastXLines(file, atoi(optarg));
					file.close();
					std::cout << std::endl;
					optind = optind + 2;
					break;
				}
				case '?':
				{
					std::wcout << "Chybny parameter '" << argv[optind - 1] << "'" << std::endl;
					DisplayUsage(argv[0]);
					std::cout << "Press any key to continue" << std::endl;
					getchar();
					return -1;
				}
				default:
				{
					std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
					DisplayUsage(argv[0]);
					std::cout << "Press any key to continue" << std::endl;
					getchar();
					return -1;
				}
			}
		}
	}
	std::cout << "Press any key to continue" << std::endl;
	getchar();
	return 0;
}

