#pragma once
#include "Sprite2D/CSprite2D.h"
#include "CDirectX11.h"
#include "SkinMeshObject/Player/CPlayer.h"

class CUIManager
{
public:
	//UI���X�g
	enum UIList
	{
		Fade,		//�V�[���J�ڎ��Ɏg���t�F�[�h�p�̉摜
		WhiteFade,  //���܂����Ɏg�����t�F�[�h�p�摜

		Max,
	};

	//�V���O���g����
	static CUIManager* GetInstance() {
		static CUIManager s_Instance;
		return &s_Instance;
	}

public:
	~CUIManager();

	HRESULT Load(CDirectX11* Dx11);

	void SetDx11(CDirectX11& Dx11) { m_pDx11 = &Dx11; }

	static CSprite2D& GetSprite(UIList list) { return *GetInstance()->m_pSprite2D[list]; }

private:
	//�V���O���g����
	CUIManager();
	CUIManager(const CUIManager& rhs) = delete;
	CUIManager& operator = (const CUIManager& rhs) = delete;

private:
	CDirectX11* m_pDx11;

	CSprite2D* m_pSprite2D[UIList::Max];

	CPlayer* m_pPlayer;
};

//UI�T�C�Y�萔
static const D3DXVECTOR2 TEXTBOXSIZE = { 641.0f, 97.0f };    //�e�L�X�g�{�b�N�X
