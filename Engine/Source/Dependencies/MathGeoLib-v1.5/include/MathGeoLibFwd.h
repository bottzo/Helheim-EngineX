/* Copyright Jukka Jyl�nki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file MathFwd.h
	@author Jukka Jyl�nki
	@brief */
#pragma once

#include "MathBuildConfig.h"
#include "Math/MathNamespace.h"

// The CONST_WIN32 is a #define which resolves to 'const' on Windows, and null on other
// platforms. This #define is used on Windows to detect accidental programming errors
// occurring from an expression "const float3 vec; vec[1] = 5;". Trying to return
// const float from operator[] on GCC gives a warning "type qualifiers ignored on function return type",
// so hence this is only enabled on Visual Studio.
#ifdef _MSC_VER
#define CONST_WIN32 const
#else
#define CONST_WIN32
#endif

#ifdef _MSC_VER
#define NAMELESS_UNION_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable:4201))

#define NAMELESS_UNION_END \
	__pragma(warning(pop))

#else

#define NAMELESS_UNION_BEGIN union {
#define NAMELESS_UNION_END };

#endif

#if !defined(MATH_ENABLE_STL_SUPPORT) && !defined(assert)
#include <stdio.h>
#define assert(x) do { if (!(x)) { printf("Error: assert(%s) failed!\n", #x); } } while(0)
#endif

MATH_BEGIN_NAMESPACE

class float2;
class float3;
class float4;
class float2x2;
class float2x3;
class float3x3;
class float3x4;
class float4x4;
class Quat;

class TranslateOp;
class ScaleOp;

class AABB;
class Capsule;
class Circle;
#ifdef Complex
#undef Complex
#endif
class Complex;
class Cone;
class Cylinder;
class Ellipsoid;
class Frustum;
struct HitInfo;
class Line;
class LineSegment;
class OBB;
class Plane;
class Polygon;
class Polyhedron;
class Polynomial;
class Quat;
class Ray;
class Sphere;
class TranslateOp;
class Torus;
class ScaleOp;
class Triangle;
class LCG;

MATH_END_NAMESPACE

#ifdef MATH_GRAPHICSENGINE_INTEROP
class VertexBuffer;
#endif

#ifdef MATH_ENABLE_STL_SUPPORT
#include <iosfwd>
#endif

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif