#include "Scene\Appearance\CAppearanceScene.h"
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
#include "StaticMeshObject\Ground\CGround.h"

//�萔�̖��O���
using namespace Constant_AppearanceScene;

CAppearanceScene::CAppearanceScene()
	:m_pCamera         (&CCameraManager::GetInstance())
	,m_pHero	       (&CHeroManager::GetInstance())
	,m_pEnemyHero      (&CEnemyHeroManager::GetInstance())
	,m_pRaccoonDog     ()
	,m_pGround	       ()
	,m_YuiHiddenFlag   ()
	,m_KaitoHiddenFlag ()
	,m_YuiAnimEndFlag  ()
	,m_KaitoAnimEndFlag()
{
}

CAppearanceScene::~CAppearanceScene()
{
}

void CAppearanceScene::Create()
{
	//�I�����ꂽ�q�[���[�̃C���X�^���X����
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		m_pHero->CreateHero(CHeroManager::Yui);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Kaito);
	}
	else if (m_pHero->GetSelectHeroName() == "Kaito")
	{
		m_pHero->CreateHero(CHeroManager::Kaito);
		//�I������Ȃ������q�[���[��G�Ƃ��Đ���
		m_pEnemyHero->CreateEnemyHero(CHeroManager::Yui);
	}

	//�^�k�L
	m_pRaccoonDog = make_unique<CRaccoonDog>();

	//�n��
	m_pGround = make_unique<CGround>();
}

void CAppearanceScene::Releace()
{
    m_pCamera    = nullptr;
    m_pHero      = nullptr;
	m_pEnemyHero = nullptr;
}

void CAppearanceScene::LoadData()
{
	//�I������Ă���q�[���[�̃��b�V���f�[�^�ݒ�
	m_pHero->LoadMeshData();
	//�G�̃q�[���[�̃��b�V���f�[�^�ݒ�
	m_pEnemyHero->LoadMeshData();

	//�^�k�L�̃��b�V���f�[�^�ݒ�
	m_pRaccoonDog->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::RaccoonDog));
	//�n�ʂ̃��b�V���f�[�^�ݒ�
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CAppearanceScene::Initialize()
{
	//�J���������ݒ�
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		m_pCamera->SetPos(YUI_CAMPOS);	 //�������W
		m_pCamera->SetLook(YUI_CAMLOOK); //���������_
	}
	else
	{
		m_pCamera->SetPos(KAITO_CAMPOS);	 //�������W
		m_pCamera->SetLook(KAITO_CAMLOOK); //���������_
	}

	//�^�k�L�̏�����
	m_pRaccoonDog->Initialize();

	//�e�q�[���[�̏�����
	m_pHero->AppearanceInitialize();      //����
	m_pEnemyHero->AppearanceInitialize(); //�G

	//�J�����𓮂����l�̏����l
	m_MoveCamPos = { 0.0f, 0.0f, 0.0f };
}

void CAppearanceScene::Update()
{
	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	
	//���������C��I�����Ă����ꍇ
	if (m_pHero->GetSelectHeroName() == "Yui")
	{
		//�^�k�L�̃��C�o�ꎞ�A�j���[�V����
		m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);
		//���C�̃A�j���[�V����
		YuiAppearance();
		//���C�̃A�j���[�V�������I��������
		if (m_YuiAnimEndFlag)
		{
			//�J�C�g�̃A�j���[�V������
			KaitoAppearance();
		}
	}

	//�������J�C�g��I�����Ă����ꍇ
	if (m_pHero->GetSelectHeroName() == "Kaito")
	{
		//�J�C�g�̃A�j���[�V����
		KaitoAppearance();
		//�J�C�g�̃A�j���[�V�������I��������
		if (m_KaitoAnimEndFlag)
		{
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

void CAppearanceScene::Draw()
{
	//�J�����̓���
	m_pCamera->CameraUpdate();

	if (!m_YuiAnimEndFlag) 
	{
		//�^�k�L�̕`��
		m_pRaccoonDog->Draw();
		//���C�̕`��
		YuiDraw();
	}

	//�n�ʂ̕`��
	m_pGround->Draw();
}

void CAppearanceScene::Debug()
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

void CAppearanceScene::YuiAppearance()
{
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
		if (m_pHero->GetSelectHeroName() == "Yui")
		{
			m_pHero->AppearanceAnimation();
			//�J�����̐ݒ�
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pHero->GetPosition().z - 2.0f),
						 D3DXVECTOR3(m_pHero->GetPosition().x, m_MoveCamLook.y, m_pHero->GetPosition().z));
		}
		//�G�����C�̏ꍇ
		else if (m_pHero->GetAppealanceAnimEndFlag())
		{
			//�J�����̐ݒ�
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x - 2.0f, m_MoveCamPos.y, m_pEnemyHero->GetPosition().z - 2.0f),
				         D3DXVECTOR3(m_pEnemyHero->GetPosition().x, m_pEnemyHero->GetPosition().y, m_pEnemyHero->GetPosition().z));
		}

		//�J���������̍����ɂȂ�܂�
		if (!m_pHero->GetAppealanceAnimEndFlag())
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
		if (m_pHero->GetSelectHeroName() == "Yui")
		{
			m_pHero->AppearanceAnimation();
			//�J�����̐ݒ�
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pHero->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pHero->GetPosition().x, m_MoveCamLook.y, m_pHero->GetPosition().z));
		}
		//�G�����C�̏ꍇ
		else if (m_pHero->GetAppealanceAnimEndFlag())
		{
			//�J�����̐ݒ�
			YuiSetCamera(D3DXVECTOR3(m_MoveCamPos.x, m_MoveCamPos.y, m_pEnemyHero->GetPosition().z - 4.0f),
				         D3DXVECTOR3(m_pEnemyHero->GetPosition().x, m_pEnemyHero->GetPosition().y, m_pEnemyHero->GetPosition().z));
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
			PlayWhiteFade(1, 0.02f, 1.0f);
			m_AnimCnt++;
			if (m_AnimCnt >= 50)
			{
				//���C�̔�\��
				m_YuiHiddenFlag= true;
			}

			if (m_AnimCnt >= 60)
			{
				//���C�̃A�j���[�V�����̏I��
				m_YuiAnimEndFlag = true;
			}
		}
		break;
	case 3:
		break;
	}
}

void CAppearanceScene::KaitoAppearance()
{
}

void CAppearanceScene::YuiSetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look)
{
	m_pCamera->SetPos(pos);
	m_pCamera->SetLook(look);
}

void CAppearanceScene::YuiDraw()
{
	//���������C���g�p���Ă���ꍇ�̕`��
	if (m_pHero->GetSelectHeroName() == "Yui" && !m_YuiHiddenFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pHero->Draw();
		}
	}
	//�G�����C�̏ꍇ�̕`��
	else if (m_KaitoAnimEndFlag)
	{
		if (m_pRaccoonDog->GetHiddenFlag())
		{
			m_pEnemyHero->Draw();
		}
	}
}
