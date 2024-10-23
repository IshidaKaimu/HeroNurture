#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"
#include "StaticMeshObject/Character/CCharacter.h"

/**************************************************
*	�n�ʃN���X.
**/
class CGround
	: public CStaticMeshObject
{
public:
	CGround();
	virtual ~CGround();

	virtual void Update() override;

	//�v���C���[��ݒ�
	void SetPlayer(CCharacter& pPlayer) { m_pPlayer = &pPlayer; }

protected:
	CCharacter* m_pPlayer;

};

