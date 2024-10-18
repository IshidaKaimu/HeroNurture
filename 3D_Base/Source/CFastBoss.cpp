#include "CFastBoss.h"
#include "CEffect.h"
#include "CSceneManager.h"

CFastBoss::CFastBoss()
	: m_BonePos()
	, m_AnimChange()
	, m_EffPosZ(1.0f)
{
	SetScale(0.5f, 0.5f, 0.5f);
	SetPosition(0.0f, 40.0f, 8.0f);
}

CFastBoss::~CFastBoss()
{
}

void CFastBoss::Update()
{

	//--------------------------
	//�X�L�����b�V��
	//--------------------------

	//Boss
	//�A�j���[�V�����ԍ�����
	//0:�ҋ@
	//1:?
	//2:�_���[�W
	//3:��_���[�W

}

void CFastBoss::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

void CFastBoss::AnimChange()
{
	m_AnimChange = true;
}

void CFastBoss::ApeAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
	}

	if (m_AnimNo == 1)
	{

		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 0;	  //�ړ��A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}

	if (m_vPosition.y >= 0.0f)
	{
		m_EffCnt++;

		//�G�t�F�N�g���ƂɕK�v�ȃn���h��
		//��3�\�����Đ��䂷��Ȃ�3�K�v�ɂȂ�
		static ::EsHandle hEffect = 1;
		CEffect* Eff = CEffect::GetInstance();
		Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
		Eff->Speed(hEffect, 1.0f);
		if (m_EffCnt >= 1) {
			hEffect = CEffect::Play(CEffect::Dark, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
		}

	}

	if (m_vPosition.y >= 0.0f)
	{
		m_vPosition.y -= FASTBOSS_SPEED;
	}

}

void CFastBoss::EvoAnim()
{
	SetPosition(0.0f, 0.0f, 8.0f);
}


