#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float FASTBOSS_SPEED = 0.05f;

/*****************************************
* �o��{�X�N���X
**/
class CFastBoss
	:public CSkinMeshObject
{
public:
	CFastBoss();
	virtual ~CFastBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void AnimChange();

	void ApeAnim();

	void EvoAnim();

protected:
	D3DXVECTOR3    m_BonePos;			//�{�X:�{�[�����W
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu
	int            m_EffCnt;			//�G�t�F�N�g�̎���
};

