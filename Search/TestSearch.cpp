#include "stdafx.h"
#include "Search.h"

#define TEST_SEARCHCOMP
#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.h");
	filePatterns.push_back("*.cpp");

	std::string regStr = "(.*?)FileSys(.*?)";

	ISearch* searchInstance = new Search();
	searchInstance->put(".", filePatterns, regStr);


	std::cout << "\n\n Results: \n";
	std::cout << "=========================\n";
	std::string msg;
	do
	{
		msg = searchInstance->get();
		std::cout << msg << std::endl;
	} while (msg != "END");

	return 0;
}
#endif // TEST_SEARCHCOMP
