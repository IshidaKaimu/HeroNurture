#include "Scene\Appearance\Yui\CYuiAppearanceScene.h"
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

//�萔�̖��O���
using namespace Constant_AppearanceScene;

CYuiAppearanceScene::CYuiAppearanceScene()
	:m_pCamera         (&CCameraManager::GetInstance())
	,m_pYui	           ()
	,m_pKaito          ()
	,m_pRaccoonDog     ()
	,m_pGround	       ()
	,m_YuiHiddenFlag   ()
	,m_KaitoHiddenFlag ()
	,m_YuiAnimEndFlag  ()
	,m_KaitoAnimEndFlag()
{
}

CYuiAppearanceScene::~CYuiAppearanceScene()
{
}

void CYuiAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//���C
	m_pYui = make_unique<CYui>();
	//�J�C�g
	m_pKaito = make_unique<CKaito>();

	//�^�k�L
	m_pRaccoonDog = make_unique<CRaccoonDog>();

	//�n��
	m_pGround = make_unique<CGround>();
}

void CYuiAppearanceScene::Releace()
{
    m_pCamera    = nullptr;
}

void CYuiAppearanceScene::LoadData()
{
	//�q�[���[�̃��b�V���f�[�^�ݒ�
	m_pYui->LoadMeshData();
	m_pKaito->LoadMeshData();

	//�^�k�L�̃��b�V���f�[�^�ݒ�
	m_pRaccoonDog->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::RaccoonDog));
	//�n�ʂ̃��b�V���f�[�^�ݒ�
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CYuiAppearanceScene::Initialize()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�J���������ݒ�
	if (HeroMng->GetBattleHeroName() == "Yui")
	{
		m_pCamera->SetPos(YUI_CAMPOS);	 //�������W
		m_pCamera->SetLook(YUI_CAMLOOK); //���������_
	}
	else if(HeroMng->GetBattleHeroName() == "Kaito")
	{
		m_pCamera->SetPos(KAITO_CAMPOS);	 //�������W
		m_pCamera->SetLook(KAITO_CAMLOOK); //���������_
	}

	//�^�k�L�̏�����
	m_pRaccoonDog->Initialize();

	//�e�q�[���[�̏�����
	m_pYui->AppearanceInitialize();   //����
	m_pKaito->AppearanceInitialize(); //�G

	//�J�����𓮂����l�̏����l
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };
}

void CYuiAppearanceScene::Update()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	
	//���������C��I�����Ă����ꍇ
  if (HeroMng->GetBattleHeroName() == "Yui")
	{
	  if (!m_YuiAnimEndFlag)
	  {
		  //�^�k�L�̃��C�o�ꎞ�A�j���[�V����
		  if (!m_pRaccoonDog->GetHiddenFlag()) 
		  {
			  m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);
		  }
		  //���C�̃A�j���[�V����
		  YuiAppearance();
	  }
	  //���C�̃A�j���[�V�������I��������
	  else 
	  {
		  //�V�[���i�K�̃��Z�b�g
		  m_Scene = 0;
		  //�J�C�g�̃A�j���[�V������
		  KaitoAppearance();
	  }
	}

	//�������J�C�g��I�����Ă����ꍇ
	if (HeroMng->GetBattleHeroName() == "Kaito")
	{
		if (!m_KaitoAnimEndFlag) {
			//�J�C�g�̃A�j���[�V����
			KaitoAppearance();
		}
		//�J�C�g�̃A�j���[�V�������I��������
		else
		{
			//�V�[���i�K�̃��Z�b�g
			m_Scene = 0;
			//�^�k�L�̃��C�o�ꎞ�A�j���[�V����
			m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);
			//���C�̃A�j���[�V����
			YuiAppearance();
		}
	}

	//�V�[���J��(��)
	if (KeyMng->IsDown(VK_RETURN))
	{
		//����SE�̍Đ�
		CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
		CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, 40);

		//�I�[�v�j���O�V�[����
		m_SceneTransitionFlg = true;
	}
	//�t�F�[�h�A�E�g����
	if (m_SceneTransitionFlg && FadeOut())
	{
		SceneMng->LoadCreate(CSceneManager::Battle);
	}

#if DEBUG
	//�f�o�b�O����
	Debug();
#endif
}

void CYuiAppearanceScene::Draw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�J�����̓���
	m_pCamera->CameraUpdate();

	
	if (HeroMng->GetBattleHeroName() == "Yui")
	{
		//���C�̃A�j���[�V������
		if (!m_YuiAnimEndFlag)
		{
			//�^�k�L�̕`��
			m_pRaccoonDog->Draw();
			//���C�̕`��
			YuiDraw();
		}
		else
		{
			if (!GetWhiteFadeNow()) 
			{
				//�J�C�g�̕`��
				KaitoDraw();
			}
		}
	}
	//�J�C�g�̃A�j���[�V�������̕`��
	else if(HeroMng->GetBattleHeroName() == "Kaito")
	{
		//	�J�C�g�̃A�j���[�V������
		if (!m_KaitoAnimEndFlag)
		{
			KaitoDraw();
		}
		else
		{
			//�^�k�L�̕`��
			m_pRaccoonDog->Draw();
			//���C�̕`��
			YuiDraw();
		}

	}

	//�n�ʂ̕`��
	m_pGround->Draw();
}

void CYuiAppearanceScene::Debug()
{
	ImGui::Begin(JAPANESE("�f�o�b�O"));
	//ImGui::InputFloat3(JAPANESE("�J�����ʒu:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("�J���������_:%f"), m_DebugCamLook);
	ImGui::InputFloat3(JAPANESE("�^�k�L��]:%f"), m_DebugRotate);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
	m_pRaccoonDog->SetRotation(D3DXVECTOR3(D3DXToRadian(m_DebugRotate.x), D3DXToRadian(m_DebugRotate.y), D3DXToRadian(m_DebugRotate.z)));
}

void CYuiAppearanceScene::YuiAppearance()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		//�������J�����̒l���Z�b�g
		m_pCamera->SetPos(YUI_CAMPOS.x + m_MoveCamPos.x, YUI_CAMPOS.y + m_MoveCamPos.y, YUI_CAMPOS.z + m_MoveCamPos.z);

		//���t�F�[�h
		if (m_pRaccoonDog->GetPosition().z <= FLICK_WHITEFADE)
		{
			PlayWhiteFade(0, 0.06f, 1.0f);
		}

		//�^�k�L���J������Z���W�𒴂�����
		if (m_pRaccoonDog->GetPosition().z <= YUI_CAMPOS.z)
		{
			if (m_MoveCamPos.z >= -CAM_FLICK_DISTANCE)
			{
				m_MoveCamPos.z -= CAM_FLICK_SPEED;
			}
		
		}
		//�^�k�L����\���ɂȂ�����
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			//�V�[����i�߂�
			m_Scene = 1;
			//�������J������y��
			m_MoveCamPos.y = 1.5f;
		}
		break;
	case 1:
		//���������C��I�����Ă����ꍇ
		if (HeroMng->GetSelectHeroName() == "Yui")
		{
			m_pYui->AppearanceAnimation();
			//�J�����̐ݒ�
			SetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pYui->GetPosition().z - 2.0f),
						 D3DXVECTOR3(m_pYui->GetPosition().x, m_MoveCamLook.y, m_pYui->GetPosition().z));
		}
		//�G�����C�̏ꍇ
		else if (m_pYui->GetAppealanceAnimEndFlag())
		{
			//�J�����̐ݒ�
			SetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pYui->GetPosition().z - 2.0f),
				         D3DXVECTOR3(m_pYui->GetPosition().x, m_pYui->GetPosition().y, m_pYui->GetPosition().z));
		}

		//�J���������̍����ɂȂ�܂�
		if (!m_pYui->GetAppealanceAnimEndFlag())
		{
			//���W�ƒ����_��������
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}

		if(m_AnimCnt >= 60)
		{
			m_Scene = 2;
			//�������J������y��
			m_MoveCamPos.y  = 2.0f;  //���W
			m_MoveCamLook.y = 2.0f; //�����_
			//�A�j���[�V�����J�E���g�̃��Z�b�g
			m_AnimCnt = 0;
		}
		break;
	case 2:
		//���������C��I�����Ă����ꍇ
		if (HeroMng->GetSelectHeroName() == "Yui")
		{
			m_pYui->AppearanceAnimation();
			//�J�����̐ݒ�
			SetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pYui->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pYui->GetPosition().x, m_MoveCamLook.y, m_pYui->GetPosition().z));
		}
		//�G�����C�̏ꍇ
		else if (m_pYui->GetAppealanceAnimEndFlag())
		{
			//�J�����̐ݒ�
			SetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pYui->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pYui->GetPosition().x, m_pYui->GetPosition().y, m_pYui->GetPosition().z));
		}

		//�J���������̍����ɂȂ�܂�
		if (m_MoveCamPos.y <= YUI_CAMPOS.y + 2.5f)
		{
			//���W�ƒ����_��������
			m_MoveCamPos.y += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
			if (m_AnimCnt >= 120)
			{
				m_AnimCnt = 0;
				//���C�̃A�j���[�V�����̏I��
				m_YuiAnimEndFlag = true;
				//�J�C�g�̃A�j���[�V������łȂ����
				if (!m_KaitoAnimEndFlag)
				{
					m_MoveCamPos.y = 1.0f;
				}
			}
		}
		break;
	}
}

void CYuiAppearanceScene::KaitoAppearance()
{
	CEffect* Eff = CEffect::GetInstance();
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hMagicSircle = -1;	//���@�w�G�t�F�N�g
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle, 4.0f,4.0f,4.0f);
	Eff->Rotate(hMagicSircle, D3DXToRadian(90.0f), 1.0f,1.0f);

	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));
		
		m_AnimCnt++;
		if (m_AnimCnt == 1)
		{
			hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
		}

		if (m_MoveCamPos.y <= 20.0f)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		break;
	case 1:
		break;
	default:
		break;
	}
}

void CYuiAppearanceScene::SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}

void CYuiAppearanceScene::YuiDraw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//���������C���g�p���Ă���ꍇ�̕`��
	if (HeroMng->GetSelectHeroName() == "Yui" && !m_YuiHiddenFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pYui->Draw();
		}
	}
	//�G�����C�̏ꍇ�̕`��
	else if (m_KaitoAnimEndFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pYui->Draw();
		}
	}
}

void CYuiAppearanceScene::KaitoDraw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�������J�C�g���g�p���Ă���ꍇ�̕`��
	if (HeroMng->GetSelectHeroName() == "Kaito" && !m_KaitoHiddenFlag)
	{
		m_pKaito->Draw();
	}
	//�G���J�C�g�̏ꍇ�̕`��
	else if (m_YuiAnimEndFlag)
	{
	    m_pKaito->Draw();
	}
}
