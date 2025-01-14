#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"
#include "Utility\CUtility.h"

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

// =======================
// 定数宣言
// =======================
//----トレーニング関連----		
//トレーニングの基本上昇値
constexpr float INCREASE_VALUE = 20.0f;
//----スタミナゲージ関連----
//スタミナの最大値
constexpr float MAX_STAMINA = 100.0f;
//スタミナの基本減少量
constexpr float REDUSE_STAMINA = 25.0f;
//スタミナの基本回復量
constexpr float RECOVERY_STAMINA = 25.0f;


//=====================================
//ヒーロー基底クラス
// 制作者:石田櫂夢
//=====================================
class CHeroBase
	: public CSkinMeshObject
{
public :

	//ヒーロー名リスト
	enum enHeroList :char
	{
		Yui,
		Kaito,
		Max,
	};

	//パラメータ構造体
	struct enParam
	{
		//筋力
		float Power;
		//魔力
		float Magic;
		//素早さ
		float Speed;
		//体力
		float Hp;
	};

	//適正率構造体
	struct enAppropriate
	{
		//筋力
		float PowerApp;
		//魔力
		float MagicApp;
		//素早さ
		float SpeedApp;
		//体力
		float HpApp;
	};

public:
	CHeroBase();
	virtual ~CHeroBase() override;

	// =======================
	// 各シーンごとの初期化
	// =======================
	//主に使用する初期化関数
	virtual void Initialize() {};
	//バトルシーンで使用する初期化
	virtual void BattleInitialize() {};
	//敵になった際の初期化関数
	virtual void EnemyInit() {};

	//データ読み込み関数
	virtual void LoadMeshData() {};

	//パラメータ情報読み込み
	virtual void LoadParamData(const json& jsondata) {};

	//バトルパラメータ情報読み込み
	virtual void SetBattleParamData(const json& jsondata) {};

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw();

	//デバッグ関数
	virtual void Debug() {};

public:
	// =======================
	// シーンごとのアニメーション関数
	// =======================		
	//育成ヒーロー選択シーン
	virtual void NatureHeroSelectAnimation() {};
	//バトルヒーロー選択シーン
	virtual void BattleHeroSelectAnimation() {};
	//育成シーン
	virtual void NatureAnimation(int no) {};

    // =======================
	// 各ヒーローの攻撃関数
	// =======================
	//攻撃1(筋力による攻撃)
	virtual float PowerAttack() { return 0; }
	//攻撃1(魔力による攻撃)
	virtual float MagicAttack() { return 0; }
	//固有攻撃(各ヒーローの一番高いステータスを反映した攻撃)
	virtual float UniqueAttack() { return 0; }

	// =======================
	// ステータス上昇関数
	// =======================		
	//----トレーニングによる上昇----
	//筋力
	void PowerUp( float stamina );
	//魔力
	void MagicUp( float stamina );
	//素早さ
	void SpeedUp( float stamina );
	//体力
	void HpUp( float stamina );

	//ダメージ関数
	void Damage(float damage);

	// =======================
	// ゲッター・セッター関数
	// =======================		
	//育成中のパラメータ
	enParam GetParam()       { return  m_Param; }
	//バトルに使用するパラメータ
	enParam GetBattleParamData() { return m_BattleParam; }
	//バトルに使用するヒーローの名前
	std::string GetBattleHeroName() { return m_BattleHeroName; }
	void SetBattleHeroName(std::string heroname) { m_BattleHeroName = heroname; }
	//キャラごとの適正率
	enAppropriate GetApp()  { return  m_App; }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//トレーニング失敗フラグ
	bool GetFailure() { return m_Failure; }
	void SetFailure(bool failure) { m_Failure = failure; }
	//バトルに使用するパラメータ情報の設定
	void SetBattleParam(const json& jsondata);
	//バトル中のHP
	float GetHp() { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }

protected :	
	// =======================
	// jsonファイル関連関数
	// =======================		
	//各ヒーローの初期パラメータ取得
	void LoadParam(const json& jsondata , const std::string& heroname);
	//各ヒーローのパラメータ更新
	void UpdateParam(const json& jsondata, const std::string& heroname);

private:
	//残りスタミナ量による補正関数
	void CorrectionByStamina(float stamina);
	//失敗率を返す関数
	int FailureRate(float stamina);
	//トレーニング結果関数
	void TraningResult(float stamina, float app, float& param);

protected:
	// =======================
	// パラメータ
	// =======================		
	//育成中
	enParam m_Param;
	//バトル
	enParam m_BattleParam;

	//バトルするヒーローの名前
	std::string m_BattleHeroName;

	//ヒーローの適正率構造体
	enAppropriate m_App;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

	//----デバッグ用----
	D3DXVECTOR3 DebugPos;
	D3DXVECTOR3 DebugScale;

private:
	//パラメータ更新前のパラメータ情報
	enParam m_BeforeParam;

	//残りスタミナによる補正
	float m_Correction;

	//トレーニングが失敗した際に立てるフラグ
	bool m_Failure;

	//----体力関連の変数----
	//現在の体力
	float m_Hp;		//自分
	float m_EnemyHp;//敵

};