#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"

CNatureScene::CNatureScene()
    : m_pCamera( &CCameraManager::GetInstance() )
{
}

CNatureScene::~CNatureScene()
{
}

//�\�z�֐�
void CNatureScene::Create()
{

    //----�C���X�^���X����----
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����
    switch (CHeroManager::GetInstance().GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        CHeroManager::GetInstance().SetHero(CHeroManager::Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        CHeroManager::GetInstance().SetHero(CHeroManager::Kaito);
        break;
    default:
        break;
    }
    
    //�n��
    m_pGround = new CGround();

    //�X�J�C�{�b�N�X
    m_pSky = new CSky();


}

//�j���֐�
void CNatureScene::Releace()
{
    //----�j��----
    m_pCamera = nullptr;
}


//�f�[�^�ǂݍ��݊֐�
void CNatureScene::LoadData()
{  
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃f�[�^�ǂݍ���
    CHeroManager::GetInstance().LoadData();

    //�n��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

}

//�������֐�
void CNatureScene::Initialize()
{
    //�J�����̏�����
    m_pCamera->Initialize();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̏�����
    CHeroManager::GetInstance().Initialize();

    //���C�g���
    m_Light.Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����

}


//�X�V�֐�
void CNatureScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    CHeroManager::GetInstance().Update();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃A�j���[�V����
    CHeroManager::GetInstance().Animation();

}

//�`��N���X
void CNatureScene::Draw()
{
    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    CHeroManager::GetInstance().Draw( m_Light );

    //�n�ʃN���X�̕`��
    m_pGround->Draw( m_Light );

}
