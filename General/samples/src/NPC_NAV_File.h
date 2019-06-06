/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_NAV_File.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2012-02-21
 * Description   :  NAV�ļ���дģ��
 *----------------------------------------------------------------------------*/

#ifndef __NPC_NAV_FILE_H
#define __NPC_NAV_FILE_H

#include "NPC_TypeDef.h"


//--------------------------------------------------------------------------------
//��������
#define NPC_D_NAV_DEF_CM_VEDIO_PARAMS_BUFSIZE					64								//��Ƶ������������С
#define NPC_D_NAV_DEF_CM_AUDIO_PARAMS_BUFSIZE					64								//��Ƶ������������С


//--------------------------------------------------------------------------------
//����Ƶ��ʽ���ݽṹ
typedef struct _NPC_S_NAV_AV_FORMAT
{
	NPC_BOOL							bVedioFlag;												//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ
	NPC_BOOL							bAudioFlag;												//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ

	NPC_INT								iVedioCodecId;											//��Ƶ���������0��Ĭ�ϱ��룬1��H264��2��MPEG4��3��H263������
	NPC_USHORT							usVedioWidth;											//��Ƶ���
	NPC_USHORT							usVedioHeight;											//��Ƶ�߶�
	NPC_INT								iVedioBitRate;											//��Ƶ���ʲ�����0��ʾΪĬ������
	NPC_INT								iVedioFrameRate;										//��Ƶ֡�ʲ�����0��ʾΪĬ��֡��
	NPC_CHAR							sVedioParams[NPC_D_NAV_DEF_CM_VEDIO_PARAMS_BUFSIZE];	//��Ƶ������BASE64��ʽ���Զ̺ŷָ������ΪH264��ʽ�����������SPS��PPS

	NPC_INT								iAudioCodecId;											//��Ƶ���������0��Ĭ�ϱ��룬1��16λ����PCM��2��G711A��3��G711U��4��G721������
	NPC_INT								iAudioSampleRate;										//��Ƶ������
	NPC_INT								iAudioChNum;											//��Ƶͨ������1��2
	NPC_CHAR							sAudioParams[NPC_D_NAV_DEF_CM_AUDIO_PARAMS_BUFSIZE];	//��Ƶ����

} NPC_S_NAV_AV_FORMAT, *PNPC_S_NAV_AV_FORMAT;


//--------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif


//����NAV�ļ�
NPC_API_INTER	NPC_HANDLE	NPC_F_NAV_CreateFile(
	IN		PNPC_CHAR						in_pFileName,				//�ļ���
	IN		NPC_INT							in_iDevVendor,				//�豸����
	IN		NPC_INT							in_iRecCodecFormat,			//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
	IN		PNPC_S_NAV_AV_FORMAT			in_pRecFormat,				//¼���ʽ
	IN		NPC_DWORD						in_dwTimestampRef,			//ʱ����ο�ֵ��Ĭ��Ϊ90000
	IN		PNPC_CHAR						in_pRecBeginTime			//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	);

//��NAV�ļ�
NPC_API_INTER	NPC_HANDLE	NPC_F_NAV_OpenFile(
	IN		PNPC_CHAR						in_pFileName,				//�ļ���
	OUT		PNPC_INT						out_pDevVendor,				//�豸����
	OUT		PNPC_INT						out_pRecCodecFormat,		//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
	OUT		PNPC_S_NAV_AV_FORMAT			out_pRecFormat,				//¼���ʽ
	OUT		PNPC_DWORD						out_pTimestampRef,			//ʱ����ο�ֵ��Ĭ��Ϊ90000
	OUT		PNPC_CHAR						out_pRecBeginTime,			//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_CHAR						out_pRecEndTime,			//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_DWORD						out_pRecTimeLen				//¼��ʱ�����룩
	);

//�ر�NAV�ļ�
NPC_API_INTER	NPC_VOID	NPC_F_NAV_CloseFile(
	IN		NPC_HANDLE						in_hNavFile					//NAV�ļ����
	);

//���ļ����ý�����ݣ���Ƶ����Ƶ��
NPC_API_INTER	NPC_BOOL	NPC_F_NAV_AddMediaData(
	IN		NPC_HANDLE						in_hNavFile,				//NAV�ļ����
	IN		NPC_INT							in_iMediaType,				//ý�����ͣ�0����Ƶ��1����Ƶ
	IN		NPC_CHAR						in_cFrameType,				//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
	IN		NPC_DWORD						in_dwTimestamp,				//ʱ���
	IN		NPC_DWORD						in_dwRecOffsetTime,			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
	IN		PNPC_BYTE						in_pMediaDataBuf,			//ý�����ݻ�������ԭʼ�������ݣ�
	IN		NPC_INT							in_iMediaDataLen			//ý�����ݳ���
	);

//��ȡý�����ݣ���Ƶ����Ƶ��
NPC_API_INTER	NPC_BOOL	NPC_F_NAV_ReadMediaData(
	IN		NPC_HANDLE						in_hNavFile,				//NAV�ļ����
	OUT		PNPC_INT						out_pMediaType,				//ý�����ͣ�0����Ƶ��1����Ƶ
	OUT		PNPC_CHAR						out_pFrameType,				//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
	OUT		PNPC_DWORD						out_pTimestamp,				//ʱ���
	OUT		PNPC_DWORD						out_pRecOffsetTime,			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
	OUT		PNPC_BYTE*						out_ppMediaDataBuf,			//ý�����ݻ�������ԭʼ�������ݣ�
	OUT		PNPC_INT						out_pMediaDataBufSize,		//ý�����ݻ�������С
	OUT		PNPC_INT						out_pMediaDataLen			//ý�����ݳ���
	);

//��ת��ָ��λ��
NPC_API_INTER	NPC_BOOL	NPC_F_NAV_JumpCurPos(
	IN		NPC_HANDLE						in_hNavFile,				//NAV�ļ����
	IN		NPC_DWORD						in_dwRecOffsetTime			//��ת��ָ��λ�ã��ò���¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
	);

//�����ļ�ͷ��Ϣ
NPC_API_INTER	NPC_BOOL	NPC_F_NAV_UpdateFileHead_RecEndTime(
	IN		NPC_HANDLE						in_hNavFile,				//NAV�ļ����
	IN		PNPC_CHAR						in_pRecEndTime,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	IN		NPC_DWORD						in_dwRecTimeLen				//¼��ʱ�����룩
	);

//����ļ��Ƿ������ݿɶ�������TRUE��ʾ�������ݣ�FALSE��ʾû��
NPC_API_INTER	NPC_BOOL	NPC_F_NAV_CheckFileIfEnd(
	IN		NPC_HANDLE						in_hNavFile					//NAV�ļ����
	);

//�ͷŻ�����
NPC_API_INTER	NPC_VOID	NPC_F_NAV_ReleaseBuf(
	INOUT	PNPC_BYTE*						inout_ppDataBuf				//���ݻ�����
	);


#ifdef __cplusplus
}
#endif


#endif

