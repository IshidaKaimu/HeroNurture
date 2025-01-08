#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"

CBattleScene::CBattleScene()
	: m_pHero( &CHeroManager::GetInstance() )
	, m_BattleTurn()
{
}

CBattleScene::~CBattleScene()
{
}

void CBattleScene::Create()
{
	//�I�����ꂽ�q�[���[�̃C���X�^���X����
	if (m_pHero->GetBattleHeroName() == "Yui")
	{
		m_pHero->SetHero(CHeroManager::Yui);
	}
	else if (m_pHero->GetBattleHeroName() == "Kaito")
	{
		m_pHero->SetHero(CHeroManager::Kaito);
	}
}

void CBattleScene::Releace()
{
}

void CBattleScene::LoadData()
{
	//�I������Ă���q�[���[�̃��b�V���f�[�^�ݒ�
	m_pHero->LoadMeshData();
	//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
	m_pHero->LoadBattleParamData();

}

void CBattleScene::Initialize()
{
}

void CBattleScene::Update()
{
	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//�f�o�b�O����
	Debug();
}

void CBattleScene::Draw()
{
	//�q�[���[�}�l�[�W���[
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	HeroMng->Draw();
}

void CBattleScene::Debug()
{
	ImGui::Begin(JAPANESE("�p�����[�^"));
	ImGui::Text(JAPANESE("�ؗ�:%f"), m_pHero->GetBattleParam().Power);
	ImGui::Text(JAPANESE("����:%f"), m_pHero->GetBattleParam().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), m_pHero->GetBattleParam().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), m_pHero->GetBattleParam().Hp);
	ImGui::End();
}

//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
void CBattleScene::LoadBattleData()
{
	//�ǂݍ��ރt�@�C���̃p�X
	//�p�����[�^���X�V���ɓǂݍ��ރt�@�C���̃p�X
	std::string BattleDataFilePath = "Data\\Hero\\BattleData\\BattleData";

	//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
	if (!m_pJson->Load(m_BattleData, BattleDataFilePath)) { return; }

}
