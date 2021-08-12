// CryptoRegApp.cpp : DLL �̏��������[�`���ł��B
//

#include "stdafx.h"
#include "CryptoRegApp.h"
#include "CryptoReg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//
//TODO: ���� DLL �� MFC DLL �ɑ΂��ē��I�Ƀ����N�����ꍇ�A
//		MFC ���ŌĂяo����邱�� DLL ����G�N�X�|�[�g���ꂽ�ǂ̊֐���
//		�֐��̍ŏ��ɒǉ������ AFX_MANAGE_STATE �}�N����
//		�����Ȃ���΂Ȃ�܂���B
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �ʏ�֐��̖{�̂͂��̈ʒu�ɂ���܂�
//		}
//
//		���̃}�N�����e�֐��Ɋ܂܂�Ă��邱�ƁAMFC ����
//		�ǂ̌Ăяo�����D�悷�邱�Ƃ͔��ɏd�v�ł��B
//		����͊֐����̍ŏ��̃X�e�[�g�����g�łȂ���΂� 
//		��Ȃ����Ƃ��Ӗ����܂��A�R���X�g���N�^�� MFC
//		DLL ���ւ̌Ăяo�����s���\��������̂ŁA�I�u
//		�W�F�N�g�ϐ��̐錾�����O�łȂ���΂Ȃ�܂���B
//
//		�ڍׂɂ��Ă� MFC �e�N�j�J�� �m�[�g 33 �����
//		58 ���Q�Ƃ��Ă��������B
//

// CCryptoRegApp

BEGIN_MESSAGE_MAP(CCryptoRegApp, CWinApp)
END_MESSAGE_MAP()


// CCryptoRegApp �R���X�g���N�V����

CCryptoRegApp::CCryptoRegApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_pEncryptObj = NULL;
	m_pRegisterObj = NULL;
}


// �B��� CCryptoRegApp �I�u�W�F�N�g�ł��B

CCryptoRegApp theApp;


// CCryptoRegApp ������

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

