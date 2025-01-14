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

//=====================================
// 定数宣言(_B = バトルシーンで用いることを示す)
//=====================================
//----カメラ情報----
const D3DXVECTOR3 INIT_CAMPOS_B  = { -1.0f,2.0f,-6.0f }; //初期座標
const D3DXVECTOR3 INIT_CAMLOOK_B = { -1.0f,2.0f,-0.0f }; //初期注視点
//----ゲージ情報----
//HP
const D3DXVECTOR3 HPGAGE_POS     = { 0.0f, 16.0f, 0.0f }; //座標
const D3DXVECTOR3 HPGAGE_SCALE   = { 0.8f, 0.8f, 0.8f };  //拡縮
const D3DXVECTOR2 HPGAGE_DISPLAY = { 1.0f, 1.0f };
//HPの枠
const D3DXVECTOR3 HPFRAME_POS = { 0.0f, 10.0f, 0.0f };
//敵のHP
const D3DXVECTOR3 ENEMY_HPGAGE_POS  = { 800.0f, 16.0f, 0.0f }; //座標
//敵のHPの枠
const D3DXVECTOR3 ENEMY_HPFRAME_POS = { 800.0f, 10.0f, 0.0f }; //座標

//=====================================
// バトルシーンクラス
// 制作者:石田櫂夢
//=====================================
class CBattleScene
	:public CSceneBase
{
private:
	//攻撃の種類
	enum enAttackList :char
	{
		PowerAttack,
		MagicAttack,
		UniqueAttack,
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

	//----体力ゲージ関連----
	//それぞれの体力ゲージの描画
	void DrawHpGage();
	//体力ゲージ/背景の初期設定
	void InitHpGage();
	//体力ゲージのアニメーション
	void HpGageAnim(std::unique_ptr<CUIObject>& gage, float hp, float maxhp, float& width);

	//行動選択フェーズ中の処理
	void MoveSelect();
	//攻撃フェーズ中の処理
	void Attack();
	//次のターン準備中の処理
	void SetUpToNextTurn();

	//----それぞれのターンに行う処理----
	//自分
	void HeroTurn();
	//敵
	void EnemyHeroTurn();
private:
	//自分が使うヒーロー
	CHeroManager* m_pHero;
	//敵のヒーロー
	CEnemyHeroManager* m_pEnemyHero;

	//カメラマネージャー
	CCameraManager* m_pCamera;

	// =======================
	// オブジェクトクラス
	// =======================		
	//----スタティックメッシュ----
	//地面
	std::unique_ptr<CGround> m_pGround;
	//空
	std::unique_ptr<CSky> m_pSky;
	//----UI----
	//自分の体力ゲージ
	std::unique_ptr<CUIObject> m_pHpGage;	   //ゲージ
	std::unique_ptr<CUIObject> m_pHpGageBack;  //背景
	std::unique_ptr<CUIObject> m_pHpGageFrame; //枠
	//敵の体力ゲージ
	std::unique_ptr<CUIObject> m_pEnemyHpGage;	  //ゲージ
	std::unique_ptr<CUIObject> m_pEnemyHpGageBack;//背景
	std::unique_ptr<CUIObject> m_pEnemyHpGageFrame;//枠

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//バトルに使用するパラメータのデータ
	json m_BattleData;
	//敵のパラメータのデータ
	json m_EnemyHeroData;

	//体力ゲージの変動する幅
	float m_HpWidth;    //自分
	float m_EnemyHpWidth;//敵

	//経過ターン数
	int m_BattleTurn;

	//自分のターンであるかのフラグ
	bool m_IsHeroTurn;

	//行動を選択済みであるかの判断
	bool m_SelectAttack;

	//自分が選択する攻撃のリスト
	enAttackList m_Attack;

	//バトルのフェーズ
	enBattlePhase m_BattlePhase;
};