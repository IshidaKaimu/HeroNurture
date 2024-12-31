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

//�\�z�֐�
void CBattleHeroSelectScene::Create()
{
	//json�N���X
	m_pJson = std::make_unique<CJson>();
}

//�j���֐�
void CBattleHeroSelectScene::Releace()
{
}

//�f�[�^�ݒ�֐�
void CBattleHeroSelectScene::LoadData()
{
	//�琬���ʂ��ۑ�����Ă���t�@�C���̃p�X
	std::string ResultDataPath = "Data\\Hero\\Result\\Result";
	//�琬���ʂ̃t�@�C�������[�h
	m_pJson->Load(m_ResultData,ResultDataPath);
}

//�������֐�
void CBattleHeroSelectScene::Initialize()
{
	//�I��ԍ��̏�����
	m_SelectNo = 1;
}

//�X�V�֐�
void CBattleHeroSelectScene::Update()
{
	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//�N���X�̃C���X�^���X��ϐ��ɑ��
	CKeyManager* KeyMng = CKeyManager::GetInstance();

	KeyMng->Update();

	//�J�[�\���̈ړ�
	if (KeyMng->IsDown(VK_RIGHT))
	{
		//�L�[���͂őI����i�߂�
		if (m_SelectNo < m_ResultData.size()) { m_SelectNo++; }
		else { m_SelectNo = 1; }
	}
	else if (KeyMng->IsDown(VK_LEFT))
	{
		if (m_SelectNo > 0) { m_SelectNo--; }
		else { m_SelectNo = 1; }
	}

}

//�`��֐�
void CBattleHeroSelectScene::Draw()
{
    //�N���X�̃C���X�^���X��ϐ��ɑ��
	//�e�L�X�g�`��N���X
	WriteText* Text = WriteText::GetInstance();

	//�ۑ�����Ă���琬�f�[�^�̐���`��
	Text->Draw_Text(std::to_wstring(m_ResultData.size()), WriteText::Normal, NATUREDATA_MAX_POS);

	//�I�𒆂̈琬�f�[�^�̃p�����[�^�̕\��
	DrawSaveParameter(m_ResultData,m_SelectNo);
}

//�f�o�b�O����
void CBattleHeroSelectScene::Debug()
{
}

//�ۑ�����Ă���q�[���[�̃p�����[�^��I��ԍ����Ƃɕ\������
void CBattleHeroSelectScene::DrawSaveParameter(const json& jsondata, int number)
{
	//�N���X�̃C���X�^���X��ϐ��ɑ��
	//�e�L�X�g�`��N���X
	WriteText* Text = WriteText::GetInstance();
	//�q�[���[�}�l�[�W���[
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
