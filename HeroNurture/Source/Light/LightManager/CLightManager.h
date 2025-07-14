#pragma once
#include "Global\Global.h"
#include "Singleton\CSingleton.h"

//=====================================
// ���C�g�}�l�[�W���[�N���X
// �����:�Γc�D��
//=====================================

class CLightManager
	: public CSingleton<CLightManager>
{
private:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CLightManager>;
	~CLightManager();

public:
	//���̎擾
	LIGHT GetLight() { return m_Light; }
	
	//�ʒu�̐ݒ�
	void SetPos(const D3DXVECTOR3& pos) { m_Light.Position = pos; }
	void SetPos(float x, float y,float z)
	{
		m_Light.Position.x = x;
		m_Light.Position.y = y;
		m_Light.Position.z = z;
	}
	void SetPosX(float x){ m_Light.Position.x = x; }
	void SetPosY(float y){ m_Light.Position.y = y; }
	void SetPosZ(float z){ m_Light.Position.z = z; }
	
	//�����̐ݒ�
	void SetDir(const D3DXVECTOR3& dir) { m_Light.vDirection = dir; }
	void SetDir(float x, float y, float z)
	{
		m_Light.vDirection.x = x;
		m_Light.vDirection.y = y;
		m_Light.vDirection.z = z;
	}
	void SetDirX(float x) { m_Light.vDirection.x = x; }
	void SetDirY(float y) { m_Light.vDirection.y = y; }
	void SetDirZ(float z) { m_Light.vDirection.z = z; }

	//���C�g�̃f�o�b�O����
	void Debug();

private:
	//������A�N�Z�X����邱�Ƃ��Ȃ��悤��
	CLightManager();

private:
	//���C�g���
	LIGHT m_Light;

	//�f�o�b�O�p�ϐ�
	//�ʒu
	D3DXVECTOR3 m_DebugDirection;
};

