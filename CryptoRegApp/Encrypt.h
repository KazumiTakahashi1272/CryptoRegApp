// Encrypt.h: interface for the CEncrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCRYPT_H__AE0B9B78_D27C_477E_B342_CE13FF433314__INCLUDED_)
#define AFX_ENCRYPT_H__AE0B9B78_D27C_477E_B342_CE13FF433314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WIN32_WINNT 0x0400
#include "wincrypt.h"
#include "CryptoReg.h"

//#define MY_ENCODING_TYPE (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)


class CEncrypt  
{
public:
	CEncrypt(CString keyValue);
	virtual ~CEncrypt();
	int  CEncrypt::Decrypt(string& dest,DWORD actualSize);
	int  CEncrypt::Encrypt(string& msg,long orginalSize);

private:
	//HKEY hKey;
	CString		m_strEncryptKey;
	int			m_initialisationSuccess;
	HCRYPTKEY	m_keyEncryption;
	HCRYPTPROV	m_cspContext;
	HCRYPTHASH	m_hashData;

};

#endif // !defined(AFX_ENCRYPT_H__AE0B9B78_D27C_477E_B342_CE13FF433314__INCLUDED_)
