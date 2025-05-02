#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// 定数宣言
//=====================================
namespace Constant_AppearanceScene
{
	//----カメラ情報----
	//ユイ
	const D3DXVECTOR3 YUI_CAMPOS  = { 0.0f, 4.0f, -5.0f }; //座標
	const D3DXVECTOR3 YUI_CAMLOOK = { 0.0f, 4.0f, 0.0f }; //注視点
	//カイト
	const D3DXVECTOR3 KAITO_CAMPOS  = { 1.0f, 4.0f, 0.0f }; //座標
	const D3DXVECTOR3 KAITO_CAMLOOK = { 1.0f, 4.0f, 0.0f }; //注視点
	//----イベントシーン----
	//カメラ
	constexpr float CAM_FLICK_DISTANCE  = 25.0f; //タヌキにはじかれる距離
	constexpr float CAM_FLICK_SPEED		= 0.7f;  //タヌキにはじかれる速度
	constexpr float CAM_MOVE_SPEED		= 0.03f;  //カメラの動く速度
	//白フェード
	constexpr float FLICK_WHITEFADE		= -3.0f; //カメラがタヌキにはじかれるとき
}

//=====================================
// 前方宣言
//=====================================
//----マネージャークラス----
//シーン
class CSceneManager;
//スタティックメッシュ
class CMeshManager;
//UI
class CUIManager;
//スキンメッシュ
class CSkinMeshManager;
//サウンド
class CSoundManager;
//ImGui
class ImGuiManager;
//カメラ
class CCameraManager;
//ヒーロー
class CHeroManager;
//敵のヒーロー
class CEnemyHeroManager;
//キー入力
class CKeyManager;
//エフェクト
class CEffect;
//----オブジェクトクラス----
//タヌキ
class CRaccoonDog;
//地面
class CGround;

//=====================================
// ヒーロー登場シーンクラス
// 制作者:石田櫂夢
//=====================================
class CAppearanceScene
	: public CSceneBase
{
public:
	CAppearanceScene();
	~CAppearanceScene();

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

	//デバッグ関数
	void Debug();

private:
	//----各ヒーローの登場シーンのアニメーション関数----
	//ユイ
	void YuiAppearance();
	//カイト
	void KaitoAppearance();
	//----各ヒーローの登場シーンのカメラ設定関数----
	void YuiSetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);
	void KaitoSetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

	//----各ヒーローの条件付き描画----
	//ユイ
	void YuiDraw();
	//カイト
	void KaitoDraw();

private:
	//カメラマネージャー
	CCameraManager* m_pCamera;

	//自分が使うヒーロー
	CHeroManager*      m_pHero;
	//敵のヒーロー
	CEnemyHeroManager* m_pEnemyHero;

	//----登場に使用するヒーロー以外のスキンメッシュ----
	//タヌキ
	std::unique_ptr<CRaccoonDog> m_pRaccoonDog;

	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;

	//----フラグ----
	//各ヒーローのアニメーション、カメラ処理が終了したとき
	bool m_YuiAnimEnd;   //ユイ
	bool m_KaitoAnimEnd; //カイト

};

