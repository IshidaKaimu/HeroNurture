#include "Scene\Appearance\Kaito\CKaitoAppearanceScene.h"
#include "Scene\CSceneManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Sound\CSoundManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "SkinMeshObject\Hero\Enemy\CEnemyHeroManager.h"
#include "KeyManager\CKeyManager.h"
#include "Effect\CEffect.h"
#include "SkinMeshObject\Event\RaccoonDog\CRaccoonDog.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "WriteText\WriteText.h"

//�萔�̖��O���
using namespace Constant_KaitoAppearanceScene;

CKaitoAppearanceScene::CKaitoAppearanceScene()
	:m_pCamera     (&CCameraManager::GetInstance())
	, m_pKaito     ()
	, m_pGround	   ()
	, m_HiddenFlag ()
	, m_AnimEndFlag()
	, m_SkipFlag   ()
{
}

CKaitoAppearanceScene::~CKaitoAppearanceScene()
{
}

void CKaitoAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�J�C�g
	m_pKaito = make_unique<CKaito>();
	//�n��
	m_pGround = make_unique<CGround>();
}

void CKaitoAppearanceScene::Releace()
{
	m_pCamera = nullptr;
}

void CKaitoAppearanceScene::LoadData()
{
	//�q�[���[�̃��b�V���f�[�^�ݒ�
	m_pKaito->LoadMeshData();

	//�n�ʂ̃��b�V���f�[�^�ݒ�
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CKaitoAppearanceScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�J���������ݒ�
	m_pCamera->SetPos(INIT_CAMPOS);	  //�������W
	m_pCamera->SetLook(INIT_CAMLOOK); //���������_

	//�J�C�g������
	m_pKaito->AppearanceInitialize(); 

	//�J�����𓮂����l�̏����l
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };

	//�J�C�g�̔�\���t���O������
	m_HiddenFlag = true;
}

void CKaitoAppearanceScene::Update()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = &CSceneManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();

	//�o�g���q�[���[�I��BGM���~
	CSoundManager::GetInstance()->Stop(CSoundManager::BGM_BattleHeroSelect);

	//�o�g��BGM�̍Đ�
	CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Battle);
	CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Battle, 40);

	//�L�[�}�l�[�W���̓���
	KeyMng->Update();

	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//�������J�C�g��I�����Ă����ꍇ
	//�J�C�g�̃A�j���[�V����
	KaitoAppearance();

	//�X�L�b�v
	if (KeyMng->IsDown(VK_RETURN))
	{
		//���o�X�L�b�v�t���O�𗧂Ă�
		m_SkipFlag = true;

		//�S�ẴG�t�F�N�g���~�߂�
		Eff->StopAll();

		//�o�g���V�[����
		m_SceneTransitionFlg = true;
	}


	//�V�[���J��(��)
	if (m_AnimEndFlag)
	{
		//�I�[�v�j���O�V�[����
		m_SceneTransitionFlg = true;
	}
	//�t�F�[�h�A�E�g����
	if (m_SceneTransitionFlg && FadeOut())
	{
		if (HeroMng->GetBattleHeroName() == "Kaito")
		{
		   SceneMng->LoadCreate(CSceneManager::YuiAppearance);
		}
		else 
		{
			SceneMng->LoadCreate(CSceneManager::Battle);
		}

		//���o�X�L�b�v�t���O�������Ă���΃o�g���V�[����
		if (m_SkipFlag)
		{
			SceneMng->LoadCreate(CSceneManager::Battle);
		}
	}

#if DEBUG
	//�f�o�b�O����
	Debug();
#endif
}

void CKaitoAppearanceScene::Draw()
{
	CHeroManager* HeroMng   = &CHeroManager::GetInstance();
	WriteText* Text	        = WriteText::GetInstance();
	CSceneManager* SceneMng = &CSceneManager::GetInstance();

	//�J�����̓���
	m_pCamera->CameraUpdate();

	//�J�C�g�̃A�j���[�V�������̕`��
	if (!m_HiddenFlag)
	{
		m_pKaito->Draw();
	}

	//�n�ʂ̕`��
	m_pGround->Draw();

	//��̕`��
	DrawSky();

	//������@�w���o�[�̕`��
	DrawControlBar(false);

	//���o�X�L�b�v�w���̕`��
	Text->Draw_Text(L"Enter ���o�X�L�b�v", WriteText::Control, ENTERTEXT_POS);

}

void CKaitoAppearanceScene::Debug()
{
#if DEBUG
	ImGui::Begin(JAPANESE("�f�o�b�O"));
	//ImGui::InputFloat3(JAPANESE("�J�����ʒu:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("�J���������_:%f"), m_DebugCamLook);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
#endif
}

void CKaitoAppearanceScene::KaitoAppearance()
{
	CSceneManager* SceneMng = &CSceneManager::GetInstance();
	CHeroManager* HeroMng = &CHeroManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hMagicSircle = -1;	//���@�w�G�t�F�N�g
	static ::EsHandle hLaser       = 3;	    //���G�t�F�N�g
	//----���@�w�G�t�F�N�g�̐ݒ�----
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle,  MAGICSIRCLE_SCALE);
	Eff->Rotate(hMagicSircle, MAGICSIRCLE_ROTATE);
	//----���G�t�F�N�g�̐ݒ�----
	Eff->Speed(hLaser, 1.0f);
	Eff->Scale(hLaser,  LASER_SCALE);
	Eff->Rotate(hLaser, LASER_ROTATE);

	switch (m_Scene)
	{
	case 0:
		//�J�����̐ݒ�
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));

		//�J������y���̍��W�����̒l�܂ŏグ��
		if (m_MoveCamPos.y <= ANIMCHANGE_CAMPOS_Y)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		else
		{
			//�A�j���[�V�����J�E���g����
			m_AnimCnt++;
			//���@�w�G�t�F�N�g�̍Đ�
			if (m_AnimCnt == 1)
			{
				hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
				//���@�wSE�̍Đ�
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_MagicSircle);
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_MagicSircle, 40);
			}
			//�J�E���g�����l�𒴂����疂�@�w�G�t�F�N�g�̍Đ�
			if (m_AnimCnt >= ANIMCHANGE_CNT) 
			{
				m_Scene = 1;
				m_AnimCnt = 0;
			}
		}

		break;
	case 1:
		//�J�����̐ݒ�
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x - m_MoveCamPos.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			      D3DXVECTOR3(MAGICSIRCLE_POS.x, MAGICSIRCLE_POS.y + m_MoveCamLook.y, MAGICSIRCLE_POS.z));
		//�J������z�������Ɉړ�
		if (m_MoveCamPos.z <= MOVE_CAMPOS_MAX.z)
		{
			m_MoveCamPos.z += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}

		//�J������x�������Ɉړ�
		if (m_MoveCamPos.x <= MOVE_CAMPOS_MAX.x)
		{
			m_MoveCamPos.x += CAM_MOVE_SPEED;
		}

		//�J������y�������Ɉړ�
		if (m_MoveCamPos.y >= MOVE_CAMPOS_MAX.y)
		{
			m_MoveCamPos.y -= CAM_MOVE_SPEED;
		}

		//�����_��y�������̈ړ�
		if (m_MoveCamLook.y <= MOVE_CAMLOOK_MAX_Y)
		{
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}

		//���G�t�F�N�g�̍Đ�
		if (m_AnimCnt == 1)
		{
			hLaser = Eff->Play(CEffect::Laser, MAGICSIRCLE_POS);
		}

		if (m_AnimCnt == 120)
		{
			//��SE�̍Đ�
			CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Laser);
			CSoundManager::GetInstance()->Volume(CSoundManager::SE_Laser, 40);
		}

		//�V�[����i�߂�
		if (m_AnimCnt >= SCENECHANGE_CNT_FAST)
		{
			m_Scene = 2;

			//�A�j���[�V�����J�E���g�̏�����
			m_AnimCnt = 0;
			//���̃V�[���ł̓������J�����̒l�̏����l
			m_MoveCamPos = MOVE_CAMPOS_INIT;
			m_MoveCamLook.y = 1.0f;
		}

		break;
	case 2:
		//�J�����̐ݒ�
		SetCamera(D3DXVECTOR3(0.0f, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			D3DXVECTOR3(MAGICSIRCLE_POS.x, m_MoveCamLook.y, MAGICSIRCLE_POS.z));

		//�J�C�g�̓o��V�[���̃A�j���[�V����
		m_pKaito->AppearanceAnimation();

		//��\���t���O�����낷
		m_HiddenFlag = false;

		if (m_MoveCamPos.y <= MOVE_CAMPOS_MAX_Y)
		{
			m_MoveCamPos.y  += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			//�A�j���[�V�����J�E���g�̉��Z
			m_AnimCnt++;
			
			//�J�������~�܂��Ă��炵�΂炭�o���Ă���
			if (m_AnimCnt >= SCENECEND_CNT_SECOND)
			{
				m_AnimEndFlag = true;
				//���@�w�G�t�F�N�g�̒�~
				Eff->Stop(hMagicSircle);
			}
		}

		break;
	default:
		break;
	}
}

void CKaitoAppearanceScene::SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}

