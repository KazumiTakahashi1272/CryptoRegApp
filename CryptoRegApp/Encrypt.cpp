// Encrypt.cpp: implementation of the CEncrypt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CryptoRegApp.h"
#include "Encrypt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncrypt::CEncrypt(CString keyString)
{
	m_strEncryptKey = keyString;
		
	m_initialisationSuccess = CryptAcquireContext( &m_cspContext, NULL, NULL, PROV_RSA_FULL, 0 );
	if ( m_initialisationSuccess )
	{
		m_initialisationSuccess = CryptCreateHash( m_cspContext, CALG_MD5, 0, 0, &m_hashData );
	}

	if ( m_initialisationSuccess )
	{
		m_initialisationSuccess = CryptHashData( m_hashData, (const unsigned char *)m_strEncryptKey.GetBuffer(256), m_strEncryptKey.GetLength(), 0 );
	}

	if ( m_initialisationSuccess )
	{
		m_initialisationSuccess = CryptDeriveKey( m_cspContext, CALG_RC2, m_hashData, 0, &m_keyEncryption );
	}
}

int  CEncrypt::Decrypt(string& dest,DWORD actualSize)
{
	if( m_initialisationSuccess )
	{
		if ( !CryptDecrypt( m_keyEncryption, 0, true, 0, (unsigned char *)dest.c_str(), (unsigned long *)&actualSize ) )
		{
			DWORD dw = GetLastError();
			return -1; 
		}

		dest.resize( actualSize );

		return actualSize;
	}

	return -1;
}

int CEncrypt::Encrypt(string& msg, long orginalSize)
{
	//long actualSize = msg.length();
	long actualSize = 0;
	for ( ; msg[actualSize] != _T('\0') ; actualSize++ ) ;

	if ( m_initialisationSuccess )
	{
		if ( !CryptEncrypt( m_keyEncryption, NULL, true, 0, (unsigned char *)msg.c_str(), (unsigned long *)&actualSize, orginalSize ) )
		{
			DWORD dw = GetLastError();
			return -1;
		}

		msg.resize( actualSize );
 	 
		return actualSize;
	}

	return -1;
}

CEncrypt::~CEncrypt()
{
	//RegCloseKey( m_hKey );

	CryptDestroyHash( m_hashData );
	CryptReleaseContext( m_keyEncryption, 0 );
	CryptReleaseContext (m_cspContext, 0 );
}
