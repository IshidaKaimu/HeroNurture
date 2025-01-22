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
//���ʂ̏����ʒu
const D3DXVECTOR3 TITLE_POS = { 0.0f, 0.0f, 1.0f };
//���C�̏����ݒ�
const D3DXVECTOR3 TITLE_YUI_SCALE = { 0.04f, 0.04f, 0.04f }; //�g�k
//�J�C�g�̏����ݒ�
const D3DXVECTOR3 TITLE_KAITO_SCALE = { 0.3f, 0.3f, 0.3f };  //�g�k

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

private:

	//�����̓���
	float Easing(float x);
	//�A�J�E���g�����͏���
	void  InputName();	
	//UI�̕`��
	void DrawUI();

	//wstring����string�ւ̕ϊ�
	std::string WstringToString(std::wstring owstring);

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
	//�J�C�g
	std::unique_ptr<CKaito> m_pKaito;

	//----UI----
	//�^�C�g���w�i
	std::unique_ptr<CUIObject> m_pTitleBack;
	//�^�C�g���w���e�L�X�g�w�i
	std::unique_ptr<CUIObject> m_pTitleInfoBack;

	//���[�U�[������
	std::wstring m_UserName;

	//Json�N���X
	std::unique_ptr<CJson> m_pJson;


	//�\���q�[���[
	int m_HeroNo;

};

