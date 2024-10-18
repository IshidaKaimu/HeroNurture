#include "CText.h"
#include "DirectWriteCustomFont.h"

CText::CText()
    : m_pDx9()
    , m_pDevice()
    , m_pFont( nullptr )
    , m_x( 0 )
    , m_y( 0 )
{

   m_pDevice = CSceneManager::GetInstance()->GetDx9()->GetDevice();

   // �f�o�C�X�̗L�������m�F
   if (!m_pDevice) {
       MessageBox(NULL, L"DirectX device is NULL", L"Error", MB_OK | MB_ICONERROR);
       return;
   }

   //�t�H���g�̍쐬
    CreateF();
}

CText::~CText()
{
    // �t�H���g�I�u�W�F�N�g�����
    if( m_pFont ) {
        m_pFont->Release();
    }
}

void CText::SetText( const std::string& text )
{
    // �}���`�o�C�g����������C�h������ɕϊ�
    std::wstring wtext( text.begin(), text.end() );
    m_text = wtext;
}

void CText::SetPosition( float x, float y )
{
    m_x = x; // X���W��ݒ�
    m_y = y; // Y���W��ݒ�
}

HRESULT CText::Render() {
    if( m_pFont )
    {
        RECT rect;
        SetRect( &rect, static_cast<LONG>( m_x ), static_cast<LONG>( m_y ),1920, 1080 );

        // DrawText ���\�b�h�̖߂�l�� HRESULT �^�Ƃ��Ď擾
        HRESULT hr = m_pFont->DrawText( NULL, m_text.c_str(), -1, &rect, DT_NOCLIP, D3DCOLOR_XRGB( 255, 255, 255 ) );

        // HRESULT ��Ԃ�
        return hr;
    }

    // �t�H���g�I�u�W�F�N�g�� NULL �̏ꍇ�̓G���[�R�[�h��Ԃ�
    return E_FAIL;
}

void CText::CreateF()
{
    // �t�H���g�̐ݒ�
    D3DXFONT_DESC fontDesc = {
        50,                   // �t�H���g�̃T�C�Y
        0,                    // �s�v�Ȑݒ�
        FW_NORMAL,            // �t�H���g�̑���
        0,                    // �s�v�Ȑݒ�
        FALSE,                // �C�^���b�N�̂łȂ�
        DEFAULT_CHARSET,      // �����Z�b�g
        OUT_DEFAULT_PRECIS,   // �o�͐��x
        DEFAULT_QUALITY,      // �i��
        DEFAULT_PITCH,        // �s�b�`
        _T("Arial")           // �t�H���g�t�@�~��
    };

    // �t�H���g�I�u�W�F�N�g�̍쐬
    HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &fontDesc, &m_pFont);

    if (FAILED(hr)) {
        std::wstring errorMsg = L"Failed to create font. HRESULT: " + std::to_wstring(hr);
        MessageBox(NULL, errorMsg.c_str(), L"Error", MB_OK | MB_ICONERROR);
    }

}
