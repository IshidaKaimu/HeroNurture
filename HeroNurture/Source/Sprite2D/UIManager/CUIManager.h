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
		Fade,		        //�V�[���J�ڎ��Ɏg���t�F�[�h�p�̉摜
		WhiteFade,	        //���t�F�[�h�p�摜
		TitleBack,          //�^�C�g���w�i
		TitleInfoBack,      //�^�C�g���w���e�L�X�g�w�i
		ModeSelectLeft,     //���[�h�I���V�[���w�i��
		ModeSelectRight,	//���[�h�I���V�[���w�i�E
		ModeSelectCover,    //���[�h�I���V�[���w�i���Ԃ���摜
		ParamList,          //�琬���̃p�����[�^�\
		ResultParamList,    //�琬���ʕ\�����̃p�����[�^�\
		PowerTraning,       //�ؗ̓g���[�j���O
		MagicTraning,       //���̓g���[�j���O
		SpeedTraning,       //�f�����g���[�j���O
		HpTraning,          //�̗̓g���[�j���O
		Rest,               //�x��		
		PowerBack,		    //�ؗ̓g���[�j���O�w�i
		MagicBack,		    //���̓g���[�j���O�w�i
		SpeedBack,		    //�f�����g���[�j���O�w�i
		HpBack,		        //�̗̓g���[�j���O�w�i
		RestBack,		    //�x���w�i
		TextBox,		    //�e�L�X�g�{�b�N�X
		StaminaGage,        //�X�^�~�i�Q�[�W
		StaminaBack,        //�X�^�~�i�Q�[�W�w�i
		StaminaFrame,       //�X�^�~�i�Q�[�W�w�i
		HpGage,			    //�̗̓Q�[�W
		HpGageBack,         //�̗̓Q�[�W�w�i
		GageFrame,          //�Q�[�W�g
		TurnBack,			//�^�[�����w�i
		PowerAttack,	    //�͍ؗU���A�C�R��
		MagicAttack,		//���@�U���A�C�R��
		AttackCover,        //�U���A�C�R���ɔ킹��摜
		UniqueGage,		    //���j�[�N�Q�[�W
		Arrow,              //���
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

