/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_SYS_Thread_DataDef.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2012-01-20
 * Description   :  NPCϵͳ�̴߳���ģ�����ݶ���
 *----------------------------------------------------------------------------*/

#ifndef __NPC_SYS_THREAD_DATADEF_H
#define __NPC_SYS_THREAD_DATADEF_H

#include "NPC_TypeDef.h"

#ifdef _WIN32
#define NPC_D_THREAD_MAX_WAIT_OBJ_NUM					64			//���ȴ�������
#else
#define NPC_D_THREAD_MAX_WAIT_OBJ_NUM					64			//���ȴ�������
#endif


//�߳����ݶ���
typedef struct _NPC_S_THREAD_DATA
{
	//NPC_BOOL						bRunFlag;						//�߳����б�־

#ifdef _WIN32
	NPC_DWORD						dwThreadId;						//�߳�ID
	HANDLE							hThread;						//�߳̾��
#else
	pthread_t						t_thread_data;					//�߳�����
	NPC_BOOL						bIfCreated;						//�Ƿ񱻴���
	pthread_mutex_t					t_mutex_lock;					//������
	NPC_BOOL						bIfInitMutex;					//�Ƿ��ʼ���˻�����
	pthread_cond_t					cond_exit_notify;				//�˳�֪ͨ��������
	NPC_BOOL						bIfInitCond;					//�Ƿ��ʼ������������
#endif

	fNPC_F_THREAD_StartProc			pThreadProc;					//�̴߳������
	PNPC_VOID						pThreadParam;					//�̲߳���

	NPC_INT							iEndFlag;						//������־

} NPC_S_THREAD_DATA, *PNPC_S_THREAD_DATA;

//���������ݶ���
typedef struct _NPC_S_THREAD_MUTEX_DATA
{
#ifdef _WIN32
	CRITICAL_SECTION				crsMutex;						//������
#else
	pthread_mutex_t					mutex_lock;						//������
#endif

} NPC_S_THREAD_MUTEX_DATA, *PNPC_S_THREAD_MUTEX_DATA;

//�¼����ݶ���
typedef struct _NPC_S_THREAD_EVENT_DATA
{
#ifdef _WIN32
	NPC_HANDLE						hEvent;							//�¼�
#else
	pthread_mutex_t					t_mutex_lock;					//������
	NPC_BOOL						bIfInitMutex;					//�Ƿ��ʼ���˻�����

	pthread_cond_t					cond_event;						//�¼���������
	NPC_BOOL						bIfInitCond;					//�Ƿ��ʼ������������

	NPC_BOOL						bSingleFlag;					//�źű�־��TRUE��ʾ���źţ�FALSE��ʾ���ź�
	NPC_BOOL						bManualReset; 					//�Ƿ��ֶ���λΪ���ź�

	NPC_HANDLE						hWaitObjTable[NPC_D_THREAD_MAX_WAIT_OBJ_NUM];	//�ȴ������
#endif

} NPC_S_THREAD_EVENT_DATA, *PNPC_S_THREAD_EVENT_DATA;

//�ź������ݶ���
typedef struct _NPC_S_THREAD_SEM_DATA
{
#ifdef _WIN32
	NPC_HANDLE						hSemaphore;						//�ź���
#else
	pthread_mutex_t					t_mutex_lock;					//������
	NPC_BOOL						bIfInitMutex;					//�Ƿ��ʼ���˻�����

	pthread_cond_t					cond_event;						//�¼���������
	NPC_BOOL						bIfInitCond;					//�Ƿ��ʼ������������

	NPC_UINT						uiSemNum;						//�ź���
	NPC_UINT						uiMaxSemNum;					//����ź���
#endif

} NPC_S_THREAD_SEM_DATA, *PNPC_S_THREAD_SEM_DATA;

//�����������ݶ���
typedef struct _NPC_S_THREAD_WAITOBJ_DATA
{
	NPC_INT							iObjNum;						//������

#ifdef _WIN32
	NPC_HANDLE						hWaitObjTable[NPC_D_THREAD_MAX_WAIT_OBJ_NUM];		//�ȴ������
#else
	pthread_mutex_t					t_mutex_lock;					//������
	NPC_BOOL						bIfInitMutex;					//�Ƿ��ʼ���˻�����

	pthread_cond_t					cond_event;						//�¼���������
	NPC_BOOL						bIfInitCond;					//�Ƿ��ʼ������������

	NPC_HANDLE						hWaitObjTable[NPC_D_THREAD_MAX_WAIT_OBJ_NUM];		//�ȴ������
	NPC_BOOL						bObjSigFlag[NPC_D_THREAD_MAX_WAIT_OBJ_NUM];			//�����Ƿ����ź�
#endif

} NPC_S_THREAD_WAITOBJ_DATA, *PNPC_S_THREAD_WAITOBJ_DATA;



#endif
