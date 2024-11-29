#include "CUIObject.h"

CUIObject::CUIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
{
}

CUIObject::~CUIObject()
{
	DetachSprite();
}

//�X�V�֐�
void CUIObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

//�`��֐�
void CUIObject::Draw()
{
	if( m_pSprite == nullptr ){
		return;
	}

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );

	//�p�^�[���ԍ���ݒ�.
	m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y );

	//�����_�����O.
	m_pSprite->Render();
}
