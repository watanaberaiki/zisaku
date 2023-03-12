#include "Camera.h"
#include"WinApp.h"
void Camera::Initialize(Input*input) {
	eye = { 0, 5, -100 };
	target={0, 0, 0};
	up = { 0, 1, 0 };
	this->input = input;
	//�������e�ϊ��s��̌v�Z
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 1000.0f
	);
	//�r���[�ϊ��s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::Update() {
	if (input->PushKey(DIK_LEFT)) {
		eye.x -= 0.1;
	}
	else if (input->PushKey(DIK_RIGHT)) {
		eye.x += 0.1;
	}
	//�r���[�ϊ��s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}