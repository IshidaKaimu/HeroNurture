#pragma once
#include "SkinMeshObject/Hero/CHeroManager.h"
#include "Scene/CSceneBase.h"
#include <memory>
//----------------
//育成シーンクラス
//----------------
class CNatureScene
	:public CSceneBase
{
public:
	CNatureScene();
	~CNatureScene();

	//構築関数
	void Create()	  override;
	//破棄関数
	void Releace()	  override;
	//データ設定関数
	void LoadData()	  override;
	//初期化関数
	void Initialize() override;
	//更新関数
	void Update()     override;
	//描画関数
	void Draw()		  override;

public:
	//ヒーロークラス
	CHeroManager* m_pHero;

	//カメラマネージャクラス
	CCameraManager* m_pCamera;
};

