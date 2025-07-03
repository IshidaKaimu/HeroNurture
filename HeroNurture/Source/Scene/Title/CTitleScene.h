#pragma once
#include "Scene\CSceneBase.h"					
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"			
#include "WriteText\WriteText.h"				
#include "StaticMeshObject\Ground\CGround.h"	
#include "SkinMeshObject\Hero\Yui\CYui.h"       
#include "SkinMeshObject\Hero\Kaito\CKaito.h"   
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
//========================

// =======================
// �萔�錾
// =======================
namespace Constant_TitleScene
{
	//----�J����----
	const D3DXVECTOR3 CAM_POS		  = { 1.0f, 5.0f, -7.0f }; //���W
	const D3DXVECTOR3 CAM_LOOK		  = { 2.0f, 5.0f, 0.0f };  //�����_
	//--------------
	
	//----�X�L�����b�V���I�u�W�F�N�g---- 
	//���C				   
	const D3DXVECTOR3 YUI_POS		  = { 0.0f, 0.0f, 0.0f };    //���W
	const D3DXVECTOR3 YUI_ROT		  = { 0.0f, -0.5f, 0.0f };   //��]
	const D3DXVECTOR3 YUI_SCALE		  = { 0.04f, 0.04f, 0.04f }; //�g�k
	//�J�C�g				  
	const D3DXVECTOR3 KAITO_POS		  = { -1.0f, 0.3f, 2.0f }; //���W
	const D3DXVECTOR3 KAITO_ROT		  = { 0.0f, -0.5f, 0.0f }; //��]
	const D3DXVECTOR3 KAITO_SCALE	  = { 0.3f, 0.3f, 0.3f };  //�g�k
	//-----------------------------------
	
	//----UI---- 
	//�^�C�g���e�L�X�g		   
	const D3DXVECTOR2 TITLE_POS = { 30.0f, -50.0f }; //���W

	//�I�����e�L�X�g
	const D3DXVECTOR2 SELECT_POS	  = { 900.0f, 400.0f }; //��l
	constexpr float   SELECT_INTERVAL = 80.0f;				//�Ԋu	

	//�I����
	const D3DXVECTOR3 SELECTARROW_POS   = { 810.0f, 425.0f, 0.0f }; //���W
	const D3DXVECTOR3 SELECTARROW_SCALE = { 0.7f, 0.7f, 0.7f };		//�g�k
	const D3DXVECTOR2 SELECTARROW_DISP  = { 1.0f, 1.0f };			//��
	const float		  SELECTARROW_RANGE = 3.0f;						//�ړ��͈�	
	//----------

}
//========================

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
	//UI�̕`��
	void DrawUI();

	//�I����𓮂���
	void MoveArrow();

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
	//----------------------------

	//----�X�L�����b�V��----
	//���C
	std::unique_ptr<CYui> m_pYui;
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;
	//----------------------

	//----UI----
	//�I����
	std::unique_ptr<CUIObject> m_pSelectArrow;
	float m_MoveArrow;		//���W�𓮂����l
	bool m_SwitchArrowFlag; //���̈ړ��t���O
	//----------
	//========================


	//�\���q�[���[
	int m_HeroNo;

};

