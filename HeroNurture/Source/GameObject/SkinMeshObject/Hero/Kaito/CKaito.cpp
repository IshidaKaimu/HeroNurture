#include "CKaito.h"
#include "Effect/CEffect.h"
#include "Sound/CSoundManager.h"

CKaito::CKaito()
	: m_BonePos		()
	, m_Run			()
	, m_AnimChange	()
	, m_EffPosZ		(1.0f)
	, m_EffCnt		()
	, m_MagicCnt	()
	, m_SlashCnt	()
	, m_RootCnt		()
	, m_White		()
	, m_Magic		()
	, m_Setup		()
	, m_Slash		()
	, m_Root		()
{
}

CKaito::~CKaito()
{
}

void CKaito::Update()
{

	//--------------------------
	//�X�L�����b�V��
	//--------------------------
	
	//Kaito
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

void CKaito::Draw( LIGHT& Light )
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw( Light );
}

bool CKaito::SceneChange()
{
	if (m_EffPosZ >= 10.0f)
	{
		return true;
	}
	return false;
}

void CKaito::AnimChange()
{
	m_AnimChange = true;
}

//�I�[�v�j���O�ł̈ʒu�̏�����
void CKaito::OpInit()
{
	SetPosition(0.0f, 0.0f, 8.0f);
	SetScale(0.5f, 0.5f, 0.5f);
}

void CKaito::OPAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_Run = true;
			m_AnimNo = 1;	  //�ړ��A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}

	}
   if(m_AnimNo == 1)
	{
	   if (m_AnimChange == true)
	   {
		   m_Run = false;
		   m_AnimNo = 2;	  //�ړ��A�j���[�V������
		   m_AnimTime = 0.0f; //�A�j���[�V�����o�ߎ��ԏ�����
		   m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		   //�a��SE
		   CSoundManager::PlaySE(CSoundManager::SE_Slash);
		   CSoundManager::Volume(CSoundManager::SE_Slash, 300);

	   }
	}

	if (m_AnimNo == 2)
	{
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		if (0.3 < m_AnimTime)
		{
			m_SlashCnt++;

			m_AnimSpeed = 0.0f;
			//�G�t�F�N�g���ƂɕK�v�ȃn���h��
			//��3�\�����Đ��䂷��Ȃ�3�K�v�ɂȂ�
			static ::EsHandle hEffect = -1;
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect, 0.0f, 0.0f, D3DXToRadian(90));
			Eff->Speed(hEffect, 0.5);
			m_EffPosZ += 0.08f;
			hEffect = CEffect::Play(CEffect::Sword, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z - m_EffPosZ));


		}
	}

	if (m_Run == true)
	{
		m_vPosition.z -= KAITO_SPEED;
	}

}

void CKaito::SpAnim()
{

	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hEffect = -1;	//�p���[�A�b�v
	static ::EsHandle hEffect2 = 1; //�����@�ۂ���
	static ::EsHandle hEffect3 = 2; //�a��
	static ::EsHandle hEffect4 = 3; //�O��


	//�A�j���[�V�����ԍ�0 1
	if (m_AnimNo == 0 && !m_White)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			AnimNoChange(4);
		}
	}

	//�A�j���[�V�����ԍ�0 2
	if (m_AnimNo == 0 && m_White)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		//�o��A�j���[�V�����̏I�����Ԃ𒴂���?
		if (m_Run == true)
		{
			AnimNoChange(1);
		}
	}

	if (m_AnimNo == 1)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

	}

	if(m_AnimNo == 4 && m_White == false)
	{
		m_AnimSpeed = 0.01;
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (0.3 < m_AnimTime)
		{
			m_EffCnt++;
			m_AnimSpeed = 0.0f;
			if (m_EffCnt > 1)
			{
				//�p���[�A�b�v�G�t�F�N�g
				CEffect* Eff = CEffect::GetInstance();
				Eff->Scale(hEffect,4.0f, 4.0f, 4.0f);
				if (m_EffCnt == 3) {
					hEffect = CEffect::Play(CEffect::Power, D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z));
					CSoundManager::PlaySE(CSoundManager::SE_Sp);
					CSoundManager::Volume(CSoundManager::SE_Sp, 300);
				}
				if (m_EffCnt > 60)
				{
					m_White = true;
					m_EffCnt = 0;
				}
			}
		}

	}

	if (m_AnimNo == 3 && m_Slash == false)
	{
		m_AnimSpeed = 0.001;
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		if ((0.001 < m_AnimTime))
		{
			m_AnimSpeed = 0.0f;
			m_Setup = true;
		}
	}

	if (m_AnimNo == 3 && m_Slash == true)
	{
		m_AnimSpeed = 0.01;
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		m_SlashCnt++;
		if (m_SlashCnt > 1) {
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect3,7.0, 7.0f, 7.0f);
			Eff->Rotate(hEffect3, 0.0, 0.0, D3DXToRadian(120));
			if (m_SlashCnt == 2) {
				hEffect3 = CEffect::Play(CEffect::BigSlash, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z - 4.5));
				//�O���pSE
				CSoundManager::PlaySE(CSoundManager::SE_Slash);
				//����
				CSoundManager::Volume(CSoundManager::SE_Slash, 300);

			}
		}

		if (0.3 < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;
		}
	}

	//�ړ�����
	if (m_Run == true)
	{
		m_vPosition.z -= KAITO_SPEED * 5;
	}

	//���@
	if (m_Magic == true)
	{
		m_MagicCnt++;
		if ( m_MagicCnt >= 1) 
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect2, 1.0f);
			Eff->Scale(hEffect2, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect2, 1.0f, D3DXToRadian(30), 1.0f);
			if (m_MagicCnt == 2) {
				hEffect2 = CEffect::Play(CEffect::Magic, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 2.0f, m_vPosition.z));
				//�O���pSE
				CSoundManager::PlaySE(CSoundManager::SE_Charge);
				//����
				CSoundManager::Volume(CSoundManager::SE_Charge, 300);

			}
		}
	}
	else
	{
		CEffect::GetInstance()->Stop(hEffect2);
	}

	//�O���\��
	if (m_Root == true)
	{
		m_RootCnt++;
		if (m_RootCnt >= 1)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect4, 0.8f);
			Eff->Scale(hEffect4, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect4, 0.0f, D3DXToRadian(90), 0.0f);
			if (m_RootCnt == 2) {
				hEffect4 = CEffect::Play(CEffect::Root, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 2.0f, m_vPosition.z + 5.0f));
				//�O���pSE
				CSoundManager::PlaySE(CSoundManager::SE_Root);
				//����
				CSoundManager::Volume(CSoundManager::SE_Root, 300);

			}
		}
	}
	else
	{
		CEffect::GetInstance()->Stop(hEffect4);
	}

}

//�K�E�Z�V�[���ł̈ʒu�̏�����
void CKaito::SpInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	m_AnimNo = 0;
}

//���t�F�[�h�J�n
bool CKaito::WhiteStart()
{
	if (m_White == true)
	{
		return true;
	}
	return false;
}

void CKaito::Run(bool run)
{
	m_Run = run;
}

void CKaito::Wait()
{
	AnimNoChange(0);
}

//�A�j���[�V�����ύX�֐�
void CKaito::AnimNoChange(int no)
{
	m_AnimNo = no;	  //�ړ��A�j���[�V������
	m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//�A�j���[�V�������I�������
bool CKaito::EndAnim(int no)
{
	if (m_pMesh->GetAnimPeriod(no) < m_AnimTime)
	{
		return true;
	}
	return false;
}

//�\������������
bool CKaito::Setup()
{
	if (m_Setup == true)
	{
		return true;
	}
	return false;
}

//���@�w����
void CKaito::Magic(bool magic)
{
	m_Magic = magic;
}


void CKaito::Slash()
{
	m_Slash = true;
}

void CKaito::Root()
{
	m_Root = true;
}

