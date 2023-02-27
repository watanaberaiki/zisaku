#pragma once
#include<Windows.h>

class WinApp
{
public://�萔
	//�E�B���h�E�T�C�Y
	static const int window_width = 1280;//����
	static const int window_height = 720;//�c��

public://�ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://�����o�֐�
	//������
	void Initialize();
	//�X�V
	void Update();
	//���b�Z�[�W�̏���
	bool ProcessMesseage();
	//�I��
	void Finalize();

	//�Q�b�^�[
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }

private://�����o�ϐ�
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;
	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
};


