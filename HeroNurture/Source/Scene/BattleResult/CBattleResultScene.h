#pragma once
#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "StaticMeshObject\Sky\CSky.h"			//�X�J�C�{�b�N�X�N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include "StaticMeshObject\Ground\CGround.h"	//�n�ʃN���X
#include "SkinMeshObject\Hero\CHeroManager.h"	//�v���C���[�N���X
#include <Windows.h>

//=====================================
// �萔�錾 
//=====================================
//----���s�e�L�X�gUI----
const D3DXVECTOR2 RESULTTEXT_POS = { 250.0f,300.0f }; //���W


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


};

