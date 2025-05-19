#pragma once
#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "StaticMeshObject\Sky\CSky.h"			//�X�J�C�{�b�N�X�N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include "StaticMeshObject\Ground\CGround.h"	//�n�ʃN���X
#include <Windows.h>

//=====================================
// �O���錾 
//=====================================
//----�}�l�[�W���[�N���X----
//�o�g�����[�h
class CBattleManager;
//�q�[���[
class CHeroManager;
//�G�̃q�[���[
class CEnemyHeroManager;
//�J����
class CCameraManager;


//=====================================
// �萔�錾 
//=====================================
namespace Constant_BattleResultScene
{
	//�J����
	const D3DXVECTOR3 WIN_CAM_POS    = { -2.4f, 2.0f, 1.1f };  //���������W
	const D3DXVECTOR3 WIN_CAM_LOOK   = { -5.0f, 2.0f, -1.0f }; //�����������_
	const D3DXVECTOR3 LOSE_CAM_POS   = { -0.3f, 1.8f, 1.8f };  //�s�k�����W
	const D3DXVECTOR3 LOSE_CAM_LOOK  = { 2.0f, 2.0f, 1.0f };   //�s�k�������_
	//----���s�e�L�X�gUI----
	const D3DXVECTOR2 RESULTTEXT_POS = { 150.0f,220.0f };      //���W
}

//=====================================
// �o�g�����ʃV�[���N���X
// �����:�Γc�D��
//=====================================
class CBattleResultScene
	:public CSceneBase
{
public:
	CBattleResultScene();
	~CBattleResultScene();

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
	//�f�o�b�O
	void Debug();

	//UI�̕`��
	void DrawUI();

private:
	//�J�����N���X
	CCameraManager* m_pCamera;

	// =======================
	// �I�u�W�F�N�g�N���X
	// =======================		
	//----�X�^�e�B�b�N���b�V��----
	std::unique_ptr<CSky> m_pSky;		//��
	std::unique_ptr<CGround> m_pGround; //�n��
};

