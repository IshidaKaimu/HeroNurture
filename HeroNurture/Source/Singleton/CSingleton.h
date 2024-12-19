#pragma once
//=====================================
// �V���O���g���N���X
//=====================================

template<typename T>

class CSingleton
{
public:
    //�V���O���g���C���X�^���X���擾����
    static T& GetInstance() {
        static T Instance;
        return Instance;
    }

    //�R�s�[�R���X�g���N�^�Ƒ�����Z�q���폜���Ĉ��������Ȃ��悤�ɂ���
    CSingleton(const CSingleton& rhs) = delete;
    CSingleton& operator = (const CSingleton& rhs) = delete;

protected:
    //�p���֌W�łȂ��O������̃R���X�g���N�^�ւ̊����֎~����
    CSingleton() = default;
    virtual ~CSingleton() = default;

};

