#pragma once
#include"WinApp.h"
#include <Windows.h>
#include<cassert>
#define DIRECTINPUT_VERSION     0x0800   // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <wrl.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//����
class Input
{
public:
	//namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�

	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
	//�L�[�`�F�b�N
	bool PushKey(BYTE keyNumber);
	//�L�[�g���K�[�`�F�b�N
	bool TriggerKey(BYTE keyNumber);
	//�L�[�����[�X�`�F�b�N
	bool released(BYTE keyNumber);
private://�����o�ϐ�
	//�L�[
	BYTE key[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
	ComPtr<IDirectInputDevice8> keyboard=nullptr;
	//WindowsAPI
	WinApp* winApp = nullptr;
};

