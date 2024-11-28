#pragma once
#include "Scene\CSceneBase.h"					//�V�[���x�[�X�N���X
#include "Camera\CameraManager\CCameraManager.h"//�J�����}�l�[�W���N���X
#include "StaticMeshObject\Sky\CSky.h"			//�X�J�C�{�b�N�X�N���X
#include "WriteText\WriteText.h"				//�e�L�X�g�`��N���X
#include "StaticMeshObject\Ground\CGround.h"	//�n�ʃN���X
#include "SkinMeshObject\Hero\CHeroManager.h"		//�v���C���[�N���X
#include <memory>
#include <Windows.h>

//json�N���X
class CJson;

//�V�[���I���V�[��
class CTitle
	:public CSceneBase
{
public:
	CTitle();
	~CTitle();


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

	//�����̓���
	float Easing(float x);

	//�A�J�E���g�����͏���
	void  InputName();

	//wstring����string�ւ̕ϊ�
	std::string WstringToString(std::wstring owstring);

private:

	//�J�����N���X
	CCameraManager* m_pCamera;

	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//���[�U�[������
	std::wstring m_UserName;

	//Json�N���X
	std::unique_ptr<CJson> m_pJson;

	//�v���C���[
	std::unique_ptr<CHeroManager> m_pHero;

	//----�t���O----
	//�I�[�v�j���O�Ɉڂ点��t���O
	bool m_Opening;
	//�{�X�o���V�[���Ɉڂ点��t���O
	bool m_BossApp;
	//�{�X�i���V�[���Ɉڂ点��t���O
	bool m_BossEvo;
	//�K�E�Z�V�[���Ɉڂ点��t���O
	bool m_Special;
	//�{�X���j�V�[���Ɉڂ点��t���O
	bool m_BossDeath;

	//���Ԍo�߂ł����X
	float m_Time;


};

