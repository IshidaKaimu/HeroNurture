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

#if DEBUG
	//�J�������W�̃f�o�b�N�R�}���h.
	float add_value = 0.1f;
	if (GetAsyncKeyState('W') & 0x8000) {
		m_Camera.Position.y += add_value;
		m_Camera.Look.y += add_value;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		m_Camera.Position.y -= add_value;
		m_Camera.Look.y -= add_value;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		m_Camera.Position.x -= add_value;
		m_Camera.Look.x -= add_value;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		m_Camera.Position.x += add_value;
		m_Camera.Look.x += add_value;
	}
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_Camera.Position.z += add_value;
		m_Camera.Look.z += add_value;
	}
	if (GetAsyncKeyState('E') & 0x8000) {
		m_Camera.Position.z -= add_value;
		m_Camera.Look.z -= add_value;
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



