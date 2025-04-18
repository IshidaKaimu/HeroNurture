#pragma once
#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "StaticMeshObject\Sky\CSky.h"			//�X�J�C�{�b�N�X�N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include "StaticMeshObject\Ground\CGround.h"	//�n�ʃN���X
#include "SkinMeshObject\Hero\Yui\CYui.h"       //���C�N���X
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   //�J�C�g�N���X
#include <memory>
#include <Windows.h>

// =======================
// �O���錾
// =======================		
class CJson;
class CUtility;
class CUIManager;
class CHeroManager;
class CSoundManager;
class CSceneManager;

// =======================
// �萔�錾
// =======================
namespace Constant_TitleScene
{
	//�J����
	const D3DXVECTOR3 CAM_POS		  = { 1.0f, 5.0f, -7.0f }; //���W
	const D3DXVECTOR3 CAM_LOOK		  = { 2.0f, 5.0f, 0.0f };  //�����_
	//���C�̏����ݒ�				   
	const D3DXVECTOR3 YUI_POS		  = { 0.0f, 0.0f, 0.0f };    //���W
	const D3DXVECTOR3 YUI_ROT		  = { 0.0f, -0.5f, 0.0f };   //��]
	const D3DXVECTOR3 YUI_SCALE		  = { 0.04f, 0.04f, 0.04f }; //�g�k
	//�J�C�g�̏����ݒ�				  
	const D3DXVECTOR3 KAITO_POS		  = { -1.0f, 0.3f, 2.0f }; //���W
	const D3DXVECTOR3 KAITO_ROT		  = { 0.0f, -0.5f, 0.0f }; //��]
	const D3DXVECTOR3 KAITO_SCALE	  = { 0.3f, 0.3f, 0.3f };  //�g�k
	//�^�C�g���e�L�X�g�̈ʒu		   
	const D3DXVECTOR2 TITLE_POS		  = { 30.0f, -50.0f };
	//�I�����e�L�X�g�̊�l
	const D3DXVECTOR2 SELECT_POS	  = { 900.0f, 400.0f };
	//�I�����e�L�X�g���m�̊Ԋu
	constexpr float   SELECT_INTERVAL = 80.0f;
}

//=====================================
// �^�C�g���V�[���N���X
//=====================================
class CTitleScene
	:public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();


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
	//�f�o�b�O�p�֐�
	void Debug();

private:
	//�A�J�E���g�����͏���
	void  InputName();	
	//UI�̕`��
	void DrawUI();

private:

	//�J�����N���X
	CCameraManager* m_pCamera;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----�X�^�e�B�b�N���b�V��----
	//��
	std::unique_ptr<CSky> m_pSky;	
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui> m_pYui;
	D3DXVECTOR3 m_YuiPos;
	D3DXVECTOR3 m_YuiRot;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;
	D3DXVECTOR3 m_KaitoPos;
	D3DXVECTOR3 m_KaitoRot;


	//----UI----
	//�^�C�g���w�i
	std::unique_ptr<CUIObject> m_pTitleBack;
		

	//�\���q�[���[
	int m_HeroNo;

};

