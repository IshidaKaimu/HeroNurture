#pragma once
#include "Sprite2D/CSprite2D.h"
#include "CDirectX11.h"
#include "SkinMeshObject/Hero/CHeroBase.h"

class CUIManager
{
public:
	//UI���X�g
	enum UIList
	{
		Fade,		 //�V�[���J�ڎ��Ɏg���t�F�[�h�p�̉摜
		WhiteFade,	 //���t�F�[�h�p�摜
		PowerParam,  //�ؗ̓p�����[�^�\���p�摜
		SpeedParam,  //�f�����p�����[�^�\���p�摜
		MagicParam,  //���̓p�����[�^�\���p�摜
		HpParam,     //�̗̓p�����[�^�\���p�摜
		StaminaGage, //�X�^�~�i�Q�[�W�\���p�摜

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

	CHeroBase* m_pHero;
};

