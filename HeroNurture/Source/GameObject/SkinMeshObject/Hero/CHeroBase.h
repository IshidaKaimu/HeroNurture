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
//=====================================

class CHeroBase
	: public CSkinMeshObject
{
public :
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

	//キャラクターリスト構造体
	enum enCharacterList : char
	{
		Yui,
		Kaito,
		max,
	};

public:
	CHeroBase();
	virtual ~CHeroBase() override;

	//初期化関数
	//ベースなので何もしない
	virtual void Initialize() {};

	//データ読み込み関数
	virtual void LoadMeshData() {};

	//パラメータ情報読み込み
	virtual void LoadParamData(const json& jsondata) {};

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw();

	// =======================
	// シーンごとのアニメーション関数
	// =======================		
	//ヒーロー選択シーン
	virtual void SelectAnimation() {};
	//育成シーン
	virtual void NatureAnimation(int no) {};

public:
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

	// =======================
	// ゲッター・セッター関数
	// =======================		
	//育成中のパラメータ
	enParam GetParam()      { return  m_Param; }
	//キャラごとの適正率
	enAppropriate GetApp()  { return  m_App; }
	//更新前のパラメータ
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }
	//トレーニング失敗フラグ
	bool GetFailure() { return m_Failure; }
	void SetFailure(bool failure) { m_Failure = failure; }
	//バトルに使用するパラメータ
	enParam GetBattleParam() { return m_BattleParam; }
	void SetBattleParam(enParam battle) { m_BattleParam = battle; }
	void SetBattlePower(float power) { m_BattleParam.Power = power; }
	void SetBattleMagic(float magic) { m_BattleParam.Magic = magic; }
	void SetBattleSpeed(float speed) { m_BattleParam.Speed = speed; }
	void SetBattleHp   (float hp)    { m_BattleParam.Hp = hp; }


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

	//ヒーローの適正率構造体
	enAppropriate m_App;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

private:
	//パラメータ更新前のパラメータ情報
	enParam m_BeforeParam;

	//残りスタミナによる補正
	float m_Correction;

	//トレーニングが失敗した際に立てるフラグ
	bool m_Failure;

};