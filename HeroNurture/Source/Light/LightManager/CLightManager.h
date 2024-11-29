#pragma once
#include "Global\Global.h"
#include "Singleton\CSingleton.h"
class CLightManager
	: public CSingleton<CLightManager>
{
public:
	//�t�����h�錾�ŃA�N�Z�X����^����.
	friend class CSingleton<CLightManager>;
	~CLightManager();

public:
	//----�Q�b�^�[----
	//���C�g���̎擾
	LIGHT GetLight() { return m_Light; }

private:
	//������A�N�Z�X����邱�Ƃ��Ȃ��悤��
	CLightManager();

private:
	//���C�g���
	LIGHT m_Light;
};

