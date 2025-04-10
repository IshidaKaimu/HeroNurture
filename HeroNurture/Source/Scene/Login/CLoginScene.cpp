#include "CLoginScene.h"
#include "KeyManager\CKeyManager.h"
#include "Sound\CSoundManager.h"
#include "Scene\CSceneManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Json\CJson.h"
//�萔�̖��O���
using namespace Constant_LoginScene;

CLoginScene::CLoginScene()
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

    //���A���^�C�����͏���
    InputName();

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�V�[���J��(��)
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�X�^�[�gSE�̍Đ�
        CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Start);
        CSoundManager::GetInstance()->Volume(CSoundManager::SE_Start, 40);

        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut())
    {
        SceneMng->LoadCreate(CSceneManager::Login);
    }
}

void CLoginScene::Draw()
{
    WriteText* Text = WriteText::GetInstance();

    //���O���̓X�y�[�X�̕`��
    m_pNameSpace->Draw();

    if (m_UserName.empty())
    {
        //���͂��ꂽ�����̕`��
        Text->Draw_Text(L"�����ɖ��O�����...", WriteText::NameInfo, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
    }

    //���͂��ꂽ�����̕`��
    Text->Draw_Text(m_UserName, WriteText::InputName, D3DXVECTOR2(NAME_STARTPOS.x, NAME_STARTPOS.y));
}

//���O���͏���
void CLoginScene::InputName()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();

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

