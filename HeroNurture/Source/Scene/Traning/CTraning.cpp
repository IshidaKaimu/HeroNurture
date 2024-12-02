#include "CTraning.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CTraning::CTraning()
    : m_pCamera (&CCameraManager::GetInstance())
{
}

CTraning::~CTraning()
{
}

//�\�z�֐�
void CTraning::Create()
{
    //----�C���X�^���X����----

    //�X�^�e�B�b�N���b�V���I�u�W�F�N�g
    //��
    m_pSky = make_unique<CSky>();
    //�n��
    m_pGround = make_unique<CGround>();
}
//�j���֐�
void CTraning::Releace()
{
}
//�f�[�^�ǂݍ��݊֐�
void CTraning::LoadData()
{
}
//�������֐�
void CTraning::Initialize()
{
}

//�X�V�֐�
void CTraning::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

   //�L�[�}�l�[�W���[�̍X�V����
   CKeyManager::GetInstance()->Update();

   //�琬�V�[���ւƖ߂�
   if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
   {
       m_SceneTransitionFlg = true;
   }  
   if (m_SceneTransitionFlg && FadeOut())
   {
       CSceneManager::GetInstance()->IsDataLoaded(true);
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//�`��֐�
void CTraning::Draw()
{
    DrawUpText();
}

//�㏸�ʃe�L�X�g�̕`��
void CTraning::DrawUpText()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();

    Text->Draw_Text(L"�ؗ͂�" + std::to_wstring( CHeroManager::GetInstance().GetPowerUpValue() ), WriteText::Normal, D3DXVECTOR2(0.0f, 0.0f));
}
