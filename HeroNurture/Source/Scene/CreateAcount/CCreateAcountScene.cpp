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
{
}

CCreateAcountScene::~CCreateAcountScene()
{
}

void CCreateAcountScene::Create()
{
    //----UI----
    m_pNameSpace = std::make_unique<CUIObject>();
}

void CCreateAcountScene::Releace()
{
}

void CCreateAcountScene::LoadData()
{
    m_pNameSpace->AttachSprite(CUIManager::GetSprite(CUIManager::NameSpace));
}

void CCreateAcountScene::Initialize()
{
    //���O���̓X�y�[�X�̈ʒu������
    m_pNameSpace->SetPosition(NAMESPACE_POS.x, NAMESPACE_POS.y, NAMESPACE_POS.z);
    //���O���̓X�y�[�X�̃X�P�[��������
    m_pNameSpace->SetScale(NAMESPACE_SCALE.x, NAMESPACE_SCALE.y, NAMESPACE_SCALE.z);
    //���O���̓X�y�[�X�̕�������
    m_pNameSpace->SetDisplay(NAMESPACE_DISP.x, NAMESPACE_DISP.y);
}

void CCreateAcountScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //���A���^�C�����͏���
    CUtility::GetInstance().InputText(m_UserName,NAME_MAXLENGTH);

    //�R�s�[���t�H���_�̃p�X
    m_SorceDir = "Data\\Acount\\Hero";
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
            }

            //�I�[�v�j���O�V�[����
            m_SceneTransitionFlg = true;
        }
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

