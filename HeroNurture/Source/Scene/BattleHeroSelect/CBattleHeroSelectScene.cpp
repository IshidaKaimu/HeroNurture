#pragma once
#include "CBattleHeroSelectScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Scene\CSceneManager.h"
#include "Utility\CUtility.h"
#include "Sound\CSoundManager.h"

CBattleHeroSelectScene::CBattleHeroSelectScene()
	: m_BattleTurn      ()
	, m_pJson			()
	, m_ResultData      ()
	, m_BattleDataWriter()
	, m_pCamera			( &CCameraManager::GetInstance() )
	, m_pParamBack		()
	, m_pYui			()
	, m_pKaito			()
	, m_pLeftArrow		()
	, m_pRightArrow		()
{
}

CBattleHeroSelectScene::~CBattleHeroSelectScene()
{
}

void CBattleHeroSelectScene::Create()
{
	//----インスタンス生成----
	//jsonクラス
	m_pJson = std::make_unique<CJson>();
	//パラメータ背景
	m_pParamBack = std::make_unique<CUIObject>();

	//----ヒーロークラス----
	//カイトクラス
	m_pKaito = std::make_unique<CKaito>();
	//ユイクラス
	m_pYui = std::make_unique<CYui>();

	//----UI----
	m_pLeftArrow = make_unique<CUIObject>();
	m_pRightArrow = make_unique<CUIObject>();

}

void CBattleHeroSelectScene::Releace()
{
}

void CBattleHeroSelectScene::LoadData()
{
	//育成結果が保存されているファイルのパス
	std::string ResultDataPath = "Data\\Hero\\Result\\Result";
	//育成結果のファイルをロード
	m_pJson->Load(m_ResultData,ResultDataPath);

	//----各ヒーロークラスのメッシュデータ設定----
	//ユイ
	m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
	//カイト
	m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

	//----UI----
	m_pLeftArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow)); //矢印左
	m_pRightArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow));//矢印右
	m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));	//パラメータ背景

}

void CBattleHeroSelectScene::Initialize()
{
	//選択番号の初期化
	m_SelectNo = 1;

	//----各ヒーロークラスの初期化----
    //ユイ
	m_pYui->Initialize();
	//カイト
	m_pKaito->Initialize();

	//カメラ情報の設定
	m_pCamera->SetPos(CAMPOS_BS);
	m_pCamera->SetLook(CAMLOOK_BS);

	//パラメータ背景UIの設定
	//位置
	m_pParamBack->SetPosition(PARAMBACK_POS_BS);
	//拡縮
	m_pParamBack->SetScale(PARAMBACK_SCALE_BS);
	//α値
	m_pParamBack->SetAlpha(1.0f);
	//幅
	m_pParamBack->SetDisplay(1.0f, 1.0f);
}

void CBattleHeroSelectScene::Update()
{
	//フェードイン処理
	if (!FadeIn()) { return; }

	//モード選択画面のBGM停止
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

	//モード選択BGMの再生
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_BattleHeroSelect);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_BattleHeroSelect, 40);

	CKeyManager* KeyMng = CKeyManager::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	KeyMng->Update();

	//選択番号の遷移
	if (KeyMng->IsDown(VK_RIGHT))
	{
		//選択SEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

		//キー入力で選択を進める
		if (m_SelectNo < m_ResultData.size()) { m_SelectNo++; }
		else { m_SelectNo = 1; }
	}
	else if (KeyMng->IsDown(VK_LEFT))
	{
		//選択SEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

		if (m_SelectNo > 1) { m_SelectNo--; }
		else { m_SelectNo = m_ResultData.size(); }
	}

	//フェード開始
	if (KeyMng->IsDown(VK_RETURN))
	{
		//決定SEの再生
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

		m_SceneTransitionFlg = true;
	}

	if (m_SceneTransitionFlg && FadeOut())
	{
		//選択した育成データをバトルに使用するデータとして書き込み
		m_pJson->SaveBattleData(m_ResultData,m_BattleDataWriter,m_SelectNo);
		SceneMng->LoadCreate(CSceneManager::Battle);
	}
}

void CBattleHeroSelectScene::Draw()
{
	//カメラの動作
	m_pCamera->CameraUpdate();

	//保存されている育成評価の表示
	DrawResultData();

	//矢印の描画
	DrawArrow();
}

//デバッグ処理
void CBattleHeroSelectScene::Debug()
{
}

void CBattleHeroSelectScene::DrawResultData()
{
	WriteText* Text = WriteText::GetInstance();
	CUtility* Utility = &CUtility::GetInstance();

	//保存されている育成データの数と現在の選択番号を描画
	Text->Draw_Text(std::to_wstring(m_SelectNo) + L"/", WriteText::Normal, Utility->PosCorrection(m_SelectNo,2,SELECTNO_POS.x, SELECTNO_POS.y));
	Text->Draw_Text(std::to_wstring(m_ResultData.size()), WriteText::Normal, NATUREDATA_MAX_POS);

	for (const auto& data : m_ResultData)
	{
		if (data["Number"] == m_SelectNo)
		{
			//選択されているデータのヒーローの描画
			if (data["HeroName"] == "Yui")
			{
				m_pYui->BattleHeroSelectAnimation();
				m_pYui->Draw();
			}
			else if (data["HeroName"] == "Kaito")
			{
				m_pKaito->BattleHeroSelectAnimation();
				m_pKaito->Draw();
			}
		}
	}
	//パラメータ背景の描画
	m_pParamBack->Draw();

	//選択中の育成データのパラメータの描画
	DrawSaveParameter(m_ResultData, m_SelectNo);	 
}


//保存されているヒーローのパラメータを選択番号ごとに描画する
void CBattleHeroSelectScene::DrawSaveParameter(const json& jsondata, int number)
{
	WriteText* Text = WriteText::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CUtility* Utility = &CUtility::GetInstance();

	//「育成ランク」テキストの描画
	std::wstring ResultText = L"育成ランク";
	Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS_BS, false, true);

	for (const auto& data : jsondata)
	{
		if (data["Number"] == number)
		{
			//各パラメータの格納
			float Power = data["Parameter"]["Power"];
			float Magic = data["Parameter"]["Magic"];
			float Speed = data["Parameter"]["Speed"];
			float Hp = data["Parameter"]["Hp"];
			//パラメータの合計
			float ParamTotal = Power + Magic + Speed + Hp;

			//各パラメータの描画
			Text->Draw_Text(std::to_wstring(static_cast<int>(Power)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS));
			Utility->DrawRank(Power, 2,PARAMRANK_POSX_BS, PARAMRANK_POSY_BS);
			Text->Draw_Text(std::to_wstring(static_cast<int>(Magic)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + PARAMVALUE_INTERVAL_BS));
			Utility->DrawRank(Magic, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + PARAMRANK_INTERVAL_BS);
			Text->Draw_Text(std::to_wstring(static_cast<int>(Speed)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + (PARAMVALUE_INTERVAL_BS * 2)));
			Utility->DrawRank(Speed, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + (PARAMRANK_INTERVAL_BS * 2));
			Text->Draw_Text(std::to_wstring(static_cast<int>(Hp)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + (PARAMVALUE_INTERVAL_BS * 3)));
			Utility->DrawRank(Hp, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + (PARAMRANK_INTERVAL_BS * 3));
			
			//育成ランクの描画
			Utility->DrawRank(ParamTotal, 1, RANK_POSX_BS, RANK_POSY_BS);
		}
	}

}

//矢印の描画
void CBattleHeroSelectScene::DrawArrow()
{
	//設定
    //左
    m_pLeftArrow->SetPosition(ARROW_LEFT_POS_BS);
    m_pLeftArrow->SetScale(ARROW_SCALE);
    m_pLeftArrow->SetRotation(ARROW_LEFT_ROTATE);
    m_pLeftArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pLeftArrow->SetAlpha(ARROW_ALPHA);
    //右
    m_pRightArrow->SetPosition(ARROW_RIGHT_POS_BS);
    m_pRightArrow->SetScale(ARROW_SCALE);
    m_pRightArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pRightArrow->SetAlpha(ARROW_ALPHA);

    //描画
    m_pLeftArrow->Draw();
    m_pRightArrow->Draw();

}

