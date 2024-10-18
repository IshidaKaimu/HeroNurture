#pragma once
#include "CStaticMeshObject.h"
#include "CCharacter.h"

/**************************************************
*	�n�ʃN���X.
**/
class CSky
	: public CStaticMeshObject
{
public:
	CSky();
	virtual ~CSky();

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

protected:
};

