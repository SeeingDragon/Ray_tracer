#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"



color ray_color(const ray& r)
{
	//获取单位向量
	//r=origin+t*direction
	//direction方向y轴的取值范围是（-1，1）
	vec3 unit_direction = unit_vector(r.direction());
	std::cout << unit_direction << std::endl;
	//要让t从0到1变化，unit_direction大概范围是-0.7-0.7
	auto t = 0.5 * (unit_direction.y()+ 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main()
{
	//image
	//aspect_ratio=width/height
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width/aspect_ratio);

	//Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;//camera到image的z轴距离

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	//左下角,(0,0,0)定义正中心，变为向量，从(0,0,0)指向左下角
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	//Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	//从上到下，从左到右进行输出
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i <image_width; ++i)
		{
			//把u，v限制到（0，1）
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);

			//定义光线
			//lower_left_corner是从原点指向左下角的向量
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			//定义在vec3.h的颜色向量
			color pixel_color=ray_color(r);
			//write_color(std::cout, pixel_color);
		}
	}
	
	std::cerr << "\nDone.\n";
}

