#pragma once
#include "CBattleScene.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"

CBattleScene::CBattleScene()
	: m_pHero	  (&CHeroManager::GetInstance())
	, m_pEnemyHero(&CEnemyHeroManager::GetInstance())
	, m_pCamera   (&CCameraManager::GetInstance())
	, m_pGround   ()
	, m_pSky      ()
	, m_pHpGage   ()
	, m_pHpGageBack ()
	, m_pHpGageFrame()
	, m_pEnemyHpGage()
	, m_pEnemyHpGageFrame()
	, m_pJson()
	, m_BattleData()
	, m_EnemyHeroData()
	, m_HpWidth(1.0f)
	, m_EnemyHpWidth(1.0f)
	, m_UniqueGageCnt(0)
	, m_EnemyUniqueGageCnt(0)
	, m_BattleTurn()
	, m_IsHeroTurn()
	, m_SelectAttack()
	, m_Attack()
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

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
	//�n��
	m_pGround = std::make_unique<CGround>();
	//��
	m_pSky = std::make_unique<CSky>();
	//----UI�I�u�W�F�N�g----
	//Hp�Q�[�W
	m_pHpGage      = std::make_unique<CUIObject>();
	m_pHpGageBack  = std::make_unique<CUIObject>();
	m_pHpGageFrame = std::make_unique<CUIObject>();
	//�G��Hp�Q�[�W
	m_pEnemyHpGage      = std::make_unique<CUIObject>();
	m_pEnemyHpGageBack  = std::make_unique<CUIObject>();
	m_pEnemyHpGageFrame = std::make_unique<CUIObject>();
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
	LoadBattleData();
	//�o�g���Ɏg�p����f�[�^���q�[���[�ɓn��
	m_pHero->SetBattleParamData(m_BattleData);
	//�G�̃p�����[�^��G�̃q�[���[�ɓn��
	for (const auto& enemy : m_EnemyHeroData)
	{
		//�G�ɂȂ��Ă���q�[���[�̂��̂̂ݓn��
		if (m_pEnemyHero->GetEnemyHeroName() == enemy["HeroName"])
		{
			m_pEnemyHero->SetBattleParamData(enemy);
		}
	}

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̃��b�V���f�[�^�ݒ�----
	//�n��
	m_pGround->LoadData();
	//��
	m_pSky->LoadData();

	//----UI�I�u�W�F�N�g�̃X�v���C�g�ݒ�----
	//Hp�Q�[�W
	m_pHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//�G��Hp�Q�[�W
	m_pEnemyHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pEnemyHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pEnemyHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
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

	//�̗͂̏�����
	m_pHero->SetHp(m_pHero->GetBattleParamData().Hp * 10.0f);
	m_pEnemyHero->SetHp(m_pEnemyHero->GetBattleParamData().Hp * 10.0f);

	//Hp�Q�[�W�̕\�����ȊO�̐ݒ�
	InitHpGage();
}

void CBattleScene::Update()
{
	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	switch (m_BattlePhase)
	{
	case CBattleScene::MoveSelectPhase: 
		MoveSelect();	//�U���̑I��
		break;
	case CBattleScene::AttackPhase:
		Attack();		//���݂��̍U��
		break;
	}

	//�f�o�b�O����
	Debug();
}

void CBattleScene::Draw()
{
	//�N���X�̃C���X�^���X��ϐ��ɑ��
	//�e�L�X�g�`��N���X
	WriteText* Text = WriteText::GetInstance();

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

	//----�ŗL�U���Q�[�W�̕`��----
	//����
	ChangeUniqueGage(m_pUniqueGages,m_pHero->GetUniqueGage(), UNIQUEGAGE_POS,80.0f,m_UniqueGageCnt);
	DrawUniqueGage(m_pUniqueGages);
	//�G
	ChangeUniqueGage(m_pEnemyUniqueGages,m_pEnemyHero->GetUniqueGage(), ENEMY_UNIQUEGAGE_POS, -80.0f,m_EnemyUniqueGageCnt);
	DrawUniqueGage(m_pEnemyUniqueGages);

	CSceneManager::GetInstance()->GetDx11()->SetDepth(false);
	//�eHp�Q�[�W�̕`��
	DrawHpGage();
	CSceneManager::GetInstance()->GetDx11()->SetDepth(true);

}

void CBattleScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("�p�����[�^"));
	ImGui::Text(JAPANESE("�v���C���["));
	ImGui::Text(JAPANESE("�ؗ�:%f"), m_pHero->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("����:%f"), m_pHero->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), m_pHero->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), m_pHero->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("�G"));
	ImGui::Text(JAPANESE("�ؗ�:%f"), m_pEnemyHero->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("����:%f"), m_pEnemyHero->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), m_pEnemyHero->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), m_pEnemyHero->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("HP%f"), m_pHero->GetHp());
	ImGui::Text(JAPANESE("�GHP%f"), m_pEnemyHero->GetHp());
	ImGui::End();
#endif
#if DEBUG
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
	std::string BattleParamFilePath = "Data\\Hero\\BattleData\\BattleParam";//�o�g���Ɏg�p����p�����[�^
	std::string EnemyParamFilePath = "Data\\Hero\\BattleData\\EnemyParam";  //�G�̃p�����[�^

	//�o�g���Ɏg�p����f�[�^�̃t�@�C����ǂݍ���
	if (!m_pJson->Load(m_BattleData, BattleParamFilePath)) { return; }

	//�G�̃p�����[�^���ۑ�����Ă���t�@�C���̓ǂݍ���
	if (!m_pJson->Load(m_EnemyHeroData, EnemyParamFilePath)) { return; }
}

//���ꂼ��̗̑̓Q�[�W�̕`��
void CBattleScene::DrawHpGage()
{
	//----UI�I�u�W�F�N�g�̕`��----
    //������Hp�Q�[�W
	HpGageAnim(m_pHpGage,m_pHero->GetHp(), m_pHero->GetBattleParamData().Hp * 10.0f, m_HpWidth);
	m_pHpGageBack->Draw();
	m_pHpGage->Draw();
	m_pHpGageFrame->Draw();
	//�G��Hp�Q�[�W
	HpGageAnim(m_pEnemyHpGage, m_pEnemyHero->GetHp(), m_pEnemyHero->GetBattleParamData().Hp * 10.0f, m_EnemyHpWidth);
	m_pEnemyHpGageBack->Draw();
	m_pEnemyHpGage->Draw();
	m_pEnemyHpGageFrame->Draw();
}

//�̗̓Q�[�W�̊e�평���ݒ�
void CBattleScene::InitHpGage()
{
	//----�ݒ�----
	//Hp�Q�[�W
	m_pHpGage->SetPosition(HPGAGE_POS);
	m_pHpGage->SetScale(HPGAGE_SCALE);
	m_pHpGage->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//Hp�Q�[�W�w�i
	m_pHpGageBack->SetPosition(HPGAGE_POS);
	m_pHpGageBack->SetScale(HPGAGE_SCALE);
	m_pHpGageBack->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//Hp�Q�[�W�g
	m_pHpGageFrame->SetPosition(HPFRAME_POS);
	m_pHpGageFrame->SetScale(HPGAGE_SCALE);
	m_pHpGageFrame->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//�G��Hp�Q�[�W
	m_pEnemyHpGage->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGage->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGage->SetDisplay(1.0f, 1.0f);
	//�G��Hp�Q�[�W�w�i
	m_pEnemyHpGageBack->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGageBack->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageBack->SetDisplay(1.0f, 1.0f);
	//�G��Hp�Q�[�W�g
	m_pEnemyHpGageFrame->SetPosition(ENEMY_HPFRAME_POS);
	m_pEnemyHpGageFrame->SetScale(0.8f, 0.8f, 0.8f);
	m_pEnemyHpGageFrame->SetDisplay(1.0f, 1.0f);
}

//�̗̓Q�[�W�̃A�j���[�V����
void CBattleScene::HpGageAnim(std::unique_ptr<CUIObject>& gage, float hp, float maxhp, float& width)
{
	//�Q�[�W���̊m�F
	float GageScale = 1.0f * hp / maxhp;

	// �������X�ɖڕW�l�ɋ߂Â���
	if (std::fabs(GageScale - width) < 0.01f) {
		// �ڕW�l�Ə\���߂��ꍇ�A���ڃX�i�b�v
		width = GageScale;
	}
	else {
		// �ɂ₩�ɖڕW�l�ɋ߂Â���
		width += (GageScale - width) * 0.1f;
	}

	//�Q�[�W����ݒ�
	gage->SetDisplay(width, 1.0f);
}

//�ŗL�U���Q�[�W�̕`�搔�ϓ�
void CBattleScene::ChangeUniqueGage(std::vector<std::unique_ptr<CUIObject>>& gages, int count, D3DXVECTOR2 pos, float interval, int& current)
{
	if (count == current) return;

	//�Â��Q�[�W������
	gages.clear();

	for (int i = 0; i < count; i++)
	{
		auto gage = std::make_unique<CUIObject>();
		gage->AttachSprite(CUIManager::GetSprite(CUIManager::UniqueGage));
		float xoffset = pos.x + (i * interval);
		gage->SetPosition(xoffset, pos.y, 0.0f);
		gage->SetScale(0.8f, 0.8f, 0.8f);
		gage->SetDisplay(1.0f, 1.0f);
		gages.push_back(std::move(gage));
	}

	//���݂̕\�������X�V
	current = count;
}

//�ŗL�U���Q�[�W�̕`��
void CBattleScene::DrawUniqueGage(std::vector<std::unique_ptr<CUIObject>>& gages)
{
	//�ŗL�U���Q�[�W
	for (const auto& gage : gages)
	{
		if (gage)
		{
			gage->Draw();
		}
	}
}

//�s���I���t�F�[�Y���̏���
void CBattleScene::MoveSelect()
{
	//----�N���X�̃C���X�^���X��ϐ��ɑ��----
	//�L�[�}�l�[�W���[
	CKeyManager* KeyMng = CKeyManager::GetInstance();
	KeyMng->Update();

	m_pHero->MoveSelectAnim();
	m_pEnemyHero->MoveSelectAnim();

	//�J�[�\���̈ړ�
	if (KeyMng->IsDown(VK_RIGHT))
		{
			//�L�[���͂őI����i�߂�
			if (m_SelectNo < enAttackList::Max - 1) { m_SelectNo++; }
			else { m_SelectNo = 0; }
		}
		else if (KeyMng->IsDown(VK_LEFT))
		{
			if (m_SelectNo > 0) { m_SelectNo--; }
			else { m_SelectNo = enAttackList::Max - 1; }
		}

		if (KeyMng->IsDown(VK_RETURN))
		{
			switch (m_SelectNo)
			{
			case 0: m_Attack = enAttackList::PowerAttack; break;
			case 1: m_Attack = enAttackList::MagicAttack; break;
			case 2: m_Attack = enAttackList::UniqueAttack; break;
			}
			
			//�U���t�F�[�Y�֑J��
			m_BattlePhase = enBattlePhase::AttackPhase;
		}
}

void CBattleScene::Attack()
{
	//���x�ɂ��s�����̔��f
	SetUpToNextTurn();

	if (m_IsHeroTurn)
	{
		HeroTurn();
		if (m_pEnemyHero->GetHp() > 0.0f) {
			EnemyHeroTurn();
		}
	}
	else
	{
		EnemyHeroTurn();
		if (m_pHero->GetHp() > 0.0f) {
			HeroTurn();
		}
	}

	//�����t�F�[�Y�ֈړ�
	m_BattlePhase = enBattlePhase::MoveSelectPhase;
}

//���̃^�[���̏������̏���
void CBattleScene::SetUpToNextTurn()
{
	//�����ƓG�̃X�s�[�h���r
	if (m_pHero->GetBattleParamData().Speed > m_pEnemyHero->GetBattleParamData().Speed)
	{
		//�����̃X�s�[�h��������Ύ����̃^�[��
		m_IsHeroTurn = true;
	}
	else
	{
		//�Ⴏ��ΓG�̃^�[��
		m_IsHeroTurn = false;
	}
}

//�����̃^�[���ɍs������
void CBattleScene::HeroTurn()
{
	m_pCamera->SetPos(ATTACK_CAMPOS);
	m_pCamera->SetLook(ATTACK_CAMLOOK);

	switch (m_Attack)
	{
	case CBattleScene::PowerAttack: m_pEnemyHero->Damage(m_pHero->PowerAttack()); break;
	case CBattleScene::MagicAttack: m_pEnemyHero->Damage(m_pHero->MagicAttack()); break;
	case CBattleScene::UniqueAttack: m_pEnemyHero->Damage(m_pHero->UniqueAttack());break;
	}
}

//�G�̃^�[���ɍs������
void CBattleScene::EnemyHeroTurn()
{
	m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
	m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);

	m_pHero->Damage(m_pEnemyHero->PowerAttack());
}
