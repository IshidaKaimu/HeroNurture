#pragma once
#include "CBattleHeroSelectScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "KeyManager\CKeyManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Scene\CSceneManager.h"
#include "Utility\CUtility.h"


CBattleHeroSelectScene::CBattleHeroSelectScene()
	: m_BattleTurn()
	, m_pJson()
	, m_ResultData()
	, m_BattleDataWriter()
	, m_pCamera( &CCameraManager::GetInstance() )
	, m_pParamBack()
	, m_pYui()
	, m_pKaito()
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
}

void CBattleHeroSelectScene::Releace()
{
}

void CBattleHeroSelectScene::LoadData()
{
	//�琬���ʂ��ۑ�����Ă���t�@�C���̃p�X
	std::string ResultDataPath = "Data\\Hero\\Result\\Result";
	//�琬���ʂ̃t�@�C�������[�h
	m_pJson->Load(m_ResultData,ResultDataPath);

	//----�e�q�[���[�N���X�̃��b�V���f�[�^�ݒ�----
	//���C
	m_pYui->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Yui));
	//�J�C�g
	m_pKaito->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Kaito));

	//�p�����[�^�w�iUI�̃X�v���C�g��ݒ�
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
	m_pCamera->SetPos(CAMPOS_BS);
	m_pCamera->SetLook(CAMLOOK_BS);

	//�p�����[�^�w�iUI�̐ݒ�
	//�ʒu
	m_pParamBack->SetPosition(PARAMBACK_POS_BS);
	//�g�k
	m_pParamBack->SetScale(PARAMBACK_SCALE_BS);
	//���l
	m_pParamBack->SetAlpha(1.0f);
	//��
	m_pParamBack->SetDisplay(1.0f, 1.0f);
}

void CBattleHeroSelectScene::Update()
{
	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	CKeyManager* KeyMng = CKeyManager::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	KeyMng->Update();

	//�I��ԍ��̑J��
	if (KeyMng->IsDown(VK_RIGHT))
	{
		//�L�[���͂őI����i�߂�
		if (m_SelectNo < m_ResultData.size()) { m_SelectNo++; }
		else { m_SelectNo = 1; }
	}
	else if (KeyMng->IsDown(VK_LEFT))
	{
		if (m_SelectNo > 1) { m_SelectNo--; }
		else { m_SelectNo = m_ResultData.size(); }
	}

	//�t�F�[�h�J�n
	if (KeyMng->IsDown(VK_RETURN))
	{
		m_SceneTransitionFlg = true;
	}

	if (m_SceneTransitionFlg && FadeOut())
	{
		//�I�������琬�f�[�^���o�g���Ɏg�p����f�[�^�Ƃ��ď�������
		m_pJson->SaveBattleData(m_ResultData,m_BattleDataWriter,m_SelectNo);
		SceneMng->LoadCreate(CSceneManager::Battle);
	}
}

void CBattleHeroSelectScene::Draw()
{
	//�J�����̓���
	m_pCamera->CameraUpdate();

	//�ۑ�����Ă���琬�]���̕\��
	DrawResultData();
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
	Text->Draw_Text(std::to_wstring(m_SelectNo) + L"/", WriteText::Normal, Utility->PosCorrection(m_SelectNo,2,SELECTNO_POS.x, SELECTNO_POS.y));
	Text->Draw_Text(std::to_wstring(m_ResultData.size()), WriteText::Normal, NATUREDATA_MAX_POS);

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
	//�p�����[�^�w�i�̕`��
	m_pParamBack->Draw();

	//�I�𒆂̈琬�f�[�^�̃p�����[�^�̕`��
	DrawSaveParameter(m_ResultData, m_SelectNo);	 
}


//�ۑ�����Ă���q�[���[�̃p�����[�^��I��ԍ����Ƃɕ`�悷��
void CBattleHeroSelectScene::DrawSaveParameter(const json& jsondata, int number)
{
	WriteText* Text = WriteText::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CUtility* Utility = &CUtility::GetInstance();

	//�u�琬�����N�v�e�L�X�g�̕`��
	std::wstring ResultText = L"�琬�����N";
	Text->Draw_Text(ResultText, WriteText::Normal, RESULTTEXT_POS_BS, false, true);

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
			Text->Draw_Text(std::to_wstring(static_cast<int>(Power)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS));
			Utility->DrawRank(Power, 2,PARAMRANK_POSX_BS, PARAMRANK_POSY_BS);
			Text->Draw_Text(std::to_wstring(static_cast<int>(Magic)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + PARAMVALUE_INTERVAL_BS));
			Utility->DrawRank(Magic, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + PARAMRANK_INTERVAL_BS);
			Text->Draw_Text(std::to_wstring(static_cast<int>(Speed)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + (PARAMVALUE_INTERVAL_BS * 2)));
			Utility->DrawRank(Speed, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + (PARAMRANK_INTERVAL_BS * 2));
			Text->Draw_Text(std::to_wstring(static_cast<int>(Hp)), WriteText::Normal, D3DXVECTOR2(PARAMVALUE_POSX_BS, PARAMVALUE_POSY_BS + (PARAMVALUE_INTERVAL_BS * 3)));
			Utility->DrawRank(Hp, 2, PARAMRANK_POSX_BS, PARAMRANK_POSY_BS + (PARAMRANK_INTERVAL_BS * 3));
			
			//�琬�����N�̕`��
			Utility->DrawRank(ParamTotal, 1, RANK_POSX_BS, RANK_POSY_BS);
		}
	}

}

