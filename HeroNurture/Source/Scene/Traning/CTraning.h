#pragma once
#include "Scene\CSceneBase.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "WriteText\WriteText.h"
#include "StaticMeshObject\Ground\CGround.h"
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "json.hpp"

//----�O���錾----
class CHeroManager;

//�g���[�j���O�V�[��
class CTraning
	:public CSceneBase
{
public:
	CTraning();
	~CTraning();

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

public:
	//�㏸�ʃe�L�X�g�̕`��
	void DrawUpText();

private:

	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//----�I�u�W�F�N�g�N���X----
	// �X�^�e�B�b�N���b�V��
	//�X�J�C�{�b�N�X
	std::unique_ptr<CSky> m_pSky;
	//�n��
	std::unique_ptr<CGround> m_pGround;
};