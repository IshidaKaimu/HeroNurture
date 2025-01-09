#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"

CBattleScene::CBattleScene()
	: m_pHero( &CHeroManager::GetInstance() )
	, m_pEnemyHero( &CEnemyHeroManager::GetInstance() )
	, m_pCamera( &CCameraManager::GetInstance() )
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
		m_pHero->CreateHero(CHeroManager::Yui);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (m_pHero->GetBattleHeroName() == "Kaito")
	{
		m_pHero->CreateHero(CHeroManager::Kaito);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Yui);
	}

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̃C���X�^���X����----
	//�n��
	m_pGround = std::make_unique<CGround>();
	//��
	m_pSky = std::make_unique<CSky>();
}

void CBattleScene::Releace()
{
	m_pHero = nullptr;
}

void CBattleScene::LoadData()
{
	//�I������Ă���q�[���[�̃��b�V���f�[�^�ݒ�
	m_pHero->LoadMeshData();
	//�G�̃q�[���[�̃��b�V���f�[�^�ݒ�
	m_pEnemyHero->LoadMeshData();

	//�t�@�C������o�g���Ɏg�p����f�[�^��ǂݍ���
	std::string BattleDataPath = "Data\\Hero\\BattleData\\BattleData";
	m_pJson->Load(m_BattleData, BattleDataPath);

	//�o�g���Ɏg�p����f�[�^���q�[���[�ɓn��
	m_pHero->SetBattleParamData(m_BattleData);

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̃��b�V���f�[�^�ݒ�----
	//�n��
	m_pGround->LoadData();
	//��
	m_pSky->LoadData();
}

void CBattleScene::Initialize()
{
	//�I�������q�[���[�̏�����
	m_pHero->BattleInitialize();
	//�G�̃q�[���[�̏�����
	m_pEnemyHero->Initialize();
	//�J�������̏�����
	m_pCamera->SetPos(INIT_CAMPOS_B);
	m_pCamera->SetLook(INIT_CAMLOOK_B);
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

	//�J�����̓���
	CCameraManager::GetInstance().CameraUpdate();

	//�I�������q�[���[�̕`��
	m_pHero->Draw();
	//�G�̃q�[���[�̕`��
	m_pEnemyHero->Draw();

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̕`��----
	//�n��
	m_pGround->Draw();
	//��
	m_pSky->Draw();
}

void CBattleScene::Debug()
{

#if DEBUG
	ImGui::Begin(JAPANESE("�p�����[�^"));
	ImGui::Text(JAPANESE("�ؗ�:%f"), m_pHero->GetBattleParam().Power);
	ImGui::Text(JAPANESE("����:%f"), m_pHero->GetBattleParam().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), m_pHero->GetBattleParam().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), m_pHero->GetBattleParam().Hp);
	ImGui::End();

	m_pHero->Debug();
	m_pEnemyHero->Debug();


	CCameraManager::GetInstance().CameraUpdate();

	ImGui::Begin(JAPANESE("�J�����ʒu"));
	ImGui::InputFloat3(JAPANESE("���W:%f"), m_CamPos);
	ImGui::InputFloat3(JAPANESE("�����_:%f"), m_CamLook);
	CCameraManager::GetInstance().SetPos(m_CamPos);
	CCameraManager::GetInstance().SetLook(m_CamLook);
	ImGui::End();
#endif

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
