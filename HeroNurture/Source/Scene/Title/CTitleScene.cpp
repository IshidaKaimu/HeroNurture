#include "CTitleScene.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sound\CSoundManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"
#include "Sprite2D\UIManager\CUIManager.h" 
#include <cmath>


CTitleScene::CTitleScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pYui    ()
    , m_pKaito  ()
    , m_pSky    ()
    , m_pGround ()
    , m_HeroNo  ()
{
    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Create()
{
    //----�X�^�e�B�b�N���b�V��----
    //�X�J�C�{�b�N�X
    m_pSky = std::make_unique<CSky>();
    //�n��
    m_pGround = std::make_unique<CGround>();
    
    //----�X�L�����b�V��----
    //���C
    m_pYui = std::make_unique<CYui>();
    //�J�C�g
    m_pKaito = std::make_unique<CKaito>();

    //json
    m_pJson = std::make_unique<CJson>();

    //----UI----
    //�^�C�g���w�i
    m_pTitleBack = std::make_unique<CUIObject>();
    //�^�C�g���w���e�L�X�g�w�i
    m_pTitleInfoBack = std::make_unique<CUIObject>();
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MMng = CMeshManager::GetInstance();
    //----�X�^�e�B�b�N���b�V��----
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));      //��
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));//�n��

    //----�^�C�g����ʂɕ\������q�[���[�̃��b�V���ݒ�----
    m_pYui->LoadMeshData();  //���C
    m_pKaito->LoadMeshData();//�J�C�g

    //----UI----
    m_pTitleBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleBack));
    m_pTitleInfoBack->AttachSprite(CUIManager::GetSprite(CUIManager::TitleInfoBack));
}

void CTitleScene::Initialize()
{
    //�J�����̏����ʒu
    m_pCamera->SetPos(5.0f, 4.0f, -5.0f);
    m_pCamera->SetLook(0.0f, 4.0f, 0.0f);

    //�ǂ���̃q�[���[��\�����邩�A�����Őݒ�
    m_HeroNo = CUtility::GetInstance().GenerateRandomValue(0,1);

    //�ݒ肳�ꂽ�q�[���[�̏�����
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->Initialize();
        break;
    case 1:
        m_pKaito->Initialize();
        break;
    default:
        break;
    }
}

//�X�V�֐�
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = CSceneManager::GetInstance();
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    KeyMng->Update();

    //�^�C�g��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start,40);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CTitleScene::Draw()
{
    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw();

    //�n�ʂ̕`��
    m_pGround->Draw();

    //�\����؂�ւ���
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    default:
        break;
    }

    //UI
    DrawUI();
}

//�C�[�W���O
float CTitleScene::Easing(float x)
{
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}

//���O���͏���
void CTitleScene::InputName()
{
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

//�^�C�g����ʂ̕`��
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //�^�C�g���w�iUI�����ݒ�
    m_pTitleBack->SetPosition(260.0f, 200.0f,0.0f);
    m_pTitleBack->SetScale(1.5f, 0.8f, 1.5f);
    m_pTitleBack->SetDisplay(1.0f, 1.0f);
    m_pTitleBack->SetAlpha(0.9f);
    //�^�C�g���w���e�L�X�g�w�i
    m_pTitleInfoBack->SetPosition(420.0f, 445.0f, 0.0f);
    m_pTitleInfoBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pTitleInfoBack->SetDisplay(1.0f, 1.0f);
    m_pTitleInfoBack->SetAlpha(0.9f);

    //�^�C�g���w�i�`��
    m_pTitleBack->Draw();
    //�^�C�g���w���e�L�X�g�w�i�`��
    m_pTitleInfoBack->Draw();

    Text->Draw_Text(L"HeroNature", WriteText::B_Big, D3DXVECTOR2(305.0f, 165.0f));   //�^�C�g��
    Text->Draw_Text(L"Press Enter", WriteText::B_Small, D3DXVECTOR2(480.0f, 450.0f)); //�w��

}

//wstring��string�ɕϊ�
std::string CTitleScene::WstringToString(std::wstring owstring)
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
