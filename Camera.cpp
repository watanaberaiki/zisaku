#include "Camera.h"
#include"WinApp.h"
void Camera::Initialize(Input* input) {
	//�������e�ϊ��s��̌v�Z
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 1000.0f
	);
	this->input = input;
}

void Camera::Update() {
	if (input->PushKey(DIK_LEFT)) {
		eye.x -= 1.0;
	}
	else if (input->PushKey(DIK_RIGHT)) {
		eye.x += 1.0;
	}
	//�r���[�ϊ��s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}