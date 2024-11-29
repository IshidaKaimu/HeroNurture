#pragma once
#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"
#include "SkinMeshObject/Hero/CHeroBase.h"

/*****************************************
*�J�C�g�N���X
**/
class CKaito
	:public CHeroBase
{
public:
	CKaito();
	virtual ~CKaito() override;


	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadData( const json& jsondata ) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	//�A�j���[�V�����֐�
	void Animation() override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//��ʐ؂�ւ�
	bool SceneChange();

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//�J�C�g:�{�[�����W
	bool           m_Run;				//����o���t���O
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu

};

