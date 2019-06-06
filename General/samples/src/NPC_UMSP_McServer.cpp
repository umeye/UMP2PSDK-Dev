/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_UMSP_McServer.cpp
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-10
 * Description   :  UMSP����������ģ��
 *----------------------------------------------------------------------------*/

#include "NPC_UMSP_McServer.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")
#endif

#ifndef NPC_D_DPS_ZERO_CHANNEL_VALUE
#define NPC_D_DPS_ZERO_CHANNEL_VALUE	10000
#endif

//�ص���������
NPC_VOID	CALLBACK  NPC_F_UMSP_FILECAM_SDK_RealDataCallBack(
	IN		NPC_INT									in_iMediaType,				//ý������
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý������
	IN		NPC_INT									in_iMediaDataLen,			//ý�����ݳ���
	IN		NPC_DWORD								in_dwUserData				//�û�����
	)
{
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	PNPC_S_UMSP_MCSRV_DATA							pMcSrvData;
	NPC_INT											iFrameType;

	//INIT AREA
	{
		pCameraData = (PNPC_S_UMSP_CAMERA_DATA)in_dwUserData;
		if ( pCameraData == NULL )
			return;

		if ( !pCameraData->bIfUsed )
			return;

		pMcSrvData = (PNPC_S_UMSP_MCSRV_DATA)(pCameraData->pMcSrvData);
		if ( pMcSrvData == NULL )
			return;

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock			//���������
			);
	}

	//CODE AREA
	{
		if ( in_iMediaType == 0 )
		{
			//���֡���ͣ�����֡���ͣ�0��δ��⵽��1��I֡��2��P֡
			switch ( NPC_F_UMSP_MC_CheckFrameType(
				in_pMediaDataBuf,			//֡���ݻ�����
				in_iMediaDataLen			//֡���ݳ���
				) )
			{
			case 1:
				iFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_I;
				break;
			case 2:
				iFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P;
				break;
			case 0:
			default:
				iFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P;
				break;
			}
			
			//������
			if ( pCameraData->bMainStreamOpenFlag )
			{
				//������Ƶ��
				NPC_F_DPS_InputVideoStream(
					pMcSrvData->hUmspProSrv,			//�豸Э�����������
					pCameraData->iChNo,					//ͨ����
					0,									//�����ţ�0����������1��������
					iFrameType,							//֡���ͣ��μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
					in_pMediaDataBuf,					//ý�����ݻ�����
					in_iMediaDataLen					//ý�����ݳ���
					);
			}

			//������
			if ( pCameraData->bSubStreamOpenFlag )
			{
				//������Ƶ��
				NPC_F_DPS_InputVideoStream(
					pMcSrvData->hUmspProSrv,			//�豸Э�����������
					pCameraData->iChNo,					//ͨ����
					1,									//�����ţ�0����������1��������
					iFrameType,							//֡���ͣ��μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
					in_pMediaDataBuf,					//ý�����ݻ�����
					in_iMediaDataLen					//ý�����ݳ���
					);
			}

			//��������
			if ( pCameraData->bThirdStreamOpenFlag)
			{
				//������Ƶ��
				NPC_F_DPS_InputVideoStream(
					pMcSrvData->hUmspProSrv,			//�豸Э�����������
					pCameraData->iChNo,					//ͨ����
					2,									//�����ţ�0����������1��������
					iFrameType,							//֡���ͣ��μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
					in_pMediaDataBuf,					//ý�����ݻ�����
					in_iMediaDataLen					//ý�����ݳ���
					);
			}

			pCameraData->dwRecvFrameNum++;

			if ( time(NULL) - pCameraData->tPrecShowCacheTime >= 1 )
			{
				NPC_INT iMainCacheVideoFrameNum, iSubCacheVideoFrameNum;

				pCameraData->tPrecShowCacheTime = time(NULL);
				iMainCacheVideoFrameNum = iSubCacheVideoFrameNum = 0;

				if ( pCameraData->bMainStreamOpenFlag )
				{
					//��ѯͨ��������Ƶ֡��
					iMainCacheVideoFrameNum = NPC_F_DPS_QueryCacheVideoFrameNum(
						pMcSrvData->hUmspProSrv,		//�豸Э�����������
						pCameraData->iChNo,				//ͨ����
						0								//�����ţ�0����������1��������
						);
				}

				if ( pCameraData->bSubStreamOpenFlag )
				{
					//��ѯͨ��������Ƶ֡��
					iSubCacheVideoFrameNum = NPC_F_DPS_QueryCacheVideoFrameNum(
						pMcSrvData->hUmspProSrv,		//�豸Э�����������
						pCameraData->iChNo,				//ͨ����
						1								//�����ţ�0����������1��������
						);
				}

				//д��־
				NPC_CHAR sTempLogBuf[256];
				sprintf(sTempLogBuf, "[UMSP]  Cache video frame num: main: %d, sub: %d.", 
					iMainCacheVideoFrameNum, iSubCacheVideoFrameNum);
				NPC_F_LOG_SR_WriteLog(sTempLogBuf);
			}
		}
		else
		{
			//��Ƶ
			if ( pCameraData->bMainStreamOpenFlag )
			{
				//������Ƶ��
				NPC_F_DPS_InputAudioStream(
					pMcSrvData->hUmspProSrv,			//�豸Э�����������
					pCameraData->iChNo,					//ͨ����
					0,									//�����ţ�0����������1��������
					in_pMediaDataBuf,					//ý�����ݻ�����
					in_iMediaDataLen					//ý�����ݳ���
					);
			}

			if ( pCameraData->bSubStreamOpenFlag )
			{
				//������Ƶ��
				NPC_F_DPS_InputAudioStream(
					pMcSrvData->hUmspProSrv,			//�豸Э�����������
					pCameraData->iChNo,					//ͨ����
					1,									//�����ţ�0����������1��������
					in_pMediaDataBuf,					//ý�����ݻ�����
					in_iMediaDataLen					//ý�����ݳ���
					);
			}
		}

		//д¼���ļ�����
		if ( pCameraData->hNavFile )
		{
			NPC_CHAR cFrameType;
			NPC_DWORD dwTimestamp;
			NPC_DWORD dwRecOffsetTime;
			NPC_BOOL bIfNeedWriteData;

			bIfNeedWriteData = FALSE;
			cFrameType = 0;

			if ( in_iMediaType == 0 )
			{
				if ( !pCameraData->bIfWriteIFrame )
				{
					if ( iFrameType == NPC_D_MON_CSD_VIDEO_FRAME_TYPE_I )
					{
						bIfNeedWriteData = TRUE;
						pCameraData->bIfWriteIFrame = TRUE;
					}
				}
				else
				{
					bIfNeedWriteData = TRUE;
				}

				switch (iFrameType)
				{
				case NPC_D_MON_CSD_VIDEO_FRAME_TYPE_I:
					cFrameType = 'I';
					break;
				case NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P:
				default:
					cFrameType = 'P';
					break;
				}
			}
			else
			{
				bIfNeedWriteData = pCameraData->bIfWriteIFrame;
			}

			if ( bIfNeedWriteData )
			{
				dwRecOffsetTime = pCameraData->dwRecvFrameNum / pCameraData->iFrameRate;
				dwTimestamp = dwRecOffsetTime * 1000 + 
					(pCameraData->dwRecvFrameNum % pCameraData->iFrameRate) * 
					(1000 / pCameraData->iFrameRate);

				//���ļ����ý�����ݣ���Ƶ����Ƶ��
				if ( !NPC_F_NAV_AddMediaData(
					pCameraData->hNavFile,		//NAV�ļ����
					in_iMediaType,				//ý�����ͣ�0����Ƶ��1����Ƶ
					cFrameType,					//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
					dwTimestamp,				//ʱ���
					dwRecOffsetTime,			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
					in_pMediaDataBuf,			//ý�����ݻ�������ԭʼ�������ݣ�
					in_iMediaDataLen			//ý�����ݳ���
					) )
				{
					//д��־
					NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_FILECAM_SDK_RealDataCallBack NPC_F_NAV_AddMediaData fail.");
				}
			}
		}
	}

	//CLEAR AREA
	{
		//����
		NPC_F_THREAD_Mutex_Unlock(
			pCameraData->hWorkLock				//���������
			);
	}
}

//Э���¼��ص���������
NPC_VOID	NPC_F_UMSP_DPS_ProEventCallback(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD+��������
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_UMSP_MCSRV_DATA							pMcSrvData;
	PNPC_S_DPS_MSG_HEAD								pMsgHead;

	pMcSrvData = (PNPC_S_UMSP_MCSRV_DATA)in_pUserData;
	if ( pMcSrvData == NULL )
		return ;

	pMsgHead = (PNPC_S_DPS_MSG_HEAD)in_pMsgDataBuf;

	switch ( pMsgHead->iMsgFuncId )
	{
	case NPC_D_DPS_MSGID_EVENT_E2_OPEN_MEDIA_STREAM:		//��ý����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_OPEN_MEDIA_STREAM(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_CLOSE_MEDIA_STREAM:		//�ر�ý����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_CLOSE_MEDIA_STREAM(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_PTZ_CTRL:					//��̨����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_PTZ_CTRL(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FORCE_I_FRAME:			//����ǿ�Ʒ���I֡
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FORCE_I_FRAME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_GET_VIDEO_QUALITY_CAP:	//��ȡ��Ƶ�����ȼ������б�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_CAP(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_GET_VIDEO_QUALITY_LEVEL:	//��ȡ��Ƶ�����ȼ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_LEVEL(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_SET_VIDEO_QUALITY_LEVEL:	//������Ƶ�����ȼ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_SET_VIDEO_QUALITY_LEVEL(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_QUERY:				//��ѯ�ļ���¼���ͼƬ�ļ���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QUERY(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_NSP_FILE_QUERY:			//��չ��ѯ�ļ���¼���ͼƬ�ļ���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_RANGE_QUERY:
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RANGE_QUERY(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_OPEN:				//���ļ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_OPEN_BY_TIME:
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN_BY_TIME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_CLOSE:				//�ر��ļ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_CLOSE(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FILE_READ:				//��ȡ�ļ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FILE_SEEK:				//��λ�ļ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_FILE_SEEK_BY_TIME:		//��λ�ļ�,��ʱ�䷽ʽ
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK_BY_TIME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FILE_QVIDEO:				//��ѯ��Ƶ����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QVIDEO(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FILE_ONLY_IFRAME:			//����I֡����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_ONLY_IFRAME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_FILE_RECOVER_ALLFRAME:	//����ָ�ȫ֡����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RECOVER_ALLFRAME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E2_TALK_START:				//��ʼ�����Խ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E2_TALK_STOP:				//ֹͣ�����Խ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_STOP(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E3_MODIFY_USER_PWD:			//�޸��û�����
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_USER_PWD(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_GET_CONFIG:				//��ȡ���ò���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_CONFIG(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_SET_CONFIG:				//�������ò���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_SET_CONFIG(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_GET_DEF_CONFIG:			//��ȡȱʡ���ò���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_DEF_CONFIG(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_IEC_IMP_CONFIG:			//��������
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_IMP_CONFIG(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_IEC_EXP_CONFIG:			//��������
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_EXP_CONFIG(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E3_QUERY_NET_INFO:			//��ѯ������Ϣ
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_QUERY_NET_INFO(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_MODIFY_NET_ADDR:			//�޸������ַ
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_NET_ADDR(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E3_COM_OPEN:					//�򿪴���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_OPEN(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_COM_CLOSE:				//�رմ���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_CLOSE(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_COM_SEND_DATA:			//��������(�ͻ��˷��͸��豸��)
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SEND_DATA(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_COM_SUBS_DATA:			//�豸��������(�豸�˷��͸��ͻ���)(��Ӧ��)
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SUBS_DATA(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E3_UNS_ADD_USER:				//�����û�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_ADD_USER(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_UNS_DEL_USER:				//ɾ���û�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_DEL_USER(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_UNS_GET_USER_POP:			//��ȡ�û�Ȩ���б�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_GET_USER_POP(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E3_UNS_SET_USER_POP:			//�����û�Ȩ���б�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_SET_USER_POP(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E7_CUSTOM:					//���ƹ���
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_CUSTOM(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E7_RMY_QUERY_ABILITY:		//��ѯ������
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_QUERY_ABILITY(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_RMY_REBOOT:				//�����豸(�ް���)(��Ӧ����Ϣ)
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_REBOOT(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_RMY_STOP:					//ֹͣ�豸(�ް���)(��Ӧ����Ϣ)
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_STOP(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_DEV_VER_INFO:	//��ѯ�豸�汾��Ϣ
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_DEV_VER_INFO(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_DUP_REQU_UPGRADE:			//��������
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_REQU_UPGRADE(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_PROGRESS:		//��ѯ��������
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_PROGRESS(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_DUP_QUERY_TRANS_POS:		//��ѯ����λ��
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_TRANS_POS(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;
	case NPC_D_DPS_MSGID_EVENT_E7_DUP_UPGRADE_DATA:			//�������ݰ�
		NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_UPGRADE_DATA(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

	case NPC_D_DPS_MSGID_MEDIA_E8_AUDIO_FRAME:				//��Ƶ֡����
		NPC_F_UMSP_MC_DoProEvent_MEDIA_E8_AUDIO_FRAME(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
		break;

// 	case NPC_D_DPS_MSGID_EVENT_E2_GUARD:					//������ͣ�ã�
// 		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GUARD(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
// 		break;
// 	case NPC_D_DPS_MSGID_EVENT_E2_UNGUARD:					//������ͣ�ã�
// 		NPC_F_UMSP_MC_DoProEvent_EVENT_E2_UNGUARD(pMcSrvData, pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
// 		break;

	default:
		{
			//д��־
			NPC_CHAR sTempLogBuf[256];
			sprintf(sTempLogBuf, "[UMSP]  Massage function id error: %8.8X.", pMsgHead->iMsgFuncId);
			NPC_F_LOG_SR_WriteLog(sTempLogBuf);

			pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_MSGFUNC_ERROR;

			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}
		break;
	}
}

//��ѯ�û���Ϣ�ص���������
NPC_BOOL	NPC_F_UMSP_DPS_QueryUserInfoCallback(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	IN		PNPC_CHAR								in_pUserName,				//�û���
	OUT		PNPC_S_DPS_USER_INFO					out_pUserInfo				//�û���Ϣ
	)
{
	NPC_CHAR										sCfgFileName[256];
	NPC_BOOL										bPwdIfMd5;
	NPC_CHAR										sKeyName[128];
	NPC_CHAR										sKeyValue[128];
	NPC_CHAR										sUserName[32];
	NPC_CHAR										sUserPwd[32];
	NPC_INT											i, k, iUserNum;

	strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

	//�û���
	iUserNum = GetPrivateProfileInt("USER", "UserNum", -1, sCfgFileName);
	if ( iUserNum < 0 )
	{
		WritePrivateProfileString("USER", "UserNum", "1", sCfgFileName);
		WritePrivateProfileString("USER", "UserName[0]", "admin", sCfgFileName);
		WritePrivateProfileString("USER", "UserPwd[0]", "admin", sCfgFileName);

		iUserNum = 1;
	}

	//NPC_BOOL									bPwdIfMd5;					//�����Ƿ�ΪMD5�����ΪTRUE��ʾ����ΪMD5���ܺ�ģ�FALSE��ʾ����Ϊ����
	bPwdIfMd5 = GetPrivateProfileInt("USER", "PwdIfMd5", 0, sCfgFileName);

	for ( i=0; i<iUserNum; i++ )
	{
		sprintf(sKeyName, "UserName[%d]", i);
		GetPrivateProfileString("USER", sKeyName, "", sUserName, sizeof(sUserName), sCfgFileName);

		if ( strcmp(in_pUserName, sUserName) == 0 )
		{
			sprintf(sKeyName, "UserPwd[%d]", i);
			GetPrivateProfileString("USER", sKeyName, "", sUserPwd, sizeof(sUserPwd), sCfgFileName);

			strcpy(out_pUserInfo->sUserName, in_pUserName);
			if ( bPwdIfMd5 )
			{
				//MD5����
				NPC_TOOLS_MD5_MD5Encrypt(out_pUserInfo->sUserPwd, sUserPwd);
			}
			else
			{
				strcpy(out_pUserInfo->sUserPwd, sUserPwd);
			}
			memset(out_pUserInfo->ucPopTable, 1, sizeof(out_pUserInfo->ucPopTable));

			//ȫ��Ȩ��
			sprintf(sKeyName, "GlobalPop[%d]", i);
			GetPrivateProfileString("USER", sKeyName, "", sKeyValue, sizeof(sKeyValue), sCfgFileName);

			if ( sKeyValue[0] == 0 )
				out_pUserInfo->dwGlobalPop = 0;
			else
				out_pUserInfo->dwGlobalPop = NPC_F_SYS_HexStrToDWORD(sKeyValue);

			//ͨ��Ȩ��
			for ( k=0; k<NPC_D_DPS_MAX_CHANNEL_NUM; k++ )
			{
				sprintf(sKeyName, "ChPop[%d][%d]", i, k);
				GetPrivateProfileString("USER", sKeyName, "", sKeyValue, sizeof(sKeyValue), sCfgFileName);

				if ( sKeyValue[0] == 0 )
					out_pUserInfo->dwChPopTable[k] = 0;
				else
					out_pUserInfo->dwChPopTable[k] = NPC_F_SYS_HexStrToDWORD(sKeyValue);
			}

/*
#define NPC_D_DPS_POP_REALPLAY							0x00000001				//ʵʱԤ��Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_PTZ_CTRL							0x00000002				//��̨����Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_TALK								0x00000004				//�����Խ�Ȩ�ޣ�����ȫ�ֺ�ͨ��Ȩ�ޣ�
#define NPC_D_DPS_POP_QUERY_FILE						0x00000008				//¼���ļ���ѯȨ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_BACKPLAY							0x00000010				//¼��ط�Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_ALARM								0x00000020				//��������Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_GET_CONFIG						0x00000040				//��ѯ����Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
#define NPC_D_DPS_POP_SET_CONFIG						0x00000080				//��������Ȩ�ޣ�ֻ��ȫ��Ȩ�ޣ�
*/
			return TRUE;
		}
	}

	return FALSE;
}

NPC_INT			G_iSum = 0;

//��ѯ�û���Ϣ�ص���������
NPC_BOOL	NPC_F_UMSP_DPS_DoConnectCallback(
	IN		PNPC_VOID								in_pUserData,				//�û�����
	OUT		PNPC_S_DPS_CONNECT_INFO					out_pDoConnInfo				//���Ӵ�����Ϣ	
	)
{
	if (G_iSum >= 10)
	{
		out_pDoConnInfo->iRet = 1;	
	}
	else if (out_pDoConnInfo->iType == 0)
	{
		G_iSum++;
	}
	
	if (out_pDoConnInfo->iType == 0)
	{
		
		printf("[DEBUG_UMSP]:��ȡ�����Ӵ���ص��¼�,ID = %0.8x, �¼����ͣ�����\r\n", out_pDoConnInfo->dwLoginID);
	}
	else
	{
		printf("[DEBUG_UMSP]:��ȡ�����Ӵ���ص��¼�,ID = %0.8x, �¼����ͣ��Ͽ�����\r\n", out_pDoConnInfo->dwLoginID);
	}
	return TRUE;
}
//-------------------------------------------------------------------------------
//�������ط���
NPC_BOOL	NPC_F_UMSP_MC_StartMcServer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_BOOL										bRet;

	//INIT AREA
	{
		bRet = TRUE;
	}

	//CODE AREA
	{
		//��ʼ������
		if ( !NPC_F_UMSP_MC_InitData(
			in_pMcSrvData			//���ط�������
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_UMSP_MC_InitData fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//��ȡ����
		if ( !NPC_F_UMSP_MC_ReadConfig(
			in_pMcSrvData				//���ط�������
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_UMSP_MC_ReadConfig fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//��ʼ���ļ������SDK
		if ( !NPC_F_FILECAM_SDK_InitSdk() )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_FILECAM_SDK_InitSdk fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//�����ļ������
		in_pMcSrvData->hFileCamera = NPC_F_FILECAM_SDK_ConnectFilecam(
			"FileCamera",				//Ŀ¼��
			&in_pMcSrvData->iChNum		//ͨ����
			);
		if ( in_pMcSrvData->hFileCamera == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_FILECAM_SDK_ConnectFilecam fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  Connection file camera success.");

		strcpy(in_pMcSrvData->tDevCapInfo.sDevType, "FileCamera");			//�豸����
		strcpy(in_pMcSrvData->tDevCapInfo.sDevModel, "FileCamera");			//�豸�ͺ�
		strcpy(in_pMcSrvData->tDevCapInfo.sSerialNumber, "123456");			//���к�
		in_pMcSrvData->tDevCapInfo.iVideoChanNum = in_pMcSrvData->iChNum;	//�豸ͨ������
		in_pMcSrvData->tDevCapInfo.iAudioChanNum = in_pMcSrvData->iChNum;	//�豸����ͨ����
		in_pMcSrvData->tDevCapInfo.iAlarmInPortNum = 0;						//�����������
		in_pMcSrvData->tDevCapInfo.iAlarmOutPortNum = 0;					//�����������
		in_pMcSrvData->tDevCapInfo.iDiskNum = 0;							//Ӳ�̸���
		in_pMcSrvData->tDevCapInfo.iSubProtoNum = 2;						//��������
		in_pMcSrvData->tDevCapInfo.bIfSupportZeroChannel = TRUE;			//��ͨ��
		in_pMcSrvData->tDevCapInfo.bIfSupportRecordBytime = TRUE;			//��ʱ��ط�
		in_pMcSrvData->tDevCapInfo.bIfSupportFileRange = FALSE;				//¼��ʱ�䷶Χ

#if 0
		in_pMcSrvData->tDevCapInfo.bIfOpenDoConnCallback = TRUE;
		in_pMcSrvData->tDevCapInfo.pDoConnCallback = (PNPC_VOID)NPC_F_UMSP_DPS_DoConnectCallback;
		in_pMcSrvData->tDevCapInfo.pDoConnUserData = (PNPC_VOID)in_pMcSrvData;
#endif

		//�����豸Э���������
		in_pMcSrvData->hUmspProSrv = NPC_F_DPS_StartDevProNetServer(
			5800,										//ý��TCP�����˿ں�
			&in_pMcSrvData->tDevCapInfo,				//�豸������Ϣ
			NPC_F_UMSP_DPS_ProEventCallback,			//Э���¼��ص�����ָ��
			(PNPC_VOID)in_pMcSrvData,					//Э���¼��û�����
			NPC_F_UMSP_DPS_QueryUserInfoCallback,		//��ѯ�û���Ϣ�ص�����ָ��
			(PNPC_VOID)in_pMcSrvData,					//��ѯ�û���Ϣ�û�����
			in_pMcSrvData->tConfig.bIfDebug,			//�Ƿ���ԣ��ڵ���״̬�£�������ܶ���־��Ϣ����ʽʹ��ʱ��Ҫ�ر�
			in_pMcSrvData->tConfig.bIfShowStreamLog,	//�Ƿ���ʾ����־����ý�����շ���־��Ϣ
			in_pMcSrvData->tConfig.bIfWriteLogToFile,	//�Ƿ�д��־���ļ�
			in_pMcSrvData->tConfig.sLogDir,				//��־Ŀ¼����־�ļ����Զ���������ʽΪLog����.txt
			in_pMcSrvData->tConfig.usLogPort,			//��־�˿ںţ����Ϊ0����������־�����˿ڣ�����0��������־�����˿ڷ���
			(in_pMcSrvData->tConfig.bPwdIfMd5?1:0)		//����ģʽ��ָ���봫��SDK�ķ�ʽ����0�����ģ�1��MD5
			);
		if ( in_pMcSrvData->hUmspProSrv == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_DPS_StartDevProNetServer fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//��������״̬��Ϣ��ʾ����
		NPC_F_DPS_SetShowRunState(
			in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
			TRUE									//�Ƿ���ʾ����״̬��Ϣ��TRUE��ʾҪ��ʾ��FALSE��ʾ����ʾ��ȱʡΪTRUE
			);

		

		//����ʵʱԤ��ֻ��I֡��ʱ�����룩
		//NPC_F_DPS_SetOnlySendIFrameTimeLen(
		//	in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
		//	30									//ֻ��I֡��ʱ�����룩��ȱʡΪ60��
		//	);

		//�����߳�
		if ( !NPC_F_UMSP_MC_StartThread(
			in_pMcSrvData							//���ط�������
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_StartMcServer NPC_F_UMSP_MC_StartThread fail.");

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  The success of network service protocol for starting the equipment.");
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//ֹͣ���ط���
			NPC_F_UMSP_MC_StopMcServer(
				in_pMcSrvData				//���ط�������
				);
		}
	}

	return bRet;
}

//ֹͣ���ط���
NPC_VOID	NPC_F_UMSP_MC_StopMcServer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	//�˳��߳�
	NPC_F_UMSP_MC_QuitThread(
		in_pMcSrvData						//���ط�������
		);

	//�Ͽ������ļ������
	if ( in_pMcSrvData->hFileCamera )
	{
		NPC_F_FILECAM_SDK_DisconnectFilecam(
			in_pMcSrvData->hFileCamera		//�ļ���������
			);
		in_pMcSrvData->hFileCamera = NULL;
	}

	//����ʼ���ļ������SDK
	NPC_F_FILECAM_SDK_UninitSdk();

	//ֹͣ�豸Э���������
	if ( in_pMcSrvData->hUmspProSrv )
	{
		NPC_F_DPS_StopDevProNetServer(
			in_pMcSrvData->hUmspProSrv		//�豸Э�����������
			);
		in_pMcSrvData->hUmspProSrv = NULL;
	}

	//����ʼ������
	NPC_F_UMSP_MC_UninitData(
		in_pMcSrvData						//���ط�������
		);
}

//��ʼ������
NPC_BOOL	NPC_F_UMSP_MC_InitData(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_INT											i;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;

	//��ʼ�����������
	for ( i=0; i<NPC_D_DPS_MAX_CHANNEL_NUM; i++ )
	{
		pCameraData = &in_pMcSrvData->tCameraTable[i];

		//����������
		pCameraData->hWorkLock = NPC_F_THREAD_Mutex_Create();
		if ( pCameraData->hWorkLock == NULL )
		{
			return FALSE;
		}

		sprintf(pCameraData->sChName, "Camera%2.2d", i);
	}

	in_pMcSrvData->iMp3FileNum = NPC_D_UMSP_MC_MAX_MP3_FILE_NUM / 4;
	for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
	{
		in_pMcSrvData->tMp3FileTable[i].bIfUsed = TRUE;
		sprintf(in_pMcSrvData->tMp3FileTable[i].sFileName, "TestFile-%d.mp3", i);
		in_pMcSrvData->tMp3FileTable[i].bIfPlaying = FALSE;
	}

	return TRUE;
}

//����ʼ������
NPC_VOID	NPC_F_UMSP_MC_UninitData(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_INT											i;

	for ( i=0; i<NPC_D_DPS_MAX_CHANNEL_NUM; i++ )
	{
		if ( in_pMcSrvData->tCameraTable[i].hWorkLock )
		{
			//�ͷŻ�����
			NPC_F_THREAD_Mutex_Destroy(
				in_pMcSrvData->tCameraTable[i].hWorkLock	//���������
				);
			in_pMcSrvData->tCameraTable[i].hWorkLock = NULL;
		}
	}
}

//��ȡ����
NPC_BOOL	NPC_F_UMSP_MC_ReadConfig(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_CHAR										sCfgFileName[256];

	strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

	//NPC_BOOL									bIfDebug;					//�Ƿ���ԣ��ڵ���״̬�£�������ܶ���־��Ϣ����ʽʹ��ʱ��Ҫ�ر�
	in_pMcSrvData->tConfig.bIfDebug = GetPrivateProfileInt("DEBUG", "IfDebug", 0, sCfgFileName);

	//NPC_BOOL									bIfShowStreamLog;			//�Ƿ���ʾ����־����ý�����շ���־��Ϣ
	in_pMcSrvData->tConfig.bIfShowStreamLog = GetPrivateProfileInt("DEBUG", "IfShowStreamLog", 0, sCfgFileName);

	//NPC_BOOL									bIfWriteLogToFile;			//�Ƿ�д��־���ļ�
	in_pMcSrvData->tConfig.bIfWriteLogToFile = GetPrivateProfileInt("DEBUG", "IfWriteLogToFile", 0, sCfgFileName);

	if ( in_pMcSrvData->tConfig.bIfWriteLogToFile )
	{
		//NPC_CHAR								sLogDir[256];				//��־Ŀ¼����־�ļ����Զ���������ʽΪLog����.txt
		GetPrivateProfileString("DEBUG", "LogDir", "", in_pMcSrvData->tConfig.sLogDir, sizeof(in_pMcSrvData->tConfig.sLogDir), sCfgFileName);
	}

	//NPC_USHORT								usLogPort;					//��־�˿ںţ����Ϊ0����������־�����˿ڣ�����0��������־�����˿ڷ���
	in_pMcSrvData->tConfig.usLogPort = GetPrivateProfileInt("DEBUG", "LogPort", 0, sCfgFileName);

	//NPC_BOOL									bPwdIfMd5;					//�����Ƿ�ΪMD5�����ΪTRUE��ʾ����ΪMD5���ܺ�ģ�FALSE��ʾ����Ϊ����
	in_pMcSrvData->tConfig.bPwdIfMd5 = GetPrivateProfileInt("USER", "PwdIfMd5", 0, sCfgFileName);

	//NPC_BOOL									bIfSendAlarmMsg;			//�Ƿ��ͱ�����Ϣ
	in_pMcSrvData->tConfig.bIfSendAlarmMsg = GetPrivateProfileInt("DEBUG", "IfSendAlarmMsg", 1, sCfgFileName);

	//NPC_INT									iSendAlarmIntervalTime;		//���ͱ�����Ϣ�ļ��ʱ�䣨�룩
	in_pMcSrvData->tConfig.iSendAlarmIntervalTime = GetPrivateProfileInt("DEBUG", "SendAlarmIntervalTime", 10, sCfgFileName);

	//NPC_INT									iMaxFileConnNum;			//����ļ�������������ܳ���NPC_D_UMSP_MC_MAX_FILE_WORK_NUM
	in_pMcSrvData->tConfig.iMaxFileConnNum = GetPrivateProfileInt("DEBUG", "MaxFileConnNum", NPC_D_UMSP_MC_MAX_FILE_WORK_NUM, sCfgFileName);
	if ( in_pMcSrvData->tConfig.iMaxFileConnNum <= 0 )
		in_pMcSrvData->tConfig.iMaxFileConnNum = 1;
	else if ( in_pMcSrvData->tConfig.iMaxFileConnNum > NPC_D_UMSP_MC_MAX_FILE_WORK_NUM )
		in_pMcSrvData->tConfig.iMaxFileConnNum = NPC_D_UMSP_MC_MAX_FILE_WORK_NUM;

	return TRUE;
}

//��ȡ��̬����
NPC_BOOL	NPC_F_UMSP_MC_ReadDynamicConfig(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_CHAR										sCfgFileName[256];

	strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

	//NPC_BOOL									bIfSwitchVideo;				//�Ƿ��л���Ƶ
	in_pMcSrvData->tConfig.bIfSwitchVideo = GetPrivateProfileInt("DEBUG", "IfSwitchVideo", 0, sCfgFileName);

	if ( in_pMcSrvData->tConfig.bIfSwitchVideo )
	{
		WritePrivateProfileString("DEBUG", "IfSwitchVideo", "0", sCfgFileName);
	}

	return TRUE;
}


//-------------------------------------------------------------------------------
//�����߳�
NPC_BOOL	NPC_F_UMSP_MC_StartThread(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	in_pMcSrvData->bRunFlag = TRUE;

	//�����߳�
	in_pMcSrvData->hThread = NPC_F_THREAD_CreateThread(
		NPC_F_UMSP_MC_ThreadWork,				//�̹߳�������
		(PNPC_VOID)in_pMcSrvData				//�������
		);
	if ( in_pMcSrvData->hThread == NULL )
	{
		return FALSE;
	}

	return TRUE;
}

//�˳��߳�
NPC_VOID	NPC_F_UMSP_MC_QuitThread(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	in_pMcSrvData->bRunFlag = FALSE;

	if ( in_pMcSrvData->hThread )
	{
		//�ȴ��˳��߳�
		NPC_F_THREAD_WaitExitThread(
			in_pMcSrvData->hThread,			//�߳̾��
			5000							//��ʱʱ�������룩
			);
	}
}

//�����߳�
NPC_VOID	NPC_F_UMSP_MC_ThreadWork(
	IN		PNPC_VOID								in_pParameter				//����ָ��
	)
{
	PNPC_S_UMSP_MCSRV_DATA							pMcSrvData;

	pMcSrvData = (PNPC_S_UMSP_MCSRV_DATA)in_pParameter;
	if ( pMcSrvData == NULL )
		return;

	while ( pMcSrvData->bRunFlag )
	{
		//����ʱ��
		NPC_F_UMSP_MC_DoTimer(
			pMcSrvData			//DPS���ط�������
			);

		NPC_F_SYS_Sleep(100);
	}
}

//����ʱ��
NPC_VOID	NPC_F_UMSP_MC_DoTimer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	time_t											tCurTime;

	tCurTime = time(NULL);

	if ( tCurTime - in_pMcSrvData->tPrecReadAlarmStateTime >= 1 )
	{
		in_pMcSrvData->tPrecReadAlarmStateTime = tCurTime;

		//������״̬
		NPC_F_UMSP_MC_DoAlarmState(
			in_pMcSrvData				//���ط�������
			);
	}

	if ( tCurTime - in_pMcSrvData->tPrecReadConfigTime >= 5 )
	{
		in_pMcSrvData->tPrecReadConfigTime = tCurTime;

		//��ȡ��̬����
		NPC_F_UMSP_MC_ReadDynamicConfig(
			in_pMcSrvData				//���ط�������
			);

		if ( in_pMcSrvData->tConfig.bIfSwitchVideo )
		{
			in_pMcSrvData->tConfig.bIfSwitchVideo = FALSE;

			//�ر�������Ƶ��
			NPC_F_UMSP_MC_CloseVideoStream(
				in_pMcSrvData			//���ط�������
				);
		}
	}
}


//-------------------------------------------------------------------------------
//����Э���¼�����ý����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_OPEN_MEDIA_STREAM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_OPEN_MEDIA_STREAM	pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	NPC_BOOL										bIfLock;
	NPC_S_FILECAM_SDK_CH_PARAM						tChParam = {0};
	NPC_INT											iChNo = 0;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_OPEN_MEDIA_STREAM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pCameraData = NULL;
		bIfLock = FALSE;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Open media stream: channel no: %d, stream no: %d.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iStreamNo);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

			
		if ( pMsgBody->i_iChNo < 0 || pMsgBody->i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM && pMsgBody->i_iChNo != NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_OPEN_MEDIA_STREAM i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_iStreamNo < 0 || pMsgBody->i_iStreamNo > NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_OPEN_MEDIA_STREAM i_iStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if (pMsgBody->i_iChNo == NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			iChNo = NPC_D_DPS_MAX_CHANNEL_NUM;
		}
		else
		{
			iChNo = pMsgBody->i_iChNo;
		}
		pCameraData = &(in_pMcSrvData->tCameraTable[iChNo]);

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);
		bIfLock = TRUE;

		switch ( pMsgBody->i_iStreamNo)
		{
		case 0:
			{
				pCameraData->bMainStreamOpenFlag = TRUE;
				pCameraData->iMainVideoLevel = -1;
			}
			break;

		case 1:
			{
				pCameraData->bSubStreamOpenFlag = TRUE;
				pCameraData->iSubVideoLevel = -1;
			}
			break;
		case 2:
			{
				pCameraData->bThirdStreamOpenFlag = TRUE;
				pCameraData->iSubVideoLevel = -1;
			}
			break;
		}
		

		pCameraData->iStreamNo = pMsgBody->i_iStreamNo;

		if ( !pCameraData->bIfUsed )
		{
			if (pMsgBody->i_iChNo != NPC_D_DPS_ZERO_CHANNEL_VALUE)
			{
				//��ʼԤ��
				if ( !NPC_F_FILECAM_SDK_RealPlay(
					in_pMcSrvData->hFileCamera,					//�ļ���������
					pMsgBody->i_iChNo,							//ͨ����
					NPC_F_UMSP_FILECAM_SDK_RealDataCallBack,	//ý�����ݻص�����
					(NPC_DWORD)pCameraData,						//�û�����
					&tChParam									//�ļ����������
					) )
				{
					//д��־
					NPC_F_LOG_SR_WriteLog("[UMSP]  Open file camera realplay fail!");
					
					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OPEN_STREAM_FAIL;
					goto _NPC_CLEAR;
				}
			}
			else
			{
				//��ʼԤ��
				if ( !NPC_F_FILECAM_SDK_RealPlay(
					in_pMcSrvData->hFileCamera,					//�ļ���������
					0,							//ͨ����
					NPC_F_UMSP_FILECAM_SDK_RealDataCallBack,	//ý�����ݻص�����
					(NPC_DWORD)pCameraData,						//�û�����
					&tChParam									//�ļ����������
					) )
				{
					//д��־
					NPC_F_LOG_SR_WriteLog("[UMSP]  Open file camera realplay fail!");
					
					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OPEN_STREAM_FAIL;
					goto _NPC_CLEAR;
				}
			}
			

			pCameraData->bIfUsed = TRUE;
			pCameraData->iChNo = pMsgBody->i_iChNo;
			pCameraData->pMcSrvData = (PNPC_VOID)in_pMcSrvData;
			pCameraData->iFrameRate = tChParam.iFrameRate;
			pCameraData->bIfSupportAudio = tChParam.bIfSupportAudio;

			pCameraData->tRecStartTime = 0;
			pCameraData->dwRecvFrameNum = 0;
			pCameraData->bIfWriteIFrame = FALSE;

			//��ʼ¼��
			if ( !NPC_F_UMSP_MC_StartRecord(
				in_pMcSrvData,				//���ط�������
				pCameraData,				//���������
				pMsgBody->i_iChNo,			//ͨ����
				tChParam.iFrameRate			//֡��
				) )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  Start record fail!");
			}
		}

		pMsgBody->o_bVideoFlag = TRUE;									//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
		pMsgBody->o_bAudioFlag = pCameraData->bIfSupportAudio;			//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ

		pMsgBody->o_iVideoCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;	//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
		pMsgBody->o_iVideoFrameRate = tChParam.iFrameRate;				//��Ƶ֡��
		pMsgBody->o_iVideoBitRate = 128;								//��Ƶ���ʣ�kbps��
		pMsgBody->o_usVideoWidth = 352;									//��Ƶ���
		pMsgBody->o_usVideoHeight = 288;								//��Ƶ�߶�

		if ( pCameraData->bIfSupportAudio )
		{
			pMsgBody->o_iAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_*����
			pMsgBody->o_iAudioBitRate = 64;									//��Ƶ���ʣ�kbps������64
			pMsgBody->o_iAudioSampleRate = 8000;							//��Ƶ�����ʣ���8000
			pMsgBody->o_iAudioChNum = 1;									//��Ƶ����������1
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pCameraData && bIfLock )
		{
			//����
			NPC_F_THREAD_Mutex_Unlock(
				pCameraData->hWorkLock			//���������
				);
		}

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼����ر�ý����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_CLOSE_MEDIA_STREAM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM	pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	NPC_BOOL										bIfLock;
	NPC_INT											iChNo;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		if ( in_pMsgHead->ucMsgType != NPC_D_DPS_MSG_TYPE_REQUEST )
			return;

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pCameraData = NULL;
		bIfLock = FALSE;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Close media stream: channel no: %d, stream no: %d.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iStreamNo);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_iChNo < 0 || pMsgBody->i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM && pMsgBody->i_iChNo != NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_CLOSE_MEDIA_STREAM i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_iStreamNo < 0 || pMsgBody->i_iStreamNo >= NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_CLOSE_MEDIA_STREAM i_iStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if (pMsgBody->i_iChNo == NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			iChNo = NPC_D_DPS_MAX_CHANNEL_NUM;
		}
		else
		{
			iChNo = pMsgBody->i_iChNo;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[iChNo]);

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);
		bIfLock = TRUE;

		if ( pMsgBody->i_iStreamNo == 0 )
			pCameraData->bMainStreamOpenFlag = FALSE;
		else
			pCameraData->bSubStreamOpenFlag = FALSE;

		if ( pCameraData->bIfUsed && 
			!pCameraData->bMainStreamOpenFlag && 
			!pCameraData->bSubStreamOpenFlag )
		{
			//����Ԥ��
			NPC_F_FILECAM_SDK_StopRealPlay(
				in_pMcSrvData->hFileCamera,			//�ļ���������
				pMsgBody->i_iChNo					//ͨ����
				);
			pCameraData->bIfUsed = FALSE;

			//ֹͣ¼��
			NPC_F_UMSP_MC_StopRecord(
				in_pMcSrvData,			//���ط�������
				pCameraData				//���������
				);
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pCameraData && bIfLock )
		{
			//����
			NPC_F_THREAD_Mutex_Unlock(
				pCameraData->hWorkLock			//���������
				);
		}

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����̨����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_PTZ_CTRL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_PTZ_CTRL			pMsgBody;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_PTZ_CTRL)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  PTZ ctrl: channel no: %d, order: %d, param: %d, ext_param1: %d, ext_param2: %d.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iPtzCmd, 
			pMsgBody->i_dwPtzData, 
			pMsgBody->i_dwPtzExtParam1, 
			pMsgBody->i_dwPtzExtParam2 
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_iChNo < 0 || pMsgBody->i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_PTZ_CTRL i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

#if 0
		if (pMsgBody->i_iPtzCmd == 101)
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_PTZ_CTRL PtzCmd = 101.");
			
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_WITHOUT_PERMISSION;
			goto _NPC_CLEAR;
		}
#endif
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�������ǿ�Ʒ���I֡
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FORCE_I_FRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FORCE_I_FRAME		pMsgBody;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FORCE_I_FRAME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//�����ʾ������δ����ǿ��I֡���豸������Ҫ�������Ϣ��ǿ�ƴ�I֡����

		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Force i frame: channel no: %d, stream no: %d.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iStreamNo
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_iChNo < 0 || pMsgBody->i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FORCE_I_FRAME i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_iStreamNo < 0 || pMsgBody->i_iStreamNo >= NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FORCE_I_FRAME i_iStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		//����ǿ��I֡
		NPC_F_FILECAM_SDK_RequestForceIFrame(
			in_pMcSrvData->hFileCamera,			//�ļ���������
			pMsgBody->i_iChNo					//ͨ����
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//����Э���¼�����ȡ��Ƶ�����ȼ������б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_CAP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_CAP		pMsgBody;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_CAP)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Get video quality cap: channel no: %d, stream no: %d.", 
			pMsgBody->i_usChNo, 
			pMsgBody->i_usStreamNo
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_usChNo < 0 || pMsgBody->i_usChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_CAP i_usChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_usStreamNo < 0 || pMsgBody->i_usStreamNo >= NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_CAP i_usStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		pMsgBody->o_iLevelNum = 3;

		strcpy(pMsgBody->o_tLevelTable[0].sLevelName, "��");		//�ȼ�����
		pMsgBody->o_tLevelTable[0].iLevelValue = 0;					//�ȼ�ֵ��������ڵ���0
		pMsgBody->o_tLevelTable[0].usWidth = 1280;					//ͼ���
		pMsgBody->o_tLevelTable[0].usHeight = 720;					//ͼ���
		pMsgBody->o_tLevelTable[0].usFrameRate = 10;				//֡��
		pMsgBody->o_tLevelTable[0].usBitRate = 1280;				//���ʣ���λ��kbps

		strcpy(pMsgBody->o_tLevelTable[1].sLevelName, "��");		//�ȼ�����
		pMsgBody->o_tLevelTable[1].iLevelValue = 1;					//�ȼ�ֵ��������ڵ���0
		pMsgBody->o_tLevelTable[1].usWidth = 720;					//ͼ���
		pMsgBody->o_tLevelTable[1].usHeight = 576;					//ͼ���
		pMsgBody->o_tLevelTable[1].usFrameRate = 8;					//֡��
		pMsgBody->o_tLevelTable[1].usBitRate = 512;					//���ʣ���λ��kbps

		strcpy(pMsgBody->o_tLevelTable[2].sLevelName, "��");		//�ȼ�����
		pMsgBody->o_tLevelTable[2].iLevelValue = 2;					//�ȼ�ֵ��������ڵ���0
		pMsgBody->o_tLevelTable[2].usWidth = 320;					//ͼ���
		pMsgBody->o_tLevelTable[2].usHeight = 288;					//ͼ���
		pMsgBody->o_tLevelTable[2].usFrameRate = 5;					//֡��
		pMsgBody->o_tLevelTable[2].usBitRate = 128;					//���ʣ���λ��kbps
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����ȡ��Ƶ�����ȼ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_LEVEL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_LEVEL	pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA									pCameraData;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_GET_VIDEO_QUALITY_LEVEL)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Get video quality level: channel no: %d, stream no: %d.", 
			pMsgBody->i_usChNo, 
			pMsgBody->i_usStreamNo
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_usChNo < 0 || pMsgBody->i_usChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_LEVEL i_usChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_usStreamNo < 0 || pMsgBody->i_usStreamNo >= NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_LEVEL i_iStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[pMsgBody->i_usChNo]);

		if ( pMsgBody->i_usStreamNo == 0 )
			pMsgBody->o_iLevelValue = pCameraData->iMainVideoLevel;
		else
			pMsgBody->o_iLevelValue = pCameraData->iSubVideoLevel;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼���������Ƶ�����ȼ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_SET_VIDEO_QUALITY_LEVEL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E2_SET_VIDEO_QUALITY_LEVEL	pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA									pCameraData;

	//INIT AREA
	{
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_SET_VIDEO_QUALITY_LEVEL)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Set video quality level: channel no: %d, stream no: %d, level: %d.", 
			pMsgBody->i_usChNo, 
			pMsgBody->i_usStreamNo, 
			pMsgBody->i_iLevelValue
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		if ( pMsgBody->i_usChNo < 0 || pMsgBody->i_usChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_SET_VIDEO_QUALITY_LEVEL i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		if ( pMsgBody->i_usStreamNo < 0 || pMsgBody->i_usStreamNo >= NPC_D_DPS_MAX_CH_STREAM_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_SET_VIDEO_QUALITY_LEVEL i_iStreamNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR;
			goto _NPC_CLEAR;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[pMsgBody->i_usChNo]);

		if ( pMsgBody->i_usStreamNo == 0 )
			pCameraData->iMainVideoLevel = pMsgBody->i_iLevelValue;
		else
			pCameraData->iSubVideoLevel = pMsgBody->i_iLevelValue;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//����Э���¼�����ѯ�ļ���¼���ͼƬ�ļ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QUERY			pMsgBody;
	NPC_CHAR										sStartTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	PNPC_BYTE										pFileInfoDataBuf;
	NPC_INT											iFileInfoDataBufSize;
	NPC_INT											iFileInfoDataLen;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataLen;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QUERY)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pFileInfoDataBuf = NULL;
		iFileInfoDataBufSize = 0;
		iFileInfoDataLen = 0;

		pSendDataBuf = NULL;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tStartTime,		//TDʱ��
			sStartTimeStr					//ʱ���ַ���
			);

		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tEndTime,			//TDʱ��
			sEndTimeStr						//ʱ���ַ���
			);

		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Query file: channel no: %d, file type: %d, create mode: %d, alerm event: %d, start time: %s, end time: %s.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iFileType, 
			pMsgBody->i_iCreateMode, 
			pMsgBody->i_iAlarmEvent, 
			sStartTimeStr,  
			sEndTimeStr
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��ѯ�ļ�
		if ( !NPC_F_UMSP_MC_FindFile(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_iChNo,			//ͨ����
			&pMsgBody->i_tStartTime,	//��ʼʱ��
			&pMsgBody->i_tEndTime,		//����ʱ��
			&pMsgBody->o_iFileNum,		//�ļ���
			&pFileInfoDataBuf,			//�ļ���Ϣ���ݻ�����
			&iFileInfoDataBufSize,		//�ļ���Ϣ���ݻ�������С
			&iFileInfoDataLen			//�ļ���Ϣ���ݳ���
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QUERY NPC_F_UMSP_MC_FindFile fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_QUERY_FILE_FAIL;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		iSendDataLen = in_iMsgDataLen + iFileInfoDataLen;
		pSendDataBuf = (PNPC_BYTE)malloc(iSendDataLen);
		if ( pSendDataBuf == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QUERY malloc fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		memcpy(pSendDataBuf, in_pMsgDataBuf, in_iMsgDataLen);
		if ( pFileInfoDataBuf && iFileInfoDataLen > 0 )
			memcpy(pSendDataBuf+in_iMsgDataLen, pFileInfoDataBuf, iFileInfoDataLen);

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		if ( pMsgBody->o_iFileNum == 0 )
			pSendMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_EXIST;

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		if ( pFileInfoDataBuf )
		{
			free(pFileInfoDataBuf);
			pFileInfoDataBuf = NULL;
		}

		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}
}

//����Э���¼�����չ��ѯ�ļ���¼���ͼƬ�ļ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_NSP_FILE_QUERY		pMsgBody;
	NPC_CHAR										sStartTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	PNPC_BYTE										pFileInfoDataBuf;
	NPC_INT											iFileInfoDataBufSize;
	NPC_INT											iFileInfoDataLen;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataLen;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	NPC_CHAR										sTempAlarmEventTable[128];
	PNPC_CHAR										pPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_NSP_FILE_QUERY)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pFileInfoDataBuf = NULL;
		iFileInfoDataBufSize = 0;
		iFileInfoDataLen = 0;

		pSendDataBuf = NULL;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tStartTime,		//TDʱ��
			sStartTimeStr					//ʱ���ַ���
			);

		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tEndTime,			//TDʱ��
			sEndTimeStr						//ʱ���ַ���
			);

		sTempAlarmEventTable[0] = 0;
		pPos = sTempAlarmEventTable;
		for ( i=0; i<pMsgBody->i_iAlarmEventNum; i++ )
		{
			if ( i == 0 )
				sprintf(pPos, "%d", pMsgBody->i_ucAlarmEventTable[i]);
			else
				sprintf(pPos, ",%d", pMsgBody->i_ucAlarmEventTable[i]);
			pPos += strlen(pPos);
		}

		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Query nsp file: channel no: %d, file type: %d, create mode: %d, alerm event: %s, start time: %s, end time: %s.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iFileType, 
			pMsgBody->i_iCreateMode, 
			sTempAlarmEventTable, 
			sStartTimeStr,  
			sEndTimeStr
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��չ��ѯ�ļ�
		if ( !NPC_F_UMSP_MC_NspFindFile(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_iChNo,			//ͨ����
			pMsgBody->i_iStreamNo,		//������
			&pMsgBody->i_tStartTime,	//��ʼʱ��
			&pMsgBody->i_tEndTime,		//����ʱ��
			&pMsgBody->o_iFileNum,		//�ļ���
			&pFileInfoDataBuf,			//�ļ���Ϣ���ݻ�������ΪNPC_S_MON_MPS_FILE_HEAD_INFO����
			&iFileInfoDataBufSize,		//�ļ���Ϣ���ݻ�������С
			&iFileInfoDataLen			//�ļ���Ϣ���ݳ���
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY NPC_F_UMSP_MC_FindFile fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_QUERY_FILE_FAIL;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		iSendDataLen = in_iMsgDataLen + iFileInfoDataLen;
		pSendDataBuf = (PNPC_BYTE)malloc(iSendDataLen);
		if ( pSendDataBuf == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY malloc fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		memcpy(pSendDataBuf, in_pMsgDataBuf, in_iMsgDataLen);
		if ( pFileInfoDataBuf && iFileInfoDataLen > 0 )
			memcpy(pSendDataBuf+in_iMsgDataLen, pFileInfoDataBuf, iFileInfoDataLen);

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		if ( pMsgBody->o_iFileNum == 0 )
			pSendMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_EXIST;

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		if ( pFileInfoDataBuf )
		{
			free(pFileInfoDataBuf);
			pFileInfoDataBuf = NULL;
		}

		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}
}


//����Э���¼�����ѯ¼���ļ�ʱ�䷶Χ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RANGE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RANGE_QUERY	pMsgBody;
	NPC_CHAR										sStartTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	PNPC_BYTE										pFileInfoDataBuf;
	NPC_INT											iFileInfoDataBufSize;
	NPC_INT											iFileInfoDataLen;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataLen;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	NPC_CHAR										sTempAlarmEventTable[128];
	PNPC_CHAR										pPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RANGE_QUERY)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pFileInfoDataBuf = NULL;
		iFileInfoDataBufSize = 0;
		iFileInfoDataLen = 0;

		pSendDataBuf = NULL;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tStartTime,		//TDʱ��
			sStartTimeStr					//ʱ���ַ���
			);

		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tEndTime,			//TDʱ��
			sEndTimeStr						//ʱ���ַ���
			);

		sTempAlarmEventTable[0] = 0;
		pPos = sTempAlarmEventTable;
		for ( i=0; i<pMsgBody->i_iAlarmEventNum; i++ )
		{
			if ( i == 0 )
				sprintf(pPos, "%d", pMsgBody->i_ucAlarmEventTable[i]);
			else
				sprintf(pPos, ",%d", pMsgBody->i_ucAlarmEventTable[i]);
			pPos += strlen(pPos);
		}

		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Query file Range: channel no: %d,  create mode: %d, alerm event: %s, start time: %s, end time: %s.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iCreateMode, 
			sTempAlarmEventTable, 
			sStartTimeStr,  
			sEndTimeStr
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��ȡ¼���ļ�ʱ�䷶Χ
		if ( !NPC_F_UMSP_MC_GetFileRange(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_iChNo,			//ͨ����
			pMsgBody->i_iStreamNo,		//������
			&pMsgBody->i_tStartTime,	//��ʼʱ��
			&pMsgBody->i_tEndTime,		//����ʱ��
			&pMsgBody->o_iFileNum,		//�ļ���
			&pFileInfoDataBuf,			//�ļ���Ϣ���ݻ�������ΪNPC_S_MON_MPS_FILE_HEAD_INFO����
			&iFileInfoDataBufSize,		//�ļ���Ϣ���ݻ�������С
			&iFileInfoDataLen			//�ļ���Ϣ���ݳ���
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY NPC_F_UMSP_MC_FindFile fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_QUERY_FILE_FAIL;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		iSendDataLen = in_iMsgDataLen + iFileInfoDataLen;
		pSendDataBuf = (PNPC_BYTE)malloc(iSendDataLen);
		if ( pSendDataBuf == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY malloc fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		memcpy(pSendDataBuf, in_pMsgDataBuf, in_iMsgDataLen);
		if ( pFileInfoDataBuf && iFileInfoDataLen > 0 )
			memcpy(pSendDataBuf+in_iMsgDataLen, pFileInfoDataBuf, iFileInfoDataLen);

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		if ( pMsgBody->o_iFileNum == 0 )
			pSendMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_EXIST;

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		if ( pFileInfoDataBuf )
		{
			free(pFileInfoDataBuf);
			pFileInfoDataBuf = NULL;
		}

		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}
}


//����Э���¼������ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Open file: file flag: %s, start data pos: %d, start time pos: %d.", 
			pMsgBody->i_sFileFlag, 
			pMsgBody->i_dwStartOffsetDataPos, 
			pMsgBody->i_dwStartOffsetTimePos
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//���ļ�
		in_pMsgHead->ucResult = NPC_F_UMSP_MC_File_OpenFile(
			in_pMcSrvData,						//���ط�������
			pMsgBody->i_sFileFlag,				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
			pMsgBody->i_dwStartOffsetDataPos,	//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
			pMsgBody->i_dwStartOffsetTimePos,	//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
			&pMsgBody->o_dwFileReadId,			//�����ļ���ȡID
			&pMsgBody->o_tFileInfo				//�ļ���Ϣ
			);
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼������ļ�,��ʱ�䷽ʽ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN_BY_TIME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN_BY_TIME	pMsgBody;

	NPC_CHAR										sStartTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	NPC_CHAR										sTempAlarmEventTable[128];
	PNPC_CHAR										pPos;
	NPC_INT											i;

	NPC_S_MON_MPS_FILE_HEAD_INFO					tFileInfo = {0};

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_OPEN_BY_TIME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ

		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tStartTime,		//TDʱ��
			sStartTimeStr					//ʱ���ַ���
			);
		
		//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
		NPC_F_SYS_TdTime_To_TimeStr(
			&pMsgBody->i_tEndTime,			//TDʱ��
			sEndTimeStr						//ʱ���ַ���
			);
		
		sTempAlarmEventTable[0] = 0;
		pPos = sTempAlarmEventTable;
		for ( i=0; i<pMsgBody->i_iAlarmEventNum; i++ )
		{
			if ( i == 0 )
				sprintf(pPos, "%d", pMsgBody->i_ucAlarmEventTable[i]);
			else
				sprintf(pPos, ",%d", pMsgBody->i_ucAlarmEventTable[i]);
			pPos += strlen(pPos);
		}
		
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  open file by time: channel no: %d, file type: %d, create mode: %d, alerm event: %s, start time: %s, end time: %s.", 
			pMsgBody->i_iChNo, 
			pMsgBody->i_iFileType, 
			pMsgBody->i_iCreateMode, 
			sTempAlarmEventTable, 
			sStartTimeStr,  
			sEndTimeStr
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��ѯ�ļ�,��ȡ��һ���ļ���Ϣ
		if ( !NPC_F_UMSP_MC_NspFindFirstFile(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_iChNo,			//ͨ����
			pMsgBody->i_iStreamNo,		//������
			&pMsgBody->i_tStartTime,	//��ʼʱ��
			&pMsgBody->i_tEndTime,		//����ʱ��
			&tFileInfo		
			) )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN_BY_TIME NPC_F_UMSP_MC_NspFindFirstFile fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_QUERY_FILE_FAIL;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}
		
		//���ļ�
		in_pMsgHead->ucResult = NPC_F_UMSP_MC_File_OpenFile(
			in_pMcSrvData,						//���ط�������
			tFileInfo.sFileFlag,				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������			
			0,	//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
			0,	//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
			&pMsgBody->o_dwFileReadId,			//�����ļ���ȡID
			&pMsgBody->o_tFileInfo				//�ļ���Ϣ
			);
	}

	//CLEAR AREA
_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼����ر��ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_CLOSE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_CLOSE			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_CLOSE)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Close file: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		if ( pMsgBody->i_dwFileReadId != 0 )
		{
			//�ر��ļ�
			NPC_F_UMSP_MC_File_CloseFile(
				in_pMcSrvData,				//���ط�������
				pMsgBody->i_dwFileReadId	//�ļ���ȡID
				);
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����ȡ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ			pMsgBody;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	NPC_INT											iMediaType;					//ý�����ͣ�0����Ƶ��1����Ƶ
	NPC_CHAR										cFrameType;					//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
	NPC_DWORD										dwTimestamp;				//ʱ���
	NPC_DWORD										dwRecOffsetTime;			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
	PNPC_BYTE										pMediaDataBuf;				//ý�����ݻ�������ԭʼ�������ݣ�
	NPC_INT											iMediaDataBufSize;			//ý�����ݻ�������С
	NPC_INT											iMediaDataLen;				//ý�����ݳ���

	NPC_DWORD										dwBeginReadTime;
	NPC_INT											iVideoFrameNum;
	NPC_BOOL										bIfSendFrameData;
	NPC_INT											iEndFlag;
	NPC_INT											iIFrameNum;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pMediaDataBuf = NULL;
		iMediaDataBufSize = 0;
		iMediaDataLen = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Read file: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��ѯ�ļ��������ݣ������ļ���ID��
		pFileWorkData = NPC_F_UMSP_MC_File_QueryFileWorkDataByFileReadId(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_dwFileReadId	//�ļ���ȡID
			);
		if ( pFileWorkData == NULL )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ i_dwFileReadId not exist.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		if ( pFileWorkData->hNavFile == NULL )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ file not open.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_OPEN;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//--------------------------------------------------------------------
		//��ȡ�ļ�
		/*
		NPC_BYTE		i_ucReqDataSize;	
		//�������ݴ�С���������ָ����Ƶ���ݣ��ò���ָ֡������Ƶָ֡������Ƶָ������ͼƬ����ָ����K�ֽ�
		//���Ϊ0����ֹͣ��һֱ��ȡ���ͣ�ֱ����ȡ�ļ����
		//��ȡ�������ʱ�������ļ��е�����˳���ȡ�������ȡΪ��Ƶ֡��������Ƶ֡���������Ƶ���ݣ�������Ƶ����Ƶ���ݵ������ݰ���С���10K��һ������Ķ�ȡ����������Ƶ֡Ϊ׼��
		*/

		//�����ȡ���������ͣ�0��������ݣ�1����Ƶ��2����Ƶ���������ͼƬ�ļ����ò�����Ч����ֵΪ100��ʾֹͣ��������
		dwBeginReadTime = 0;
		iVideoFrameNum = 0;
		iIFrameNum = 0;

		while ( 1 )
		{
			//��ȡý�����ݣ���Ƶ����Ƶ��
			if ( !NPC_F_NAV_ReadMediaData(
				pFileWorkData->hNavFile,		//NAV�ļ����
				&iMediaType,					//ý�����ͣ�0����Ƶ��1����Ƶ
				&cFrameType,					//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
				&dwTimestamp,					//ʱ���
				&dwRecOffsetTime,				//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
				&pMediaDataBuf,					//ý�����ݻ�������ԭʼ�������ݣ�
				&iMediaDataBufSize,				//ý�����ݻ�������С
				&iMediaDataLen					//ý�����ݳ���
				) )
			{
				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Read file end.");

				//����һý��֡���ݣ���Ƶ����Ƶ��
				if ( !NPC_F_UMSP_MC_File_SendMediaFrameData(
					in_pMcSrvData,				//���ط�������
					pFileWorkData,				//�ļ���������
					in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen,				//��Ϣ���ݳ���
					2,							//������־��0��δ������1���������������2���ļ�����
					0,							//ý�����ͣ�0����Ƶ��1����Ƶ
					'P',						//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
					0,							//ʱ���
					0,							//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
					NULL,						//ý�����ݻ�������ԭʼ�������ݣ�
					0							//ý�����ݳ���
					) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ NPC_F_UMSP_MC_File_SendMediaFrameData fail.");
				}

				if ( pMsgBody->i_dwFileReadId != 0 )
				{
					//�ر��ļ�
					NPC_F_UMSP_MC_File_CloseFile(
						in_pMcSrvData,					//���ط�������
						pFileWorkData->dwFileReadId		//�ļ���ȡID
						);
				}
				goto _NPC_CLEAR;
			}

			if ( iMediaType == 0 )
				iVideoFrameNum++;

			if ( dwBeginReadTime == 0 )
				dwBeginReadTime = dwRecOffsetTime;

			bIfSendFrameData = FALSE;
			iEndFlag = 0;

			if ( pFileWorkData->bIfOnlySendIFrame )
			{
				//iMediaType,								//ý�����ͣ�0����Ƶ��1����Ƶ
				//cFrameType,								//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
				//pFileWorkData->bIfOnlySendIFrame;			//�Ƿ�ֻ��I֡
				//pFileWorkData->iDiscardIFrame;			//����I֡����0������I֡��1������1��I֡�������1��I֡���䣩��2������2��I֡���������

				if ( iMediaType == 0 && cFrameType == 'I' )
				{
					if ( ++iIFrameNum >= pFileWorkData->iDiscardIFrame )
					{
						bIfSendFrameData = TRUE;
						iEndFlag = 1;
					}
				}
			}
			else
			{
				switch ( pMsgBody->i_ucReqDataType )
				{
				case 0: //0���������
					bIfSendFrameData = TRUE;
					break;
				case 1: //1����Ƶ
					if ( iMediaType == 0 )
						bIfSendFrameData = TRUE;
					break;
				case 2: //2����Ƶ
					if ( iMediaType == 1 )
						bIfSendFrameData = TRUE;
					break;
				}

				if ( pMsgBody->i_ucReqDataSize != 0 && dwRecOffsetTime - dwBeginReadTime >= pMsgBody->i_ucReqDataSize )
				{
					iEndFlag = 1;
				}
			}

			if ( bIfSendFrameData )
			{
				//����һý��֡���ݣ���Ƶ����Ƶ��
				if ( !NPC_F_UMSP_MC_File_SendMediaFrameData(
					in_pMcSrvData,				//���ط�������
					pFileWorkData,				//�ļ���������
					in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen,				//��Ϣ���ݳ���
					iEndFlag,					//������־��0��δ������1���������������2���ļ�����
					iMediaType,					//ý�����ͣ�0����Ƶ��1����Ƶ
					cFrameType,					//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
					dwTimestamp,				//ʱ���
					dwRecOffsetTime,			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
					pMediaDataBuf,				//ý�����ݻ�������ԭʼ�������ݣ�
					iMediaDataLen				//ý�����ݳ���
					) )
				{
					break;
				}
			}

			if ( iEndFlag == 1 )
			{
				break;
			}
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		//�ͷŻ�����
		NPC_F_NAV_ReleaseBuf(
			&pMediaDataBuf		//���ݻ�����
			);
	}
}

//����Э���¼�����λ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Seek file: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��λ�ļ�
		in_pMsgHead->ucResult = NPC_F_UMSP_MC_File_SeekFile(
			in_pMcSrvData,					//���ط�������
			pMsgBody->i_dwFileReadId,		//�ļ���ȡID
			pMsgBody->i_dwOffsetTimePos		//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ��
			);
		if ( in_pMsgHead->ucResult != 0 )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Seek file fail.");
		}
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//����Э���¼�����λ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK_BY_TIME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL												bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK_BY_TIME			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_SEEK_BY_TIME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Seek file by time: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//��λ�ļ�
		in_pMsgHead->ucResult = NPC_F_UMSP_MC_File_SeekFile(
			in_pMcSrvData,					//���ط�������
			pMsgBody->i_dwFileReadId,		//�ļ���ȡID
			0								//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ��
			);
		if ( in_pMsgHead->ucResult != 0 )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Seek file fail.");
		}
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����ѯ��Ƶ����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QVIDEO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QVIDEO		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_QVIDEO)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Query video file param: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//��ȡ�ļ�����Ƶ����
		if ( !NPC_F_UMSP_MC_File_GetFileVideoParam(
			in_pMcSrvData,					//���ط�������
			pMsgBody->i_dwFileReadId,		//�ļ���ȡID
			&pMsgBody->o_iVideoFrameRate,	//֡��
			&pMsgBody->o_iVideoGop			//GOP
			) )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Query video file param fail.");
		}
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�������I֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_ONLY_IFRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_ONLY_IFRAME	pMsgBody;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_ONLY_IFRAME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Request file only i frame: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//��ѯ�ļ��������ݣ������ļ���ID��
		pFileWorkData = NPC_F_UMSP_MC_File_QueryFileWorkDataByFileReadId(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_dwFileReadId	//�ļ���ȡID
			);
		if ( pFileWorkData == NULL )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Query file work data fail.");
			goto _NPC_CLEAR;
		}

		pFileWorkData->bIfOnlySendIFrame = TRUE;							//�Ƿ�ֻ��I֡
		pFileWorkData->iDiscardIFrame = pMsgBody->i_iDiscardIFrame;			//����I֡����0������I֡��1������1��I֡�������1��I֡���䣩��2������2��I֡���������

		//------------------------------------------------------------------------------
		//��ȡ�ļ�����Ƶ����
		if ( !NPC_F_UMSP_MC_File_GetFileVideoParam(
			in_pMcSrvData,						//���ط�������
			pMsgBody->i_dwFileReadId,			//�ļ���ȡID
			&pMsgBody->o_iVideoFrameRate,		//֡��
			&pMsgBody->o_iVideoGop				//GOP
			) )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get file video param fail.");
			goto _NPC_CLEAR;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�������ָ�ȫ֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RECOVER_ALLFRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RECOVER_ALLFRAME	pMsgBody;
	PNPC_S_UMSP_FILE_WORK_DATA							pFileWorkData;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_RECOVER_ALLFRAME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Request recover all frame: file read ID: 0x%8.8x.", 
			pMsgBody->i_dwFileReadId
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//��ѯ�ļ��������ݣ������ļ���ID��
		pFileWorkData = NPC_F_UMSP_MC_File_QueryFileWorkDataByFileReadId(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_dwFileReadId	//�ļ���ȡID
			);
		if ( pFileWorkData == NULL )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Query file work data fail.");
			goto _NPC_CLEAR;
		}

		pFileWorkData->bIfOnlySendIFrame = FALSE;		//�Ƿ�ֻ��I֡
		pFileWorkData->iDiscardIFrame = 0;				//����I֡����0������I֡��1������1��I֡�������1��I֡���䣩��2������2��I֡���������
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//����Э���¼�����ʼ�����Խ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_START			pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	NPC_BOOL										bIfLock;
	NPC_INT											iChNo = 0;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_START)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pCameraData = NULL;
		bIfLock = FALSE;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Start talk: channel no: %d.", 
			pMsgBody->i_iTalkChNo
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		if ( pMsgBody->i_iTalkChNo < 0 || pMsgBody->i_iTalkChNo >= NPC_D_DPS_MAX_CHANNEL_NUM && pMsgBody->i_iTalkChNo != NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}


		if (pMsgBody->i_iTalkChNo == NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			iChNo = NPC_D_DPS_MAX_CHANNEL_NUM;
		}
		else
		{
			iChNo = pMsgBody->i_iTalkChNo;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[iChNo]);

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);
		bIfLock = TRUE;

		pMsgBody->o_iDevAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//�豸����Ƶ����ID���μ�NPC_D_PVM_DP_UMSP_CODEC_ID_AUDIO_*����
		pMsgBody->o_iDevAudioBitRate = 64;									//�豸����Ƶ����
		pMsgBody->o_iDevAudioSampleRate = 8000;								//�豸����Ƶ������
		pMsgBody->o_iDevAudioChNum = 1;										//�豸����Ƶ������

		if ( pCameraData->bTalkIfOpen )
		{
			goto _NPC_CLEAR;
		}
		if (pMsgBody->i_iTalkChNo != NPC_D_DPS_ZERO_CHANNEL_VALUE)
		{
			//��ʼ�Խ�
			if ( !NPC_F_FILECAM_SDK_StartTalk(
				in_pMcSrvData->hFileCamera,			//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
				pMsgBody->i_iTalkChNo				//ͨ����
				) )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START NPC_F_FILECAM_SDK_StartTalk fail.");
				
				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_START_TALK_FAIL;
				goto _NPC_CLEAR;
			}
		}
		else
		{
			//��ʼ�Խ�
			if ( !NPC_F_FILECAM_SDK_StartTalk(
				in_pMcSrvData->hFileCamera,			//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
				0				//ͨ����
				) )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START NPC_F_FILECAM_SDK_StartTalk fail.");
				
				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_START_TALK_FAIL;
				goto _NPC_CLEAR;
			}
		}
		
		pCameraData->bTalkIfOpen = TRUE;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pCameraData && bIfLock )
		{
			//����
			NPC_F_THREAD_Mutex_Unlock(
				pCameraData->hWorkLock			//���������
				);
		}

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼���ֹͣ�����Խ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_STOP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP			pMsgBody;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	NPC_BOOL										bIfLock;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pCameraData = NULL;
		bIfLock = FALSE;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Stop talk: channel no: %d.", 
			pMsgBody->i_iTalkChNo
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		if ( pMsgBody->i_iTalkChNo < 0 || pMsgBody->i_iTalkChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_STOP i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[pMsgBody->i_iTalkChNo]);

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);
		bIfLock = TRUE;

		if ( !pCameraData->bTalkIfOpen )
		{
			goto _NPC_CLEAR;
		}

		//ֹͣ�Խ�
		NPC_F_FILECAM_SDK_StopTalk(
			in_pMcSrvData->hFileCamera,			//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
			pMsgBody->i_iTalkChNo				//ͨ����
			);
		pCameraData->bTalkIfOpen = FALSE;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pCameraData && bIfLock )
		{
			//����
			NPC_F_THREAD_Mutex_Unlock(
				pCameraData->hWorkLock			//���������
				);
		}

		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GUARD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	//INIT AREA
	{
		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		//NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"����");

		//in_pMcSrvData->bAlarmIfOpen = TRUE;

		//������ֱ�ӷ���Ӧ��
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_UNGUARD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	//INIT AREA
	{
		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		//NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"����");

		//in_pMcSrvData->bAlarmIfOpen = FALSE;

		//������ֱ�ӷ���Ӧ��
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//����Э���¼����޸��û�����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_USER_PWD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_USER_PWD	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_USER_PWD)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Modify user password: user name: %s.", 
			pMsgBody->i_sUserName
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		//�޸��û����룬����0��ʾ�ɹ���1���û�������2��ԭ�������9������ʧ��
		switch ( NPC_F_UMSP_MC_ModifyUserPwd(
			in_pMcSrvData,				//���ط�������
			pMsgBody->i_sUserName,		//�û���
			pMsgBody->i_sOldPwd,		//ԭ����
			pMsgBody->i_sNewPwd			//������
			) )
		{
		case 0: //0���ɹ�
			break;
		case 1: //1���û�������
			{
				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Modify user password fail, cause: user name error.");

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_USERNAME_ERROR;
			}
			break;
		case 2: //2��ԭ�������
			{
				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Modify user password fail, cause: old password error.");

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PASSWORD_ERROR;
			}
			break;
		case 9:
		default:
			{
				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Modify user password fail, cause: other error.");

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;
			}
			break;
		}
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����ȡ���ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		switch ( pMsgBody->i_iCfgFuncId )
		{
		case NPC_D_PVM_CFG_FUNCID_DEV_NAME:					//�豸����
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev name.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_IP:					//�豸����IP��ַ
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD						tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG	tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_IP				tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev ip.");

				memcpy(&tPacketData, in_pMsgDataBuf, 
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				tPacketData.tMsgHead.iMsgBodyLen = 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_IP);

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(NPC_S_PVM_IMD_CFG_DEV_IP);

				if ( in_pMcSrvData->tDevIp.sNetcardName[0] == 0 )
				{
					strcpy(in_pMcSrvData->tDevIp.sNetcardName, "eth0");			//��������
					strcpy(in_pMcSrvData->tDevIp.sMac, "28-D2-44-02-D3-17");	//����MAC��ַ����ʽΪXX-XX-

					in_pMcSrvData->tDevIp.bDhcpEnable = FALSE;					//DHCPʹ��
					strcpy(in_pMcSrvData->tDevIp.sIpaddr, "192.168.1.160");		//IP��ַ
					strcpy(in_pMcSrvData->tDevIp.sNetmask, "255.255.255.0");	//��������
					strcpy(in_pMcSrvData->tDevIp.sGateway, "192.168.1.1");		//���ص�ַ
				}
				tPacketData.tCfgBody = in_pMcSrvData->tDevIp;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_WIFI:					//�豸WIFI��Ϣ
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD						tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG	tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_WIFI				tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev wifi.");

				memcpy(&tPacketData, in_pMsgDataBuf, 
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				tPacketData.tMsgHead.iMsgBodyLen = 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_WIFI);

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(NPC_S_PVM_IMD_CFG_DEV_WIFI);

				if ( in_pMcSrvData->tDevWifi.sNetcardName[0] == 0 )
				{
					strcpy(in_pMcSrvData->tDevWifi.sNetcardName, "eth2");			//�������ƣ���ѡ��
					strcpy(in_pMcSrvData->tDevWifi.sMac, "28-D2-44-02-D3-17");		//����MAC��ַ����ѡ��Ϊ�գ���ΪĬ��WIFI����������ʽΪXX-XX-

					in_pMcSrvData->tDevWifi.bEnable = TRUE;							//�Ƿ����ã����

					strcpy(in_pMcSrvData->tDevWifi.sWifiSSID, "cchdlink");			//WIFI SSID�����
					strcpy(in_pMcSrvData->tDevWifi.sWifiPwd, "123445676789");		//WIFI���루���

					in_pMcSrvData->tDevWifi.bIfSetNetParam = TRUE;					//�Ƿ�������������������TRUE�����ã����²�����Ч��FALSE�������ã�����ԭ�������
					in_pMcSrvData->tDevWifi.bDhcpEnable = FALSE;					//DHCPʹ�ܣ���ѡ��
					strcpy(in_pMcSrvData->tDevWifi.sIpaddr, "192.168.1.22");		//IP��ַ����ѡ��
					strcpy(in_pMcSrvData->tDevWifi.sNetmask, "255.255.255.0");		//�������루��ѡ��
					strcpy(in_pMcSrvData->tDevWifi.sGateway, "192.168.1.1");		//���ص�ַ����ѡ��
				}
				tPacketData.tCfgBody = in_pMcSrvData->tDevWifi;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_GET_WIFIAP_LIST:			//��ȡWIFIAP�б�
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD						tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG	tMsgBody;
					NPC_S_PVM_IMD_CFG_GET_WIFIAP_LIST		tCfgBody;
					NPC_S_PVM_IMD_CFG_WIFIAP_INFO			tWifiApTable[5];
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: get wifiap list.");

				memcpy(&tPacketData, in_pMsgDataBuf, 
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				tPacketData.tMsgHead.iMsgBodyLen = 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_GET_WIFIAP_LIST) + 
					sizeof(NPC_S_PVM_IMD_CFG_WIFIAP_INFO) * 5;

				tPacketData.tMsgBody.io_iCfgDataLen = 
					sizeof(NPC_S_PVM_IMD_CFG_GET_WIFIAP_LIST) + 
					sizeof(NPC_S_PVM_IMD_CFG_WIFIAP_INFO) * 5;

				tPacketData.tCfgBody.iWifiApNum = 5;

				for ( NPC_INT i=0; i<5; i++ )
				{
					sprintf(tPacketData.tWifiApTable[i].sSSID, "wifissid-%d", i);		//SSID�����
					strcpy(tPacketData.tWifiApTable[i].sAuthType, "WPA2PSK");			//��ȫ���ͣ���ѡ��
					strcpy(tPacketData.tWifiApTable[i].sEncrypType, "AES");				//�������ͣ���ѡ��
					tPacketData.tWifiApTable[i].iChannel = 10 + i;						//�ŵ��ţ���ѡ��
					tPacketData.tWifiApTable[i].iRSSI = 50 + 10 * i;					//�ź�ǿ�ȣ�ֵ��ΧΪ0~100��0Ϊ�ź���ͣ�100Ϊ�ź���ǿ
				}

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_CODEC:				//��������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_CODEC pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev codec.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_CODEC) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev codec fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_CODEC)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev codec fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				*pCfgBody = pCameraData->tDevCodec;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_MOTION_DETECT:	//�ƶ���ⱨ������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm motion detect.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm motion detect fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm motion detect fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				*pCfgBody = pCameraData->tMotionDetect;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_PROBE:			//̽ͷ���뱨������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm probe.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm probe fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev alarm probe fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				*pCfgBody = pCameraData->tProbe;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_SYS_TIME:				//�豸ϵͳʱ��
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG			tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_SYS_TIME					tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev sys time.");

				memcpy(&tPacketData, in_pMsgDataBuf, 
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				tPacketData.tMsgHead.iMsgBodyLen = 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_SYS_TIME);

				tPacketData.tMsgBody.io_iCfgDataLen = 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_SYS_TIME);

				if ( in_pMcSrvData->tDevTime == 0 )
					in_pMcSrvData->tDevTime = time(NULL);

				//��time_tת��ΪNPC_S_TD_DATE_TIMEʱ��
				NPC_F_SYS_Timet_To_TdTime(
					in_pMcSrvData->tDevTime,			//ʱ��ֵ
					&tPacketData.tCfgBody.tDevTime		//TDʱ��
					);

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_INFO:					//�豸��Ϣ
			//���������Ϣ���ͻ���ͨ����¼ʱ��ȡ�豸��Ϣ
			break;
		case NPC_D_PVM_CFG_FUNCID_CH_NAME:					//ͨ������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_CH_NAME pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: ch name.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_CH_NAME) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: ch name fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_CH_NAME)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: ch name fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				strcpy(pCfgBody->sChName, pCameraData->sChName);

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_CAMERA_PARAM:				//���������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_CAMERA_PARAM pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: camera param.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_CAMERA_PARAM) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: camera param fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_CAMERA_PARAM)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: camera param fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCfgBody->bIfPictureFlip = pCameraData->bIfPictureFlip;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_RECORD_PLAN:			//¼��ƻ�����
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev record plan.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev record plan fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: dev record plan fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				*pCfgBody = pCameraData->tDevRecordPlan;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_ALARM_CLOUD_STORAGE:		//�����ƴ洢����
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: alarm cloud storate.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: alarm cloud storate fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				if ( pCfgBody->iChNo < 0 || 
					pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					pCfgBody->iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: alarm cloud storate fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				*pCfgBody = pCameraData->tAlarmCloudStorage;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					in_pMsgDataBuf,					//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					in_iMsgDataLen					//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_STORAGE_QUERY_SIZE:		//��ѯ�洢����
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG			tMsgBody;
					NPC_S_PVM_IMD_CFG_STORAGE_QUERY_SIZE			tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get config: storage query size.");

				memcpy(&tPacketData, in_pMsgDataBuf, 
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG));

				tPacketData.tMsgHead.iMsgBodyLen = 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_STORAGE_QUERY_SIZE);

				tPacketData.tMsgBody.io_iCfgDataLen = 
					sizeof(NPC_S_PVM_IMD_CFG_STORAGE_QUERY_SIZE);

				tPacketData.tCfgBody.iStorageNum = 1;

				tPacketData.tCfgBody.tStorage[0].iSerialNo = 0;
				tPacketData.tCfgBody.tStorage[0].dwStorageSize = 200;
				tPacketData.tCfgBody.tStorage[0].dwRemainSize = 100;

				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_STORAGE_FORMAT:			//��ʽ���洢��
			//���������Ϣ������Ϣ�������ò���ʹ��
			break;

		default:
			{
				//��ʾ��Ϣ
				NPC_CHAR sTempLogBuf[128];
				sprintf(sTempLogBuf, "[UMSP]  Get config: error fund id: %d.", pMsgBody->i_iCfgFuncId);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
				bRet = FALSE;
			}
			break;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}
	}
}

//����Э���¼����������ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_SET_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		switch ( pMsgBody->i_iCfgFuncId )
		{
		case NPC_D_PVM_CFG_FUNCID_DEV_NAME:					//�豸����
			//�ݲ��������Ϣ
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_IP:					//�豸����IP��ַ
			{
				PNPC_S_PVM_IMD_CFG_DEV_IP pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev ip.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_IP) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev ip fail, cause: in_iMsgDataLen error.");
					
					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_IP)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				in_pMcSrvData->tDevIp = *pCfgBody;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: sNetcardName: %s.", pCfgBody->sNetcardName);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: sMac: %s.", pCfgBody->sMac);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: bDhcpEnable: %d.", pCfgBody->bDhcpEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: sIpaddr: %s.", pCfgBody->sIpaddr);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: sNetmask: %s.", pCfgBody->sNetmask);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev ip: sGateway: %s.", pCfgBody->sGateway);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_WIFI:					//�豸WIFI��Ϣ
			{
				PNPC_S_PVM_IMD_CFG_DEV_WIFI pDevWifi;
				NPC_CHAR sTempLogBuf[256];

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev wifi.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_WIFI) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev wifi fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
					bRet = FALSE;
					break;
				}

				pDevWifi = (PNPC_S_PVM_IMD_CFG_DEV_WIFI)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				in_pMcSrvData->tDevWifi = *pDevWifi;

				//---------------------------------------------------------------------------
				//��ʾ��Ϣ
				sprintf(sTempLogBuf, "[UMSP]  Set wifi: bEnable: %d.", pDevWifi->bEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: sWifiSSID: %s.", pDevWifi->sWifiSSID);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: sWifiPwd: %s.", pDevWifi->sWifiPwd);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: bFieldEnable_AuthType: %d, sAuthType: %s.", pDevWifi->bFieldEnable_AuthType, pDevWifi->sAuthType);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: bFieldEnable_EncrypType: %d, sEncrypType: %s.", pDevWifi->bFieldEnable_EncrypType, pDevWifi->sEncrypType);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: bFieldEnable_Channel: %d, iChannel: %d.", pDevWifi->bFieldEnable_Channel, pDevWifi->iChannel);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set wifi: iRSSI: %d, iRSSI: %d.", pDevWifi->iRSSI, pDevWifi->iRSSI);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_CODEC:				//��������
			{
				PNPC_S_PVM_IMD_CFG_DEV_CODEC pCfgBody;
				PNPC_S_UMSP_CAMERA_DATA pCameraData;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev codec.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_CODEC) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev codec fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_CODEC)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev codec fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->tDevCodec = *pCfgBody;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set dev codec: iChNo: %d.", pCfgBody->iChNo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				for ( NPC_INT y=0; y<2; y++ )
				{
					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: bVideoEnable[%d]: %d.", y, pCfgBody->tCodecInfo[y].bVideoEnable);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: bAudioEnable[%d]: %d.", y, pCfgBody->tCodecInfo[y].bAudioEnable);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iCodecId[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iCodecId);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iResolution[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iResolution);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iBitRateControl[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iBitRateControl);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iBitRate[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iBitRate);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iFrameRate[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iFrameRate);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iGOP[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iGOP);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tVideoFormat.iQuality[%d]: %d.", y, pCfgBody->tCodecInfo[y].tVideoFormat.iQuality);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tAudioFormat.iCodecId[%d]: %d.", y, pCfgBody->tCodecInfo[y].tAudioFormat.iCodecId);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tAudioFormat.iBitRate[%d]: %d.", y, pCfgBody->tCodecInfo[y].tAudioFormat.iBitRate);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tAudioFormat.iSampleRate[%d]: %d.", y, pCfgBody->tCodecInfo[y].tAudioFormat.iSampleRate);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

					sprintf(sTempLogBuf, "[UMSP]  Set dev codec: tAudioFormat.iMaxVolume[%d]: %d.", y, pCfgBody->tCodecInfo[y].tAudioFormat.iMaxVolume);
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
				}
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_MOTION_DETECT:	//�ƶ���ⱨ������
			{
				PNPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT pCfgBody;
				PNPC_S_UMSP_CAMERA_DATA pCameraData;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm motion detect.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT) ) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm motion detect fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm motion detect fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->tMotionDetect = *pCfgBody;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[1024];

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iChNo: %d.", pCfgBody->iChNo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bIfEnable: %d.", pCfgBody->bIfEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Level: %d.", pCfgBody->bFuncEnable_Level);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Region: %d.", pCfgBody->bFuncEnable_Region);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Photo: %d.", pCfgBody->bFuncEnable_Photo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Record: %d.", pCfgBody->bFuncEnable_Record);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_AlarmOut: %d.", pCfgBody->bFuncEnable_AlarmOut);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Beep: %d.", pCfgBody->bFuncEnable_Beep);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "Set dev alarm: bFuncEnable_WeekSect: %d.", pCfgBody->bFuncEnable_WeekSect);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iLevel: %d.", pCfgBody->iLevel);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				if ( pCfgBody->bFuncEnable_Region )
				{
					strcpy(sTempLogBuf, "[UMSP]  Set dev alarm: dwRegion: ");
					for ( NPC_INT y=0; y<32; y++ )
					{
						sprintf(sTempLogBuf+strlen(sTempLogBuf), "0x%8.8X ", pCfgBody->dwRegion[y]);
					}
					NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
				}

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bPhotoEnable: %d.", pCfgBody->bPhotoEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bRecordEnable: %d.", pCfgBody->bRecordEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iRecordDelayedTime: %d.", pCfgBody->iRecordDelayedTime);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bAlarmOutEnable: %d.", pCfgBody->bAlarmOutEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iAlarmOutDelayedTime: %d.", pCfgBody->iAlarmOutDelayedTime);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bBeepEnable: %d.", pCfgBody->bBeepEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
				
				if ( pCfgBody->bFuncEnable_WeekSect )
				{
					for ( NPC_INT k=0; k<7; k++ )
					{
						for ( NPC_INT m=0; m<NPC_D_PVM_CFG_REC_PLAN_TIME_SECT_NUM; m++ )
						{
							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: bIfEnable[%d][%d]: %d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].bIfEnable);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: tBeginTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: tEndTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
						}
					}
				}
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_PROBE:			//̽ͷ���뱨������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm probe.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm probe fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev alarm probe fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->tProbe = *pCfgBody;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iChNo: %d.", pCfgBody->iChNo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bIfEnable: %d.", pCfgBody->bIfEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_SensorType: %d.", pCfgBody->bFuncEnable_SensorType);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Photo: %d.", pCfgBody->bFuncEnable_Photo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Record: %d.", pCfgBody->bFuncEnable_Record);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_AlarmOut: %d.", pCfgBody->bFuncEnable_AlarmOut);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_Beep: %d.", pCfgBody->bFuncEnable_Beep);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bFuncEnable_WeekSect: %d.", pCfgBody->bFuncEnable_WeekSect);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iSensorType: %d.", pCfgBody->iSensorType);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bPhotoEnable: %d.", pCfgBody->bPhotoEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bRecordEnable: %d.", pCfgBody->bRecordEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iRecordDelayedTime: %d.", pCfgBody->iRecordDelayedTime);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bAlarmOutEnable: %d.", pCfgBody->bAlarmOutEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: iAlarmOutDelayedTime: %d.", pCfgBody->iAlarmOutDelayedTime);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: bBeepEnable: %d.", pCfgBody->bBeepEnable);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
				
				if ( pCfgBody->bFuncEnable_WeekSect )
				{
					for ( NPC_INT k=0; k<7; k++ )
					{
						for ( NPC_INT m=0; m<NPC_D_PVM_CFG_REC_PLAN_TIME_SECT_NUM; m++ )
						{
							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: bIfEnable[%d][%d]: %d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].bIfEnable);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: tBeginTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev alarm: Time sect: tEndTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
						}
					}
				}
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_SYS_TIME:				//�豸ϵͳʱ��
			{
				PNPC_S_PVM_IMD_CFG_DEV_SYS_TIME pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev sys time.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_SYS_TIME)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev sys time fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_SYS_TIME)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				//��NPC_S_TD_DATE_TIMEת��Ϊtime_tʱ��
				in_pMcSrvData->tDevTime = NPC_F_SYS_TdTime_To_Timet(
					&pCfgBody->tDevTime		//TDʱ��
					);

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];
				NPC_CHAR sTempTimeStr[20];

				//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
				NPC_F_SYS_TdTime_To_TimeStr(
					&pCfgBody->tDevTime,		//TDʱ��
					sTempTimeStr				//ʱ���ַ�������ʽΪ��HH:MM:SS
					);

				sprintf(sTempLogBuf, "[UMSP]  Set dev sys time: tDevTime: %s.", sTempTimeStr);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_INFO:					//�豸��Ϣ
			//�������ò������޴���Ϣ
			break;
		case NPC_D_PVM_CFG_FUNCID_CH_NAME:					//ͨ������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_CH_NAME pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: ch name.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_CH_NAME)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: ch name fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_CH_NAME)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: ch name fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				strcpy(pCameraData->sChName, pCfgBody->sChName);

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set ch name: sChName: %s.", pCfgBody->sChName);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_CAMERA_PARAM:				//���������
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_CAMERA_PARAM pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: camera param.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_CAMERA_PARAM)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: camera param fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_CAMERA_PARAM)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: camera param fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->bIfPictureFlip = pCfgBody->bIfPictureFlip;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set camera param: bIfPictureFlip: %d.", pCfgBody->bIfPictureFlip);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_RECORD_PLAN:			//¼��ƻ�����
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev record plan.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev record plan fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: dev record plan fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->tDevRecordPlan = *pCfgBody;

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: iSerialNo: %d.", pCfgBody->iChNo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: iRecState: %d.", pCfgBody->iRecState);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: iPacketLength: %d.", pCfgBody->iPacketLength);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: iPreRecord: %d.", pCfgBody->iPreRecord);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: bOpenAudio: %d.", pCfgBody->bOpenAudio);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: iRecStream: %d.", pCfgBody->iRecStream);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: bOpenGeneral: %d.", pCfgBody->bOpenGeneral);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: bOpenCheckAlarm: %d.", pCfgBody->bOpenCheckAlarm);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: bOpenInputAlarm: %d.", pCfgBody->bOpenInputAlarm);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				//if ( pCfgBody->iRecState == 2 )
				{
					for ( NPC_INT k=0; k<7; k++ )
					{
						for ( NPC_INT m=0; m<NPC_D_PVM_CFG_REC_PLAN_TIME_SECT_NUM; m++ )
						{
							sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: Time sect: bOpenGeneral[%d][%d]: %d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].bOpenGeneral);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: Time sect: bOpenCheckAlarm[%d][%d]: %d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].bOpenCheckAlarm);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: Time sect: bOpenInputAlarm[%d][%d]: %d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].bOpenInputAlarm);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: Time sect: tBeginTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tBeginTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

							sprintf(sTempLogBuf, "[UMSP]  Set dev record plan: Time sect: tEndTime[%d][%d]: %2.2d:%2.2d:%2.2d.", 
								k, m, pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucHour, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucMin, 
								pCfgBody->tWeekSect[k].tTimeSect[m].tEndTime.ucSec);
							NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
						}
					}
				}
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_ALARM_CLOUD_STORAGE:		//�����ƴ洢����
			{
				PNPC_S_UMSP_CAMERA_DATA pCameraData;
				PNPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: alarm cloud storage.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: alarm cloud storage fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				if ( pCfgBody->iChNo < 0 || pCfgBody->iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: alarm cloud storage fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					break;
				}

				pCameraData = &in_pMcSrvData->tCameraTable[pCfgBody->iChNo];

				pCameraData->tAlarmCloudStorage = *pCfgBody;
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_STORAGE_QUERY_SIZE:		//��ѯ�洢����
			//�������ò������޴���Ϣ
			break;
		case NPC_D_PVM_CFG_FUNCID_STORAGE_FORMAT:			//��ʽ���洢��
			{
				PNPC_S_PVM_IMD_CFG_STORAGE_FORMAT pCfgBody;

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: storage format.");

				if ( in_iMsgDataLen != (NPC_INT)(
					sizeof(NPC_S_DPS_MSG_HEAD) + 
					sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG) + 
					sizeof(NPC_S_PVM_IMD_CFG_STORAGE_FORMAT)) )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Set config: storage format fail, cause: in_iMsgDataLen error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

					bRet = FALSE;
					break;
				}

				pCfgBody = (PNPC_S_PVM_IMD_CFG_STORAGE_FORMAT)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_SET_CONFIG));

				//---------------------------------------------------------------------------
				NPC_CHAR sTempLogBuf[256];

				//��ʾ��Ϣ
				sprintf(sTempLogBuf, "[UMSP]  Format storage: iSerialNo: %d.", pCfgBody->iSerialNo);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
			}
			break;

		default:
			{
				//��ʾ��Ϣ
				NPC_CHAR sTempLogBuf[128];
				sprintf(sTempLogBuf, "[UMSP]  Set config: error func id: %d.", pMsgBody->i_iCfgFuncId);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
				bRet = FALSE;
			}
			break;
		}
	}

	//CLEAR AREA
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//����Э���¼�����ȡȱʡ���ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_DEF_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		if ( in_iMsgDataLen != (NPC_INT)(
			sizeof(NPC_S_DPS_MSG_HEAD) + 
			sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG) ) )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev codec fail, cause: in_iMsgDataLen error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		switch ( pMsgBody->i_iCfgFuncId )
		{
		case NPC_D_PVM_CFG_FUNCID_DEV_NAME:					//�豸����
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev name.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_IP:					//�豸����IP��ַ
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev ip.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_WIFI:					//�豸WIFI��Ϣ
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev wifi.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_GET_WIFIAP_LIST:			//��ȡWIFIAP�б�
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: get wifiap list.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_CODEC:				//��������
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_CODEC						tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev codec.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev codec fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				//ȱʡ����Ϊģ���������Ϊ��ʾʹ��
				tPacketData.tCfgBody.iCodecNum = 2;

				//������
				tPacketData.tCfgBody.tCodecInfo[0].bVideoEnable = TRUE;					//�Ƿ�������Ƶ
				tPacketData.tCfgBody.tCodecInfo[0].bAudioEnable = FALSE;					//�Ƿ�������Ƶ

				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iResolution = NPC_D_MON_CSD_VEDIO_RESOLUTION_D1;		//�ֱ��ʣ��μ�NPC_D_MON_CSD_VEDIO_RESOLUTION_*����
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iBitRateControl = NPC_D_MON_CSD_BITRATECTRL_CBR;		//��������ģʽ���μ�NPC_D_MON_CSD_BITRATECTRL_*���壬�磺"CBR"�̶�������"VBR"�ɱ�������"MBR"�������
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iBitRate = 1024;										//��Ƶ������kbps��
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iFrameRate = 25;										//��Ƶ֡�ʣ�������ʾ����һ֡������-3��ʾ3��һ֡��ȡֵ��Χ-5~30
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iGOP = 50;												//I֡���
				tPacketData.tCfgBody.tCodecInfo[0].tVideoFormat.iQuality = 3;											//ͼ��������ֻ���ڿɱ������²������ã�ȡֵ1-6��ֵԽ��ͼ������Խ��

				tPacketData.tCfgBody.tCodecInfo[0].tAudioFormat.iCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_AUDIO_*����
				tPacketData.tCfgBody.tCodecInfo[0].tAudioFormat.iBitRate = 64;											//�����ʣ�kbps��
				tPacketData.tCfgBody.tCodecInfo[0].tAudioFormat.iSampleRate = 8000;									//������
				tPacketData.tCfgBody.tCodecInfo[0].tAudioFormat.iMaxVolume = 6;										//�������

				//������
				tPacketData.tCfgBody.tCodecInfo[1].bVideoEnable = TRUE;						//�Ƿ�������Ƶ
				tPacketData.tCfgBody.tCodecInfo[1].bAudioEnable = FALSE;					//�Ƿ�������Ƶ

				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iResolution = NPC_D_MON_CSD_VEDIO_RESOLUTION_CIF;		//�ֱ��ʣ��μ�NPC_D_MON_CSD_VEDIO_RESOLUTION_*����
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iBitRateControl = NPC_D_MON_CSD_BITRATECTRL_CBR;		//��������ģʽ���μ�NPC_D_MON_CSD_BITRATECTRL_*���壬�磺"CBR"�̶�������"VBR"�ɱ�������"MBR"�������
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iBitRate = 256;										//��Ƶ������kbps��
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iFrameRate = 12;										//��Ƶ֡�ʣ�������ʾ����һ֡������-3��ʾ3��һ֡��ȡֵ��Χ-5~30
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iGOP = 50;												//I֡���
				tPacketData.tCfgBody.tCodecInfo[1].tVideoFormat.iQuality = 3;											//ͼ��������ֻ���ڿɱ������²������ã�ȡֵ1-6��ֵԽ��ͼ������Խ��

				tPacketData.tCfgBody.tCodecInfo[1].tAudioFormat.iCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;			//��Ƶ����ID���μ�NPC_D_MON_CSD_CODEC_ID_AUDIO_*����
				tPacketData.tCfgBody.tCodecInfo[1].tAudioFormat.iBitRate = 64;											//�����ʣ�kbps��
				tPacketData.tCfgBody.tCodecInfo[1].tAudioFormat.iSampleRate = 8000;									//������
				tPacketData.tCfgBody.tCodecInfo[1].tAudioFormat.iMaxVolume = 6;										//�������

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_MOTION_DETECT:	//�ƶ���ⱨ������
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_ALARM_MOTION_DETECT		tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev alarm motion detect.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev alarm motion detect fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				//ȱʡ����Ϊģ���������Ϊ��ʾʹ��
				tPacketData.tCfgBody.bIfEnable = FALSE;						//�Ƿ������

				tPacketData.tCfgBody.bFuncEnable_Level = FALSE;				//�����Ƿ���Ч�������ȣ�TRUE�������Ȳ�������Ч��FALSE��Ϊ��Ч����ͬ��
				tPacketData.tCfgBody.bFuncEnable_Region = FALSE;				//�����Ƿ���Ч����������
				tPacketData.tCfgBody.bFuncEnable_Photo = FALSE;				//�����Ƿ���Ч������
				tPacketData.tCfgBody.bFuncEnable_Record = FALSE;				//�����Ƿ���Ч��¼��
				tPacketData.tCfgBody.bFuncEnable_AlarmOut = FALSE;				//�����Ƿ���Ч���������
				tPacketData.tCfgBody.bFuncEnable_Beep = FALSE;					//�����Ƿ���Ч������
				tPacketData.tCfgBody.bFuncEnable_WeekSect = FALSE;				//�����Ƿ���Ч�����ʱ���

				tPacketData.tCfgBody.iLevel = 5;								//������
				//tPacketData.tCfgBody.dwRegion[32];							//�������飬ÿһλΪһ���㣨0��ʾ����⣬1��ʾҪ��⣬��ߵĵ��ڵ�λ����ÿ��32λΪһ�У���һ��˫�֣�����32�У���32*32�ľ��Σ����Ը���ʵ��ͼ�����ѡ�񲿷ֵ㴦��
				tPacketData.tCfgBody.bPhotoEnable = FALSE;						//����ʹ��
				tPacketData.tCfgBody.bRecordEnable = FALSE;					//¼��ʹ��
				tPacketData.tCfgBody.iRecordDelayedTime = 5;					//¼����ʱʱ�䣨�룩
				tPacketData.tCfgBody.bAlarmOutEnable = FALSE;					//�������ʹ��
				tPacketData.tCfgBody.iAlarmOutDelayedTime = 5;					//���������ʱʱ�䣨�룩
				tPacketData.tCfgBody.bBeepEnable = FALSE;						//����ʹ��

				//���ʱ���
				/*struct _WeekSect{
					struct _TimeSect{
						NPC_BOOL							bIfEnable;						//�Ƿ�����
						NPC_S_TD_TIME						tBeginTime;						//��ʼʱ��
						NPC_S_TD_TIME						tEndTime;						//����ʱ��
					} tTimeSect[NPC_D_PVM_CFG_CHECK_TIME_SECT_NUM];
				} tWeekSect[7];*/

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_ALARM_PROBE:			//̽ͷ���뱨������
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_ALARM_PROBE				tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev alarm probe.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev alarm probe fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				//ȱʡ����Ϊģ���������Ϊ��ʾʹ��
				tPacketData.tCfgBody.bIfEnable = FALSE;							//�Ƿ������

				tPacketData.tCfgBody.bFuncEnable_SensorType = FALSE;			//�����Ƿ���Ч�����������ͣ�TRUE�����������Ͳ�������Ч��FALSE��Ϊ��Ч����ͬ��
				tPacketData.tCfgBody.bFuncEnable_Photo = FALSE;					//�����Ƿ���Ч������
				tPacketData.tCfgBody.bFuncEnable_Record = FALSE;				//�����Ƿ���Ч��¼��
				tPacketData.tCfgBody.bFuncEnable_AlarmOut = FALSE;				//�����Ƿ���Ч���������
				tPacketData.tCfgBody.bFuncEnable_Beep = FALSE;					//�����Ƿ���Ч������
				tPacketData.tCfgBody.bFuncEnable_WeekSect = FALSE;				//�����Ƿ���Ч�����ʱ���

				tPacketData.tCfgBody.iSensorType = 0;							//���������ͣ�0�����գ�1������
				tPacketData.tCfgBody.bPhotoEnable = FALSE;						//����ʹ��
				tPacketData.tCfgBody.bRecordEnable = FALSE;						//¼��ʹ��
				tPacketData.tCfgBody.iRecordDelayedTime = 5;					//¼����ʱʱ�䣨�룩
				tPacketData.tCfgBody.bAlarmOutEnable = FALSE;					//�������ʹ��
				tPacketData.tCfgBody.iAlarmOutDelayedTime = 5;					//���������ʱʱ�䣨�룩
				tPacketData.tCfgBody.bBeepEnable = FALSE;						//����ʹ��

				//���ʱ���
				/*struct _WeekSect{
					struct _TimeSect{
						NPC_BOOL							bIfEnable;						//�Ƿ�����
						NPC_S_TD_TIME						tBeginTime;						//��ʼʱ��
						NPC_S_TD_TIME						tEndTime;						//����ʱ��
					} tTimeSect[NPC_D_PVM_CFG_CHECK_TIME_SECT_NUM];
				} tWeekSect[7];*/

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_SYS_TIME:				//�豸ϵͳʱ��
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev sys time.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		case NPC_D_PVM_CFG_FUNCID_DEV_INFO:					//�豸��Ϣ
			//���������Ϣ���ͻ���ͨ����¼ʱ��ȡ�豸��Ϣ
			break;
		case NPC_D_PVM_CFG_FUNCID_CH_NAME:					//ͨ������
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_CH_NAME						tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: ch name.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: ch name fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				//ȱʡ����Ϊģ���������Ϊ��ʾʹ��
				sprintf(tPacketData.tCfgBody.sChName, "CH %2.2d", tPacketData.tMsgBody.i_iChNo);

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_CAMERA_PARAM:				//���������
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_CAMERA_PARAM					tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: camera param.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: camera param fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				//ȱʡ����Ϊģ���������Ϊ��ʾʹ��
				tPacketData.tCfgBody.bIfPictureFlip = FALSE;

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_DEV_RECORD_PLAN:			//¼��ƻ�����
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_DEV_RECORD_PLAN				tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev record plan.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				if ( tPacketData.tMsgBody.i_iChNo < 0 || 
					tPacketData.tMsgBody.i_iChNo >= NPC_D_DPS_MAX_CHANNEL_NUM || 
					tPacketData.tMsgBody.i_iChNo >= in_pMcSrvData->iChNum )
				{
					//��ʾ��Ϣ
					NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: dev record plan fail, cause: iChNo error.");

					in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;

					bRet = FALSE;
					goto _NPC_CLEAR;
				}

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				tPacketData.tCfgBody.iRecState = 0;							//¼��״̬��0���رգ�1��ʼ��¼��2������¼��

				tPacketData.tCfgBody.iPacketLength = 5;						//ÿ��¼���ļ���¼��ʱ�����Է���Ϊ��λ
				tPacketData.tCfgBody.iPreRecord = 5;						//Ԥ¼ʱ�����룩
				tPacketData.tCfgBody.bOpenAudio = FALSE;					//�Ƿ�����Ƶ¼��
				tPacketData.tCfgBody.iRecStream = 0;						//¼��������0����������1��������

				//��������������¼��״̬Ϊʼ��¼��ʱ��Ч
				tPacketData.tCfgBody.bOpenGeneral = FALSE;					//�Ƿ�������¼�񣨶�ʱ¼��
				tPacketData.tCfgBody.bOpenCheckAlarm = FALSE;				//�Ƿ�����ⱨ��¼���ƶ���������Ƶ�ڵ�����Ƶ��ʧ�ȣ�
				tPacketData.tCfgBody.bOpenInputAlarm = FALSE;				//�Ƿ������뱨��¼��ָ̽ͷ�������ȣ�

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_ALARM_CLOUD_STORAGE:		//�����ƴ洢����
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_ALARM_CLOUD_STORAGE			tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: alarm cloud storage.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				tPacketData.tCfgBody.bOpenAlarmRecord = FALSE;				//�Ƿ�������¼��
				tPacketData.tCfgBody.iPreRecordTime = 5;					//¼��Ԥ¼ʱ�����룩��ָ¼�Ʊ�������֮ǰ��N���¼��
				tPacketData.tCfgBody.iTotalRecordTime = 30;					//¼��ʱ�����룩

				tPacketData.tCfgBody.bOpenAlarmPhotos = FALSE;				//�Ƿ�����������
				tPacketData.tCfgBody.iPhotosIntervalTime = 1;				//���ռ��ʱ�䣨���룩
				tPacketData.tCfgBody.iPhotosPicNum = 10;					//��������

				//-------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
					(PNPC_BYTE)&tPacketData,		//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)				//�豸Э�����ݳ���
					);
			}
			break;

		case NPC_D_PVM_CFG_FUNCID_STORAGE_QUERY_SIZE:		//��ѯ�洢����
			{
				struct _PacketData{
					NPC_S_DPS_MSG_HEAD								tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG		tMsgBody;
					NPC_S_PVM_IMD_CFG_STORAGE_QUERY_SIZE			tCfgBody;
				} tPacketData = {0};

				//��ʾ��Ϣ
				NPC_F_LOG_SR_ShowInfo("[UMSP]  Get default config: storage query size.");

				memcpy(&tPacketData, in_pMsgDataBuf, in_iMsgDataLen);

				tPacketData.tMsgHead.iMsgBodyLen = sizeof(tPacketData) - sizeof(NPC_S_DPS_MSG_HEAD);
				tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

				tPacketData.tMsgBody.io_iCfgDataLen = sizeof(tPacketData) - 
					sizeof(NPC_S_DPS_MSG_HEAD) - sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_GET_DEF_CONFIG);

				//--------------------------------------------------------------------------------
				tPacketData.tCfgBody.iStorageNum = 1;

				tPacketData.tCfgBody.tStorage[0].iSerialNo = 0;
				tPacketData.tCfgBody.tStorage[0].dwStorageSize = 200;
				tPacketData.tCfgBody.tStorage[0].dwRemainSize = 100;

				//--------------------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tPacketData)					//�豸Э�����ݳ���
					);
			}
			break;
		case NPC_D_PVM_CFG_FUNCID_STORAGE_FORMAT:			//��ʽ���洢��
			//���������Ϣ������Ϣ�������ò���ʹ��
			break;

		default:
			{
				//��ʾ��Ϣ
				NPC_CHAR sTempLogBuf[128];
				sprintf(sTempLogBuf, "[UMSP]  Get default config: error fund id: %d.", pMsgBody->i_iCfgFuncId);
				NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
				bRet = FALSE;
			}
			break;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}
	}
}

//����Э���¼�����������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_IMP_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG		pMsgBody;
	PNPC_CHAR										pCfgPos;
	NPC_INT											iCfgLen;

	pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
	pCfgPos = (PNPC_CHAR)(pMsgBody + 1);
	iCfgLen = in_iMsgDataLen - (NPC_INT)(
		sizeof(NPC_S_DPS_MSG_HEAD) + 
		sizeof(NPC_S_DPS_MSG_BODY_EVENT_E3_IEC_IMP_CONFIG) );

	in_pMsgHead->ucResult = 0;
	in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

	if ( iCfgLen <= 0 )
	{
		in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;
	}
	else
	{
		if ( iCfgLen > sizeof(in_pMcSrvData->sImportCfgBuf) - 1 )
			iCfgLen = sizeof(in_pMcSrvData->sImportCfgBuf) - 1;

		memcpy(in_pMcSrvData->sImportCfgBuf, pCfgPos, iCfgLen);
		in_pMcSrvData->sImportCfgBuf[iCfgLen] = 0;
	}

	//������Ϣ���豸Э���������
	NPC_F_DPS_SendDevProData(
		in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
		in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
		in_iMsgDataLen						//�豸Э�����ݳ���
		);
}

//����Э���¼�����������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_EXP_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG		pMsgBody;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataBufSize;
	NPC_INT											iSendDataLen;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG		pSendMsgBody;
	
	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pSendDataBuf = NULL;
		iSendDataBufSize = 0;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		//�򻺳����������
		if ( !NPC_F_MEM_MG_AddDataToBuf(
			&pSendDataBuf,				//���ݻ�����ָ��
			&iSendDataBufSize,			//���ݻ�������С
			&iSendDataLen,				//ʵ�����ݳ���
			in_pMsgDataBuf,				//�������ָ��
			in_iMsgDataLen				//������ݳ���
			) )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		if ( in_pMcSrvData->sImportCfgBuf[0] == 0 )
			strcpy(in_pMcSrvData->sImportCfgBuf, "{\"config\": \"data\"}");

		//�򻺳����������
		if ( !NPC_F_MEM_MG_AddDataToBuf(
			&pSendDataBuf,									//���ݻ�����ָ��
			&iSendDataBufSize,								//���ݻ�������С
			&iSendDataLen,									//ʵ�����ݳ���
			(PNPC_BYTE)(in_pMcSrvData->sImportCfgBuf),		//�������ָ��
			strlen(in_pMcSrvData->sImportCfgBuf)			//������ݳ���
			) )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;
		pSendMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_IEC_EXP_CONFIG)((PNPC_BYTE)pSendMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		pSendMsgBody->o_iCfgDataLen = strlen(in_pMcSrvData->sImportCfgBuf);

		//--------------------------------------------------------------------
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEARA REA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}
}


//����Э���¼�����ѯ������Ϣ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_QUERY_NET_INFO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO		pMsgBody;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataBufSize;
	NPC_INT											iSendDataLen;

	NPC_S_DPS_MSG_BODY_EVENT_E3_NET_CARD_INFO		tNetCardInfo = {0};
	NPC_CHAR										sCfgFileName[256];
	NPC_CHAR										sKeyName[128];
	NPC_CHAR										sKeyValue[128];
	NPC_INT											i, iNetCardNum;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO		pSendMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pSendDataBuf = NULL;
		iSendDataBufSize = 0;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Query network info");

		//--------------------------------------------------------------------
		//�򻺳����������
		if ( !NPC_F_MEM_MG_AddDataToBuf(
			&pSendDataBuf,				//���ݻ�����ָ��
			&iSendDataBufSize,			//���ݻ�������С
			&iSendDataLen,				//ʵ�����ݳ���
			in_pMsgDataBuf,				//�������ָ��
			in_iMsgDataLen				//������ݳ���
			) )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		//--------------------------------------------------------------------
		strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

		//������
		iNetCardNum = GetPrivateProfileInt("NET", "NetCardNum", 0, sCfgFileName);

		for ( i=0; i<iNetCardNum; i++ )
		{
			memset(&tNetCardInfo, 0, sizeof(tNetCardInfo));

			//��������
			sprintf(sKeyName, "NetCardName[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", tNetCardInfo.sNetCardName, sizeof(tNetCardInfo.sNetCardName), sCfgFileName);

			//MAC��ַ
			sprintf(sKeyName, "Mac[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", sKeyValue, sizeof(sKeyValue), sCfgFileName);

			//���ַ���MAC��ַת���ɶ�����MAC��ַ
			NPC_F_SYS_GetBitMacAddr(
				sKeyValue,				//�ַ���MAC��ַ
				tNetCardInfo.sMac		//������MAC��ַ
				);

			//�Ƿ��DHCP�����ΪTRUE�����������������Ч
			sprintf(sKeyName, "IfOpenDhcp[%d]", i);
			tNetCardInfo.bIfOpenDhcp = GetPrivateProfileInt("NET", sKeyName, 0, sCfgFileName);

			//IP��ַ
			sprintf(sKeyName, "Ipaddr[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", tNetCardInfo.sIpaddr, sizeof(tNetCardInfo.sIpaddr), sCfgFileName);

			//��������
			sprintf(sKeyName, "Submask[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", tNetCardInfo.sSubmask, sizeof(tNetCardInfo.sSubmask), sCfgFileName);

			//���ص�ַ
			sprintf(sKeyName, "Gateway[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", tNetCardInfo.sGateway, sizeof(tNetCardInfo.sGateway), sCfgFileName);

			//�򻺳����������
			if ( !NPC_F_MEM_MG_AddDataToBuf(
				&pSendDataBuf,					//���ݻ�����ָ��
				&iSendDataBufSize,				//���ݻ�������С
				&iSendDataLen,					//ʵ�����ݳ���
				(PNPC_BYTE)&tNetCardInfo,		//�������ָ��
				sizeof(tNetCardInfo)			//������ݳ���
				) )
			{
				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;

				bRet = FALSE;
				goto _NPC_CLEAR;
			}
		}

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;
		pSendMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_QUERY_NET_INFO)((PNPC_BYTE)pSendMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		pSendMsgBody->o_iNetCardNum = iNetCardNum;

		//--------------------------------------------------------------------
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}

		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}
}

//����Э���¼����޸������ַ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_NET_ADDR(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_NET_ADDR	pMsgBody;

	NPC_CHAR										sCfgFileName[256];
	NPC_CHAR										sKeyName[128];
	NPC_CHAR										sKeyValue[128];
//	NPC_BYTE										sTempMac[6];
	NPC_INT											i, iNetCardNum, iFindIndex;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_MODIFY_NET_ADDR)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Modify net addr: net card name: %s.", 
			pMsgBody->i_sNetCardName
			);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		//--------------------------------------------------------------------
		strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

		//������
		iNetCardNum = GetPrivateProfileInt("NET", "NetCardNum", 0, sCfgFileName);

		iFindIndex = -1;
		for ( i=0; i<iNetCardNum; i++ )
		{
			//��������
			sprintf(sKeyName, "NetCardName[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", sKeyValue, sizeof(sKeyValue), sCfgFileName);

			if ( strcmp(sKeyValue, pMsgBody->i_sNetCardName) != 0 )
			{
				continue;
			}
/*
			//MAC��ַ
			sprintf(sKeyName, "Mac[%d]", i);
			GetPrivateProfileString("NET", sKeyName, "", sKeyValue, sizeof(sKeyValue), sCfgFileName);

			//���ַ���MAC��ַת���ɶ�����MAC��ַ
			NPC_F_SYS_GetBitMacAddr(
				sKeyValue,				//�ַ���MAC��ַ
				sTempMac				//������MAC��ַ
				);

			if ( memcmp(sTempMac, pMsgBody->i_sMac, 6) != 0 )
			{
				continue;
			}
*/
			iFindIndex = i;
			break;
		}

		if ( iFindIndex == -1 )
		{
			//��ʾ��Ϣ
			NPC_F_LOG_SR_ShowInfo("[UMSP]  Modify net addr fail, cause: No corresponding network card was found..");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_EXIST;
			goto _NPC_CLEAR;
		}

		//--------------------------------------------------------------------
		//�Ƿ��DHCP�����ΪTRUE�����������������Ч
		sprintf(sKeyName, "IfOpenDhcp[%d]", iFindIndex);
		sprintf(sKeyValue, "%d", pMsgBody->i_bIfOpenDhcp);
		WritePrivateProfileString("NET", sKeyName, sKeyValue, sCfgFileName);

		//IP��ַ
		sprintf(sKeyName, "Ipaddr[%d]",iFindIndex);
		WritePrivateProfileString("NET", sKeyName, pMsgBody->i_sIpaddr, sCfgFileName);

		//��������
		sprintf(sKeyName, "Submask[%d]", iFindIndex);
		WritePrivateProfileString("NET", sKeyName, pMsgBody->i_sSubmask, sCfgFileName);

		//���ص�ַ
		sprintf(sKeyName, "Gateway[%d]", iFindIndex);
		WritePrivateProfileString("NET", sKeyName, pMsgBody->i_sGateway, sCfgFileName);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//-----------------------------------------------------------------------------------
//�򿪴���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_OPEN(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_OPEN			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_OPEN)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Open com: com type: %d, port no: %d.", 
			pMsgBody->i_iComType, pMsgBody->i_iPortNo);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//�رմ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_CLOSE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_CLOSE			pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_CLOSE)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Close com: com type: %d, port no: %d.", 
			pMsgBody->i_iComType, pMsgBody->i_iPortNo);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//��������(�ͻ��˷��͸��豸��)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SEND_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_SEND_DATA		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_COM_SEND_DATA)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Client send com data: com type: %d, port no: %d, data len: %d.", 
			pMsgBody->i_iComType, pMsgBody->i_iPortNo, pMsgBody->i_iDataLen);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//�豸��������(�豸�˷��͸��ͻ���)(��Ӧ��)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SUBS_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
}


//-----------------------------------------------------------------------------------
//�����û�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_ADD_USER(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_ADD_USER		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_ADD_USER)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Add user: user name: %s, user pwd: %s.", 
			pMsgBody->i_sUserName, pMsgBody->i_sUserPwd);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//ɾ���û�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_DEL_USER(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_DEL_USER		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_DEL_USER)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Add user: user name: %s.", 
			pMsgBody->i_sUserName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//��ȡ�û�Ȩ���б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_GET_USER_POP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_GET_USER_POP	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_GET_USER_POP)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Get user pop: user name: %s.", 
			pMsgBody->i_sUserName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//�����û�Ȩ���б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_SET_USER_POP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_SET_USER_POP	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E3_UNS_SET_USER_POP)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[256];
		sprintf(sTempLogBuf, "[UMSP]  Set user pop: user name: %s.", 
			pMsgBody->i_sUserName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//-----------------------------------------------------------------------------------
//���ƹ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_CUSTOM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_BYTE										pCusBodyPos;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM);

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		switch ( pMsgBody->i_iCusFuncId )
		{
		case NPC_D_DPS_CUSTOM_NI_FUNCID_QUERY_MP3_FILE_LIST:			//��ѯMP3�ļ��б�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_QUERY_MP3_FILE_LIST(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_DELETE_MP3_FILE:				//ɾ��MP3�ļ�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_DELETE_MP3_FILE(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_START_PLAY_MP3_FILE:			//��ʼ����MP3�ļ�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_START_PLAY_MP3_FILE(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_STOP_PLAY_MP3_FILE:				//ֹͣ����MP3�ļ�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_STOP_PLAY_MP3_FILE(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_CTRL_VOLUME:					//��������
			bRet = NPC_F_UMSP_MC_DoCustomEvent_CTRL_VOLUME(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_START_UPLOAD_MP3_FILE:			//��ʼ�ϴ��ļ�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_START_UPLOAD_MP3_FILE(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_STOP_UPLOAD_MP3_FILE:			//ֹͣ�ϴ��ļ�
			bRet = NPC_F_UMSP_MC_DoCustomEvent_STOP_UPLOAD_MP3_FILE(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		case NPC_D_DPS_CUSTOM_NI_FUNCID_UPLOAD_FILE_DATA:				//�ϴ��ļ�����
			bRet = NPC_F_UMSP_MC_DoCustomEvent_UPLOAD_FILE_DATA(in_pMcSrvData, in_pMsgHead, in_pMsgDataBuf, in_iMsgDataLen);
			break;
		default:
			bRet = FALSE;
			break;
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		if ( !bRet )
		{
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;

			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}
	}
}


//-----------------------------------------------------------------------------------
//��ѯ������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_QUERY_ABILITY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Query ability");

		switch ( pMsgBody->i_iRequVerNo )
		{
		case 1:
			{
				struct _AbPacket{
					NPC_S_DPS_MSG_HEAD tMsgHead;
					NPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY tMsgBody;
					NPC_S_PVM_IMD_CFG_ABILITY_HEAD tCfgHead;
					NPC_S_PVM_IMD_CFG_ABILITY_DATA_V1 tCfgBody;
				} tAbPacket = {0};

				//-------------------------------------------------------------------
				memcpy(&tAbPacket, in_pMsgDataBuf, sizeof(NPC_S_DPS_MSG_HEAD) + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_RMY_QUERY_ABILITY));

				tAbPacket.tMsgHead.iMsgBodyLen = sizeof(tAbPacket) - sizeof(NPC_S_DPS_MSG_HEAD);

				tAbPacket.tMsgBody.o_iAbilityDataLen = sizeof(NPC_S_PVM_IMD_CFG_ABILITY_HEAD) + sizeof(NPC_S_PVM_IMD_CFG_ABILITY_DATA_V1);

				//-------------------------------------------------------------------
				tAbPacket.tCfgHead.usAbVerNo = pMsgBody->i_iRequVerNo;							//�������汾��
				tAbPacket.tCfgHead.usAbDataLen = sizeof(NPC_S_PVM_IMD_CFG_ABILITY_DATA_V1);		//���������ݳ���

				tAbPacket.tCfgBody.tNet.bIfCableNet = TRUE;						//�Ƿ�����������
				tAbPacket.tCfgBody.tNet.bIfWifiNet = FALSE;						//�Ƿ���WIFI����

				//-------------------------------------------------------------------
				tAbPacket.tCfgBody.iCodecSchemeNum = 1;							//���뷽����

				tAbPacket.tCfgBody.tCodecScheme[0].bSupportAudio = TRUE;		//�Ƿ�֧����Ƶ
				tAbPacket.tCfgBody.tCodecScheme[0].iStreamNum = 2;				//�����������5��

				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucVedioCodecTable[0] = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;			//��Ƶ�����б����ֵΪ0��ʾ������ڣ��μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucResolutionTable[0] = NPC_D_MON_CSD_VEDIO_RESOLUTION_720P;		//�ֱ����б����ֵΪ0��ʾ������ڣ��μ�NPC_D_MON_CSD_VEDIO_RESOLUTION_*����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucResolutionTable[1] = NPC_D_MON_CSD_VEDIO_RESOLUTION_D1;
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].usBitRateStart = 128;					//��Ƶ������Χ��ʼ��kbps��
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].usBitRateEnd = 4096;					//��Ƶ������Χ������kbps��
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucFrameRateStart = 2;					//��Ƶ֡�ʷ�Χ��ʼ
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucFrameRateEnd = 25;					//��Ƶ֡�ʷ�Χ����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucGOPStart = 2;						//I֡�����Χ��ʼ
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[0].ucGOPEnd = 100;						//I֡�����Χ����

				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucVedioCodecTable[0] = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;		//��Ƶ�����б����ֵΪ0��ʾ������ڣ��μ�NPC_D_MON_CSD_CODEC_ID_VEDIO_*����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucResolutionTable[0] = NPC_D_MON_CSD_VEDIO_RESOLUTION_VGA;		//�ֱ����б����ֵΪ0��ʾ������ڣ��μ�NPC_D_MON_CSD_VEDIO_RESOLUTION_*����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucResolutionTable[1] = NPC_D_MON_CSD_VEDIO_RESOLUTION_CIF;
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].usBitRateStart = 128;					//��Ƶ������Χ��ʼ��kbps��
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].usBitRateEnd = 1024;					//��Ƶ������Χ������kbps��
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucFrameRateStart = 2;					//��Ƶ֡�ʷ�Χ��ʼ
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucFrameRateEnd = 25;					//��Ƶ֡�ʷ�Χ����
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucGOPStart = 2;						//I֡�����Χ��ʼ
				tAbPacket.tCfgBody.tCodecScheme[0].tSubCh[1].ucGOPEnd = 100;						//I֡�����Χ����

				tAbPacket.tCfgBody.tCodecScheme[0].ucUseChTable[0] = 0;				//����ͨ����
				tAbPacket.tCfgBody.tCodecScheme[0].ucUseChTable[1] = 1;				//����ͨ����
				tAbPacket.tCfgBody.tCodecScheme[0].ucUseChTable[2] = 2;				//����ͨ����
				tAbPacket.tCfgBody.tCodecScheme[0].ucUseChTable[3] = 3;				//����ͨ����
				tAbPacket.tCfgBody.tCodecScheme[0].iUseChNum = 4;					//����ͨ����

				//-------------------------------------------------------------------
				tAbPacket.tCfgBody.tAlarm.bMotionDetect = TRUE;						//�Ƿ�֧���ƶ����
				tAbPacket.tCfgBody.tAlarm.bProbeInput = TRUE;						//�Ƿ�֧��̽ͷ����
				tAbPacket.tCfgBody.tAlarm.bBlindDetect = TRUE;						//�Ƿ�֧����Ƶ�ڵ����
				tAbPacket.tCfgBody.tAlarm.bLossDetect = TRUE;						//�Ƿ�֧����Ƶ��ʧ���

				//-------------------------------------------------------------------
				//������Ϣ���豸Э���������
				NPC_F_DPS_SendDevProData(
					in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
					(PNPC_BYTE)&tAbPacket,				//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
					sizeof(tAbPacket)					//�豸Э�����ݳ���
					);
			}
			break;
		default:
			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP;
			bRet = FALSE;
			break;
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//������Ϣ���豸Э���������
			NPC_F_DPS_SendDevProData(
				in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
				in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
				in_iMsgDataLen						//�豸Э�����ݳ���
				);
		}
	}
}

//�����豸(�ް���)(��Ӧ����Ϣ)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_REBOOT(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	//��ʾ��Ϣ
	NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Reboot");
}

//ֹͣ�豸(�ް���)(��Ӧ����Ϣ)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_STOP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	//��ʾ��Ϣ
	NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Stop");
}



//-----------------------------------------------------------------------------------
//��ѯ�豸�汾��Ϣ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_DEV_VER_INFO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_DEV_VER_INFO	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_DEV_VER_INFO)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Query dev ver info");

		pMsgBody->o_usModuleType[0] = 3;				//ģ������,0:δ֪����,1:UI,2:SYS,3:UI&SYS
		pMsgBody->o_uiModuleVerNo[0] = 0x00000102;		//ģ��汾��,��˳���Ӧģ������,��ʽΪ:x.x.x.x,ÿ�ֽ�Ϊһ����
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//��������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_REQU_UPGRADE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_REQU_UPGRADE		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_REQU_UPGRADE)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Request upgrade");

		pMsgBody->o_uiUpgradeId = 44444;					//����ID
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//��ѯ��������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_PROGRESS(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_PROGRESS		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_PROGRESS)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Query upgrade progress");

		pMsgBody->o_iUpgProgress = 40;
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//��ѯ����λ��
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_TRANS_POS(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_TRANS_POS	pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_QUERY_TRANS_POS)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Query trans pos");

		pMsgBody->o_iTransPos = 4000;
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}

//�������ݰ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_UPGRADE_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL											bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_UPGRADE_DATA		pMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_DUP_UPGRADE_DATA)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo((PNPC_CHAR)"[UMSP]  Upgrade data");
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}
}


//-----------------------------------------------------------------------------------
//����Э���¼�����Ƶ֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_MEDIA_E8_AUDIO_FRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME		pMsgBody;
	PNPC_BYTE										pMediaDataPos;
	NPC_INT											iMediaDataLen;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	NPC_BOOL										bIfLock;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pMediaDataPos = (PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME);
		iMediaDataLen = in_iMsgDataLen - (
			sizeof(NPC_S_DPS_MSG_HEAD) + 
			sizeof(NPC_S_DPS_MSG_BODY_MEDIA_E8_AUDIO_FRAME) );

		in_pMsgHead->ucResult = 0;
		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;

		pCameraData = NULL;
		bIfLock = FALSE;
	}

	//CODE AREA
	{
		//printf("iMediaDataLen: %d\n", iMediaDataLen);

		/*if ( iMediaDataLen != 160 )
		{
			printf("iMediaDataLen: %d,  MediaData: %2.2x %2.2x %2.2x %2.2x \n", 
				iMediaDataLen, 
				pMediaDataPos[0], 
				pMediaDataPos[1], 
				pMediaDataPos[2], 
				pMediaDataPos[3]
				);

			FILE* f;
			NPC_CHAR sFileName[128];
			static int iFileNo = 0;

			sprintf(sFileName, "d:\\audio%d.pcm", iFileNo++);
			f = fopen(sFileName, "wb");
			if ( f )
			{
				fwrite(pMediaDataPos, 1, iMediaDataLen, f);

				fclose(f);
				f = NULL;
			}
		}

		{
			static FILE* f = fopen("d:\\audio_kkkkkkkkkkk.pcm", "wb");

			if ( f )
			{
				fwrite(pMediaDataPos, 1, iMediaDataLen, f);
			}
		}*/

		if ( iMediaDataLen <= 0 )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_MEDIA_E8_AUDIO_FRAME iMediaDataLen <= 0.");
			return;
		}

		//--------------------------------------------------------------------
		if ( pMsgBody->i_usChNo < 0 || pMsgBody->i_usChNo >= NPC_D_DPS_MAX_CHANNEL_NUM )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_DoProEvent_MEDIA_E8_AUDIO_FRAME i_iChNo error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR;
			goto _NPC_CLEAR;
		}

		pCameraData = &(in_pMcSrvData->tCameraTable[pMsgBody->i_usChNo]);

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);
		bIfLock = TRUE;

		if ( pCameraData->bTalkIfOpen )
		{
			//����Խ���Ƶ����
			NPC_F_FILECAM_SDK_InputTalkAudioData(
				in_pMcSrvData->hFileCamera,				//�ļ�������������NPC_F_FILECAM_SDK_ConnectFilecam��������
				pMsgBody->i_usChNo,						//ͨ����
				pMediaDataPos,							//��Ƶ���ݻ�����
				iMediaDataLen							//��Ƶ���ݳ���
				);
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pCameraData && bIfLock )
		{
			//����
			NPC_F_THREAD_Mutex_Unlock(
				pCameraData->hWorkLock			//���������
				);
		}
	}
}


//-----------------------------------------------------------------------------------
//���֡���ͣ�����֡���ͣ�0��δ��⵽��1��I֡��2��P֡
NPC_INT		NPC_F_UMSP_MC_CheckFrameType(
	IN		PNPC_BYTE								in_pFrameDataBuf,			//֡���ݻ�����
	IN		NPC_INT									in_iFrameDataLen			//֡���ݳ���
	)
{
	PNPC_BYTE										pFindPos;
	PNPC_BYTE										pEndPos;
	NPC_BYTE										forbidden_zero_bit;
    NPC_BYTE										nal_ref_idc;
	NPC_BYTE										nal_unit_type;

	pFindPos = in_pFrameDataBuf;
	pEndPos = in_pFrameDataBuf + in_iFrameDataLen - 4;

	while ( pFindPos < pEndPos )
	{
		if ( *(PNPC_DWORD)pFindPos == 0x01000000 )
		{
			pFindPos += 4;
			
			forbidden_zero_bit = (*pFindPos & 0x80) >> 7;
			nal_ref_idc = (*pFindPos & 0x60) >> 5;
			nal_unit_type = (*pFindPos & 0x1F);

			switch ( nal_unit_type )
			{
			case 5:
			case 7:
			case 8:
				return 1; //1��I֡
			case 1:
				return 2; //2��P֡
			default:
				break;
			}
		}

		pFindPos++;
	}

	return 0;
}


//-----------------------------------------------------------------------------------
//��ʼ¼��
NPC_BOOL	NPC_F_UMSP_MC_StartRecord(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData,				//���������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iFrameRate				//֡��
	)
{
	NPC_CHAR										sRecFileName[256];
	NPC_CHAR										sTempTimeStr[20];
	NPC_CHAR										sCurTimeStr[20];
	NPC_S_NAV_AV_FORMAT								tAvFormat = {0};

	in_pCameraData->tRecStartTime = time(NULL);

	//��time_t���͵�ʱ�䣬��ʽ��ΪYYYY-MM-DD HH24:MI:SS�͵��ַ���
	NPC_F_SYS_Time_To_Str(
		in_pCameraData->tRecStartTime,		//ʱ��ֵ
		sTempTimeStr						//ʱ���ַ���
		);

	strftime(sCurTimeStr, 20, "%Y%m%d%H%M%S", localtime(&in_pCameraData->tRecStartTime));

	sprintf(sRecFileName, ".\\rec\\REC_%d_%s.nav", in_iChNo, sCurTimeStr);

	tAvFormat.bVedioFlag = TRUE;							//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ
	tAvFormat.bAudioFlag = FALSE;							//��Ƶ��־��TRUE��ʾ����Ƶ��FALSE��ʾû����Ƶ

	tAvFormat.iVedioCodecId = 1;							//��Ƶ���������0��Ĭ�ϱ��룬1��H264��2��MPEG4��3��H263������
	tAvFormat.usVedioWidth = 352;							//��Ƶ���
	tAvFormat.usVedioHeight = 288;							//��Ƶ�߶�
	tAvFormat.iVedioBitRate = 128;							//��Ƶ���ʲ�����0��ʾΪĬ������
	tAvFormat.iVedioFrameRate = in_iFrameRate;				//��Ƶ֡�ʲ�����0��ʾΪĬ��֡��

	//����NAV�ļ�
	in_pCameraData->hNavFile = NPC_F_NAV_CreateFile(
		sRecFileName,				//�ļ���
		1008,						//�豸����
		0,							//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
		&tAvFormat,					//¼���ʽ
		1000,						//ʱ����ο�ֵ��Ĭ��Ϊ90000
		sTempTimeStr				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
		);
	if ( in_pCameraData->hNavFile == NULL )
	{
		return FALSE;
	}

	return TRUE;
}

//ֹͣ¼��
NPC_VOID	NPC_F_UMSP_MC_StopRecord(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData				//���������
	)
{
	if ( in_pCameraData->hNavFile )
	{
		time_t tCurTime;
		NPC_CHAR sCurTimeStr[20];
		time_t dwRecTimeLen;

		tCurTime = time(NULL);

		//��time_t���͵�ʱ�䣬��ʽ��ΪYYYY-MM-DD HH24:MI:SS�͵��ַ���
		NPC_F_SYS_Time_To_Str(
			tCurTime,			//ʱ��ֵ
			sCurTimeStr			//ʱ���ַ���
			);

		dwRecTimeLen = tCurTime - in_pCameraData->tRecStartTime;

		//�����ļ�ͷ��Ϣ
		NPC_F_NAV_UpdateFileHead_RecEndTime(
			in_pCameraData->hNavFile,		//NAV�ļ����
			sCurTimeStr,					//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
			dwRecTimeLen					//¼��ʱ�����룩
			);

		//�ر�NAV�ļ�
		NPC_F_NAV_CloseFile(
			in_pCameraData->hNavFile				//NAV�ļ����
			);
		in_pCameraData->hNavFile = NULL;
	}
}


//-----------------------------------------------------------------------------------
//��ѯ�ļ�
NPC_BOOL	NPC_F_UMSP_MC_FindFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		PNPC_S_TD_DATE_TIME						in_pStartTime,				//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME						in_pEndTime,				//����ʱ��
	OUT		PNPC_INT								out_pFileNum,				//�ļ���
	OUT		PNPC_BYTE*								out_ppFileInfoDataBuf,		//�ļ���Ϣ���ݻ�����
	OUT		PNPC_INT								out_pFileInfoDataBufSize,	//�ļ���Ϣ���ݻ�������С
	OUT		PNPC_INT								out_pFileInfoDataLen		//�ļ���Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	HANDLE											hFind;
	WIN32_FIND_DATA									tFindFileData;
	NPC_CHAR										sFindPath[MAX_PATH];
	NPC_CHAR										TempFilePath[MAX_PATH];

	NPC_CHAR										sBeginTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	NPC_CHAR										sBeginFileNameStr[128];
	NPC_CHAR										sEndFileNameStr[128];

	NPC_S_NAV_AV_FORMAT						tAvFormat;
	NPC_S_MON_MPS_FILE_INFO							tFileInfo;
	NPC_DWORD										dwRecTimeLen;
	NPC_INT											iFileNum;

	//INIT AREA
	{
		bRet = TRUE;
		hFind = INVALID_HANDLE_VALUE;
		*out_pFileNum = 0;
		*out_pFileInfoDataLen = 0;
		iFileNum = 0;
	}

	//CODE AREA
	{
		sprintf(sBeginTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pStartTime->usYear,						//��
			in_pStartTime->usMonth,						//��
			in_pStartTime->ucDay,						//��
			in_pStartTime->ucHour,						//ʱ
			in_pStartTime->ucMinute,					//��
			in_pStartTime->ucSecond						//��
			);

		sprintf(sEndTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pEndTime->usYear,						//��
			in_pEndTime->usMonth,						//��
			in_pEndTime->ucDay,							//��
			in_pEndTime->ucHour,						//ʱ
			in_pEndTime->ucMinute,						//��
			in_pEndTime->ucSecond						//��
			);

		sprintf(sFindPath, ".\\rec\\REC_%d_*.nav", in_iChNo);

		sprintf(sBeginFileNameStr, "REC_%d_%s.nav", in_iChNo, sBeginTimeStr);
		sprintf(sEndFileNameStr, "REC_%d_%s.nav", in_iChNo, sEndTimeStr);

		hFind = FindFirstFile(sFindPath, &tFindFileData);

		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			do{
				if ( !(tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
				{
					if ( strcmp(tFindFileData.cFileName, sBeginFileNameStr) >= 0 && 
						strcmp(tFindFileData.cFileName, sEndFileNameStr) <= 0 )
					{
						sprintf(TempFilePath, ".\\rec\\%s", tFindFileData.cFileName);

						//��ȡ¼���ļ���Ϣ
						if ( !NPC_F_UMSP_MC_ReadRecFileInfo(
							TempFilePath,				//�ļ���������·��
							&tAvFormat,					//�ļ���ʽ
							sBeginTimeStr,				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							sEndTimeStr,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							&dwRecTimeLen				//¼��ʱ�����룩
							) )
						{
							//��ʾ��Ϣ
							NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: Failed to read the video file information.");

							bRet = FALSE;
							goto _NPC_CLEAR;
						}

						//--------------------------------------------------------------------
						if ( dwRecTimeLen > 0 )
						{
							memset(&tFileInfo, 0, sizeof(tFileInfo));

							strcpy(tFileInfo.sFileFlag, tFindFileData.cFileName);			//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
							tFileInfo.iFileType = NPC_D_MON_CSD_FILE_TYPE_RECORD;			//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
							tFileInfo.iCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
							tFileInfo.iAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_ALL;			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_DPS_FILE_CREATE_MODE_ALARMʱ��Ч
							tFileInfo.dwFileSize = tFindFileData.nFileSizeLow / 1024;		//�ļ���С����λ��KB��

							//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
							NPC_F_SYS_StrTime_To_TdTime(
								sBeginTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tStartTime			//TDʱ��
								);

							NPC_F_SYS_StrTime_To_TdTime(
								sEndTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tEndTime				//TDʱ��
								);

							tFileInfo.dwFileTimeLen = dwRecTimeLen;

							tFileInfo.bVideoFlag = tAvFormat.bVedioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
							tFileInfo.bAudioFlag = tAvFormat.bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
							tFileInfo.bPictureFlag = 0;										//ͼƬ��־��TRUE����ʾΪͼƬ��FALSE����ʾ����ͼƬ������ò���TRUE��������Ƶ������Ч

							tFileInfo.iVideoCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
							tFileInfo.iVideoFrameRate = tAvFormat.iVedioFrameRate;			//��Ƶ֡��
							tFileInfo.iVideoBitRate = tAvFormat.iVedioBitRate;				//��Ƶ���ʣ�kbps��
							tFileInfo.usVideoWidth = tAvFormat.usVedioWidth;				//��Ƶ���
							tFileInfo.usVideoHeight = tAvFormat.usVedioHeight;				//��Ƶ�߶�

							tFileInfo.iAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
							tFileInfo.iAudioBitRate = 64;									//��Ƶ����
							tFileInfo.iAudioSampleRate = tAvFormat.iAudioSampleRate;		//��Ƶ������
							tFileInfo.iAudioChNum = 1;										//��Ƶ������

							//--------------------------------------------------------------------
							//�򻺳����������
							if ( !NPC_F_MEM_MG_AddDataToBuf(
								out_ppFileInfoDataBuf,				//���ݻ�����ָ��
								out_pFileInfoDataBufSize,			//���ݻ�������С
								out_pFileInfoDataLen,				//ʵ�����ݳ���
								(PNPC_BYTE)&tFileInfo,				//�������ָ��
								sizeof(tFileInfo)					//������ݳ���
								) )
							{
								//��ʾ��Ϣ
								NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: add data to buf fail.");

								bRet = FALSE;
								goto _NPC_CLEAR;
							}

							//--------------------------------------------------------------------
							iFileNum++;
						}
					}
				}
			}
			while( FindNextFile(hFind, &tFindFileData) != 0 );
		}

		*out_pFileNum = iFileNum;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( hFind )
		{
			FindClose(hFind);
			hFind = NULL;
		}
	}

	return bRet;
}

//��չ��ѯ�ļ�
NPC_BOOL	NPC_F_UMSP_MC_NspFindFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//������
	IN		PNPC_S_TD_DATE_TIME						in_pStartTime,				//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME						in_pEndTime,				//����ʱ��
	OUT		PNPC_INT								out_pFileNum,				//�ļ���
	OUT		PNPC_BYTE*								out_ppFileInfoDataBuf,		//�ļ���Ϣ���ݻ�������ΪNPC_S_MON_MPS_FILE_HEAD_INFO����
	OUT		PNPC_INT								out_pFileInfoDataBufSize,	//�ļ���Ϣ���ݻ�������С
	OUT		PNPC_INT								out_pFileInfoDataLen		//�ļ���Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	HANDLE											hFind;
	WIN32_FIND_DATA									tFindFileData;
	NPC_CHAR										sFindPath[MAX_PATH];
	NPC_CHAR										TempFilePath[MAX_PATH];

	NPC_CHAR										sBeginTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	NPC_CHAR										sBeginFileNameStr[128];
	NPC_CHAR										sEndFileNameStr[128];

	NPC_S_NAV_AV_FORMAT								tAvFormat;
	NPC_S_MON_MPS_FILE_HEAD_INFO					tFileInfo;
	NPC_DWORD										dwRecTimeLen;
	NPC_INT											iFileNum;

	//INIT AREA
	{
		bRet = TRUE;
		hFind = INVALID_HANDLE_VALUE;
		*out_pFileNum = 0;
		*out_pFileInfoDataLen = 0;
		iFileNum = 0;
	}

	//CODE AREA
	{
		sprintf(sBeginTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pStartTime->usYear,						//��
			in_pStartTime->usMonth,						//��
			in_pStartTime->ucDay,						//��
			in_pStartTime->ucHour,						//ʱ
			in_pStartTime->ucMinute,					//��
			in_pStartTime->ucSecond						//��
			);

		sprintf(sEndTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pEndTime->usYear,						//��
			in_pEndTime->usMonth,						//��
			in_pEndTime->ucDay,							//��
			in_pEndTime->ucHour,						//ʱ
			in_pEndTime->ucMinute,						//��
			in_pEndTime->ucSecond						//��
			);

		sprintf(sFindPath, ".\\rec\\REC_%d_*.nav", in_iChNo);

		sprintf(sBeginFileNameStr, "REC_%d_%s.nav", in_iChNo, sBeginTimeStr);
		sprintf(sEndFileNameStr, "REC_%d_%s.nav", in_iChNo, sEndTimeStr);

		hFind = FindFirstFile(sFindPath, &tFindFileData);

		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			do{
				if ( !(tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
				{
					if ( strcmp(tFindFileData.cFileName, sBeginFileNameStr) >= 0 && 
						strcmp(tFindFileData.cFileName, sEndFileNameStr) <= 0 )
					{
						sprintf(TempFilePath, ".\\rec\\%s", tFindFileData.cFileName);

						//��ȡ¼���ļ���Ϣ
						if ( !NPC_F_UMSP_MC_ReadRecFileInfo(
							TempFilePath,				//�ļ���������·��
							&tAvFormat,					//�ļ���ʽ
							sBeginTimeStr,				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							sEndTimeStr,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							&dwRecTimeLen				//¼��ʱ�����룩
							) )
						{
							//��ʾ��Ϣ
							NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: Failed to read the video file information.");

							bRet = FALSE;
							goto _NPC_CLEAR;
						}

						//--------------------------------------------------------------------
						if ( dwRecTimeLen > 0 )
						{
							memset(&tFileInfo, 0, sizeof(tFileInfo));

							strcpy(tFileInfo.sFileFlag, tFindFileData.cFileName);			//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
							tFileInfo.usChNo = in_iChNo;									//ͨ����
							tFileInfo.ucStreamNo = in_iStreamNo;							//������
							tFileInfo.ucFileType = NPC_D_MON_CSD_FILE_TYPE_RECORD;			//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
							tFileInfo.ucCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
							tFileInfo.ucAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_ALL;			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_DPS_FILE_CREATE_MODE_ALARMʱ��Ч
							tFileInfo.uiFileSize = tFindFileData.nFileSizeLow / 1024;		//�ļ���С����λ��KB��

							//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
							NPC_F_SYS_StrTime_To_TdTime(
								sBeginTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tStartTime			//TDʱ��
								);

							NPC_F_SYS_StrTime_To_TdTime(
								sEndTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tEndTime				//TDʱ��
								);

							tFileInfo.uiFileTimeLen = dwRecTimeLen;

							tFileInfo.ucVideoFlag = tAvFormat.bVedioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
							tFileInfo.ucAudioFlag = tAvFormat.bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ

							tFileInfo.ucVideoCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
							tFileInfo.ucVideoFrameRate = tAvFormat.iVedioFrameRate;			//��Ƶ֡��
							tFileInfo.uiVideoBitRate = tAvFormat.iVedioBitRate;				//��Ƶ���ʣ�kbps��
							tFileInfo.usVideoWidth = tAvFormat.usVedioWidth;				//��Ƶ���
							tFileInfo.usVideoHeight = tAvFormat.usVedioHeight;				//��Ƶ�߶�

							tFileInfo.usAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
							tFileInfo.usAudioBitRate = 64;									//��Ƶ����
							tFileInfo.uiAudioSampleRate = tAvFormat.iAudioSampleRate;		//��Ƶ������
							tFileInfo.usAudioChNum = 1;										//��Ƶ������

							//--------------------------------------------------------------------
							//�򻺳����������
							if ( !NPC_F_MEM_MG_AddDataToBuf(
								out_ppFileInfoDataBuf,				//���ݻ�����ָ��
								out_pFileInfoDataBufSize,			//���ݻ�������С
								out_pFileInfoDataLen,				//ʵ�����ݳ���
								(PNPC_BYTE)&tFileInfo,				//�������ָ��
								sizeof(tFileInfo)					//������ݳ���
								) )
							{
								//��ʾ��Ϣ
								NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: add data to buf fail.");

								bRet = FALSE;
								goto _NPC_CLEAR;
							}

							//--------------------------------------------------------------------
							iFileNum++;
						}
					}
				}
			}
			while( FindNextFile(hFind, &tFindFileData) != 0 );
		}

		*out_pFileNum = iFileNum;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( hFind )
		{
			FindClose(hFind);
			hFind = NULL;
		}
	}

	return bRet;
}

//��չ��ѯ�ļ�
NPC_BOOL	NPC_F_UMSP_MC_GetFileRange(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//������
	IN		PNPC_S_TD_DATE_TIME						in_pStartTime,				//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME						in_pEndTime,				//����ʱ��
	OUT		PNPC_INT								out_pFileNum,				//�ļ���
	OUT		PNPC_BYTE*								out_ppFileInfoDataBuf,		//�ļ���Ϣ���ݻ�������ΪNPC_S_MON_MPS_FILE_HEAD_INFO����
	OUT		PNPC_INT								out_pFileInfoDataBufSize,	//�ļ���Ϣ���ݻ�������С
	OUT		PNPC_INT								out_pFileInfoDataLen		//�ļ���Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	HANDLE											hFind;
	WIN32_FIND_DATA									tFindFileData;
	NPC_CHAR										sFindPath[MAX_PATH];
	NPC_CHAR										TempFilePath[MAX_PATH];

	NPC_CHAR										sBeginTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	NPC_CHAR										sBeginFileNameStr[128];
	NPC_CHAR										sEndFileNameStr[128];

	NPC_S_NAV_AV_FORMAT								tAvFormat;
	NPC_S_MON_MPS_FILE_RANGE_INFO					tFileInfo;
	NPC_DWORD										dwRecTimeLen;
	NPC_INT											iFileNum;

	//INIT AREA
	{
		bRet = TRUE;
		hFind = INVALID_HANDLE_VALUE;
		*out_pFileNum = 0;
		*out_pFileInfoDataLen = 0;
		iFileNum = 0;
	}

	//CODE AREA
	{
		sprintf(sBeginTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pStartTime->usYear,						//��
			in_pStartTime->usMonth,						//��
			in_pStartTime->ucDay,						//��
			in_pStartTime->ucHour,						//ʱ
			in_pStartTime->ucMinute,					//��
			in_pStartTime->ucSecond						//��
			);

		sprintf(sEndTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pEndTime->usYear,						//��
			in_pEndTime->usMonth,						//��
			in_pEndTime->ucDay,							//��
			in_pEndTime->ucHour,						//ʱ
			in_pEndTime->ucMinute,						//��
			in_pEndTime->ucSecond						//��
			);

		sprintf(sFindPath, ".\\rec\\REC_%d_*.nav", in_iChNo);

		sprintf(sBeginFileNameStr, "REC_%d_%s.nav", in_iChNo, sBeginTimeStr);
		sprintf(sEndFileNameStr, "REC_%d_%s.nav", in_iChNo, sEndTimeStr);

		hFind = FindFirstFile(sFindPath, &tFindFileData);

		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			do{
				if ( !(tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
				{
					if ( strcmp(tFindFileData.cFileName, sBeginFileNameStr) >= 0 && 
						strcmp(tFindFileData.cFileName, sEndFileNameStr) <= 0 )
					{
						sprintf(TempFilePath, ".\\rec\\%s", tFindFileData.cFileName);

						//��ȡ¼���ļ���Ϣ
						if ( !NPC_F_UMSP_MC_ReadRecFileInfo(
							TempFilePath,				//�ļ���������·��
							&tAvFormat,					//�ļ���ʽ
							sBeginTimeStr,				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							sEndTimeStr,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
							&dwRecTimeLen				//¼��ʱ�����룩
							) )
						{
							//��ʾ��Ϣ
							NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: Failed to read the video file information.");

							bRet = FALSE;
							goto _NPC_CLEAR;
						}

						//--------------------------------------------------------------------
						if ( dwRecTimeLen > 0 )
						{
							memset(&tFileInfo, 0, sizeof(tFileInfo));

							tFileInfo.dwFileFlag = iFileNum + 1;				//��ʶ
							tFileInfo.iCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_M
							tFileInfo.iAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_ALL;			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_DPS_FILE_CREATE_MODE_ALARMʱ��Ч
							
#if 1
							if (tFileInfo.dwFileFlag == 3)
							{
								tFileInfo.iCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_ALARM;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_M
								tFileInfo.iAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_MOTION;		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_DPS_FILE_CREATE_MODE_ALARMʱ��Ч

							}
#endif
							//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
							NPC_F_SYS_StrTime_To_TdTime(
								sBeginTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tStartTime			//TDʱ��
								);

							NPC_F_SYS_StrTime_To_TdTime(
								sEndTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
								&tFileInfo.tEndTime				//TDʱ��
								);


							//--------------------------------------------------------------------
							//�򻺳����������
							if ( !NPC_F_MEM_MG_AddDataToBuf(
								out_ppFileInfoDataBuf,				//���ݻ�����ָ��
								out_pFileInfoDataBufSize,			//���ݻ�������С
								out_pFileInfoDataLen,				//ʵ�����ݳ���
								(PNPC_BYTE)&tFileInfo,				//�������ָ��
								sizeof(tFileInfo)					//������ݳ���
								) )
							{
								//��ʾ��Ϣ
								NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: add data to buf fail.");

								bRet = FALSE;
								goto _NPC_CLEAR;
							}

							//--------------------------------------------------------------------
							iFileNum++;
						}
					}
				}
			}
			while( FindNextFile(hFind, &tFindFileData) != 0 );
		}

		*out_pFileNum = iFileNum;
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( hFind )
		{
			FindClose(hFind);
			hFind = NULL;
		}
	}

	return bRet;
}

//��ѯ�ļ�,��ȡ��һ���ļ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_NspFindFirstFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//������
	IN		PNPC_S_TD_DATE_TIME						in_pStartTime,				//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME						in_pEndTime,				//����ʱ��
	INOUT	PNPC_S_MON_MPS_FILE_HEAD_INFO			io_pFileInfo				//�ļ���Ϣ
	)
{
	NPC_BOOL										bRet;
	HANDLE											hFind;
	WIN32_FIND_DATA									tFindFileData;
	NPC_CHAR										sFindPath[MAX_PATH];
	NPC_CHAR										TempFilePath[MAX_PATH];

	NPC_CHAR										sBeginTimeStr[20];
	NPC_CHAR										sEndTimeStr[20];

	NPC_CHAR										sBeginFileNameStr[128];
	NPC_CHAR										sEndFileNameStr[128];

	NPC_S_NAV_AV_FORMAT								tAvFormat;
	NPC_DWORD										dwRecTimeLen;

	//INIT AREA
	{
		bRet = TRUE;
		hFind = INVALID_HANDLE_VALUE;;
	}

	//CODE AREA
	{
		sprintf(sBeginTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pStartTime->usYear,						//��
			in_pStartTime->usMonth,						//��
			in_pStartTime->ucDay,						//��
			in_pStartTime->ucHour,						//ʱ
			in_pStartTime->ucMinute,					//��
			in_pStartTime->ucSecond						//��
			);

		sprintf(sEndTimeStr, "%4.4d%2.2d%2.2d%2.2d%2.2d%2.2d", 
			in_pEndTime->usYear,						//��
			in_pEndTime->usMonth,						//��
			in_pEndTime->ucDay,							//��
			in_pEndTime->ucHour,						//ʱ
			in_pEndTime->ucMinute,						//��
			in_pEndTime->ucSecond						//��
			);

		sprintf(sFindPath, ".\\rec\\REC_%d_*.nav", in_iChNo);

		sprintf(sBeginFileNameStr, "REC_%d_%s.nav", in_iChNo, sBeginTimeStr);
		sprintf(sEndFileNameStr, "REC_%d_%s.nav", in_iChNo, sEndTimeStr);

		hFind = FindFirstFile(sFindPath, &tFindFileData);

		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			if ( !(tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			{
				if ( strcmp(tFindFileData.cFileName, sBeginFileNameStr) >= 0 && 
					strcmp(tFindFileData.cFileName, sEndFileNameStr) <= 0 )
				{
					sprintf(TempFilePath, ".\\rec\\%s", tFindFileData.cFileName);
					
					//��ȡ¼���ļ���Ϣ
					if ( !NPC_F_UMSP_MC_ReadRecFileInfo(
						TempFilePath,				//�ļ���������·��
						&tAvFormat,					//�ļ���ʽ
						sBeginTimeStr,				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
						sEndTimeStr,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
						&dwRecTimeLen				//¼��ʱ�����룩
						) )
					{
						//��ʾ��Ϣ
						NPC_F_LOG_SR_ShowInfo("[UMSP]  Query record file fail, cause: Failed to read the video file information.");
						
						bRet = FALSE;
						goto _NPC_CLEAR;
					}
					
					//--------------------------------------------------------------------
					if ( dwRecTimeLen > 0 )
					{
						memset(io_pFileInfo, 0, sizeof(NPC_S_MON_MPS_FILE_HEAD_INFO));
						
						strcpy(io_pFileInfo->sFileFlag, tFindFileData.cFileName);			//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
						io_pFileInfo->usChNo = in_iChNo;									//ͨ����
						io_pFileInfo->ucStreamNo = in_iStreamNo;							//������
						io_pFileInfo->ucFileType = NPC_D_MON_CSD_FILE_TYPE_RECORD;			//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
						io_pFileInfo->ucCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
						io_pFileInfo->ucAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_ALL;			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_DPS_FILE_CREATE_MODE_ALARMʱ��Ч
						io_pFileInfo->uiFileSize = tFindFileData.nFileSizeLow / 1024;		//�ļ���С����λ��KB��
						
						//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
						NPC_F_SYS_StrTime_To_TdTime(
							sBeginTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
							&io_pFileInfo->tStartTime			//TDʱ��
							);
						
						NPC_F_SYS_StrTime_To_TdTime(
							sEndTimeStr,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
							&io_pFileInfo->tEndTime				//TDʱ��
							);
						
						io_pFileInfo->uiFileTimeLen = dwRecTimeLen;
						
						io_pFileInfo->ucVideoFlag = tAvFormat.bVedioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
						io_pFileInfo->ucAudioFlag = tAvFormat.bAudioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
						
						io_pFileInfo->ucVideoCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
						io_pFileInfo->ucVideoFrameRate = tAvFormat.iVedioFrameRate;			//��Ƶ֡��
						io_pFileInfo->uiVideoBitRate = tAvFormat.iVedioBitRate;				//��Ƶ���ʣ�kbps��
						io_pFileInfo->usVideoWidth = tAvFormat.usVedioWidth;				//��Ƶ���
						io_pFileInfo->usVideoHeight = tAvFormat.usVedioHeight;				//��Ƶ�߶�
						
						io_pFileInfo->usAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
						io_pFileInfo->usAudioBitRate = 64;									//��Ƶ����
						io_pFileInfo->uiAudioSampleRate = tAvFormat.iAudioSampleRate;		//��Ƶ������
						io_pFileInfo->usAudioChNum = 1;										//��Ƶ������
					}
				}
			}
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( hFind )
		{
			FindClose(hFind);
			hFind = NULL;
		}
	}

	return bRet;
}

//��ȡ¼���ļ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_ReadRecFileInfo(
	IN		PNPC_CHAR								in_pFileName,			//�ļ���������·��
	OUT		PNPC_S_NAV_AV_FORMAT					out_pAvFormat,			//�ļ���ʽ
	OUT		PNPC_CHAR								out_pRecBeginTime,		//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_CHAR								out_pRecEndTime,		//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_DWORD								out_pRecTimeLen			//¼��ʱ�����룩
	)
{
	NPC_HANDLE										hRecFileHandle;

	NPC_INT											iDevVendor;				//�豸����
	NPC_INT											iRecCodecFormat;		//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
	NPC_DWORD										dwTimestampRef;			//ʱ����ο�ֵ��Ĭ��Ϊ90000

	//��NAV�ļ�
	hRecFileHandle = NPC_F_NAV_OpenFile(
		in_pFileName,				//�ļ���
		&iDevVendor,				//�豸����
		&iRecCodecFormat,			//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
		out_pAvFormat,				//¼���ʽ
		&dwTimestampRef,			//ʱ����ο�ֵ��Ĭ��Ϊ90000
		out_pRecBeginTime,			//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
		out_pRecEndTime,			//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
		out_pRecTimeLen				//¼��ʱ�����룩
		);
	if ( hRecFileHandle == NULL )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_ReadRecFileInfo NPC_F_NAV_OpenFile fail.");
		return FALSE;
	}

	//�ر�NAV�ļ�
	NPC_F_NAV_CloseFile(
		hRecFileHandle					//NAV�ļ����
		);
	hRecFileHandle = NULL;

	return TRUE;
}



//-----------------------------------------------------------------------------------
//���ļ���������ΪNPC_D_MON_CSD_DPS_ERROR_CODE_*
NPC_INT		NPC_F_UMSP_MC_File_OpenFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_CHAR								in_pFileFlag,				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
	IN		NPC_DWORD								in_dwStartOffsetDataPos,	//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
	IN		NPC_DWORD								in_dwStartOffsetTimePos,	//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
	OUT		PNPC_DWORD								out_pFileReadId,			//�����ļ���ȡID
	OUT		PNPC_S_MON_MPS_FILE_INFO				out_pFileInfo				//�ļ���Ϣ
	)
{
	NPC_INT											iRet;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	NPC_INT											iDevVendor;
	NPC_INT											iRecCodecFormat;
	NPC_S_NAV_AV_FORMAT								tAvFormat;
	NPC_DWORD										dwTimestampRef;
	NPC_CHAR										sRecBeginTime[20];
	NPC_CHAR										sRecEndTime[20];
	NPC_DWORD										dwRecTimeLen;

	NPC_LONG										lFileSize;
	NPC_CHAR										sFilePath[256];

	NPC_INT											i;
	NPC_INT											iIndex;
	NPC_INT											iUseNum;

	//INIT AREA
	{
		iRet = 0;
		pFileWorkData = NULL;
	}

	//CODE AREA
	{
		//ͳ������
		iUseNum = 0;
		for ( i=0; i<NPC_D_UMSP_MC_MAX_FILE_WORK_NUM; i++ )
		{
			if ( in_pMcSrvData->tFileWorkTable[i].bIfUsed )
			{
				iUseNum++;
			}
		}
		if ( iUseNum >= in_pMcSrvData->tConfig.iMaxFileConnNum )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile fail, cause: Maximum limit.");
			return NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NO_IDLE;
		}

		//���ҿ���λ��
		iIndex = -1;
		for ( i=0; i<NPC_D_UMSP_MC_MAX_FILE_WORK_NUM; i++ )
		{
			if ( !in_pMcSrvData->tFileWorkTable[i].bIfUsed )
			{
				pFileWorkData = &in_pMcSrvData->tFileWorkTable[i];
				iIndex = i;
				break;
			}
		}
		if ( pFileWorkData == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile no idle pos.");
			return NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NO_IDLE;
		}

		pFileWorkData->bIfUsed = TRUE;
		pFileWorkData->dwFileReadId = (rand()<<16) | iIndex;
		if ( pFileWorkData->dwFileReadId == 0 )
			pFileWorkData->dwFileReadId = 1 | iIndex;

		sprintf(sFilePath, ".\\rec\\%s", in_pFileFlag);

		//�����ļ���С
		lFileSize = NPC_F_UMSP_MC_ComputeFileSize(
			sFilePath					//�ļ���������·����
			);
		if ( lFileSize == -1 )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile NPC_F_UMSP_MC_ComputeFileSize fail.");

			iRet = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_OPEN_FAIL;
			goto _NPC_CLEAR;
		}

		//��NAV�ļ�
		pFileWorkData->hNavFile = NPC_F_NAV_OpenFile(
			sFilePath,					//�ļ���
			&iDevVendor,				//�豸����
			&iRecCodecFormat,			//¼������ʽ��0��Ϊ��׼��ʽ��tRecFormat��Ч������Ϊ����ԭʼ��ʽ����Ҫ�ó��̵�SDK����
			&tAvFormat,					//¼���ʽ
			&dwTimestampRef,			//ʱ����ο�ֵ��Ĭ��Ϊ90000
			sRecBeginTime,				//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
			sRecEndTime,				//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
			&dwRecTimeLen				//¼��ʱ�����룩
			);
		if ( pFileWorkData->hNavFile == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile NPC_F_NAV_OpenFile fail.");

			iRet = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_OPEN_FAIL;
			goto _NPC_CLEAR;
		}

		if ( dwRecTimeLen > 0 )
		{
			if ( in_dwStartOffsetTimePos >= dwRecTimeLen )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile in_dwStartOffsetTimePos fail.");

				iRet = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
				goto _NPC_CLEAR;
			}

			//��ת��ָ��λ��
			if ( !NPC_F_NAV_JumpCurPos(
				pFileWorkData->hNavFile,		//NAV�ļ����
				in_dwStartOffsetTimePos			//��ת��ָ��λ�ã��ò���¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
				) )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_OpenFile NPC_F_NAV_JumpCurPos fail.");

				iRet = NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER;
				goto _NPC_CLEAR;
			}
		}

		*out_pFileReadId = pFileWorkData->dwFileReadId;

		memset(out_pFileInfo, 0, sizeof(NPC_S_MON_MPS_FILE_INFO));

		strcpy(out_pFileInfo->sFileFlag, in_pFileFlag);						//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
		out_pFileInfo->iFileType = NPC_D_MON_CSD_FILE_TYPE_RECORD;			//�ļ����ͣ��μ�NPC_D_MON_CSD_FILE_TYPE_*����
		out_pFileInfo->iCreateMode = NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER;	//������ʽ���μ�NPC_D_MON_CSD_FILE_CREATE_MODE_*����
		out_pFileInfo->iAlarmEvent = NPC_D_MON_CSD_ALARM_EVENT_ALL;			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*���壬ֻ�д�����ʽΪNPC_D_MON_CSD_FILE_CREATE_MODE_ALARMʱ��Ч
		out_pFileInfo->dwFileTimeLen = dwRecTimeLen;						//�ļ���ʱ�����룩��¼���ļ���Ч
		out_pFileInfo->dwFileSize = lFileSize/1024;							//�ļ���С����λ��KB��

		//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
		NPC_F_SYS_StrTime_To_TdTime(
			sRecBeginTime,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
			&out_pFileInfo->tStartTime		//TDʱ��
			);

		NPC_F_SYS_StrTime_To_TdTime(
			sRecEndTime,					//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
			&out_pFileInfo->tEndTime		//TDʱ��
			);

		out_pFileInfo->bVideoFlag = tAvFormat.bVedioFlag;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
		out_pFileInfo->bAudioFlag = tAvFormat.bAudioFlag;;					//��Ƶ��־��TRUE����ʾ����Ƶ��FALSE����ʾû����Ƶ
		out_pFileInfo->bPictureFlag = 0;									//ͼƬ��־��TRUE����ʾΪͼƬ��FALSE����ʾ����ͼƬ������ò���TRUE��������Ƶ������Ч

		out_pFileInfo->iVideoCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
		out_pFileInfo->iVideoFrameRate = tAvFormat.iVedioFrameRate;			//��Ƶ֡��
		out_pFileInfo->iVideoBitRate = tAvFormat.iVedioBitRate;				//��Ƶ���ʣ�kbps��
		out_pFileInfo->usVideoWidth = tAvFormat.usVedioWidth;				//��Ƶ���
		out_pFileInfo->usVideoHeight = tAvFormat.usVedioHeight;				//��Ƶ�߶�

		out_pFileInfo->iAudioCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;	//��Ƶ����ID���μ�NPC_D_MON_CODEC_ID_*����
		out_pFileInfo->iAudioBitRate = 64;									//��Ƶ����
		out_pFileInfo->iAudioSampleRate = tAvFormat.iAudioSampleRate;		//��Ƶ������
		out_pFileInfo->iAudioChNum = 1;										//��Ƶ������

		//--------------------------------------------------------------------
		pFileWorkData->iFileVideoFrameRate = tAvFormat.iVedioFrameRate;
		pFileWorkData->dwFileTimeLen = dwRecTimeLen;
		pFileWorkData->tFileBeginRecTime = NPC_F_SYS_Str_To_Time(sRecBeginTime);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( iRet != 0 && pFileWorkData )
		{
			if ( pFileWorkData->hNavFile )
			{
				//�ر�NAV�ļ�
				NPC_F_NAV_CloseFile(
					pFileWorkData->hNavFile		//NAV�ļ����
					);
				pFileWorkData->hNavFile = NULL;
			}

			memset(pFileWorkData, 0, sizeof(NPC_S_UMSP_FILE_WORK_DATA));
		}
	}

	return iRet;
}

//�ر��ļ�
NPC_VOID	NPC_F_UMSP_MC_File_CloseFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId				//�ļ���ȡID
	)
{
	NPC_INT											iIndex;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	iIndex = in_dwFileReadId & 0xFFFF;
	if ( iIndex >= NPC_D_UMSP_MC_MAX_FILE_WORK_NUM )
		return;

	pFileWorkData = &(in_pMcSrvData->tFileWorkTable[iIndex]);
	if ( !pFileWorkData->bIfUsed )
		return;

	if ( pFileWorkData->dwFileReadId != in_dwFileReadId )
		return;

	if ( pFileWorkData->hNavFile )
	{
		//�ر�NAV�ļ�
		NPC_F_NAV_CloseFile(
			pFileWorkData->hNavFile		//NAV�ļ����
			);
		pFileWorkData->hNavFile = NULL;
	}

	memset(pFileWorkData, 0, sizeof(NPC_S_UMSP_FILE_WORK_DATA));
}

//��λ�ļ���������ΪNPC_D_MON_CSD_DPS_ERROR_CODE_*
NPC_INT		NPC_F_UMSP_MC_File_SeekFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId,			//�ļ���ȡID
	IN		NPC_DWORD								in_dwOffsetTimePos			//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ��
	)
{
	NPC_INT											iIndex;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	iIndex = in_dwFileReadId & 0xFFFF;
	if ( iIndex >= NPC_D_UMSP_MC_MAX_FILE_WORK_NUM )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile in_dwFileReadId fail.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
	}

	pFileWorkData = &(in_pMcSrvData->tFileWorkTable[iIndex]);
	if ( !pFileWorkData->bIfUsed )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile bIfUsed fail.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
	}

	if ( pFileWorkData->dwFileReadId != in_dwFileReadId )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile in_dwFileReadId error.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
	}

	if ( pFileWorkData->hNavFile == NULL )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile hNavFile fail.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_OPEN;
	}

	if ( in_dwOffsetTimePos >= pFileWorkData->dwFileTimeLen )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile in_dwOffsetTimePos fail.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
	}

	//��ת��ָ��λ��
	if ( !NPC_F_NAV_JumpCurPos(
		pFileWorkData->hNavFile,		//NAV�ļ����
		in_dwOffsetTimePos				//��ת��ָ��λ�ã��ò���¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
		) )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_SeekFile NPC_F_NAV_JumpCurPos fail.");
		return NPC_D_MON_CSD_DPS_ERROR_CODE_FILE_OP_FAIL;
	}

	return NPC_D_MON_CSD_DPS_ERROR_CODE_SUCCESS;
}

//��ȡ�ļ�����Ƶ����
NPC_BOOL	NPC_F_UMSP_MC_File_GetFileVideoParam(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId,			//�ļ���ȡID
	OUT		PNPC_INT								out_pFrameRate,				//֡��
	OUT		PNPC_INT								out_pGOP					//GOP
	)
{
	NPC_INT											iIndex;
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;

	iIndex = in_dwFileReadId & 0xFFFF;
	if ( iIndex >= NPC_D_UMSP_MC_MAX_FILE_WORK_NUM )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_GetFileVideoParam in_dwFileReadId fail.");
		return FALSE;
	}

	pFileWorkData = &(in_pMcSrvData->tFileWorkTable[iIndex]);
	if ( !pFileWorkData->bIfUsed )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_GetFileVideoParam bIfUsed fail.");
		return FALSE;
	}

	if ( pFileWorkData->dwFileReadId != in_dwFileReadId )
	{
		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  NPC_F_UMSP_MC_File_GetFileVideoParam in_dwFileReadId error.");
		return FALSE;
	}

	*out_pFrameRate = pFileWorkData->iFileVideoFrameRate;
	*out_pGOP = *out_pFrameRate * 2; //����¼���ļ���û��GOP��������������̶�дһ��ֵ

	return TRUE;
}

//����һý��֡���ݣ���Ƶ����Ƶ��
NPC_BOOL	NPC_F_UMSP_MC_File_SendMediaFrameData(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_FILE_WORK_DATA				in_pFileWorkData,			//�ļ���������
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen,				//��Ϣ���ݳ���
	IN		NPC_INT									in_iEndFlag,				//������־��0��δ������1���������������2���ļ�����
	IN		NPC_INT									in_iMediaType,				//ý�����ͣ�0����Ƶ��1����Ƶ
	IN		NPC_CHAR								in_cFrameType,				//֡���ͣ���ƵΪ��I������P������B���ȣ���Ƶ�ò�����Ч
	IN		NPC_DWORD								in_dwTimestamp,				//ʱ���
	IN		NPC_DWORD								in_dwRecOffsetTime,			//¼��ƫ��ʱ�䣨�룩��������ļ�ͷ��ʱ��
	IN		PNPC_BYTE								in_pMediaDataBuf,			//ý�����ݻ�������ԭʼ�������ݣ�
	IN		NPC_INT									in_iMediaDataLen			//ý�����ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataLen;
	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ			pSendMsgBody;

	//INIT AREA
	{
		bRet = TRUE;
		pSendDataBuf = NULL;
		iSendDataLen = 0;
	}

	//CODE AREA
	{
		if ( in_pMediaDataBuf == NULL || in_iMediaDataLen < 0 )
			in_iMediaDataLen = 0;

		iSendDataLen = in_iMsgDataLen + in_iMediaDataLen;
		pSendDataBuf = (PNPC_BYTE)malloc(iSendDataLen);
		if ( pSendDataBuf == NULL )
		{
			bRet = FALSE;
			goto _NPC_CLEAR;
		}

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;
		pSendMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E2_FILE_READ)((PNPC_BYTE)pSendMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));

		memcpy(pSendDataBuf, in_pMsgDataBuf, in_iMsgDataLen);

		if ( in_pMediaDataBuf && in_iMediaDataLen > 0 )
			memcpy(pSendDataBuf+in_iMsgDataLen, in_pMediaDataBuf, in_iMediaDataLen);

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		pSendMsgBody->o_ucRetDataType = in_iMediaType + 1;				//�����������ͣ�1����Ƶ��2����Ƶ��3��ͼƬ����
		if ( in_iMediaType == 0 )
		{
			switch ( in_cFrameType )
			{
			case 'I':
				pSendMsgBody->o_ucFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_I;				//֡���ͣ���Ƶ��Ч���μ�NPC_D_MON_CSD_VIDEO_FRAME_TYPE_*����
				break;
			case 'P':
				pSendMsgBody->o_ucFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P;
				break;
			case 'B':
				pSendMsgBody->o_ucFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_B;
				break;
			default:
				pSendMsgBody->o_ucFrameType = NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P;
				break;
			}

			pSendMsgBody->o_ucMediaCodecId = NPC_D_MON_CSD_CODEC_ID_VEDIO_H264;			//ý������ʽ���μ�NPC_D_MON_CSD_CODEC_ID_*����
			pSendMsgBody->o_ucVideoFrameRate = in_pFileWorkData->iFileVideoFrameRate;	//��Ƶ֡�ʣ�Ϊ��Ƶ֡ʱ��Ч��
		}
		else
		{
			pSendMsgBody->o_ucMediaCodecId = NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA;			//ý������ʽ���μ�NPC_D_MON_CSD_CODEC_ID_*����
		}

		pSendMsgBody->o_ucIfDataEnd = in_iEndFlag;									//�Ƿ������0��δ������1���������������2���ļ�����
		pSendMsgBody->o_dwOffsetDataPos = 0;										//��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
		pSendMsgBody->o_dwOffsetTimePos = in_dwRecOffsetTime;						//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ��
		pSendMsgBody->o_dwDataLen = in_iMediaDataLen;								//���ݳ���

		//��time_tת��ΪNPC_S_TD_DATE_TIMEʱ��
		NPC_F_SYS_Timet_To_TdTime(
			in_pFileWorkData->tFileBeginRecTime + in_dwRecOffsetTime,		//ʱ��ֵ
			&pSendMsgBody->o_tDataTime										//TDʱ��
			);

		/*//------------------------------------------------------------------------------------
		NPC_CHAR sTempLogBuf[2000];

		//д��־
		NPC_F_LOG_SR_WriteLog("=====================================.");

		sprintf(sTempLogBuf, "i_ucReqDataType: %d", pSendMsgBody->i_ucReqDataType);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "i_ucReqDataSize: %d", pSendMsgBody->i_ucReqDataSize);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_ucRetDataType: %d", pSendMsgBody->o_ucRetDataType);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_ucFrameType: %d", pSendMsgBody->o_ucFrameType);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_ucIfDataEnd: %d", pSendMsgBody->o_ucIfDataEnd);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_ucMediaCodecId: %d", pSendMsgBody->o_ucMediaCodecId);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_ucVideoFrameRate: %d", pSendMsgBody->o_ucVideoFrameRate);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_dwOffsetTimePos: %d", pSendMsgBody->o_dwOffsetTimePos);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);

		sprintf(sTempLogBuf, "o_dwDataLen: %d", pSendMsgBody->o_dwDataLen);
		NPC_F_LOG_SR_WriteLog(sTempLogBuf);*/

		//------------------------------------------------------------------------------------
		//������Ϣ���豸Э���������
		if ( !NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			) )
		{
			bRet = FALSE;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}

	return bRet;
}

//��ѯ�ļ��������ݣ������ļ���ID��
PNPC_S_UMSP_FILE_WORK_DATA		NPC_F_UMSP_MC_File_QueryFileWorkDataByFileReadId(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId				//�ļ���ȡID
	)
{
	PNPC_S_UMSP_FILE_WORK_DATA						pFileWorkData;
	NPC_INT											iIndex;

	iIndex = in_dwFileReadId & 0xFFFF;
	if ( iIndex >= NPC_D_UMSP_MC_MAX_FILE_WORK_NUM )
		return NULL;

	pFileWorkData = &(in_pMcSrvData->tFileWorkTable[iIndex]);
	if ( !pFileWorkData->bIfUsed )
		return NULL;

	if ( pFileWorkData->dwFileReadId != in_dwFileReadId )
		return NULL;

	return pFileWorkData;
}


//-----------------------------------------------------------------------------------
//�����ļ���С
NPC_LONG	NPC_F_UMSP_MC_ComputeFileSize(
	IN		PNPC_CHAR								in_pFileName				//�ļ���������·����
	)
{
	FILE*											f;
	NPC_LONG										lFileSize;

	f = fopen(in_pFileName, "rb");
	if ( f == NULL )
		return -1;

	//�ƶ����ļ��Ľ�β
	if ( fseek(f, 0, SEEK_END) == -1 )
		return -1;

	//����ļ���С
	lFileSize = ftell(f);
	if ( lFileSize == -1 )
		return -1;

	return lFileSize;
}


//-----------------------------------------------------------------------------------
//������״̬
NPC_VOID	NPC_F_UMSP_MC_DoAlarmState(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_INT											i;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;
	time_t											tCurTime;
	NPC_CHAR										sAlarmId[32];

	if ( !in_pMcSrvData->tConfig.bIfSendAlarmMsg )
		return;

	tCurTime = time(NULL);

	for ( i=0; i<in_pMcSrvData->iChNum; i++ )
	{
		pCameraData = &in_pMcSrvData->tCameraTable[i];

		if ( tCurTime - pCameraData->tPrecSendAlarmMsgTime >= in_pMcSrvData->tConfig.iSendAlarmIntervalTime )
		{
			pCameraData->tPrecSendAlarmMsgTime = tCurTime;

			//���ͱ�����Ϣ
			/*NPC_F_UMSP_MC_SendAlarmMsg(
				in_pMcSrvData,							//���ط�������
				pCameraData,							//���������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_FAULT,		//�����¼�
				1										//����״̬
				);*/

			/*
			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_MOTION,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"Mobile detection alarm"		//������Ϣ
				);

			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_VIDEO_BLIND,	//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"Video blind alarm"			//������Ϣ
				);

			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_VIDEO_LOSS,	//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"Video lost alarm"			//������Ϣ
				);

			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_PROBE,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"Probe alarm"				//������Ϣ
				);

			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_PIR,			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"PIR alarm"					//������Ϣ
				);

			//�ϱ�������Ϣ��ֻ�в����ı�����Ϣ�ŷ��͸���������
			NPC_F_DPS_UpAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_DOORBELL,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				1,										//����״̬��0��ֹͣ��1����ʼ
				(PNPC_CHAR)"Doorbell alarm"				//������Ϣ
				);
			*/

			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);
			
			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				sAlarmId,								//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,										//ͨ����
				2,										//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Mobile detection alarm"		//������Ϣ
				);

/*
			//-------------------------------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,				//�豸Э�����������
				sAlarmId,								//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,										//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_MOTION,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Mobile detection alarm"		//������Ϣ
				);
			
			//------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,					//�豸Э�����������
				sAlarmId,									//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_VIDEO_BLIND,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Video blind alarm"				//������Ϣ
				);

			//------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,					//�豸Э�����������
				sAlarmId,									//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_VIDEO_LOSS,		//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Video lost alarm"				//������Ϣ
				);

			//------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,					//�豸Э�����������
				sAlarmId,									//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_PROBE,			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Probe alarm"					//������Ϣ
				);

			//------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,					//�豸Э�����������
				sAlarmId,									//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_PIR,				//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"PIR alarm"						//������Ϣ
				);

			//------------------------------------------------------------
			//��������ID
			NPC_F_UMSP_MC_CreateAlarmId(
				in_pMcSrvData,			//���ط�������
				sAlarmId				//����ID
				);

			//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
			NPC_F_DPS_SendAlarmMsg(
				in_pMcSrvData->hUmspProSrv,					//�豸Э�����������
				sAlarmId,									//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_DOORBELL,			//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
				(PNPC_CHAR)"Doorbell alarm"					//������Ϣ
				);

			//------------------------------------------------------------
			//���ͱ�����Ϣ
			NPC_F_UMSP_MC_SendAlarmInfo(
				in_pMcSrvData,								//���ط�������
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_HDD_ERROR,		//�����¼�
				(PNPC_CHAR)"Hard disk error"				//������Ϣ
				);

			//���ͱ�����Ϣ
			NPC_F_UMSP_MC_SendAlarmInfo(
				in_pMcSrvData,								//���ط�������
				i,											//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_HDD_FULL,			//�����¼�
				(PNPC_CHAR)"Hard disk full"					//������Ϣ
				);

			//------------------------------------------------------------
			//���ͱ�����Ϣ
			NPC_F_UMSP_MC_SendAlarmInfo(
				in_pMcSrvData,										//���ط�������
				i,													//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_CROSS_LINE,		//�����¼�
				(PNPC_CHAR)"Smart ipc cross line"					//������Ϣ
				);

			//���ͱ�����Ϣ
			NPC_F_UMSP_MC_SendAlarmInfo(
				in_pMcSrvData,											//���ط�������
				i,														//ͨ����
				NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_INTRUSION,		//�����¼�
				(PNPC_CHAR)"Smart ipc area intrusion"					//������Ϣ
				);

*/
		}
	}
}

//���ͱ�����Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendAlarmMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData,				//���������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼�
	IN		NPC_INT									in_iAlarmState				//����״̬
	)
{
	struct _PacketData{
		NPC_S_DPS_MSG_HEAD							tMsgHead;
		NPC_S_DPS_MSG_BODY_EVENT_E2_ALARM_INFO		tMsgBody;
	} tPacketData = {0};

	tPacketData.tMsgHead.iMsgFuncId = NPC_D_DPS_MSGID_EVENT_E2_ALARM_INFO;					//��Ϣ����ID���μ�NPC_D_DPS_MSGID_*����
	tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_REQUEST;							//��Ϣ���ͣ��μ�NPC_D_DPS_MSG_TYPE_*����
	tPacketData.tMsgHead.iMsgBodyLen = sizeof(NPC_S_DPS_MSG_BODY_EVENT_E2_ALARM_INFO);		//��Ϣ���峤��

	tPacketData.tMsgBody.i_iChNo = in_iChNo;												//ͨ����
	tPacketData.tMsgBody.i_iAlarmEvent = in_iAlarmEvent;									//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
	tPacketData.tMsgBody.i_iAlarmState = in_iAlarmState;									//����״̬��0��������ʼ��1����������

	//������Ϣ���豸Э���������
	if ( !NPC_F_DPS_SendDevProData(
		in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
		(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
		sizeof(tPacketData)					//�豸Э�����ݳ���
		) )
	{
		return FALSE;
	}

	return TRUE;
}

//���͹ر�ý������Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendCloseMediaStreamMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo				//����
	)
{
	struct _PacketData{
		NPC_S_DPS_MSG_HEAD									tMsgHead;
		NPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM		tMsgBody;
	} tPacketData = {0};

	tPacketData.tMsgHead.iMsgFuncId = NPC_D_DPS_MSGID_EVENT_E2_CLOSE_MEDIA_STREAM;					//��Ϣ����ID���μ�NPC_D_DPS_MSGID_*����
	tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_REQUEST;									//��Ϣ���ͣ��μ�NPC_D_DPS_MSG_TYPE_*����
	tPacketData.tMsgHead.iMsgBodyLen = sizeof(NPC_S_DPS_MSG_BODY_EVENT_E2_CLOSE_MEDIA_STREAM);		//��Ϣ���峤��

	tPacketData.tMsgBody.i_iChNo = in_iChNo;														//ͨ����
	tPacketData.tMsgBody.i_iStreamNo = in_iStreamNo;												//�����ţ�0����������1��������

	//������Ϣ���豸Э���������
	if ( !NPC_F_DPS_SendDevProData(
		in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
		(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
		sizeof(tPacketData)					//�豸Э�����ݳ���
		) )
	{
		return FALSE;
	}

	return TRUE;
}

//���͹رնԽ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendCloseTalkMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo					//ͨ����
	)
{
	struct _PacketData{
		NPC_S_DPS_MSG_HEAD							tMsgHead;
		NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP		tMsgBody;
	} tPacketData = {0};

	tPacketData.tMsgHead.iMsgFuncId = NPC_D_DPS_MSGID_EVENT_E2_TALK_STOP;					//��Ϣ����ID���μ�NPC_D_DPS_MSGID_*����
	tPacketData.tMsgHead.ucMsgType = NPC_D_DPS_MSG_TYPE_REQUEST;							//��Ϣ���ͣ��μ�NPC_D_DPS_MSG_TYPE_*����
	tPacketData.tMsgHead.iMsgBodyLen = sizeof(NPC_S_DPS_MSG_BODY_EVENT_E2_TALK_STOP);		//��Ϣ���峤��

	tPacketData.tMsgBody.i_iTalkChNo = in_iChNo;											//ͨ����

	//������Ϣ���豸Э���������
	if ( !NPC_F_DPS_SendDevProData(
		in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
		(PNPC_BYTE)&tPacketData,			//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
		sizeof(tPacketData)					//�豸Э�����ݳ���
		) )
	{
		return FALSE;
	}

	return TRUE;
}


//-----------------------------------------------------------------------------------
//�޸��û����룬����0��ʾ�ɹ���1���û�������2��ԭ�������9������ʧ��
NPC_INT		NPC_F_UMSP_MC_ModifyUserPwd(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_CHAR								in_pUserName,				//�û���
	IN		PNPC_CHAR								in_pOldPwd,					//ԭ����
	IN		PNPC_CHAR								in_pNewPwd					//������
	)
{
	NPC_CHAR										sCfgFileName[256];
	NPC_CHAR										sKeyName[128];
	NPC_CHAR										sUserName[32];
	NPC_CHAR										sUserPwd[32];
	NPC_INT											i, iUserNum;

	strcpy(sCfgFileName, ".\\npc_umsp_server_config.ini");

	//�û���
	iUserNum = GetPrivateProfileInt("USER", "UserNum", 0, sCfgFileName);

	for ( i=0; i<iUserNum; i++ )
	{
		sprintf(sKeyName, "UserName[%d]", i);
		GetPrivateProfileString("USER", sKeyName, "", sUserName, sizeof(sUserName), sCfgFileName);

		sprintf(sKeyName, "UserPwd[%d]", i);
		GetPrivateProfileString("USER", sKeyName, "", sUserPwd, sizeof(sUserPwd), sCfgFileName);

		if ( strcmp(in_pUserName, sUserName) == 0 )
		{
			if ( strcmp(in_pOldPwd, sUserPwd) != 0 )
			{
				return 2;
			}

			sprintf(sKeyName, "UserPwd[%d]", i);
			WritePrivateProfileString("USER", sKeyName, in_pNewPwd, sCfgFileName);

			return 0;
		}
	}

	return 1;
}

//------------------------------------------------------------------------------------------
//��ѯMP3�ļ��б�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_QUERY_MP3_FILE_LIST(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_BYTE										pCusBodyPos;

	PNPC_BYTE										pSendDataBuf;
	NPC_INT											iSendDataLen;

	NPC_INT											iMp3FileNum;
	NPC_INT											iPreMsgDataLen;

	PNPC_S_DPS_MSG_HEAD								pSendMsgHead;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pSendMsgBody;

	PNPC_S_DPS_CUSTOM_NI_BODY_QUERY_MP3_FILE_LIST	pMp3FileList;
	PNPC_S_DPS_CUSTOM_NI_BODY_MP3_FILE_INFO			pMp3FileInfo;

	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM);

		pSendDataBuf = NULL;
		iSendDataLen = 0;
		iMp3FileNum = 0;

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_F_LOG_SR_ShowInfo("[UMSP]  Query mp3 file list.");

		iPreMsgDataLen = sizeof(NPC_S_DPS_MSG_HEAD) + 
			sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM);

		iMp3FileNum = 0;
		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed )
			{
				iMp3FileNum++;
			}
		}

		iSendDataLen = 
			iPreMsgDataLen + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_QUERY_MP3_FILE_LIST) + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_MP3_FILE_INFO) * iMp3FileNum;
		pSendDataBuf = (PNPC_BYTE)malloc(iSendDataLen);
		if ( pSendDataBuf == NULL )
		{
			bRet = FALSE;
			goto _NPC_CLEAR;
		}
		memset(pSendDataBuf, 0, iSendDataLen);

		pSendMsgHead = (PNPC_S_DPS_MSG_HEAD)pSendDataBuf;
		pSendMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)pSendMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pMp3FileList = (PNPC_S_DPS_CUSTOM_NI_BODY_QUERY_MP3_FILE_LIST)((PNPC_BYTE)pSendMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));
		pMp3FileInfo = (PNPC_S_DPS_CUSTOM_NI_BODY_MP3_FILE_INFO)((PNPC_BYTE)pMp3FileList + sizeof(NPC_S_DPS_CUSTOM_NI_BODY_QUERY_MP3_FILE_LIST));

		memcpy(pSendDataBuf, in_pMsgDataBuf, iPreMsgDataLen);

		pMp3FileList->o_iFilNum = 0;
		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed )
			{
				strcpy(pMp3FileInfo->sFileName, in_pMcSrvData->tMp3FileTable[i].sFileName);
				pMp3FileInfo->bIfPlaying = in_pMcSrvData->tMp3FileTable[i].bIfPlaying;

				pMp3FileInfo++;
				pMp3FileList->o_iFilNum++;
			}
		}

		pSendMsgBody->i_iBodyLen = sizeof(NPC_S_DPS_CUSTOM_NI_BODY_QUERY_MP3_FILE_LIST) + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_MP3_FILE_INFO) * pMp3FileList->o_iFilNum;

		pSendMsgHead->iMsgBodyLen = iSendDataLen - sizeof(NPC_S_DPS_MSG_HEAD);

		//-----------------------------------------------------------------------------
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			pSendDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			iSendDataLen						//�豸Э�����ݳ���
			);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( pSendDataBuf )
		{
			free(pSendDataBuf);
			pSendDataBuf = NULL;
		}
	}

	return bRet;
}

//ɾ��MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_DELETE_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_DELETE_MP3_FILE		pCusBodyPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_DELETE_MP3_FILE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Delete mp3 file, file name: %s.", pCusBodyPos->sFileName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed && 
				strcmp(in_pMcSrvData->tMp3FileTable[i].sFileName, pCusBodyPos->sFileName) == 0 )
			{
				in_pMcSrvData->tMp3FileTable[i].bIfUsed = FALSE;
				break;
			}
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//��ʼ����MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_START_PLAY_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_START_PLAY_MP3_FILE	pCusBodyPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_START_PLAY_MP3_FILE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Start play mp3 file, file name: %s.", pCusBodyPos->sFileName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed )
			{
				in_pMcSrvData->tMp3FileTable[i].bIfPlaying = FALSE;
			}
		}

		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed && 
				strcmp(in_pMcSrvData->tMp3FileTable[i].sFileName, pCusBodyPos->sFileName) == 0 )
			{
				in_pMcSrvData->tMp3FileTable[i].bIfPlaying = TRUE;
				break;
			}
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//ֹͣ����MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_STOP_PLAY_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_STOP_PLAY_MP3_FILE	pCusBodyPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_STOP_PLAY_MP3_FILE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Stop play mp3 file, file name: %s.", pCusBodyPos->sFileName);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed && 
				strcmp(in_pMcSrvData->tMp3FileTable[i].sFileName, pCusBodyPos->sFileName) == 0 )
			{
				in_pMcSrvData->tMp3FileTable[i].bIfPlaying = FALSE;
				break;
			}
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//��������
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_CTRL_VOLUME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_CTRL_VOLUME			pCusBodyPos;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_CTRL_VOLUME)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Ctrl volume, file name: %s, volume: %d.", pCusBodyPos->i_sFileName, pCusBodyPos->i_iVolumeSize);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( in_pMcSrvData->tMp3FileTable[i].bIfUsed && 
				strcmp(in_pMcSrvData->tMp3FileTable[i].sFileName, pCusBodyPos->i_sFileName) == 0 )
			{
				in_pMcSrvData->tMp3FileTable[i].iVolumeSize = pCusBodyPos->i_iVolumeSize;
				break;
			}
		}
	}

	//CLEAR AREA
	//_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//��ʼ�ϴ��ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_START_UPLOAD_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_START_UPLOAD_MP3_FILE	pCusBodyPos;
	PNPC_S_UMSP_MP3_FILE_DATA						pMp3FileInfo;
	NPC_CHAR										sTempFileName[256];
	NPC_INT											iUpFileIndex;
	NPC_INT											i;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_START_UPLOAD_MP3_FILE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Start Upload mp3 file, file name: %s, file size: %dB.", pCusBodyPos->i_sFileName, pCusBodyPos->i_dwFileSize);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		pMp3FileInfo = NULL;
		iUpFileIndex = -1;
		for ( i=0; i<in_pMcSrvData->iMp3FileNum; i++ )
		{
			if ( !in_pMcSrvData->tMp3FileTable[i].bIfUsed )
			{
				pMp3FileInfo = &in_pMcSrvData->tMp3FileTable[i];
				iUpFileIndex = i;
				break;
			}
		}
		if ( pMp3FileInfo == NULL )
		{
			if ( in_pMcSrvData->iMp3FileNum >= NPC_D_UMSP_MC_MAX_MP3_FILE_NUM )
			{
				//д��־
				NPC_F_LOG_SR_WriteLog("[UMSP]  Upload mp3 file fail, cause: upload file too mush.");

				in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR;
				goto _NPC_CLEAR;
			}
			pMp3FileInfo = &in_pMcSrvData->tMp3FileTable[in_pMcSrvData->iMp3FileNum];
			iUpFileIndex = in_pMcSrvData->iMp3FileNum;
			in_pMcSrvData->iMp3FileNum++;
		}

		pMp3FileInfo->bIfUsed = TRUE;
		pMp3FileInfo->bIfPlaying = FALSE;
		sprintf(pMp3FileInfo->sFileName, "M%d_%s", rand(), pCusBodyPos->i_sFileName);
		pMp3FileInfo->dwUpFileId = (rand()<<16) | iUpFileIndex;

		pCusBodyPos->o_dwUploadId = pMp3FileInfo->dwUpFileId;
		strcpy(pCusBodyPos->o_sSaveFileName, pMp3FileInfo->sFileName);

		sprintf(sTempFileName, "d:\\%s", pMp3FileInfo->sFileName);
		pMp3FileInfo->pSaveFile = fopen(sTempFileName, "wb");
		if ( pMp3FileInfo->pSaveFile == NULL )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  Upload mp3 file fail, cause: open file fail.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_OPEN_FAIL;
			goto _NPC_CLEAR;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//ֹͣ�ϴ��ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_STOP_UPLOAD_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_STOP_UPLOAD_MP3_FILE	pCusBodyPos;
	PNPC_S_UMSP_MP3_FILE_DATA						pMp3FileInfo;
	NPC_INT											iUpFileIndex;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_STOP_UPLOAD_MP3_FILE)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Stop upload mp3 file, upload ID: 0x%8.8X.", pCusBodyPos->i_dwUploadId);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		iUpFileIndex = pCusBodyPos->i_dwUploadId & 0xFFFF;
		if ( iUpFileIndex >= in_pMcSrvData->iMp3FileNum )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  Stop upload mp3 file fail, cuase: iUpFileIndex error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
			goto _NPC_CLEAR;
		}

		pMp3FileInfo = &in_pMcSrvData->tMp3FileTable[iUpFileIndex];
		if ( pMp3FileInfo->dwUpFileId != pCusBodyPos->i_dwUploadId )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  Stop upload mp3 file fail, cuase: i_dwUploadId error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
			goto _NPC_CLEAR;
		}

		//---------------------------------------------------------
		pMp3FileInfo->dwUpFileId = 0;

		if ( pMp3FileInfo->pSaveFile )
		{
			fclose(pMp3FileInfo->pSaveFile);
			pMp3FileInfo->pSaveFile = NULL;
		}
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}

//�ϴ��ļ�����
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_UPLOAD_FILE_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	)
{
	NPC_BOOL										bRet;
	PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM				pMsgBody;
	PNPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA		pCusBodyPos;
	PNPC_BYTE										pFileDataPos;
	NPC_INT											iFileDataLen;
	PNPC_S_UMSP_MP3_FILE_DATA						pMp3FileInfo;
	NPC_INT											iUpFileIndex;

	//INIT AREA
	{
		bRet = TRUE;
		pMsgBody = (PNPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM)((PNPC_BYTE)in_pMsgHead + sizeof(NPC_S_DPS_MSG_HEAD));
		pCusBodyPos = (PNPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA)((PNPC_BYTE)pMsgBody + sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM));
		pFileDataPos = (PNPC_BYTE)pCusBodyPos + sizeof(NPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA);
		iFileDataLen = in_iMsgDataLen - (
			sizeof(NPC_S_DPS_MSG_HEAD) + 
			sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM) + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA)
			);

		in_pMsgHead->ucMsgType = NPC_D_DPS_MSG_TYPE_RESPONSION;
		in_pMsgHead->ucResult = 0;
	}

	//CODE AREA
	{
		//��ʾ��Ϣ
		NPC_CHAR sTempLogBuf[512];
		sprintf(sTempLogBuf, "[UMSP]  Upload mp3 file data, upload ID: 0x%8.8X, data len: %d.", 
			pCusBodyPos->i_dwUploadId, pCusBodyPos->i_iDataLen);
		NPC_F_LOG_SR_ShowInfo(sTempLogBuf);

		iUpFileIndex = pCusBodyPos->i_dwUploadId & 0xFFFF;
		if ( iUpFileIndex >= in_pMcSrvData->iMp3FileNum )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  Stop upload mp3 file fail, cause: iUpFileIndex error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
			goto _NPC_CLEAR;
		}

		pMp3FileInfo = &in_pMcSrvData->tMp3FileTable[iUpFileIndex];
		if ( pMp3FileInfo->dwUpFileId != pCusBodyPos->i_dwUploadId )
		{
			//д��־
			NPC_F_LOG_SR_WriteLog("[UMSP]  Stop upload mp3 file fail, cause: i_dwUploadId error.");

			in_pMsgHead->ucResult = NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR;
			goto _NPC_CLEAR;
		}

		//----------------------------------------------------------------------------
		//�����ļ�
		if ( pMp3FileInfo->pSaveFile )
		{
			fwrite(pFileDataPos, 1, iFileDataLen, pMp3FileInfo->pSaveFile);
		}

		//----------------------------------------------------------------------------
		in_pMsgHead->iMsgBodyLen = 
			sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM) + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA);

		pMsgBody->i_iBodyLen = sizeof(NPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA);

		in_iMsgDataLen = 
			sizeof(NPC_S_DPS_MSG_HEAD) + 
			sizeof(NPC_S_DPS_MSG_BODY_EVENT_E7_CUSTOM) + 
			sizeof(NPC_S_DPS_CUSTOM_NI_BODY_UPLOAD_FILE_DATA);
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		//������Ϣ���豸Э���������
		NPC_F_DPS_SendDevProData(
			in_pMcSrvData->hUmspProSrv,			//�豸Э�����������
			in_pMsgDataBuf,						//�豸Э�����ݻ�����������NPC_S_DPS_MSG_HEAD
			in_iMsgDataLen						//�豸Э�����ݳ���
			);
	}

	return bRet;
}


//------------------------------------------------------------------------------------------
//�ر�������Ƶ��
NPC_BOOL	NPC_F_UMSP_MC_CloseVideoStream(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	)
{
	NPC_INT											i;
	PNPC_S_UMSP_CAMERA_DATA							pCameraData;

	for ( i=0; i<NPC_D_DPS_MAX_CHANNEL_NUM+1; i++ )
	{
		pCameraData = &in_pMcSrvData->tCameraTable[i];

		if ( !pCameraData->bIfUsed || pCameraData->hWorkLock == NULL )
			continue;

		//����
		NPC_F_THREAD_Mutex_Lock(
			pCameraData->hWorkLock		//���������
			);

		if ( pCameraData->bIfUsed )
		{
			if ( pCameraData->bMainStreamOpenFlag )
			{
				//���͹ر�ý������Ϣ
				NPC_F_UMSP_MC_SendCloseMediaStreamMsg(
					in_pMcSrvData,		//���ط�������
					i,					//ͨ����
					0					//����
					);
			}

			if ( pCameraData->bSubStreamOpenFlag )
			{
				//���͹ر�ý������Ϣ
				NPC_F_UMSP_MC_SendCloseMediaStreamMsg(
					in_pMcSrvData,		//���ط�������
					i,					//ͨ����
					1					//����
					);
			}

			if ( pCameraData->bTalkIfOpen )
			{
				//���͹رնԽ���Ϣ
				NPC_F_UMSP_MC_SendCloseTalkMsg(
					in_pMcSrvData,		//���ط�������
					i					//ͨ����
					);
			}

			//------------------------------------------------------------------
			pCameraData->bMainStreamOpenFlag = FALSE;
			pCameraData->bSubStreamOpenFlag = FALSE;
			pCameraData->bTalkIfOpen = FALSE;

			//����Ԥ��
			NPC_F_FILECAM_SDK_StopRealPlay(
				in_pMcSrvData->hFileCamera,			//�ļ���������
				i									//ͨ����
				);
			pCameraData->bIfUsed = FALSE;

			//ֹͣ¼��
			NPC_F_UMSP_MC_StopRecord(
				in_pMcSrvData,			//���ط�������
				pCameraData				//���������
				);
		}

		//����
		NPC_F_THREAD_Mutex_Unlock(
			pCameraData->hWorkLock			//���������
			);
	}

	return TRUE;
}



//------------------------------------------------------------------------------------------
//��������ID
NPC_VOID	NPC_F_UMSP_MC_CreateAlarmId(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	OUT		PNPC_CHAR								out_pAlarmId				//����ID
	)
{
	NPC_TIME_T										tCurTime;
	NPC_CHAR										sTimeStr[20];

	tCurTime = time(NULL);
	strftime(sTimeStr, 20, "%Y%m%d%H%M%S", localtime(&tCurTime));

	sprintf(out_pAlarmId, "UAI%s%4.4d", sTimeStr, in_pMcSrvData->uiAlarmSeqNo++);
}

//���ͱ�����Ϣ
NPC_VOID	NPC_F_UMSP_MC_SendAlarmInfo(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼�
	IN		PNPC_CHAR								in_pAlarmInfo				//������Ϣ
	)
{
	NPC_CHAR										sAlarmId[32];

	//��������ID
	NPC_F_UMSP_MC_CreateAlarmId(
		in_pMcSrvData,			//���ط�������
		sAlarmId				//����ID
		);

	//���ͱ�����Ϣ���ú������͵ı�����Ϣ������ɸѡ��ֱ�ӷ��͸���������
	NPC_F_DPS_SendAlarmMsg(
		in_pMcSrvData->hUmspProSrv,		//�豸Э�����������
		sAlarmId,						//����ID��Ҫ���豸��Ψһ���������ʱ��ֵ+��ţ���20150301091022001
		in_iChNo,						//ͨ����
		in_iAlarmEvent,					//�����¼����μ�NPC_D_MON_CSD_ALARM_EVENT_*����
		in_pAlarmInfo					//������Ϣ
		);
}

