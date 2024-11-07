#pragma once
#include "SkinMeshObject/Player/CPlayer.h"
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

	//�������֐�
	void Initialize() override;
	//�\�z�֐�
	void Create()	  override;
	//�f�[�^�ݒ�֐�
	void LoadData()	  override;
	//�j���֐�
	void Releace()	  override;
	//�X�V�֐�
	void Update()     override;
	//�`��֐�
	void Draw()		  override;


private:
	

public:

	//�v���C���[�N���X
	std::unique_ptr<CPlayer> m_pPlayer;

};

