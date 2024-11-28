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
	virtual void Draw( LIGHT& light );

	//アニメーション関数
	virtual void Animation();

public:

	//----ステータス上昇関数----
	//筋力
	void PowerUp(int power )	    { m_Para.Power += power; }
	//魔力
	void MagicUp(int magic )	    { m_Para.Magic += magic; }
	//素早さ
	void SpeedUp(int speed)         { m_Para.Speed += speed; }
	//体力
	void HpUp(int hp)		        { m_Para.Hp += hp; }

	//----ゲッター・セッター----
	//現在のステータス取得
	enStatus GetStatus() { return m_Para; }

protected:
	//プレイヤーのパラメータ構造体
	enStatus m_Para;

	//jsonクラス
	std::unique_ptr<CJson> m_pJson;

	//ユーザーネーム
	std::string m_UserName;

	//ステータスファイル
	json Status;


};