#include "stdafx.h"
#include "Search.h"

#ifdef TEST_SEARCHCOMP
int main()
{
	std::cout << "  TEST SEARCH COMPONENT\n";
	std::cout << "=========================\n";
	std::vector<std::string> filePatterns;
	filePatterns.push_back("*.h");
	filePatterns.push_back("*.cpp");

	std::string regStr = "(.*?)FileSys(.*?)";
	IFileMgr* IfileMgr = FileMgrFactory::CreateFileMgr();
	ISearch* searchInstance = new Search();
	searchInstance->setFileMgr(IfileMgr);
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
