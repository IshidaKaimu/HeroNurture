#pragma once
#include "CGameObject.h"
#include "Sprite2D\CSprite2D.h"
#include "Global\Global.h"

/************************************************************
*	UIオブジェクトクラス.
**/
class CUIObject
	: public CGameObject
{
public:
	CUIObject();
	virtual ~CUIObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	//CUIObjectで宣言したで関数で、以降はこれをoverrideさせる.
	virtual void Draw();

	//スプライトを接続する.
	void AttachSprite( CSprite2D& pSprite ){
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite(){
		m_pSprite = nullptr;
	}
	//パターン番号を設定.
	void SetPatternNo( SHORT x, SHORT y ){
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}

	//UIの幅、高さを設定
	void SetDisplay(float w, float h)
	{
		m_DisplaySize.x = w;
		m_DisplaySize.y = h;
	}
	//UIの幅を設定
	void SetWidth(float w)
	{
		m_DisplaySize.x = w;
	}
	//UIの高さを設定
	void SetHeight(float h)
	{
		m_DisplaySize.y = h;
	}

	//ディスプレイサイズ取得
	D3DXVECTOR2 GetDisplay()
	{
		return m_DisplaySize;
	}

	//アルファ値を設定する
	void SetAlpha(float value) { m_pSprite->SetAlpha(value); }

protected:
	CSprite2D*	m_pSprite;		//スプライト2Dクラス
	POINTS		m_PatternNo;	//パターン番号(マス目).
	D3DXVECTOR2 m_DisplaySize;	//UIの幅、高さ
};
