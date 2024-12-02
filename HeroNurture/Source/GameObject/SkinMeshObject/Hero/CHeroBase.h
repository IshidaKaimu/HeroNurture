#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "Json\CJson.h"

//Json使用に必要な名前空間の格納
using json = nlohmann::json;

/**************************************************
*	ヒーロー基底クラス.
**/
class CHeroBase
	: public CSkinMeshObject
{
public :
	//ステータス構造体
	struct enStatus
	{
		//筋力
		int Power;
		//魔力
		int Magic;
		//素早さ
		int Speed;
		//体力
		int Hp;
	};

	//キャラクターリスト構造体
	enum enCharacterList : unsigned char
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
	virtual void LoadData(const json& jsondata) {};

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw();

	//アニメーション関数
	virtual void Animation();

public:
	//----ステータス上昇関数----
    //筋力
	void PowerUp(int power) 
	{
		m_Param.Power += power; 
		//上昇量描画用の値
		m_PowerUpValue = power;
	};
	//魔力
	void MagicUp(int magic) 
	{
		m_Param.Magic += magic; 
		//上昇量描画用の値
		m_MagicUpValue = magic;
	}
	//素早さ
	void SpeedUp(int speed) 
	{
		m_Param.Speed += speed;
		//上昇量描画用の値
		m_SpeedUpValue = speed;
	}
	//体力
	void HpUp(int hp)
	{ 
		m_Param.Hp += hp; 
		//上昇量描画用の値
		m_HpUpValue = hp;
	}

	//----ゲッター・セッター----
	//現在のパラメータ取得
	enStatus GetParam()   { return  m_Param; }
	//上昇量の取得
	//筋力
	int GetPowerUpValue() { return m_PowerUpValue; }
	//魔力
	int GetMagicUpValue() { return m_MagicUpValue; }
	//素早さ
	int GetSpeedUpValue() { return m_SpeedUpValue; }
	//体力
	int GetHpUpValue()    { return m_HpUpValue; }

protected :	
	//----json関連----
	//各ヒーローの初期パラメータ取得
	void LoadParam( const json& jsondata , const std::string& heroname );

protected:
	//プレイヤーのパラメータ構造体
	enStatus m_Param;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

private:
	//----ステータス上昇値----
	//筋力
	int m_PowerUpValue;
	//魔力
	int m_MagicUpValue;
	//素早さ
	int m_SpeedUpValue;
	//体力
	int m_HpUpValue;


};