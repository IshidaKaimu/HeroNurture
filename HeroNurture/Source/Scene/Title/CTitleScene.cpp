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
#include "Light\LightManager\CLightManager.h"
#include <cmath>

//�萔�̖��O���
using namespace Constant_TitleScene;

CTitleScene::CTitleScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pYui    ()
    , m_pKaito  ()
    , m_pSky    ()
    , m_pGround ()
    , m_HeroNo  ()
{
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

    //---------------------------

    
    //----�X�L�����b�V��----
    
    //���C
    m_pYui = std::make_unique<CYui>();
   
    //�J�C�g
    m_pKaito = std::make_unique<CKaito>();
    
    //----------------------

    //----UI----
   
    //�I����
    m_pSelectArrow = std::make_unique<CUIObject>();

    //----------
}

void CTitleScene::Releace()
{
    m_pCamera = nullptr;
}

void CTitleScene::LoadData()
{
    CMeshManager* MeshMng = CMeshManager::GetInstance();
    CUIManager* UiMng = &CUIManager::GetInstance();
    //----�X�^�e�B�b�N���b�V��----
  
    //�n��
    m_pGround->AttachMesh(MeshMng->GetMesh(CMeshManager::Ground));
   
    //----------------------------

    //----�^�C�g����ʂɕ\������q�[���[�̃��b�V���ݒ�----
    
     //���C
    m_pYui->LoadMeshData();  

    //�J�C�g
    m_pKaito->LoadMeshData();    
    
    //----------------------------------------------------

    //----UI----

    //�I�������
    m_pSelectArrow->AttachSprite(UiMng->GetSprite(CUIManager::SelectArrow)); 

    //----------
}

void CTitleScene::Initialize()
{
    //�J�����̏����ʒu
    m_pCamera->SetPos(CAM_POS);
    m_pCamera->SetLook(CAM_LOOK);

    //�ǂ���̃q�[���[��\�����邩�A�����Őݒ�
    m_HeroNo = CUtility::GetInstance().GenerateRandomValue(0,1);

    //�ݒ肳�ꂽ�q�[���[�̏�����
    switch (m_HeroNo)
    {
    case 0:
        m_pYui->Initialize();
        m_pYui->SetPosition(YUI_POS);
        m_pYui->SetRotation(YUI_ROT);
        break;
    case 1:
        m_pKaito->Initialize();
        m_pKaito->SetPosition(KAITO_POS);
        m_pKaito->SetRotation(KAITO_ROT);
        break;
    default:
        break;
    }

    //�I�������̏����ݒ�
    m_pSelectArrow->SetPosition(SELECTARROW_POS);                       //���W
    m_pSelectArrow->SetScale(SELECTARROW_SCALE);                        //�g�k
    m_pSelectArrow->SetDisplay(SELECTARROW_DISP.x, SELECTARROW_DISP.y); //��
}

//�X�V�֐�
void CTitleScene::Update()
{   
    CSceneManager* SceneMng = &CSceneManager::GetInstance();
    CKeyManager* KeyMng     = &CKeyManager::GetInstance();

    KeyMng->Update();

    //���[�h�I��BGM���~
    CSoundManager::GetInstance()->Stop(CSoundManager::BGM_ModeSelect);

    //�^�C�g��BGM�̍Đ�
    CSoundManager::GetInstance()->PlayLoop(CSoundManager::BGM_Title);
    CSoundManager::GetInstance()->Volume(CSoundManager::BGM_Title, 40);

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�I����̓���
    MoveArrow();

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
        switch (m_SelectNo)
        {
        case 0: SceneMng->LoadCreate(CSceneManager::CreateAcount); break;
        case 1: SceneMng->LoadCreate(CSceneManager::Login);        break;
        case 2: DestroyWindow(SceneMng->GetWnd());                 break;
        default:                                                   break;
        }
    }

    #ifdef DEBUG
        //�f�o�b�O����
        Debug();
    #endif
}

void CTitleScene::Draw()
{
    //�J�����̓���
    m_pCamera->CameraUpdate();

    //�n�ʂ̕`��
    m_pGround->Draw();


    //�e�q�[���[�̕`��,�A�j���[�V����
    switch (m_HeroNo)
    {
    case 0:
        //���C
        m_pYui->MoveSelectAnim();
        m_pYui->Draw();
        break;
    case 1:
        //�J�C�g
        m_pKaito->MoveSelectAnim();
        m_pKaito->Draw();
        break;
    }

    //��̕`��
    DrawSky();

    //UI
    DrawUI();

}

void CTitleScene::Debug()
{
#ifdef DEBUG
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    ImGui::InputFloat3(JAPANESE("�J�C�g���W"), m_KaitoPos);
    ImGui::InputFloat3(JAPANESE("���C���W"), m_YuiPos);
    ImGui::InputFloat3(JAPANESE("�J�C�g��]"), m_KaitoRot);
    ImGui::InputFloat3(JAPANESE("���C��]"), m_YuiRot);
    //CCameraManager::GetInstance().SetPos(m_CamPos);
    //CCameraManager::GetInstance().SetLook(m_CamLook);
    m_pKaito->SetPosition(m_KaitoPos);
    m_pYui->SetPosition(m_YuiPos);
    m_pKaito->SetRotation(m_KaitoRot);
    m_pYui->SetRotation(m_YuiRot);
    ImGui::End();

#endif // DEBUG
}

//�^�C�g����ʂ̕`��
void CTitleScene::DrawUI()
{
    WriteText* Text = WriteText::GetInstance();

    //�I����
    m_pSelectArrow->SetPosition(SELECTARROW_POS.x + m_MoveArrow, SELECTARROW_POS.y + (SELECT_INTERVAL * m_SelectNo), SELECTARROW_POS.z);

    //�I����̕`��
    m_pSelectArrow->Draw();

    //�^�C�g��
    Text->Draw_Text(L"HeroNurture", WriteText::B_Big, D3DXVECTOR2(TITLE_POS)); 
    //�u�A�J�E���g�쐬�v�e�L�X�g
    Text->Draw_Text(L"�A�J�E���g�쐬", WriteText::Select, D3DXVECTOR2(SELECT_POS));
    //�u���O�C���v�e�L�X�g
    Text->Draw_Text(L"���O�C��", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL));
    //�u�Q�[���I���v�e�L�X�g
    Text->Draw_Text(L"�Q�[���I��", WriteText::Select, D3DXVECTOR2(SELECT_POS.x,SELECT_POS.y + SELECT_INTERVAL*2));
}

//���̓���
void CTitleScene::MoveArrow()
{
    CKeyManager* KeyMng = &CKeyManager::GetInstance();
    //�I�����ړ�
    if (KeyMng->IsDown('S'))
    {

        if (m_SelectNo < 2)
        {
            //�I��SE�̍Đ�
            CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
            CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

            m_SelectNo++;
        }
        else
        {
            m_SelectNo = 2;
        }
    }

    if (KeyMng->IsDown('W'))
    {

        if (m_SelectNo > 0)
        {
            //�I��SE�̍Đ�
            CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Select);
            CSoundManager::GetInstance()->Volume(CSoundManager::SE_Select, 40);

            m_SelectNo--;
        }
        else
        {
            m_SelectNo = 0;
        }
    }


    if (m_MoveArrow <= SELECTARROW_RANGE && !m_SwitchArrowFlag)
    {
        m_MoveArrow += 0.1f;
    }
    else
    {
        m_SwitchArrowFlag = true;
    }

    if (m_SwitchArrowFlag)
    {
        if (m_MoveArrow >= 0.0f)
        {
            m_MoveArrow -= 0.1f;
        }
        else
        {
            m_SwitchArrowFlag = false;
        }
    }

}
