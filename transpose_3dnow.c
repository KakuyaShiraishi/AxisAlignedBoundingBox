void SIMDx86Matrix_Transpose(SIMDx86Matrix* pDest, SIMDx86Matrix* pToBeTransposed)
{
   __asm
   {
      mov       eax,[pDest]
      mov       edx,[pToBeTransposed]
      movq      mm0,[eax]
      movq      mm1,[eax+16]
      movq     mm4,mm0
      movq     mm2,[eax+8]
      punpckldq mm0,mm1
      punpckhdq mm4,mm1
      movq   [edx],mm0
      movq     mm3,[eax+24]
      movq [edx+16],mm4
      movq     mm4,mm2
      movq     mm0,[eax+32]
      punpckldq mm2,mm3
      punpckhdq mm4,mm3
      movq [edx+32],mm2
      movq     mm1,[eax+48]
      movq [edx+48],mm4
      movq     mm4,mm0
      movq     mm2,[eax+40]
      punpckldq mm0,mm1
      punpckhdq mm4,mm1
      movq  [edx+8],mm0
      movq     mm3,[eax+56]
      movq [edx+24],mm4
      movq     mm4,mm2
      punpckldq mm2,mm3
      punpckhdq mm4,mm3
      movq [edx+40],mm2
      movq [edx+56],mm4
   }
}