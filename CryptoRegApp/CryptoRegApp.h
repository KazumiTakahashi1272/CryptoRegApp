// CryptoRegApp.h : CryptoRegApp.DLL �̃��C�� �w�b�_�[ �t�@�C��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��

#include "Encrypt.h"
#include "Register.h"


// CCryptoRegApp
// ���̃N���X�̎����Ɋւ��Ă� CryptoRegApp.cpp ���Q�Ƃ��Ă��������B
//

class CCryptoRegApp : public CWinApp
{
public:
	CCryptoRegApp();

	T_CRYPTO_DATA	m_CryptoData;
	CEncrypt*		m_pEncryptObj;
	CRegister*		m_pRegisterObj;

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
