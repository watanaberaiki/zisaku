#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <array>
#include<string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

//�X�v���C�g���ʕ�
class SpriteCommon
{

public:
	//������
	void Initialize(DirectXCommon* dxCommon);

	void PreDraw();

	void PostDraw();
	void LoadTexture(uint32_t index, const std::string& fileName);

	void SetTextureCommands(uint32_t index);

	DirectXCommon* GetDirectXCommon() { return dxcommon_; }

	ID3D12Resource* GetTextureBuffer(uint32_t index) { return texBuff[index].Get(); }


private:
	//SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;

	static std::string kDefaultTextureDirectoryPath;

private:
	DirectXCommon* dxcommon_;

	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;

	// ���[�g�V�O�l�`���́A�e�N�X�`����萔�o�b�t�@�ȂǃV�F�[�_�[�ɓn�����\�[�X�̏����܂Ƃ߂��I�u�W�F�N�g�B
	ComPtr<ID3D12RootSignature> rootSignature;


	//�e�N�X�`���o�b�t�@�̐���
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount> texBuff;

	ComPtr<ID3D12DescriptorHeap> srvHeap;
};