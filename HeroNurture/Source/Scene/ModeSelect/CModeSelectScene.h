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
// �萔�錾
// =======================
//----�eUI�̐ݒ�----
//�琬���[�h		
const D3DXVECTOR3 NATUREMODE_POS = { 0.0f,0.0f,-1.0f };  //���W
//�o�g�����[�h
const D3DXVECTOR3 BATTLEMODE_POS = { 640.0f,0.0f,-1.0f };//���W
//�킹��摜
const D3DXVECTOR3 COVER_POS = { 640.0f,0.0f,0.0f };//���W
constexpr float COVER_ALPHA = 0.8f;
//����
const D3DXVECTOR3 MODE_SCALE = { 1.0f,1.0f,1.0f }; //�g�k
const D3DXVECTOR2 MODE_DISP  = { 1.0f, 1.0f };     //���l
constexpr float   MODE_ALPHA = 1.0f;
//�V�[����
const D3DXVECTOR2 SCENENAME_POS = { 430.0f,0.0f };


//=====================================
// ���[�h�Z���N�g�V�[���N���X
// �쐬��:�Γc�D��
//=====================================
class CModeSelectScene
	:public CSceneBase
{
private:
	//���[�h���X�g
	enum enModeList :char
	{
		NatureMode,
		BattleMode,
		Max
	};

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
	//�琬���[�h
	std::unique_ptr<CUIObject> m_pNatureMode;
	//�ΐ탂�[�h
	std::unique_ptr<CUIObject> m_pBattleMode;
	//�I������Ă��Ȃ��ق��ɂ��Ԃ���摜
	std::unique_ptr<CUIObject> m_pCover;

};

