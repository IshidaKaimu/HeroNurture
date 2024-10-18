#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float BOSS_SPEED = 0.05f;

/*****************************************
* �{�X�N���X
**/
class CBoss
	:public CSkinMeshObject
{
public:
	CBoss();
	virtual ~CBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	//�A�j���[�V�������x�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void AnimChange();		   //�A�j���[�V�����؂�ւ��t���O�@���i���V�[���Ŏg��
							   
	void EvoAnim();			   //�i���V�[���ł̃A�j���[�V����
							   
	void SpAnim();			   //�K�E�Z�V�[���ł̃A�j���[�V����
							   
	void DeathAnim();		   //���S�V�[���ł̃A�j���[�V����
							   
	bool SceneChange();		   //�V�[�����V�[���Z���N�g�ɖ߂�����
							   
	void EvoInit();			   //�i���V�[���ł̏�����
							   
	void SpInit();			   //�K�E�Z�V�[���ł̏�����
							   
	void DeathInit();		   //���S�V�[���ł̏�����
							   
	void Death();			   //�����G�t�F�N�g�Đ��J�n
							   
	bool AfterDeath();		   //���S��

	void AnimNoChange(int no); //�A�j���[�V�����ԍ��؂�ւ�

	bool BossFell();		   //�{�X���|��؂��Ă��邩�̔��f


protected:
	D3DXVECTOR3    m_BonePos;			//�{�X:�{�[�����W
	
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O

	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu
	int            m_EffCnt;			//�G�t�F�N�g�̎���
	bool           m_EffStart;			//�G�t�F�N�g�X�^�[�g�t���O

	int            m_DeathCnt;			//���S����
	bool           m_Death;				//�����G�t�F�N�g�Đ��t���O

	int            m_BossRadianX;        //�{�X��X����]�ϓ��p
	int            m_RotateCnt;			 //���X�ɓ|���Ă������߂̃J�E���g	

	bool           m_Fell;				 //�{�X���|��؂����t���O
	int            m_FellCnt;			 //�|��؂����ォ��̃J�E���g
};

