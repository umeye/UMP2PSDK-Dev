/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_DISP_Sdk_DataDef.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2011-08-29
 * Description   :  ����SDK���ݶ���
 *----------------------------------------------------------------------------*/

#ifndef __NPC_DISP_SDK_DATADEF_H
#define __NPC_DISP_SDK_DATADEF_H

#include "NPC_TypeDef.h"
#include "NPC_DEF_CM_DataDef.h"


//--------------------------------------------------------------------------------
//�豸ID�������Ͷ���
#define NPC_D_DISP_SDK_DEVMAINTYPE_SERVER					1								//���������ͣ����ȷ�����/����/�洢������/��ý���������
#define NPC_D_DISP_SDK_DEVMAINTYPE_DEV						3								//�豸���ͣ�DVR/IPC/ƽ̨��
#define NPC_D_DISP_SDK_DEVMAINTYPE_CAMERA					5								//���������
#define NPC_D_DISP_SDK_DEVMAINTYPE_CLIENT					6								//���ȿͻ������ͣ���¼����Ʒ�������ҵ��ӿڷ��������û��ͻ��ˣ�


//�豸ID�������Ͷ���
//������������
#define NPC_D_DISP_SDK_DEVSUBTYPE_SR_DISP					1								//���ȷ�����
#define NPC_D_DISP_SDK_DEVSUBTYPE_SR_GATEWAY				2								//����
#define NPC_D_DISP_SDK_DEVSUBTYPE_SR_STORE					3								//�洢������
#define NPC_D_DISP_SDK_DEVSUBTYPE_SR_MEDIA					4								//��ý�������

//�豸������
#define NPC_D_DISP_SDK_DEVSUBTYPE_DV_DVR					1								//DVR
#define NPC_D_DISP_SDK_DEVSUBTYPE_DV_IPC					2								//IPC
#define NPC_D_DISP_SDK_DEVSUBTYPE_DV_FLAT					3								//ƽ̨

//�ͻ���������
#define NPC_D_DISP_SDK_DEVSUBTYPE_CL_REC					1								//¼����Ʒ�����
#define NPC_D_DISP_SDK_DEVSUBTYPE_CL_SIG					2								//���������
#define NPC_D_DISP_SDK_DEVSUBTYPE_CL_INTER					6								//ҵ��ӿڷ�����
#define NPC_D_DISP_SDK_DEVSUBTYPE_CL_USER					8								//�û��ͻ���


//--------------------------------------------------------------------------------
//¼���ļ���������
#define NPC_D_DISP_SDK_RECFILE_FILE_FLAG					0x4143504E						//¼���ļ�ͷ��־����ΪNPCA
#define NPC_D_DISP_SDK_RECFILE_FIELD_FLAG					0x01000000						//¼���ļ��α�־
#define NPC_D_DISP_SDK_RECFILE_FRAME_HEAD_TYPE				0xEC							//¼��֡ͷ����
#define NPC_D_DISP_SDK_RECFILE_INDEX_HEAD_TYPE				0xED							//¼��������ͷ����
#define NPC_D_DISP_SDK_RECFILE_INDEX_TABLE_SIZE				8192							//ȱʡ¼���������С
#define NPC_D_DISP_SDK_RECFILE_CACHE_MEDIA_SIZE				1024*1024*4						//ȱʡ����ý�����ݴ�С

//--------------------------------------------------------------------------------
//RTSP������������
#define NPC_D_DISP_SDK_RTSP_VEDIO_SDP_ID					96								//��ƵSDPID
#define NPC_D_DISP_SDK_RTSP_AUDIO_SDP_ID					97								//��ƵSDPID

#define NPC_D_DISP_SDK_RTSP_NAV_VEDIO_SDP_ID				180								//���̸�ʽ��ƵSDPID
#define NPC_D_DISP_SDK_RTSP_NAV_AUDIO_SDP_ID				181								//���̸�ʽ��ƵSDPID

#define NPC_D_DISP_SDK_RTSP_DEF_VEDIO_TIMESTAMP				90000							//ȱʡ��Ƶʱ����ο�ֵ

#define NPC_D_DISP_SDK_RTSP_VEDIO_TRACK_ID					0								//��ƵTRACKID
#define NPC_D_DISP_SDK_RTSP_AUDIO_TRACK_ID					1								//��ƵTRACKID

//--------------------------------------------------------------------------------
//��Ƶ���볣������
#define NPC_D_DISP_SDK_VEDIO_CODEC_H264						0x0101							//H264����
#define NPC_D_DISP_SDK_VEDIO_CODEC_MPEG4					0x0102							//MPEG4����
#define NPC_D_DISP_SDK_VEDIO_CODEC_H263						0x0103							//H263����

//��Ƶ���볣������
#define NPC_D_DISP_SDK_AUDIO_ENCODE_PCM_S16					0x0201							//16λ����PCM
#define NPC_D_DISP_SDK_AUDIO_ENCODE_PCM_ALAW				0x0202							//8λA��PCM��G711A��
#define NPC_D_DISP_SDK_AUDIO_ENCODE_PCM_ULAW				0x0203							//8λU��PCM��G711U��
#define NPC_D_DISP_SDK_AUDIO_ENCODE_G721					0x0204							//G721
#define NPC_D_DISP_SDK_AUDIO_ENCODE_G723_1					0x0205							//G723.1
#define NPC_D_DISP_SDK_AUDIO_ENCODE_G726					0x0206							//G726
#define NPC_D_DISP_SDK_AUDIO_ENCODE_G729					0x0207							//G729
#define NPC_D_DISP_SDK_AUDIO_ENCODE_AAC						0x0208							//AAC
#define NPC_D_DISP_SDK_AUDIO_ENCODE_AMR						0x0209							//AMR

//¼���ļ���ý��ͷ��ý�����ͳ�������
#define NPC_D_DISP_SDK_RECFILE_MEDIATYPE_VEDIO				0								//��Ƶ
#define NPC_D_DISP_SDK_RECFILE_MEDIATYPE_AUDIO				1								//��Ƶ


//--------------------------------------------------------------------------------
//ʵʱԤ�����ƴ��붨��
#define NPC_D_DISP_SDK_REALPLAY_CTRLCODE_STOP				1								//ֹͣ
#define NPC_D_DISP_SDK_REALPLAY_CTRLCODE_PAUSE				2								//��ͣ
#define NPC_D_DISP_SDK_REALPLAY_CTRLCODE_CONTINUE			3								//����
#define NPC_D_DISP_SDK_REALPLAY_CTRLCODE_START_AUDIO		4								//������Ƶ
#define NPC_D_DISP_SDK_REALPLAY_CTRLCODE_STOP_AUDIO			5								//ֹͣ��Ƶ

//--------------------------------------------------------------------------------
//¼��طſ��ƴ��붨��
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_STOP				1								//ֹͣ
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_PAUSE				2								//��ͣ
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_CONTINUE			3								//����
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_FAST_FORWARD		4								//���
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_SLOW_FORWARD		5								//����
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_FAST_BACK			6								//����
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_SLOW_BACK			7								//����
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_RESUME				8								//�ָ���������
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_FRAME_FORWARD		9								//��֡��
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_FRAME_BACK			10								//��֡��
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_SEEK				11								//��ת����λ��
#define NPC_D_DISP_SDK_PLAYBACK_CTRLCODE_SET_FRAMERATE		12								//����֡��

//--------------------------------------------------------------------------------
//¼�����ؿ��ƴ��붨��
#define NPC_D_DISP_SDK_RECDOWN_CTRLCODE_STOP				1								//ֹͣ
#define NPC_D_DISP_SDK_RECDOWN_CTRLCODE_PAUSE				2								//��ͣ
#define NPC_D_DISP_SDK_RECDOWN_CTRLCODE_CONTINUE			3								//����

//--------------------------------------------------------------------------------
//��̨Ԥ�õ������
#define NPC_D_DISP_SDK_PTZPRESET_SET_PRESET					0								//����Ԥ�õ� 
#define NPC_D_DISP_SDK_PTZPRESET_CLE_PRESET					1								//���Ԥ�õ� 
#define NPC_D_DISP_SDK_PTZPRESET_GOTO_PRESET				2								//ת��Ԥ�õ� 

//--------------------------------------------------------------------------------
//����Ƶ��ʽ���ݽṹ
typedef struct _NPC_S_DISP_SDK_MN_AV_FORMAT
{
	NPC_BOOL							bVedioFlag;											//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ
	NPC_BOOL							bAudioFlag;											//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ

	NPC_INT								iVedioCodecId;										//��Ƶ���������0��Ĭ�ϱ��룬1��H264��2��MPEG4��3��H263������
	NPC_USHORT							usVedioWidth;										//��Ƶ���
	NPC_USHORT							usVedioHeight;										//��Ƶ�߶�
	NPC_INT								iVedioBitRate;										//��Ƶ���ʲ�����0��ʾΪĬ������
	NPC_INT								iVedioFrameRate;									//��Ƶ֡�ʲ�����0��ʾΪĬ��֡��
	NPC_CHAR							sVedioParams[NPC_D_DEF_CM_VEDIO_PARAMS_BUFSIZE];	//��Ƶ������BASE64��ʽ���Զ̺ŷָ������ΪH264��ʽ�����������SPS��PPS

	NPC_INT								iAudioCodecId;										//��Ƶ���������0��Ĭ�ϱ��룬1��16λ����PCM��2��G711A��3��G711U��4��G721������
	NPC_INT								iAudioSampleRate;									//��Ƶ������
	NPC_INT								iAudioChNum;										//��Ƶͨ������1��2
	NPC_CHAR							sAudioParams[NPC_D_DEF_CM_AUDIO_PARAMS_BUFSIZE];	//��Ƶ����

} NPC_S_DISP_SDK_MN_AV_FORMAT, *PNPC_S_DISP_SDK_MN_AV_FORMAT;

//������Ϣ���ݽṹ
typedef struct _NPC_S_DISP_SDK_GW_INFO
{
	NPC_CHAR							sGwId[NPC_D_DEF_CM_DEVID_BUFSIZE];					//����ID
	NPC_CHAR							sGwName[NPC_D_DEF_CM_DEVNAME_BUFSIZE];				//��������
	NPC_CHAR							sGwIpAddr[NPC_D_DEF_CM_IPADDR_BUFSIZE];				//����IP��ַ
	NPC_USHORT							usGwRtspPort;										//����RTSP�˿ں�
	NPC_INT								iDevNum;											//�豸��

} NPC_S_DISP_SDK_GW_INFO, *PNPC_S_DISP_SDK_GW_INFO;

//�豸��Ϣ���ݽṹ
typedef struct _NPC_S_DISP_SDK_DEV_INFO
{
	NPC_CHAR							sDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];					//�豸ID
	NPC_INT								iDevVendor;											//�豸����
	NPC_INT								iDevType;											//�豸����
	NPC_CHAR							sDevName[NPC_D_DEF_CM_DEVNAME_BUFSIZE];				//�豸����
	NPC_CHAR							sDevIpAddr[NPC_D_DEF_CM_IPADDR_BUFSIZE];			//�豸IP��ַ
	NPC_USHORT							usDevPort;											//�豸�˿ں�
	NPC_CHAR							sDevUserName[NPC_D_DEF_CM_USERNAME_BUFSIZE];		//�û���
	NPC_CHAR							sDevPwd[NPC_D_DEF_CM_USERPWD_BUFSIZE];				//����
	NPC_CHAR							sExtendParam[NPC_D_DEF_CM_EXTEND_PARAM_BUFSIZE];	//��չ����
	NPC_INT								iCameraNum;											//�������
	NPC_CHAR							sGwId[NPC_D_DEF_CM_DEVID_BUFSIZE];					//��������ID

} NPC_S_DISP_SDK_DEV_INFO, *PNPC_S_DISP_SDK_DEV_INFO;

//�������Ϣ���ݽṹ
typedef struct _NPC_S_DISP_SDK_CAMERA_INFO
{
	NPC_CHAR							sCameraId[NPC_D_DEF_CM_DEVID_BUFSIZE];				//�����ID
	NPC_INT								iChNo;												//ͨ����
	NPC_INT								iState;												//�����״̬��0��ͣ��״̬��1������״̬
	NPC_BOOL							bIfRecing;											//�Ƿ���¼��
	NPC_CHAR							sExtId[NPC_D_DEF_CM_DEVID_BUFSIZE];					//��չID
	NPC_CHAR							sAtDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];				//�����豸ID

} NPC_S_DISP_SDK_CAMERA_INFO, *PNPC_S_DISP_SDK_CAMERA_INFO;

//��Ԫͷ�ṹ
typedef struct _NPC_S_DISP_SDK_UNIT_HEAD
{
	NPC_INT								iUnitType;											//��Ԫ���ͣ�0�����أ�1���豸��2�������

} NPC_S_DISP_SDK_UNIT_HEAD, *PNPC_S_DISP_SDK_UNIT_HEAD;

//¼���ļ���Ϣ���ݽṹ
typedef struct _NPC_S_DISP_SDK_RECFILE_INFO
{
	NPC_CHAR							sCameraId[NPC_D_DEF_CM_DEVID_BUFSIZE];				//�����ID
	NPC_CHAR							sRecFileName[NPC_D_DEF_CM_FILENAME_BUFSIZE];		//¼���ļ���
	NPC_CHAR							sRecBeginTime[20];									//¼��ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_CHAR							sRecEndTime[20];									//¼�����ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_INT								iDevVendor;											//�豸����
	NPC_INT								iRecCodecFormat;									//¼������ʽ��0��Ϊ��׼��ʽ���μ�tRecFormat������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
	NPC_S_DISP_SDK_MN_AV_FORMAT			tRecFormat;											//¼���ʽ
	NPC_INT								iRecPosType;										//¼������λ�����ͣ�0�������أ�1�����豸��2���ڴ洢������
	NPC_CHAR							sRecPosDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];			//¼������λ�õ��豸ID

} NPC_S_DISP_SDK_RECFILE_INFO, *PNPC_S_DISP_SDK_RECFILE_INFO;


//--------------------------------------------------------------------------------
//¼���ļ�ͷ���ݽṹ
typedef struct _NPC_S_DISP_SDK_REC_FILE_HEAD
{
	NPC_DWORD							dwFileFlag;											//�ļ�ͷ��־��ֵΪ"NPCA"���μ�NPC_D_DISP_SDK_RECFILE_FILE_FLAG����

	NPC_INT								iDevVendor;											//�豸����
	NPC_INT								iRecCodecFormat;									//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
	NPC_S_DISP_SDK_MN_AV_FORMAT			tRecFormat;											//¼���ʽ

	NPC_DWORD							dwTimestampRef;										//ʱ����ο�ֵ��Ĭ��Ϊ90000

	NPC_CHAR							sRecBeginTime[20];									//¼��ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_CHAR							sRecEndTime[20];									//¼�����ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_DWORD							dwRecTimeLen;										//¼��ʱ�����룩

	NPC_DWORD							dwFirstIndexOffset;									//��һ���������ֽ�ƫ������������ļ�ͷ

} NPC_S_DISP_SDK_REC_FILE_HEAD, *PNPC_S_DISP_SDK_REC_FILE_HEAD;

//¼���ͷ���ݽṹ
typedef struct _NPC_S_DISP_SDK_REC_FIELD_HEAD
{
	NPC_DWORD							dwFieldFlag;										//�α�ʶ��ֵΪNPC_D_DISP_SDK_RECFILE_FIELD_FLAG
	NPC_BYTE							ucFieldType;										//�����ͣ�ֵΪNPC_D_DISP_SDK_RECFILE_FRAME_HEAD_TYPE��NPC_D_DISP_SDK_RECFILE_INDEX_HEAD_TYPE
	NPC_BYTE							ucReserve;											//����
	NPC_USHORT							usReserve;											//����
	NPC_DWORD							dwFieldDataLen;										//�����ݳ��ȣ���������ͷ

} NPC_S_DISP_SDK_REC_FIELD_HEAD, *PNPC_S_DISP_SDK_REC_FIELD_HEAD;

//¼��֡ͷ���ݽṹ
typedef struct _NPC_S_DISP_SDK_REC_FRAME_HEAD
{
	NPC_BYTE							ucFrameType;										//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
	NPC_BYTE							ucReserve;											//����
	NPC_USHORT							usMediaType;										//ý�����ͣ�0����Ƶ��1����Ƶ���μ�NPC_D_DISP_SDK_RECFILE_MEDIATYPE_*����
	NPC_DWORD							dwTimestamp;										//ʱ���
	NPC_DWORD							dwRecOffsetTime;									//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��

} NPC_S_DISP_SDK_REC_FRAME_HEAD, *PNPC_S_DISP_SDK_REC_FRAME_HEAD;

//¼��������ͷ���ݽṹ
typedef struct _NPC_S_DISP_SDK_REC_INDEX_TABLE_HEAD
{
	NPC_DWORD							dwIndexTableSize;									//�������С��Ĭ��Ϊ8192���64K�ֽڵ�������
	NPC_DWORD							dwValidityIndexItemNum;								//��Ч����������
	NPC_DWORD							dwBeginOffsetTime;									//���������¼��ƫ�ƿ�ʼʱ�䣨�룩��������������Ը�ʱ���ƫ��ʱ��
	NPC_DWORD							dwNextIndexOffset;									//��һ��������ƫ��λ�ã�������ļ���ʼλ�ã����Ϊ0��ʾ�����һ��������

} NPC_S_DISP_SDK_REC_INDEX_TABLE_HEAD, *PNPC_S_DISP_SDK_REC_INDEX_TABLE_HEAD;

//¼�����������ݽṹ
typedef struct _NPC_S_DISP_SDK_REC_INDEX_ITEM
{
	NPC_DWORD							dwRecDataOffset;									//¼������ƫ�������ֽڣ���������ļ���ʼλ�ã�����������Ϊ���ʱ�䣨�룩

} NPC_S_DISP_SDK_REC_INDEX_ITEM, *PNPC_S_DISP_SDK_REC_INDEX_ITEM;


//--------------------------------------------------------------------------------
//͸������
typedef struct _NPC_S_DISP_COM_BODY_EXPAND_DATA
{
	NPC_CHAR							sDestDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];				//Ŀ���豸ID����IDΪ��ԪID��������ID��DVRID�������ID��
	NPC_CHAR							sSrcDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];				//Դ�豸ID����IDΪ��ԪID��������ID��DVRID�������ID��
	NPC_BOOL							bIfReturnResp;										//�Ƿ�Ҫ�󷵻�Ӧ����Ϣ
	NPC_INT								iDataLen;											//�������ݳ���

	NPC_INT								iRespResult;										//Ӧ������bIfWaitResp����ΪTRUE���ò�������Ч

} NPC_S_DISP_COM_BODY_EXPAND_DATA, *PNPC_S_DISP_COM_BODY_EXPAND_DATA;


//--------------------------------------------------------------------------------
//������Ϣ
typedef struct _NPC_S_DISP_COM_BODY_BILL_DATA
{
	NPC_CHAR							sBillId[NPC_D_DEF_CM_BILLID_BUFSIZE];				//����ID
	NPC_CHAR							sClientIpAddr[NPC_D_DEF_CM_IPADDR_BUFSIZE];			//�ͻ���IP��ַ
	NPC_CHAR							sMediaName[NPC_D_DEF_CM_FILENAME_BUFSIZE];			//�����ʵ�ý�����ƣ��������ID���ļ��� 
	NPC_CHAR							sBeginTime[20];										//���ʿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_CHAR							sEndTime[20];										//���ʽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_INT								iTimeLen;											//����ʱ������λΪ��

} NPC_S_DISP_COM_BODY_BILL_DATA, *PNPC_S_DISP_COM_BODY_BILL_DATA;

//��־��Ϣ���ݽṹ
typedef struct _NPC_S_DISP_COM_BODY_LOG_DATA
{
	NPC_CHAR							sLogId[NPC_D_DEF_CM_BILLID_BUFSIZE];				//��־ID
	NPC_CHAR							sDevId[NPC_D_DEF_CM_DEVID_BUFSIZE];					//������־���豸ID
	NPC_CHAR							sLogTime[20];										//��־������ʱ�� ����ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_INT								iLogType;											//��־���ͣ�0�����أ�1����Ҫ��2��һ�㣬3����ʾ��Ϣ
	NPC_CHAR							sLogInfo[256];										//��־��Ϣ����'\0'����

} NPC_S_DISP_COM_BODY_LOG_DATA, *PNPC_S_DISP_COM_BODY_LOG_DATA;

//�澯��Ϣ
typedef struct _NPC_S_DISP_COM_BODY_ALARM_DATA
{
	NPC_CHAR							sAlarmId[NPC_D_DEF_CM_BILLID_BUFSIZE];				//�澯ID
	NPC_CHAR							sAlarmTime[20];										//����������ʱ�� ����ʽΪ��YYYY-MM-DD HH:MM:SS
	NPC_INT								iAlarmType;											//��������
	NPC_INT								iAlarmLevel;										//��Ҫ�̶�
	NPC_CHAR							sAlarmInfo[256];									//������Ϣ����'\0'����

} NPC_S_DISP_COM_BODY_ALARM_DATA, *PNPC_S_DISP_COM_BODY_ALARM_DATA;

//¼��طŽ�����Ϣ
typedef struct _NPC_S_DISP_COM_BODY_PLAYBACK_DATA
{
	NPC_DWORD							dwMnId;												//����ID
	NPC_DWORD							dwPlaybackId;										//�ط�ID
	NPC_CHAR							sRecFileName[NPC_D_DEF_CM_FILENAME_BUFSIZE];		//¼���ļ���
	NPC_DWORD							dwPlayPos;											//��ǰ����λ�ã��룩
	NPC_INT								iPlayFrameRate;										//����֡��

} NPC_S_DISP_COM_BODY_PLAYBACK_DATA, *PNPC_S_DISP_COM_BODY_PLAYBACK_DATA;

//¼�����֪ͨ��Ϣ
typedef struct _NPC_S_DISP_COM_BODY_RECCOMPLETE_DATA
{
	NPC_DWORD							dwMnId;												//����ID
	NPC_S_DISP_SDK_RECFILE_INFO			tRecFileInfo;										//¼���ļ���Ϣ

} NPC_S_DISP_COM_BODY_RECCOMPLETE_DATA, *PNPC_S_DISP_COM_BODY_RECCOMPLETE_DATA;


//--------------------------------------------------------------------------------
//�����볣������
#define NPC_D_DISP_SDK_ERROR_CODE_SUCCESS							0						//�ɹ�

#define NPC_D_DISP_SDK_ERROR_CODE_GENERAL							1						//һ�����
#define NPC_D_DISP_SDK_ERROR_CODE_SYS_ERROR							2						//ϵͳ����������ڴ�ʧ�ܣ�����ϵͳ����ʧ�ܵ�
#define NPC_D_DISP_SDK_ERROR_CODE_PARAM_ERROR						3						//��������
#define NPC_D_DISP_SDK_ERROR_CODE_DB_ACC_FAIL						4						//���ݿ����ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_USERORPWD_ERROR					5						//�ͻ��˵�¼���û������������
#define NPC_D_DISP_SDK_ERROR_CODE_SEND_MSG_FAIL						6						//������Ϣʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_CLIENT_NO_LOGIN					1000					//�ͻ���δ��¼
#define NPC_D_DISP_SDK_ERROR_CODE_DEV_ID_EXIST						1001					//�豸ID�Ѵ���
#define NPC_D_DISP_SDK_ERROR_CODE_GW_ID_EXIST						1002					//����ID�Ѵ���
#define NPC_D_DISP_SDK_ERROR_CODE_GW_ID_NOT_FIND					1003					//����ID������
#define NPC_D_DISP_SDK_ERROR_CODE_DEV_ID_NOT_FIND					1004					//�豸ID������
#define NPC_D_DISP_SDK_ERROR_CODE_NOT_IDLE_GW						1005					//�޿������ؿ���
#define NPC_D_DISP_SDK_ERROR_CODE_ADD_DEV_FAIL						1006					//����豸ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_DEL_DEV_FAIL						1007					//ɾ���豸ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_ADD_CAMERA_FAIL					1008					//��������ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_DEL_CAMERA_FAIL					1009					//ɾ�������ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_CAMERA_ID_EXIST					1010					//�����ID�Ѵ���
#define NPC_D_DISP_SDK_ERROR_CODE_CAMERA_ID_NOT_FIND				1011					//�����ID������
#define NPC_D_DISP_SDK_ERROR_CODE_CH_DEV_PARAM_FAIL					1012					//�޸��豸����ʧ��
#define NPC_D_DISP_SDK_ERROR_CODE_PTZ_LOCKED						1013					//��̨������
#define NPC_D_DISP_SDK_ERROR_CODE_NO_FIND_DEST_ID					1014					//δ�ҵ�Ŀ��ID
#define NPC_D_DISP_SDK_ERROR_CODE_GW_NOT_ONLINE						1015					//����ID������




#endif

