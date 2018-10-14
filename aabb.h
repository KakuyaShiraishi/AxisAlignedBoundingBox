#ifndef _SIMDX86_AABB_H
#define _SIMDX86_AABB_H

#include <SIMDx86/vector.h>

typedef struct SIMDx86AABB
{
	SIMDx86Vector Min, Max;
} SIMDx86AABB;

#endif