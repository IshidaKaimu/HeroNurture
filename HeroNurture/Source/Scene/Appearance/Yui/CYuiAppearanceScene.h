#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// �萔�錾
//=====================================
namespace Constant_AppearanceScene
{
	//----�J�������----
	const D3DXVECTOR3 INIT_CAMPOS     = { 0.0f, 4.0f, -5.0f };  //�������W
	const D3DXVECTOR3 INIT_CAMLOOK    = { 0.0f, 4.0f, 0.0f };   //���������_
	const D3DXVECTOR3 INIT_MOVECAMPOS = { 0.0f, 0.0f, 0.0f };//�����ړ��p�l
	//----�C�x���g���o----
	//�J����
	constexpr float CAM_FLICK_DISTANCE  = 25.0f; //�^�k�L�ɂ͂�����鋗��
	constexpr float CAM_FLICK_SPEED		= 0.7f;  //�^�k�L�ɂ͂�����鑬�x
	constexpr float CAM_MOVE_SPEED		= 0.03f; //�J�����̓������x
	//���t�F�[�h
	constexpr float FLICK_WHITEFADE		= -3.0f; //�J�������^�k�L�ɂ͂������Ƃ�
	//���@�w�G�t�F�N�g
	const D3DXVECTOR3 MAGICSIRCLE_POS    = { 0.0f, 0.5f,  -5.0f }; //���W
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //���@�w���f���J�����������W
	//----�C�x���g���o�p���l----
	//----�V�[��1----
	//���̃V�[���ł̃J�������W�����炷�l
	constexpr float SHIFT_CAMPOS = 2.0f;
	//�V�[����1����2�ɑJ�ڂ����邽�߂̃J�E���g
	constexpr int   ANIMCHANGE_CNT = 60;
	//���̃V�[���ł̏����J�������
	const float MOVE_INIT_CAMPOS_Y  = 2.0f; //y���W
	const float MOVE_INIT_CAMLOOK_Y = 2.0f; //y�����_
	//----�V�[��2----
	//�J�����̍ő�ړ��͈�
	constexpr float  MOVEMENT_RANGE_MAX_Y = 6.5f;
	//�V�[��2����I�����邽�߂ɗp����J�E���g
	constexpr int  SCENECEND_CNT_SECOND = 120;
}

//=====================================
// �O���錾
//=====================================
//----�}�l�[�W���[�N���X----
//�V�[��
class CSceneManager;
//�X�^�e�B�b�N���b�V��
class CMeshManager;
//UI
class CUIManager;
//�X�L�����b�V��
class CSkinMeshManager;
//�T�E���h
class CSoundManager;
//ImGui
class ImGuiManager;
//�J����
class CCameraManager;
//�q�[���[
class CHeroManager;
//�G�̃q�[���[
class CEnemyHeroManager;
//�L�[����
class CKeyManager;
//�G�t�F�N�g
class CEffect;
//�e�L�X�g
class WriteText;
//----�I�u�W�F�N�g�N���X----
//�^�k�L
class CRaccoonDog;
//���C
class CYui;
//�n��
class CGround;

//=====================================
// ���C�o��V�[���N���X
// �����:�Γc�D��
//=====================================
class CYuiAppearanceScene
	: public CSceneBase
{
public:
	CYuiAppearanceScene();
	~CYuiAppearanceScene();

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

	//�f�o�b�O�֐�
	void Debug();

private:
	//----�e�q�[���[�̓o��V�[���̃A�j���[�V�����֐�----
	//���C
	void YuiAppearance();
	//----�e�q�[���[�̓o��V�[���̃J�����ݒ�֐�----
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;

	//----�q�[���[�̃X�L�����b�V��----
	std::unique_ptr<CYui>   m_pYui;  //���C

	//----�o��Ɏg�p����q�[���[�ȊO�̃X�L�����b�V��----
	//�^�k�L
	std::unique_ptr<CRaccoonDog> m_pRaccoonDog;
	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----�t���O----
	//��\���t���O
	bool m_HiddenFlag;	
	//�A�j���[�V�����A�J�����������I�������Ƃ�
	bool m_AnimEndFlag;   
	//���o�X�L�b�v�t���O
	bool m_SkipFlag;

};

