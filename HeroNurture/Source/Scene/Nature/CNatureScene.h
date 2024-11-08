#pragma once
#include "SkinMeshObject/Hero/CHeroManager.h"
#include "Scene/CSceneBase.h"
#include <memory>
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

public:
	//�q�[���[�N���X
	CHeroManager* m_pHero;

	//�J�����}�l�[�W���N���X
	CCameraManager* m_pCamera;
};

