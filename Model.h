#pragma once
#include <d3dx12.h>
#include <DirectXMath.h>
#include <d3d12.h>

using namespace DirectX;
using namespace Microsoft::WRL;

class Model
{
public:
	//OBJ�t�@�C������3D���f����ǂݍ���
	static Model* LoadFromObj(const std::string& modelname, XMFLOAT3 minModel, XMFLOAT3 maxModel);
	//�f�o�C�X�Z�b�^�[
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

private:
	//OBJ�t�@�C������3D���f����ǂݍ���
	void LoadFromOBJInternal(const std::string& modelname,XMFLOAT3 minModel, XMFLOAT3 maxModel);
	//�o�b�t�@����
	void CreateBuff();
	//�}�e���A���ǂݍ���
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	//�e�N�X�`���ǂݍ���
	void LoadTexture(const std::string& directoryPath, const std::string& filename);
	//�f�X�N���v�^�q�[�v�̏�����
	void InitializeDescriptorHeap();
public://�����o�֐�
	//�`��
	void Draw(ID3D12GraphicsCommandList*cmdList,UINT rootParamIndexMaterial);
	//�Q�b�^�[
	XMFLOAT3 GetminModel()const { return minModel; }
	XMFLOAT3 GetmaxModel()const { return maxModel; }
public:
	//�T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};
	//�}�e���A��
	struct Material
	{
		std::string name; //�}�e���A����
		XMFLOAT3 ambient; //�A���r�G���g�e���x
		XMFLOAT3 diffuse; //�f�B�t���[�Y�e���x
		XMFLOAT3 specular; //�X�y�L�����[�e���x
		float alpha; //�A���t�@
		std::string textureFilename; //�e�N�X�`���t�@�C����
		//�R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
	//�萔�o�b�t�@�p
	struct ConstBufferDataB1 {
		XMFLOAT3 ambient;	//�A���r�G���g�W��
		float pad1;			//�p�e�B���O
		XMFLOAT3 diffuse;	//�f�B�t�[�Y�W��
		float pad2;			//�p�e�B���O
		XMFLOAT3 specular;	//�X�y�L�����[�W��
		float alpha;		//�A���t�@
	};

private://�����o�ϐ�
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv>vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short>indices;
	//�}�e���A��
	Material material;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB1;
	//�ŏ��A�ő�
	XMFLOAT3 minModel = {}, maxModel = {};
private://�ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
};

