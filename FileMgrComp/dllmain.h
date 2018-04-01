// dllmain.h : Declaration of module class.

class CFileMgrCompModule : public ATL::CAtlDllModuleT< CFileMgrCompModule >
{
public :
	DECLARE_LIBID(LIBID_FileMgrCompLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEMGRCOMP, "{aaba6a33-d1e7-4a4c-8aeb-7a23660f7776}")
};

extern class CFileMgrCompModule _AtlModule;
