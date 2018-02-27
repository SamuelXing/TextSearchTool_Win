#pragma once
#ifndef FILEMGRFACTORY_H
#define FILEMGRFACTORY_H
#include "FileMgr.h"

class FileMgrFactory
{
public:
	static IFileMgr* CreateFileMgr();
};
#endif // !FILEMGRFACTORY_H

