#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

//write the translated [0,255] value of each color component.
//std::ostream& out ���������
void write_color(std::ostream& out, color pixel_color)
{
	//static_cast��(255.999 * r)ת��Ϊint����,���ҷŴ�0-256��Χ��
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}


#endif // !COLOR_H

