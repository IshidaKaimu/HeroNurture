#pragma once
#include "SkinMeshObject/CSkinMeshObject.h"

/**************************************************
*	�v���C���[�N���X.
**/
class CPlayer
	: public CSkinMeshObject
{
public :
	//�p�����[�^�\����
	struct enParamater
	{
		//������
		int Power;
		//����
		int Magic;
		//�f����
		int Speed;
		//�̗�
		int HP;
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
	//�v���C���[�̃p�����[�^�\����
	enParamater m_Paramater;

};