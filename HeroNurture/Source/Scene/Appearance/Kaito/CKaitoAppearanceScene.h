#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// 定数宣言
//=====================================
namespace Constant_KaitoAppearanceScene
{
	//----カメラ情報----
	//カイト
	const D3DXVECTOR3 INIT_CAMPOS  = { 1.0f, 0.5f, -5.0f };  //初期座標
	const D3DXVECTOR3 INIT_CAMLOOK = { 0.0f, 0.0f,  -5.0f }; //初期注視点
	//------------------
	
	//----イベント演出----
	//カメラ
	constexpr float CAM_MOVE_SPEED = 0.03f; //カメラの動く速度
	//魔法陣エフェクト
	const D3DXVECTOR3 MAGICSIRCLE_POS    = { 0.0f, 0.5f,  -5.0f }; //座標
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //魔法陣を映すカメラ初期座標
	const D3DXVECTOR3 MAGICSIRCLE_SCALE  = { 4.0f, 4.0f, 4.0f };   //魔法陣の拡縮
	const D3DXVECTOR3 MAGICSIRCLE_ROTATE = { D3DXToRadian(90.0f), 1.0f, 1.0f };  //魔法陣の回転
	//光エフェクト
	const D3DXVECTOR3 LASER_POS      = { 0.0f, 0.5f, -5.0f };				 //座標
	const D3DXVECTOR3 LASER_SCALE    = { 5.0f, 5.0f, 5.0f  };				 //拡縮
	const D3DXVECTOR3 LASER_ROTATE   = { D3DXToRadian(270.0f), 1.0f, 1.0f }; //回転
	//-------------------

	//イベント演出用数値
	//----シーン0----
	//移動させるカメラのy軸の値
	constexpr float ANIMCHANGE_CAMPOS_Y = 10.0f;
	//シーンを0から1に遷移させるためのカウント
	constexpr int   ANIMCHANGE_CNT      = 60;  
	//---------------
	
	//----シーン1----
	//カメラを移動させる値の最大値
	const D3DXVECTOR3 MOVE_CAMPOS_MAX         = { 1.0f, 6.0f, 10.0f }; //座標
	constexpr float   MOVE_CAMLOOK_MAX_Y      = 4.0f;				   //注視点y軸
	//次のシーンでの初期座標
	const D3DXVECTOR3 MOVE_CAMPOS_INIT	  = {  0.0f, 1.0f, 5.0f }; //座標
	//シーン1から2へ遷移するために用いるカウント
	constexpr int     SCENECHANGE_CNT_FAST	= 240;
	//---------------

	//----シーン2----
	//カメラを移動させる値の最大値
	constexpr float   MOVE_CAMPOS_MAX_Y    = 4.5f; //座標y軸
	//シーン2から終了するために用いるカウント
	constexpr int     SCENECEND_CNT_SECOND = 120;
	//---------------
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
//-------------------------

//----オブジェクトクラス----
//カイト
class CKaito;
//地面
class CGround;
//--------------------------

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
	
	//登場シーンのカメラ設定関数
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//カメラマネージャー
	CCameraManager* m_pCamera;

	//スキンメッシュ
	std::unique_ptr<CKaito> m_pKaito;//カイト

	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;
	//----------------------------

	//----フラグ----
	//非表示フラグ
	bool m_HiddenFlag;
	//アニメーション、カメラ処理が終了したとき
	bool m_AnimEndFlag;
	//演出スキップフラグ
	bool m_SkipFlag;
	//--------------

};

