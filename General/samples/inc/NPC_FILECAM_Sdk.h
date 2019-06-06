/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_FILECAM_Sdk.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2011-08-24
 * Description   :  NPCϵͳ�ļ������ģ��
 *----------------------------------------------------------------------------*/

#ifndef __NPC_FILECAM_SDK_H
#define __NPC_FILECAM_SDK_H

#include "NPC_TypeDef.h"


//�ص���������
typedef void(CALLBACK *fNPC_F_FILECAM_SDK_RealDataCallBack)(
	IN		NPC_INT			in_iMediaType,				//ý�����ͣ�0����Ƶ��1����Ƶ
	IN		PNPC_BYTE		in_pMediaDataBuf,			//ý������
	IN		NPC_INT			in_iMediaDataLen,			//ý�����ݳ���
	IN		NPC_DWORD		in_dwUserData				//�û�����
	);


//�豸����
typedef struct _NPC_S_FILECAM_SDK_CH_PARAM
{
	NPC_HANDLE				hFileCam;					//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	NPC_INT					iChNo;						//ͨ����

	NPC_INT					iFrameRate;					//֡��
	NPC_BOOL				bIfSupportAudio;			//�Ƿ�֧����Ƶ

} NPC_S_FILECAM_SDK_CH_PARAM, *PNPC_S_FILECAM_SDK_CH_PARAM;



//--------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif


//��ʼ���ļ������SDK
NPC_API_INTER	NPC_BOOL	NPC_F_FILECAM_SDK_InitSdk();

//����ʼ���ļ������SDK
NPC_API_INTER	NPC_VOID	NPC_F_FILECAM_SDK_UninitSdk();

//�����ļ������
NPC_API_INTER	NPC_HANDLE	NPC_F_FILECAM_SDK_ConnectFilecam(
	IN		PNPC_CHAR						in_pDirName,				//Ŀ¼��
	OUT		PNPC_INT						out_pChNum					//ͨ����
	);

//�Ͽ������ļ������
NPC_API_INTER	NPC_VOID	NPC_F_FILECAM_SDK_DisconnectFilecam(
	IN		NPC_HANDLE						in_hFileCam					//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	);

//��ʼԤ��
NPC_API_INTER	NPC_BOOL	NPC_F_FILECAM_SDK_RealPlay(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo,					//ͨ����
	IN		fNPC_F_FILECAM_SDK_RealDataCallBack		in_cbRealDataCallBack,		//ý�����ݻص�����
	IN		NPC_DWORD						in_dwUserData,				//�û�����
	OUT		PNPC_S_FILECAM_SDK_CH_PARAM		out_pCamParam				//�ļ����������
	);

//����Ԥ��
NPC_API_INTER	NPC_BOOL	NPC_F_FILECAM_SDK_StopRealPlay(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo					//ͨ����
	);

//��ʼ�Խ�
NPC_API_INTER	NPC_BOOL	NPC_F_FILECAM_SDK_StartTalk(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo					//ͨ����
	);

//ֹͣ�Խ�
NPC_API_INTER	NPC_VOID	NPC_F_FILECAM_SDK_StopTalk(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo					//ͨ����
	);

//����Խ���Ƶ����
NPC_API_INTER	NPC_BOOL	NPC_F_FILECAM_SDK_InputTalkAudioData(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo,					//ͨ����
	IN		PNPC_BYTE						in_pAudioDataBuf,			//��Ƶ���ݻ�����
	IN		NPC_INT							in_iAudioDataLen			//��Ƶ���ݳ���
	);

//����ǿ��I֡
NPC_API_INTER	NPC_VOID	NPC_F_FILECAM_SDK_RequestForceIFrame(
	IN		NPC_HANDLE						in_hFileCam,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
	IN		NPC_INT							in_iChNo					//ͨ����
	);


#ifdef __cplusplus
}
#endif


#endif

