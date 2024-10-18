#pragma once

#include "CCharacter.h"

/**************************************************
*	�v���C���[�N���X.
**/
class CPlayer
	: public CCharacter
{
public :
	//�p�����[�^�񋓌^
	enum enParamater
	{
		Power,
		Magic,
		Speed,
		HP,
		max,
	};

public:
	CPlayer();
	virtual ~CPlayer() override;

	//�f�[�^�ݒ�֐�
	void SetData();


	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;


	

protected:

};