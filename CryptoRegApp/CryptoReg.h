
#if !defined(_CRYPTOREG_H_INCLUDE_)
#define _CRYPTOREG_H_INCLUDE_

#include "windows.h"
#include <string>
#include <vector>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef CRYPTOREG_EXPORTS
#define CRYPTOREG_API __declspec(dllexport)
#else
#define CRYPTOREG_API __declspec(dllimport)
#pragma comment(lib, "CryptoReg.lib")
#pragma message("Automatically linking with CryptoReg.dll")
#endif

//----------------------------------------------------------------------------
//	��`�ς݃L�[���w��
//----------------------------------------------------------------------------
#define		keyHCR		HKEY_CLASSES_ROOT
#define		keyHCU		HKEY_CURRENT_USER
#define		keyHLM		HKEY_LOCAL_MACHINE
#define		keyHU		HKEY_USERS
#define		keyHPD		HKEY_PERFORMANCE_DATA
#define		keyHCC		HKEY_CURRENT_CONFIG
#define		keyHDD		HKEY_DYN_DATA

//----------------------------------------------------------------------------
//	�Í����p�����[�^
//----------------------------------------------------------------------------
typedef struct _CRYPTO_DATA
{
	string		m_encryptKey;		// �Í���/�������L�[
	HKEY		m_hKey;				// ��`�ς݃L�[���w��
	string		m_subKey;			// �쐬�܂��̓I�[�v������T�u�L�[�̖��O��\��������
	string		m_valueKey;			// �L�[��
} T_CRYPTO_DATA;


#ifdef __cplusplus
extern "C" {
#endif

CRYPTOREG_API HANDLE WINAPI cryptoOpenRegistry( T_CRYPTO_DATA* pCryptoData );
CRYPTOREG_API void WINAPI cryptoCloseRegistry( HANDLE hCrypto );

CRYPTOREG_API bool WINAPI cryptoWriteRegistry( HANDLE hCrypto, string strData );
CRYPTOREG_API bool WINAPI cryptoReadRegistry( HANDLE hCrypto, string& strData );

#ifdef __cplusplus
}
#endif

#endif // !defined(_CRYPTOREG_H_INCLUDE_)