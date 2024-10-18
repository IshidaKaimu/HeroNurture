#include "CWooo.h"
#include "CEffect.h"

CWooo::CWooo()
	: m_BonePos()
	, m_Run()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
	SetScale(2.0f, 2.0f, 2.0f);
}

CWooo::~CWooo()
{
}

void CWooo::Update()
{

	//--------------------------
	//�X�L�����b�V��
	//--------------------------

	//Wooo
	//�A�j���[�V�����ԍ�����
	//0:�ҋ@
	//1:����
	//2:�a��(�E�ォ��E��)
	//3:�a��(��������E���)
	//4:�a�艺�낷
	//5:���
	//6:����o��
	//7:�_���[�W
	//8:���S

}

void CWooo::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

bool CWooo::SceneChange()
{
	if (m_EffPosZ >= 10.0f)
	{
		return true;
	}
	return false;
}

void CWooo::AnimChange()
{
	m_AnimChange = true;
}


void CWooo::SpAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.0003;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_Run = true;
			m_AnimNo = 3;	  //�ړ��A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}

}

//�K�E�Z�V�[���ł̈ʒu�̏�����
void CWooo::SpInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
}


