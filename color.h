#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include <iostream>

//write the translated [0,255] value of each color component.
//std::ostream& out ���������
void write_color(std::ostream& out, color pixel_color, int samples_per_pixel){
	
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	//ȡ���ۼ���samples_per_pixel����������������1/sample_per_pixel,٤�����Ϊ gamma=2.0.
	auto scale = 1.0 / samples_per_pixel;
	r =sqrt(scale*r);
	g = sqrt(scale*g);
	b = sqrt(scale*b);

	//static_cast��(255.999 * r)ת��Ϊint����,���ҷŴ�0-256��Χ��
	out << static_cast<int>(256 * clamp(r,0.0,0.999)) << ' '
		<< static_cast<int>(256 * clamp(g,0.0,0.999)) << ' '
		<< static_cast<int>(256 * clamp(b,0.0,0.999)) << '\n';
}


#endif // !COLOR_H

