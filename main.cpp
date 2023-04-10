//#include <d3dcompiler.h>

//#include <d3d12.h>
//#include <dxgi1_6.h>
//#include <cassert>
//#include <vector>
//#include <string>
//#include <DirectXMath.h>
//#include<math.h>
//#include <wrl.h>

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
	ParticleManager::StaticInitialize(dxCommon, winApp->window_width, winApp->window_height);

	//�p�[�e�B�N��
	ParticleManager* particleManager = new ParticleManager();
	particleManager->Initialize("effect1.png");
	//�p�[�e�B�N��
	for (int i = 0; i < 50; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		const float rnd_acc = 0.001f;
		XMFLOAT3 acc{};
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//�F
		const float rnd_color = 1.0f;
		XMFLOAT4 color{  };
		color.x = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.y = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.z = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.w = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		//�ǉ�
		particleManager->Add(600, pos, vel, acc, 1.0f, 0.0f, color);
	}
	particleManager->Update();

	ParticleManager* particleManager2 = new ParticleManager();
	particleManager2->Initialize("effect3.png");
	//�p�[�e�B�N��
	for (int i = 0; i < 50; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		const float rnd_acc = 0.001f;
		XMFLOAT3 acc{};
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//�F
		const float rnd_color = 1.0f;
		XMFLOAT4 color{  };
		color.x = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.y = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.z = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.w = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		//�ǉ�
		particleManager2->Add(600, pos, vel, acc, 1.0f, 0.0f, color);
	}
	particleManager2->Update();

	




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
	Sprite* mariosprite = new Sprite();
	mariosprite->Initialize(spriteCommon, 1);
	mariosprite->SetPosition({ 800,0 });
	mariosprite->Update();


	/*Sprite* sprite1 = new Sprite();
	sprite1->Initialize(spriteCommon, 1);
	sprite1->SetPosition({ 800,300 });*/

	/*OBJ���烂�f���f�[�^��ǂݍ���*/
	//��
	XMFLOAT3 minsphereModel = {}, maxsphereModel = {};
	Model* spheremodel = Model::LoadFromObj("Skydome", minsphereModel, maxsphereModel);
	minsphereModel = spheremodel->GetminModel();
	maxsphereModel = spheremodel->GetmaxModel();

	//�n��
	XMFLOAT3 minplaneModel = {}, maxplaneModel = {};
	Model* planemodel = Model::LoadFromObj("plane", minplaneModel, maxplaneModel);
	minplaneModel = planemodel->GetminModel();
	maxplaneModel = planemodel->GetmaxModel();

	//�^���G
	XMFLOAT3 mincubeModel = {}, maxcubeModel = {};
	Model* cubemodel = Model::LoadFromObj("cube", mincubeModel, maxcubeModel);
	mincubeModel = cubemodel->GetminModel();
	maxcubeModel = cubemodel->GetmaxModel();

	//�u���b�N
	XMFLOAT3 minblockModel = {}, maxblockModel = {};
	Model* blockmodel = Model::LoadFromObj("block", minblockModel, maxblockModel);
	minblockModel = blockmodel->GetminModel();
	maxblockModel = blockmodel->GetmaxModel();

	//��
	XMFLOAT3 minredModel = {}, maxredModel = {};
	Model* redmodel = Model::LoadFromObj("redcube", minredModel, maxredModel);
	minredModel = redmodel->GetminModel();
	maxredModel = redmodel->GetmaxModel();


	//��
	Object3d* sphereobj = Object3d::Create();
	sphereobj->SetModel(spheremodel);
	sphereobj->SetPosition({ 0,2,0 });

	//�n��
	Object3d* planeobj = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�Â���
	planeobj->SetModel(planemodel);
	//�v���C���[���W�ۑ��p
	DirectX::XMFLOAT3 playerPosition;
	planeobj->SetPosition({ 0,0,0 });
	planeobj->SetScale({ 100.0f,1.0f,10.0f });

	//�^���G
	Object3d* cubeobj[3];
		for (int i = 0; i < 3; i++) {
			cubeobj[i]= Object3d::Create();
		}
	cubeobj[0]->SetPosition({10,1,5});
	cubeobj[0]->SetRotation({0,90,0});
	cubeobj[0]->SetModel(cubemodel);

	cubeobj[1]->SetPosition({6,1,4});
	cubeobj[1]->SetRotation({ 0,270,0 });
	cubeobj[1]->SetModel(blockmodel);

	cubeobj[2]->SetPosition({ 14,1,4 });
	cubeobj[2]->SetRotation({ 0,270,0 });
	cubeobj[2]->SetModel(blockmodel);

	//�����蔻��
	Object3d* collisionobj=Object3d::Create();
	collisionobj->SetModel(redmodel);
	collisionobj->SetPosition({ 10,1,-2 });
	collisionobj->SetScale({ 3,1,5 });
	collisionobj->SetRotation({ 0,0,0 });

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
	bool isFound = false;
	bool isback = false;
	float countTime = 0;
	float maxTime = 100;

	//�d��
	const float gravity = 0.05f;

	//�W�����v
	float jumpspeed =0.0f;
	float highjump = 0.8f;
	float normaljump = 0.6f;
	float lowjump = 0.3f;
	int jumpCount = 0;


	//�J����
	Camera camera;
	Camera camera2;
	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye(10, 5, -30);	//���_���W
	XMFLOAT3 target(10, 0, 0);	//�����_���W
	XMFLOAT3 up(0, 1, 0);		//������x�N�g��
	camera.Initialize(input);
	camera.SetEye(eye);
	camera.SetTarget(target);
	camera.SetUp(up);

	camera2.Initialize(input);

	XMFLOAT3 enemytarget;
	XMFLOAT3 enemyvec;
	Vector3 enemyEye;

	int cameraNo = 1;
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
				/*spherepos.x -= 0.1;*/
				eye.x -= 1;
			}
			else if (input->PushKey(DIK_D)) {
				/*spherepos.x += 0.1;*/
				eye.x += 1;
			}
		}
		//�W�����v
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
			/*hitsprite->Update();*/
		}
		else {
			isHit = false;
		}

		sphereobj->SetPosition(spherepos);
		//�������Ă��邩�ǂ���
		if (isback == false) {
			if (CheakCollision(sphereobj->GetPosition(), collisionobj->GetPosition(), sphereobj->GetScale(), collisionobj->GetScale(), minsphereModel, minredModel, maxsphereModel, maxredModel)) {
				isFound = true;
				hitsprite->Update();
			}
			else {
				isFound = false;
			}
		}
		else {
			isFound = false;
		}

		

		countTime++;
		if (countTime >= maxTime) {
			if (isback == true) {
				/*particleManager->LoadTexture("effect2.png");*/
				isback = false;
			}
			else {
				/*particleManager->LoadTexture("effect3.png");*/
				isback = true;
			}
			countTime = 0;
		}


		camera.SetEye(eye);

		if (input->TriggerKey(DIK_1)) {
			cameraNo = 1;
		}
		else if (input->TriggerKey(DIK_2)) {
			cameraNo = 2;
		}
		//�J����
		if (cameraNo == 1) {
			camera.Update();
			matView = camera.GetmatView();
		}else if(cameraNo == 2){
			camera2.Update();
			matView = camera2.GetmatView();
		}
		
		if (isback == false) {
			cubeobj[0]->SetRotation({0,90,0});

		}
		else if (isback == true) {
			cubeobj[0]->SetRotation({0,270,0});
		}
		
		sphereobj->Update(matView);
		planeobj->Update(matView);
		for (int i = 0; i < 3; i++) {
			cubeobj[i]->Update(matView);
		}
		collisionobj->Update(matView);


		

		particleManager->Update();
		particleManager2->Update();
		//// 4.�`��R�}���h��������

		dxCommon->PreDraw();
		
		//�ŏ��̃V�[���̕`��
		Object3d::PreDraw(dxCommon->GetCommandlist());

		sphereobj->Draw();
		planeobj->Draw();
		for (int i = 0; i < 3; i++) {
			cubeobj[i]->Draw();
		}
		if (input->PushKey(DIK_3)&& isback == false) {
			collisionobj->Draw();
		}

		Object3d::PostDraw();

		//// 3D�I�u�W�F�N�g�`��O����
		//ParticleManager::PreDraw(dxCommon->GetCommandlist());

		// 3D�I�u�N�W�F�N�g�̕`��
		particleManager->Draw();
		particleManager2->Draw();

		// 3D�I�u�W�F�N�g�`��㏈��

		//ParticleManager::PostDraw();

		spriteCommon->PreDraw();

		hitsprite->Draw();
		mariosprite->Draw();

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
	delete spheremodel;
	delete planemodel;

	delete particleManager;
	delete particleManager2;

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

