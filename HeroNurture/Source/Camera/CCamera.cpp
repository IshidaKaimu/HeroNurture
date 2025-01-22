#include "CCamera.h"
#include "Scene/CSceneManager.h"

CCamera::CCamera()
	: m_Camera	()
{
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{

#if _DEBUG
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
#endif
	//�v���W�F�N�V�����̌v�Z
	Projection();

	//�J�����ϊ�
	Camera();
}

void CCamera::Camera()
{
		D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//����i�x�N�g���j.

		//�r���[�i�J�����j�ϊ�.
		D3DXMatrixLookAtLH(		//LH(Left Hand)
			&m_Camera.View,		//(out)�r���[�v�Z����.
			&m_Camera.Position, //�ʒu���
			&m_Camera.Look,		//�����_
			&vUpVec);			//����x�N�g��

}

//3�l�̃J����
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

void CCamera::Projection()
{
	//y�����̎���p�B���l��傫�������王�삪�����Ȃ�.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//���W�A���l.
	//�A�X�y�N�g�i���������j.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;	//��O0.1f�܂ŕ\��
	float far_z = 200.0f;	//����100.0f�܂ŕ\��(���l��傫����������Əd���Ȃ�)

	//�v���W�F�N�V�����i�ˉe�j�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_Camera.Proj,		//(out)�v���W�F�N�V�����v�Z����.
		fov_y,				//����p�iFOV�FField of View�j.
		aspect,				//�A�X�y�N�g.
		near_z,				//�߂��r���[���ʂ�z�l.
		far_z);				//�����r���[���ʂ�z�l.
}



