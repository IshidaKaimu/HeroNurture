#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

//トレーニング時上昇値の基礎
constexpr float INCREASE_VALUE = 20.0f;

//=====================================
//ヒーロー基底クラス
//制作者：石田櫂夢
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

	//アニメーション関数
	virtual void Animation();

public:
	// =======================
	// ステータス上昇関数
	// =======================		
	//----トレーニングによる上昇----
	//筋力
	void PowerUp();
	//魔力
	void MagicUp();
	//素早さ
	void SpeedUp();
	//体力
	void HpUp();

	//----イベントによる上昇----
    //筋力
	void PowerUpEvent(float power) 
	{
		m_Param.Power += power; 
		//上昇量描画用の値
		m_PowerUpValue = power;
	};
	//魔力
	void MagicUpEvent(float magic) 
	{
		m_Param.Magic += magic; 
		//上昇量描画用の値
		m_MagicUpValue = magic;
	}
	//素早さ
	void SpeedUpEvent(float speed) 
	{
		m_Param.Speed += speed;
		//上昇量描画用の値
		m_SpeedUpValue = speed;
	}
	//体力
	void HpUpEvent(float hp)
	{ 
		m_Param.Hp += hp; 
		//上昇量描画用の値
		m_HpUpValue = hp;
	}

	// =======================
	// ゲッター・セッター
	// =======================		
	//現在のパラメータ取得
	enParam GetParam()      { return  m_Param; }
	//キャラごとの適正率取得
	enAppropriate GetApp()  { return  m_App; }

	//更新前のパラメータ
	enParam GetBeforeParam() { return m_BeforeParam; }
	void SetBeforeParam(enParam before) { m_BeforeParam = before; }

	//上昇量
	//筋力
	float GetPowerUpValue() { return m_PowerUpValue; }
	//魔力
	float GetMagicUpValue() { return m_MagicUpValue; }
	//素早さ
	float GetSpeedUpValue() { return m_SpeedUpValue; }
	//体力
	float GetHpUpValue()    { return m_HpUpValue; }

protected :	
	// =======================
	// jsonファイル関連
	// =======================		
	//各ヒーローの初期パラメータ取得
	void LoadParam( const json& jsondata , const std::string& heroname );
	//各ヒーローのパラメータ更新
	void UpdateParam( const json& jsondata, const std::string& heroname );

protected:
	//ヒーローのパラメータ構造体
	enParam m_Param;

	//ヒーローの適正率構造体
	enAppropriate m_App;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

private:
	//パラメータ更新前のパラメータ情報
	enParam m_BeforeParam;

	//----ステータス上昇値----
	//筋力
	float m_PowerUpValue;
	//魔力
	float m_MagicUpValue;
	//素早さ
	float m_SpeedUpValue;
	//体力
	float m_HpUpValue;
};