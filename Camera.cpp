#include "Camera.h"
#include"WinApp.h"
void Camera::Initialize() {
	eye = { 0, 5, -100 };
	target={0, 0, 0};
	up = { 0, 1, 0 };
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
	//�r���[�ϊ��s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}