#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// 定数宣言
//=====================================
namespace Constant_AppearanceScene
{
	//----カメラ情報----
	const D3DXVECTOR3 INIT_CAMPOS     = { 0.0f, 4.0f, -5.0f };  //初期座標
	const D3DXVECTOR3 INIT_CAMLOOK    = { 0.0f, 4.0f, 0.0f };   //初期注視点
	const D3DXVECTOR3 INIT_MOVECAMPOS = { 0.0f, 0.0f, 0.0f };//初期移動用値
	//----イベント演出----
	//カメラ
	constexpr float CAM_FLICK_DISTANCE  = 25.0f; //タヌキにはじかれる距離
	constexpr float CAM_FLICK_SPEED		= 0.7f;  //タヌキにはじかれる速度
	constexpr float CAM_MOVE_SPEED		= 0.03f; //カメラの動く速度
	//白フェード
	constexpr float FLICK_WHITEFADE		= -3.0f; //カメラがタヌキにはじかれるとき
	//魔法陣エフェクト
	const D3DXVECTOR3 MAGICSIRCLE_POS    = { 0.0f, 0.5f,  -5.0f }; //座標
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //魔法陣を映すカメラ初期座標
	//----イベント演出用数値----
	//----シーン1----
	//このシーンでのカメラ座標をずらす値
	constexpr float SHIFT_CAMPOS = 2.0f;
	//シーンを1から2に遷移させるためのカウント
	constexpr int   ANIMCHANGE_CNT = 60;
	//次のシーンでの初期カメラ情報
	const float MOVE_INIT_CAMPOS_Y  = 2.0f; //y座標
	const float MOVE_INIT_CAMLOOK_Y = 2.0f; //y注視点
	//----シーン2----
	//カメラの最大移動範囲
	constexpr float  MOVEMENT_RANGE_MAX_Y = 6.5f;
	//シーン2から終了するために用いるカウント
	constexpr int  SCENECEND_CNT_SECOND = 120;
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
//テキスト
class WriteText;
//----オブジェクトクラス----
//タヌキ
class CRaccoonDog;
//ユイ
class CYui;
//地面
class CGround;

//=====================================
// ユイ登場シーンクラス
// 制作者:石田櫂夢
//=====================================
class CYuiAppearanceScene
	: public CSceneBase
{
public:
	CYuiAppearanceScene();
	~CYuiAppearanceScene();

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
	//----各ヒーローの登場シーンのカメラ設定関数----
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//カメラマネージャー
	CCameraManager* m_pCamera;

	//----ヒーローのスキンメッシュ----
	std::unique_ptr<CYui>   m_pYui;  //ユイ

	//----登場に使用するヒーロー以外のスキンメッシュ----
	//タヌキ
	std::unique_ptr<CRaccoonDog> m_pRaccoonDog;
	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;

	//----フラグ----
	//非表示フラグ
	bool m_HiddenFlag;	
	//アニメーション、カメラ処理が終了したとき
	bool m_AnimEndFlag;   
	//演出スキップフラグ
	bool m_SkipFlag;

};

