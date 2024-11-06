#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "json.hpp"

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
	struct enParamater
	{
		//ユーザー名
		std::string Username;
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

	//ユーザーネームの設定
	void SetUserName(std::wstring& name) { m_UserName = name; }

	//データ読み込み関数
	void SetData(std::wstring& name);

	//データ作成関数
	void MakeData(std::wstring& name);

	//ステータス書き込み関数
	void WriteData(std::wstring name,int power,int magic, int speed,int hp);


protected:
	//プレイヤーのパラメータ構造体
	enParamater m_Para;

	//ユーザーネーム
	std::wstring m_UserName;

	//ステータスファイル
	json Status;


};