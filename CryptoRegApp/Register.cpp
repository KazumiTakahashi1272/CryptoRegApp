// Register.cpp: implementation of the CRegister class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CryptoRegApp.h"
#include "Register.h"
#include "CryptoReg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegister::CRegister(T_CRYPTO_DATA* pCryptoData)
{
	DWORD dwDisposition = 0;
	
	RegCreateKeyEx( pCryptoData->m_hKey,
					pCryptoData->m_subKey.c_str(),
					0, NULL, 0, KEY_ALL_ACCESS, NULL,
					&m_hKey,
					&dwDisposition );
}

CRegister::~CRegister()
{
	RegCloseKey( m_hKey );
}

string CRegister::getRegValue(char* key, DWORD* aSize)
{
	DWORD dwType = REG_BINARY;
	static string dest;
	DWORD dwDataSize = 0;

	if ( ERROR_SUCCESS == RegQueryValueEx(m_hKey, key, 0, &dwType, (PBYTE)NULL, &dwDataSize) )
	{
		dest.resize( sizeof(char)*dwDataSize );
		RegQueryValueEx( m_hKey, key, 0, &dwType, (PBYTE)(LPTSTR)dest.c_str(), &dwDataSize );
	}
	else
	{
		DWORD dw = GetLastError();
		dest.clear();
	}
	
	*aSize = dest.length();

	return dest;
}

void CRegister::setRegValue(char *key,char * newValue,long actualSize)
{
	DWORD dwType = REG_BINARY;

	if ( m_hKey != NULL )
	{
		RegSetValueEx( m_hKey, _T(key), 0, dwType, (const unsigned char *)newValue, actualSize );
	}
}
