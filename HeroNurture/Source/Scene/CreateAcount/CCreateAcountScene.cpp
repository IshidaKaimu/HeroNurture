#include "CCreateAcountScene.h"
#include "Json\CJson.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Utility\CUtility.h"
//�萔�̖��O���
using namespace Constant_CreateAcountScene;

CCreateAcountScene::CCreateAcountScene()
    : m_pCamera    ()
    , m_SorceDir   ()
    , m_DestDir    ()
    , m_UserName   ()
    , m_pNameSpace ()
    , m_pJson      ()
    , m_Duplication()
{
}

CCreateAcountScene::~CCreateAcountScene()
{
}

void CCreateAcountScene::Create()
{
    //----UI----
    //���O���͋��
    m_pNameSpace = std::make_unique<CUIObject>();
    //�w�i
    m_pBack = std::make_unique<CUIObject>();
    //----------
}

void CCreateAcountScene::Releace()
{
}

void CCreateAcountScene::LoadData()
{
    //----UI----
    //���O���͋��
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
    //�w�i
    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::BasicBack));
    //---------
}

void CCreateAcountScene::Initialize()
{
    //���O���̓X�y�[�X
    m_pNameSpace->SetPosition(NAMESPACE_POS);                    //���W
    m_pNameSpace->SetScale(NAMESPACE_SCALE);                     //�g�k
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);//��
    //�w�i
    m_pBack->SetPosition(BACK_POS);                         //���W
    m_pBack->SetScale(BACK_SCALE);                          //�g�k
    m_pBack->SetDisplay(BACK_DISP.x, BACK_DISP.y);          //��
}

void CCreateAcountScene::Update()
{
    //�^�C�g��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    WriteText* Text = WriteText::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //���A���^�C�����͏���
    CUtility::GetInstance().InputText(m_UserName,NAME_MAXLENGTH);

    //�R�s�[���t�H���_�̃p�X
    m_SorceDir = "Data\\Acount\\Base";
    //�R�s�[��t�H���_�̃p�X
    m_DestDir = "Data\\Acount\\" + CUtility::GetInstance().WstringToString(m_UserName);

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        if (!m_UserName.empty()) {

            //�R�s�[��̃t�H���_�����݂��Ă��Ȃ����
            if (!std::filesystem::exists(m_DestDir))
            {
                //�t�H���_�̃R�s�[
                std::filesystem::copy(
                    m_SorceDir,     //�R�s�[���̃p�X
                    m_DestDir,      //�R�s�[��̃p�X
                    std::filesystem::copy_options::recursive    //�t�H���_���̃t�@�C�������R�s�[
                );
                
                //�d���̕\�����Ȃ���
                m_Duplication = false;

                //�I�[�v�j���O�V�[����
                m_SceneTransitionFlg = true;
            }
            else
            {
                //�d�����Ă��邱�Ƃ�\������
                m_Duplication = true;
            }
        }
    }

    //�O�̉�ʂɖ߂�
    if (KeyMng->IsDown(VK_ESCAPE))
    {
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::Title);
    }
}

void CCreateAcountScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();


    //�[�x�𖳌��ɂ���
    SceneMng->GetDx11()->SetDepth(false);

    //�ėp�w�i�̕`��
    DrawBasicBackGround();

    //������@�w���o�[�̕`��
    DrawControlBar(true);

    //���O���̓X�y�[�X�̕`��
    m_pNameSpace->Draw();

    //�[�x��L���ɂ���
    SceneMng->GetDx11()->SetDepth(true);

    //�V�[�����̕`��
    Text->Draw_Text(L"�A�J�E���g���쐬", WriteText::Select, SCENENAME_POS);

    //�������͂���Ă��Ȃ����
    if (m_UserName.empty())
    {
        //���͂��ꂽ�����̕`��
        Text->Draw_Text(L"�����ɖ��O�����...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //���͂��ꂽ�����̕`��
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));

    if (m_Duplication)
    {
        Text->Draw_Text(L"�����̃A�J�E���g���͊��Ɏg�p����Ă��܂�", WriteText::Error, D3DXVECTOR2(300.0f, 450.0f));
    }
}

