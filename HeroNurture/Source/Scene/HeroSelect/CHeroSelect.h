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
static const D3DXVECTOR3 CAMPOS  = { 0.0f, 5.2f, -2.8f };
static const D3DXVECTOR3 CAMLOOK = { 0.0f, 6.2f,  3.0f };


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

    //----�e�q�[���[�N���X----
	//���C
	CYui*	m_pYui;
	//�J�C�g
	CKaito* m_pKaito;

};