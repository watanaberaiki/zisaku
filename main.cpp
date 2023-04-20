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

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//　基盤システムの初期化
	//ポインタ
	Input* input = nullptr;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;


	//WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

#ifdef _DEBUG
	ID3D12Debug1* debugController = nullptr;
	if(SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		//デバッグレイヤーを有効にする
		debugController->EnableDebugLayer();
		//さらにGPU側でもチェックを行えるようにする
		debugController->SetEnableGPUBasedValidation(TRUE);
	}

#endif

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);
#ifdef  _DEBUG
	ID3D12InfoQueue* infoQueue = nullptr;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		//ヤバいエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, false);
		//警告時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, false);
		//解放
		infoQueue->Release();
		//抑制するメッセージのID
		D3D12_MESSAGE_ID denyIds[] = {
			//Windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーメッセージ
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);
	}

#endif 
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//モデル名を指定してファイル読み込み
	FbxLoader::GetInstance()->LoadModelFromFile("cube");

	//入力の初期化
	input = new Input();
	input->Initialize(winApp);

	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), winApp->window_width, winApp->window_height);
	ParticleManager::StaticInitialize(dxCommon, winApp->window_width, winApp->window_height);

	//パーティクル
	ParticleManager* particleManager = new ParticleManager();
	particleManager->Initialize("effect1.png");
	//パーティクル
	for (int i = 0; i < 50; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.001f;
		XMFLOAT3 acc{};
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//色
		const float rnd_color = 1.0f;
		XMFLOAT4 color{  };
		color.x = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.y = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.z = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		color.w = (float)rand() / RAND_MAX * rnd_color - rnd_color / 2.0f;
		//追加
		particleManager->Add(600, pos, vel, acc, 1.0f, 0.0f, color);
	}
	particleManager->Update();

	SpriteCommon* spriteCommon = nullptr;
	//スプライト共通部の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);


	//基盤システムの初期化
	spriteCommon->LoadTexture(0, "hit.png");
	spriteCommon->LoadTexture(1, "mario.jpg");


	//最初のシーンの初期化
	Sprite* hitsprite = new Sprite();
	hitsprite->Initialize(spriteCommon, 0);
	Sprite* mariosprite = new Sprite();
	mariosprite->Initialize(spriteCommon, 1);
	mariosprite->SetPosition({ 800,0 });
	mariosprite->Update();


	/*OBJからモデルデータを読み込む*/
	//球
	XMFLOAT3 minsphereModel = {}, maxsphereModel = {};
	Model* spheremodel = Model::LoadFromObj("Skydome", minsphereModel, maxsphereModel);
	minsphereModel = spheremodel->GetminModel();
	maxsphereModel = spheremodel->GetmaxModel();



	//球
	Object3d* sphereobj = Object3d::Create();
	sphereobj->SetModel(spheremodel);
	sphereobj->SetPosition({ 0,2,0 });

	/*Camera* camera;
	camera->Initialize(input);*/
	XMFLOAT3 eye(0, 5, -30);	//視点座標
	XMFLOAT3 target(0, 0, 0);	//注視点座標
	XMFLOAT3 up(0, 1, 0);		//上方向ベクトル
	XMMATRIX matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	//最初のシーンの初期化

#ifdef _DEBUG

#endif
	//ゲームループ
	while (true) {
		//　基盤システムの更新


		//メッセージがある？
		if (winApp->ProcessMesseage()) {
			//ゲームループを抜ける
			break;
		}

		//DirectX毎フレーム処理 ここから

		//入力の更新
		input->Update();

		sphereobj->Update(matView);
		
		//// 4.描画コマンドここから

		dxCommon->PreDraw();
		
		//最初のシーンの描画
		Object3d::PreDraw(dxCommon->GetCommandlist());

		sphereobj->Draw();

		Object3d::PostDraw();


		spriteCommon->PreDraw();


		spriteCommon->PostDraw();

		

		//最初のシーンの描画

		dxCommon->PostDraw();


		// 4.描画コマンドここまで


		////DirectX毎フレーム処理 ここまで
	}

	//　基盤システムの終了


	//入力開放
	delete input;
	//WindowsAPIの終了処理
	winApp->Finalize();
	//WindowsAPIの解放
	delete winApp;
	//DirectX解放
	delete dxCommon;
	delete spriteCommon;
	//3dオブジェクト解放
	delete sphereobj;
	//3Dモデル解放
	delete spheremodel;
	delete particleManager;
	//カメラ解放
	/*delete camera;*/
	FbxLoader::GetInstance()->Finalize();
	//基盤システムの終了

	return 0;
}

