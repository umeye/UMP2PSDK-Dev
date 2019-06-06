/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_DPS_DevProNetServer.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-07-16
 * Description   :  UMSP�豸Э���������ӿ�
 *----------------------------------------------------------------------------*/

#ifndef __NPC_DPS_DEVPRONETSERVER_H
#define __NPC_DPS_DEVPRONETSERVER_H

#include "NPC_TypeDef.h"
#include "NPC_MON_ConsDef.h"
#include "NPC_DPS_DevProtocolDef.h"


#ifdef _WIN32
	#ifdef _NPC_DPS_DEVPRO_EXPORTS
		#define NPC_DPS_DEVPRO_API __declspec(dllexport)
	#else
		#ifdef _NPC_DPS_DEVPRO_NON
			#define NPC_DPS_DEVPRO_API
		#else
			#define NPC_DPS_DEVPRO_API __declspec(dllimport)
		#endif
	#endif
#else
	#define NPC_DPS_DEVPRO_API
#endif


//-------------------------------------------------------------------------------
//��������
#define NPC_D_DPS_MAX_CHANNEL_NUM						64						//���ͨ����
#define NPC_D_DPS_MAX_CH_STREAM_NUM						3						//���ͨ��������

//-------------------------------------------------------------------------------
//Ȩ��λ����
#define NPC_D_DPS_POP_REALPLAY							0x00000001				//ʵʱԤ��Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_PTZ_CTRL							0x00000002				//��̨����Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_TALK								0x00000004				//�����Խ�Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_QUERY_FILE						0x00000008				//¼���ļ���ѯȨ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_BACKPLAY							0x00000010				//¼��ط�Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_ALARM								0x00000020				//��������Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_GET_CONFIG						0x00000040				//��ѯ����Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_SET_CONFIG						0x00000080				//��������Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�


//-------------------------------------------------------------------------------
//�û���Ϣ
typedef struct _NPC_S_DPS_USER_INFO
{
	NPC_CHAR										sUserName[32];				//�û���
	NPC_CHAR										sUserPwd[32];				//�û����루���ģ�
	NPC_BYTE										ucPopTable[8];				//Ȩ�ޱ���ͣʹ�ã�������ǰ�ĳ���

	NPC_DWORD										dwGlobalPop;				//ȫ��Ȩ�ޣ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_DWORD										dwChPopTable[NPC_D_DPS_MAX_CHANNEL_NUM];	//ͨ��Ȩ�ޱ�λֵ�ο�NPC_D_DPS_POP_*����

} NPC_S_DPS_USER_INFO, *PNPC_S_DPS_USER_INFO;

//�豸������Ϣ
typedef struct _NPC_S_DPS_DEV_CAP_INFO
{
	NPC_CHAR										sDevType[12];				//�豸���ͣ��磺DEV��IPC
	NPC_CHAR										sDevModel[32];				//�豸�ͺ�
	NPC_CHAR										sSerialNumber[32];			//���к�
	NPC_INT											iVideoChanNum;				//�豸ͨ������
	NPC_INT											iAudioChanNum;				//�豸����ͨ����
	NPC_INT											iPtzChNum;					//PTZͨ����
	NPC_INT											iAlarmInPortNum;			//�����������
	NPC_INT											iAlarmOutPortNum;			//�����������
	NPC_INT											iDiskNum;					//Ӳ�̸���
	NPC_INT											iSubProtoNum;				//����������0��ʾ��֧��������
	NPC_BOOL										bIfSupportZeroChannel;		//�Ƿ�֧����ͨ��
	NPC_BOOL										bIfSupportRecordBytime;		//�Ƿ�֧�ְ�ʱ��ط�
	NPC_BOOL										bIfSupportFileRange;		//�Ƿ�֧�ֻ�ȡ¼���ļ�ʱ�䷶Χ

	NPC_BOOL										bIfOpenDoConnCallback;		//�Ƿ������Ӵ���ص�
	PNPC_VOID										pDoConnCallback;			//���Ӵ���ص�������ڵ�ַ	
	PNPC_VOID										pDoConnUserData;			//���Ӵ���ص��û�����	
	
	NPC_CHAR										bEnableSpeedCtl;			//�Ƿ�֧�ֻط��ٶȿ���
	NPC_CHAR										bEnableAlarmPushCallback;	//�Ƿ���ձ������ͻص�������ID��
																				//NPC_D_DPS_MSGID_EVENT_E2_GUARD
																				//NPC_D_DPS_MSGID_EVENT_E2_UNGUARD
	NPC_CHAR										sReserve[62];				//Ԥ��
} NPC_S_DPS_DEV_CAP_INFO, *PNPC_S_DPS_DEV_CAP_INFO;

//���Ӵ�����Ϣ
typedef struct _NPC_S_DPS_CONNECT_INFO
{
	NPC_DWORD										dwLoginID;					//��¼ʶ��ID
	NPC_INT											iChNo;						//ͨ����
	NPC_INT											iStreamNo;					//������
	
	NPC_INT											iType;						//�������ͣ�0=��ʵʱԤ����1=�ر�ʵʱԤ��
	NPC_INT											iRet;						//��������0=�ɹ�������ʧ�ܣ�iType = 0ʱ��Ч
} NPC_S_DPS_CONNECT_INFO, *PNPC_S_DPS_CONNECT_INFO;
//-------------------------------------------------------------------------------
//Э���¼��ص���������
typedef		NPC_VOID	(*PNPC_F_DPS_ProEventCallback)(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD+��������
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ѯ�û���Ϣ�ص���������
typedef		NPC_BOOL	(*PNPC_F_DPS_QueryUserInfoCallback)(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	IN		PNPC_CHAR								in_pUserName,				//�û���
	OUT		PNPC_S_DPS_USER_INFO					out_pUserInfo				//�û���Ϣ
	);

//��ѯ�û���Ϣ�ص���������(��չ���ͻ��˶��Ʊ�ʶУ��)
//0:У��ͨ����1:�û�������2:�������3:У�����
typedef		NPC_INT	(*PNPC_F_DPS_UserCallbackByCustom)(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	IN		PNPC_CHAR								in_pUserName,				//�û���
 	IN		NPC_INT									in_iCltCumNum,				//�ͻ��˶��Ʊ�ʶ����
 	IN		NPC_INT									in_iCltCumStrLen,			//�ͻ��˶��Ʊ�ʶ�ַ�������
 	IN		PNPC_CHAR								in_pCltCumStr,				//�ͻ��˶��Ʊ�ʶ�ַ���
	OUT		PNPC_S_DPS_USER_INFO					out_pUserInfo				//�û���Ϣ
	);


//���Ӵ���ص���������
typedef		NPC_BOOL	(*PNPC_F_DPS_DoConnectCallback)(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	OUT		PNPC_S_DPS_CONNECT_INFO					out_pDoConnInfo				//���Ӵ�����Ϣ
	);

//-------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif


//�����豸Э���������
NPC_DPS_DEVPRO_API		NPC_HANDLE	NPC_F_DPS_StartDevProNetServer(
	IN		NPC_USHORT								in_usMediaTcpPort,			//ý��TCP�����˿ں�
	IN		PNPC_S_DPS_DEV_CAP_INFO					in_pDevCapInfo,				//�豸������Ϣ
	IN		PNPC_F_DPS_ProEventCallback				in_pProEventCallback,		//Э���¼��ص�����ָ��
	IN		PNPC_VOID								in_pProEventUserData,		//Э���¼��û�����
	IN		PNPC_F_DPS_QueryUserInfoCallback		in_pQueryUserInfoCallback,	//��ѯ�û���Ϣ�ص�����ָ��
	IN		PNPC_VOID								in_pQueryUserInfoUserData,	//��ѯ�û���Ϣ�û�����
	IN		NPC_BOOL								in_bIfDebug=FALSE,			//�Ƿ���ԣ��ڵ���״̬�£�������ܶ���־��Ϣ����ʽʹ��ʱ��Ҫ�ر�
	IN		NPC_BOOL								in_bIfShowStreamLog=FALSE,	//�Ƿ���ʾ����־����ý�����շ���־��Ϣ
	IN		NPC_BOOL								in_bIfWriteLogToFile=FALSE,	//�Ƿ�д��־���ļ�
	IN		PNPC_CHAR								in_pLogDir=NULL,			//��־Ŀ¼����־�ļ����Զ���������ʽΪLog����.txt
	IN		NPC_USHORT								in_usLogPort=0,				//��־�˿ںţ����Ϊ0����������־�����˿ڣ�����0��������־�����˿ڷ���
	IN		NPC_INT									in_iPwdMode=0				//����ģʽ��ָ���봫��SDK�ķ�ʽ����0�����ģ�1��MD5
	);

//ֹͣ�豸Э���������
NPC_DPS_DEVPRO_API		NPC_VOID	NPC_F_DPS_StopDevProNetServer(
	IN		NPC_HANDLE								in_hDevProNetSrv			//�豸Э�����������
	);

//�����û���Ϣ�ص����ͻ��˶��Ʊ�ʶУ�飩
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetUserCallbackByCustom(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		PNPC_F_DPS_UserCallbackByCustom			in_pUserCallbackByCustom,	//��ѯ�û���Ϣ�ص�����ָ��
	IN		PNPC_VOID								in_pUserByCustomUserData	//��ѯ�û���Ϣ�û�����
	);

//-------------------------------------------------------------------------------
//������Ϣ���豸Э���������
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SendDevProData(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		PNPC_BYTE								in_pDevProDataBuf,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iDevProDataLen			//�豸Э�����ݳ���
	);

//����ý�����ݻ����С
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetMediaDataBufSize(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iMediaDataBufSize		//ý�����ݻ����С���ֽڣ�
	);

//����ͨ��ý�����ݻ����С��1~30Mbps�������in_iMediaDataBufSize = 0����ʾ��������
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetMediaDataBufSizeByCh(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		NPC_INT									in_iMediaDataBufSize		//ý�����ݻ����С���ֽڣ�
	);

//��������״̬��Ϣ��ʾ����
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetShowRunState(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_BOOL								in_bIfShowRunState			//�Ƿ���ʾ����״̬��Ϣ��TRUE��ʾҪ��ʾ��FALSE��ʾ����ʾ��ȱʡΪTRUE
	);

//����ʵʱԤ��ֻ��I֡��ʱ�����룩����ͣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetOnlySendIFrameTimeLen(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iIFrameTimeLen			//ֻ��I֡��ʱ�����룩��ȱʡΪ60��
	);

//�������ʵʱԤ��·�����ͻ���·����
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SetMaxRealplayClientNum(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iMaxClientNum			//���ʵʱԤ���ͻ�������ȱʡΪ64·��ֵ��ΧΪ1~1024
	);

//-------------------------------------------------------------------------------
//������Ƶ�����൱�ڷ���NPC_D_DPS_MSGID_MEDIA_E8_VIDEO_FRAME��Ϣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_InputVideoStream(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		NPC_INT									in_iFrameType,				//֡���ͣ��μ�NPC_D_DPS_VIDEO_FRAME_TYPE_*����
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý�����ݻ�����
	IN		NPC_INT									in_iMediaDataLen			//ý�����ݳ���
	);

//������Ƶ�����൱�ڷ���NPC_D_DPS_MSGID_MEDIA_E8_AUDIO_FRAME��Ϣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_InputAudioStream(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý�����ݻ�����
	IN		NPC_INT									in_iMediaDataLen			//ý�����ݳ���
	);

//������Ƶ�����൱�ڷ���NPC_D_DPS_MSGID_MEDIA_E8_VIDEO_FRAME_EX��Ϣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_InputVideoStreamEx(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		NPC_INT									in_iFrameType,				//֡���ͣ��μ�NPC_D_DPS_VIDEO_FRAME_TYPE_*����
	IN		NPC_DWORD								in_dwTimeStamp,				//ʱ�����32λ
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý�����ݻ�����
	IN		NPC_INT									in_iMediaDataLen			//ý�����ݳ���
	);

//������Ƶ�����൱�ڷ���NPC_D_DPS_MSGID_MEDIA_E8_AUDIO_FRAME_EX��Ϣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_InputAudioStreamEx(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		NPC_DWORD								in_dwTimeStamp,				//ʱ�����32λ
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý�����ݻ�����
	IN		NPC_INT									in_iMediaDataLen			//ý�����ݳ���
	);

//�޸ı��������������NPC_D_DPS_MSGID_EVENT_E2_MODIFY_CODEC��Ϣ��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_ModifyCodec(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	IN		NPC_BOOL								in_bVideoFlag,				//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	IN		NPC_BOOL								in_bAudioFlag,				//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	IN		NPC_INT									in_iVideoCodecId,			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	IN		NPC_INT									in_iVideoFrameRate,			//��Ƶ֡��
	IN		NPC_INT									in_iVideoBitRate,			//��Ƶ���ʣ�kbps��
	IN		NPC_USHORT								in_usVideoWidth,			//��Ƶ���
	IN		NPC_USHORT								in_usVideoHeight,			//��Ƶ�߶�
	IN		NPC_INT									in_iAudioCodecId,			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	IN		NPC_INT									in_iAudioBitRate,			//��Ƶ���ʣ�kbps������64
	IN		NPC_INT									in_iAudioSampleRate,		//��Ƶ�����ʣ���8000
	IN		NPC_INT									in_iAudioChNum				//��Ƶ����������1
	);

//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_UpAlarmMsg(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
	IN		NPC_INT									in_iAlarmState,				//����״̬��0��ֹͣ��1����ʼ
	IN		PNPC_CHAR								in_pAlarmInfo				//������Ϣ
	);

//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SendAlarmMsg(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		PNPC_CHAR								in_pAlarmId,				//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
	IN		PNPC_CHAR								in_pAlarmInfo,				//������Ϣ
	IN		PNPC_S_TD_DATE_TIME						in_pAlarmTime=NULL			//����ʱ��
	);

//��ѯͨ��������Ƶ֡��
NPC_DPS_DEVPRO_API		NPC_INT		NPC_F_DPS_QueryCacheVideoFrameNum(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo				//�����ţ�0����������1��������
	);

//��ѯͨ������ý������
NPC_DPS_DEVPRO_API		NPC_BOOL		NPC_F_DPS_QuerySendMediaDataLen(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//�����ţ�0����������1��������
	OUT		PNPC_DWORD								out_pMediaLen,				//ý�����ݳ���
	OUT		PNPC_INT								out_pSendTime				//ý�����ݳ����Ƿ����˶೤ʱ���
	);

//--------------------------------------------------------------------------------
//����ý����Դ��ֵ
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_ControlMediaResource(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_BOOL								in_bIfOpenMediaResourceCtl,	//�Ƿ���ý����Դ��ֵ����
	IN		NPC_FLOAT								in_fMaxMediaResource,		//������Ч�����ý����Դ:������ÿ���������1���������ͻط���İ����ô���
	IN		NPC_FLOAT								in_fMainMediaResourceLoss,	//������Ч��ÿ·�����������
	IN		NPC_FLOAT								in_fReplayResourceLoss		//������Ч��ÿ·�طŵ���Դ���
	);

//��ȡ��ǰ���е�ý����Դ��С
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_GetFreeMediaResourceNum(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		PNPC_FLOAT								in_pMaxMediaResource,		//���ý����Դ:������ÿ���������1���������ͻط���İ����ô���
	IN		PNPC_FLOAT								in_pFreeMediaResource		//����ý����Դ
	);


//------------------------------------------------------------------------------
//�����е�ý��ͨ�����Ͷ�����Ϣ
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_SendCusFuncToOrderChnl(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//�豸Э�����������
	IN		NPC_INT									in_iCusFuncId,				//����ID
	IN		PNPC_BYTE								in_pBodyDataBuf,			//�������ݻ�����
	IN		NPC_INT									in_iBodyDataLen				//�������ݳ���
	);

//��ѯ��ǰ�������Ӧͨ�����û���Ϣ����������ID��
NPC_DPS_DEVPRO_API		NPC_BOOL	NPC_F_DPS_QueryUserInfoByTransId(
	IN		NPC_HANDLE								in_hDevProNetSrv,			//[IN]�豸Э�����������
	IN		NPC_DWORD								in_dwTransId,				//[IN]����ID
	OUT		PNPC_S_DPS_USER_INFO					out_pUserInfo				//[OUT]�û���Ϣ	
	);

#ifdef __cplusplus
}
#endif

#endif

