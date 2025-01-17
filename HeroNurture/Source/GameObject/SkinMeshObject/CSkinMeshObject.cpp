#include "CSkinMeshObject.h"
#include "Camera\CameraManager\CCameraManager.h"
#include "Light\LightManager\CLightManager.h"

CSkinMeshObject::CSkinMeshObject()
	: m_pMesh    ( nullptr )
	, m_pBSphere ( nullptr )
	, m_pAnimCtrl( nullptr )
{
	m_pBSphere = new CBoundingSphere();
}

CSkinMeshObject::~CSkinMeshObject()
{
	SAFE_DELETE(m_pBSphere);
	DetachMesh();
}

void CSkinMeshObject::Update()
{
	if (m_pMesh == nullptr) {
		return;
	}
}

void CSkinMeshObject::Draw()
{
	if (m_pMesh == nullptr) {
		return;
	}

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	//�J���������擾
	CAMERA camera = CCameraManager::GetInstance().GetCamera();
	//���C�g�����擾
	LIGHT  light = CLightManager::GetInstance().GetLight();

	//�����_�����O.
	m_pMesh->Render(camera.View, camera.Proj, light, camera.Position, m_pAnimCtrl);
}

//���b�V����ڑ�����
void CSkinMeshObject::AttachMesh(CSkinMesh& pMesh)
{
	m_pMesh = &pMesh;

	//�A�j���[�V�����R���g���[�����擾
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimationController();

	//�A�j���[�V�����R���g���[���̃N���[�����쐬
	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl)))	//�N���[���쐻��
	{
		_ASSERT_EXPR(false, L"�A�j���[�V�����R���g���[���̃N���[���쐻���s");
	}
}

//���b�V����؂藣��
void CSkinMeshObject::DetachMesh()
{
	m_pMesh = nullptr;

	SAFE_RELEASE(m_pAnimCtrl);
}


