#pragma once
#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "StaticMeshObject\Sky\CSky.h"			//�X�J�C�{�b�N�X�N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include "StaticMeshObject\Ground\CGround.h"	//�n�ʃN���X
#include "SkinMeshObject\Hero\CHeroManager.h"	//�v���C���[�N���X
#include "SkinMeshObject\Hero\Yui\CYui.h"       //���C�N���X
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   //�J�C�g�N���X
#include <memory>
#include <Windows.h>

// =======================
// �O���錾
// =======================		
//json
class CJson;
//�ėp�N���X
class CUtility;
//UI�}�l�[�W���[
class CUIManager;

// =======================
// �O���錾
// =======================
//���ʂ̏����ʒu
const D3DXVECTOR3 TITLE_POS = { 0.0f, 0.0f, 1.0f };
//���C�̏����ݒ�
const D3DXVECTOR3 TITLE_YUI_SCALE = { 0.04f, 0.04f, 0.04f }; //�g�k
//�J�C�g�̏����ݒ�
const D3DXVECTOR3 TITLE_KAITO_SCALE = { 0.3f, 0.3f, 0.3f };  //�g�k

//=====================================
// ���[�h�Z���N�g�V�[���N���X
// �쐬��:�Γc�D��
//=====================================
class CModeSelectScene
	:public CSceneBase
{
public:
	CModeSelectScene();
	~CModeSelectScene();


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

private:
	//UI�̕`��
	void DrawUI();
private:
	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----UI----
	//�^�C�g���w�i
	std::unique_ptr<CUIObject> m_pTitleBack;
	//�^�C�g���w���e�L�X�g�w�i
	std::unique_ptr<CUIObject> m_pTitleInfoBack;

};

