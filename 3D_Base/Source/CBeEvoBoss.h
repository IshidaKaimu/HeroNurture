#pragma once
#include "CSkinMeshObject.h"

constexpr float BEEVOBOSS_SPEED = 0.05f;

/*****************************************
* �i���O�{�X�N���X
**/
class CBeEvoBoss
	:public CSkinMeshObject
{
public:
	CBeEvoBoss();
	virtual ~CBeEvoBoss() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void EvoAnim();

	void EffStart();

protected:
	D3DXVECTOR3    m_BonePos;			//�{�X:�{�[�����W
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu
	float          m_EffScaX;			//�G�t�F�N�g�X�P�[��X
	float          m_EffScaY;			//�G�t�F�N�g�X�P�[��Y
	float          m_EffScaZ;			//�G�t�F�N�g�X�P�[��Z
	int            m_EffCnt;			//�G�t�F�N�g�̎���;
	bool           m_EffStart;			//�G�t�F�N�g����
	

};
