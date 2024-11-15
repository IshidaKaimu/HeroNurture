#pragma once
#include "Scene/CSceneBase.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Hero/CHeroBase.h"
#include "json.hpp"

//�Q�[�����C���V�[��
class CGameMain
	:public CSceneBase
{
public:
	CGameMain();
	~CGameMain();

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
	//�A�J�E���g���擾
	void SetUserName(std::wstring name) { m_UserName = name; }


private:

	//�J�����}�l�[�W��
	CCameraManager* m_pCamera;

	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//���[�U�[��
	std::wstring m_UserName;

	//�f�o�b�O�p
	D3DXVECTOR3 CamPos;
	D3DXVECTOR3 CamLook;	
};