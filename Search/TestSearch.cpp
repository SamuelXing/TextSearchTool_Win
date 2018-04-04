#include "stdafx.h"
#include "Search.h"

// ------<test stub>-------
#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> result;
	std::string regStr = "(.*?)FileSys(.*?)";
	ISearch* searchInstance = new Search();
	result = searchInstance->scanner("Specify a filename", regStr);
	for (int i = 0; i < result.size(); i++) 
	{
		std::cout << result << std::endl;
	}
	return 0;
}
#endif // TEST_SEARCHCOMP
