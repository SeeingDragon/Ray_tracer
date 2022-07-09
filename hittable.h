#ifndef HITTABLE_H
#define HITTABLE_H


#include "rtweekend.h"


class material;

struct hit_record {
	point3 p;//����
	vec3 normal;//����
	shared_ptr<material> mat_ptr;//����ָ��
	double t;
	bool front_face;//�÷��߷���ʼ��������෴
	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		//�ù��շ���ͷ��߷���ʼ�ձ����෴
		//������շ�������ⷨ�߷����˽��С��0����˵�������෴
		front_face = dot(r.direction(), outward_normal)<0;
		//���front_face��Ϊ0˵�����շ���ͷ��߷����෴��������÷����ı䡣
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
	public :
		//��ײ����
		//����0�����Ǵ��麯��
		virtual bool hit(const ray& r, double t_min,double t_max, hit_record& rec) const = 0;
};





#endif // !HITTABLE_H

