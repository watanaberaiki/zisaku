#pragma once
#include <DirectXMath.h>

//��
struct Sphere
{
	//���S���W
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//���a
	float radius=1.0f;
};

//����
struct Plane 
{
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//���_����̋���
	float distance = 0.0f;
};