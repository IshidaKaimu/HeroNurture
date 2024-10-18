#pragma once
#pragma once
#include "CSkinMeshObject.h"

constexpr float WOOO_SPEED = 0.05f;

/*****************************************
*wooo�N���X
**/
class CWooo
	:public CSkinMeshObject
{
public:
	CWooo();
	virtual ~CWooo() override;


	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	bool SceneChange();

	void AnimChange();

	void SpAnim();

	void SpInit();

protected:
	D3DXVECTOR3    m_BonePos;			//�J�C�g:�{�[�����W
	bool           m_Run;				//����o���t���O
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu
};

