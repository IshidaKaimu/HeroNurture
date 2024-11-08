#pragma once
#include "SkinMeshObject\Hero\CHeroBase.h"
#include "Singleton\CSingleton.h"
#include <memory>

class CHeroManager
	: public CHeroBase
	, public CSingleton<CHeroManager>
{
public:
	~CHeroManager();

	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadData() override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw( LIGHT& light ) override;

	//�A�j���[�V�����֐�
	void Animation();

private:
	CHeroManager();

private:
	//�q�[���[�x�[�X�N���X
	std::unique_ptr<CHeroBase> m_Hero;
};

