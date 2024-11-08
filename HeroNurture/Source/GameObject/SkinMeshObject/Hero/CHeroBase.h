#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "json.hpp"
#include "CJson.h"

//json関係使うのに必要な名前空間を定義
using namespace nlohmann;

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
		int HP;
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
	virtual void Initialize() = 0;

	//データ読み込み関数
	virtual void LoadData() = 0;

	//更新関数
	virtual void Update();

	//描画関数
	virtual void Draw( LIGHT& light );

	//アニメーション関数
	virtual void Animation() = 0;

public:

	//ユーザーネームの設定
	void SetUserName(const std::string& name) { m_UserName = name; }

	//ファイルデータ読み込み
	void Fromjson(const json& j);

	//ファイルデータ保存関数
	void Tojson(json& j);

	//ステータスセット関数
	bool LoadStatus(const std::string& name);

	//ステータス保存関数
	bool SaveStatus(const std::string& name);

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