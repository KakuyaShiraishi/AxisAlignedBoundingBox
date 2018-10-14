
#include <windows.h>

int SIMDx86Code_MarkReadWriteExec(void* pFunctionAddress, unsigned int NumBytes)
{
	DWORD oldprot;
	return (VirtualProtect(pFunctionAddress, NumBytes, PAGE_EXECUTE_READWRITE, &oldprot) != 0);
}

int SIMDx86Code_MakeReadExec(void* pFunctionAddress, unsigned int Bytes)
{
	DWORD oldprot;
return (VirtualProtect(pFunctionAddress, NumBytes, PAGE_EXECUTE_READ, &oldprot) != 0);
}

