#pragma once
#include "CBattleHeroSelectScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Scene\CSceneManager.h"
#include "Utility\CUtility.h"
#include "Rank\CRank.h"
#include "Sound\CSoundManager.h"

//�萔�錾�̖��O���
using namespace Constant_BattleHeroSelectScene;

CBattleHeroSelectScene::CBattleHeroSelectScene()
	: m_BattleTurn      ()
	, m_pJson			()
	, m_ResultData      ()
	, m_BattleDataWriter()
	, m_pCamera			( &CCameraManager::GetInstance() )
	, m_pParamBack		()
	, m_pLeftArrow      ()
	, m_pRightArrow		()
	, m_pYui			()
	, m_pKaito			()
	, m_BackSceneFlag   ()
{
}

CBattleHeroSelectScene::~CBattleHeroSelectScene()
{
}

void CBattleHeroSelectScene::Create()
{
	//----�C���X�^���X����----
	//json�N���X
	m_pJson = std::make_unique<CJson>();
	//�p�����[�^�w�i
	m_pParamBack = std::make_unique<CUIObject>();

	//----�q�[���[�N���X----
	//�J�C�g�N���X
	m_pKaito = std::make_unique<CKaito>();
	//���C�N���X
	m_pYui = std::make_unique<CYui>();

	//----UI----
	m_pLeftArrow  = make_unique<CUIObject>();
	m_pRightArrow = make_unique<CUIObject>();
}

void CBattleHeroSelectScene::Releace()
{
}

void CBattleHeroSelectScene::LoadData()
{
	CSceneManager* SceneMng = CSceneManager::GetInstance();
	
	//�ݒ肳��Ă��郆�[�U�[���̎擾
	std::string UserName = SceneMng->GetStringName();

	//�琬���ʂ��ۑ�����Ă���t�@�C���̃p�X
	std::string ResultDataPath = "Data\\Acount\\" + UserName + "\\Result\\Result";
	//�琬���ʂ̃t�@�C�������[�h
	m_pJson->Load(m_ResultData,ResultDataPath);

	//----�e�q�[���[�N���X�̃��b�V���f�[�^�ݒ�----
	//���C
	m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
	//�J�C�g
	m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

	//----UI----
	//���
	m_pLeftArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow));          
	//���E
	m_pRightArrow->AttachSprite(CUIManager::GetSprite(CUIManager::Arrow));         
	//�p�����[�^�w�i
	m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ResultParamList));

}

void CBattleHeroSelectScene::Initialize()
{
	//�I��ԍ��̏�����
	m_SelectNo = 1;

	//----�e�q�[���[�N���X�̏�����----
    //���C
	m_pYui->Initialize();
	//�J�C�g
	m_pKaito->Initialize();

	//�J�������̐ݒ�
	m_pCamera->SetPos(CAMPOS);
	m_pCamera->SetLook(CAMLOOK);
}

void CBattleHeroSelectScene::Update()
{
	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//���[�h�I����ʂ�BGM��~
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

	//���[�h�I��BGM�̍Đ�
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_BattleHeroSelect);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_BattleHeroSelect, 40);

	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	KeyMng->Update();

	//�I��ԍ��̑J��
	if (KeyMng->IsDown(VK_RIGHT))
	{
		//�I��SE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

		//�L�[���͂őI����i�߂�
		if (m_SelectNo < m_ResultData.size()) { m_SelectNo++; }
		else { m_SelectNo = 1; }
	}
	else if (KeyMng->IsDown(VK_LEFT))
	{
		//�I��SE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

		if (m_SelectNo > 1) { m_SelectNo--; }
		else { m_SelectNo = m_ResultData.size(); }
	}

	//�o�g���Ɏg�p����q�[���[�����߂���
	if (KeyMng->IsDown(VK_RETURN))
	{
		//����SE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);
		//�t�F�[�h�J�n
		m_SceneTransitionFlg = true;
	}

	//Escape�L�[�������ꂽ��
	if (KeyMng->IsDown(VK_ESCAPE))
	{
		//����SE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);	
		//�O�̃V�[���ɖ߂��t���O�𗧂Ă�
		m_BackSceneFlag = true;
		//�t�F�[�h�J�n
		m_SceneTransitionFlg = true;
	}

	if (m_SceneTransitionFlg && FadeOut())
	{
		//�I�������琬�f�[�^���o�g���Ɏg�p����f�[�^�Ƃ��ď�������
		m_pJson->SaveBattleData(m_ResultData,m_BattleDataWriter,m_SelectNo);
		//�������I�������q�[���[�o��V�[����
		if (!m_BackSceneFlag)
		{
			if (HeroMng->GetBattleHeroName() == "Yui")
			{
				SceneMng->LoadCreate(CSceneManager::YuiAppearance);
			}
			else if (HeroMng->GetBattleHeroName() == "Kaito")
			{
				SceneMng->LoadCreate(CSceneManager::KaitoAppearance);
			}
		}
		else
		{
			SceneMng->LoadCreate(CSceneManager::ModeSelect);
		}
	}
}

void CBattleHeroSelectScene::Draw()
{
	WriteText* Text = WriteText::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//�J�����̓���
	m_pCamera->CameraUpdate();


	SceneMng->GetDx11()->SetDepth(false);
	
	//�ėp�w�i�̕`��
	DrawBasicBackGround();

	//�ۑ�����Ă���琬�]���̕\��
	DrawResultData();

	//���̕`��
	DrawArrow();

	SceneMng->GetDx11()->SetDepth(true);

	//�q�[���[�̕`��
	DrawHero();

	//������@�w���o�[�̕`��
	DrawControlBar(true);
	//������@�w���u���� �I���v�e�L�X�g�̕`��
	Text->Draw_Text(L"���� �I��", WriteText::Control, SELECTTEXT_POS);
}

//�f�o�b�O����
void CBattleHeroSelectScene::Debug()
{
}

void CBattleHeroSelectScene::DrawResultData()
{
	WriteText* Text = WriteText::GetInstance();
	CUtility* Utility = &CUtility::GetInstance();

	//�ۑ�����Ă���琬�f�[�^�̐��ƌ��݂̑I��ԍ���`��
	Text->Draw_Text(std::to_wstring(m_SelectNo) + L"/", WriteText::Normal, Utility->PosCorrection(m_SelectNo,2,SELECTNO_POS));
	Text->Draw_Text(std::to_wstring(m_ResultData.size()), WriteText::Normal, NATUREDATA_MAX_POS);

	//�p�����[�^�w�i�̕`��
	m_pParamBack->SetPosition(PARAMBACK_POS);
	m_pParamBack->SetScale(PARAMBACK_SCALE);
	m_pParamBack->SetDisplay(1.0f, 1.0f);
	m_pParamBack->Draw();

	//�I�𒆂̈琬�f�[�^�̃p�����[�^�̕`��
	DrawSaveParameter(m_ResultData, m_SelectNo);	 
}


//�ۑ�����Ă���q�[���[�̃p�����[�^��I��ԍ����Ƃɕ`�悷��
void CBattleHeroSelectScene::DrawSaveParameter(const json& jsondata, int number)
{
	WriteText* Text = WriteText::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CRank* Rank = &CRank::GetInstance();

	//�u�琬�����N�v�e�L�X�g�̕`��
	std::wstring ResultText = L"�琬�����N";
	Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS, false, true);

	for (const auto& data : jsondata)
	{
		if (data["Number"] == number)
		{
			//�e�p�����[�^�̊i�[
			float Power = data["Parameter"]["Power"];
			float Magic = data["Parameter"]["Magic"];
			float Speed = data["Parameter"]["Speed"];
			float Hp = data["Parameter"]["Hp"];
			//�p�����[�^�̍��v
			float ParamTotal = Power + Magic + Speed + Hp;

			//�e�p�����[�^�̕`��
			Text->Draw_Text(std::to_wstring(static_cast<int>(Power)), WriteText::Normal, PARAMVALUE_POS);
			Rank->DrawRank(Power, 2,PARAMRANK_POS);
			Text->Draw_Text(std::to_wstring(static_cast<int>(Magic)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + PARAMVALUE_INTERVAL));
			Rank->DrawRank(Magic, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + PARAMRANK_INTERVAL));
			Text->Draw_Text(std::to_wstring(static_cast<int>(Speed)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + (PARAMVALUE_INTERVAL * 2)));
			Rank->DrawRank(Speed, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + (PARAMRANK_INTERVAL * 2)));
			Text->Draw_Text(std::to_wstring(static_cast<int>(Hp)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POS.x, PARAMVALUE_POS.y + (PARAMVALUE_INTERVAL * 3)));
			Rank->DrawRank(Hp, 2, D3DXVECTOR2(PARAMRANK_POS.x, PARAMRANK_POS.y + (PARAMRANK_INTERVAL * 3)));
			
			//�琬�����N�̕`��
			Rank->DrawRank(ParamTotal, 1, RANK_POS);
		}
	}

}

//���O���Ƃ̃q�[���[�̕`��
void CBattleHeroSelectScene::DrawHero()
{
	for (const auto& data : m_ResultData)
	{
		if (data["Number"] == m_SelectNo)
		{
			//�I������Ă���f�[�^�̃q�[���[�̕`��
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

}

//���̕`��
void CBattleHeroSelectScene::DrawArrow()
{
	//�ݒ�
    //��
    m_pLeftArrow->SetPosition(ARROW_LEFT_POS_BS);
    m_pLeftArrow->SetScale(ARROW_SCALE);
    m_pLeftArrow->SetRotation(ARROW_LEFT_ROTATE);
    m_pLeftArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pLeftArrow->SetAlpha(ARROW_ALPHA);
    //�E
    m_pRightArrow->SetPosition(ARROW_RIGHT_POS_BS);
    m_pRightArrow->SetScale(ARROW_SCALE);
    m_pRightArrow->SetDisplay(ARROW_DISP.x, ARROW_DISP.y);
    m_pRightArrow->SetAlpha(ARROW_ALPHA);

    //�`��
    m_pLeftArrow->Draw();
    m_pRightArrow->Draw();

}

