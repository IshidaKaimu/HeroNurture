#include "CRaccoonDog.h"
using namespace Constant_RaccoonDog;

CRaccoonDog::CRaccoonDog()
{
}

CRaccoonDog::~CRaccoonDog()
{
}

void CRaccoonDog::Initialize()
{
	m_AnimNo = 1;
	m_AnimSpeed = 0.85f;
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//�����ݒ�
	SetPosition(INIT_POS);    //���W
	SetScale(INIT_SCALE);     //�g�k
	SetRotation(INIT_ROTATE); //��]

	m_MoveZ = INIT_POS.z;
}

void CRaccoonDog::AppearanceAnim(float camz)
{
	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();
	//�J�����Ɠ���z���ɂȂ�܂�
	if (m_vPosition.z >= camz) 
	{
		//z�������Z
		m_MoveZ -= MOVE_SPEED;
	}

	//���W�̍X�V
	SetPositionZ(m_MoveZ);
}


void CRaccoonDog::Draw()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//�`��
	CSkinMeshObject::Draw();
}
