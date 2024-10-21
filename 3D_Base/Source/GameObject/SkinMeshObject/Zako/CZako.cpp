#include "CZako.h"

CZako::CZako()
	: m_AnimNo   ()
	, m_AnimTime ()
	, m_AnimSpeed( 0.0001 )
	, m_BonePos  ()
{
	SetScale(0.002f, 0.002f, 0.002f);
	SetPosition(0.0f, 0.0f, 8.0f);
}

CZako::~CZako()
{
}

void CZako::Update()
{
	m_pMesh->SetAnimSpeed( m_AnimSpeed );

	//--------------------------
	//�X�L�����b�V��
	//--------------------------
	//�A�j���[�V�����؂�ւ�
	if (GetAsyncKeyState('N') & 0x8000)
	{
		m_AnimNo = 2;	//�o��A�j���[�V������
		m_AnimTime = 0; //�A�j���[�V�����o�ߎ��ԏ�����
		//�o��A�j���[�V����
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}
	if (m_AnimNo == 2)
	{
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod( m_AnimNo ) < m_AnimTime)
		{
			m_AnimNo = 0;	//�ҋ@�A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}
	if (m_AnimNo == 0)
	{
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 1;	//�ړ��A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}

	//�{�[�����W�̐؂�ւ�
	m_pMesh->GetPosFromBone("entotu_Joint", &m_BonePos);

}

void CZako::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed( m_AnimSpeed );
    CSkinMeshObject::Draw( View, Proj, Light,Camera );
}
