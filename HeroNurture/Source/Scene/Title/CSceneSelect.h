#pragma once
#include "Scene/CSceneBase.h"
#include "SkinMeshObject/Kaito/CKaito.h"
#include "Camera/CCamera.h"
#include "StaticMeshObject/Sky/CSky.h"
#include "WriteText/WriteText.h"
#include "StaticMeshObject/Ground/CGround.h"
#include "json.hpp"


using namespace nlohmann;

//�V�[���I���V�[��
class CSceneSelect
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
	CSceneSelect();
	~CSceneSelect();


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
	//�����̓���
	float Easing(float x);

private:
	//�X�J�C�{�b�N�X
	CSky* m_pSky;

	//�n��
	CGround* m_pGround;

	//�s�i�[�p
	std::vector<std::wstring> m_Lines;
	std::wstring m_Line;

	//������i�[�p
	std::vector<std::wstring> m_Statuses;


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

