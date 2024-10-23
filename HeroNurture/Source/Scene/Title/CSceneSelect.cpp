#include "CSceneSelect.h"
#include "Scene/CSceneManager.h"
#include "KeyManager/CKeyManager.h"
#include "StaticMesh/MeshManager/CMeshManager.h"
#include "Sound/CSoundManager.h"
#include <cmath>
#include <iostream>
#include "ImGui/ImGuiManager/ImGuiManager.h"
#include <fstream>

//�^�C�g���V�[��
CSceneSelect::CSceneSelect()
    : m_pSky    ()
    , m_pGround ()
    , m_Opening(false)
    , m_BossApp(false)
    , m_BossEvo(false)
    , m_Special(false)
    , m_Time   (-10.0f)
{
    CCamera::GetInstance()->SetPos(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
    CCamera::GetInstance()->SetLook(D3DXVECTOR3(0.0f, 0.0f, 4.0f));

    //���C�g���
    m_Light.vDirection = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //���C�g����
}

CSceneSelect::~CSceneSelect()
{
}

//�\�z�֐�
void CSceneSelect::Create()
{
    m_pSky = new CSky();
    m_pGround = new CGround();

    //json�t�@�C���e�X�g
    json m_json;

    //     ���@�@�@���g�@�@aaa�̒��g
    m_json["Name"] = "ABC";

    ////�A�h���X�n���ŏȗ�
    //json& temp = m_json["fff"];
  

    //�t�@�C���̍쐬
    string fileName = m_json["Name"];
    string directory = ".json";
    string fullpath;
    fileName += directory;

    //�쐬�����t�@�C���ɓ��e����������
    ofstream writing_file;
    writing_file.open(fileName, ios::out);

    //writing_file.write()
    //m_json.dump(); ���s�I�ȓz
    writing_file << m_json.dump(2) << endl;
    writing_file.close();
}

//�f�[�^�ݒ�֐�
void CSceneSelect::LoadData()
{
    //���b�V���}�l�[�W���[�̃C���X�^���X��ϐ��ɑ��
    CMeshManager* MMng = CMeshManager::GetInstance();
    m_pSky->AttachMesh(CMeshManager::GetMesh(CMeshManager::Sky));
    m_pGround->AttachMesh(CMeshManager::GetMesh(CMeshManager::Ground));
}

//�j���֐�
void CSceneSelect::Releace()
{
    SAFE_DELETE(m_pSky);
    SAFE_DELETE(m_pGround);
}

//�X�V�֐�
void CSceneSelect::Update()
{

    
    //�t�F�[�h�C������
    if (!FadeIn()) { return; }

    CKeyManager::GetInstance()->Update();

    //D3DXVECTOR3 skyPos = m_pSky->GetPosition();
    //ImGui::InputFloat3(JAPANESE("����W"), skyPos);
    //m_pSky->SetPosition(skyPos);

    //�V�[���J��(��)
    if (CKeyManager::GetInstance()->IsDown(VK_RETURN))
    {
        //�I�[�v�j���O�V�[����
        m_SceneTransitionFlg = true;
        m_Opening = true;
    }
    //�t�F�[�h�A�E�g����
    if (m_SceneTransitionFlg && FadeOut()) 
    {
        if (m_Opening == true) {
            CSceneManager::GetInstance()->LoadCreate(CSceneManager::GameMain);
        }
    }


}

//�`��֐�
void CSceneSelect::Draw()
{

    CCamera::GetInstance()->Projection();
    CCamera::GetInstance()->Update();
    m_mProj = CCamera::GetInstance()->GetProjection();
    m_mView = CCamera::GetInstance()->GetViewMatrix();


    if (m_Time <= 5.0f) {
        m_Time += 0.1f;
    }

    //�X�J�C�{�b�N�X�̕`��
    m_pSky->Draw(m_mView, m_mProj, m_Light, m_Camera);

    //�n�ʂ̕`��
    m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);

    float x = Easing(m_Time);

    for (int i = 0; i < m_Statuses.size(); i++)
    {
        WriteText::GetInstance()->Draw_Text(m_Statuses[i], WriteText::Select, D3DXVECTOR2(x, 80 * i));
    }

}

//�C�[�W���O
float CSceneSelect::Easing(float x)
{
    const float c1 = 1.70158;
    const float c3 = c1 + 1.0f;

    return c3 * x * x * x - c1 * x * x;
}
