#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// 定数宣言
//=====================================
namespace Constant_KaitoAppearanceScene
{
	//----カメラ情報----
	//カイト
	const D3DXVECTOR3 CAMPOS  = { 1.0f, 0.0f, -5.0f };  //座標
	const D3DXVECTOR3 CAMLOOK = { 0.0f, 0.0f,  -5.0f }; //注視点
	//----イベント演出----
	//カメラ
	constexpr float CAM_MOVE_SPEED = 0.03f; //カメラの動く速度
	//魔法陣エフェクト
	const D3DXVECTOR3 MAGICSIRCLE_POS = { 0.0f, 0.5f,  -5.0f }; //座標
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //魔法陣を映すカメラ初期座標
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
//ユイ
class CYui;
//カイト
class CKaito;
//地面
class CGround;

//=====================================
// カイト登場シーンクラス
// 制作者:石田櫂夢
//=====================================
class CKaitoAppearanceScene
	: public CSceneBase
{
public:
	CKaitoAppearanceScene();
	~CKaitoAppearanceScene();

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
	//登場シーンのアニメーション関数
	//カイト
	void KaitoAppearance();
	//----各ヒーローの登場シーンのカメラ設定関数----
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//カメラマネージャー
	CCameraManager* m_pCamera;

	//----ヒーローのスキンメッシュ----
	std::unique_ptr<CYui>   m_pYui;  //ユイ
	std::unique_ptr<CKaito> m_pKaito;//カイト

	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;

	//----フラグ----
	//非表示フラグ
	bool m_HiddenFlag;
	//アニメーション、カメラ処理が終了したとき
	bool m_AnimEndFlag;

};

