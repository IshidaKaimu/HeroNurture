#pragma once
#include "SkinMeshObject\CSkinMeshObject.h"
#include "SkinMeshObject\Hero\CHeroBase.h"

//----�O���錾----
class CSceneManager;

//=====================================
//���C�N���X
//����ҁF�Γc�D��
//=====================================
class CYui
	:public CHeroBase
{
public:
	CYui();
	virtual ~CYui()	override;

	//�������֐�
	void Initialize() override;

	//�f�[�^�ǂݍ��݊֐�
	void LoadMeshData() override;

	//�p�����[�^���ǂݍ���
    void LoadParamData(const json& jsondata) override;

	//�X�V�֐�
	void Update() override;

	//�`��֐�
	void Draw() override;

	// =======================
	// �e�V�[�����Ƃ̃A�j���[�V����
	// =======================
	//�q�[���[�I���V�[�� 
	void SelectAnimation() override;
	// �琬�V�[��		
	void NatureAnimation(int no) override;

private:
	//�A�j���[�V�����X�s�[�h�̐ݒ�
	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	//�A�j���[�V�����؂�ւ��t���O���Ă�
	void AnimChange();

protected:
	D3DXVECTOR3    m_BonePos;			//�J�C�g:�{�[�����W
	bool           m_Run;				//����o���t���O
	bool           m_AnimChange;		//�A�j���[�V�����؂�ւ��t���O
	float          m_EffPosZ;			//�G�t�F�N�g��Z���ʒu

};

