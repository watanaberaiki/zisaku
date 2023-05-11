#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteCommon;
	//3d�I�u�W�F�N�g���
	delete sphereobj;
	//3D���f�����
	delete spheremodel;
	delete particleManager;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//���f�������w�肵�ăt�@�C���ǂݍ���
	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	//�p�[�e�B�N��
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

	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//�e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(0, "hit.png");
	spriteCommon->LoadTexture(1, "mario.jpg");

	//�X�v���C�g�Ƀe�N�X�`�����蓖��
	hitsprite->Initialize(spriteCommon, 0);
	mariosprite->Initialize(spriteCommon, 1);
	//�X�v���C�g�����ʒu
	mariosprite->SetPosition({ 800,0 });
	mariosprite->Update();

	//3D�I�u�W�F�N�g
	spheremodel = Model::LoadFromObj("Skydome");
	//�����蔻��
	minsphereModel = spheremodel->GetminModel();
	maxsphereModel = spheremodel->GetmaxModel();

	//���I�u�W�F�N�g
	sphereobj = Object3d::Create();
	sphereobj->SetModel(spheremodel);
	sphereobj->SetPosition({ 0,1,-10 });

	eye =XMFLOAT3(0, 5, -30);	//���_���W
	target = XMFLOAT3(0, 0, 0);	//�����_���W
	up = XMFLOAT3(0, 1, 0);		//������x�N�g��
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	sphereobj->Update(matView);
}

void GameScene::Draw()
{
	//�I�u�W�F�N�g�`��
	Object3d::PreDraw(dxCommon_->GetCommandlist());

	sphereobj->Draw();

	Object3d::PostDraw();

	//�X�v���C�g�`��
	spriteCommon->PreDraw();


	spriteCommon->PostDraw();
}
