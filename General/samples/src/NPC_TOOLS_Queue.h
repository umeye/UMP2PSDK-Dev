/*----------------------------------------------------------------------------
 * Copyright(c)  :  XXXX CORPORTAION  All Rights Reserved                       
 * FileName      :  NPC_TOOLS_Queue.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2010-05-26
 * Description   :  NPCϵͳ���й���
 *----------------------------------------------------------------------------*/

#ifndef __NPC_TOOLS_QUEUE_H
#define __NPC_TOOLS_QUEUE_H

#include "NPC_TypeDef.h"


//--------------------------------------------------------------------------------
//���뵼������
#ifdef _WIN32
	#ifdef _NPC_QUEUE_EXPORTS
		#define NPC_QUEUE_API __declspec(dllexport)
	#else
		#ifdef _NPC_QUEUE_IMPORT
			#define NPC_QUEUE_API __declspec(dllimport)
		#else
			#define NPC_QUEUE_API
		#endif
	#endif
#else
	#define NPC_QUEUE_API
#endif


//---------------------------------------------------------------------
#ifdef _WIN32
// C++ support
#ifdef __cplusplus
extern "C"
{
#endif
#endif


//-----------------------------------------------------------------------------
//��ʼ���ж�
NPC_QUEUE_API	NPC_BOOL	NPC_F_TOOLS_QUEUE_InitQueue(
	IN		NPC_HANDLE*		in_hQueue,			//���о��
	IN		NPC_INT			in_iQueueSize=10000	//���д�С
	);

//�ͷŶ���
NPC_QUEUE_API	NPC_VOID	NPC_F_TOOLS_QUEUE_FreeQueue(
	IN		NPC_HANDLE*		in_hQueue		//���о��
	);

//-----------------------------------------------------------------------------------
//�������ݵ�����
NPC_QUEUE_API	NPC_BOOL	NPC_F_TOOLS_QUEUE_SetData(
	IN		NPC_HANDLE		in_hQueue,		//���о��
	IN		PNPC_BYTE		in_pData,		//����ָ��
	IN		NPC_INT			in_iDataLen,	//���ݳ���
	IN		NPC_INT			in_iTimeout		//��ʱʱ�������룩
	);

//�Ӷ��л�ȡ����
NPC_QUEUE_API	NPC_BOOL	NPC_F_TOOLS_QUEUE_GetData(
	IN		NPC_HANDLE		in_hQueue,		//���о��
	OUT		PNPC_BYTE		out_pData,		//���������ָ�룬�û������ɵ����߷��䣬�����С������ڶ����е����ݳ��ȣ��������ʧ��
	OUT		PNPC_INT		out_pDataLen,	//��������ݳ��ȣ����뻺������С���������ݳ���
	IN		NPC_INT			in_iTimeout		//��ʱʱ�������룩
	);

//�Ӷ��л�ȡ���ݣ��ɸú��������ڴ�
NPC_QUEUE_API	NPC_BOOL	NPC_F_TOOLS_QUEUE_GetDataEx(
	IN		NPC_HANDLE		in_hQueue,		//���о��
	OUT		PNPC_BYTE*		out_ppData,		//���������ָ�룬�ɶ��з����ڴ棬�ڴ��ͷ��ɵ����ߵ���NPC_F_TOOLS_QUEUE_FreeMemory�ͷ�
	OUT		PNPC_INT		out_pDataLen,	//��������ݳ���
	OUT		PNPC_INT		out_pBufSize,	//��������С����������е����ݴ��ڸû�������С����������·����ڴ棬�ͷ�֮ǰ���ڴ棬�����ڴ��Сͨ���ò�������
	IN		NPC_INT			in_iTimeout		//��ʱʱ�������룩
	);

//�Ӷ������Ƴ�һ������
NPC_QUEUE_API	NPC_BOOL	NPC_F_TOOLS_QUEUE_MoveData(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

//--------------------------------------------------------------------------------
//��ȡ��������
NPC_QUEUE_API	NPC_INT		NPC_F_TOOLS_QUEUE_GetCount(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

//��ȡ���ж��¼����
NPC_QUEUE_API	HANDLE		NPC_F_TOOLS_QUEUE_GetReadEventHandle(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

//��ȡ����д�¼����
NPC_QUEUE_API	HANDLE		NPC_F_TOOLS_QUEUE_GetWriteEventHandle(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

#ifdef _WIN32
//��ȡ���ж��¼����
NPC_QUEUE_API	HANDLE		NPC_F_TOOLS_QUEUE_GetWinReadEventHandle(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

//��ȡ����д�¼����
NPC_QUEUE_API	HANDLE		NPC_F_TOOLS_QUEUE_GetWinWriteEventHandle(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);

//������Ϣ֪ͨ�Ĵ��ھ��
NPC_QUEUE_API	NPC_VOID	NPC_F_TOOLS_QUEUE_SetMsgWnd(
	IN		NPC_HANDLE		in_hQueue,		//���о��
	IN		NPC_HWND		in_hWnd,		//���봰�ھ��
	IN		NPC_UINT		in_uMsg			//������ϢID
	);
#endif

//�������洢����
NPC_QUEUE_API	NPC_VOID	NPC_F_TOOLS_QUEUE_SetMaxStoreDataNum(
	IN		NPC_HANDLE		in_hQueue,		//���о��
	IN		NPC_INT			in_iNum			//���洢��
	);

//�ͷ��ڴ棬���ڴ���DLL�����
NPC_QUEUE_API	NPC_VOID	NPC_F_TOOLS_QUEUE_FreeMemory(
	IN		PNPC_BYTE*		in_ppDataPos	//����ָ��
	);

//��ѯ���������ۼƴ�С���ֽڣ�
NPC_QUEUE_API	NPC_DWORD	NPC_F_TOOLS_QUEUE_QueryQueueDataTotalLen(
	IN		NPC_HANDLE		in_hQueue		//���о��
	);


#ifdef _WIN32
// C++ support
#ifdef __cplusplus
}
#endif
#endif


#endif
