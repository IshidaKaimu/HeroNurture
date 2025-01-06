#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CCamera.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"

//=====================================
// �O���錾
//=====================================
//----�e�q�[���[�̃N���X
class CYui;
class CKaito;

// =======================
// �萔�錾 (_NS = �g���[�j���O���ʃV�[���ŗp���邱�Ƃ�����)
// =======================	
//----�e�q�[���[�̃J�����z�u�E�����_----
static const D3DXVECTOR3 CAMPOS_NS  = { 0.0f, 5.2f, -2.8f };
static const D3DXVECTOR3 CAMLOOK_NS = { 0.0f, 6.2f,  3.0f };


class CNatureHeroSelectScene
	:public CSceneBase
{
public:
	CNatureHeroSelectScene();
	~CNatureHeroSelectScene();

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


    //=====================================
	// �I�u�W�F�N�g�N���X
	//=====================================
	//----�X�^�e�B�b�N���b�V��-----
	//�X�J�C�{�b�N�X
	std::unique_ptr<CSky>    m_pSky;
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui>	m_pYui;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;


	//���[�U�[��
	std::wstring m_UserName;


};