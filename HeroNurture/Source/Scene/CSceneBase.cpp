#include "CSceneBase.h"
#include "Sprite2D\UIManager\CUIManager.h"

CSceneBase::CSceneBase()
    : m_Light     ()
    , m_CamPos    ()
    , m_CamLook   ()
    , m_IsScene   (true)
    , m_SelectNo  ()
    , m_pFade     (nullptr)
    , m_FadeTime  (0)
    , m_FadeAlpha (1.0f)	//�s���߂ɐݒ�
    , m_FadeOutFlg(false)
{
    m_pFade = new CUIObject();		//�t�F�[�h
    m_pFade->AttachSprite(CUIManager::GetSprite(CUIManager::Fade));
    m_pFade->SetAlpha(m_FadeAlpha);
}

CSceneBase::~CSceneBase()
{
	//�j��
	SAFE_DELETE( m_pFade );		//�t�F�[�h
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
	//�`��
	m_pFade->Draw();	//�t�F�[�h
}

//�j���֐�
void CSceneBase::Releace()
{
}

//���[�h�񐔐����t���O�̑���
void CSceneBase::IsDataLoaded(bool loaded)
{
    m_IsDataLoaded = loaded;
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

