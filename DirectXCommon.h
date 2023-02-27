#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include"WinApp.h"
#include <vector>
#include<chrono>
class DirectXCommon
{

public:

	//������
	void Initialize(WinApp* winApp);

	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//�f�o�C�X�擾
	ID3D12Device* GetDevice() const { return device.Get(); }

	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandlist()const { return commandList.Get(); }

private://�֐�
	//�f�o�C�X�̏�����
	void InitializeDevice();
	//�R�}���h�֘A�̏�����
	void InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	void InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();
	//�[�x�o�b�t�@
	void InitializeDepthBuffer();
	//�t�F���X
	void InitializeFence();
	//FPS�Œ菉����
	void InitializeFixFPS();
	//FPS�Œ�X�V
	void UpdateFixFPS();

private://�ϐ�
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	D3D12_RESOURCE_BARRIER barrierDesc{};

	UINT64 fenceVal = 0;

	//�o�b�N�o�b�t�@
	std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	//WindowsAPI
	WinApp* winApp = nullptr;

	//�L�^����(FPS�p)
	std::chrono::steady_clock::time_point reference_;
};

