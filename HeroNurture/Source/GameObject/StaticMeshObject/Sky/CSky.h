#pragma once
#include "StaticMeshObject\CStaticMeshObject.h"
#include "StaticMeshObject\Character\CCharacter.h"
#include "StaticMeshObject\Sky\SkyMesh\CSkyMesh.h"

//=====================================
// ��N���X
// �����:�Γc�D��
//=====================================
class CSky
	: public CGameObject
{
public:
	CSky();
	virtual ~CSky();

	//���b�V���f�[�^�ݒ�
	void LoadData();
	//�X�V�֐�
	virtual void Update() override;
	//�`��֐�
	virtual void Draw() override;

private:
	
	//���b�V����ڑ�����.
	void AttachMesh(CSkyMesh& pskymesh) {
		m_pSkyMesh = &pskymesh;
	}
	//���b�V����؂藣��.
	void DetachMesh() {
		m_pSkyMesh = nullptr;
	}

protected:
	CSkyMesh* m_pSkyMesh;

};

