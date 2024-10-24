#include "CGameMain.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "SkinMesh/SkinMeshManager/CSkinMeshManager.h"
#include "Sound/CSoundManager.h"
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <cmath>
#include <fstream>
#include <sstream>


CGameMain::CGameMain()
    : m_pSky()
    , m_pGround()
    , m_UserName()
    , m_pPlayer()
{
}

CGameMain::~CGameMain()
{
}

void CGameMain::Initialize()
{
    //�v���C���[�̍��W����ϐ��ɑ��
    D3DXVECTOR3 PPos = m_pPlayer->GetPosition();

    CCamera::GetInstance()->SetPos(D3DXVECTOR3(PPos.x,PPos.y + 10.0f,PPos.z-5.0));
    m_Camera.Look = D3DXVECTOR3(0.0, 0.0, 0.0);

    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

//�\�z�֐�
void CGameMain::Create()
{
    //�X�J�C�{�b�N�X�̃C���X�^���X����
    m_pSky    = new CSky();
    //�n�ʂ̃C���X�^���X����
    m_pGround = new CGround();
    //�v���C���[�̃C���X�^���X����
    m_pPlayer = new CPlayer();


}

//�f�[�^�ݒ�֐�
void CGameMain::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();

    //�X�L�����b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CSkinMeshManager* SKMng = CSkinMeshManager::GetInstance();


    //�X�J�C�{�b�N�X�̃��b�V���ݒ�
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    //�n�ʂ̃��b�V���ݒ�
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
    //�v���C���[�̃��b�V���ݒ�
    m_pPlayer->AttachMesh(CSkinMeshManager::GetMesh(CSkinMeshManager::Player));
    
    //���[�U�[���̐ݒ�
    m_pPlayer->MakeData(m_UserName);
    m_pPlayer->SetUserName(m_UserName);

}

//�j���֐�
void CGameMain::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    SAFE_DELETE(m_pPlayer);
}

//�X�V�֐�
void CGameMain::Update()
{
    //�v���C���[�̍��W����ϐ��ɑ��
    D3DXVECTOR3 PPos = m_pPlayer->GetPosition();


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

#ifdef _DEBUG 
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_Camera.Position);
    ImGui::InputFloat3(JAPANESE("�����_"), m_Camera.Look);
    CCamera::GetInstance()->SetPos(m_Camera.Position);
    CCamera::GetInstance()->SetLook(m_Camera.Look);

#endif

    
    m_pPlayer->Update();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
      
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::SceneSelect);
    }
}

//�`��֐�
void CGameMain::Draw()
{

    CCamera::GetInstance()->Projection();
    CCamera::GetInstance()->Update();

    //�v���W�F�N�V�����̎擾
    m_mProj = CCamera::GetInstance()->GetProjection();
    //�r���[�̎擾
    m_mView = CCamera::GetInstance()->GetViewMatrix();

    //�v���C���[�̕`��
    m_pPlayer->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //��̕`��
    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //�n�ʂ̕`��
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
}

