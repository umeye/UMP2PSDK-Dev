/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_UMSP_DataDef.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-10
 * Description   :  UMSP���������ݶ���
 *----------------------------------------------------------------------------*/

#ifndef __NPC_UMSP_DATADEF_H
#define __NPC_UMSP_DATADEF_H

#include "NPC_TypeDef.h"
#include "NPC_SYS_Thread.h"
#include "NPC_SYS_FuncShare.h"
#include "NPC_MEM_Manager.h"
#include "NPC_TOOLS_Queue.h"
#include "NPC_LOG_Server.h"
#include "NPC_FILECAM_Sdk.h"
#include "NPC_NAV_File.h"
#include "NPC_DPS_DevProNetServer.h"
#include "NPC_DPS_PRO_NI_Custom.h"
#include "NPC_TOOLS_Md5.h"


//-------------------------------------------------------------------------------
//��������
//#define NPC_D_UMSP_MC_MAX_CAMERA_NUM						32				//����������
#define NPC_D_UMSP_MC_MAX_FILE_WORK_NUM						32				//����ļ�������
#define NPC_D_UMSP_MC_MAX_MP3_FILE_NUM						32				//���MP3�ļ���
//#define NPC_D_UMSP_MC_MAX_CAMERA_STREAM_NUM					2				//���������


//-------------------------------------------------------------------------------
//���ò���
typedef struct _NPC_S_UMSP_CONFIG_DATA
{
	NPC_BOOL									bIfDebug;					//�Ƿ���ԣ��ڵ���״̬�£�������ܶ���־��Ϣ����ʽʹ��ʱ��Ҫ�ر�
	NPC_BOOL									bIfShowStreamLog;			//�Ƿ���ʾ����־����ý�����շ���־��Ϣ
	NPC_BOOL									bIfWriteLogToFile;			//�Ƿ�д��־���ļ�
	NPC_CHAR									sLogDir[256];				//��־Ŀ¼����־�ļ����Զ���������ʽΪLog����.txt
	NPC_USHORT									usLogPort;					//��־�˿ںţ����Ϊ0����������־�����˿ڣ�����0��������־�����˿ڷ���
	NPC_BOOL									bIfSwitchVideo;				//�Ƿ��л���Ƶ
	NPC_BOOL									bPwdIfMd5;					//�����Ƿ�ΪMD5�����ΪTRUE��ʾ����ΪMD5���ܺ�ģ�FALSE��ʾ����Ϊ����
	NPC_BOOL									bIfSendAlarmMsg;			//�Ƿ��ͱ�����Ϣ
	NPC_INT										iSendAlarmIntervalTime;		//���ͱ�����Ϣ�ļ��ʱ�䣨�룩
	NPC_INT										iMaxFileConnNum;			//����ļ�������������ܳ���NPC_D_UMSP_MC_MAX_FILE_WORK_NUM

} NPC_S_UMSP_CONFIG_DATA, *PNPC_S_UMSP_CONFIG_DATA;

//���������
typedef struct _NPC_S_UMSP_CAMERA_DATA
{
	NPC_BOOL									bIfUsed;					//�Ƿ�ռ��
	NPC_HANDLE									hWorkLock;					//������

	NPC_INT										iChNo;						//ͨ����
	NPC_INT										iFrameRate;					//֡��
	NPC_BOOL									bIfSupportAudio;			//�Ƿ�֧����Ƶ
	NPC_CHAR									sChName[64];				//ͨ������
	NPC_BOOL									bIfPictureFlip;				//�Ƿ�ͼ��ת

	NPC_BOOL									iStreamNo;					//������

	NPC_BOOL									bMainStreamOpenFlag;		//�������򿪱�־
	NPC_BOOL									bSubStreamOpenFlag;			//�������򿪱�־
	NPC_BOOL									bThirdStreamOpenFlag;		//��3�����򿪱�־

	PNPC_VOID									pMcSrvData;					//���ط�������

	NPC_HANDLE									hNavFile;					//NAV�ļ����
	NPC_TIME_T									tRecStartTime;				//¼��ʼʱ��
	NPC_DWORD									dwRecvFrameNum;				//����֡��
	NPC_BOOL									bIfWriteIFrame;				//�Ƿ�д����I֡

	NPC_BOOL									bTalkIfOpen;				//�Ƿ�򿪶Խ�

	NPC_INT										iMainVideoLevel;			//��������Ƶ�����ȼ�
	NPC_INT										iSubVideoLevel;				//��������Ƶ�����ȼ�

	NPC_TIME_T									tPrecSendAlarmMsgTime;		//ǰһ�η��ͱ�����Ϣ��ʱ��
	NPC_INT										iAlarmState;				//����״̬

	NPC_S_PVM_IMD_CFG_DEV_CODEC					tDevCodec;					//ͨ��������Ϣ
	NPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT	tMotionDetect;				//�ƶ����
	NPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE			tProbe;						//̽ͷ���뱨��
	NPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN			tDevRecordPlan;				//¼��ƻ�
	NPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE		tAlarmCloudStorage;			//�����ƴ洢����

	NPC_TIME_T									tPrecShowCacheTime;			//ǰһ����ʾ�����ʱ��

} NPC_S_UMSP_CAMERA_DATA, *PNPC_S_UMSP_CAMERA_DATA;

//�ļ���������
typedef struct _NPC_S_UMSP_FILE_WORK_DATA
{
	NPC_BOOL									bIfUsed;					//�Ƿ�ռ��
	NPC_DWORD									dwFileReadId;				//�ļ���ȡID
	NPC_HANDLE									hNavFile;					//NAV�ļ����
	NPC_DWORD									dwFileTimeLen;				//�ļ�ʱ�䳤�ȣ��룩
	NPC_INT										iFileVideoFrameRate;		//��Ƶ֡��
	time_t										tFileBeginRecTime;			//�ļ���ʼ¼��ʱ��
	NPC_BOOL									bIfOnlySendIFrame;			//�Ƿ�ֻ��I֡
	NPC_INT										iDiscardIFrame;				//����I֡����0������I֡��1������1��I֡�������1��I֡���䣩��2������2��I֡���������

} NPC_S_UMSP_FILE_WORK_DATA, *PNPC_S_UMSP_FILE_WORK_DATA;

//MP3�ļ�����
typedef struct _NPC_S_UMSP_MP3_FILE_DATA
{
	NPC_BOOL									bIfUsed;					//�Ƿ�ռ��
	NPC_CHAR									sFileName[128];				//�ļ���
	NPC_BOOL									bIfPlaying;					//�Ƿ��ڲ���
	NPC_INT										iVolumeSize;				//����
	NPC_DWORD									dwUpFileId;					//�ϴ��ļ�ID

	FILE*										pSaveFile;					//�����ļ�

} NPC_S_UMSP_MP3_FILE_DATA, *PNPC_S_UMSP_MP3_FILE_DATA;

//���ط�������
typedef struct _NPC_S_UMSP_MCSRV_DATA
{
	NPC_BOOL									bRunFlag;					//���б�־
	NPC_HANDLE									hThread;					//�߳̾��

	NPC_S_UMSP_CONFIG_DATA						tConfig;					//���ò���

	NPC_HANDLE									hUmspProSrv;				//UMSPЭ�������
	NPC_HANDLE									hFileCamera;				//�ļ���������
	NPC_INT										iChNum;						//ͨ����

	NPC_S_DPS_DEV_CAP_INFO						tDevCapInfo;				//�豸������Ϣ
	NPC_S_PVM_IMD_CFG_DEV_IP					tDevIp;						//�豸IP
	NPC_S_PVM_IMD_CFG_DEV_WIFI					tDevWifi;					//�豸WIFI
	NPC_TIME_T									tDevTime;					//�豸ʱ��

	NPC_S_UMSP_CAMERA_DATA						tCameraTable[NPC_D_DPS_MAX_CHANNEL_NUM+1];			//�������
	NPC_S_UMSP_FILE_WORK_DATA					tFileWorkTable[NPC_D_UMSP_MC_MAX_FILE_WORK_NUM];	//�ļ�������

	NPC_BOOL									bAlarmIfOpen;				//�Ƿ�򿪲���

	NPC_S_UMSP_MP3_FILE_DATA					tMp3FileTable[NPC_D_UMSP_MC_MAX_MP3_FILE_NUM];	//MP3�ļ���
	NPC_INT										iMp3FileNum;									//MP3�ļ���

	NPC_TIME_T									tPrecReadAlarmStateTime;	//ǰһ�ζ�ȡ����״̬��ʱ��
	NPC_TIME_T									tPrecReadConfigTime;		//ǰһ�ζ�ȡ���õ�ʱ��

	NPC_UINT									uiAlarmSeqNo;				//�������
	NPC_CHAR									sImportCfgBuf[128];			//���������

} NPC_S_UMSP_MCSRV_DATA, *PNPC_S_UMSP_MCSRV_DATA;



#endif

