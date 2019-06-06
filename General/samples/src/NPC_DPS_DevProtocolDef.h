/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_DPS_DevProtocolDef.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-07-16
 * Description   :  UMSP�豸Э�齻�����ݶ���
 *----------------------------------------------------------------------------*/

#ifndef __NPC_DPS_DEVPROTOCOLDEF_H
#define __NPC_DPS_DEVPROTOCOLDEF_H

#include "NPC_TypeDef.h"
#include "NPC_MON_ConsDef.h"
#include "NPC_MON_MpsDef.h"
#include "NPC_PVM_OrderCfgDef.h"


//-------------------------------------------------------------------------------
//��Ϣ���Ͷ���
#define NPC_D_DPS_MSG_TYPE_REQUEST								0					//������Ϣ
#define NPC_D_DPS_MSG_TYPE_RESPONSION							1					//Ӧ����Ϣ


//-------------------------------------------------------------------------------
//�¼���ϢID����
#define NPC_D_DPS_MSGID_EVENT_E2_OPEN_MEDIA_STREAM				0x0201				//��ý��������ʵʱԤ����
#define NPC_D_DPS_MSGID_EVENT_E2_CLOSE_MEDIA_STREAM				0x0202				//�ر�ý�������ر�ʵʱԤ����
#define NPC_D_DPS_MSGID_EVENT_E2_PTZ_CTRL						0x0203				//��̨����
#define NPC_D_DPS_MSGID_EVENT_E2_FORCE_I_FRAME					0x0204				//����ǿ�Ʒ���I֡
#define NPC_D_DPS_MSGID_EVENT_E2_MODIFY_CODEC					0x0205				//�޸ı���������ϲ�����SDK��
#define NPC_D_DPS_MSGID_EVENT_E2_GET_VIDEO_QUALITY_CAP			0x0206				//��ȡ��Ƶ�����ȼ������б�
#define NPC_D_DPS_MSGID_EVENT_E2_GET_VIDEO_QUALITY_LEVEL		0x0207				//��ȡ��Ƶ�����ȼ�
#define NPC_D_DPS_MSGID_EVENT_E2_SET_VIDEO_QUALITY_LEVEL		0x0208				//������Ƶ�����ȼ�

#define NPC_D_DPS_MSGID_EVENT_E2_FILE_QUERY						0x0211				//��ѯ�ļ���¼���ͼƬ�ļ���
#define NPC_D_DPS_MSGID_EVENT_E2_NSP_FILE_QUERY					0x0212				//��չ��ѯ�ļ���¼���ͼƬ�ļ���
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_RANGE_QUERY				0x0213				//��ѯ¼���ļ�ʱ�䷶Χ�����豸����������

#define NPC_D_DPS_MSGID_EVENT_E2_FILE_OPEN						0x0221				//���ļ�
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_CLOSE						0x0222				//�ر��ļ�
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_READ						0x0223				//��ȡ�ļ�
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_SEEK						0x0224				//��λ�ļ�
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_QVIDEO					0x0225				//��ѯ��Ƶ����
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_ONLY_IFRAME				0x0226				//����I֡����
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_RECOVER_ALLFRAME			0x0227				//����ָ�ȫ֡����
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_OPEN_BY_TIME				0x0228				//���ļ�,��ʱ�䷽ʽ�����豸����������
#define NPC_D_DPS_MSGID_EVENT_E2_FILE_SEEK_BY_TIME				0x0229				//��λ�ļ�,��ʱ�䷽ʽ�����豸����������

#define NPC_D_DPS_MSGID_EVENT_E2_TALK_START						0x0231				//��ʼ�����Խ�
#define NPC_D_DPS_MSGID_EVENT_E2_TALK_STOP						0x0232				//ֹͣ�����Խ�

#define NPC_D_DPS_MSGID_EVENT_E2_GUARD							0x0241				//��������ͣʹ�ã�
#define NPC_D_DPS_MSGID_EVENT_E2_UNGUARD						0x0242				//��������ͣʹ�ã�
#define NPC_D_DPS_MSGID_EVENT_E2_ALARM_INFO						0x0243				//�澯��Ϣ
#define NPC_D_DPS_MSGID_EVENT_E2_EX_ALARM_INFO					0x0244				//�澯��Ϣ����չ��

#define NPC_D_DPS_MSGID_EVENT_E3_MODIFY_USER_PWD				0x0301				//�޸��û�����
#define NPC_D_DPS_MSGID_EVENT_E3_GET_CONFIG						0x0302				//��ȡ���ò���
#define NPC_D_DPS_MSGID_EVENT_E3_SET_CONFIG						0x0303				//�������ò���
#define NPC_D_DPS_MSGID_EVENT_E3_GET_DEF_CONFIG					0x0304				//��ȡȱʡ���ò���
#define NPC_D_DPS_MSGID_EVENT_E3_IEC_IMP_CONFIG					0x0305				//��������
#define NPC_D_DPS_MSGID_EVENT_E3_IEC_EXP_CONFIG					0x0306				//��������

#define NPC_D_DPS_MSGID_EVENT_E3_QUERY_NET_INFO					0x0311				//��ѯ������Ϣ
#define NPC_D_DPS_MSGID_EVENT_E3_MODIFY_NET_ADDR				0x0312				//�޸������ַ

#define NPC_D_DPS_MSGID_EVENT_E3_COM_OPEN						0x0321				//�򿪴���
#define NPC_D_DPS_MSGID_EVENT_E3_COM_CLOSE						0x0322				//�رմ���
#define NPC_D_DPS_MSGID_EVENT_E3_COM_SEND_DATA					0x0323				//��������(�ͻ��˷��͸��豸��)
#define NPC_D_DPS_MSGID_EVENT_E3_COM_SUBS_DATA					0x0324				//�豸��������(�豸�˷��͸��ͻ���)(��Ӧ��)

#define NPC_D_DPS_MSGID_EVENT_E3_UNS_ADD_USER					0x0331				//�����û�
#define NPC_D_DPS_MSGID_EVENT_E3_UNS_DEL_USER					0x0332				//ɾ���û�
#define NPC_D_DPS_MSGID_EVENT_E3_UNS_GET_USER_POP				0x0333				//��ȡ�û�Ȩ���б�
#define NPC_D_DPS_MSGID_EVENT_E3_UNS_SET_USER_POP				0x0334				//�����û�Ȩ���б�

#define NPC_D_DPS_MSGID_EVENT_E7_CUSTOM							0x0701				//���ƹ���

#define NPC_D_DPS_MSGID_EVENT_E7_RMY_QUERY_ABILITY				0x0721				//��ѯ������
#define NPC_D_DPS_MSGID_EVENT_E7_RMY_REBOOT						0x0722				//�����豸(�ް���)(��Ӧ����Ϣ)
#define NPC_D_DPS_MSGID_EVENT_E7_RMY_STOP						0x0723				//ֹͣ�豸(�ް���)(��Ӧ����Ϣ)

#define NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_DEV_VER_INFO			0x0731				//��ѯ�豸�汾��Ϣ
#define NPC_D_DPS_MSGID_EVENT_E7_DUP_REQU_UPGRADE				0x0732				//��������
#define NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_PROGRESS				0x0733				//��ѯ��������
#define NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_TRANS_POS			0x0734				//��ѯ����λ��
#define NPC_D_DPS_MSGID_EVENT_E7_DUP_UPGRADE_DATA				0x0735				//�������ݰ�

#define NPC_D_DPS_MSGID_MEDIA_E8_VIDEO_FRAME					0x0801				//��Ƶ֡����
#define NPC_D_DPS_MSGID_MEDIA_E8_AUDIO_FRAME					0x0802				//��Ƶ֡����
#define NPC_D_DPS_MSGID_MEDIA_E8_VIDEO_FRAME_EX					0x0811				//��Ƶ֡���ݴ�ʱ���
#define	NPC_D_DPS_MSGID_MEDIA_E8_AUDIO_FRAME_EX					0x0812				//��Ƶʱ���ݴ�ʱ���


//-------------------------------------------------------------------------------
//�¼���Ϣͷ����
typedef struct _NPC_S_DPS_MSG_HEAD
{
	NPC_INT											iMsgFuncId;						//��Ϣ����ID���μ�NPC_D_DPS_MSGID_*����
	NPC_BYTE										ucMsgType;						//��Ϣ���ͣ��μ�NPC_D_DPS_MSG_TYPE_*����
	NPC_BYTE										ucResult;						//�����0���ɹ�������ʧ�ܣ��μ�NPC_D_MON_CSD_DPS_ERROR_CODE_*����
	NPC_BYTE										ucReserve[2];					//����
	NPC_DWORD										dwTransId;						//����ID������Ӧ����Ϣԭ������������Ϣ�е�����ID
	NPC_INT											iMsgBodyLen;					//��Ϣ���峤��

} NPC_S_DPS_MSG_HEAD, *PNPC_S_DPS_MSG_HEAD;


//-------------------------------------------------------------------------------
//�¼���Ϣ�嶨��

//��ý����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_OPEN_MEDIA_STREAM
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iStreamNo;					//�����ţ�0����������1��������

	NPC_BOOL										o_bVideoFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	NPC_BOOL										o_bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ

	NPC_INT											o_iVideoCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	NPC_INT											o_iVideoFrameRate;				//��Ƶ֡��
	NPC_INT											o_iVideoBitRate;				//��Ƶ���ʣ�kbps��
	NPC_USHORT										o_usVideoWidth;					//��Ƶ���
	NPC_USHORT										o_usVideoHeight;				//��Ƶ�߶�

	NPC_INT											o_iAudioCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	NPC_INT											o_iAudioBitRate;				//��Ƶ���ʣ�kbps������64
	NPC_INT											o_iAudioSampleRate;				//��Ƶ�����ʣ���8000
	NPC_INT											o_iAudioChNum;					//��Ƶ����������1

} NPC_S_DPS_MSG_BODY_EVENT_E2_OPEN_MEDIA_STREAM, *PNPC_S_DPS_MSG_BODY_EVENT_E2_OPEN_MEDIA_STREAM;

//�ر�ý����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iStreamNo;					//�����ţ�0����������1��������

} NPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM, *PNPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM;

//��̨����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_PTZ_CTRL
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iPtzCmd;						//PTZ����μ�NPC_D_MON_CSD_PTZ_CMD_*����
	NPC_DWORD										i_dwPtzData;					//PTZ����
	NPC_DWORD										i_dwPtzExtParam1;				//PTZ��չ����1
	NPC_DWORD										i_dwPtzExtParam2;				//PTZ��չ����2

} NPC_S_DPS_MSG_BODY_EVENT_E2_PTZ_CTRL, *PNPC_S_DPS_MSG_BODY_EVENT_E2_PTZ_CTRL;

//����ǿ�Ʒ���I֡
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FORCE_I_FRAME
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iStreamNo;					//�����ţ�0����������1��������

} NPC_S_DPS_MSG_BODY_EVENT_E2_FORCE_I_FRAME, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FORCE_I_FRAME;

//�޸ı������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_MODIFY_CODEC
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iStreamNo;					//�����ţ�0����������1��������

	NPC_BOOL										i_bVideoFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
	NPC_BOOL										i_bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ

	NPC_INT											i_iVideoCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	NPC_INT											i_iVideoFrameRate;				//��Ƶ֡��
	NPC_INT											i_iVideoBitRate;				//��Ƶ���ʣ�kbps��
	NPC_USHORT										i_usVideoWidth;					//��Ƶ���
	NPC_USHORT										i_usVideoHeight;				//��Ƶ�߶�

	NPC_INT											i_iAudioCodecId;				//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
	NPC_INT											i_iAudioBitRate;				//��Ƶ���ʣ�kbps������64
	NPC_INT											i_iAudioSampleRate;				//��Ƶ�����ʣ���8000
	NPC_INT											i_iAudioChNum;					//��Ƶ����������1

} NPC_S_DPS_MSG_BODY_EVENT_E2_MODIFY_CODEC, *PNPC_S_DPS_MSG_BODY_EVENT_E2_MODIFY_CODEC;

//��ȡ��Ƶ�����ȼ������б�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_CAP
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������

	//��Ƶ�����ȼ��б�
	NPC_INT											o_iLevelNum;					//�ȼ���
	struct _LevelTable{
		NPC_CHAR									sLevelName[16];					//�ȼ�����
		NPC_INT										iLevelValue;					//�ȼ�ֵ��������ڵ���0
		NPC_USHORT									usWidth;						//ͼ���
		NPC_USHORT									usHeight;						//ͼ���
		NPC_USHORT									usFrameRate;					//֡��
		NPC_USHORT									usBitRate;						//���ʣ���λ��kbps
	} o_tLevelTable[8];

} NPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_CAP, *PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_CAP;

//��ȡ��Ƶ�����ȼ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_LEVEL
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������

	NPC_INT											o_iLevelValue;					//�ȼ�ֵ�����Ϊ-1��ʾȱʡ���ã���û�����õȼ�

} NPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_LEVEL, *PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_LEVEL;

//������Ƶ�����ȼ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_SET_VIDEO_QUALITY_LEVEL
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������
	NPC_INT											i_iLevelValue;					//�ȼ�ֵ�����ڵ���0������Ϊ-1��-1��ʾȱʡ����

} NPC_S_DPS_MSG_BODY_EVENT_E2_SET_VIDEO_QUALITY_LEVEL, *PNPC_S_DPS_MSG_BODY_EVENT_E2_SET_VIDEO_QUALITY_LEVEL;


//-------------------------------------------------------------------------------
//��ѯ�ļ���¼���ͼƬ�ļ�����Ӧ����Ϣ�иýṹ��֮��ΪNPC_S_MON_MPS_FILE_INFO����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QUERY
{
	NPC_INT											i_iChNo;						//ͨ���ţ����Ϊ-1��ʾ��ѯ����ͨ�����ļ�
	NPC_INT											i_iFileType;					//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
	NPC_INT											i_iCreateMode;					//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_INT											i_iAlarmEvent;					//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_S_TD_DATE_TIME								i_tStartTime;					//��ʼʱ�䣬���ļ�����ʱ���¼��Ŀ�ʼʱ��Ϊ��ѯʱ��
	NPC_S_TD_DATE_TIME								i_tEndTime;						//����ʱ��

	NPC_INT											o_iFileNum;						//�ļ���

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QUERY, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QUERY;

//��չ��ѯ�ļ���¼���ͼƬ�ļ�����Ӧ����Ϣ�иýṹ��֮��ΪNPC_S_MON_MPS_FILE_HEAD_INFO����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_NSP_FILE_QUERY
{
	NPC_INT											i_iChNo;						//ͨ���ţ����Ϊ-1��ʾ��ѯ����ͨ�����ļ�
	NPC_INT											i_iStreamNo;					//�����ţ����Ϊ-1��ʾ��ѯ�����������ļ�
	NPC_INT											i_iFileType;					//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
	NPC_INT											i_iCreateMode;					//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_BYTE										i_ucAlarmEventTable[16];		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_INT											i_iAlarmEventNum;				//�����¼���
	NPC_S_TD_DATE_TIME								i_tStartTime;					//��ʼʱ�䣬���ļ�����ʱ���¼��Ŀ�ʼʱ��Ϊ��ѯʱ��
	NPC_S_TD_DATE_TIME								i_tEndTime;						//����ʱ��

	NPC_INT											o_iFileNum;						//�ļ���

} NPC_S_DPS_MSG_BODY_EVENT_E2_NSP_FILE_QUERY, *PNPC_S_DPS_MSG_BODY_EVENT_E2_NSP_FILE_QUERY;

//��ѯ¼���ļ���ʱ�䷶Χ��Ӧ����Ϣ�иýṹ��֮��ΪNPC_S_MON_MPS_FILE_RANGE_INFO����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RANGE_QUERY
{
	NPC_INT											i_iChNo;						//ͨ���ţ����Ϊ-1��ʾ��ѯ����ͨ�����ļ�
	NPC_INT											i_iStreamNo;					//�����ţ����Ϊ-1��ʾ��ѯ�����������ļ�
	NPC_INT											i_iCreateMode;					//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_BYTE										i_ucAlarmEventTable[16];		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_INT											i_iAlarmEventNum;				//�����¼���
	NPC_S_TD_DATE_TIME								i_tStartTime;					//��ʼʱ�䣬���ļ�����ʱ���¼��Ŀ�ʼʱ��Ϊ��ѯʱ��
	NPC_S_TD_DATE_TIME								i_tEndTime;						//����ʱ��
	
	NPC_INT											o_iFileNum;						//�ļ���
	
} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RANGE_QUERY, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RANGE_QUERY;

//-------------------------------------------------------------------------------
//���ļ�������ͬʱ��ͬһ���ļ��򿪶�εĿ��ܣ�����ͬ�Ŀͻ��˶�ͬһ���ļ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN
{
	NPC_CHAR										i_sFileFlag[NPC_D_MON_CSD_MAX_FILE_FLAG_LEN];		//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
	NPC_DWORD										i_dwStartOffsetDataPos;			//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ�ã���ͣʹ�ã�
	NPC_DWORD										i_dwStartOffsetTimePos;			//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
																					//ͼƬ�ļ��ò�����Ч

	NPC_DWORD										o_dwFileReadId;					//�����ļ���ȡID
	NPC_S_MON_MPS_FILE_INFO							o_tFileInfo;					//�ļ���Ϣ

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN;

//���ļ�������ͬʱ��ͬһ���ļ��򿪶�εĿ��ܣ�����ͬ�Ŀͻ��˶�ͬһ���ļ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN_BY_TIME
{
	NPC_INT											i_iChNo;						//ͨ���ţ����Ϊ-1��ʾ��ѯ����ͨ�����ļ�
	NPC_INT											i_iStreamNo;					//�����ţ����Ϊ-1��ʾ��ѯ�����������ļ�
	NPC_INT											i_iFileType;					//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
	NPC_INT											i_iCreateMode;					//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
	NPC_BYTE										i_ucAlarmEventTable[16];		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
	NPC_INT											i_iAlarmEventNum;				//�����¼���
	NPC_S_TD_DATE_TIME								i_tStartTime;					//��ʼʱ�䣬���ļ�����ʱ���¼��Ŀ�ʼʱ��Ϊ��ѯʱ��
	NPC_S_TD_DATE_TIME								i_tEndTime;						//����ʱ��,ͼƬ�ļ��ò�����Ч
	
	NPC_DWORD										o_dwFileReadId;					//�����ļ���ȡID
	NPC_S_MON_MPS_FILE_INFO							o_tFileInfo;					//�ļ���Ϣ
	
} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN_BY_TIME, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN_BY_TIME;

//�ر��ļ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_CLOSE
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_CLOSE, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_CLOSE;

//��ȡ�ļ�����ȡ��һ�����ݣ���Ӧ����Ϣ��ʵ�������ڸýṹ��֮��Ӧ����Ϣ�У����󲿷�Ӧԭ������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID
	NPC_DWORD										i_dwRequId;						//����ID
	NPC_BYTE										i_ucReqDataType;				//�����ȡ���������ͣ�0��������ݣ�1����Ƶ��2����Ƶ��3���ļ����ݣ���ͼƬ�ļ�����ֵΪ100��ʾֹͣ��������
	NPC_BYTE										i_ucReqDataSize;				//�������ݴ�С��������ݻ���Ƶ����Ƶ�ò���ָ������ͼƬ����ָ����K�ֽ�
																					//���Ϊ0����ֹͣ��һֱ��ȡ���ͣ�ֱ����ȡ�ļ����
																					//��ȡ�������ʱ�������ļ��е�����˳���ȡ�������ȡΪ��Ƶ֡��������Ƶ֡���������Ƶ���ݣ�������Ƶ����Ƶ���ݵ������ݰ���С���10K��һ������Ķ�ȡ����������Ƶ֡Ϊ׼��

	NPC_BYTE										o_ucRetDataType;				//�����������ͣ�1����Ƶ��2����Ƶ��3���ļ����ݣ�ͼƬ���ݣ�
	NPC_BYTE										o_ucFrameType:4;				//֡���ͣ���Ƶ��Ч���μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
	NPC_BYTE										o_ucIfDataEnd:2;				//�Ƿ������0��δ������1���������������2���ļ�����
	NPC_BYTE										o_ucReserve1:2;					//����1
	NPC_BYTE										o_ucMediaCodecId;				//ý������ʽ���μ�NPC_D_MON_CSD_CODEC_ID_*����
	NPC_BYTE										o_ucVideoFrameRate;				//��Ƶ֡�ʣ�Ϊ��Ƶ֡ʱ��Ч��
	NPC_BYTE										o_ucReserve2[2];				//����2
	NPC_DWORD										o_dwOffsetDataPos;				//��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
	NPC_DWORD										o_dwOffsetTimePos;				//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬�ļ����ݸò�����Ч
	NPC_S_TD_DATE_TIME								o_tDataTime;					//����ʱ�䣬Ϊ����ʱ�䣬��ƵΪ֡��ʱ�䣬��ƵΪ���ݵĿ�ʼʱ�䣬�ļ����ݸò�����Ч
	NPC_DWORD										o_dwDataLen;					//���ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ;


//��λ�ļ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID
	NPC_DWORD										i_dwOffsetTimePos;				//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ڵ���0��С���ļ���ʱ��

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK;

//��λ�ļ�(��ʱ�䷽ʽ)
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK_BY_TIME
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID
	NPC_S_TD_DATE_TIME								i_tOffsetTimePos;				//��ȡʱ��λ�ã���λ�룩

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK_BY_TIME, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK_BY_TIME;

//��ѯ��Ƶ����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QVIDEO
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID

	NPC_INT											o_iVideoFrameRate;				//��Ƶ֡��
	NPC_INT											o_iVideoGop;					//��ƵGOPֵ

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QVIDEO, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QVIDEO;

//����I֡���ݣ�������ƵP֡����Ƶ��ֻ����ƵI֡��
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_ONLY_IFRAME
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID
	NPC_INT											i_iDiscardIFrame;				//����I֡����0������I֡��1������1��I֡�������1��I֡���䣩��2������2��I֡���������

	NPC_INT											o_iVideoFrameRate;				//��Ƶ֡��
	NPC_INT											o_iVideoGop;					//��ƵGOPֵ

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_ONLY_IFRAME, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_ONLY_IFRAME;

//����ָ�ȫ֡����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RECOVER_ALLFRAME
{
	NPC_DWORD										i_dwFileReadId;					//�ļ���ȡID

} NPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RECOVER_ALLFRAME, *PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RECOVER_ALLFRAME;


//-------------------------------------------------------------------------------
//��ʼ�����Խ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_START
{
	NPC_INT											i_iTalkChNo;					//�Խ�ͨ����

	NPC_INT											o_iDevAudioCodecId;				//�豸����Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_AUDIO_*����
	NPC_INT											o_iDevAudioBitRate;				//�豸����Ƶ����
	NPC_INT											o_iDevAudioSampleRate;			//�豸����Ƶ������
	NPC_INT											o_iDevAudioChNum;				//�豸����Ƶ������

} NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_START, *PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_START;

//ֹͣ�����Խ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP
{
	NPC_INT											i_iTalkChNo;					//�Խ�ͨ����

} NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP, *PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP;


//-------------------------------------------------------------------------------
//�澯��Ϣ
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_ALARM_INFO
{
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iAlarmEvent;					//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
	NPC_INT											i_iAlarmState;					//����״̬��0������������1��������ʼ
	NPC_CHAR										i_sAlarmInfo[128];				//������Ϣ

} NPC_S_DPS_MSG_BODY_EVENT_E2_ALARM_INFO, *PNPC_S_DPS_MSG_BODY_EVENT_E2_ALARM_INFO;

//�澯��Ϣ����չ��
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E2_EX_ALARM_INFO
{
	NPC_CHAR										i_sAlarmId[32];					//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
	NPC_INT											i_iChNo;						//ͨ����
	NPC_INT											i_iAlarmEvent;					//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
	NPC_CHAR										i_sAlarmInfo[128];				//������Ϣ

} NPC_S_DPS_MSG_BODY_EVENT_E2_EX_ALARM_INFO, *PNPC_S_DPS_MSG_BODY_EVENT_E2_EX_ALARM_INFO;



//-------------------------------------------------------------------------------
//�޸��û�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_USER_PWD
{
	NPC_CHAR										i_sUserName[32];				//�û���
	NPC_CHAR										i_sOldPwd[32];					//ԭ���루���ģ�
	NPC_CHAR										i_sNewPwd[32];					//�����루���ģ�

} NPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_USER_PWD, *PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_USER_PWD;

//��ȡ���ò������ýṹ��֮��Ϊ���ò������ݣ����ò�������ο�NPC_PVM_OrderCfgDef.h�ļ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG
{
	NPC_INT											i_iCfgFuncId;					//���ù���ID���μ�NPC_D_PVM_CFG_FUNCID_*����

	NPC_INT											io_iCfgDataLen;					//�������ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG, *PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG;

//�������ò������ýṹ��֮��Ϊ���ò������ݣ����ò�������ο�NPC_PVM_OrderCfgDef.h�ļ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG
{
	NPC_INT											i_iCfgFuncId;					//���ù���ID���μ�NPC_D_PVM_CFG_FUNCID_*����
	NPC_INT											i_iCfgDataLen;					//�������ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG, *PNPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG;

//��ȡȱʡ���ò������ýṹ��֮��Ϊ���ò������ݣ����ò�������ο�NPC_PVM_OrderCfgDef.h�ļ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG
{
	NPC_INT											i_iCfgFuncId;					//���ù���ID���μ�NPC_D_PVM_CFG_FUNCID_*����
	NPC_INT											i_iChNo;						//ͨ����

	NPC_INT											io_iCfgDataLen;					//�������ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG, *PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG;

//�������ã��ýṹ��֮��ΪXML��ʽ�����ñ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG
{
	NPC_INT											i_iCfgDataLen;					//�������ݳ��ȣ���XML���ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG, *PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG;

//�������ã��ýṹ��֮��ΪXML��ʽ�����ñ�����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG
{
	NPC_INT											o_iCfgDataLen;					//�������ݳ��ȣ���XML���ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG, *PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG;


//-------------------------------------------------------------------------------
//��ѯ������Ϣ��Ӧ����Ϣ�иýṹ��֮��Ϊ������Ϣ����
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO
{
	NPC_INT											o_iNetCardNum;					//������

} NPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO, *PNPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO;

//������Ϣ
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_NET_CARD_INFO
{
	NPC_CHAR										sNetCardName[32];				//��������
	NPC_BYTE										sMac[6];						//MAC��ַ
	NPC_BOOL										bIfOpenDhcp;					//�Ƿ��DHCP�����ΪTRUE�����������������Ч
	NPC_CHAR										sIpaddr[16];					//IP��ַ
	NPC_CHAR										sSubmask[16];					//��������
	NPC_CHAR										sGateway[16];					//���ص�ַ

} NPC_S_DPS_MSG_BODY_EVENT_E3_NET_CARD_INFO, *PNPC_S_DPS_MSG_BODY_EVENT_E3_NET_CARD_INFO;

//�޸������ַ
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_NET_ADDR
{
	NPC_CHAR										i_sNetCardName[32];				//��������
	NPC_BYTE										i_sMac[6];						//MAC��ַ
	NPC_BOOL										i_bIfOpenDhcp;					//�Ƿ��DHCP�����ΪTRUE�����������������Ч
	NPC_CHAR										i_sIpaddr[16];					//IP��ַ
	NPC_CHAR										i_sSubmask[16];					//��������
	NPC_CHAR										i_sGateway[16];					//���ص�ַ

} NPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_NET_ADDR, *PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_NET_ADDR;


//------------------------------------------------------------------------------
//�򿪴���
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_COM_OPEN
{
	NPC_DWORD										i_dwClientConnId;				//�ͻ�������ID
	NPC_INT											i_iComType;						//�������ͣ�0��RS232���ڣ�1��RS485����
	NPC_INT											i_iPortNo;						//�˿ں�
	NPC_INT											i_iBaudRate;					//�����ʣ���4800��14400��28800��36600
	NPC_INT											i_iDataBit;						//����λ����8λ
	NPC_INT											i_iStopBit;						//ֹͣλ����1
	NPC_INT											i_iCheckBit;					//��żУ��λ

} NPC_S_DPS_MSG_BODY_EVENT_E3_COM_OPEN, *PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_OPEN;

//�رմ���
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_COM_CLOSE
{
	NPC_DWORD										i_dwClientConnId;				//�ͻ�������ID
	NPC_BOOL										i_bIfCloseAllCom;				//�Ƿ�ر���ͻ�������ID��ص����д���
	NPC_INT											i_iComType;						//�������ͣ�0��RS232���ڣ�1��RS485����
	NPC_INT											i_iPortNo;						//�˿ں�

} NPC_S_DPS_MSG_BODY_EVENT_E3_COM_CLOSE, *PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_CLOSE;

//���ʹ�������(�ͻ��˷��͸��豸��)���ýṹ��֮��Ϊ��������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_COM_SEND_DATA
{
	NPC_DWORD										i_dwClientConnId;				//�ͻ�������ID
	NPC_INT											i_iComType;						//�������ͣ�0��RS232���ڣ�1��RS485����
	NPC_INT											i_iPortNo;						//�˿ں�
	NPC_INT											i_iDataLen;						//���ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_COM_SEND_DATA, *PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_SEND_DATA;

//�豸��������(�豸�˷��͸��ͻ���)���ýṹ��֮��Ϊ��������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_COM_SUBS_DATA
{
	NPC_DWORD										i_dwClientConnId;				//�ͻ�������ID
	NPC_INT											i_iComType;						//�������ͣ�0��RS232���ڣ�1��RS485����
	NPC_INT											i_iPortNo;						//�˿ں�
	NPC_INT											i_iDataLen;						//���ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E3_COM_SUBS_DATA, *PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_SUBS_DATA;


//------------------------------------------------------------------------------
//�����û�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_ADD_USER
{
	NPC_CHAR										i_sUserName[32];				//�û���
	NPC_CHAR										i_sUserPwd[32];					//�û�����
	NPC_DWORD										i_dwGlobalPop;					//ȫ��Ȩ�ޣ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_INT											i_iChNum;						//ͨ�������ýṹ��֮��Ϊͨ��Ȩ�ޱ�ÿ4�ֽ�Ϊһ��ͨ����Ȩ�ޣ�4�ֽڵ�˳���Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_DWORD										i_dwChPopTable[64];				//ͨ��Ȩ�ޱ�����������Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����

} NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_ADD_USER, *PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_ADD_USER;

//ɾ���û�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_DEL_USER
{
	NPC_CHAR										i_sUserName[32];				//�û���

} NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_DEL_USER, *PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_DEL_USER;

//��ȡ�û�Ȩ���б�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_GET_USER_POP
{
	NPC_CHAR										i_sUserName[32];				//�û���

	NPC_DWORD										o_dwGlobalPop;					//ȫ��Ȩ�ޣ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_INT											o_iChNum;						//ͨ�������ýṹ��֮��Ϊͨ��Ȩ�ޱ�ÿ4�ֽ�Ϊһ��ͨ����Ȩ�ޣ�4�ֽڵ�˳���Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_DWORD										o_dwChPopTable[64];				//ͨ��Ȩ�ޱ�����������Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����

} NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_GET_USER_POP, *PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_GET_USER_POP;

//�����û�Ȩ���б�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_SET_USER_POP
{
	NPC_CHAR										i_sUserName[32];				//�û���
	NPC_DWORD										i_dwGlobalPop;					//ȫ��Ȩ�ޣ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_INT											i_iChNum;						//ͨ�������ýṹ��֮��Ϊͨ��Ȩ�ޱ�ÿ4�ֽ�Ϊһ��ͨ����Ȩ�ޣ�4�ֽڵ�˳���Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����
	NPC_DWORD										i_dwChPopTable[64];				//ͨ��Ȩ�ޱ�����������Ϊͨ���ţ�λֵ�ο�NPC_D_DPS_POP_*����

} NPC_S_DPS_MSG_BODY_EVENT_E3_UNS_SET_USER_POP, *PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_SET_USER_POP;


//-------------------------------------------------------------------------------
//���ƹ���
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM
{
	NPC_INT											i_iCusFuncId;					//���ƹ���ID���μ���Ӧ�ļ�����
	NPC_INT											i_iBodyLen;						//���峤��

} NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM, *PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM;


//-------------------------------------------------------------------------------
//��ѯ������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY
{
	NPC_INT											i_iRequVerNo;					//����汾��

	NPC_INT											o_iAbilityDataLen;				//�������ݳ���,�ýṹ��֮��Ϊ��������,�������ݲμ�NPC_PVM_OrderCfgDef.h�ļ��Ķ���

} NPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY, *PNPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY;


//------------------------------------------------------------------------------
//��ѯ�豸�汾��Ϣ
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_DEV_VER_INFO
{
	NPC_USHORT										o_usModuleType[4];				//ģ������,0:δ֪����,1:UI,2:SYS,3:UI&SYS
	NPC_UINT										o_uiModuleVerNo[4];				//ģ��汾��,��˳���Ӧģ������,��ʽΪ:x.x.x.x,ÿ�ֽ�Ϊһ����

} NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_DEV_VER_INFO, *PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_DEV_VER_INFO;

//��������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_REQU_UPGRADE
{
	NPC_USHORT										i_usModuleType;					//ģ������,0:δ֪����,1:UI,2:SYS,3:UI&SYS
	NPC_USHORT										i_usCheckSum;					//�ļ������
	NPC_INT											i_iFileSize;					//�����ļ���С(�ֽ�)

	NPC_UINT										o_uiUpgradeId;					//����ID

} NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_REQU_UPGRADE, *PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_REQU_UPGRADE;

//��ѯ��������
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_PROGRESS
{
	NPC_UINT										i_uiUpgradeId;					//����ID

	NPC_INT											o_iUpgProgress;					//��������,ֵΪ0~100,ָдFLASH�Ľ���

} NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_PROGRESS, *PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_PROGRESS;

//��ѯ����λ��(����ͨ��)
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_TRANS_POS
{
	NPC_UINT										i_uiUpgradeId;					//����ID

	NPC_INT											o_iTransPos;					//����λ�ã�������ļ�ͷ��ƫ��λ�ã���0��ʼ����ֵ�൱�ڽ��յ����ļ����ݳ���

} NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_TRANS_POS, *PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_TRANS_POS;

//�������ݰ�
typedef struct _NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_UPGRADE_DATA
{
	NPC_UINT										i_uiUpgradeId;					//����ID
	NPC_INT											i_iUpgDataLen;					//�������ݳ���,�ýṹ��֮��Ϊ��������

} NPC_S_DPS_MSG_BODY_EVENT_E7_DUP_UPGRADE_DATA, *PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_UPGRADE_DATA;


//-------------------------------------------------------------------------------
//��Ƶ֡����
typedef struct _NPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������
	NPC_USHORT										i_usFrameType;					//֡���ͣ��μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
	NPC_BYTE										i_ucReserve[2];					//����

} NPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME, *PNPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME;

//��Ƶ֡����
typedef struct _NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������

} NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME, *PNPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME;


//��Ƶ֡����
typedef struct _NPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME_EX
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������
	NPC_USHORT										i_usFrameType;					//֡���ͣ��μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
	NPC_BYTE										i_ucReserve[2];					//����
	NPC_DWORD										i_dwTimestamp;					//ʱ���
	NPC_BYTE										i_ucReserve2[16];				//����2
	
} NPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME_EX, *PNPC_S_DPS_MSG_BODY_MEDIA_E8_VIDEO_FRAME_EX;

//��Ƶ֡����
typedef struct _NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME_EX
{
	NPC_USHORT										i_usChNo;						//ͨ����
	NPC_USHORT										i_usStreamNo;					//�����ţ�0����������1��������
	NPC_DWORD										i_dwTimestamp;					//ʱ���
	NPC_BYTE										i_ucReserve[16];				//����	
} NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME_EX, *PNPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME_EX;

#endif

