#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

//生成随机数
#include <cstdlib>


//Using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;



//Constans
//std::numeric_limits<double>::infinity()返回无穷大
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//Utility Function
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}


//Random
//rand()最大是32767最小是0,再除以32768就是一个0到1之间的小数(不能等于1)
inline double random_double() {

	return rand() / (RAND_MAX + 1.0);
}


inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
	if (x < min)return min;
	if (x > max) return max;
	return x;
}

//Common Headers

#include "ray.h"
#include "vec3.h"


#endif // !RTWEEKEND_H

