#pragma once
#include"Vector3.h"
#include "Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include"Object3d.h"
#include <DirectXMath.h>
#include<math.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include "CollisionPrimitive.h"
#include "Collision.h"
#include"Camera.h"
#include <math.h>
#include"ParticleManager.h"
#include"FbxLoader.h"

class GameScene
{
//�����o�֐�
public:
	GameScene();
	~GameScene();
	//������
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	//�|�C���^
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;

	//�p�[�e�B�N��
	ParticleManager* particleManager = new ParticleManager();

	//�X�v���C�g���ʕ�
	SpriteCommon* spriteCommon = nullptr;
	//�X�v���C�g
	Sprite* hitsprite = new Sprite();
	Sprite* mariosprite = new Sprite();
	
	/*OBJ���烂�f���f�[�^��ǂݍ���*/
	//��
	Model* spheremodel=nullptr;
	//�����蔻��p
	XMFLOAT3 minsphereModel = {}, maxsphereModel = {};
	//��
	Object3d* sphereobj=nullptr;

	//�J�����p
	XMFLOAT3 eye;		//���_���W
	XMFLOAT3 target;	//�����_���W
	XMFLOAT3 up;		//������x�N�g��
	XMMATRIX matView;
};
