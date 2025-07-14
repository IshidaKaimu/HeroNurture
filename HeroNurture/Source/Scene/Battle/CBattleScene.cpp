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
	: m_pCamera				(&CCameraManager::GetInstance())
	, m_pGround				()
	, m_pHpGauge			()
	, m_pHpGaugeBack		()
	, m_pHpGaugeFrame		()
	, m_pHpDecrease			()
	, m_pEnemyHpGauge		()
	, m_pEnemyHpGaugeBack	()
	, m_pEnemyHpGaugeFrame	()
	, m_pPowerAttack		()
	, m_pMagicAttack		()
	, m_pAttackCover		()
	, m_pJson				()
	, m_BattleData			()
	, m_EnemyHeroData		()
	, m_HpWidth				(1.0f)
	, m_HpDecreaseWidth		(1.0f)
	, m_EnemyHpWidth		(1.0f)
	, m_EnemyHpDecreaseWidth(1.0f)
	, m_BattleTurn			()
	, m_MoveSelectCut		()
	, m_IsHeroTurn			()
	, m_CurrentTurn			()
	, m_SelectAttack		()
	, m_Attack				()
	, m_EnemyAttack			()
	, m_EnemyAttackNo		()
	, m_BattlePhase			()
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
		//�I�����ꂽ�q�[���[�̐ݒ�
		HeroMng->CreateHero(CHeroManager::Yui);

		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (HeroMng->GetBattleHeroName() == "Kaito")
	{
		//�I�����ꂽ�q�[���[�̐ݒ�
		HeroMng->CreateHero(CHeroManager::Kaito);

		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		EnemyHeroMng->CreateEnemyHero(CHeroManager::Yui);
	}

	//----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
	
	//�n��
	m_pGround = std::make_unique<CGround>();

	//----------------------------------------
	
	//----UI�I�u�W�F�N�g----
	
	//Hp�Q�[�W
	m_pHpGauge		= std::make_unique<CUIObject>(); //�Q�[�W
	m_pHpGaugeBack	= std::make_unique<CUIObject>(); //�g
	m_pHpGaugeFrame	= std::make_unique<CUIObject>(); //�w�i
	m_pHpDecrease	= std::make_unique<CUIObject>(); //�������Ɍ�����摜
	
	//�G��Hp�Q�[�W
	m_pEnemyHpGauge      = std::make_unique<CUIObject>(); //�Q�[�W
	m_pEnemyHpGaugeBack  = std::make_unique<CUIObject>(); //�g
	m_pEnemyHpGaugeFrame = std::make_unique<CUIObject>(); //�w�i
	m_pEnemyHpDecrease	= std::make_unique<CUIObject>(); //�������Ɍ�����摜
	
	//�U���A�C�R��
	m_pPowerAttack = std::make_unique<CUIObject>(); //�ؗ�
	m_pMagicAttack = std::make_unique<CUIObject>(); //����
	m_pAttackCover = std::make_unique<CUIObject>(); //�킹��摜
	
	//---------------------
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
	m_pHpGauge->AttachSprite(CUIManager::GetSprite(CUIManager::HpGauge));			//�Q�[�W
	m_pHpGaugeBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGaugeBack));	//�g
	m_pHpGaugeFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GaugeFrame));	//�w�i
	m_pHpDecrease->AttachSprite(CUIManager::GetSprite(CUIManager::GaugeDecrease));  //�������Ɍ�����摜
	
	//�G��Hp�Q�[�W
	m_pEnemyHpGauge->AttachSprite(CUIManager::GetSprite(CUIManager::EnemyHpGauge));	   //�Q�[�W
	m_pEnemyHpGaugeBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpGaugeBack)); //�g
	m_pEnemyHpGaugeFrame->AttachSprite(CUIManager::GetSprite(CUIManager::GaugeFrame)); //�w�i
	m_pEnemyHpDecrease->AttachSprite(CUIManager::GetSprite(CUIManager::GaugeDecrease));//�������Ɍ�����摜

	//�U���A�C�R��
	m_pPowerAttack->AttachSprite(CUIManager::GetSprite(CUIManager::PowerAttack)); //�ؗ�
	m_pMagicAttack->AttachSprite(CUIManager::GetSprite(CUIManager::MagicAttack)); //����
	m_pAttackCover->AttachSprite(CUIManager::GetSprite(CUIManager::AttackCover)); //�킹��摜

	//--------------------------------------

}

void CBattleScene::Initialize()
{
	CHeroManager*	   HeroMng		= &CHeroManager::GetInstance();
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
	InitHpGauge();

	//�s���I�����J�������ړ�������l�̏�����
	m_MoveCamPos  = INIT_MOVE_CAMPOS;
	m_MoveCamLook = INIT_MOVE_CAMLOOK;

}

void CBattleScene::Update()
{
	CSceneManager*       SceneMng     = &CSceneManager::GetInstance();
	CHeroManager*        HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager*   EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//�o�g���q�[���[�I��BGM���~
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_BattleHeroSelect);

	//�o�g��BGM�̍Đ�
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Battle);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Battle, BGM_VOLUME);

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
	DrawHpGauge();

	//�q�[���[�̖��O�̍��W
	D3DXVECTOR2 HeroNamePos;	  //����
	D3DXVECTOR2 EnemyHeroNamePos; //�G


	//�I�������q�[���[�ƓG�̃q�[���[�̖��O�̍��W�̐ݒ�
	if (HeroMng->GetSelectHeroName() == "Yui")
	{
		
		HeroNamePos      = YUI_TEXT_POS;
		EnemyHeroNamePos = ENEMY_KAITO_TEXT_POS;
	}
	else
	{
		HeroNamePos      = KAITO_TEXT_POS;
		EnemyHeroNamePos = ENEMY_YUI_TEXT_POS;
	}

	//�����A�G���ꂼ��̃q�[���[��
	Text->Draw_Text(Utility->StringToWstring(HeroMng->GetSelectHeroName()), WriteText::Hero, HeroNamePos);			     //����
	Text->Draw_Text(Utility->StringToWstring(EnemyHeroMng->GetEnemyHeroName()), WriteText::EnemyHero, EnemyHeroNamePos); //�G

	//�����A�G���ꂼ��̃^�[���̕`�揈��
	if (m_SelectAttack)
	{
		//�G�̃^�[���łȂ����
		if (!m_CurrentTurn) 
		{ 
			DrawHeroTurn();
		}
		else 
		{
			DrawEnemyHeroTurn(); 
		}
	}

	//�U���A�C�R���̕`��
	DrawAttack(m_pPowerAttack, POWER_ATTACK_POS, ATTACK_ALPHA); //�͍ؗU��
	DrawAttack(m_pMagicAttack, MAGIC_ATTACK_POS, ATTACK_ALPHA); //���͍U��
	
	//�I���ɂ���Ĉʒu��ς��邽�߂̕ϐ�
	D3DXVECTOR3 CoverPos;
	if (m_SelectNo == 0)
	{ 
		CoverPos = MAGIC_ATTACK_POS; 
	}else
	{ 
		CoverPos = POWER_ATTACK_POS;
	}

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
void CBattleScene::DrawHpGauge()
{
	CHeroManager*      HeroMng      = &CHeroManager::GetInstance();
	CEnemyHeroManager* EnemyHeroMng = &CEnemyHeroManager::GetInstance();

	//----UI�I�u�W�F�N�g�̕`��----
    
	//������Hp�Q�[�W
	m_pHpGaugeBack->Draw();	 //�w�i
	m_pHpDecrease->Draw();	 //�������Ɍ�����摜
	m_pHpGauge->Draw();		 //�Q�[�W
	m_pHpGaugeFrame->Draw(); //�g

	HpGaugeAnim(m_pHpGauge,	   HeroMng->GetHp(), HeroMng->GetBattleParamData().Hp * 10.0f, 0.1f,  m_HpWidth);		     //�Q�[�W�{�̂̃A�j���[�V����
	HpDecreaseAnim(m_pHpDecrease, HeroMng->GetHp(), HeroMng->GetBattleParamData().Hp * 10.0f, 0.1f,  m_HpDecreaseWidth); //�������Ɍ�����摜�̃A�j���[�V����

	//�G��Hp�Q�[�W
	m_pEnemyHpGaugeBack->Draw();   //�w�i
	m_pEnemyHpDecrease->Draw();    //�������Ɍ�����摜
	m_pEnemyHpGauge->Draw();	   //�Q�[�W
	m_pEnemyHpGaugeFrame->Draw();  //�g
	HpGaugeAnim(m_pEnemyHpGauge,	EnemyHeroMng->GetHp(), EnemyHeroMng->GetBattleParamData().Hp * 10.0f, 0.1f,  m_EnemyHpWidth);		     //�Q�[�W�{�̂̃A�j���[�V����
	HpDecreaseAnim(m_pEnemyHpDecrease, EnemyHeroMng->GetHp(), EnemyHeroMng->GetBattleParamData().Hp * 10.0f, 0.1f,  m_EnemyHpDecreaseWidth); //�������Ɍ�����摜�̃A�j���[�V����

	//----------------------------
}

//�̗̓Q�[�W�̊e�평���ݒ�
void CBattleScene::InitHpGauge()
{
	//----�ݒ�----
	
	//Hp�Q�[�W
	m_pHpGauge->SetPosition(HPGAUGE_POS);
	m_pHpGauge->SetScale(HPGAUGE_SCALE);
	m_pHpGauge->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//Hp�Q�[�W�w�i
	m_pHpGaugeBack->SetPosition(HPGAUGE_POS);
	m_pHpGaugeBack->SetScale(HPGAUGE_SCALE);
	m_pHpGaugeBack->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//Hp�������̉摜
	m_pHpDecrease->SetPosition(HPGAUGE_POS);
	m_pHpDecrease->SetScale(HPGAUGE_SCALE);
	m_pHpDecrease->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);

	//Hp�Q�[�W�g
	m_pHpGaugeFrame->SetPosition(HPFRAME_POS);
	m_pHpGaugeFrame->SetScale(HPGAUGE_SCALE);
	m_pHpGaugeFrame->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//�G��Hp�Q�[�W
	m_pEnemyHpGauge->SetPosition(ENEMY_HPGAUGE_POS);
	m_pEnemyHpGauge->SetScale(HPGAUGE_SCALE);
	m_pEnemyHpGauge->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//�G��Hp�Q�[�W�w�i
	m_pEnemyHpGaugeBack->SetPosition(ENEMY_HPGAUGE_POS);
	m_pEnemyHpGaugeBack->SetScale(HPGAUGE_SCALE);
	m_pEnemyHpGaugeBack->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//�G��Hp�������̉摜
	m_pEnemyHpDecrease->SetPosition(ENEMY_HPGAUGE_POS);
	m_pEnemyHpDecrease->SetScale(HPGAUGE_SCALE);
	m_pEnemyHpDecrease->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);

	//�G��Hp�Q�[�W�g
	m_pEnemyHpGaugeFrame->SetPosition(ENEMY_HPFRAME_POS);
	m_pEnemyHpGaugeFrame->SetScale(HPGAUGE_SCALE);
	m_pEnemyHpGaugeFrame->SetDisplay(HPGAUGE_DISPLAY.x, HPGAUGE_DISPLAY.y);
	
	//------------
}

//�̗̓Q�[�W�̃A�j���[�V����
void CBattleScene::HpGaugeAnim(std::unique_ptr<CUIObject>& gauge, float hp, float maxhp, float speed, float& width)
{
	//�Q�[�W���̊m�F
	float GaugeScale = 1.0f * hp / maxhp;

	// �������X�ɖڕW�l�ɋ߂Â���
	if (std::fabs(GaugeScale - width) < 0.01f) {
		// �ڕW�l�Ə\���߂��ꍇ�A���ڃX�i�b�v
		width = GaugeScale;

		m_HpGageAnim = false;
	}
	else {
		// �ɂ₩�ɖڕW�l�ɋ߂Â���
		width += (GaugeScale - width) * speed;

		m_HpGageAnim = true;
	}

	//�Q�[�W����ݒ�
	gauge->SetDisplay(width, 1.0f);
}

void CBattleScene::HpDecreaseAnim(std::unique_ptr<CUIObject>& gauge, float hp, float maxhp, float speed, float& width)
{
	if (!m_CurrentTurn && m_HpGageAnim)
	{
		m_EnemyHpDecreaseAnimStartCount = 0;

		m_HpDecreaseAnimStartCount++;
		
		if (m_HpDecreaseAnimStartCount >= HP_DECREASE_ANIM_START)
		{
			HpGaugeAnim(gauge, hp, maxhp, speed, width);
		}
	}
	else 
	{
		if (!m_HpGageAnim) 
		{
			m_HpDecreaseAnimStartCount = 0;

			m_EnemyHpDecreaseAnimStartCount++;

			if (m_EnemyHpDecreaseAnimStartCount >= HP_DECREASE_ANIM_START)
			{
				HpGaugeAnim(gauge, hp, maxhp, speed, width);
			}
		}
	}
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
	if (KeyMng->IsDown('D'))
		{
		    //�I��SE�̍Đ�
		    CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
		    CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, SE_VOLUME);

			//�L�[���͂őI����i�߂�
			if (m_SelectNo < enAttackList::Max - 1) { m_SelectNo++; }
			else { m_SelectNo = 0; }
		}
		else if (KeyMng->IsDown('A'))
		{
			//�I��SE�̍Đ�
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, SE_VOLUME);

			if (m_SelectNo > 0) { m_SelectNo--; }
			else { m_SelectNo = enAttackList::Max - 1; }
		}

	if (KeyMng->IsDown(VK_RETURN))
		{
			//����SE�̍Đ�
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, SE_VOLUME);

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
		if (!EnemyHeroMng->GetDamageAnimEndFlag()) 
		{
			HeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0f && HeroMng->GetAttackAnimEndFlag()) 
			{		
				//�G�ւ̃_���[�W����
				if (!EnemyHeroMng->GetDamageFlag()) 
				{
					switch (m_Attack)
					{
					case CBattleScene::PowerAttack:
						//�͍ؗU���̃_���[�W
						EnemyHeroMng->Damage(HeroMng->PowerAttack());
						break;
					case CBattleScene::MagicAttack:
						//���͍U���̃_���[�W
						EnemyHeroMng->Damage(HeroMng->MagicAttack());
						break;
					}
				}
			}
		}
		else
		{
		  if (!EnemyHeroMng->Death()) 
		  {
			  EnemyHeroTurn();
			 //�����ւ̃_���[�W����
			 if (HeroMng->GetHp() > 0.0f && EnemyHeroMng->GetAttackAnimEndFlag())
			 {
				 if (!HeroMng->GetDamageFlag())
				 {
					 //�G�̍U���̎�ނɂ���ă_���[�W��^����
					 switch (m_EnemyAttack)
					 {
					 case CBattleScene::PowerAttack:
						 //�͍ؗU���̃_���[�W
						 HeroMng->Damage(EnemyHeroMng->PowerAttack());
						 break;
					 case CBattleScene::MagicAttack:
						 //���͍U���̃_���[�W
						 HeroMng->Damage(EnemyHeroMng->MagicAttack());
						 break;
					}
				}
			}
		  }
		}
	}
	else
	{
		//�G����s�̏ꍇ
		if (!HeroMng->GetDamageAnimEndFlag())
		{
			EnemyHeroTurn();
			if (EnemyHeroMng->GetHp() > 0.0f && EnemyHeroMng->GetAttackAnimEndFlag()) {
				//�����ւ̃_���[�W����
				if (!HeroMng->GetDamageFlag())
				{
					switch (m_EnemyAttack)
					{
					case CBattleScene::PowerAttack:
						//�͍ؗU���̃_���[�W
						HeroMng->Damage(EnemyHeroMng->PowerAttack());
						break;
					case CBattleScene::MagicAttack:
						//���͍U���̃_���[�W
						HeroMng->Damage(EnemyHeroMng->MagicAttack());
						break;
					}
				}
			}
		}
		else 
		{
			if (!HeroMng->Death()) 
			{
				HeroTurn();
				if (HeroMng->GetHp() > 0.0f && HeroMng->GetAttackAnimEndFlag()) {
					//�G�ւ̃_���[�W����
					if (!EnemyHeroMng->GetDamageFlag())
					{
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
		}
	}

	//�����t�F�[�Y�ֈړ�

	CBattleManager* BattleMng = &CBattleManager::GetInstance();

	if (!HeroMng->Death() && !EnemyHeroMng->Death())
	{
		if (HeroMng->GetDamageAnimEndFlag() && EnemyHeroMng->GetDamageAnimEndFlag())
		{

			//�����A�G�̏�����
			HeroMng->BattleInitialize();
			EnemyHeroMng->Initialize();


			//�s���𖢑I���Ƃ���
			m_SelectAttack = false;

			//�����A�G�̃A�j���[�V�����I���t���O������

			//�U���A�j���[�V����
			HeroMng->SetAttackAnimEndFlag(false);		//����
			EnemyHeroMng->SetAttackAnimEndFlag(false);  //�G

			//�_���[�W�A�j���[�V����
			HeroMng->SetDamageAnimEndFlag(false);		//����
			EnemyHeroMng->SetDamageAnimEndFlag(false);  //�G

			//�s���I�𒆂̃J�������o�����߂���ɂ���
			m_MoveSelectCut = 0;

			//�o�g���̃t�F�[�Y���s���I���ɖ߂�
			m_BattlePhase = enBattlePhase::MoveSelectPhase;
		}
	}

	//���S������
	//����
	if (HeroMng->Death())
	{
		//���s�̐ݒ�
		BattleMng->SetBattleResult(BattleMng->Lose);

		if (HeroMng->GetDamageAnimEndFlag())
		{
			m_SceneTransitionFlg = true;
		}
	}

	//�G
	if (EnemyHeroMng->Death())
	{
		//���s�̐ݒ�
		BattleMng->SetBattleResult(BattleMng->Win);

		if (EnemyHeroMng->GetDamageAnimEndFlag())
		{
			m_SceneTransitionFlg = true;
		}
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
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_SECOND_X, m_MoveCamPos.y, HeroMng->GetPosition().z - SHIFT_CAMPOS_SECOND_Z);
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
				m_MoveCamPos.y  = INIT_MOVE_CAMPOS.y;
				m_MoveCamLook.y = INIT_MOVE_CAMLOOK.y;
				//���̃J�b�g��
				m_MoveSelectCut = 3;
			}
		}
		break;
	case 3:
		m_pCamera->SetPos(HeroMng->GetPosition().x + SHIFT_CAMPOS_THIRD_X, m_MoveCamPos.y, HeroMng->GetPosition().z + SHIFT_CAMPOS_THIRD_Z);
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

			if (!EnemyHeroMng->GetDamageAnimEndFlag())
			{
				EnemyHeroMng->DamageAnim(ANIM_VECTOR_VALUE);//�G�̃_���[�W�A�j���[�V����
			}
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
			
			if (!EnemyHeroMng->GetDamageAnimEndFlag())
			{
				EnemyHeroMng->DamageAnim(ANIM_VECTOR_VALUE);//�G�̃_���[�W�A�j���[�V����
			}
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

			if (!HeroMng->GetDamageAnimEndFlag())
			{
				HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //�����̃_���[�W�A�j���[�V����
			}
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
		
		if (EnemyHeroMng->GetAttackAnimEndFlag())	 //�U���A�j���[�V�������I�������
		{
			m_pCamera->SetPos(ATTACK_CAMPOS);
			m_pCamera->SetLook(ATTACK_CAMLOOK);

			if (!HeroMng->GetDamageAnimEndFlag())
			{
				HeroMng->DamageAnim(-ANIM_VECTOR_VALUE); //�����̃_���[�W�A�j���[�V����
			}
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
