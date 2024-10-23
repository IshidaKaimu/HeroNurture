#pragma once
#include "StaticMeshObject/CStaticMeshObject.h"
#include "StaticMeshObject/Character/CCharacter.h"

/**************************************************
*	’n–ÊƒNƒ‰ƒX.
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

