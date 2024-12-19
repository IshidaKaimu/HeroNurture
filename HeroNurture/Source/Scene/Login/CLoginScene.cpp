#include "CLoginScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include <cmath>
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"

//�^�C�g���V�[��
CLoginScene::CLoginScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pHero()
    , m_pSky    ()
    , m_pGround ()
{
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CLoginScene::~CLoginScene()
{
}

//�\�z�֐�
void CLoginScene::Create()
{
    //�X�J�C�{�b�N�X�N���X
    m_pSky = new CSky();
    //�n�ʃN���X
    m_pGround = new CGround();
    //json�N���X
    m_pJson = std::make_unique<CJson>();
}

//�j���֐�
void CLoginScene::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
    m_pCamera = nullptr;
}


//�f�[�^�ݒ�֐�
void CLoginScene::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));

    Initialize();
}

void CLoginScene::Initialize()
{
}


//�X�V�֐�
void CLoginScene::Update()
{   
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���[�U�[�����͏���
    InputName();

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
       //���[�U�[�l�[�����o�^����Ă�����
       if (!m_UserName.empty()) 
       {
           //�V�[���̃��[�h
           CSceneManager::GetInstance()->LoadCreate(CSceneManager::HeroSelect);
       }
    }


}

//�`��֐�
void CLoginScene::Draw()
{
    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //�����̓���
    WriteText::GetInstance()->Draw_Text(m_UserName, WriteText::Select, D3DXVECTOR2(0.0f, 0.0f));
}

//�C�[�W���O
float CLoginScene::Easing(float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

//���O���͏���
void CLoginScene::InputName()
{
    //�L�[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    //�L�[�}�l�[�W���̏�ɍs������
    KeyMng->Update();

    //�L�[�S���𒲂ׂ�
    for (int key = 0x30; key <= 0x5A; key++)
    {
        if (KeyMng->IsDown(key))
        {
            //���͂��ꂽ������ǉ�
            m_UserName += wchar_t(key);
        }
    }

    //�e�L�X�g����ł͂Ȃ��Ȃ�
    if (!m_UserName.empty()) 
    {
        //�o�b�N�X�y�[�X�������ꂽ��
        if (KeyMng->IsDown(VK_BACK))
        {
            //�Ō�̕������폜
            m_UserName.pop_back();
        }
    }
}

//wstring��string�ɕϊ�
std::string CLoginScene::WstringToString(std::wstring owstring)
{
    //wstring����SJIS
    int iBufferSize = 
        WideCharToMultiByte( CP_OEMCP, 0, owstring.c_str(), -1, (char * )NULL, 0, NULL, NULL );

    //�o�b�t�@�̎擾
    CHAR* cpMultiByte = new CHAR[ iBufferSize ];

    //wstring����SJIS
    WideCharToMultiByte(CP_OEMCP, 0, owstring.c_str(), -1, cpMultiByte, iBufferSize, NULL, NULL);

    //string�̐���
    std::string oRet( cpMultiByte, cpMultiByte + iBufferSize -1 );

    //�o�b�t�@�̔j��
    delete [] cpMultiByte;

    return (oRet);
}
