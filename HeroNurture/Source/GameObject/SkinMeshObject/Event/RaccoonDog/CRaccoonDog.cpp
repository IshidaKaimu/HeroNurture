#include "CRaccoonDog.h"
#include "Effect\CEffect.h"

using namespace Constant_RaccoonDog;

CRaccoonDog::CRaccoonDog()
	: m_ReachCamFlag()
	, m_HiddenFlag  ()
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

	m_MoveY = INIT_POS.y;
	m_MoveZ = INIT_POS.z;
}

void CRaccoonDog::AppearanceAnim(float camz)
{
	//�G�t�F�N�g�n���h���̗p��
	static ::EsHandle hSteam = -1;	//���G�t�F�N�g
	//���G�t�F�N�g
	CEffect* Eff = CEffect::GetInstance();
	Eff->Speed(hSteam, 1.0f);
	Eff->Scale(hSteam, 0.1f, 0.1f, 0.1f);
	Eff->Rotate(hSteam, 0.0f, 0.0f, 0.0f);

	//�A�j���[�V�����̌o�ߎ��Ԃ����Z		
	m_AnimTime += m_pMesh->GetAnimSpeed();

	//�㉺�̓���
	UpDown();

	//�J�����Ɠ���z���ɂȂ�܂�
	if (m_vPosition.z >= camz) 
	{
		//z�������Z
		m_MoveZ -= MOVE_SPEED;
	}
	else
	{
		m_ReachCamFlag = true;
	}

	//�^�k�L���J�����ɓ��B������
	if (m_ReachCamFlag)
	{
		SetRotation(UPRIGHT_ROTATE);
		m_AnimNo = 0;
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_AnimCnt++;

		if (m_AnimCnt == STEAM_TIME)
		{
			//���G�t�F�N�g�̍Đ�
			hSteam = Eff->Play(CEffect::enList::Steam, D3DXVECTOR3(m_vPosition.x,m_vPosition.y,m_vPosition.z - STEAM_DELAY));
		}
	}

	//�J�����ɓ��B���Ă��琔�b��
	if (m_AnimCnt > HIDDEN_TIME)
	{
		//��\���ɂ���
		m_HiddenFlag = true;
	}

	//���W�̍X�V
	SetPositionY(m_MoveY);
	SetPositionZ(m_MoveZ);
}


void CRaccoonDog::Draw()
{
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	//�`��
	if (!m_HiddenFlag)
	{
		CSkinMeshObject::Draw();
	}
}

//�㉺�̓���
void CRaccoonDog::UpDown()
{
	//�J�����ɓ��B����܂ł̊�
	if (!m_ReachCamFlag) 
	{
		//���̍����܂ŏ㏸
		if (m_MoveY < MAX_UP && !m_Up)
		{
			m_MoveY += UP_SPEED;
		}
		else
		{
			//�オ��؂�����t���O�𗧂Ă�
			m_Up = true;
		}

		//�t���O���オ���Ă���ԉ��~
		if (m_Up)
		{
			m_MoveY -= UP_SPEED;
			if (m_MoveY <= INIT_POS.y)
			{
				m_Up = false;
			}
		}
	}
	else
	{
		//�J�����ɓ��B�����獂�����Œ�
		m_MoveY = INIT_POS.y;
	}
}
