#include "CBoss.h"
#include "CEffect.h"
#include "CSoundManager.h"

CBoss::CBoss()
	: m_BonePos    ()
	, m_AnimChange ()
	, m_EffPosZ    (1.0f)
	, m_EffCnt     ()
	, m_DeathCnt   ()
	, m_EffStart   ()
	, m_BossRadianX()
	, m_RotateCnt  ()
	, m_Fell	   ()
	, m_FellCnt	   ()
{
}

CBoss::~CBoss()
{
}

void CBoss::Update()
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

void CBoss::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	CSkinMeshObject::Draw(View, Proj, Light, Camera);
}

void CBoss::AnimChange()
{
	m_AnimChange = true;
}

void CBoss::EvoAnim()
{
	if (m_AnimNo == 0)
	{
		m_AnimSpeed = 0.01f;
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		if (m_AnimChange == true)
		{
			m_AnimNo = 2;	  //�ړ��A�j���[�V������
			m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}

	if (m_AnimNo == 2)
	{
		
		m_AnimSpeed = 0.01f;
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();
		


		if (m_AnimTime >= 0.41f)
		{
			m_EffStart = true;
			m_AnimSpeed = 0.0f;
		}


		if (m_EffStart == true)
		{
			m_EffCnt++;
		}

		if (m_EffCnt == 1) 
		{
			//�G�t�F�N�g���ƂɕK�v�ȃn���h��
			//��3�\�����Đ��䂷��Ȃ�3�K�v�ɂȂ�
			static ::EsHandle hEffect = 1;
			CEffect* Eff = CEffect::GetInstance();
			Eff->Scale(hEffect, 3.0f, 3.0f, 3.0f);
			Eff->Speed(hEffect, 0.01f);
			hEffect = CEffect::Play(CEffect::Howling, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 6.0f, m_vPosition.z - 5.0f));
			//���KSE
			CSoundManager::PlaySE(CSoundManager::SE_BossVo);
			CSoundManager::Volume(CSoundManager::SE_BossVo, 300);

		}
	}


}

bool CBoss::SceneChange()
{
	if (m_EffCnt >= 115)
	{
		return true;
	}
	return false;
}

//�i���V�[���ł̏�����
void CBoss::EvoInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);

}

//�K�E�Z�V�[���ł̏�����
void CBoss::SpInit()
{
	SetPosition(0.0f, 0.0f, -15.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	SetRotation(0.0f, D3DXToRadian(180), 0.0f);

}

//���S�V�[���ł̏�����
void CBoss::DeathInit()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	SetScale(0.5f, 0.5f, 0.5f);
	AnimNoChange(3);
}

//�K�E�Z�V�[���ł̃A�j���[�V����
void CBoss::SpAnim()
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hEffect = -1;	//�����G�t�F�N�g

	if (m_AnimNo == 0)
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

	if (m_Death == true)
	{
		m_DeathCnt++;
		if (m_DeathCnt >= 1)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect, 1.0f);
			Eff->Scale(hEffect, 1.0f, 1.0f, 1.0f);
			Eff->Rotate(hEffect, D3DXToRadian(40), 0.0, 0.0f);

			if (m_DeathCnt == 110)
			{
				hEffect = CEffect::Play(CEffect::BossDeath, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 4.0f, m_vPosition.z - 7.0));
				//�{�X�����OSE
				CSoundManager::PlaySE(CSoundManager::SE_BeforeDeath);
				//����
				CSoundManager::Volume(CSoundManager::SE_BeforeDeath, 300);

			}
			if (m_DeathCnt == 320)
			{
				CSoundManager::Stop(CSoundManager::SE_BeforeDeath);

				//����SE
				CSoundManager::PlaySE(CSoundManager::SE_BossDeath);
				//����
				CSoundManager::Volume(CSoundManager::SE_BossDeath, 300);
			}
		}
	}

	if (m_AnimNo == 2)
	{
		m_AnimSpeed = 0.01;

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		

		if (0.3 < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;
		}

	}

}

//�{�X���j�A�j���[�V����
void CBoss::DeathAnim()
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hEffect = -1;	//���ŃG�t�F�N�g


	//�_���[�W���[�V����
	if (m_AnimNo == 3)
	{
		//�r������A�j���[�V�������x���������ɂ���
		if (m_AnimTime <= 0.2) 
		{
			m_AnimSpeed = 0.007;
		}
		else 
		{
			m_AnimSpeed = 0.0015;
		}

		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_pMesh->GetAnimSpeed();

		//�A�j���[�V�����̌o�ߎ��Ԃ���莞�Ԃ𒴂�����X���n�߂�
		if (m_AnimTime > 0.4) 
		{
			if (m_BossRadianX >= -10) {
				m_RotateCnt++;
			    m_BossRadianX -= 0.5;
			}
		}

		//�{�X�̉�]�̐ݒ�
		SetRotation(D3DXToRadian(m_BossRadianX), 0.0f, 0.0f);

		//�A�j���[�V�������I��钼�O�Ŏ~�߂�
		if ((m_pMesh->GetAnimPeriod(m_AnimNo) - 0.05) < m_AnimTime)
		{
			m_AnimSpeed = 0.0f;

			//�|��؂����t���O�𗧂Ă�
			m_Fell = true;
		}
	}
	
	//�|��؂�����
	if (m_Fell == true)
	{

		m_FellCnt++;
		if(m_FellCnt >= 45)
		{
			CEffect* Eff = CEffect::GetInstance();
			Eff->Speed(hEffect, 1.0f);
			Eff->Scale(hEffect, 3.0f,3.0f, 3.0f);
			if (m_FellCnt == 46)
			{
				hEffect = CEffect::Play(CEffect::Extinction, D3DXVECTOR3(m_vPosition.x, m_vPosition.y + 3.0f, m_vPosition.z));
				//���Ŏ�
				CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_BossDeath);
				//���Ŏ�����
				CSoundManager::GetInstance()->Volume(CSoundManager::SE_BossDeath, 300);

			}
		}
	}

}

//�����G�t�F�N�g�Đ�
void CBoss::Death()
{
	m_Death = true;
}

bool CBoss::AfterDeath()
{
	if (m_DeathCnt > 420) {
		return true;
	}
	return false;
}

//�A�j���[�V�����ύX�֐�
void CBoss::AnimNoChange(int no)
{
	m_AnimNo = no;	  //�ړ��A�j���[�V������
	m_AnimTime = 0.0; //�A�j���[�V�����o�ߎ��ԏ�����
	m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

}

//�|��؂��Ă����
bool CBoss::BossFell()
{
	if (m_Fell == true)
	{
		return true;
	}
	return false;
}

