#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "json.hpp"
#include "SkinMeshObject/Player/CPlayer.h"
#include "Scene/GameMain/CGameMain.h"

using namespace nlohmann;

//�V�[���I���V�[��
class CTitle
	:public CSceneBase
{
public:
	//�V�[���񋓌^
	enum enSelectScene
	{
		Opening,
		BossApp,
	};

public:
	CTitle();
	~CTitle();


	//�\�z�֐�
	void Create() override;

	void Releace() override;

	//�f�[�^�ݒ�֐�
	void LoadData() override;
	//�j���֐�
	//�X�V�֐�
	void Update() override;
	//�`��֐�
	void Draw() override;
	//�����̓���
	float Easing(float x);

	//�A�J�E���g�����͏���
	void  InputName();

private:
	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//�Q�[�����C��
	CGameMain* m_pGameMain;

	//���[�U�[������
	std::wstring m_UserName;

	//�v���C���[
	CPlayer* m_pPlayer;

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

