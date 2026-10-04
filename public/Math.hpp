#ifndef MATH_HPP
#define MATH_HPP
#include <math.h>

inline int max(int a,int b) {return a>b?a:b;}
inline int numDigits(int a){return a>0?(int)log10((double)a)+1 : 1;}
#endif