// dllmain.h : Declaration of module class.

class CTextSearchCompModule : public ATL::CAtlDllModuleT< CTextSearchCompModule >
{
public :
	DECLARE_LIBID(LIBID_TextSearchCompLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEXTSEARCHCOMP, "{9bfdb6a8-27ec-4521-aab2-7150d03e6dc0}")
};

extern class CTextSearchCompModule _AtlModule;
