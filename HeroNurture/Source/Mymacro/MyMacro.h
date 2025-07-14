#pragma once
#include <crtdbg.h>//_ASSERT_EXPR()�ŕK�v.

//===========================================================
//	�}�N��.
//  ���Ɠ��Ő���
//===========================================================

//���.
#define SAFE_RELEASE(p)	if(p!=nullptr){(p)->Release();(p)=nullptr;}
//�j��.
#define SAFE_DELETE(p) if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	\
{								\
	if(p!=nullptr){				\
		delete[] (p);			\
		(p) = nullptr;			\
	}							\
}

//ImGui�@���{��Ή�.
#define JAPANESE(str) reinterpret_cast<const char*>(u8##str)