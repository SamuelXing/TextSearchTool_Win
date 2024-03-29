///////////////////////////////////////////////////////////////////////
// SimpleCompObj.h : Declaration of the TextSearchComp               //
//                                                                   //
// Zihao Xing, CSE775 - Distributed Objects, Spring 2018             //
///////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
*  TextSearchComp is an in-process COM component that provides the interfaces
* that talk to a "Search" instance.
*
* Public interfaces:
* =================
* STDMETHOD(passFileMgrIF)(IUnknown* pFileMgr);
* - pass a FileMgrComp reference to current instance
* STDMETHOD(setText)(BSTR searchText);
* - set searching text
* STDMETHOD(getResult)(SAFEARRAY ** pResult);
* - get searhcing results
*
* Required Files:
* ====================
* ../Search/Search.h
*
* Maintenance History:
* ====================
* ver 1.0 : Apr 3, 2018
* - first release
*/

#pragma once
#include "resource.h"       // main symbols
#include "TextSearchComp_i.h"
#include "../Search/Search.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSimpleCompObj

class ATL_NO_VTABLE CSimpleCompObj :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleCompObj, &CLSID_SimpleCompObj>,
	public IDispatchImpl<ISimpleCompObj, &IID_ISimpleCompObj, &LIBID_TextSearchCompLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSimpleCompObj()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CSimpleCompObj)
	COM_INTERFACE_ENTRY(ISimpleCompObj)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		pSearch_ = new Search();
		return S_OK;
	}

	void FinalRelease()
	{
		if (!pSearch_)
			delete pSearch_;
	}
private:
	inline std::string BSTR2STDSTR(const BSTR bstring, int cp = CP_UTF8) {
		std::wstring ws(bstring);
		std::string stdstr(ws.begin(), ws.end());
		return stdstr;
	}
	IUnknown * pFileMgr_;
	ISearch* pSearch_;
	bool done_ = false;

public:
	STDMETHOD(passFileMgrIF)(IUnknown* pFileMgr);
	STDMETHOD(setText)(BSTR searchText);
	STDMETHOD(getResult)(SAFEARRAY ** pResult);
};

OBJECT_ENTRY_AUTO(__uuidof(SimpleCompObj), CSimpleCompObj)
