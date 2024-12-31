#pragma once
#include "CBattleHeroSelectScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "KeyManager\CKeyManager.h"

CBattleHeroSelectScene::CBattleHeroSelectScene()
	: m_BattleTurn()
	, m_pJson()
{
}

CBattleHeroSelectScene::~CBattleHeroSelectScene()
{
}

//構築関数
void CBattleHeroSelectScene::Create()
{
	//jsonクラス
	m_pJson = std::make_unique<CJson>();
}

//破棄関数
void CBattleHeroSelectScene::Releace()
{
}

//データ設定関数
void CBattleHeroSelectScene::LoadData()
{
	//育成結果が保存されているファイルのパス
	std::string ResultDataPath = "Data\\Hero\\Result\\Result";
	//育成結果のファイルをロード
	m_pJson->Load(m_ResultData,ResultDataPath);
}

//初期化関数
void CBattleHeroSelectScene::Initialize()
{
	//選択番号の初期化
	m_SelectNo = 1;
}

//更新関数
void CBattleHeroSelectScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }

	//クラスのインスタンスを変数に代入
	CKeyManager* KeyMng = CKeyManager::GetInstance();

	KeyMng->Update();

	//カーソルの移動
	if (KeyMng->IsDown(VK_RIGHT))
	{
		//キー入力で選択を進める
		if (m_SelectNo < m_ResultData.size()) { m_SelectNo++; }
		else { m_SelectNo = 1; }
	}
	else if (KeyMng->IsDown(VK_LEFT))
	{
		if (m_SelectNo > 0) { m_SelectNo--; }
		else { m_SelectNo = 1; }
	}

}

//描画関数
void CBattleHeroSelectScene::Draw()
{
    //クラスのインスタンスを変数に代入
	//テキスト描画クラス
	WriteText* Text = WriteText::GetInstance();

	//保存されている育成データの数を描画
	Text->Draw_Text(std::to_wstring(m_ResultData.size()), WriteText::Normal, NATUREDATA_MAX_POS);

	//選択中の育成データのパラメータの表示
	DrawSaveParameter(m_ResultData,m_SelectNo);
}

//デバッグ処理
void CBattleHeroSelectScene::Debug()
{
}

//保存されているヒーローのパラメータを選択番号ごとに表示する
void CBattleHeroSelectScene::DrawSaveParameter(const json& jsondata, int number)
{
	//クラスのインスタンスを変数に代入
	//テキスト描画クラス
	WriteText* Text = WriteText::GetInstance();
	//ヒーローマネージャー
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	
	for (const auto& data : jsondata)
	{
		if (data["Number"] == number)
		{
			Text->Draw_Text(std::to_wstring(static_cast<int>(data["Parameter"]["Power"])), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS));
			Text->Draw_Text(std::to_wstring(static_cast<int>(data["Parameter"]["Magic"])), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS + PARAMVALUE_INTERVAL_BS, PARAMVALUE_POSY_BS));
			Text->Draw_Text(std::to_wstring(static_cast<int>(data["Parameter"]["Speed"])), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS + (PARAMVALUE_INTERVAL_BS * 2), PARAMVALUE_POSY_BS));
			Text->Draw_Text(std::to_wstring(static_cast<int>(data["Parameter"]["Hp"])), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS + (PARAMVALUE_INTERVAL_BS * 3), PARAMVALUE_POSY_BS));
		}
	}
}
