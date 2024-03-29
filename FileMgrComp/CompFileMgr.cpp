///////////////////////////////////////////////////////////////////////
// CompFileMgr.cpp : Implementation of CCompFileMgr                  //
//  ver 1.0                                                          //
//  Author:        Zihao Xing, CSE775, Distributed Object            //
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CompFileMgr.h"
#include <atlsafe.h>

// ------<set a searching path>------
STDMETHODIMP CCompFileMgr::setPath(BSTR path)
{
	if (fileMgr == nullptr)
		return E_FAIL;
	std::string pathStr = BSTR2STDSTR(path);
	fileMgr->setPath(pathStr);
	return S_OK;
}

// --------<add a pattern to be found>-------
STDMETHODIMP CCompFileMgr::addPattern(BSTR pattern)
{
	if (fileMgr == nullptr)
		return E_FAIL;
	std::string patternStr = BSTR2STDSTR(pattern);
	fileMgr->addPattern(patternStr);
	return S_OK;
}

//--------<create a FileMgr instance>-------
STDMETHODIMP CCompFileMgr::getFileMgrInstance()
{
	fileMgr = FileMgrFactory::CreateFileMgr();
	return S_OK;
}

// -------<start searching>----------
STDMETHODIMP CCompFileMgr::traverse()
{
	if (fileMgr == nullptr)
		return E_FAIL;
	fileMgr->traverseAndEnQ();
	return S_OK;
}

// -------<retrieve a BSTR result from the BlockingQueue>------
STDMETHODIMP CCompFileMgr::getResult(BSTR* pResult)
{
	std::string rst = fileMgr->get();
	CComBSTR BSTR_RST(rst.c_str());
	*pResult = BSTR_RST.Detach();
	return S_OK;
}

// ------<retrieve a result with success code from the BlockingQueue>-----
STDMETHODIMP CCompFileMgr::get(SAFEARRAY ** pResult)
{
	std::array<std::string, 2> rst = fileMgr->get(0);
	CComSafeArray<BSTR> _record;
	_record.Add(CComBSTR(rst[0].c_str()));
	_record.Add(CComBSTR(rst[1].c_str()));
	*pResult = _record.Detach();
	return S_OK;
}
