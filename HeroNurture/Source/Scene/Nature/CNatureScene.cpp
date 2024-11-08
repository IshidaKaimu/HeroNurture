#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"

CNatureScene::CNatureScene()
    : m_pHero()
    , m_pCamera( &CCameraManager::GetInstance() )
{
}

CNatureScene::~CNatureScene()
{
}

//�\�z�֐�
void CNatureScene::Create()
{
    //----�C���X�^���X����----
    m_pHero = std::make_unique<CHeroBase>();
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
}

//�������֐�
void CNatureScene::Initialize()
{
}


//�X�V�֐�
void CNatureScene::Update()
{
}

//�`��N���X
void CNatureScene::Draw()
{
    //----�I�u�W�F�N�g�̕`��----
    
}
