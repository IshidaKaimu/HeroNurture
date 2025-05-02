#include "CSceneBase.h"
#include "Sprite3D\CSprite3D.h"
#include "Sprite2D\CSprite2D.h"
#include "Sprite2D\UIManager\CUIManager.h"
#include "WriteText\WriteText.h"

CSceneBase::CSceneBase()
    : m_Light     ()
    , m_MoveCamPos     ()
    , m_MoveCamLook    ()
    , m_DebugPos       ()
    , m_DebugUiPos     ()
    , m_DebugCamPos    ()
    , m_DebugCamLook   ()
    , m_IsScene        (true)
    , m_SelectNo       ()
    , m_pFade          (nullptr)
    , m_FadeTime       (0)
    , m_FadeAlpha      (1.0f)	//�s���߂ɐݒ�
    , m_FadeOutFlg     (false)
{
    //�t�F�[�h
    m_pFade = std::make_unique<CUIObject>();
    m_pFade->AttachSprite(CUIManager::GetSprite(CUIManager::Fade));
    m_pFade->SetAlpha(m_FadeAlpha);
    //���t�F�[�h
    m_pWhiteFade = std::make_unique<CUIObject>();
    m_pWhiteFade->AttachSprite(CUIManager::GetSprite(CUIManager::WhiteFade));
    m_pWhiteFade->SetAlpha(m_WhiteFadeAlpha);
    //������@�w���o�[
    m_pControlBar = std::make_unique<CUIObject>();
    m_pControlBar->AttachSprite(CUIManager::GetSprite(CUIManager::ControlBar));
}

CSceneBase::~CSceneBase()
{
}

//�������֐�
void CSceneBase::Initialize()
{
}

//�X�V�֐�
void CSceneBase::Update()
{
}

//�`��֐�
void CSceneBase::Draw()
{
	////�`��
	m_pFade->Draw();	 //�t�F�[�h
    m_pWhiteFade->Draw();//���t�F�[�h
}

//�j���֐�
void CSceneBase::Releace()
{
}

//�t�F�[�h�A�E�g
bool CSceneBase::FadeOut()
{
    //�f�o�b�O�t���O���L���̏ꍇ�A���ԒZ�k�̂��ߏ����I��
    if( DEBUG_FLG ) {
        m_FadeAlpha = 0.0f;					//���l��������
        m_pFade->SetAlpha(m_FadeAlpha);
        return true;
    }

    //�t�F�[�h�A�E�g�t���O�L����
    m_FadeOutFlg = true;

    m_FadeTime++;
    m_FadeAlpha += FADESPEED;			//�t�F�[�h���Z
    m_pFade->SetAlpha(m_FadeAlpha);	//���l��ݒ�
    //�t�F�[�h�^�C�}�[������܂ōs����
    if( m_FadeTime >= FADE_TIME ) {
        //������
        m_FadeTime = 0;
        m_FadeAlpha = 1.0f;
        m_FadeOutFlg = false;

        return true;
    }

    return false;
}

//�t�F�[�h�C��
bool CSceneBase::FadeIn()
{
    //�t�F�[�h�A�E�g���Ȃ珈���I��
    if( m_FadeOutFlg ) { return true; }

    //���l��0.0f�ȉ��ɂȂ�܂Ō��Z
    if( m_FadeAlpha > 0.0f ) {
        if( m_FadeTime <= FADE_TIME )
        {
            m_FadeTime++;
            m_FadeAlpha -= FADESPEED;
        }
        //�t�F�[�h�C���I��
        if( m_FadeTime >= FADE_TIME ) {
            m_FadeTime = 0;

        }
    }
    else {
        m_FadeAlpha = 0.0f;
        return true;
    }

    m_pFade->SetAlpha(m_FadeAlpha);

    return false;
}

//������@�w���o�[�e���v���[�g�̕`��
void CSceneBase::DrawControlBar()
{
    WriteText* Text = WriteText::GetInstance();

    //������@�w���o�[�̐ݒ�
    m_pControlBar->SetPosition(CONTROLBAR_POS);                     //���W
    m_pControlBar->SetScale(CONTROLBAR_SCALE);                      //�g�k
    m_pControlBar->SetDisplay(CONTROLBAR_DISP.x, CONTROLBAR_DISP.y);//��

    //������@�w���o�[�`��
    m_pControlBar->Draw();

    //������@�w���uEnter ����v�e�L�X�g�̕`��
    Text->Draw_Text(L"Enter ����", WriteText::Control, ENTERTEXT_POS);
    //������@�w���uEsc �߂�v�e�L�X�g�̕`��
    Text->Draw_Text(L"Esc �߂�", WriteText::Control, ESCAPETEXT_POS);
}

//���t�F�[�h�֘A�̏�����
void CSceneBase::InitWhiteFade()
{
    m_WhiteFadeCnt = 0;
    m_AlphaChange = true;
    m_WhiteFadeAlpha = 0.0f;
}

//���t�F�[�h�Đ�
void CSceneBase::PlayWhiteFade(int max, float speed, float alpha)
{
    if (m_AlphaChange == false && m_WhiteFadeCnt <= max)
    {
        m_WhiteFadeAlpha += speed;

        if (m_WhiteFadeAlpha >= alpha)
        {
            m_AlphaChange = true;
            m_WhiteFadeCnt++;
        }
    }
    else
    {
        m_WhiteFadeAlpha -= speed;

        if (m_WhiteFadeAlpha < 0.0f)
        {
            m_WhiteFadeAlpha = 0.0f;
            m_AlphaChange = false;
        }
    }

    //���l�̐ݒ�
    m_pWhiteFade->SetAlpha(m_WhiteFadeAlpha);
}


