//#include <d3dcompiler.h>

//#include <d3d12.h>
//#include <dxgi1_6.h>
//#include <cassert>
//#include <vector>
//#include <string>
//#include <DirectXMath.h>
//#include<math.h>
//#include <wrl.h>

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


#pragma comment (lib,"d3dcompiler.lib")

enum Scene {
	title,
	game,
	clear,
	gameover
};

bool CheakCollision(XMFLOAT3 posA, XMFLOAT3 posB, XMFLOAT3 sclA, XMFLOAT3 sclB, XMFLOAT3 minModelA, XMFLOAT3 minModelB, XMFLOAT3 maxModelA, XMFLOAT3 maxModelB) {

	XMFLOAT3 minposA = { sclA.x * minModelA.x,sclA.y * minModelA.y,sclA.z * minModelA.z };
	XMFLOAT3 minposB = { sclB.x * minModelB.x,sclB.y * minModelB.y,sclB.z * minModelB.z };
	XMFLOAT3 maxposA = { sclA.x * maxModelA.x,sclA.y * maxModelA.y,sclA.z * maxModelA.z };
	XMFLOAT3 maxposB = { sclB.x * maxModelB.x,sclB.y * maxModelB.y,sclB.z * maxModelB.z };

	minposA = { fabsf(minposA.x),fabsf(minposA.y),fabsf(minposA.z) };
	minposB = { fabsf(minposB.x),fabsf(minposB.y),fabsf(minposB.z) };
	maxposA = { fabsf(maxposA.x),fabsf(maxposA.y),fabsf(maxposA.z) };
	maxposB = { fabsf(maxposB.x),fabsf(maxposB.y),fabsf(maxposB.z) };

	/*sclA = { sclA.x * a,sclA.y * a ,sclA.z * a };
	sclB = { sclB.x * a,sclB.y * a ,sclB.z * a };*/

	if (posA.x - minposA.x < posB.x + maxposB.x && posA.x + maxposA.x > posB.x - minposB.x &&
		posA.y - minposA.y < posB.y + maxposB.y && posA.y + maxposA.y > posB.y - minposB.y &&
		posA.z - minposA.z < posB.z + maxposB.z && posA.z + maxposA.z > posB.z - minposB.z)
	{
		return true;
	}

	return false;
}

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//�@��ՃV�X�e���̏�����
	//�|�C���^
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;


	//WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);


	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), winApp->window_width, winApp->window_height);

	SpriteCommon* spriteCommon = nullptr;
	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);


	//��ՃV�X�e���̏�����

	spriteCommon->LoadTexture(0, "hit.png");
	spriteCommon->LoadTexture(1, "mario.jpg");


	//�ŏ��̃V�[���̏�����
	Sprite* hitsprite = new Sprite();
	hitsprite->Initialize(spriteCommon, 0);

	/*Sprite* sprite1 = new Sprite();
	sprite1->Initialize(spriteCommon, 1);
	sprite1->SetPosition({ 800,300 });*/

	/*OBJ���烂�f���f�[�^��ǂݍ���*/
	//��
	XMFLOAT3 minModel = {}, maxModel = {};
	Model* model = Model::LoadFromObj("Skydome", minModel, maxModel);
	minModel = model->GetminModel();
	maxModel = model->GetmaxModel();

	//�n��
	XMFLOAT3 minModel2 = {}, maxModel2 = {};
	Model* model2 = Model::LoadFromObj("plane", minModel2, maxModel2);
	minModel2 = model2->GetminModel();
	maxModel2 = model2->GetmaxModel();


	//��
	Object3d* sphereobj = Object3d::Create();
	sphereobj->SetModel(model);
	sphereobj->SetPosition({ 0,2,0 });

	//�n��
	Object3d* planeobj = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â���
	planeobj->SetModel(model2);
	//�v���C���[���W�ۑ��p
	DirectX::XMFLOAT3 playerPosition;
	planeobj->SetPosition({ 0,0,0 });
	planeobj->SetScale({ 100.0f,1.0f,10.0f });


	//������
	Sphere sphere;
	sphere.center = XMVectorSet(sphereobj->GetPosition().x, sphereobj->GetPosition().y, sphereobj->GetPosition().z,1); //���S�_���W
	sphere.radius = 1.0f;//���a
	//�n�ʔ���
	Plane plane;
	plane.normal = XMVectorSet(0, 1, 0, 0); //�@���x�N�g��
	plane.distance = 0.0;


	//����
	bool isHit = false;

	//�d��
	const float gravity = 0.05f;

	//�W�����v
	float jumpspeed =0.0f;
	float highjump = 0.8f;
	float normaljump = 0.6f;
	float lowjump = 0.3f;
	int jumpCount = 0;

	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye(0, 5, -30);	//���_���W
	XMFLOAT3 target(0, 0, 0);	//�����_���W
	XMFLOAT3 up(0, 1, 0);		//������x�N�g��
	matView = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	float angle = 0.0f;//�J�����̉�]�p


	//�ŏ��̃V�[���̏�����

#ifdef _DEBUG

#endif
	//�Q�[�����[�v
	while (true) {
		//�@��ՃV�X�e���̍X�V


		//���b�Z�[�W������H
		if (winApp->ProcessMesseage()) {
			//�Q�[�����[�v�𔲂���
			break;
		}

		//DirectX���t���[������ ��������

		//���͂̍X�V
		input->Update();

		XMFLOAT3 spherepos = sphereobj->GetPosition();

		//�ړ�
		if (input->PushKey(DIK_A) || input->PushKey(DIK_D)) {
			if (input->PushKey(DIK_A)) {
				spherepos.x -= 0.05;

			}
			else if (input->PushKey(DIK_D)) {
				spherepos.x += 0.05;

			}
		}
		if (isHit == true) {
			jumpspeed = 0;
			if (input->PushKey(DIK_SPACE)) {
				jumpspeed = normaljump;
				spherepos.y += jumpspeed;
			}
		}
		else if (isHit == false) {
			jumpspeed -= gravity;
			spherepos.y += jumpspeed;
		}


		sphereobj->SetPosition(spherepos);
		sphere.center = XMVectorSet(sphereobj->GetPosition().x, sphereobj->GetPosition().y, sphereobj->GetPosition().z, 1);
		//�����蔻��
		XMVECTOR inter;
		bool hit = Collision::CheckSphere2Plane(sphere, plane, &inter);
		if (hit) {
			isHit = true;
			hitsprite->Update();
		}
		else {
			isHit = false;
		}
		
		sphereobj->SetPosition(spherepos);

		matView = DirectX::XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
		sphereobj->Update(matView);
		planeobj->Update(matView);

		//// 4.�`��R�}���h��������

		dxCommon->PreDraw();
		
		//�ŏ��̃V�[���̕`��
		Object3d::PreDraw(dxCommon->GetCommandlist());
		
		sphereobj->Draw();
		planeobj->Draw();

		Object3d::PostDraw();


		spriteCommon->PreDraw();

		if (isHit) {
			hitsprite->Draw();
		}

		spriteCommon->PostDraw();




		//�ŏ��̃V�[���̕`��

		dxCommon->PostDraw();


		// 4.�`��R�}���h�����܂�


		////DirectX���t���[������ �����܂�
	}

	//�@��ՃV�X�e���̏I��


	//���͊J��
	delete input;
	//WindowsAPI�̏I������
	winApp->Finalize();
	//WindowsAPI�̉��
	delete winApp;
	//DirectX���
	delete dxCommon;
	delete spriteCommon;
	//3d�I�u�W�F�N�g���
	delete sphereobj;
	delete planeobj;
	//3D���f�����
	delete model;
	delete model2;

	//delete model3;
	//delete model4;
	////�ǉ��
	//for (int i = 0; i < wallnum; i++) {
	//	delete wall[i];
	//}
	////���ړ��ǉ��
	//for (int i = 0; i < besideWallnum; i++) {
	//	delete besideWall[i];
	//}
	////�c�ړ����
	//for (int i = 0; i < verticalWallnum; i++) {
	//	delete verticalWall[i];
	//}
	////���J��
	//delete floor;
	//��ՃV�X�e���̏I��

	return 0;
}

