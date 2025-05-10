#pragma once
#include "Scene\CSceneBase.h"

//=====================================
// �萔�錾
//=====================================
namespace Constant_KaitoAppearanceScene
{
	//----�J�������----
	//�J�C�g
	const D3DXVECTOR3 CAMPOS  = { 1.0f, 0.0f, -5.0f };  //���W
	const D3DXVECTOR3 CAMLOOK = { 0.0f, 0.0f,  -5.0f }; //�����_
	//----�C�x���g���o----
	//�J����
	constexpr float CAM_MOVE_SPEED = 0.03f; //�J�����̓������x
	//���@�w�G�t�F�N�g
	const D3DXVECTOR3 MAGICSIRCLE_POS = { 0.0f, 0.5f,  -5.0f }; //���W
	const D3DXVECTOR3 MAGICSIRCLE_CAMPOS = { 1.0f, 1.5f,  -5.0f }; //���@�w���f���J�����������W
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
//----�I�u�W�F�N�g�N���X----
//�^�k�L
class CRaccoonDog;
//���C
class CYui;
//�J�C�g
class CKaito;
//�n��
class CGround;

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
	//----�e�q�[���[�̓o��V�[���̃J�����ݒ�֐�----
	void SetCamera(D3DXVECTOR3 pos, D3DXVECTOR3 look);

private:
	//�J�����}�l�[�W���[
	CCameraManager* m_pCamera;

	//----�q�[���[�̃X�L�����b�V��----
	std::unique_ptr<CYui>   m_pYui;  //���C
	std::unique_ptr<CKaito> m_pKaito;//�J�C�g

	//----�X�^�e�B�b�N���b�V��----
	//�n��
	std::unique_ptr<CGround> m_pGround;

	//----�t���O----
	//��\���t���O
	bool m_HiddenFlag;
	//�A�j���[�V�����A�J�����������I�������Ƃ�
	bool m_AnimEndFlag;

};

