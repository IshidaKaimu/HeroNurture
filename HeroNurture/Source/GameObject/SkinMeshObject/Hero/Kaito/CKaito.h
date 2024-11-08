#pragma once
#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "SkinMeshObject/Hero/CHero.h"

constexpr float KAITO_SPEED = 0.05f;

/*****************************************
*�J�C�g�N���X
**/
class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	virtual void Update() override;
	virtual void Draw( LIGHT& Light ) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//��ʐ؂�ւ�
	bool SceneChange();

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

	//�I�[�v�j���O�V�[���ł̏�����
	void OpInit();

	//�I�[�v�j���O�V�[���ł̃A�j���[�V����
	void OPAnim();

	//�K�E�Z�V�[���ł̏�����
	void SpInit();
	
	//�K�E�Z�V�[���ł̃A�j���[�V����
	void SpAnim();

	//���t�F�[�h�J�n�t���O���Ă�
	bool WhiteStart();

	//����o���t���O�𗧂Ă�
	void Run( bool run);

	//�ҋ@���[�V������
	void Wait();

	//�A�j���[�V�����ԍ��؂�ւ�
	void AnimNoChange(int no);

	//�A�j���[�V�������I�������
	bool EndAnim(int no);

	//�\������
	bool Setup();

	//���@�w����
	void Magic(bool magic);

	//�a�����[�V�����ĊJ
	void Slash();

	//�O���G�t�F�N�g�J�n
	void Root();

protected:
	D3DXVECTOR3    m_BonePos;			//�J�C�g:�{�[�����W
	bool           m_Run;				//����o���t���O
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu

	//�G�t�F�N�g�֘A�̃J�E���g
	int            m_EffCnt;			//�p���[�A�b�v�G�t�F�N�g�̃J�E���g
	int            m_MagicCnt;			//���@�w�G�t�F�N�g�̃J�E���g
	int            m_SlashCnt;			//�a���G�t�F�N�g�̃J�E���g
	int            m_RootCnt;			//�O���G�t�F�N�g�̃J�E���g

	//�t���O
	bool           m_White;				//���t�F�[�h

	//�G�t�F�N�g�֘A�̃t���O
	bool		   m_Magic;				//�����@�t���O
	bool           m_Setup;				//�\�������t���O
	bool		   m_Slash;				//�a���t���O
	bool           m_Root;				//�O���t���O

};

