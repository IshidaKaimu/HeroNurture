#pragma once
#include <d3dx9.h> // DirectX 9�̃w�b�_�[���܂߂܂�
#include <string>
#include "CDirectX9.h"
#include "Scene/CSceneManager.h"

//=============================================================================
//	�e�L�X�g�N���X
//  GitHub�����p
//=============================================================================
class CText {
public:
    // �R���X�g���N�^�FDirect3D�f�o�C�X���󂯎��A�t�H���g�I�u�W�F�N�g���쐬���܂�
    CText();

    // �f�X�g���N�^�F�t�H���g�I�u�W�F�N�g�̉�����s���܂�
    ~CText();

    //DirectX9�̎擾
    void SetDx9( CDirectX9& Dx9 ) { m_pDx9 = &Dx9; }

    // �\������e�L�X�g��ݒ肵�܂�
    void SetText( const std::string& text );

    // �e�L�X�g��\������ʒu��ݒ肵�܂�
    void SetPosition( float x, float y );

    // �e�L�X�g��`�悵�܂�
    HRESULT Render();

    //�e�L�X�g�̍쐬
    void CreateF();

private:
    CDirectX9*         m_pDx9;
    LPDIRECT3DDEVICE9  m_pDevice; // Direct3D�f�o�C�X�ւ̃|�C���^
    LPD3DXFONT m_pFont;           // �t�H���g�I�u�W�F�N�g�ւ̃|�C���^
    std::wstring m_text;          // std::wstring�ɕύX
    float m_x, m_y;               // �e�L�X�g�̕\���ʒu
};