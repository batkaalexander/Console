#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Library/Library.h"

#include <vector>

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_XGetOpt_fail)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-a", "-c", "-e", "param E", "--fail" };
			char * opts = "ab:cde:";

			Assert::IsTrue( getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual( argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'a', L"option -a");
			Assert::IsTrue(optarg == nullptr, L"option param -a");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'c', L"option -c");
			Assert::IsTrue(optarg == nullptr, L"option param -c");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[6], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == '?', L"option --fail");
			Assert::IsTrue( optind == 8, L"--fail index");
		}

		TEST_METHOD(Test_XGetOpt_param)
		{
			optarg = nullptr;
			optind = 0;

			std::vector<char *> argv = { "appName", "-db", "param B", "-e", "param E", "param 1", "param 2" };
			char * opts = "ab:cde:";

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'd', L"option -d");
			Assert::IsTrue(optarg == nullptr, L"option param -d");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'b', L"option -b");
			Assert::AreEqual(argv[2], optarg, L"option param -b");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == 'e', L"option -e");
			Assert::AreEqual(argv[4], optarg, L"option param -e");

			Assert::IsTrue(getopt((int)argv.size(), &argv[0], opts) == EOF, L"last option");
			Assert::IsTrue(optind == 5, L"first param index");
		}
	};
}