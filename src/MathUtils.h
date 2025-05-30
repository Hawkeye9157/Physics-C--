#pragma once
#include <raylib.h>
#include <cstdlib>
#include <algorithm>

inline float randf() {return rand() / (float)RAND_MAX;}
inline float randf(float max) {return randf() * max;}
inline float randf(float min, float max) { if (min > max) std::swap(min, max); return min + (randf() * (max - min)); }
inline Vector2 RandomOnUnitCircle() { float theta = randf(0, 2 * PI); return {cosf(theta),sinf(theta)}; }