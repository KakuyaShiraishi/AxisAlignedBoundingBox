#include <sys/mman.h>
#include <unistd.h>

unsigned long PageOfAddress(unsigned long addr, unsigned long PageSize)
{
    return addr & (PageSize-1);
}

unsigned long PageOffsetOfAddress(unsigned long addr, unsigned long PageSize)
{
    return addr & (~(PageSize-1));
}

int SIMDx86Code_MarkReadWriteExec(void* pFunctionAddress, unsigned int NumBytes)
{
    unsigned long PageSize;
    int ActualNumberOfBytes;
    
    PageSize = (unsigned long)sysconf(_SC_PAGE_SIZE);
    ActualNumberOfBytes	= ((unsigned long)NumBytes) + PageOffsetOfAddress((unsigned long)pFunctionAddress, PageSize);
    
    return mprotect((void*)PageOfAddress((unsigned long)pFunctionAddress, PageSize), (size_t) ActualNumberOfBytes, PROT_WRITE | PROT_READ | PROT_EXEC) == 0;
}

int SIMDx86Code_MakeReadExec(void* pFunctionAddress, unsigned int Bytes)
{
    unsigned long PageSize;
    int ActualNumberOfBytes;
    
    
    PageSize = (unsigned long)sysconf(_SC_PAGE_SIZE);
    ActualNumberOfBytes	= ((unsigned long)NumBytes) + PageOffsetOfAddress((unsigned long)pFunctionAddress, PageSize);
    
    return mprotect(PageOfAddress((unsigned long)pFunctionAddress, PageSize), (size_t) ActualNumberOfBytes, PROT_READ | PROT_EXEC) == 0;
}

