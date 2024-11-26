#pragma once
#include "Scene/CSceneBase.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Hero/CHeroBase.h"
#include "json.hpp"

//�O���錾
//----�e�q�[���[�̃N���X
class CYui;
class CKaito;

//----�e�q�[���[�̃J�����z�u�E�����_----
//���C
static const D3DXVECTOR3 CAMPOS_YUI  = { 0.0f, 5.2f, -2.8f };
static const D3DXVECTOR3 CAMLOOK_YUI = { 0.0f, 6.2f,  3.0f };
////�J�C�g
//static const D3DXVECTOR3 CAMPOS_KAITO  = { 0.0f, 5.0f, -4.0f };
//static const D3DXVECTOR3 CAMLOOK_KAITO = { 0.0f, 5.0f,  3.0f };

//�q�[���[�Z���N�g�V�[��
class CHeroSelect
	:public CSceneBase
{
public:
	CHeroSelect();
	~CHeroSelect();

	//�\�z�֐�
	void Create()	  override;
	//�j���֐�
	void Releace()	  override;
	//�f�[�^�ݒ�֐�
	void LoadData()	  override;
	//�������֐�
	void Initialize() override;
	//�X�V�֐�
	void Update()     override;
	//�`��֐�
	void Draw()		  override;


public:
	//�A�J�E���g���擾
	void SetUserName(std::wstring name) { m_UserName = name; }

private:

	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//���[�U�[��
	std::wstring m_UserName;

	//�f�o�b�O�p
	D3DXVECTOR3 CamPos;
	D3DXVECTOR3 CamLook;	

    //----�e�q�[���[�N���X----
	//���C
	CYui*	m_pYui;
	//�J�C�g
	CKaito* m_pKaito;


	//�I�����p�ԍ�
	int m_SelectNo;


};