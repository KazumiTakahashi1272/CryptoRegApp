// Register.h: interface for the CRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTER_H__571D24C0_4373_4381_8A2E_894D43EB63E6__INCLUDED_)
#define AFX_REGISTER_H__571D24C0_4373_4381_8A2E_894D43EB63E6__INCLUDED_

#include "CryptoReg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_LENGTH 256

class CRegister  
{
public:
	CRegister(T_CRYPTO_DATA* pCryptoData);
	virtual ~CRegister();
	string getRegValue(char *key,DWORD *aSize);
	void setRegValue(char *key,char * newValue,long aSize);

private:
	HKEY		m_hKey;
	LPCTSTR		m_pParentKey;
};

#endif // !defined(AFX_REGISTER_H__571D24C0_4373_4381_8A2E_894D43EB63E6__INCLUDED_)
