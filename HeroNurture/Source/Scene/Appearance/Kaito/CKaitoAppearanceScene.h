#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// �萔�錾
//=====================================
namespace Constant_KaitoAppearanceScene
{
	//----�J�������----
	//�J�C�g
	const D3DXVECTOR3 INIT_CAMPOS  = { 1.0f, 0.5f, -5.0f };  //�������W
	const D3DXVECTOR3 INIT_CAMLOOK = { 0.0f, 0.0f,  -5.0f }; //���������_
	//------------------
	
	//----�C�x���g���o----
	//�J����
	constexpr float CAM_MOVE_SPEED = 0.03f; //�J�����̓������x
	//���@�w�G�t�F�N�g
	const D3DXVECTOR3 MAGICSIRCLE_POS    = { 0.0f, 0.5f,  -5.0f }; //���W
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //���@�w���f���J�����������W
	const D3DXVECTOR3 MAGICSIRCLE_SCALE  = { 4.0f, 4.0f, 4.0f };   //���@�w�̊g�k
	const D3DXVECTOR3 MAGICSIRCLE_ROTATE = { D3DXToRadian(90.0f), 1.0f, 1.0f };  //���@�w�̉�]
	//���G�t�F�N�g
	const D3DXVECTOR3 LASER_POS      = { 0.0f, 0.5f, -5.0f };				 //���W
	const D3DXVECTOR3 LASER_SCALE    = { 5.0f, 5.0f, 5.0f  };				 //�g�k
	const D3DXVECTOR3 LASER_ROTATE   = { D3DXToRadian(270.0f), 1.0f, 1.0f }; //��]
	//-------------------

	//�C�x���g���o�p���l
	//----�V�[��0----
	//�ړ�������J������y���̒l
	constexpr float ANIMCHANGE_CAMPOS_Y = 10.0f;
	//�V�[����0����1�ɑJ�ڂ����邽�߂̃J�E���g
	constexpr int   ANIMCHANGE_CNT      = 60;  
	//---------------
	
	//----�V�[��1----
	//�J�������ړ�������l�̍ő�l
	const D3DXVECTOR3 MOVE_CAMPOS_MAX         = { 1.0f, 6.0f, 10.0f }; //���W
	constexpr float   MOVE_CAMLOOK_MAX_Y      = 4.0f;				   //�����_y��
	//���̃V�[���ł̏������W
	const D3DXVECTOR3 MOVE_CAMPOS_INIT	  = {  0.0f, 1.0f, 5.0f }; //���W
	//�V�[��1����2�֑J�ڂ��邽�߂ɗp����J�E���g
	constexpr int     SCENECHANGE_CNT_FAST	= 240;
	//---------------

	//----�V�[��2----
	//�J�������ړ�������l�̍ő�l
	constexpr float   MOVE_CAMPOS_MAX_Y    = 4.5f; //���Wy��
	//�V�[��2����I�����邽�߂ɗp����J�E���g
	constexpr int     SCENECEND_CNT_SECOND = 120;
	//---------------
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
//-------------------------

//----�I�u�W�F�N�g�N���X----
//�J�C�g
class CKaito;
//�n��
class CGround;
//--------------------------

//=====================================
// �J�C�g�o��V�[���N���X
// �����:�Γc�D��
//=====================================
class CKaitoAppearanceScene
	: public CSceneBase
{
public:
	CKaitoAppearanceScene();
	~CKaitoAppearanceScene();

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
	//�o��V�[���̃A�j���[�V�����֐�
	
	//�J�C�g
	void KaitoAppearance();
	
	//�o��V�[���̃J�����ݒ�֐�
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;

	//�X�L�����b�V��
	std::unique_ptr<CKaito> m_pKaito;//�J�C�g

	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;
	//----------------------------

	//----�t���O----
	//��\���t���O
	bool m_HiddenFlag;
	//�A�j���[�V�����A�J�����������I�������Ƃ�
	bool m_AnimEndFlag;
	//���o�X�L�b�v�t���O
	bool m_SkipFlag;
	//--------------

};

