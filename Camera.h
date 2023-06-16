#pragma once
#include <DirectXTex.h>
#include"Input.h"

using namespace DirectX;

class Camera
{

public:
	void Initialize(Input* input);
	void Update();

	/*static void SetInput(Input* input) { Camera::input = input; }*/

public:
	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetEye(XMFLOAT3 eye) { this->eye = eye; };

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetTarget(XMFLOAT3 target) { this->target = target; };

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const XMFLOAT3& GetUp() { return up; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetUp(XMFLOAT3 up) { this->up = up; };

	const XMMATRIX& GetmatView() { return matView; }
	XMMATRIX GetmatViewProjection() { return matView * matProjection; }

private:
	XMMATRIX matView;
	XMFLOAT3 eye = {};		//���_���W
	XMFLOAT3 target = {};	//�����_���W
	XMFLOAT3 up = {};		//������x�N�g��
	XMMATRIX matProjection;

	//�L�[�{�[�h
	Input* input;
};

