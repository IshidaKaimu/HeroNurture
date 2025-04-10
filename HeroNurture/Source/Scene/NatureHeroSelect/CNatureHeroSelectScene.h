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
//----�}�l�[�W���[�N���X----
//UI
class CUIManager;
//�T�E���h
class CSoundManager;

// =======================
// �萔�錾
// =======================	
namespace Constant_NatureHeroSelectScene 
{
	//----�e�q�[���[�̃J�����z�u�E�����_----
	static const D3DXVECTOR3 CAMPOS_NS = { 0.0f, 5.2f, -2.8f };
	static const D3DXVECTOR3 CAMLOOK_NS = { 0.0f, 6.2f,  3.0f };
	//----UI----
	//�V�[�����\���ʒu
	const D3DXVECTOR2 SCENENAME_POS_NS = { 350.0f, -10.0f };
	//�q�[���[���\���ʒu
	const D3DXVECTOR2 HERONAME_POS_NS = { 350.0f,450.0f };
	//�w���e�L�X�g�\���ʒu
	const D3DXVECTOR2 INFOTEXT_POS_NS = { 850.0f, 600.0f };
}

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
	//���̕`��
	void DrawArrow();
private:

	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

    //=====================================
	// �I�u�W�F�N�g�N���X
	//=====================================
	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui>	m_pYui;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;

	//----UI----
	//���
	std::unique_ptr<CUIObject> m_pLeftArrow;
	//���E
	std::unique_ptr<CUIObject> m_pRightArrow;

	//���[�U�[��
	std::wstring m_UserName;


};