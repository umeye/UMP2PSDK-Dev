/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_MON_MpsDef.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-12
 * Description   :  �������ݽṹ����
 *----------------------------------------------------------------------------*/

#ifndef __NPC_MON_MPSDEF_H
#define __NPC_MON_MPSDEF_H

#include "NPC_TypeDef.h"
#include "NPC_MON_ConsDef.h"


#pragma pack(1)

//����ļ���Ϣ
typedef struct _NPC_S_MON_MPS_FILE_INFO
{
	NPC_CHAR										sFileFlag[NPC_D_MON_CSD_MAX_FILE_FLAG_LEN];		//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
	NPC_INT											iFileType;					//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
	NPC_INT											iCreateMode;				//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_INT											iAlarmEvent;				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_S_TD_DATE_TIME								tStartTime;					//�ļ���ʼʱ�䣬�����ļ�Ϊ���յ�ʱ��
	NPC_S_TD_DATE_TIME								tEndTime;					//�ļ�����ʱ�䣬�����ļ��ò�����Ч
	NPC_DWORD										dwFileTimeLen;				//�ļ���ʱ�����룩��¼���ļ���Ч
	NPC_DWORD										dwFileSize;					//�ļ���С����λ��KB��

	NPC_BOOL										bVideoFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	NPC_BOOL										bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	NPC_BOOL										bPictureFlag;				//ͼƬ��־��TRUE����ʾΪͼƬ��FALSE����ʾ����ͼƬ������ò���TRUE��������Ƶ������Ч

	NPC_INT											iVideoCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
	NPC_INT											iVideoFrameRate;			//��Ƶ֡��
	NPC_INT											iVideoBitRate;				//��Ƶ���ʣ�kbps��
	NPC_USHORT										usVideoWidth;				//��Ƶ���
	NPC_USHORT										usVideoHeight;				//��Ƶ�߶�

	NPC_INT											iAudioCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_AUDIO_*����
	NPC_INT											iAudioBitRate;				//��Ƶ���ʣ�kbps��
	NPC_INT											iAudioSampleRate;			//��Ƶ������
	NPC_INT											iAudioChNum;				//��Ƶ������

	NPC_INT											iPictureFormat;				//ͼƬ��ʽ���μ�NPC_D_MON_CSD_PIC_FORMAT_*����

} NPC_S_MON_MPS_FILE_INFO, *PNPC_S_MON_MPS_FILE_INFO;

//�ļ�ͷ��Ϣ
typedef struct _NPC_S_MON_MPS_FILE_HEAD_INFO
{
	NPC_CHAR										sFileFlag[128];				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ�����أ����ļ���
	NPC_USHORT										usChNo;						//ͨ����
	NPC_BYTE										ucStreamNo;					//������
	NPC_BYTE										ucFileType;					//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
	NPC_BYTE										ucCreateMode;				//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_BYTE										ucAlarmEvent;				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_BYTE										ucReserve1[2];				//����1
	NPC_S_TD_DATE_TIME								tStartTime;					//�ļ���ʼʱ�䣬�����ļ�Ϊ���յ�ʱ��
	NPC_S_TD_DATE_TIME								tEndTime;					//�ļ�����ʱ�䣬�����ļ��ò�����Ч
	NPC_UINT										uiFileTimeLen;				//�ļ���ʱ�����룩��¼���ļ���Ч
	NPC_UINT										uiFileSize;					//�ļ���С����λ��KB��

	//���²�����ucFileTypeֵΪNPC_D_MON_CSD_FILE_TYPE_RECORDʱ��Ч
	NPC_BYTE										ucVideoFlag;				//��Ƶ��־��1����ʾ����Ƶ��0����ʾû����Ƶ
	NPC_BYTE										ucAudioFlag;				//��Ƶ��־��1����ʾ����Ƶ��0����ʾû����Ƶ

	NPC_BYTE										ucVideoCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
	NPC_BYTE										ucVideoFrameRate;			//��Ƶ֡��
	NPC_UINT										uiVideoBitRate;				//��Ƶ���ʣ�kbps��
	NPC_USHORT										usVideoWidth;				//��Ƶ���
	NPC_USHORT										usVideoHeight;				//��Ƶ�߶�

	NPC_USHORT										usAudioCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_AUDIO_*����
	NPC_USHORT										usAudioBitRate;				//��Ƶ���ʣ�kbps��
	NPC_UINT										uiAudioSampleRate;			//��Ƶ������
	NPC_USHORT										usAudioChNum;				//��Ƶ������

	//���²�����ucFileTypeֵΪNPC_D_MON_CSD_FILE_TYPE_PICTRUEʱ��Ч
	NPC_BYTE										ucPictureFormat;			//ͼƬ��ʽ���μ�NPC_D_MON_CSD_PIC_FORMAT_*����
	NPC_BYTE										ucReserve2;					//����2

} NPC_S_MON_MPS_FILE_HEAD_INFO, *PNPC_S_MON_MPS_FILE_HEAD_INFO;

//¼���ļ�ʱ�䷶Χ
typedef struct _NPC_S_MON_MPS_FILE_RANGE_INFO
{
	NPC_DWORD										dwFileFlag;					//��ʶ	
	NPC_INT											iCreateMode;				//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_INT											iAlarmEvent;				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч

	NPC_S_TD_DATE_TIME								tStartTime;					//��ʼʱ�䣬���ļ�����ʱ���¼��Ŀ�ʼʱ��Ϊ��ѯʱ��
	NPC_S_TD_DATE_TIME								tEndTime;					//����ʱ��
}NPC_S_MON_MPS_FILE_RANGE_INFO,*PNPC_S_MON_MPS_FILE_RANGE_INFO;


#pragma pack()

#endif

