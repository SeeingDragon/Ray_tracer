#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

//write the translated [0,255] value of each color component.
//std::ostream& out 输出流引用
void write_color(std::ostream& out, color pixel_color)
{
	//static_cast将(255.999 * r)转换为int类型,并且放大到0-256范围内
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}


#endif // !COLOR_H

