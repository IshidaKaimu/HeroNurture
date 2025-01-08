#include "CNatureScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "SkinMesh\SkinMeshManager\CSkinMeshManager.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "StaticMesh\MeshManager\CMeshManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Scene\CSceneManager.h"
#include "KeyManager\CKeyManager.h"
#include "WriteText\WriteText.h"
#include "Utility\CUtility.h"

CNatureScene::CNatureScene()
    : m_pCamera     ( &CCameraManager::GetInstance() )
    , m_pHero       ( &CHeroManager::GetInstance() )
    , m_Name        ()
    , m_pGround     ()
    , m_pSky        ()
    , m_pParamBack  ()
    , m_pPowerTraning()
    , m_pMagicTraning()
    , m_pSpeedTraning()
    , m_pHpTraning()
    , m_pRest()
    , m_pStaminaGage()
    , m_pStaminaBack()
    , m_GageWidth   ( CSceneManager::GetInstance()->GetStaminaWidth() )
    , m_pJson()
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
    
    //----�X�^�e�B�b�N���b�V���I�u�W�F�N�g----
    //�n��
    m_pGround = std::make_unique<CGround>();
    //�X�J�C�{�b�N�X
    m_pSky    = std::make_unique<CSky>();

    //----UI�I�u�W�F�N�g----
    //�p�����[�^�̔w�i
    m_pParamBack = std::make_unique<CUIObject>();
    //�e��g���[�j���OUI
    m_pPowerTraning = std::make_unique<CUIObject>();
    m_pMagicTraning = std::make_unique<CUIObject>();
    m_pSpeedTraning = std::make_unique<CUIObject>();
    m_pHpTraning    = std::make_unique<CUIObject>();
    m_pRest         = std::make_unique<CUIObject>();

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

    //�p�����[�^�̔w�iUI�̃X�v���C�g�ݒ�
    m_pParamBack->AttachSprite(CUIManager::GetSprite(CUIManager::ParamList));
    //�e��g���[�j���OUI�̃X�v���C�g�ݒ�
    m_pPowerTraning->AttachSprite(CUIManager::GetSprite(CUIManager::PowerTraning));
    m_pMagicTraning->AttachSprite(CUIManager::GetSprite(CUIManager::MagicTraning));
    m_pSpeedTraning->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedTraning));
    m_pHpTraning   ->AttachSprite(CUIManager::GetSprite(CUIManager::HpTraning));
    m_pRest        ->AttachSprite(CUIManager::GetSprite(CUIManager::Rest));

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
   
    //----�p�����[�^�̒l������UI�̏����ݒ�----
    //�p�����[�^�̔w�i
    UIInit(m_pParamBack, PARAMBACK_POSX_N, PARAMBACK_POSY_N, 0, PARAMBACK_SCALE_N, 0);
    //�e��g���[�j���O
    UIInit(m_pPowerTraning, TRANING_POSX_N, TRANING_POSY_N, 0, TRANING_SCALE_N, 0);
    UIInit(m_pMagicTraning, TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 1);
    UIInit(m_pSpeedTraning, TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 2);
    UIInit(m_pHpTraning,    TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 3);
    UIInit(m_pRest,    TRANING_POSX_N, TRANING_POSY_N, TRANING_INTERVAL_N, TRANING_SCALE_N, 4);

    //�琬�֘A�̃V�[���ŋ��ʂ�UI�̏�����
    InitNatureUI(m_pStaminaGage,m_pStaminaBack);
}

//�X�V�֐�
void CNatureScene::Update()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�L�[�}�l�[�W���[
    CKeyManager* KeyMng = CKeyManager::GetInstance();
    //�q�[���[�}�l�[�W���[
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //�V�[���}�l�[�W���[
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̍X�V
    m_pHero->Update();

    //�L�[�}�l�[�W���[�̍X�V����
    CKeyManager::GetInstance()->Update();

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
    if (KeyMng->IsDown(VK_RETURN) && !m_SceneTransitionFlg)
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

        m_SceneTransitionFlg = true;
    }

    if (SceneMng->GetRemainingTurn() <= 0) 
    {
        m_SceneTransitionFlg = true;
    }

    if (m_SceneTransitionFlg && FadeOut())
    {
        if (SceneMng->GetRemainingTurn() > 0)
        {
            SceneMng->LoadCreate(CSceneManager::Training);
        }
        else
        {
            SceneMng->LoadCreate(CSceneManager::NatureResult);
        }
    }

    //�f�o�b�O����
    Debug();
}

//�`��֐�
void CNatureScene::Draw()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�V�[���}�l�[�W���[
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�J�����̍X�V����
    m_pCamera->CameraUpdate();

    //�Z�b�g���ꂽ�q�[���[�̃N���X�̕`��
    m_pHero->Draw();

    //�n�ʃN���X�̕`��
    m_pGround->Draw();

    //�[�x�𖳎�����
    SceneMng->GetDx11()->SetDepth(false);

    //�琬�֘A�V�[���ŋ��ʂ�UI�̕`��
    DrawNatureUI(m_pStaminaGage, m_pStaminaBack);

    //�e�g���[�j���O�̕`��
    DrawTraning();

    //�e�p�����[�^UI�̕`��
    DrawParam();

    //�[�x��߂�
    SceneMng->GetDx11()->SetDepth(true);
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

    //���C�g�}�l�[�W���[
#ifdef DEBUG 
    CLightManager::GetInstance().Debug();
#endif
}

//�琬�֘AUI�̃C���X�^���X����
void CNatureScene::CreateNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�X�^�~�i�Q�[�W
    gage = std::make_unique<CUIObject>();
    //�Q�[�W�w�i
    back = std::make_unique<CUIObject>();
}
//�琬�֘AUI�̃X�v���C�g�f�[�^�̓ǂݍ���
void CNatureScene::LoadNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�X�^�~�i�Q�[�W
    gage->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaGage));
    //�Q�[�W�w�i
    back->AttachSprite(CUIManager::GetSprite(CUIManager::StaminaBack));
}
//�琬�֘AUI�̏�����
void CNatureScene::InitNatureUI(std::unique_ptr<CUIObject>& gage, std::unique_ptr<CUIObject>& back)
{
    //�ǂݍ��݂�����ł���Ȃ�
    if (!CSceneManager::GetInstance()->GetIsDataLoaded())
    {
        //�^�[�����EHP�̒l�̏�����
        //�^�[����
        CSceneManager::GetInstance()->InitTurn();
        gage->SetWidth(1.0f);
        //�X�^�~�i�̏�����
        m_pHero->InitStamina();
    }
    else
    {
        //�X�^�~�i�Ɍ�����̒l���Z�b�g
        m_pHero->SetStamina(m_pHero->GetAfterStamina());
        //���݂̃X�^�~�i�����擾���A�ݒ肷��
        gage->SetWidth(CSceneManager::GetInstance()->GetStaminaWidth());
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
    //�Q�[�W�w�i
    back->Draw();
    //�X�^�~�i�Q�[�W
    gage->Draw();
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

    //����̂ݓǂݍ��ނ��̂�ǂݍ��܂Ȃ�����
    CSceneManager::GetInstance()->SetIsDataLoaded(true);

}

//�e��UI�����ݒ�
void CNatureScene::UIInit(std::unique_ptr<CUIObject>& ui, float x, float y, float interval, D3DXVECTOR3 scale, int no)
{
    //�ʒu
    ui->SetPosition(x + (interval * no), y, 0.0f);
    //�g�k
    ui->SetScale(scale);
    //���l
    ui->SetAlpha(1.0f);
    //���A����
    ui->SetDisplay(1.0f, 1.0f);
}


//�q�[���[���Ƃ̃p�����[�^��������
void CNatureScene::SaveParam()
{
    //�g���[�j���O���s���Ƀp�����[�^�����������ރt�@�C���̊K�w
    std::string ParamFileHierarchy = "Data\\Hero\\Parameter\\";
    //�Z�b�g���ꂽ�q�[���[�̃p�����[�^���̏�������
    m_pJson->SaveNatureData(m_pHero->GetHeroName(), m_ParamWriter, ParamFileHierarchy);
}

//�e��p�����[�^�̕`��
void CNatureScene::DrawParam()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�ėp�N���X
    CUtility* Utility = &CUtility::GetInstance();

    //----�e��p�����[�^��UI�`��(�w�i,�l,�����N)----
    //�w�i
    m_pParamBack->Draw();
    //�ؗ�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Power)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Power,CORRECTION_DIGIT,PARAMVALUE_POSX_N, PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Power, 2, RANK_POSX_N, RANK_POSY_N);
    //����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Magic)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Magic, CORRECTION_DIGIT, PARAMVALUE_POSX_N + PARAMVALUE_INTERVAL_N, PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Magic, 2, RANK_POSX_N + RANK_INTERVAL_N, RANK_POSY_N);
    //�f����
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Speed)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Speed, CORRECTION_DIGIT, PARAMVALUE_POSX_N + (PARAMVALUE_INTERVAL_N * 2), PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Speed, 2, RANK_POSX_N + (RANK_INTERVAL_N * 2), RANK_POSY_N);
    //�̗�
    Text->Draw_Text(std::to_wstring(static_cast<int>(m_pHero->GetParam().Hp)), WriteText::Normal, Utility->PosCorrection(m_pHero->GetParam().Hp, CORRECTION_DIGIT, PARAMVALUE_POSX_N
        + (PARAMVALUE_INTERVAL_N * 3), PARAMVALUE_POSY_N));
    CUtility::GetInstance().DrawRank(m_pHero->GetParam().Hp, 2, RANK_POSX_N + (RANK_INTERVAL_N * 3), RANK_POSY_N);
}

//�e��g���[�j���O�̕`��
void CNatureScene::DrawTraning()
{
    //�I�����ꂽ�Ƃ����ꂼ��̈ʒu���グ��ϐ�
    float PosUp = 20.0f;

    //�ؗ̓g���[�j���O�I����
    if (m_SelectNo == 0) { m_pPowerTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pPowerTraning->SetPositionY(TRANING_POSY_N); }
    //���̓g���[�j���O�I����
    if (m_SelectNo == 1) { m_pMagicTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pMagicTraning->SetPositionY(TRANING_POSY_N); }
    //�f�����g���[�j���O�I����
    if (m_SelectNo == 2) { m_pSpeedTraning->SetPositionY(TRANING_POSY_N  - PosUp); }
    else { m_pSpeedTraning->SetPositionY(TRANING_POSY_N); }
    //�̗̓g���[�j���O�I����
    if (m_SelectNo == 3) { m_pHpTraning->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pHpTraning->SetPositionY(TRANING_POSY_N); }
    //�x���I����
    if (m_SelectNo == 4) { m_pRest->SetPositionY(TRANING_POSY_N - PosUp); }
    else { m_pRest->SetPositionY(TRANING_POSY_N); }

    m_pPowerTraning->Draw();
    m_pMagicTraning->Draw();
    m_pSpeedTraning->Draw();
    m_pHpTraning->Draw();
    m_pRest->Draw();
}

//�c��^�[�����̕`��
void CNatureScene::DrawRemainingTurn()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�ėp�N���X
    CUtility* Utility = &CUtility::GetInstance();
    //�V�[���}�l�[�W���[
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //������wstring�^�ɕϊ�
    std::wstring Turn = std::to_wstring(CSceneManager::GetInstance()->GetRemainingTurn());

    //�c��^�[�����̕`��
    Text->Draw_Text(L"�c��", WriteText::Normal, D3DXVECTOR2(0.0, -20.0));
    Text->Draw_Text(Turn, WriteText::Turn, Utility->PosCorrection(SceneMng->GetRemainingTurn(),2,140,-40.0f));
    Text->Draw_Text(L"�^�[��", WriteText::Normal, D3DXVECTOR2(200.0, -20.0));
}


//�X�^�~�i�Q�[�W�̃A�j���[�V����
void CNatureScene::GageAnim()
{
    //�N���X�̃C���X�^���X��ϐ��ɑ��
    //�V�[���}�l�[�W���[
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //�Q�[�W���̊m�F
    float GageScale = 1.0f * m_pHero->GetStamina() / STAMINA_MAX;

    //�������
    if (GageScale < m_GageWidth) { m_GageWidth -= 0.01f; }
    //�Ⴏ���
    if (GageScale > m_GageWidth){ m_GageWidth += 0.01f; }

    //���݂̃Q�[�W�����V�[���}�l�[�W���̕ϐ��ɑ��
    CSceneManager::GetInstance()->SetStaminaWidth(m_GageWidth);

    //�X�^�~�i�Q�[�W�̕�������ݒ�
    if (SceneMng->GetIsDataLoaded()) {
        m_pStaminaGage->SetDisplay(m_GageWidth, 1.0f);
    }
    else
    {
        //�s���R�ȃQ�[�W�̓������Ȃ���
        m_pStaminaGage->SetDisplay(1.0f, 1.0f);
    }


}
