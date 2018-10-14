#include "aabb.h"

float __attribute__((aligned(16))) SIMDx86_float_one_no_w[4] = { 0.5, 0.5, 0.5, 0 };

int SIMDx86AABB_IntersectsAABB(const SIMDx86AABB* pBox1, const SIMDx86AABB* pBox2)
{
	int dummy;
	#if defined(USE_SSE)
	asm(
	"movaps   (%1), %%xmm0\n"	/* xmm0 = pBox1->Min */
	"movaps 16(%1), %%xmm1\n"	/* xmm1 = pBox1->Max */
	"movaps   (%2), %%xmm2\n"	/* xmm2 = pBox2->Min */
	"movaps 16(%2), %%xmm3\n"	/* xmm3 = pBox2->Max */
	/* cmpps $1, xmm, xmm  = cmpleps xmm, xmm */
	
	/* if min > max, return 0*/
	"cmpnleps %%xmm1, %%xmm2\n"	/* xmm1 = pBox1->Max < pBox2->Min? 0xFFFFFFFF : 0x00000000 */
	"cmpnleps %%xmm3, %%xmm0\n"	/* xmm0 = pBox2->Max < pBox1->Min? 0xFFFFFFFF : 0x00000000 */
        "orps %%xmm2, %%xmm0\n"		/* xmm0 |= xmm1, 基本的には、cmpltps命令  */
	
	
	"andps _SIMDx86_float_one_no_w, %%xmm0\n" /* if(Max < Min) 1.0f else 0.0f */



	#if USE_SSE >= 3
		"haddps %%xmm0, %%xmm0\n"
		"haddps %%xmm0, %%xmm0\n"

		"movd %%xmm0, %%eax\n"
	#else
		"movhlps %%xmm0, %%xmm2\n"		/* xmm2 = ?    | ?    | ?    | res1 */
		"addss %%xmm0, %%xmm2\n"		/* xmm2 = ?    | ?    | res2 | res1 + res3 */
		"shufps $0x55, %%xmm0, %%xmm0\n"/* xmm0 = res2 | res2 | res2 | res2 */
		"addss %%xmm0, %%xmm2\n"		/* xmm2 = ?    | ?    | ?    | res1 + res2 + res3 */

		#if USE_SSE >= 2
		"movd %%xmm2, %%eax\n"
		#else
		"movss %%xmm2, -4(%%esp)\n"
		"movl -4(%%esp), %%eax\n"
		#endif

		/*
			Total gross hacks
			-----------------
			1)3f000000 (0.5f)
			2)3f800000 (1.0f)
			3)3fc00000 (1.5f),
			  |
			  v
			  3f in highest byte is the same

			AND eaxのとき 3f000000 or 00000000
			算術シフトしたあと、xorビット反転

		*/
		"shll $30, %%eax\n"
		"xorl $1, %%eax\n"

	#endif
	: "=a" (dummy)
	: "r" (pBox1), "r" (pBox2)
	);
	return dummy;
	#else

	if(pBox1->Min.x > pBox2->Max.x)
		return 0;
	if(pBox1->Min.y > pBox2->Max.y)
		return 0;
	if(pBox1->Min.z > pBox2->Max.z)
		return 0;

	if(pBox2->Min.x > pBox1->Max.x)
		return 0;
	if(pBox2->Min.y > pBox1->Max.y)
		return 0;
	if(pBox2->Min.z > pBox1->Max.z)
		return 0;

	return 1;
	#endif

}