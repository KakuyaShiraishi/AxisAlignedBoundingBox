

HalfButNoW:
dd 0.5		; x = 0.5
dd 0.5		; y = 0.5
dd 0.5		; z = 0.5
dd 0.0		; w = 0.0


GLOBAL _SIMDx86AABB_IntersectsAABB

lea eax, [esp+4]
lea edx, [esp+8]


movups xmm0, [eax]				; xmm0 = pBox1->min
movups xmm1, [eax+16]			; xmm1 = pBox1->Max
movups xmm2, [edx]				; xmm2 = pBox2->Min
movups xmm3, [edx+16]			; xmm3 = pBox2->Max

; Generate bit masks of all ones if Max < Min
cmpnleps xmm2, xmm1				; xmm1 = pBox1->Max < pBox2->Min? 0xFFFFFFFF : 0x00000000
cmpnleps xmm3, xmm0				; xmm2 = pBox2->Max < pBox1->Min? 0xFFFFFFFF : 0x00000000
orps xmm0, xmm2

andps xmm0, [HalfButNoW]		; xmm0 = Max < Min ? 0.5f : 0.0f


%if USE_SSE >= 3

haddps xmm0, xmm0
haddps xmm0, xmm0
movd eax, xmm0

%else

movhlps xmm2, xmm0
addss xmm2, xmm0
shufps xmm0, xmm0, 0x55
addss xmm2, xmm0

%if USE_SSE >= 2
	movd eax, xmm2
%else ; use movss/mov combo with store-to-load forwarding =\
	movss [esp-4], xmm2
	mov eax, [esp-4]
%endif

shl eax, 30
xor eax, 1
ret
