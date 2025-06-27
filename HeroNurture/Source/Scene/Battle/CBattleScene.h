#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json\CJson.h"
#include "Utility\CUtility.h"

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//=====================================
// 前方宣言
//=====================================
//----マネージャークラス----
//シーン
class CSceneManager;
//バトルモード
class CBattleManager;
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

//=====================================
// 定数宣言
//=====================================
namespace Constant_BattleScene 
{
	//----カメラ情報----
	const D3DXVECTOR3 INIT_CAMPOS	= { -1.5f,2.0f,-7.0f };		   //初期座標
	const D3DXVECTOR3 INIT_CAMLOOK  = { -1.5f,2.0f,0.0f };		   //初期注視点
	const D3DXVECTOR3 INIT_MOVE_CAMPOS  = { -8.0f, 1.0f, 0.0f };   //カメラを動かす値の初期座標
	const D3DXVECTOR3 INIT_MOVE_CAMLOOK = { 0.0f, 1.0f, 0.0f };    //カメラを動かす値の初期注視点
	//行動選択時
	//2カット目(カット番号は1)
	constexpr float   START_CAMPOS_FAST_Y    = 4.0f;				 //開始時座標
	constexpr float   START_CAMPOS_FAST_Z    = -3.0f;				 //開始時座標
	const D3DXVECTOR3 START_CAMLOOK_FAST     = { 0.0f, 2.0f, 0.0f }; //開始時注視点
	constexpr float   MAX_MOVE_CAMPOS_FAST_X = 8.0f;			     //動かすカメラ座標のy軸最大値
    //3カット目
	constexpr float   SHIFT_CAMPOS_SECOND_X    = 2.0f;			   //開始時座標をずらすx軸の値
	constexpr float   SHIFT_CAMPOS_SECOND_Z    = 1.0f;			   //開始時座標をずらすz軸の値
	constexpr float   MAX_MOVE_CAMPOS_SECOND_Y = 2.0f;			   //動かすカメラ座標のy軸最大値
	//4カット目
	constexpr float   SHIFT_CAMPOS_THIRD_X    = 4.0f;			   //開始時座標をずらすx軸の値
	constexpr float   SHIFT_CAMPOS_THIRD_Z    = -1.5f;			   //開始時座標をずらすz軸の値
	constexpr float   MAX_MOVE_CAMPOS_THIRD_Y = 2.0f;			   //動かすカメラ座標のy軸最大値
	//カット遷移の前に少し止める際に使うカウント
	constexpr int     CHANGE_CUT = 60;							   

	//攻撃時
	const D3DXVECTOR3 ATTACK_CAMPOS  = { -1.0f,2.0f,0.0f };		  //座標(自分)
	const D3DXVECTOR3 ATTACK_CAMLOOK = { -2.0f,2.0f,0.0f };       //注視点(自分)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMPOS  = { -1.0f,2.0f,0.0f }; //座標(敵)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMLOOK = { 2.0f,2.0f,0.0f };  //注視点(敵)
	constexpr float   CAM_MOVESPEED = 0.03f;				      //カメラの移動速度
	constexpr float   ANIM_VECTOR_VALUE = 1.0f;				      //役割に応じてアニメーションの向きを決める値
	//------------------

	//----ゲージ情報----
	//HP
	const D3DXVECTOR3 HPGAUGE_POS     = { 0.0f, 80.0f, 0.0f };	//座標
	const D3DXVECTOR3 HPGAUGE_SCALE   = { 0.8f, 0.8f, 0.8f };	//拡縮
	const D3DXVECTOR2 HPGAUGE_DISPLAY = { 1.0f, 1.2f };			//幅
	//HPの枠
	const D3DXVECTOR3 HPFRAME_POS = { 0.0f, 74.0f, 0.0f };		//座標
	//敵のHP
	const D3DXVECTOR3 ENEMY_HPGAUGE_POS  = { 800.0f, 80.2f, 0.0f }; //座標
	//敵のHPの枠
	const D3DXVECTOR3 ENEMY_HPFRAME_POS = { 800.0f, 74.0f, 0.0f };	//座標

	//減少幅アニメーションの開始カウント
	constexpr int HP_DECREASE_ANIM_START = 60; 
	//-----------------
	
	//----行動選択----
	//筋力攻撃アイコン
	const D3DXVECTOR3 POWER_ATTACK_POS = { 420.0f, 540.0f, 0.0f }; //座標
	//魔法攻撃アイコン
	const D3DXVECTOR3 MAGIC_ATTACK_POS = { 620.0f, 540.0f, 0.0f }; //座標
	//共通
	const D3DXVECTOR3 ATTACK_SCALE = { 0.5f, 0.5f, 0.5f };	//拡縮
	const D3DXVECTOR2 ATTACK_DISP  = { 1.0f, 1.0f };		//幅
	const float ATTACK_ALPHA = 1.0f;
	//攻撃アイコンに被せる画像
	constexpr float ATTACK_COVER_ALPHA = 0.8f;
	//----------------

	
	//----ターン数----
	const D3DXVECTOR2 HERO_TURNTEXT_POS  = { 450.0f, -30.0f };	//座標(自分)
	const D3DXVECTOR2 ENEMY_TURNTEXT_POS = { 340.0f, -30.0f };	//座標(敵)
	//----------------

	//----役割ごとの名前----
	//ユイ
	const D3DXVECTOR2 YUI_TEXT_POS		 = { 0.0f, -30.0f };	//座標(自分)
	const D3DXVECTOR2 ENEMY_YUI_TEXT_POS = { 1150.0f, -30.0f }; //座標(敵)

	//カイト
	const D3DXVECTOR2 KAITO_TEXT_POS	   = { 0.0f, -30.0f };	  //座標(自分)
	const D3DXVECTOR2 ENEMY_KAITO_TEXT_POS = { 1100.0f, -30.0f }; //座標(敵)
	//----------------------
}

//=====================================
// バトルシーンクラス
// 制作者:石田櫂夢
//=====================================
class CBattleScene
	:public CSceneBase
{
private:

  //=====================================
  //列挙型
  //=====================================

	//攻撃の種類
	enum enAttackList :char
	{
		PowerAttack, //筋力による攻撃
		MagicAttack, //魔力による攻撃
		Max,
	};

	//バトルのフェーズ
	enum enBattlePhase
	{
		MoveSelectPhase, //攻撃の選択をするフェーズ
		AttackPhase,	 //お互いに攻撃するフェーズ
		SetUpPhase,		 //次のターンの準備をするフェーズ
	};

public:
	CBattleScene();
	~CBattleScene();

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

	//デバッグ処理
	void Debug();

private:
	//バトルに使用するデータの読み込み
	void LoadBattleData();

	//攻撃アイコンの描画
	void DrawAttack(std::unique_ptr<CUIObject>& icon, D3DXVECTOR3 pos, float alpha);
	 
	//----体力ゲージ関連----
	
	//それぞれの体力ゲージの描画
	void DrawHpGauge();
	
	//体力ゲージ/背景の初期設定
	void InitHpGauge();
	
	//体力ゲージのアニメーション
	void HpGaugeAnim(std::unique_ptr<CUIObject>& gauge, float hp, float maxhp, float speed, float& width);

	//体力ゲージ減少幅のアニメーション
	void HpDecreaseAnim(std::unique_ptr<CUIObject>& gauge, float hp, float maxhp, float speed, float& width);
	
	//----------------------

	//----各フェーズで行う処理----
	
	//行動選択フェーズ
	void MoveSelect();		 //主な処理
	void MoveSelectCamera(); //カメラの動き
	
	//攻撃フェーズ
	void Attack();			 //主な処理
	
	//次のターンの準備フェーズ
	void SetUpToNextTurn();	 //主な処理
	
	//----------------------------

	//----それぞれのターンに行う処理----
	
	//自分
	void HeroTurn();     //行動処理
	void DrawHeroTurn(); //UI等描画処理
	
	//敵
	void EnemyHeroTurn();     //行動処理
	void DrawEnemyHeroTurn(); //UI等描画処理
	//ターンごとの攻撃の設定
	void SettingAttack(int no , enAttackList& attacklist);
	
	//----------------------------------

private:
	//カメラマネージャー
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----スタティックメッシュ----
	
	//地面
	std::unique_ptr<CGround> m_pGround;
	
	//----------------------------
	
	//----UI----
	
	//自分の体力ゲージ
	std::unique_ptr<CUIObject> m_pHpGauge;		//ゲージ
	std::unique_ptr<CUIObject> m_pHpGaugeBack;	//背景
	std::unique_ptr<CUIObject> m_pHpGaugeFrame;	//枠
	std::unique_ptr<CUIObject> m_pHpDecrease;	//減少幅	

	
	//敵の体力ゲージ
	std::unique_ptr<CUIObject> m_pEnemyHpGauge;		 //ゲージ
	std::unique_ptr<CUIObject> m_pEnemyHpGaugeBack;	 //背景
	std::unique_ptr<CUIObject> m_pEnemyHpGaugeFrame; //枠
	std::unique_ptr<CUIObject> m_pEnemyHpDecrease;	 //減少幅	

	//筋力攻撃アイコン
	std::unique_ptr<CUIObject> m_pPowerAttack;
	
	//魔力攻撃アイコン
	std::unique_ptr<CUIObject> m_pMagicAttack;
	
	//選択されていない攻撃アイコンにかぶせる画像
	std::unique_ptr<CUIObject> m_pAttackCover;
	
	//----------

	//========================

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//バトルに使用するパラメータのデータ
	json m_BattleData;
	//敵のパラメータのデータ
	json m_EnemyHeroData;

	//----体力ゲージの変動する幅----
	
	//自分
	float m_HpWidth;		 //ゲージ本体
	float m_HpDecreaseWidth; //減少時に見える画像

	//敵
	float m_EnemyHpWidth;		  //ゲージ本体
	float m_EnemyHpDecreaseWidth; //減少時に見える画像

	//------------------------------

	//経過ターン数
	int m_BattleTurn;

	//行動選択中のカメラに用いるカット番号
	int m_MoveSelectCut;

	//----体力ゲージ減少幅のアニメーションの開始カウント----
	
	int m_HpDecreaseAnimStartCount;			//自分
	int m_EnemyHpDecreaseAnimStartCount;	//敵

	//------------------------------------------------------

	//----フラグ----
	
	//ターンの順
	bool m_IsHeroTurn;
	
	//現在どちらのターンか
	bool m_CurrentTurn;
	
	//行動を選択済みであるか
	bool m_SelectAttack;

	//体力の減少中か
	bool m_HpGageAnim;

	//-------------

	//----列挙型----
	
	//自分が選択する攻撃のリスト
	enAttackList m_Attack;
	
	//敵の選択する攻撃のリスト
	enAttackList m_EnemyAttack;
	
	//敵の攻撃を決める番号
	int m_EnemyAttackNo;
	
	//バトルのフェーズ
	enBattlePhase m_BattlePhase;
	
	//--------------


};