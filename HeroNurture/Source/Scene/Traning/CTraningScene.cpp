#include "CTraningScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "ModeManager\Nurture\CNurtureManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "Sound\CSoundManager.h"

//�萔�̖��O���
using namespace Constant_TraningScene;


CTraningScene::CTraningScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_pBack   ()
    , m_TextNo  ()
    , m_pTextBox()
    , m_TextEnd ()
{
}

CTraningScene::~CTraningScene()
{
}

//�\�z�֐�
void CTraningScene::Create()
{
    //----�C���X�^���X����----
    //�X�^�e�B�b�N���b�V���I�u�W�F�N�g
    //��
    m_pSky = make_unique<CSky>();
    //�n��
    m_pGround = make_unique<CGround>();

    //UI�I�u�W�F�N�g
    //�w�i
    m_pBack = make_unique<CUIObject>();
    //�e�L�X�g�{�b�N�X
    m_pTextBox = make_unique<CUIObject>();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃C���X�^���X����
    CNurtureScene::CreateNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);
    //-------------------------
}
//�j���֐�
void CTraningScene::Releace()
{
}
//�f�[�^�ǂݍ��݊֐�
void CTraningScene::LoadData()
{
    WriteText* Text             = WriteText::GetInstance();
    CHeroManager* HeroMng       = &CHeroManager::GetInstance();
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();

    //�n�ʂ̃��b�V���f�[�^�ݒ�
    m_pGround->LoadData();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃X�v���C�g�f�[�^�ݒ�
    CNurtureScene::LoadNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);

    //�g���[�j���O���Ƃ̔w�iUI�̃X�v���C�g�f�[�^�ݒ�
    switch (HeroMng->GetTraining())
    {
    case CHeroManager::PowerTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::PowerBack));break;
    case CHeroManager::MagicTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::MagicBack));break;
    case CHeroManager::SpeedTraining: m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::SpeedBack));break;
    case CHeroManager::HpTraining:    m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::HpBack));break;
    case CHeroManager::Rest:          m_pBack->AttachSprite(CUIManager::GetSprite(CUIManager::RestBack));break;
    default:  break;
    }

    //�e�L�X�g�{�b�N�X�̃X�v���C�g�f�[�^�ݒ�
    m_pTextBox->AttachSprite(CUIManager::GetSprite(CUIManager::TextBox)); 

}
//�������֐�
void CTraningScene::Initialize()
{
    CSceneManager::GetInstance().InitWhiteFade();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI
    CNurtureScene::InitNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame, m_pTurnBack);

    //�w�i�摜�̐ݒ�
    m_pBack->SetPosition(0.0f, 0.0f, 0.0f);
    m_pBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pBack->SetDisplay(1.0f, 1.0f);

    //�e�L�X�g�{�b�N�X�̐ݒ�
    m_pTextBox->SetPosition(30.0f, 580.0f, 0.0f);
    m_pTextBox->SetScale(1.0f, 0.7f, 1.0f);
    m_pTextBox->SetDisplay(1.0f, 1.0f);

    //�e�L�X�g�I���t���O�̏�����
    m_TextEnd = false;
}

//�X�V�֐�
void CTraningScene::Update()
{
    CNurtureManager* NurtureMng = &CNurtureManager::GetInstance();
    CSceneManager*   SceneMng   = &CSceneManager::GetInstance();
    CKeyManager*     KeyMng     = &CKeyManager::GetInstance();

    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

   //�L�[�}�l�[�W���[�̍X�V����
   KeyMng->Update();


   //�X�e�[�^�X�ω�SE�̍Đ�
   if (CHeroManager::GetInstance().GetFailureFlag()) {
       m_SECnt++;
       if (m_SECnt == PLAY_SE_CNT)
       {
           CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Miss);
           CSoundManager::GetInstance()->Volume(CSoundManager::SE_Miss, SE_VOLUME);
       }
   }
   else
   {
       m_SECnt++;
       if (m_SECnt == PLAY_SE_CNT)
       {
           CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Up);
           CSoundManager::GetInstance()->Volume(CSoundManager::SE_Up, SE_VOLUME);
       }
   }


   //�e�L�X�g�̕`���i�߂�
   if (KeyMng->IsDown(VK_RETURN))
   {
       //����SE�̍Đ�
       CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Enter);
       CSoundManager::GetInstance()->Volume(CSoundManager::SE_Enter, SE_VOLUME);

       if (m_TextNo < m_ParamInc.size() - 1)
       {
           m_TextNo++;
       }
       else
       {
           //�K�v�ȃe�L�X�g�̕`�悪�I������΃V�[����߂�
           m_TextEnd = true;
       }
   }

   //�㏸�����p�����[�^�̃e�L�X�g��ǉ�
   AddText();

#if DEBUG
   ImGui::Begin(JAPANESE("�e�L�X�g�̔ԍ�"));
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_TextNo);
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_ParamInc.size());
   ImGui::Text(JAPANESE("m_Stamina:%f"),CHeroManager::GetInstance().GetStamina());
   ImGui::Text(JAPANESE("�X�^�~�i�Q�[�W�̕�:%f"),CSceneManager::GetInstance()->GetStaminaWidth());
   ImGui::End();
#endif

   //�e�L�X�g�̕`�悪�S�ďI��莟��V�[���J��
    if (m_TextEnd)
    {
        m_SceneTransitionFlg = true;
    }

   //�t�F�[�h���I��莟��V�[���J��
   if (m_SceneTransitionFlg && FadeOut())
   {
       //�x���t���O�������Ă�����~�낷
       if (NurtureMng->GetRestFlag()) { NurtureMng->SetRestFlag(false); }
       //�^�[���o�ߏ���
       NurtureMng->TurnProgress();
       SceneMng->LoadCreate(CSceneManager::Nurture);
       m_SECnt = 0;
   }
}
//�`��֐�
void CTraningScene::Draw()
{
    CSceneManager* SceneMng = &CSceneManager::GetInstance();

    m_pGround->Draw();

    //�e�g���[�j���O�w�iUI�̕`��
    m_pBack->Draw();
    
    //�[�x�𖳎�����
    SceneMng->GetDx11()->SetDepth(false);

    //�㏸�ʃe�L�X�g�̕`��
    DrawTraningText();

    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI
    CNurtureScene::DrawNurtureUI(m_pStaminaGauge,m_pStaminaBack,m_pStaminaFrame,m_pTurnBack);

    //�[�x��߂�
    SceneMng->GetDx11()->SetDepth(true);

}

//�z��Ƀe�L�X�g��ǉ�����֐�
void CTraningScene::AddText()
{
    WriteText* Text = WriteText::GetInstance();
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----���ꂼ��̃p�����[�^���ω����Ă����ꍇ�̏������Ə㏸�ʁE�����ʂ̌v�Z----
    //�ؗ�
    bool IsPowerUp = Hero->GetBeforeParam().Power < Hero->GetParam().Power;             //�㏸
    bool IsPowerDown = Hero->GetBeforeParam().Power > Hero->GetParam().Power;           //����
    float PowerInc = std::abs(Hero->GetParam().Power - Hero->GetBeforeParam().Power);   //�㏸��
    //����
    bool IsMagicUp = Hero->GetBeforeParam().Magic < Hero->GetParam().Magic;             //�㏸
    bool IsMagicDown = Hero->GetBeforeParam().Magic > Hero->GetParam().Magic;           //����
    float MagicInc = std::abs(Hero->GetParam().Magic - Hero->GetBeforeParam().Magic);   //�㏸��
    //�f����
    bool IsSpeedUp = Hero->GetBeforeParam().Speed < Hero->GetParam().Speed;             //�㏸
    bool IsSpeedDown = Hero->GetBeforeParam().Speed > Hero->GetParam().Speed;           //����
    float SpeedInc = std::abs(Hero->GetParam().Speed - Hero->GetBeforeParam().Speed);   //�㏸��
    //�̗�
    bool IsHpUp = Hero->GetBeforeParam().Hp < Hero->GetParam().Hp;             //�㏸
    bool IsHpDown = Hero->GetBeforeParam().Hp > Hero->GetParam().Hp;           //����
    float HpInc = std::abs(Hero->GetParam().Hp - Hero->GetBeforeParam().Hp);   //�㏸��
    //�X�^�~�i
    bool IsRecoveryStamina = Hero->GetBeforeStamina() <= Hero->GetStamina();   //�㏸
    bool IsReduceStamina = Hero->GetBeforeStamina() >= Hero->GetStamina();     //����
    float StaminaInc = std::abs(Hero->GetStamina() - Hero->GetBeforeStamina());//�㏸��

    //�����𖞂����Ă���΍\���̔z��Ɋi�[                                   �@�@�@�@�@�@�@�@�@�@�@�p�����[�^��,�㏸��
    if ((IsPowerUp || IsPowerDown) && !AlreadyAddCheck(L"�ؗ͂�")) { m_ParamInc.push_back({ L"�ؗ͂�",static_cast<int>(PowerInc), IsPowerUp ? L"�㏸����" : L"��������"}); }
    if ((IsMagicUp || IsMagicDown) && !AlreadyAddCheck(L"���͂�")) { m_ParamInc.push_back({ L"���͂�",static_cast<int>(MagicInc), IsMagicUp ? L"�㏸����" : L"��������" }); }
    if ((IsSpeedUp || IsSpeedDown) && !AlreadyAddCheck(L"�f������")) { m_ParamInc.push_back({ L"�f������",static_cast<int>(SpeedInc), IsSpeedUp ? L"�㏸����" : L"��������" }); }
    if ((IsHpUp || IsHpDown) && !AlreadyAddCheck(L"�̗͂�")) { m_ParamInc.push_back({ L"�̗͂�",static_cast<int>(HpInc), IsHpUp ? L"�㏸����" : L"��������" }); }
    if ((IsRecoveryStamina || IsReduceStamina) && !AlreadyAddCheck(L"�X�^�~�i��")) { m_ParamInc.push_back({ L"�X�^�~�i��",static_cast<int>(StaminaInc), IsRecoveryStamina ? L"�񕜂���" : L"��������" }); }
}

//�z��ɒǉ��ς݂łȂ������ׂ�֐�
bool CTraningScene::AlreadyAddCheck(std::wstring paramname)
{
    //���ɒǉ����Ă��Ȃ����̊m�F
    bool AlreadyAdd = std::any_of(m_ParamInc.begin(), m_ParamInc.end(), [&](IncParam param) { return param.ParamName == paramname; });
    
    //�ǉ��ς݂ł����true
    if(AlreadyAdd)
    {
        return true;
    }  
    return false;
}

//�g���[�j���O���ʃe�L�X�g�̕`��
void CTraningScene::DrawTraningText()
{
    WriteText*       Text          = WriteText::GetInstance();
    CHeroManager*    HeroMng       = &CHeroManager::GetInstance();
    CSceneManager*   SceneMng      = &CSceneManager::GetInstance();
    CNurtureManager* NurtureMng    = &CNurtureManager::GetInstance();

    //���s�������ǂ����ɂ���ĕԂ��e�L�X�g��ς���
    std::wstring ResultText = HeroMng->GetFailureFlag() ? L"���s..." : L"����!";

    //�听�����̃e�L�X�g
    std::wstring GreatSuccessText = L"�听��!!";

    //���s
    bool Failure = HeroMng->GetFailureFlag();

    //�听��
    bool GreatSuccess = HeroMng->GetGreatSuccessFlag();

    //�x��
    bool Rest = NurtureMng->GetRestFlag();


    //�e�L�X�g�{�b�N�X�̕`��
    m_pTextBox->Draw();

    //�x�e���I������Ă��Ȃ��ꍇ
    if (!Rest)
    {
        //�g���[�j���O����
        if (!Failure)
        {
            if (!GreatSuccess)
            {
                //�u����!�v�̃e�L�X�g�`��
                Text->Draw_Text(ResultText, WriteText::Success, RESULTTEXT_OFFSET);
            }
            else
            {
                //�u�听��!!�v�̃e�L�X�g�`��
                Text->Draw_Text(GreatSuccessText, WriteText::GreatSuccess, RESULTTEXT_OFFSET);
            }
        }
        else
        {
            //�u���s...�v�̃e�L�X�g�`��
            Text->Draw_Text(ResultText, WriteText::Failure, RESULTTEXT_OFFSET);
        }
    }

    //�e�L�X�g�ԍ����z��𒴂��Ă��Ȃ����
    if (m_TextNo < m_ParamInc.size())
    {
        DrawParamChange(m_ParamInc[m_TextNo]);
    }
}

//�p�����[�^�ω��̕`�揈��
void CTraningScene::DrawParamChange(const IncParam& param)
{
    WriteText* Text = WriteText::GetInstance();
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�`��ʒu�̐ݒ�
    //�e�L�X�g�̕`��ʒu��ݒ�
    //�����ʒu
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //���l�e�L�X�g�̈ʒu
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    //�f�����A�X�^�~�i�̏ꍇ�̒���
    if (param.ParamName == L"�f������")       
    {
        ValueOffset.x += 30.0f; 
    }
    else if (param.ParamName == L"�X�^�~�i��")
    {
        ValueOffset.x += 40.0f; 
    }


    //�㏸�����������������ɂ���ĕ����̐F��ύX����
    if (param.IncValue != 0) 
    {
        //�p�����[�^�̖��O�ƕω��̕`��
        Text->Draw_Text(param.ParamName, WriteText::Normal, InitOffset);

        //�p�����[�^���㏸�A�܂��̓X�^�~�i���񕜂��Ă����ꍇ
        if (param.ParamChangeText == L"�㏸����" || param.ParamChangeText == L"�񕜂���")
        {
            Text->Draw_Text(std::to_wstring(param.IncValue) + param.ParamChangeText, WriteText::Inc, ValueOffset);
        }
        else
        {
            Text->Draw_Text(std::to_wstring(param.IncValue) + param.ParamChangeText, WriteText::Dec, ValueOffset);
        }
    }
    else 
    {
        //�X�^�~�i�����ɖ��^���ŏ㏸�܂��͊���0�̏�ԂŌ��������ꍇ
        if (param.ParamName == L"�X�^�~�i��")
        {
            //�p�����[�^�̖��O�ƕω��̕`��
            Text->Draw_Text(L"�X�^�~�i��", WriteText::Normal, InitOffset);
            //�X�^�~�i������0�̏�ԂŌ��������ꍇ
            if (HeroMng->GetStamina() <= 0)
            {
                Text->Draw_Text(L"����ȏ㌸�����Ȃ�", WriteText::Dec, ValueOffset);
            }
            else if(HeroMng->GetStamina() >= 100)
            {
                Text->Draw_Text(L"����ȏ�񕜂��Ȃ�", WriteText::Inc, ValueOffset);
            }
        }
    }
}

