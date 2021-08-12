// CryptoRegApp.h : CryptoRegApp.DLL のメイン ヘッダー ファイル
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル

#include "Encrypt.h"
#include "Register.h"


// CCryptoRegApp
// このクラスの実装に関しては CryptoRegApp.cpp を参照してください。
//

class CCryptoRegApp : public CWinApp
{
public:
	CCryptoRegApp();

	T_CRYPTO_DATA	m_CryptoData;
	CEncrypt*		m_pEncryptObj;
	CRegister*		m_pRegisterObj;

// オーバーライド
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
