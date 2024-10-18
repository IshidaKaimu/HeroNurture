#pragma once

#include "CCharacter.h"

/**************************************************
*	�v���C���[�N���X.
**/
class CPlayer
	: public CCharacter
{
public :
	//�ړ���ԗ񋓌^
	enum enMoveState
	{
		Stop = 0,	//��~
		ForWard,	//�O�i
		BackWard,	//���
		TurnLeft,	//����]
		TurnRight	//�E��]
	};

public:
	CPlayer();
	virtual ~CPlayer() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;

	//���W�R������
	void RadioControl();

protected:
	//��]���x
	float m_TurnSpeed;	//��]���x
	float m_MoveSpeed;	//�ړ����x
	enMoveState m_MoveState;
};