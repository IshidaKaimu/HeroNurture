#include "CTraning.h"
#include "ImGui\ImGuiManager\ImGuiManager.h"
#include "KeyManager\CKeyManager.h"
#include "Scene\CSceneManager.h"
#include "WriteText\WriteText.h"
#include "SkinMeshObject\Hero\CHeroManager.h"

CTraning::CTraning()
    : m_pCamera (&CCameraManager::GetInstance())
    , m_pSky    ()
    , m_pGround ()
    , m_TextNo  ()
{
}

CTraning::~CTraning()
{
}

//�\�z�֐�
void CTraning::Create()
{
    //----�C���X�^���X����----
    //�X�^�e�B�b�N���b�V���I�u�W�F�N�g
    //��
    m_pSky = make_unique<CSky>();
    //�n��
    m_pGround = make_unique<CGround>();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃C���X�^���X����
    CNatureScene::CreateNatureUI(m_pStaminaGage);

}
//�j���֐�
void CTraning::Releace()
{
}
//�f�[�^�ǂݍ��݊֐�
void CTraning::LoadData()
{
    //�n�ʂ̃��b�V���f�[�^�ݒ�
    m_pGround->LoadData();

    //�琬�֘A�̃V�[���ŋ��ʂ���UI�̃X�v���C�g�f�[�^�ݒ�
    CNatureScene::LoadNatureUI(m_pStaminaGage);
}
//�������֐�
void CTraning::Initialize()
{
    //�琬�֘A�̃V�[���ŋ��ʂ���UI
    CNatureScene::InitNatureUI(m_pStaminaGage);
}

//�X�V�֐�
void CTraning::Update()
{
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

   //�L�[�}�l�[�W���[�̍X�V����
   CKeyManager::GetInstance()->Update();

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
   if (m_TextNo >= m_ParamInc.size() && !m_SceneTransitionFlg)
   {
       m_SceneTransitionFlg = true;
   }

   if (m_SceneTransitionFlg && FadeOut())
   {
       CSceneManager::GetInstance()->LoadCreate(CSceneManager::Nature);
   }
}
//�`��֐�
void CTraning::Draw()
{
    m_pGround->Draw();
    //�㏸�ʃe�L�X�g�̕`��(��)
    DrawUpText();

    //�琬�֘A�̃V�[���ŋ��ʂ��ĕ\������UI
    CNatureScene::DrawNatureUI(m_pStaminaGage);
}

//�z��Ƀe�L�X�g��ǉ�����֐�
void CTraning::AddText()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //----���ꂼ��̃p�����[�^���㏸���Ă����ꍇ�̏�����----
    //�ؗ�
    bool IsPowerUp = Hero->GetBeforeParam().Power < Hero->GetParam().Power;
    //����
    bool IsMagicUp = Hero->GetBeforeParam().Magic < Hero->GetParam().Magic;
    //�f����
    bool IsSpeedUp = Hero->GetBeforeParam().Speed < Hero->GetParam().Speed;
    //�̗�
    bool IsHpUp = Hero->GetBeforeParam().Hp < Hero->GetParam().Hp;

    //�����𖞂����Ă���΍\���̔z��Ɋi�[                                   �p�����[�^��,�㏸��
    if (IsPowerUp && !AlreadyAddCheck(L"�ؗ͂�"))   { m_ParamInc.push_back({L"�ؗ͂�",static_cast<int>(Hero->GetParam().Power - Hero->GetBeforeParam().Power)}); }
    if (IsMagicUp && !AlreadyAddCheck(L"���͂�"))   { m_ParamInc.push_back({ L"���͂�",static_cast<int>(Hero->GetParam().Magic - Hero->GetBeforeParam().Magic) }); }
    if (IsSpeedUp && !AlreadyAddCheck(L"�f������")) { m_ParamInc.push_back({ L"�f������",static_cast<int>(Hero->GetParam().Speed - Hero->GetBeforeParam().Speed) }); }
    if (IsHpUp    && !AlreadyAddCheck(L"�̗͂�"))   { m_ParamInc.push_back({ L"�̗͂�",static_cast<int>(Hero->GetParam().Hp - Hero->GetBeforeParam().Hp) }); }

}

//�z��ɒǉ��ς݂łȂ������ׂ�֐�
bool CTraning::AlreadyAddCheck(std::wstring paramname)
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

//�㏸�ʃe�L�X�g�̕`��
void CTraning::DrawUpText()
{
    //�e�L�X�g�`��N���X�̃C���X�^���X��ϐ��ɑ��
    WriteText* Text = WriteText::GetInstance();
    //�q�[���[�}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CHeroManager* Hero = &CHeroManager::GetInstance();

    //�u�㏸����!�v�e�L�X�g
    std::wstring UpText = L"�㏸�����I";

    //�e�L�X�g�̕`��ʒu��ݒ�
    //1�s���̍���
    D3DXVECTOR2 TextOffset = { 0.0f, 60.0f };
    //�����ʒu
    D3DXVECTOR2 InitOffset = PARAMTEXT_OFFSET;
    //���l�e�L�X�g�̈ʒu
    D3DXVECTOR2 ValueOffset = VALUETEXT_OFFSET;

    if (m_TextNo < m_ParamInc.size())
    {
        const auto& Increase = m_ParamInc[m_TextNo];
        
        //�f�����̎��݈̂ʒu�����炷
        if (Increase.ParamName == L"�f������") { ValueOffset.x += 30.0f; }

        Text->Draw_Text(Increase.ParamName, WriteText::Normal, InitOffset);
        Text->Draw_Text(std::to_wstring(Increase.IncValue) + L"�㏸�����I", WriteText::Inc, ValueOffset);
    }
}

