#include "stdafx.h"
#include "FileMgrFactory.h"

IFileMgr* FileMgrFactory::CreateFileMgr() 
{
	return new FileMgr();
}