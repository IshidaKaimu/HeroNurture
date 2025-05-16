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
	const D3DXVECTOR3 INIT_CAMPOS	= { -1.0f,2.0f,-7.0f };		//初期座標
	const D3DXVECTOR3 INIT_CAMLOOK  = { -1.0f,2.0f,0.0f };		//初期注視点
	const D3DXVECTOR3 ATTACK_CAMPOS = { -1.0f,2.0f,0.0f };		//攻撃時座標(自分)
	const D3DXVECTOR3 ATTACK_CAMLOOK	   = { -2.0f,2.0f,0.0f }; //攻撃時注視点(自分)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMPOS  = { -1.0f,2.0f,0.0f }; //攻撃時座標(敵)
	const D3DXVECTOR3 ENEMY_ATTACK_CAMLOOK = { 2.0f,2.0f,0.0f };  //攻撃時注視点(敵)
	//----ゲージ情報----
	//HP
	const D3DXVECTOR3 HPGAGE_POS = { 0.0f, 16.0f, 0.0f }; //座標
	const D3DXVECTOR3 HPGAGE_SCALE = { 0.8f, 0.8f, 0.8f };//拡縮
	const D3DXVECTOR2 HPGAGE_DISPLAY = { 1.0f, 1.0f };	  //幅
	//HPの枠
	const D3DXVECTOR3 HPFRAME_POS = { 0.0f, 10.0f, 0.0f };
	//敵のHP
	const D3DXVECTOR3 ENEMY_HPGAGE_POS  = { 800.0f, 16.0f, 0.0f };  //座標
	//敵のHPの枠
	const D3DXVECTOR3 ENEMY_HPFRAME_POS = { 800.0f, 10.0f, 0.0f }; //座標
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
	//----ターン名----
	const D3DXVECTOR2 HERO_TURNTEXT_POS  = { 450.0f, 50.0f };	//座標(自分)
	const D3DXVECTOR2 ENEMY_TURNTEXT_POS = { 340.0f, 50.0f };	//座標(敵)
}

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
	void DrawAttack(std::unique_ptr<CUIObject>& icon,D3DXVECTOR3 pos,float alpha);

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
	void HeroTurn();     //行動処理
	void DrawHeroTurn(); //UI等描画処理
	//敵
	void EnemyHeroTurn();     //行動処理
	void DrawEnemyHeroTurn(); //UI等描画処理

	//ターンごとの攻撃の設定
	void SettingAttack(int no , enAttackList& attacklist);

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
	//筋力攻撃アイコン
	std::unique_ptr<CUIObject> m_pPowerAttack;
	//魔力攻撃アイコン
	std::unique_ptr<CUIObject> m_pMagicAttack;
	//選択されていない攻撃アイコンにかぶせる画像
	std::unique_ptr<CUIObject> m_pAttackCover;

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

	//ターンの順を決めるフラグ
	bool m_IsHeroTurn;

	//現在どちらのターンかを判断するフラグ
	bool m_CurrentTurn;

	//行動を選択済みであるかの判断
	bool m_SelectAttack;

	//自分が選択する攻撃のリスト
	enAttackList m_Attack;

	//敵の行動を決める番号
	int m_EnemyAttackNo;

	//敵の選択する攻撃のリスト
	enAttackList m_EnemyAttack;

	//バトルのフェーズ
	enBattlePhase m_BattlePhase;

};