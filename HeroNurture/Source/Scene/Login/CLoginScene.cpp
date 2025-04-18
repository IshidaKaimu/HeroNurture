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
    , m_pJson      ()
{
}

CLoginScene::~CLoginScene()
{
}

void CLoginScene::Create()
{
    //----UI----
    m_pNameSpace = std::make_unique<CUIObject>();
}

void CLoginScene::Releace()
{
}

void CLoginScene::LoadData()
{
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
}

void CLoginScene::Initialize()
{
    //���O���̓X�y�[�X�̈ʒu������
    m_pNameSpace->SetPosition(NAMESPACE_POS.x, NAMESPACE_POS.y, NAMESPACE_POS.z);
    //���O���̓X�y�[�X�̃X�P�[��������
    m_pNameSpace->SetScale(NAMESPACE_SCALE.x, NAMESPACE_SCALE.y, NAMESPACE_SCALE.z);
    //���O���̓X�y�[�X�̕�������
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);
}

void CLoginScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();
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
            //���[�h�I���V�[����
            m_SceneTransitionFlg = true;
        }
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::ModeSelect);
    }
}

void CLoginScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();

    //���O���̓X�y�[�X�̕`��
    m_pNameSpace->Draw();

    //�V�[�����̕`��
    Text->Draw_Text(L"���O�C��", WriteText::D_Big, D3DXVECTOR2(0.0f, -20.0f));

    if (m_UserName.empty())
    {
        //���͂��ꂽ�����̕`��
        Text->Draw_Text(L"�����ɖ��O�����...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //���͂��ꂽ�����̕`��
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
}


