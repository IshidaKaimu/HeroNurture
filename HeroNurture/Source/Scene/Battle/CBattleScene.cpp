#pragma once
#include "CBattleScene.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Battle\CBattleManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "KeyManager\CKeyManager.h"
#include "Effect\CEffect.h"
#include "Sound\CSoundManager.h"

//�萔�̖��O���
using namespace Constant_BattleScene;

CBattleScene::CBattleScene()
	: m_pCamera			  (&CCameraManager::GetInstance())
	, m_pGround			  ()
	, m_pHpGage			  ()
	, m_pHpGageBack       ()
	, m_pHpGageFrame      ()
	, m_pEnemyHpGage      ()
	, m_pEnemyHpGageBack  ()
	, m_pEnemyHpGageFrame ()
	, m_pPowerAttack	  ()
	, m_pMagicAttack	  ()
	, m_pAttackCover	  ()
	, m_pJson			  ()
	, m_BattleData		  ()
	, m_EnemyHeroData     ()
	, m_HpWidth			  (1.0f)
	, m_EnemyHpWidth      (1.0f)
	, m_BattleTurn        ()
	, m_MoveSelectCut	  ()
	, m_IsHeroTurn        ()
	, m_CurrentTurn		  ()
	, m_SelectAttack      ()
	, m_Attack            ()
	, m_EnemyAttack		  ()
	, m_EnemyAttackNo     ()
	, m_BattlePhase		  ()
{
}

CBattleScene::~CBattleScene()
{
}

void CBattleScene::Create()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�I�����ꂽ�q�[���[�̃C���X�^���X����
	if (HeroMng->GetBattleHeroName() == "Yui")
	{
		HeroMng->CreateHero(CHeroManager::Yui);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (HeroMng->GetBattleHeroName() == "Kaito")
	{
		HeroMng->CreateHero(CHeroManager::Kaito);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Yui);
	}

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
	//�n��
	m_pGround = std::make_unique<CGround>();
	//----UI�I�u�W�F�N�g----
	//Hp�Q�[�W
	m_pHpGage      = std::make_unique<CUIObject>();
	m_pHpGageBack  = std::make_unique<CUIObject>();
	m_pHpGageFrame = std::make_unique<CUIObject>();
	//�G��Hp�Q�[�W
	m_pEnemyHpGage      = std::make_unique<CUIObject>();
	m_pEnemyHpGageBack  = std::make_unique<CUIObject>();
	m_pEnemyHpGageFrame = std::make_unique<CUIObject>();
	//�U���A�C�R��
	m_pPowerAttack = std::make_unique<CUIObject>(); //�ؗ�
	m_pMagicAttack = std::make_unique<CUIObject>(); //����
	m_pAttackCover = std::make_unique<CUIObject>(); //�킹��摜
}

void CBattleScene::Releace()
{
}

void CBattleScene::LoadData()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�I������Ă���q�[���[�̃��b�V���f�[�^�ݒ�
	HeroMng->LoadMeshData();
	//�G�̃q�[���[�̃��b�V���f�[�^�ݒ�
	EnemyHeroMng->LoadMeshData();

	//�t�@�C������o�g���Ɏg�p����f�[�^��ǂݍ���
	LoadBattleData();
	//�o�g���Ɏg�p����f�[�^���q�[���[�ɓn��
	HeroMng->SetBattleParamData(m_BattleData);
	//�G�̃p�����[�^��G�̃q�[���[�ɓn��
	for (const auto& enemy : m_EnemyHeroData)
	{
		//�G�ɂȂ��Ă���q�[���[�̂��̂̂ݓn��
		if (EnemyHeroMng->GetEnemyHeroName() == enemy["HeroName"].get<std::string>())
		{
			EnemyHeroMng->SetBattleParamData(enemy);
		}
	}

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g�̃��b�V���f�[�^�ݒ�----
	//�n��
	m_pGround->LoadData();

	//----UI�I�u�W�F�N�g�̃X�v���C�g�ݒ�----
	//Hp�Q�[�W
	m_pHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::HpGage));
	m_pHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//�G��Hp�Q�[�W
	m_pEnemyHpGage->AttachSprite(CUIManager::GetSprite(CUIManager::EnemyHpGage));
	m_pEnemyHpGageBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGageBack));
	m_pEnemyHpGageFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GageFrame));
	//�U���A�C�R��
	m_pPowerAttack->AttachSprite(CUIManager::GetSprite(CUIManager::PowerAttack)); //�ؗ�
	m_pMagicAttack->AttachSprite(CUIManager::GetSprite(CUIManager::MagicAttack)); //����
	m_pAttackCover->AttachSprite(CUIManager::GetSprite(CUIManager::AttackCover)); //�킹��摜

}

void CBattleScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


	//�I�������q�[���[�̏�����
	HeroMng->BattleInitialize();
	//�G�̃q�[���[�̏�����
	EnemyHeroMng->Initialize();
	//�J�������̏�����
	m_pCamera->SetPos(INIT_CAMPOS);
	m_pCamera->SetLook(INIT_CAMLOOK);

	//�s�����I���ς݂ł��邩�̃t���O�̏�����
	m_SelectAttack = false;
	
	//�̗͂̏�����
	HeroMng->SetHp(HeroMng->GetBattleParamData().Hp * 10.0f);
	EnemyHeroMng->SetHp(EnemyHeroMng->GetBattleParamData().Hp * 10.0f);

	//Hp�Q�[�W�̕\�����ȊO�̐ݒ�
	InitHpGage();

	//�s���I�����J�������ړ�������l�̏�����
	m_MoveCamPos  = INIT_MOVE_CAMPOS;
	m_MoveCamLook = INIT_MOVE_CAMLOOK;

}

void CBattleScene::Update()
{
	CSceneManager*       SceneMng     = &CSceneManager::GetInstance();
	CBattleManager*      BattleMng    = &CBattleManager::GetInstance();
	CHeroManager*        HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager*   EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�o�g���q�[���[�I��BGM���~
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_BattleHeroSelect);

	//�o�g��BGM�̍Đ�
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Battle);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Battle, 40);

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
	case CBattleScene::Max:
		break;
	}

	//���S������
    //����
	if (HeroMng->Death())
	{
		//���s�̐ݒ�
		BattleMng->SetBattleResult(BattleMng->Lose);

		m_SceneTransitionFlg = true;
	}
	//�G
	if (EnemyHeroMng->Death())
	{
		//���s�̐ݒ�
		BattleMng->SetBattleResult(BattleMng->Win);

		m_SceneTransitionFlg = true;
	}

	//�t�F�[�h�A�E�g����
	if (m_SceneTransitionFlg && FadeOut())
	{
		SceneMng->LoadCreate(CSceneManager::BattleResult);
	}


	//�f�o�b�O����
	Debug();
}

void CBattleScene::Draw()
{
	WriteText*         Text         = WriteText::GetInstance();
	CSceneManager*     SceneMng     = &CSceneManager::GetInstance();
	CUtility*          Utility      = &CUtility::GetInstance();
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�J�����̓���
	CCameraManager::GetInstance().CameraUpdate();

	//�I�������q�[���[�̕`��
	HeroMng->Draw();
	//�G�̃q�[���[�̕`��
	EnemyHeroMng->Draw();

	//�n�ʂ̕`��
	m_pGround->Draw();
	//��̕`��
	DrawSky();

	SceneMng->GetDx11()->SetDepth(false);
	
	//�eHp�Q�[�W�̕`��
	DrawHpGage();

	std::string debug = HeroMng->GetBattleHeroName();

	//�����A�G���ꂼ��̃q�[���[��
	Text->Draw_Text(Utility->StringToWstring(HeroMng->GetBattleHeroName()), WriteText::Hero, HERO_TEXT_POS);			    //����
	Text->Draw_Text(Utility->StringToWstring(EnemyHeroMng->GetBattleHeroName()), WriteText::EnemyHero, ENEMYHERO_TEXT_POS); //�G

	//�����A�G���ꂼ��̃^�[���̕`�揈��
	if (m_SelectAttack)
	{
		//�G�̃^�[���łȂ����
		if (!m_CurrentTurn) { DrawHeroTurn(); }
		else { DrawEnemyHeroTurn(); }
	}

	//�U���A�C�R���̕`��
	DrawAttack(m_pPowerAttack, POWER_ATTACK_POS, ATTACK_ALPHA); //�͍ؗU��
	DrawAttack(m_pMagicAttack, MAGIC_ATTACK_POS, ATTACK_ALPHA); //���͍U��
	//�I���ɂ���Ĉʒu��ς��邽�߂̕ϐ�
	D3DXVECTOR3 CoverPos;
	if (m_SelectNo == 0) { CoverPos = MAGIC_ATTACK_POS; }

	else{ CoverPos = POWER_ATTACK_POS; }
	DrawAttack(m_pAttackCover, CoverPos, ATTACK_COVER_ALPHA);   //�A�C�R���ɂ��Ԃ���摜

	SceneMng->GetDx11()->SetDepth(true);
}

void CBattleScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("�p�����[�^"));
	ImGui::Text(JAPANESE("�v���C���["));
	ImGui::Text(JAPANESE("�ؗ�:%f"), HeroMng->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("����:%f"), HeroMng->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), HeroMng->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), HeroMng->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("�G"));
	ImGui::Text(JAPANESE("�ؗ�:%f"), EnemyHeroMng->GetBattleParamData().Power);
	ImGui::Text(JAPANESE("����:%f"), EnemyHeroMng->GetBattleParamData().Magic);
	ImGui::Text(JAPANESE("�f����:%f"), EnemyHeroMng->GetBattleParamData().Speed);
	ImGui::Text(JAPANESE("�̗�:%f"), EnemyHeroMng->GetBattleParamData().Hp);
	ImGui::Text(JAPANESE("HP%f"), HeroMng->GetHp());
	ImGui::Text(JAPANESE("�GHP%f"), EnemyHeroMng->GetHp());
	ImGui::End();

	ImGui::Begin(JAPANESE("�J����"));
	ImGui::Text(JAPANESE("�J���������_X:%f"), m_pCamera->GetLook().x);
	ImGui::End();

	ImGui::Begin(JAPANESE("�g���[�j���O�I����"));
	if (m_SelectNo == 0) { ImGui::Text(JAPANESE("����")); }
	if (m_SelectNo == 1) { ImGui::Text(JAPANESE("���@")); }
	if (m_SelectNo == 2) { ImGui::Text(JAPANESE("�ŗL")); }
	ImGui::End();

#endif
#if DEBUG
	CCameraManager::GetInstance().CameraUpdate();
	ImGui::Begin(JAPANESE("�J�����ʒu"));
	ImGui::InputFloat3(JAPANESE("���W:%f"), m_CamPos);
	ImGui::InputFloat3(JAPANESE("�����_:%f"), m_CamLook);
	CCameraManager::GetInstance().SetPos(ATTACK_CAMPOS);
	CCameraManager::GetInstance().SetLook(ATTACK_CAMLOOK);
	ImGui::End();
#endif
#if DEBUG
	HeroMng->Debug();
	EnemyHeroMng->Debug();
#endif


}

//�o�g���Ɏg�p����f�[�^�̓ǂݍ���
void CBattleScene::LoadBattleData()
{
	CSceneManager* SceneMng = &CSceneManager::GetInstance();

	//�ݒ肳��Ă��郆�[�U�[���̎擾
	std::string UserName = SceneMng->GetStringName();

	//�ǂݍ��ރt�@�C���̃p�X
	std::string BattleParamFilePath = "Data\\Acount\\"+ UserName +"\\BattleData\\BattleParam";   //�o�g���Ɏg�p����p�����[�^
	std::string EnemyParamFilePath  = "Data\\Acount\\" + UserName + "\\BattleData\\EnemyParam";  //�G�̃p�����[�^

	//�o�g���Ɏg�p����f�[�^�̃t�@�C����ǂݍ���
	if (!m_pJson->Load(m_BattleData, BattleParamFilePath)) { return; }

	//�G�̃p�����[�^���ۑ�����Ă���t�@�C���̓ǂݍ���
	if (!m_pJson->Load(m_EnemyHeroData, EnemyParamFilePath)) { return; }
}

//�U���A�C�R���̕`��
void CBattleScene::DrawAttack(std::unique_ptr<CUIObject>& icon, D3DXVECTOR3 pos, float alpha)
{
	icon->SetPosition(pos);
	icon->SetScale(ATTACK_SCALE);
	icon->SetDisplay(ATTACK_DISP.x,ATTACK_DISP.y);
	icon->SetAlpha(alpha);

	if (!m_SelectAttack) 
	{
		icon->Draw();
	}
}

//���ꂼ��̗̑̓Q�[�W�̕`��
void CBattleScene::DrawHpGage()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//----UI�I�u�W�F�N�g�̕`��----
    //������Hp�Q�[�W
	HpGageAnim(m_pHpGage, HeroMng->GetHp(), HeroMng->GetBattleParamData().Hp * 10.0f, m_HpWidth);
	m_pHpGageBack->Draw();
	m_pHpGage->Draw();
	m_pHpGageFrame->Draw();
	//�G��Hp�Q�[�W
	HpGageAnim(m_pEnemyHpGage, EnemyHeroMng->GetHp(), EnemyHeroMng->GetBattleParamData().Hp * 10.0f, m_EnemyHpWidth);
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
	m_pEnemyHpGage->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGage->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//�G��Hp�Q�[�W�w�i
	m_pEnemyHpGageBack->SetPosition(ENEMY_HPGAGE_POS);
	m_pEnemyHpGageBack->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGageBack->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
	//�G��Hp�Q�[�W�g
	m_pEnemyHpGageFrame->SetPosition(ENEMY_HPFRAME_POS);
	m_pEnemyHpGageFrame->SetScale(HPGAGE_SCALE);
	m_pEnemyHpGageFrame->SetDisplay(HPGAGE_DISPLAY.x, HPGAGE_DISPLAY.y);
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

//�s���I���t�F�[�Y���̏���
void CBattleScene::MoveSelect()
{
	CKeyManager*       KeyMng       = &CKeyManager::GetInstance();
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�L�[�}�l�[�W���[�̓���
	KeyMng->Update();

	//�s���I�𒆂̃A�j���[�V����
	HeroMng->MoveSelectAnim();		//����
	EnemyHeroMng->MoveSelectAnim(); //�G

	//�J�����̉��o
	MoveSelectCamera();

	//���x�ɂ��s�����̔��f
	SetUpToNextTurn();

	//�J�[�\���̈ړ�
	if (KeyMng->IsDown(VK_RIGHT))
		{
		    //�I��SE�̍Đ�
		    CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		    CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

			//�L�[���͂őI����i�߂�
			if (m_SelectNo < enAttackList::Max - 1) { m_SelectNo++; }
			else { m_SelectNo = 0; }
		}
		else if (KeyMng->IsDown(VK_LEFT))
		{
			//�I��SE�̍Đ�
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

			if (m_SelectNo > 0) { m_SelectNo--; }
			else { m_SelectNo = enAttackList::Max - 1; }
		}

		if (KeyMng->IsDown(VK_RETURN))
		{
			//����SE�̍Đ�
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

			//�����̍U���̐ݒ�
			SettingAttack(m_SelectNo, m_Attack);
			
			//�I���������t���O
			m_SelectAttack = true;

			//�G�̍U���̑I��
			m_EnemyAttackNo = CUtility::GenerateRandomValue(0, 1);

			//�G�̍U���̐ݒ�
			SettingAttack(m_EnemyAttackNo, m_EnemyAttack);

			//�U���t�F�[�Y�֑J��
			m_BattlePhase = enBattlePhase::AttackPhase;
		}
}

void CBattleScene::Attack()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	if (m_IsHeroTurn)
	{
		//��������s�̏ꍇ
		if (!EnemyHeroMng->GetDamageFlag()) 
		{
			HeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0 && HeroMng->GetAttackAnimEndFlag()) {
				//�G�ւ̃_���[�W����
				switch (m_Attack)
				{
				case CBattleScene::PowerAttack:
					EnemyHeroMng->Damage(HeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					EnemyHeroMng->Damage(HeroMng->MagicAttack());
					break;
				case CBattleScene::Max:
					break;
				}
			}
		}
		else if(!EnemyHeroMng->Death())
		{
			EnemyHeroTurn();
			if (HeroMng->GetHp() > 0.0f) {
				//�����ւ̃_���[�W����
				switch (m_EnemyAttack)
				{
				case CBattleScene::PowerAttack:
					HeroMng->Damage(EnemyHeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					HeroMng->Damage(EnemyHeroMng->MagicAttack());
					break;
				case CBattleScene::Max:
					break;
				}
			}
		}
	}
	else if(!HeroMng->Death())
	{
		//�G����s�̏ꍇ
		if (!HeroMng->GetDamageFlag())
		{
			EnemyHeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0f && EnemyHeroMng->GetAttackAnimEndFlag()) {
				//�����ւ̃_���[�W����
				switch (m_EnemyAttack)
				{
				case CBattleScene::PowerAttack:
					HeroMng->Damage(EnemyHeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					HeroMng->Damage(EnemyHeroMng->MagicAttack());
					break;
				}
			}
		}
		else
		{
			HeroTurn();
			if (HeroMng->GetHp() > 0.0f && HeroMng->GetAttackAnimEndFlag()) {
				//�G�ւ̃_���[�W����
				switch (m_Attack)
				{
				case CBattleScene::PowerAttack:
					EnemyHeroMng->Damage(HeroMng->PowerAttack());
					break;
				case CBattleScene::MagicAttack:
					EnemyHeroMng->Damage(HeroMng->MagicAttack());
					break;
				}
			}
		}
	}

	//�����t�F�[�Y�ֈړ�
	if (HeroMng->GetDamageAnimEndFlag() && EnemyHeroMng->GetDamageAnimEndFlag())
	{
		//�����A�G�̏�����
		HeroMng->BattleInitialize();
		EnemyHeroMng->Initialize();

		//�s���𖢑I���Ƃ���
		m_SelectAttack = false;

		//�����A�G�̃A�j���[�V�����I���t���O������
		HeroMng->SetAttackAnimEndFlag(false);
		EnemyHeroMng->SetAttackAnimEndFlag(false);

		//�s���I�𒆂̃J�������o�����߂���ɂ���
		m_MoveSelectCut = 0;

		//�o�g���̃t�F�[�Y���s���I���ɖ߂�
		m_BattlePhase = enBattlePhase::MoveSelectPhase;

	}
}

//���̃^�[���̏������̏���
void CBattleScene::SetUpToNextTurn()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�����ƓG�̃X�s�[�h���r
	if (HeroMng->GetBattleParamData().Speed > EnemyHeroMng->GetBattleParamData().Speed)
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

//�s���I�𒆂̃J�������[�N
void CBattleScene::MoveSelectCamera()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	switch (m_MoveSelectCut)
	{
	case 0:
		m_pCamera->SetPos(INIT_CAMPOS);
		m_pCamera->SetLook(INIT_CAMLOOK);

		m_AnimCnt++;

		if (m_AnimCnt >= CHANGE_CUT * 3)
		{
			m_MoveSelectCut = 1;
			m_AnimCnt = 0;
		}
		break;
	case 1:
		m_pCamera->SetPos(m_MoveCamPos.x, START_CAMPOS_FAST_Y, START_CAMPOS_FAST_Z);
		m_pCamera->SetLook(START_CAMLOOK_FAST);

		if (m_MoveCamPos.x <= MAX_MOVE_CAMPOS_FAST_X)
		{
			m_MoveCamPos.x  += CAM_MOVESPEED;
		}
		else
		{
			m_AnimCnt++;

			if (m_AnimCnt >= CHANGE_CUT)
			{
				//�J�����𓮂����l�̏�����
				m_MoveCamPos.x = INIT_MOVE_CAMPOS.x;
				//�J�E���g�̏�����
				m_AnimCnt = 0;
				//���̃J�b�g��
				m_MoveSelectCut = 2;
			}
		}
	    break;
	case 2:
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_SECOND_Y, m_MoveCamPos.y, HeroMng->GetPosition().z - SHIFT_CAMPOS_SECOND_Z);
		m_pCamera->SetLook(HeroMng->GetPosition().x, m_MoveCamLook.y, HeroMng->GetPosition().z);

		if (m_MoveCamPos.y <= MAX_MOVE_CAMPOS_SECOND_Y)
		{
			m_MoveCamPos.y  += CAM_MOVESPEED/2;
			m_MoveCamLook.y += CAM_MOVESPEED/2;
		}
		else
		{
			//���̃J�b�g�̑O�ɏ����~�߂�
			m_AnimCnt++;
			if (m_AnimCnt >= CHANGE_CUT)
			{
				//�J�E���g�̏�����
				m_AnimCnt = 0;
				//�J�����𓮂����l�̏�����
				m_MoveCamPos.y  = 0.0f;
				m_MoveCamLook.y = 0.0f;
				//���̃J�b�g��
				m_MoveSelectCut = 3;
			}
		}
		break;
	case 3:
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_THIRD_Y, m_MoveCamPos.y, HeroMng->GetPosition().z + SHIFT_CAMPOS_THIRD_Z);
		m_pCamera->SetLook(EnemyHeroMng->GetPosition().x, m_MoveCamLook.y, EnemyHeroMng->GetPosition().z);

		if (m_MoveCamPos.y <= MAX_MOVE_CAMPOS_THIRD_Y)
		{
			m_MoveCamPos.y  += CAM_MOVESPEED/2;
			m_MoveCamLook.y += CAM_MOVESPEED/2;
		}
		else
		{
			//���̃J�b�g�̑O�ɏ����~�߂�
			m_AnimCnt++;

			if (m_AnimCnt >= CHANGE_CUT)
			{
				//�J�E���g�̏�����
				m_AnimCnt = 0;
				//�J�����𓮂����l�̏�����
				m_MoveCamPos.y = 0.0f;
				m_MoveCamLook.y = 0.0f;
				//���̃J�b�g��
				m_MoveSelectCut = 4;
			}
		}
		break;
	case 4:
		m_pCamera->SetPos(INIT_CAMPOS.x, INIT_CAMPOS.y, m_MoveCamPos.z);
		m_pCamera->SetLook(INIT_CAMLOOK);

		//�J���������񂾂񉺂���
		if (m_MoveCamPos.z >= INIT_CAMPOS.z)
		{
			m_MoveCamPos.z -= CAM_MOVESPEED;
		}
		else
		{
			//�J�����𓮂����l�̏�����
			m_MoveCamPos.z = 0;
			m_MoveSelectCut = 0;
		}
		break;
	default:
		break;
	}
}

//�����̃^�[���ɍs������
void CBattleScene::HeroTurn()
{	
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();


	//���݂ǂ���̃^�[����
	m_CurrentTurn = false;

	//�����̍U��
	switch (m_Attack)
	{
	case CBattleScene::PowerAttack:
		//�U���A�j���[�V�������I����Ă��Ȃ����
		if (!HeroMng->GetAttackAnimEndFlag()) 
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
		}

		//�����͍̋ؗU���̃A�j���[�V����
		HeroMng->PowerAttackAnim(ANIM_VECTOR_VALUE);

		if (HeroMng->GetAttackAnimEndFlag()) //�U���A�j���[�V�������I�������
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
			EnemyHeroMng->DamageAnim(1.0f);//�G�̃_���[�W�A�j���[�V����
		}

		break;
	case CBattleScene::MagicAttack:  
		
		//�U���A�j���[�V�������I����Ă��Ȃ����
		if (!HeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
		}
		
		//�����̖��͍U���̃A�j���[�V����
		HeroMng->MagicAttackAnim(ANIM_VECTOR_VALUE);

		if (HeroMng->GetAttackAnimEndFlag()) //�U���A�j���[�V�������I�������
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
			EnemyHeroMng->DamageAnim(ANIM_VECTOR_VALUE); //�G�̃_���[�W�A�j���[�V����
		}
		break;
	}
}

//�����̃^�[������UI���`�揈��
void CBattleScene::DrawHeroTurn()
{
	WriteText* Text = WriteText::GetInstance();
	Text->Draw_Text(L"HERO TURN", WriteText::HeroTurnText,HERO_TURNTEXT_POS);
}

//�G�̃^�[���ɍs������
void CBattleScene::EnemyHeroTurn()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//���݂ǂ���̃^�[����
	m_CurrentTurn = true;

	//�G�̍U��
	switch (m_EnemyAttack)
	{
	case CBattleScene::PowerAttack:
		//�U���A�j���[�V�������I����Ă��Ȃ����
		if (!EnemyHeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
		}
		//�G�̍U���A�j���[�V����
		EnemyHeroMng->PowerAttackAnim(-ANIM_VECTOR_VALUE);
		if (EnemyHeroMng->GetAttackAnimEndFlag())	 //�U���A�j���[�V�������I�������
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
			HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //�G�̃_���[�W�A�j���[�V����
		}
		break;
	case CBattleScene::MagicAttack: 
		//�U���A�j���[�V�������I����Ă��Ȃ����
		if (!EnemyHeroMng->GetAttackAnimEndFlag())
		{
			m_pCamera->SetPos(ENEMY_ATTACK_CAMPOS);
			m_pCamera->SetLook(ENEMY_ATTACK_CAMLOOK);
		}
		//�G�̍U���A�j���[�V����
		EnemyHeroMng->MagicAttackAnim(-ANIM_VECTOR_VALUE);
		if (EnemyHeroMng->GetAttackAnimEndFlag()) //�U���A�j���[�V�������I�������
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);
			HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //�G�̃_���[�W�A�j���[�V����
		}
		break;
	}

}

//�G�̃^�[�����̕`�揈��
void CBattleScene::DrawEnemyHeroTurn()
{
	WriteText* Text = WriteText::GetInstance();

	Text->Draw_Text(L"ENEMYHERO TURN", WriteText::EnemyHeroTurnText, ENEMY_TURNTEXT_POS);
}

//�^�[�����Ƃ̍U���̐ݒ�
void CBattleScene::SettingAttack(int no, enAttackList& attacklist)
{
	switch (no)
	{
	case 0: attacklist = enAttackList::PowerAttack; break;
	case 1: attacklist = enAttackList::MagicAttack; break;
	}
}
