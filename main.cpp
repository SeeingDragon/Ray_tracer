#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "Sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

hittable_list random_scene() {
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -5; a < 5; a++) {
		for (int b = -5; b < 5; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


color ray_color(const ray& r, const hittable& world,int depth)
{
	hit_record rec;

	//增加深度限制，防止无限递归,并且在最大深度不返回光贡献
	if (depth <= 0) {
		return color(0, 0, 0);
	}

	if (world.hit(r, 0.001, infinity, rec))
	{
		/*
		//Lambertian散射
		//利用两圆相切两圆心和切点在同一直线的性质，将获得的随机数进行坐标系变换，即点p加上p的法线可获得p指向散射模型的圆心的向量，如此加上随机点坐标，即可完成转换，注意从散射模型圆心指向该随机点的向量模长不得大于等于1；
		point3 target = rec.p + rec.normal + random_in_unit_sphere();
		//更直观的反射
		//point3 target = rec.p + random_in_heimsphere(rec.normal);
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth-1);
		*/
		
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			//乘法计算贡献值
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
		

	}
	//获取单位向量
	//r=origin+t*direction
	//direction方向y轴的取值范围是（-1，1）
	vec3 unit_direction = unit_vector(r.direction());
	//std::cout << unit_direction << std::endl;
	//要让t从0到1变化，unit_direction大概范围是-0.7-0.7
	auto t = 0.5 * (unit_direction.y()+ 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}



int main()
{
	//image
	//aspect_ratio=width/height
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width/aspect_ratio);
	const int samples_per_pixel = 500; 
	const int max_depth = 50;


	//World
	auto world=random_scene();

	//auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	////auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
	////auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8),0.3);
	////auto material_center = make_shared<dielectric>(1.5);
	//auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	//auto material_left = make_shared<dielectric>(1.5);
	//auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2),0.0);

	//world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0,material_ground));
	//world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0),0.5,material_center));
	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	//world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
	//world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
	


	//Camera
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0,0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus =10;
	auto aperture = 0.1;

	camera cam(lookfrom,lookat,vup,20,aspect_ratio,aperture,dist_to_focus);

	//Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	//从上到下，从左到右进行输出
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i <image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				//把u，v限制到（0，1）
				auto u = (i + random_double()) / ((double)image_width - 1);
				auto v = (j + random_double()) / ((double)image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world,max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	
	
	std::cerr << "\nDone.\n";
}

