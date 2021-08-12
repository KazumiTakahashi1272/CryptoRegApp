// CryptoRegApp.cpp : DLL の初期化ルーチンです。
//

#include "stdafx.h"
#include "CryptoRegApp.h"
#include "CryptoReg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//
//TODO: この DLL が MFC DLL に対して動的にリンクされる場合、
//		MFC 内で呼び出されるこの DLL からエクスポートされたどの関数も
//		関数の最初に追加される AFX_MANAGE_STATE マクロを
//		持たなければなりません。
//
//		例:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 通常関数の本体はこの位置にあります
//		}
//
//		このマクロが各関数に含まれていること、MFC 内の
//		どの呼び出しより優先することは非常に重要です。
//		これは関数内の最初のステートメントでなければな 
//		らないことを意味します、コンストラクタが MFC
//		DLL 内への呼び出しを行う可能性があるので、オブ
//		ジェクト変数の宣言よりも前でなければなりません。
//
//		詳細については MFC テクニカル ノート 33 および
//		58 を参照してください。
//

// CCryptoRegApp

BEGIN_MESSAGE_MAP(CCryptoRegApp, CWinApp)
END_MESSAGE_MAP()


// CCryptoRegApp コンストラクション

CCryptoRegApp::CCryptoRegApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
	m_pEncryptObj = NULL;
	m_pRegisterObj = NULL;
}


// 唯一の CCryptoRegApp オブジェクトです。

CCryptoRegApp theApp;


// CCryptoRegApp 初期化

BOOL CCryptoRegApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CRYPTOREG_API HANDLE WINAPI cryptoOpenRegistry(T_CRYPTO_DATA* pCryptoData)
{
	if ( pCryptoData == NULL )
		return NULL;

	theApp.m_CryptoData = *pCryptoData;

	CString strEncryptKey( pCryptoData->m_encryptKey.c_str() );
	theApp.m_pEncryptObj = new CEncrypt( strEncryptKey );

	theApp.m_pRegisterObj = new CRegister( pCryptoData );

	return &theApp;
}

CRYPTOREG_API void WINAPI cryptoCloseRegistry(HANDLE hCrypto)
{
	CCryptoRegApp* pCrypto = reinterpret_cast<CCryptoRegApp*>( hCrypto );
	if ( pCrypto == NULL )
		return;

	if ( pCrypto->m_pEncryptObj != NULL )
		delete pCrypto->m_pEncryptObj;

	if ( pCrypto->m_pRegisterObj != NULL )
		delete pCrypto->m_pRegisterObj;
}

CRYPTOREG_API bool WINAPI cryptoWriteRegistry(HANDLE hCrypto, string strData)
{
	CCryptoRegApp* pCrypto = reinterpret_cast<CCryptoRegApp*>( hCrypto );
	if ( pCrypto == NULL )
		return false;

	if ( pCrypto->m_pEncryptObj == NULL )
		return false;

	if ( pCrypto->m_pRegisterObj == NULL )
		return false;

	strData.resize( 256 );
	long lSize = pCrypto->m_pEncryptObj->Encrypt( strData, strData.length() );
	if ( lSize == -1 )
		return false;

	pCrypto->m_pRegisterObj->setRegValue( (TCHAR*)pCrypto->m_CryptoData.m_valueKey.c_str(), (TCHAR*)strData.c_str(), lSize );
	return true;
}

CRYPTOREG_API bool WINAPI cryptoReadRegistry(HANDLE hCrypto, string& strData)
{
	DWORD dwSize;

	CCryptoRegApp* pCrypto = reinterpret_cast<CCryptoRegApp*>( hCrypto );
	if ( pCrypto == NULL )
		return false;

	if ( pCrypto->m_pEncryptObj == NULL )
		return false;

	strData = pCrypto->m_pRegisterObj->getRegValue( (TCHAR*)pCrypto->m_CryptoData.m_valueKey.c_str(), &dwSize );
	if ( pCrypto->m_pEncryptObj->Decrypt(strData, dwSize) == -1 )
		return false;

	return true;
}

