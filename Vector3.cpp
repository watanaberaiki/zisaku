#include "Vector3.h"
#include <cmath>

//��x�N�g���ɏ���������
Vector3::Vector3()
	:x(0), y(0), z(0)
{
}

//����2�̃R���X�g���N�^
Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

//�x�N�g���̒��������߂�
float Vector3::length() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

//�x�N�g���𐳋K��(�P�ʃx�N�g��)�ɂ���
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

//���ς����߂�
float Vector3::dot(const Vector3& v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

//�O�ς����߂�
Vector3 Vector3::cross(const Vector3& v) const
{
	return { v.y * z - y * v.z,
			 v.x * z - x * v.z,
			 x * v.y - y * v.x };
}

//�P�����Z�q�{���g����悤�ɂ���
Vector3 Vector3::operator+() const
{
	return *this;
}

//�P�����Z�q�|���g����悤�ɂ���
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

//+=���g����悤�ɂ���
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//-=���g����悤�ɂ���
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//�x�N�g�������{�ɂ���
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

//�x�N�g�����P/���{�ɂ���
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

Vector3& Vector3::operator=(const XMFLOAT3& v) 
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

//Vector2�N���X�ɑ����Ȃ��֐��Q
//�񍀉��Z�q
const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

//���`�⊮
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}
