#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "json.hpp"
#include "CJson.h"

//json関係使うのに必要な名前空間を定義
using namespace nlohmann;

/**************************************************
*	プレイヤークラス.
**/
class CPlayer
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

public:
	CPlayer();
	virtual ~CPlayer() override;


	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;



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