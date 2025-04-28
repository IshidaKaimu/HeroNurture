#include "CUIObject.h"

CUIObject::CUIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
	, m_DisplaySize ()
{
}

CUIObject::~CUIObject()
{
	DetachSprite();
}


//更新関数
void CUIObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

//描画関数
void CUIObject::Draw()
{
	if( m_pSprite == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition( m_vPosition );
	m_pSprite->SetRotation( m_vRotation );
	m_pSprite->SetScale( m_vScale );

	//UIの幅、高さ
	m_pSprite->SetDisplay( m_DisplaySize.x, m_DisplaySize.y );

	//パターン番号を設定.
	m_pSprite->SetPatternNo( m_PatternNo.x, m_PatternNo.y );

	//レンダリング.
	m_pSprite->Render();
}
