#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include <memory>

//----前方宣言----
class WriteText;


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

private:
	//テキストの描画
	void TextDraw();

public:
	//カメラマネージャクラス
	CCameraManager* m_pCamera;

	//----オブジェクトクラス----
	//スタティックメッシュ
	//地面クラス
	CGround*		m_pGround;
	//スカイボックスクラス
	CSky*			m_pSky;


};

