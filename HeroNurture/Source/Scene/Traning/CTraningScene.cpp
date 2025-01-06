#include "CTraningScene.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Sprite2D\UIManager\CUIManager.h"

CTraningScene::CTraningScene()
    : m_pCamera ( &CCameraManager::GetInstance() )
    , m_pSky    ()
    , m_pGround ()
    , m_pBack   ()
    , m_TextNo  ()
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

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃C���X�^���X����
    CNatureScene::CreateNatureUI(m_pStaminaGage,m_pStaminaBack);

}
//�j���֐�
void CTraningScene::Releace()
{
}
//�f�[�^�ǂݍ��݊֐�
void CTraningScene::LoadData()
{
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�N���X
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�n�ʂ̃��b�V���f�[�^�ݒ�
    m_pGround->LoadData();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃X�v���C�g�f�[�^�ݒ�
    CNatureScene::LoadNatureUI(m_pStaminaGage,m_pStaminaBack);

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

}
//�������֐�
void CTraningScene::Initialize()
{
    CSceneManager::GetInstance()->InitWhiteFade();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI
    CNatureScene::InitNatureUI(m_pStaminaGage,m_pStaminaBack);

    m_pBack->SetPosition(0.0f, 0.0f, 0.0f);
    m_pBack->SetScale(1.0f, 1.0f, 1.0f);
    m_pBack->SetDisplay(1.0f, 1.0f);
}

//�X�V�֐�
void CTraningScene::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

   //�L�[�}�l�[�W���[�̍X�V����
   CKeyManager::GetInstance()->Update();

   //�V�[���}�l�[�W���[�N���X
   CSceneManager* SceneMng = CSceneManager::GetInstance();

   //�e�L�X�g�̕`���i�߂�
   if (CKeyManager::GetInstance()->IsDown(VK_RETURN) && m_ParamInc.size())
   {
       m_TextNo++;
   }

   //�㏸�����p�����[�^�̃e�L�X�g��ǉ�
   AddText();

#if _DEBUG
   ImGui::Begin(JAPANESE("�e�L�X�g�̔ԍ�"));
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_TextNo);
   ImGui::Text(JAPANESE("m_TextNo:%d"), m_ParamInc.size());
   ImGui::Text(JAPANESE("m_Stamina:%f"),CHeroManager::GetInstance().GetStamina());
   ImGui::Text(JAPANESE("�X�^�~�i�Q�[�W�̕�:%f"),CSceneManager::GetInstance()->GetStaminaWidth());
   ImGui::End();
#endif

   //�e�L�X�g�̕`�悪�S�ďI��莟��V�[���J��
   //�g���[�j���O���������Ă����
   if (!CHeroManager::GetInstance().GetFailure())
   {
       if (m_TextNo >= m_ParamInc.size() && !m_SceneTransitionFlg)
       {
           m_SceneTransitionFlg = true;
       }
   }
   else
   {
       //���s�����ꍇ�G���^�[�L�[�őJ��
       if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
       {
           m_SceneTransitionFlg = true;
       }
   }

   //�t�F�[�h���I��莟��V�[���J��
   if (m_SceneTransitionFlg && FadeOut())
   {
       //�x���t���O�������Ă�����~�낷
       if (SceneMng->GetRestFlag()) { SceneMng->SetRestFlag(false); }

       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//�`��֐�
void CTraningScene::Draw()
{
    //�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�V�[���}�l�[�W���[
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    m_pGround->Draw();

    //�e�g���[�j���O�w�iUI�̕`��
    m_pBack->Draw();
    
    //�㏸�ʃe�L�X�g�̕`��
    DrawTraningText();

    //�[�x�𖳎�����
    SceneMng->GetDx11()->SetDepth(false);
    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI
    CNatureScene::DrawNatureUI(m_pStaminaGage,m_pStaminaBack);
    //�[�x��߂�
    SceneMng->GetDx11()->SetDepth(true);

}

////�e�g���[�j���O�̃A�j���[�V����
//void CTraningScene::TraningAnimation()
//{    
//    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
//    //�e�L�X�g�`��N���X
//    WriteText* Text = WriteText::GetInstance();
//    //�q�[���[�}�l�[�W���[�N���X
//    CHeroManager* HeroMng = &CHeroManager::GetInstance();
//
//    switch (HeroMng->GetTraining())
//    {
//    case CHeroManager::PowerTraining:
//        HeroMng->PowerTraningAnimation();
//        break;
//    case CHeroManager::MagicTraining:
//        HeroMng->MagicTraningAnimation();
//        break;
//    case CHeroManager::SpeedTraining:
//        HeroMng->SpeedTraningAnimation();
//        break;
//    case CHeroManager::HpTraining:
//        HeroMng->HpTraningAnimation();
//        break;
//    default:
//        break;
//    }
//}

//�z��Ƀe�L�X�g��ǉ�����֐�
void CTraningScene::AddText()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
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
    bool IsRecoveryStamina = Hero->GetBeforeStamina() <= Hero->GetStamina();
    bool IsReduceStamina = Hero->GetBeforeStamina() >= Hero->GetStamina();
    float StaminaInc = std::abs(Hero->GetStamina() - Hero->GetBeforeStamina());

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
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�N���X
    CHeroManager* HeroMng = &CHeroManager::GetInstance();
    //�V�[���}�l�[�W���[�N���X
    CSceneManager* SceneMng = CSceneManager::GetInstance();

    //----�e�L�X�g��ϐ��ɑ��----
    //���s���������ۂɂ���ĕԂ��e�L�X�g��ς���
    std::wstring ResultText = HeroMng->GetFailure() ? L"���s..." : L"����!!";

    //�g���[�j���O�����s�������̏�����
    bool Failure = HeroMng->GetFailure();
    //�x�����I������Ă������̏�����
    bool Rest = SceneMng->GetRestFlag();

    //�x�e���I������Ă��Ȃ��ꍇ
    if (!Rest)
    {
        //�g���[�j���O����
        if (!Failure)
        {
            //�u����!!�v�̃e�L�X�g�`��
            Text->Draw_Text(ResultText, WriteText::Success, RESULTTEXT_OFFSET);
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
    //----�N���X�̃C���X�^���X��ϐ��ɑ��----
    //�e�L�X�g�`��N���X
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�N���X
    CHeroManager* HeroMng = &CHeroManager::GetInstance();

    //�`��ʒu�̐ݒ�
    //�e�L�X�g�̕`��ʒu��ݒ�
    //�����ʒu
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //���l�e�L�X�g�̈ʒu
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    //�f�����A�X�^�~�i�̏ꍇ�̒���
    if (param.ParamName == L"�f������") { ValueOffset.x += 30.0f; }
    else if (param.ParamName == L"�X�^�~�i��") { ValueOffset.x += 40.0f; }


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

