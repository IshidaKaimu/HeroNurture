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

//�萔�̖��O���
using namespace Constant_KaitoAppearanceScene;

CKaitoAppearanceScene::CKaitoAppearanceScene()
	:m_pCamera(&CCameraManager::GetInstance())
	, m_pYui()
	, m_pKaito()
	, m_pGround()
	, m_HiddenFlag()
	, m_AnimEndFlag()
{
}

CKaitoAppearanceScene::~CKaitoAppearanceScene()
{
}

void CKaitoAppearanceScene::Create()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//���C
	m_pYui = make_unique<CYui>();
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
	m_pCamera->SetPos(CAMPOS);	 //�������W
	m_pCamera->SetLook(CAMLOOK); //���������_

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
	CSceneManager* SceneMng = CSceneManager::GetInstance();

	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//�������J�C�g��I�����Ă����ꍇ
	//�J�C�g�̃A�j���[�V����
	KaitoAppearance();

	//�V�[���J��(��)
	if (m_AnimEndFlag)
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

void CKaitoAppearanceScene::Draw()
{
	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	//�J�����̓���
	m_pCamera->CameraUpdate();

	//�J�C�g�̃A�j���[�V�������̕`��
	if (!m_HiddenFlag)
	{
		m_pKaito->Draw();
	}

	//�n�ʂ̕`��
	m_pGround->Draw();
}

void CKaitoAppearanceScene::Debug()
{
	ImGui::Begin(JAPANESE("�f�o�b�O"));
	//ImGui::InputFloat3(JAPANESE("�J�����ʒu:%f"), m_DebugCamPos);
	//ImGui::InputFloat3(JAPANESE("�J���������_:%f"), m_DebugCamLook);
	ImGui::End();

	//m_pCamera->SetPos(m_DebugCamPos);
	//m_pCamera->SetLook(m_DebugCamLook);
}

void CKaitoAppearanceScene::KaitoAppearance()
{
	CSceneManager* SceneMng = CSceneManager::GetInstance();
	CEffect* Eff = CEffect::GetInstance();
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hMagicSircle = -1;	//���@�w�G�t�F�N�g
	static ::EsHandle hLaser       = 3;	    //���G�t�F�N�g
	//----���@�w�G�t�F�N�g�̐ݒ�----
	Eff->Speed(hMagicSircle, 1.0f);
	Eff->Scale(hMagicSircle, 4.0f, 4.0f, 4.0f);
	Eff->Rotate(hMagicSircle, D3DXToRadian(90.0f), 1.0f, 1.0f);
	//----���G�t�F�N�g�̐ݒ�----
	Eff->Speed(hLaser, 1.0f);
	Eff->Scale(hLaser, 5.0f, 5.0f, 5.0f);
	Eff->Rotate(hLaser, D3DXToRadian(270.0f), 1.0f, 1.0f);


	CHeroManager* HeroMng = &CHeroManager::GetInstance();

	switch (m_Scene)
	{
	case 0:
		//�J�����̐ݒ�
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z),
			D3DXVECTOR3(MAGICSIRCLE_POS));

		m_AnimCnt++;
		if (m_AnimCnt == 1)
		{
			hMagicSircle = Eff->Play(CEffect::enList::MagicSircle, MAGICSIRCLE_POS);
		}

		//�J������y���̍��W�����̒l�܂ŏグ��
		if (m_MoveCamPos.y <= 10.0f)
		{
			m_MoveCamPos.y += CAM_MOVE_SPEED;
		}
		else
		{
			//�V�[����i�߂�
			m_Scene = 1;
			m_AnimCnt = 0;
		}
		break;
	case 1:
		//�J�����̐ݒ�
		SetCamera(D3DXVECTOR3(MAGICSIRCLE_CAMPOS.x - m_MoveCamPos.x, MAGICSIRCLE_CAMPOS.y + m_MoveCamPos.y, MAGICSIRCLE_CAMPOS.z - m_MoveCamPos.z),
			      D3DXVECTOR3(MAGICSIRCLE_POS.x, MAGICSIRCLE_POS.y + m_MoveCamLook.y, MAGICSIRCLE_POS.z));
		//�J������z�������Ɉړ�
		if (m_MoveCamPos.z <= 12.0f)
		{
			m_MoveCamPos.z += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimCnt++;
		}


		if (m_MoveCamPos.x <= 1.0f)
		{
			m_MoveCamPos.x += CAM_MOVE_SPEED;
		}

		if (m_MoveCamPos.y >= 6.0f)
		{
			m_MoveCamPos.y -= CAM_MOVE_SPEED;
		}

		if (m_MoveCamLook.y <= 4.0f)
		{
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}

		//���G�t�F�N�g�̍Đ�
		if (m_AnimCnt == 1)
		{
			hLaser = Eff->Play(CEffect::Laser, MAGICSIRCLE_POS);
		}

		//�V�[����i�߂�
		if (m_AnimCnt >= 240)
		{
			m_Scene = 2;

			//���̃V�[���ł̓������J�����̒l�̏����l
			m_MoveCamPos = { 0.0f, 1.0f, 5.0f };
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

		if (m_MoveCamPos.y <= 6.5f)
		{
			m_MoveCamPos.y  += CAM_MOVE_SPEED;
			m_MoveCamLook.y += CAM_MOVE_SPEED;
		}
		else
		{
			m_AnimEndFlag = true;
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

