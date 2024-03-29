///////////////////////////////////////////////////////////////////////
//  CompFileMgr.h : Declaration of the CCompFileMgr                  //
//  ver 1.0                                                          //
//  Author:        Zihao Xing, CSE775, Distributed Object            //
///////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* FileMgrComp is an in-process COM component that provides the interfaces
* that talk to a FileMgr instance.
*
* Public interfaces:
* =================
*	STDMETHOD(setPath)(BSTR path);
*	- set a searching path
*	STDMETHOD(addPattern)(BSTR pattern);
*	- add a pattern to be found
*	STDMETHOD(getFileMgrInstance)();
*	- create a FileMgr instance
*	STDMETHOD(traverse)();
*	- start searching
*	STDMETHOD(getResult)(BSTR* pResult);
*	- retrieve a BSTR result from the BlockingQueue
*	STDMETHOD(get)(SAFEARRAY ** pResult);
*	- retrieve a result with success code from the BlockingQueue
*
* Required Files:
* ====================
* ../FileMgr/FileMgrFactory.h
*
* Notes:
* ====================
* Success Code examples
* - {"filename", "FILE"}
* _ {"", EOF}
*
* Maintenance History:
* ====================
* ver 1.0 : Apr 3, 2018
* - first release
*/

#pragma once
#include "resource.h"       // main symbols
#include "../FileMgr/FileMgrFactory.h"
#include "FileMgrComp_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CCompFileMgr

class ATL_NO_VTABLE CCompFileMgr :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompFileMgr, &CLSID_CompFileMgr>,
	public IDispatchImpl<ICompFileMgr, &IID_ICompFileMgr, &LIBID_FileMgrCompLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCompFileMgr()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CCompFileMgr)
	COM_INTERFACE_ENTRY(ICompFileMgr)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:
	inline std::string BSTR2STDSTR(const BSTR bstring, int cp = CP_UTF8) {
		std::wstring ws(bstring);
		std::string stdstr(ws.begin(), ws.end());
		return stdstr;
	}

	IFileMgr * fileMgr;

public:
	STDMETHOD(setPath)(BSTR path);
	STDMETHOD(addPattern)(BSTR pattern);
	STDMETHOD(getFileMgrInstance)();
	STDMETHOD(traverse)();
	STDMETHOD(getResult)(BSTR* pResult);
	STDMETHOD(get)(SAFEARRAY ** pResult);
};

OBJECT_ENTRY_AUTO(__uuidof(CompFileMgr), CCompFileMgr)
