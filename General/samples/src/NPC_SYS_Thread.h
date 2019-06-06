/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_SYS_Thread.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2012-01-20
 * Description   :  NPCϵͳ�̴߳���ģ��
 *----------------------------------------------------------------------------*/

#ifndef __NPC_SYS_THREAD_H
#define __NPC_SYS_THREAD_H

#include "NPC_TypeDef.h"


//--------------------------------------------------------------------------------
//���뵼������
#ifdef _NPC_THREAD_EXPORTS
	#define NPC_THREAD_API __declspec(dllexport)
#else
	#ifdef _NPC_THREAD_IMPORT
		#define NPC_THREAD_API __declspec(dllimport)
	#else
		#define NPC_THREAD_API
	#endif
#endif


//--------------------------------------------------------------------------------
//�̹߳��̶���
typedef NPC_VOID (*fNPC_F_THREAD_StartProc)(PNPC_VOID pInParam);


//---------------------------------------------------------------------
#ifdef _WIN32
// C++ support
#ifdef __cplusplus
extern "C"
{
#endif
#endif


//--------------------------------------------------------------------------------
//�����߳�
NPC_THREAD_API		NPC_HANDLE	NPC_F_THREAD_CreateThread(
	IN		fNPC_F_THREAD_StartProc			in_pWorkProc,			//�̹߳�������
	IN		PNPC_VOID						in_pInParam				//�������
	);

//�˳��߳�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_WaitExitThread(
	IN		NPC_HANDLE						in_hThread,				//�߳̾��
	IN		NPC_INT							in_iTimeout				//��ʱʱ�������룩
	);


//--------------------------------------------------------------------------------
//����������
NPC_THREAD_API		NPC_HANDLE	NPC_F_THREAD_Mutex_Create();

//�ͷŻ�����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Mutex_Destroy(
	IN		NPC_HANDLE						in_hMutex				//���������
	);

//����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Mutex_Lock(
	IN		NPC_HANDLE						in_hMutex				//���������
	);

//����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Mutex_Unlock(
	IN		NPC_HANDLE						in_hMutex				//���������
	);

//--------------------------------------------------------------------------------
//�����¼�
NPC_THREAD_API		NPC_HANDLE	NPC_F_THREAD_Event_Create(
	IN		NPC_BOOL						in_bManualReset, 		//�Ƿ��ֶ���λΪ���ź�
	IN		NPC_BOOL						in_bInitSigState		//��ʼ״̬�Ƿ����ź�
	);

//�ͷ��¼�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Event_Destroy(
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);

//�����¼����ź�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Event_SetEvent(
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);

//�����¼�Ϊ���ź�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Event_ResetEvent(
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);

//�ȴ��¼�������TRUE��ʾ���źţ�FALSE��ʾ���ź�
NPC_THREAD_API		NPC_BOOL	NPC_F_THREAD_Event_Wait(
	IN		NPC_HANDLE						in_hEvent,				//�¼����
	IN		NPC_INT							in_iTimeout				//��ʱʱ�������룩
	);


#ifdef _WIN32
//��WINDOWS�¼����
NPC_THREAD_API		HANDLE		NPC_F_THREAD_Event_GetWinEventHandle(
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);
#else
//��ѯ�¼��Ƿ����źţ����û�У�������ȴ�����
NPC_THREAD_API		NPC_BOOL	NPC_F_THREAD_Event_QuerySetWaitObj(
	IN		NPC_HANDLE						in_hEvent,				//�¼����
	IN		NPC_HANDLE						in_hWaitObj				//�ȴ�������
	);

//�¼�����ȴ�����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Event_ClearWaitObj(
	IN		NPC_HANDLE						in_hEvent,				//�¼����
	IN		NPC_HANDLE						in_hWaitObj				//�ȴ�������
	);

//�¼�������еȴ�����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Event_ClearAllWaitObj(
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);
#endif


//--------------------------------------------------------------------------------
//�����ź���
NPC_THREAD_API		NPC_HANDLE	NPC_F_THREAD_Sem_Create(
	IN		NPC_UINT						in_uiInitSemNum,		//��ʼ�ź���
	IN		NPC_UINT						in_uiMaxSemNum			//����ź���
	);

//�ͷ��ź���
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Sem_Destroy(
	IN		NPC_HANDLE						in_hSem					//�ź������
	);

//�ͷ��ź�����������N���ź�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_Sem_Release(
	IN		NPC_HANDLE						in_hSem,				//�ź������
	IN		NPC_UINT						in_uiRelSemNum			//�ͷ��ź���
	);

//�ȴ��ź���������TRUE��ʾ���źţ�FALSE��ʾ���ź�
NPC_THREAD_API		NPC_BOOL	NPC_F_THREAD_Sem_Wait(
	IN		NPC_HANDLE						in_hSem,				//�ź������
	IN		NPC_INT							in_iTimeout				//��ʱʱ�������룩
	);


//--------------------------------------------------------------------------------
//�����ȴ�����
NPC_THREAD_API		NPC_HANDLE	NPC_F_THREAD_WaitObj_Create();

//�ͷŵȴ�����
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_WaitObj_Destroy(
	IN		NPC_HANDLE						in_hWaitObj				//�ȴ�����
	);

//�ȴ���������¼�
NPC_THREAD_API		NPC_BOOL	NPC_F_THREAD_WaitObj_AddEvent(
	IN		NPC_HANDLE						in_hWaitObj,			//�ȴ�����
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);

//�ȴ�����ɾ���¼�
NPC_THREAD_API		NPC_BOOL	NPC_F_THREAD_WaitObj_DelEvent(
	IN		NPC_HANDLE						in_hWaitObj,			//�ȴ�����
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);

//��������¼�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_WaitObj_ClearAllEvent(
	IN		NPC_HANDLE						in_hWaitObj				//�ȴ�����
	);

#ifndef _WIN32
//���õȴ������е��¼����ź�
NPC_THREAD_API		NPC_VOID	NPC_F_THREAD_WaitObj_SetEventSig(
	IN		NPC_HANDLE						in_hWaitObj,			//�ȴ�����
	IN		NPC_HANDLE						in_hEvent				//�¼����
	);
#endif

//�ȴ��¼����������źŵ������ţ�����-1��ʾ��ʱ������-2��ʾ�д�������ȴ������źţ��򷵻��ź���
NPC_THREAD_API		NPC_INT		NPC_F_THREAD_WaitObj_WaitEvent(
	IN		NPC_HANDLE						in_hWaitObj,			//�ȴ�����
	IN		NPC_BOOL						in_bIfWaitAll,			//�Ƿ�ȴ��������źź�ŷ���
	IN		NPC_INT							in_iTimeout				//��ʱʱ�������룩
	);


//-----------------------------------------------------------------------------------------------
#ifdef _WIN32
//��ȡ������Ϣ
NPC_VOID	NPC_F_THREAD_PR_GetLastErrorInfo(
	IN		NPC_DWORD								in_dwErrorCode,				//������
	IN		PNPC_CHAR								in_pErrorBuf,				//������Ϣ������
	IN		NPC_INT									in_iErrorBufSize			//������Ϣ��������С
	);
#endif



#ifdef _WIN32
// C++ support
#ifdef __cplusplus
}
#endif
#endif



#endif

