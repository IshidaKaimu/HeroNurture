#pragma once
#include "CSceneBase.h"
#include "CKaito.h"
#include "CCamera.h"
#include "CSky.h"
#include "WriteText.h"
#include "CGround.h"



//�Q�[�����C���V�[��
class CGameMain
	:public CSceneBase
{
public:

public:
	CGameMain();
	~CGameMain();


	//�\�z�֐�
	void Create() override;
	//�f�[�^�ݒ�֐�
	void LoadData() override;
	//�j���֐�
	void Releace() override;
	//�X�V�֐�
	void Update() override;
	//�`��֐�
	void Draw() override;
	//�����̓���
	float Easing(float x);

private:
	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	D3DXMATRIX	m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX	m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.


	//�I�[�v�j���O�Ɉڂ点��t���O
	bool m_Opening;
	//�{�X�o���V�[���Ɉڂ点��t���O
	bool m_BossApp;
	//�{�X�i���V�[���Ɉڂ点��t���O
	bool m_BossEvo;
	//�K�E�Z�V�[���Ɉڂ点��t���O
	bool m_Special;
	//�{�X���j�V�[���Ɉڂ点��t���O
	bool m_BossDeath;

	//���Ԍo�߂ł����X
	float m_Time;


};

