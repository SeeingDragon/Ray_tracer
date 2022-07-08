#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

//write the translated [0,255] value of each color component.
//std::ostream& out 输出流引用
void write_color(std::ostream& out, color pixel_color, int samples_per_pixel){
	
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	//取样累加了samples_per_pixel次数，所以最后乘以1/sample_per_pixel,伽马矫正为 gamma=2.0.
	auto scale = 1.0 / samples_per_pixel;
	r =sqrt(scale*r);
	g = sqrt(scale*g);
	b = sqrt(scale*b);

	//static_cast将(255.999 * r)转换为int类型,并且放大到0-256范围内
	out << static_cast<int>(256 * clamp(r,0.0,0.999)) << ' '
		<< static_cast<int>(256 * clamp(g,0.0,0.999)) << ' '
		<< static_cast<int>(256 * clamp(b,0.0,0.999)) << '\n';
}


#endif // !COLOR_H

