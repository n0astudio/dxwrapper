#pragma once

#define VISIT_WRAPPERS(visit) \
	visit(bcrypt, BCRYPT) \
	visit(cryptsp, CRYTPSP) \
	visit(d3d8, D3D8) \
	visit(d3d9, D3D9) \
	visit(ddraw, DDRAW) \
	visit(dinput, DINPUT) \
	visit(dplayx, DPLAYX) \
	visit(dsound, DSOUND) \
	visit(dxgi, DXGI) \
	visit(winmm, WINMM) \
	visit(winspool, WINSPOOL) \
	visit(dciman32, DCIMAN32)

#define ADD_FARPROC_MEMBER(memberName) FARPROC memberName = jmpaddr;

#define ADD_NAMESPACE_CLASS(className, Z) className::className ## _dll className::module;

#define CREATE_ALL_PROC_STUB(module, MACRO) \
	namespace my ## module \
	{ \
		using namespace module; \
		VISIT_ ## MACRO ## _PROCS(CREATE_PROC_STUB); \
	}

#define CREATE_PROC_STUB(procName) \
	extern "C" __declspec(naked) void __stdcall Fake ## procName() \
	{ \
		__asm jmp module.procName \
	}

#define	LOAD_ORIGINAL_PROC(procName) \
	procName = Wrapper::GetProcAddress(dll, #procName, jmpaddr);

#define	LOAD_WRAPPER(className, Z) \
		className::module.Load();

#define	UNHOOK_WRAPPER(className, Z) \
		className::module.Unhook();

#define jmpaddr Wrapper::_jmpaddr

namespace Wrapper
{
	extern const FARPROC _jmpaddr;
	extern FARPROC Direct3DCreate9_Proc;
	extern FARPROC Direct3DCreate9_Logging;

	HMODULE LoadDll(DWORD);
	void DllAttach();
	void DllDetach();
	FARPROC GetProcAddress(HMODULE, LPCSTR, FARPROC);
};
