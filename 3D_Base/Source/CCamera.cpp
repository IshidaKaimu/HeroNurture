#include "CCamera.h"
#include "CSceneManager.h"

CCamera::CCamera()
	: m_Camera	()
	, m_mView	()
	, m_mProj	()
	, m_ShakeAmp()
	, m_ShakeFre()
	, m_ShakeDuration()
	, m_ShakeTime()
	, m_Origin  ()
	, m_IsShaking(false)
{
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{

	//�J�����̗h��
	if (m_IsShaking == true)
	{
		//�o�ߎ��Ԃ��X�V
		m_ShakeTime += 0.016f; //16�~���b

		//�h��̐U�����v�Z
		float shakeX = m_ShakeAmp * sin(m_ShakeFre * m_ShakeTime);
		float shakeY = m_ShakeAmp * cos(m_ShakeFre * m_ShakeTime);

		m_ShakeOffset = D3DXVECTOR3(shakeX,shakeY,0);

		//���̃J�����ʒu�ɗh���������
		m_Camera.Position = m_Origin + m_ShakeOffset;
	}
	else
	{
		//�V�F�C�N�I����A���̃J�����ʒu�ɖ߂�
		m_IsShaking = false;
		m_ShakeOffset = D3DXVECTOR3(0, 0, 0);
		m_Camera.Position = m_Origin;
	}

	CSceneManager::GetInstance()->SetCameraPos(m_Camera.Position);

	//�J�������W�̃f�o�b�N�R�}���h.
	float add_value = 0.1f;
	if (GetAsyncKeyState('W') & 0x8000) {
		m_Camera.Position.y += add_value;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_Camera.Position.y -= add_value;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_Camera.Position.x -= add_value;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_Camera.Position.x += add_value;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_Camera.Position.z += add_value;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		m_Camera.Position.z -= add_value;
	}

}

void CCamera::Camera(D3DXMATRIX& view, D3DXMATRIX& proj)
{
		D3DXVECTOR3 cam_pos		= m_Camera.Position;
		D3DXVECTOR3 cam_look	= m_Camera.Look;
		D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//����i�x�N�g���j.

		//�r���[�i�J�����j�ϊ�.
		D3DXMatrixLookAtLH(		//LH(Left Hand)
			&view,	//(out)�r���[�v�Z����.
			&cam_pos, &cam_look, &vUpVec);

		
		//y�����̎���p�B���l��傫�������王�삪�����Ȃ�.
		float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//���W�A���l.
		//�A�X�y�N�g�i���������j.
		float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
		float near_z = 0.1f;	//��O0.1f�܂ŕ\��
		float far_z = 200.0f;	//����100.0f�܂ŕ\��(���l��傫����������Əd���Ȃ�)

		//�v���W�F�N�V�����i�ˉe�j�ϊ�.
		D3DXMatrixPerspectiveFovLH(
			&proj,		//(out)�v���W�F�N�V�����v�Z����.
			fov_y,		//����p�iFOV�FField of View�j.
			aspect,		//�A�X�y�N�g.
			near_z,		//�߂��r���[���ʂ�z�l.
			far_z);		//�����r���[���ʂ�z�l.
}

void CCamera::ThirdPersonCamera(CAMERA* pCamera, const D3DXVECTOR3& TargetPos, float TargetRotY)
{
	//Z���x�N�g��
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);

	//Y�����̉�]�s��
	D3DXMATRIX mRotationY;
	//Y����]�s����쐬
	D3DXMatrixRotationY(
		&mRotationY,	//(out�s��)
		TargetRotY); //�Ώۂ�Y�����̉�]�l

	//Y����]�s����g����Z���x�N�g�������W�ϊ����Ă���
	D3DXVec3TransformCoord(
		&vecAxisZ,		//(out)Z���x�N�g��
		&vecAxisZ,		//(in)Z���x�N�g��
		&mRotationY);	//Y����]�s��

	//�J�����̈ʒu�A�����_��Ώۂɂ��낦��
	pCamera->Position = TargetPos;
	pCamera->Look = TargetPos;

	//�J�����̈ʒu�A�����_��Z���x�N�g����p���Ē���
	pCamera->Position -= vecAxisZ * 4.0f;//�Ώۂ̔w����
	pCamera->Look += vecAxisZ * 3.0f;//�Ώۂ�����Ō�������

	//�J�����̈ʒu�A�����_�̍��������ꂼ�������
	pCamera->Position.y += 2.0f;
	pCamera->Look.y += 0.5f;

}
//�h��̎��s
void CCamera::StartShake(float ampl, float fre, float duration, D3DXVECTOR3 origin)
{
	m_ShakeAmp = ampl;
	m_ShakeFre = fre;
	m_ShakeDuration = duration;
	m_ShakeTime = 0.0f;
	m_Origin =  origin;
	m_IsShaking = true;
}
D3DXVECTOR3 CCamera::GetCameraPosition(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 basePosition = pos;

	D3DXVECTOR3 shakeOffset = m_ShakeOffset;

	return basePosition + shakeOffset;
}
//�J�����̗h��
D3DXVECTOR3 CCamera::ApplyShake(const D3DXVECTOR3& origin )
{
	if (m_IsShaking)
	{
		return origin + m_ShakeOffset;
	}
	return origin;
}



