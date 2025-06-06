#include "CLoginScene.h"
#include "Json\CJson.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Utility\CUtility.h"

//�萔�̖��O���
using namespace Constant_LoginScene;

CLoginScene::CLoginScene()
    : m_TargetPath ()
    , m_UserName   ()
    , m_pNameSpace ()
    , m_pBack      ()
    , m_pJson      ()
    , m_NonExistent()
{
}

CLoginScene::~CLoginScene()
{
}

void CLoginScene::Create()
{
    //----UI----
    //���O���͋��
    m_pNameSpace = std::make_unique<CUIObject>(); 
    //�w�i
    m_pBack = std::make_unique<CUIObject>();
    //----------

}

void CLoginScene::Releace()
{
}

void CLoginScene::LoadData()
{
    //----UI----
    //���O���̓X�y�[�X
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
    //�w�i
    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::BasicBack));
    //----------
}

void CLoginScene::Initialize()
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

void CLoginScene::Update()
{
    //���[�h�I��BGM���~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //�^�C�g��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);


    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CUtility* Utility = &CUtility::GetInstance();

    //���A���^�C�����͏���
    Utility->InputText(m_UserName,NAME_MAXLENGTH);


    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //string�^�ɕϊ��@
        std::string UserName = Utility->WstringToString(m_UserName);
        //���݊m�F�������t�H���_�̃p�X
        m_TargetPath = "Data\\Acount\\" + UserName;

        //���͂������O�̃A�J�E���g�����ɑ��݂��Ă����
        if (!m_UserName.empty() && std::filesystem::exists(m_TargetPath)) {
            //���O�̓o�^
            SceneMng->SetName(m_UserName);
            //�t�F�[�h�J�n
            m_SceneTransitionFlg = true;
        }
        else
        {
            //��v���閼�O�����݂��Ȃ����Ƃ�\������
            m_NonExistent = true;
        }
    }

    //�O�̉�ʂɖ߂�
    if (KeyMng->IsDown(VK_ESCAPE))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //�I��ԍ���ύX����
        m_SelectNo = 1;
        //�t�F�[�h�J�n
        m_SceneTransitionFlg = true;
    }

    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        switch (m_SelectNo)
        {
        case 0: SceneMng->LoadCreate(CSceneManager::ModeSelect); break;
        case 1: SceneMng->LoadCreate(CSceneManager::Title); break;
        }
    }
}

void CLoginScene::Draw()
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
    Text->Draw_Text(L"���O�C��", WriteText::Select, SCENENAME_POS);

    if (m_UserName.empty())
    {
        //���͂��ꂽ�����̕`��
        Text->Draw_Text(L"�����ɖ��O�����...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    if (m_NonExistent)
    {
        //��v���閼�O���Ȃ��ꍇ�̕���\��
        Text->Draw_Text(L"����v����A�J�E���g�������݂��܂���", WriteText::Error, D3DXVECTOR2(300.0f, 450.0f));
    }

    //���͂��ꂽ�����̕`��
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));

}


