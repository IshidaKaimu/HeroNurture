#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"

//----前方宣言----
class CHeroManager;

//トレーニングシーン
class CTraning
	:public CSceneBase
{
public:
	CTraning();
	~CTraning();

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
	//上昇量テキストの描画
	void DrawUpText();

private:

	//カメラマネージャ
	CCameraManager* m_pCamera;

	//----オブジェクトクラス----
	// スタティックメッシュ
	//スカイボックス
	std::unique_ptr<CSky> m_pSky;
	//地面
	std::unique_ptr<CGround> m_pGround;
};