#include "CShot.h"

CShot::CShot()
	: m_Display		 ( false )
	, m_MoveDirection()
	, m_MoveSpeed    ()
	, m_DisplayTime  ()
{
}

CShot::~CShot()
{
}

void CShot::Update()
{

	if( m_Display == true ){
		m_vPosition += m_MoveDirection * m_MoveSpeed  ;

		m_DisplayTime--;
		if( m_DisplayTime < 0 ){
			//�����Ȃ����ɒu���Ă���.
			m_vPosition = D3DXVECTOR3( 0.0f, -10.0f, 0.0f );
			m_Display = false;
		}
	}
}

void CShot::Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera )
{
	if( m_Display == true ){
		CStaticMeshObject::Draw( View, Proj, Light, Camera );
	}
}

void CShot::Reload( const D3DXVECTOR3& Pos, float RotY )
{
	//�e�����ł�����I��
	if (m_Display == true) return;

	m_vRotation.y = RotY;//�e�̌���(������)���ς���
	m_vPosition = Pos;
	m_Display = true;
	m_MoveDirection.y = RotY;
	m_MoveSpeed = 0.2f;
	m_DisplayTime = FPS * 3;	//��3�b���炢�\������

	//Z���x�N�g��(z+�����ւ̒P�ʃx�N�g��)
    //������( �傫�� )���P�̃x�N�g����P�ʃx�N�g���Ƃ���
	D3DXVECTOR3 vecAxisZ(0.0f, 0.0f, 1.0f);

	//Y�����̉�]�s��
	D3DXMATRIX mRotationY;
	//Y����]�s����쐬
	D3DXMatrixRotationY(
		&mRotationY,	//(out�s��)
		m_MoveDirection.y); //�v���C���[��Y�����̉�]�l

	//Y����]�s����g����Z���x�N�g�������W�ϊ����Ă���
	D3DXVec3TransformCoord(
		&m_MoveDirection,//(out)�ړ������x�N�g��
		&vecAxisZ,		//(in)Z���x�N�g��
		&mRotationY);	//Y����]�s��

}
