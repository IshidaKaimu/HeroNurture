#pragma once
#include "CSound.h"		//�T�E���h�N���X.

//=====================================
// �T�E���h�}�l�[�W���[�N���X
// �����:�Γc�D��
// �����Ɠ�����
//=====================================
class CSoundManager
{
public:
	//�T�E���h���X�g�񋓌^.
	enum enList
	{
		BGM_Title,	          //�^�C�g��
		BGM_ModeSelect,       //���[�h�I��
		BGM_NatureHeroSelect, //�琬�q�[���[�I��
		BGM_Nature,			  //�琬
		BGM_BattleHeroSelect, //�퓬�q�[���[�I��
		BGM_Battle,			  //�퓬
		BGM_NatureResult,     //�琬����
		BGM_Win,	          //�퓬����(����)
		BGM_Lose,			  //�퓬����(�s�k)
		
		SE_Slash,			  //�a��.		
		SE_Damage,			  //�_���[�W		
		SE_Select,			  //�I��.		
		SE_Enter,			  //����.		
		SE_Tornade,			  //����.		
		SE_Start,			  //�X�^�[�g.		
		SE_FireBall,		  //�΋�.
		SE_Thunder,           //�d�C
		SE_TPose,             //T���|�[�Y
		SE_Up,                //�X�e�[�^�X(�㏸)
		SE_Miss,              //�X�e�[�^�X(���s)
		SE_RaccoonChange,     //�^�k�L�̕ϐg
		SE_RaccoonCollision,  //�^�k�L�̏Փ�
		SE_MagicSircle,       //���@�w�o��
		SE_Laser,			  //���G�t�F�N�g
		max,		//�ő吔.
	};

public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
	//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static CSoundManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CSoundManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}


	~CSoundManager();

	//�T�E���h�f�[�^�Ǎ��֐�.
	bool Load( HWND hWnd );
	//�T�E���h�f�[�^����֐�.
	void Release();

	//SE���Đ�����.
	static void PlaySE( enList list )   { CSoundManager::GetInstance()->m_pSound[list]->PlaySE();  }
	//���[�v�Đ�����.
	static void PlayLoop( enList list ) { CSoundManager::GetInstance()->m_pSound[list]->PlayLoop();}
	//��~����.
	static void Stop( enList list )     { CSoundManager::GetInstance()->m_pSound[list]->Stop();    }

	//���ʂ̑���
	static void Volume(enList list, int volume) { CSoundManager::GetInstance()->m_pSound[list]->SetVolume(volume); }


private://�O������A�N�Z�X�s�\.
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CSoundManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CSoundManager( const CSoundManager& rhs ) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CSoundManager& operator = ( const CSoundManager& rhs ) = delete;

private:
	CSound*		m_pSound[enList::max];
};