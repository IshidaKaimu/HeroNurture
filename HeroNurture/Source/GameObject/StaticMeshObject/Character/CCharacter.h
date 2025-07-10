#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"

//=====================================
//�@�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X
//  ���Ɠ��Ő���
//=====================================
class CCharacter
	: public CStaticMeshObject
{
public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() override;
	virtual void Draw() override;

	//Y�������֐L�΂������C���擾
	RAY GetRayY() const { return *m_pRayY; }

protected:
	RAY*	m_pRayY; //Y�����֔�΂������C

};

