#pragma once
#include "SkinMeshObject\Hero\CHeroManager.h"
#include "Scene\CSceneBase.h"
#include "StaticMeshObject\Sky\CSky.h"
#include "StaticMeshObject\Ground\CGround.h"
#include <memory>

//----�O���錾----
class WriteText;


//----------------
//�琬�V�[���N���X
//----------------
class CNatureScene
	:public CSceneBase
{
public:
	CNatureScene();
	~CNatureScene();

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
	//�e�L�X�g�̕`��
	void TextDraw();

public:
	//�J�����}�l�[�W���N���X
	CCameraManager* m_pCamera;

	//----�I�u�W�F�N�g�N���X----
	//�X�^�e�B�b�N���b�V��
	//�n�ʃN���X
	CGround*		m_pGround;
	//�X�J�C�{�b�N�X�N���X
	CSky*			m_pSky;


};

