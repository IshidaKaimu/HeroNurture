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
	:m_pCamera    (&CCameraManager::GetInstance())
	,m_pHero	  (&CHeroManager::GetInstance())
	,m_pEnemyHero (&CEnemyHeroManager::GetInstance())
	,m_pRaccoonDog()
	,m_pGround	  ()
{
}

CAppearanceScene::~CAppearanceScene()
{
}

void CAppearanceScene::Create()
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
	//�^�k�L�̃��b�V���f�[�^�ݒ�
	m_pRaccoonDog->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::RaccoonDog));
	//�n�ʂ̃��b�V���f�[�^�ݒ�
	m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

void CAppearanceScene::Initialize()
{
	//�J���������ݒ�
	m_pCamera->SetPos(YUI_CAMPOS);	 //�������W
	m_pCamera->SetLook(YUI_CAMLOOK); //���������_

	//�^�k�L�̏�����
	m_pRaccoonDog->Initialize();

	//�J�����𓮂����l�̏����l
	m_MoveCam = { 0.0f, 0.0f, 0.0f };
}

void CAppearanceScene::Update()
{
	CKeyManager* KeyMng = &CKeyManager::GetInstance();
	CSceneManager* SceneMng = CSceneManager::GetInstance();


	//�t�F�[�h�C������
	if (!FadeIn()) { return; }

	//�^�k�L�̃��C�o�ꎞ�A�j���[�V����
	m_pRaccoonDog->AppearanceAnim(YUI_CAMPOS.z);

	//���C�̓o��A�j���[�V����
	YuiAppearance();

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

	//�^�k�L�̕`��
	m_pRaccoonDog->Draw();

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
	//�������J�����̒l���Z�b�g
	m_pCamera->SetPos(YUI_CAMPOS.x + m_MoveCam.x, YUI_CAMPOS.y + m_MoveCam.y, YUI_CAMPOS.z + m_MoveCam.z);

	switch (m_Cut)
	{
	case 0:
		if (m_pRaccoonDog->GetPosition().z <= YUI_CAMPOS.z)
		{
			if (m_MoveCam.z >= -CAM_FLICK_DISTANCE)
			{
				m_MoveCam.z -= CAM_FLICK_SPEED;
			}
		}
		break;
	case 1:

		break;
	}
}

void CAppearanceScene::KaitoAppearance()
{
}
