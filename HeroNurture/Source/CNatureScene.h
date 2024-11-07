#pragma once
#include "SkinMeshObject/Player/CPlayer.h"
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

	//初期化関数
	void Initialize() override;
	//構築関数
	void Create()	  override;
	//データ設定関数
	void LoadData()	  override;
	//破棄関数
	void Releace()	  override;
	//更新関数
	void Update()     override;
	//描画関数
	void Draw()		  override;


private:
	

public:

	//プレイヤークラス
	std::unique_ptr<CPlayer> m_pPlayer;

};

