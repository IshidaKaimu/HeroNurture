#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Json\CJson.h"
#include "Utility\CUtility.h"

CNatureScene::CNatureScene()
    : m_pCamera     ( &CCameraManager::GetInstance() )
    , m_pHero       ( &CHeroManager::GetInstance() )
    , m_pJson       ()
    , m_Name        ()
    , m_pGround     ()
    , m_pSky        ()
    , m_pParamBack  ()
    //, m_pPowerParam ()
    //, m_pMagicParam ()
    //, m_pSpeedParam ()
    //, m_pHpParam    ()
    , m_pStaminaGage()
    , m_pStaminaBack()
    , m_GageWidth   ( CSceneManager::GetInstance()->GetStaminaWidth() )
    , m_ParamWriter ()
    , m_ParamData   ()
{
}

CNatureScene::~CNatureScene()
{
}

//�\�z�֐�
void CNatureScene::Create()
{
    //----�C���X�^���X����----
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃C���X�^���X����
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pHero->SetHero(CHeroManager::Yui);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Yui);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pHero->SetHero(CHeroManager::Kaito);
        //�t�@�C���̍쐬�A�ǂݍ���
        LoadHeroData(m_Name.Kaito);
        break;
    default:
        break;
    }
    
    //�X�^�e�B�b�N���b�V���I�u�W�F�N�g
    //�n��
    m_pGround = std::make_unique<CGround>();
    //�X�J�C�{�b�N�X
    m_pSky    = std::make_unique<CSky>();

    //UI�I�u�W�F�N�g
    //----�e�p�����[�^----
    // 
    m_pParamBack = std::make_unique<CUIObject>();

    ////�ؗ�
    //m_pPowerParam = std::make_unique<CUIObject>();
    ////����
    //m_pMagicParam = std::make_unique<CUIObject>();
    ////�f����
    //m_pSpeedParam = std::make_unique<CUIObject>();
    ////�̗�
    //m_pHpParam    = std::make_unique<CUIObject>();
    
    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI�̃C���X�^���X����
    CreateNatureUI(m_pStaminaGage,m_pStaminaBack);
}

//�j���֐�
void CNatureScene::Releace()
{
    //----�j��----
    //�J����
    m_pCamera = nullptr;
    //�q�[���[�}�l�[�W���[
    m_pHero   = nullptr;
}


//�f�[�^�ǂݍ��݊֐�
void CNatureScene::LoadData()
{   
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃��b�V���f�[�^�̓ǂݍ���
    CHeroManager::GetInstance().LoadMeshData();

    CHeroManager::GetInstance().LoadParamData(m_ParamData);

    //�n�ʂ̃��b�V���f�[�^�ݒ�
    m_pGround->LoadData();

    //----�e�p�����[�^��UI�̃X�v���C�g�ݒ�----
    // 
    m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ParamList));
    ////�ؗ�
    //m_pPowerParam->AttachSprite(CUIManager::GetSprite(CUIManager::PowerParam));
    ////����
    //m_pMagicParam->AttachSprite(CUIManager::GetSprite(CUIManager::MagicParam));
    ////�f����
    //m_pSpeedParam->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedParam));
    ////�̗�
    //m_pHpParam->AttachSprite(CUIManager::GetSprite(CUIManager::HpParam));

    //�X�^�~�i�Q�[�W��UI�̃X�v���C�g�ݒ�
    LoadNatureUI(m_pStaminaGage, m_pStaminaBack);

}

//�������֐�
void CNatureScene::Initialize()
{
    //�Z�b�g���ꂽ�q�[���[�̃N���X�̏�����
    m_pHero->Initialize();

    //�e�q�[���[�̃J�����ʒu�A�J�����̒����_�̐ݒ�
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        m_pCamera->SetPos (CAMERAPOS_YUI);
        m_pCamera->SetLook(CAMERALOOK_YUI);
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        m_pCamera->SetPos (CAMERAPOS_KAITO);
        m_pCamera->SetLook(CAMERALOOK_KAITO);
        break;
    default:
        break;
    }

    //----���C�g���----
    //�ʒu
    m_Light.Position   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    //����
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
   
    //----�e��p�����[�^UI�̏����ݒ�----
    ////�ؗ�
    ParamUIInit(m_pParamBack, 1);
    ////����
    //ParamUIInit(m_pMagicParam, 2);
    ////�f����
    //ParamUIInit(m_pSpeedParam, 3);
    ////�̗�
    //ParamUIInit(m_pHpParam, 4);

    //�琬�֘A�̃V�[���ŋ��ʂ�UI�̏�����
    InitNatureUI(m_pStaminaGage,m_pStaminaBack);
}

//�X�V�֐�
void CNatureScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    m_pHero->Update();

    //�L�[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CKeyManager* KeyMng = CKeyManager::GetInstance();

    //�L�[�}�l�[�W���[�̍X�V����
    CKeyManager::GetInstance()->Update();

    //�q�[���[�}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�ؗ̓g���[�j���O
    //�J�[�\���̈ړ�
    if (KeyMng->IsDown(VK_RIGHT))
    {
        //�L�[���͂őI����i�߂�
        if (m_SelectNo < CHeroManager::enTraningList::Max_T-1) { m_SelectNo++; }
        else { m_SelectNo = 0; }
    }
    else if (KeyMng->IsDown(VK_LEFT))
    {
        if (m_SelectNo > 0) { m_SelectNo--; }
        else { m_SelectNo = 4; }
    }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̃A�j���[�V����
    m_pHero->NatureAnimation(m_SelectNo);


    //�g���[�j���O�̌���
    if (KeyMng->IsDown(VK_RETURN))
    {
        //�I�����̈ʒu�ɉ������g���[�j���O���Z�b�g
        switch (m_SelectNo)
        {
        case 0:  m_pHero->SetTraning(CHeroManager::PowerTraining); break;
        case 1:  m_pHero->SetTraning(CHeroManager::MagicTraining); break;
        case 2:  m_pHero->SetTraning(CHeroManager::SpeedTraining); break;
        case 3:  m_pHero->SetTraning(CHeroManager::HpTraining); break;
        case 4:  m_pHero->SetTraning(CHeroManager::Rest); break;
        }
        //�p�����[�^����
        SelectTraning();
    }

    //�f�o�b�O����
    Debug();
}

//�`��֐�
void CNatureScene::Draw()
{
    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    CHeroManager::GetInstance().Draw();

    //�n�ʃN���X�̕`��
    m_pGround->Draw();

    //�琬�֘A�V�[���ŋ��ʂ�UI�̕`��
    DrawNatureUI( m_pStaminaGage, m_pStaminaBack);

    //�e�p�����[�^UI�̕`��
    DrawParam();
}

void CNatureScene::Debug()
{
#ifdef DEBUG 
    ImGui::Begin(JAPANESE("�J����"));
    ImGui::InputFloat3(JAPANESE("�J�������W"), m_CamPos);
    ImGui::InputFloat3(JAPANESE("�����_"), m_CamLook);
    CCameraManager::GetInstance().SetPos(m_CamPos);
    CCameraManager::GetInstance().SetLook(m_CamLook);
    ImGui::End();
#endif

#ifdef _DEBUG 
    ImGui::Begin(JAPANESE("�p�����[�^"));
    ImGui::Text(JAPANESE("�ؗ�:%f"), m_pHero->GetParam().Power);
    ImGui::Text(JAPANESE("����:%f"), m_pHero->GetParam().Magic);
    ImGui::Text(JAPANESE("�f����:%f"), m_pHero->GetParam().Speed);
    ImGui::Text(JAPANESE("�̗�:%f"), m_pHero->GetParam().Hp);
    ImGui::Text(JAPANESE("�X�^�~�i:%f"), m_pHero->GetStamina());
    ImGui::Text(JAPANESE("�X�^�~�i�̕�:%f"), CSceneManager::GetInstance()->GetStaminaWidth());
    ImGui::End();

    ImGui::Begin(JAPANESE("�g���[�j���O�I����"));
    if (m_SelectNo == 0) { ImGui::Text(JAPANESE("�ؗ�")); }
    if (m_SelectNo == 1) { ImGui::Text(JAPANESE("����")); }
    if (m_SelectNo == 2) { ImGui::Text(JAPANESE("�f����")); }
    if (m_SelectNo == 3) { ImGui::Text(JAPANESE("�̗�")); }
    if (m_SelectNo == 4) { ImGui::Text(JAPANESE("�x��")); }
    ImGui::End();
#endif
}

// =======================
// �琬�֘A�̃V�[���ŌŒ肷��UI�֘A�̊֐�
// =======================		
//�C���X�^���X����
void CNatureScene::CreateNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�X�^�~�i�Q�[�W
    gage = std::make_unique<CUIObject>();
    //�Q�[�W�w�i
    back = std::make_unique<CUIObject>();
}
//�X�v���C�g�f�[�^�̓ǂݍ���
void CNatureScene::LoadNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�X�^�~�i�Q�[�W
    gage->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaGage));
    //�Q�[�W�w�i
    back->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaBack));
}
//������
void CNatureScene::InitNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�ǂݍ��݂�����ł���Ȃ�
    if (!CSceneManager::GetInstance()->GetIsDataLoaded())
    {
        //�^�[�����EHP�̒l�̏�����
        //�^�[����
        CSceneManager::GetInstance()->InitTurn();
        //�X�^�~�i�Q�[�W�̕�
        CSceneManager::GetInstance()->InitStaminaWidth();
        //�X�^�~�i�̏�����
        m_pHero->InitStamina();
    }
    else
    {
        //�X�^�~�i�Ɍ�����̒l���Z�b�g
        m_pHero->SetStamina(m_pHero->GetAfterStamina());
        //���݂̃X�^�~�i�����擾���A�ݒ肷��
        m_pStaminaGage->SetWidth(CSceneManager::GetInstance()->GetStaminaWidth());
    }

    //�g�k
    gage->SetScale(1.0f, 1.0f, 1.0f);     //�Q�[�W
    back->SetScale(1.0f, 1.0f, 1.0f);     //�Q�[�W�w�i
    //�ʒu
    gage->SetPosition(350.0f, 0.0f, 0.0f);//�Q�[�W
    back->SetPosition(350.0f, 0.0f, 0.0f);//�Q�[�W�w�i
    //�Q�[�W�w�i�̕�
    back->SetDisplay(1.0f, 1.0f);
}
//�`��
void CNatureScene::DrawNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�X�^�~�i�Q�[�W�̃A�j���[�V����
    GageAnim();

    CSceneManager::GetInstance()->GetDx11()->SetDepth(false);
    //�Q�[�W�w�i
    back->Draw();
    //�X�^�~�i�Q�[�W
    gage->Draw();
    CSceneManager::GetInstance()->GetDx11()->SetDepth(true);

    //�c��^�[�����̕`��
    DrawRemainingTurn();
}

//�e�q�[���[�̃f�[�^�ǂݍ���
void CNatureScene::LoadHeroData( const std::string& heroname )
{
    //�ǂݍ��ރt�@�C���̃p�X
    //����̓ǂݍ��ݎ��ɓǂݍ��ޏ����X�e�[�^�X�t�@�C��
    std::string InitFilePath = "Data\\Hero\\HeroData";
    //�p�����[�^���X�V���ɓǂݍ��ރt�@�C��
    std::string ParamFilePath = "Data\\Hero\\Parameter\\" + heroname;

    //json�ɕۑ����ꂽ�f�[�^�̓ǂݍ���
    //�ǂݍ��݉񐔂ɉ����ēǂݍ��ރt�@�C����ς���
    if (!CSceneManager::GetInstance()->GetIsDataLoaded()) 
    {
        //����̓ǂݍ��ݎ�
        if (!m_pJson->Load(m_ParamData, InitFilePath)) { return; }
    }
    else
    {
        //2�x�ڈȍ~�̓ǂݍ��ݎ�
        if (!m_pJson->Load(m_ParamData, ParamFilePath)) { return; }
    }
}

//�g���[�j���O�I������
void CNatureScene::SelectTraning()
{
    //�V�[���}�l�[�W���̃C���X�^���X��ϐ��ɑ��
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�X�V�O�̃p�����[�^��ۑ�
     m_pHero->SetBeforeParam(m_pHero->GetParam());
    //�X�V�O�̃X�^�~�i��ۑ�
     m_pHero->SetBeforeStamina(m_pHero->GetStamina());

    //���ꂼ��̃p�����[�^�̑���
    switch (m_pHero->GetTraining())
    {
    //�ؗ�
    case::CHeroManager::PowerTraining: m_pHero->PowerUp(m_pHero->GetStamina()); break;
    //����
    case::CHeroManager::MagicTraining: m_pHero->MagicUp(m_pHero->GetStamina()); break;
    //�f����
    case::CHeroManager::SpeedTraining: m_pHero->SpeedUp(m_pHero->GetStamina()); break;
    //�̗�
    case::CHeroManager::HpTraining: m_pHero->HpUp(m_pHero->GetStamina()); break;
    //�x��
    case::CHeroManager::Rest: SceneMng->SetRestFlag(true); break;
    }

    //�X�^�~�i�̌����܂��͉�
    //�x���t���O�������Ă��Ȃ���Ό���
    if (!SceneMng->GetRestFlag()) { m_pHero->ReduceStamina(); }
    else { m_pHero->StaminaRecovery(); }

    //�X�V��p�����[�^�̕ۑ�
    SaveParam();

    //�^�[���o�ߏ���
    SceneMng->TurnProgress();

    //����̂ݓǂݍ��ނ��̂�ǂݍ��܂Ȃ�����
    CSceneManager::GetInstance()->SetIsDataLoaded(true);

    SceneMng->LoadCreate(CSceneManager::Training);
}

//�q�[���[���Ƃ̃p�����[�^��������
void CNatureScene::SaveParam()
{
    //�q�[���[���Ƃ̃p�����[�^���̏�������
    switch (m_pHero->GetSelectHero())
    {
    case CHeroManager::Yui:
        //���C
        WriteParam("Yui");
        break;
    case CHeroManager::Kaito:
        //�J�C�g
        WriteParam("Kaito");
        break;
    default:
        break;
    }
}

//�p�����[�^���̏�������
void CNatureScene::WriteParam(const std::string& heroname)
{
    //�������ޏ��̊i�[
    //----�p�����[�^----
    m_ParamWriter["Name"] = heroname;
    m_ParamWriter["Parameter"]["Power"] = m_pHero->GetParam().Power;
    m_ParamWriter["Parameter"]["Magic"] = m_pHero->GetParam().Magic;
    m_ParamWriter["Parameter"]["Speed"] = m_pHero->GetParam().Speed;
    m_ParamWriter["Parameter"]["Hp"]    = m_pHero->GetParam().Hp;
    //----�K����----
    m_ParamWriter["Appropriate"]["Power"] = m_pHero->GetApp().PowerApp;
    m_ParamWriter["Appropriate"]["Magic"] = m_pHero->GetApp().MagicApp;
    m_ParamWriter["Appropriate"]["Speed"] = m_pHero->GetApp().SpeedApp;
    m_ParamWriter["Appropriate"]["Hp"]    = m_pHero->GetApp().HpApp;

    //�t�@�C���ɏ�������
    m_pJson->CreateOrWrite("Data\\Hero\\Parameter\\", m_ParamWriter);
}


//�e��p�����[�^UI�����ݒ�
void CNatureScene::ParamUIInit(std::unique_ptr<CUIObject>& param, int no)
{
    //�ʒu
    param->SetPosition(PARAM_POSX * no, PARAM_POSY, 0.0f);
    //�g�k
    param->SetScale(0.8f, 0.8f, 0.8f);
    //���l
    param->SetAlpha(1.0f);
    //���A����
    param->SetDisplay(1.0f, 1.0f);
}

//�e��p�����[�^�̕`��
void CNatureScene::DrawParam()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();

    //----�e��p�����[�^��UI�`��(�w�i,�l,�����N)----
    //�w�i
    m_pParamBack->Draw();
    //�ؗ�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Power)), WriteText::Normal, PosCorrection(m_pHero->GetParam().Power,PARAM_POSX * 1.35f,PARAMVALUE_POSY));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Power, 2,PARAM_POSX * 1, PARAMVALUE_POSY);
    //����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Magic)), WriteText::Normal, PosCorrection(m_pHero->GetParam().Magic, PARAM_POSX * 2.35f, PARAMVALUE_POSY));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Magic, 2, PARAM_POSX * 2, PARAMVALUE_POSY);
    //�f����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Speed)), WriteText::Normal, PosCorrection(m_pHero->GetParam().Speed, PARAM_POSX * 3.35f, PARAMVALUE_POSY));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Speed, 2, PARAM_POSX * 3, PARAMVALUE_POSY);
    //�̗�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Hp)), WriteText::Normal, PosCorrection(m_pHero->GetParam().Hp, PARAM_POSX * 4.35f, PARAMVALUE_POSY));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Hp, 2, PARAM_POSX * 4, PARAMVALUE_POSY);
}

//�p�����[�^�̒l�`�掞�̌����ɂ��ʒu�␳
D3DXVECTOR2 CNatureScene::PosCorrection(float value, float x, float y)
{
    //����(�l�𕶎���ɕϊ����Č������擾)
    int DigitCount = static_cast<int>(std::to_wstring(static_cast<int>(value)).length());
    //�����ɉ������␳
    float OffsetX = (DigitCount == 3) ? -30.0f : 0.0f;

    return D3DXVECTOR2( x + OffsetX, y );
}

//�c��^�[�����̕`��
void CNatureScene::DrawRemainingTurn()
{
    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��", WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn, WriteText::Turn, D3DXVECTOR2(110.0, -30.0));
    Text->Draw_Text(L"�^�[��", WriteText::Normal, D3DXVECTOR2(160.0, -20.0));
}


//�X�^�~�i�Q�[�W�̃A�j���[�V����
void CNatureScene::GageAnim()
{
    //�Q�[�W���̊m�F
    float GageScale = 1.0f * m_pHero->GetStamina() / STAMINA_MAX;

    //�������
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //�Ⴏ���
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //���݂̃Q�[�W�����V�[���}�l�[�W���̕ϐ��ɑ��
    CSceneManager::GetInstance()->SetStaminaWidth(m_GageWidth);

    //�X�^�~�i�Q�[�W�̕�������ݒ�
    m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);

}
