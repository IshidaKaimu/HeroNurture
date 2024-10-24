#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "SkinMeshObject/Player/CPlayer.h"
#include "json.hpp"

//�Q�[�����C���V�[��
class CGameMain
	:public CSceneBase
{
public:

public:
	CGameMain();
	~CGameMain();

	//�������֐�
	void Initialize() override;
	//�\�z�֐�
	void Create() override;
	//�f�[�^�ݒ�֐�
	void LoadData() override;
	//�j���֐�
	void Releace() override;
	//�X�V�֐�
	void Update() override;
	//�`��֐�
	void Draw() override;

	//�A�J�E���g���擾
	void SetUserName(std::wstring name) { m_UserName = name; }


private:
	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//���[�U�[��
	std::wstring m_UserName;

	//�v���C���[
	CPlayer* m_pPlayer;

	D3DXMATRIX	m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX	m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.


};

