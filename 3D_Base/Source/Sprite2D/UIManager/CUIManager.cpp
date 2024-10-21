#include "CUIManager.h"



CUIManager::CUIManager()
	: m_pSprite2D()
	, m_pPlayer(nullptr)

{
	//�C���X�^���X�쐬
	m_pPlayer = new CPlayer();
}

CUIManager::~CUIManager()
{
	for (int i = UIList::Max - 1; i >= 0; i--) {
		SAFE_DELETE(m_pSprite2D[i]);
	}

	//�C���X�^���X�j��
	SAFE_DELETE(m_pPlayer);
	m_pDx11 = nullptr;
}

HRESULT CUIManager::Load(CDirectX11* Dx11)
{
	for (int i = 0; i < UIList::Max; i++) {
		m_pSprite2D[i] = new CSprite2D();
	}

	struct Sprite2DList
	{
		int listNo;
		LPCTSTR path;
		CSprite2D::SPRITE_STATE Ss;
	};

# if 0
	//�p���[�Q�[�W�X�v���C�g�̍\����
	CSprite2D::SPRITE_STATE SSPG =
	{ 64.0f, 320.0f, 64.0f, 320.0f, 64.0f, 320.0f };
	//�p���[�Q�[�W�X�v���C�g�̓ǂݍ���
	m_pSprite2D[UIList::PG]->Init(*m_pDx11,
		_T("Data\\Texture\\PowerGage.png"), SSPG);

	//�p���[�Q�[�W�t���[���X�v���C�g�̍\����
	CSprite2D::SPRITE_STATE SSPGF =
	{ 64.0f, 320.0f, 64.0f, 320.0f, 64.0f, 320.0f };
	//�p���[�Q�[�W�t���[���X�v���C�g�̓ǂݍ���
	m_pSprite2D[UIList::PGF]->Init(*m_pDx11,
		_T("Data\\Texture\\PowerGageFrame.png"), SSPGF);

	//�Z�X�v���C�g�̍\����
	CSprite2D::SPRITE_STATE SSo =
	{ 32.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f };
	//�Z�̓ǂݍ���
	m_pSprite2D[UIList::o]->Init(*m_pDx11,
		_T("Data\\Texture\\o.png"), SSo);

	//�~�X�v���C�g�̍\����
	CSprite2D::SPRITE_STATE SSx =
	{ 32.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f };
	//�~�̓ǂݍ���
	m_pSprite2D[UIList::x]->Init(*m_pDx11,
		_T("Data\\Texture\\x.png"), SSx);

	//-�X�v���C�g�̍\����
	CSprite2D::SPRITE_STATE SS_ =
	{ 32.0f, 32.0f, 32.0f, 32.0f, 32.0f, 32.0f };
	//-�̓ǂݍ���
	m_pSprite2D[UIList::_]->Init(*m_pDx11,
		_T("Data\\Texture\\-.png"), SS_);
#else 1
	Sprite2DList SList[] =

	{                                                                //�\���T�C�Y      //���摜�T�C�Y  //1�R�}������̕\���T�C�Y
		{UIList::Fade,	    _T("Data\\Texture\\fade.png")			,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
		{UIList::WhiteFade,	_T("Data\\Texture\\WhiteFade.png")		,{ 1280.0f, 720.0f, 1280.0f, 720.0f, 0.0f, 0.0f,}},
	};

	int list_max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSprite2D[SList[i].listNo]->Init(
			*Dx11, SList[i].path, SList[i].Ss) == E_FAIL)
		{
			return E_FAIL;
		}
	}

#endif
	return S_OK;
}

