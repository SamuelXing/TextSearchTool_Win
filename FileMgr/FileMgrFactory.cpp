//////////////////////////////////////////////////////////////
// FileMgrFactory.cpp - Factory Method                      //
// ver 1.0                                                  //
// Zihao Xing, CSE775 - Distributed Object, Spring 2018     //
///////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FileMgrFactory.h"

// ----<factory method>------
IFileMgr* FileMgrFactory::CreateFileMgr() 
{
	return new FileMgr();
}