#include "CHeroManager.h"
#include "SkinMeshObject\Hero\Yui\CYui.h"
#include "SkinMeshObject\Hero\Kaito\CKaito.h"

CHeroManager::CHeroManager()
    :m_Hero ()
{
    m_Hero = std::make_unique<CYui>();
}

CHeroManager::~CHeroManager()
{
}

//�������֐�
void CHeroManager::Initialize()
{
    //�e�q�[���[�N���X�̏�����
    m_Hero->Initialize();
}

//�f�[�^�ǂݍ��݊֐�
void CHeroManager::LoadData()
{
    //�e�q�[���[�N���X�̃f�[�^�ǂݍ���
    m_Hero->LoadData();
}

//�X�V�֐�
void CHeroManager::Update()
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Update();
}

//�`��֐�
void CHeroManager::Draw( LIGHT& light )
{
    //�e�q�[���[�N���X�̍X�V�֐�
    m_Hero->Draw( light );
}

//�A�j���[�V�����֐�
void CHeroManager::Animation()
{
    m_Hero->Animation();
}

//�q�[���[�ݒ�֐�
void CHeroManager::SetHero(enHeroList list)
{
    //�q�[���[��ݒ�
    m_Hero = Create(list);
}

//�e�q�[���[�N���X�̃C���X�^���X����
std::unique_ptr<CHeroBase> CHeroManager::Create(enHeroList list)
{
    switch (list)
    {
    case CHeroManager::Yui:     return std::make_unique<CYui>();
    case CHeroManager::Kaito:   return std::make_unique<CKaito>();
    case CHeroManager::Max:     return nullptr;
    default:                    return nullptr;

    }

}


