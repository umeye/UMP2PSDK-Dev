/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_UMSP_McServer.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-10
 * Description   :  UMSP����������ģ��
 *----------------------------------------------------------------------------*/

#ifndef __NPC_UMSP_MCSERVER_H
#define __NPC_UMSP_MCSERVER_H

#include "NPC_TypeDef.h"
#include "NPC_UMSP_DataDef.h"


//-------------------------------------------------------------------------------
//�������ط���
NPC_BOOL	NPC_F_UMSP_MC_StartMcServer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//ֹͣ���ط���
NPC_VOID	NPC_F_UMSP_MC_StopMcServer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//��ʼ������
NPC_BOOL	NPC_F_UMSP_MC_InitData(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//����ʼ������
NPC_VOID	NPC_F_UMSP_MC_UninitData(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//��ȡ����
NPC_BOOL	NPC_F_UMSP_MC_ReadConfig(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//��ȡ��̬����
NPC_BOOL	NPC_F_UMSP_MC_ReadDynamicConfig(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);


//-------------------------------------------------------------------------------
//�����߳�
NPC_BOOL	NPC_F_UMSP_MC_StartThread(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//�˳��߳�
NPC_VOID	NPC_F_UMSP_MC_QuitThread(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//�����߳�
NPC_VOID	NPC_F_UMSP_MC_ThreadWork(
	IN		PNPC_VOID								in_pParameter				//����ָ��
	);

//����ʱ��
NPC_VOID	NPC_F_UMSP_MC_DoTimer(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);


//-------------------------------------------------------------------------------
//����Э���¼�����ý����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_OPEN_MEDIA_STREAM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼����ر�ý����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_CLOSE_MEDIA_STREAM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����̨����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_PTZ_CTRL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�������ǿ�Ʒ���I֡
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FORCE_I_FRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//����Э���¼�����ȡ��Ƶ�����ȼ������б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_CAP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ȡ��Ƶ�����ȼ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GET_VIDEO_QUALITY_LEVEL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼���������Ƶ�����ȼ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_SET_VIDEO_QUALITY_LEVEL(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//����Э���¼�����ѯ�ļ���¼���ͼƬ�ļ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����չ��ѯ�ļ���¼���ͼƬ�ļ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_NSP_FILE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ѯ¼���ļ�ʱ�䷶Χ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RANGE_QUERY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼������ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼������ļ�,��ʱ�䷽ʽ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_OPEN_BY_TIME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼����ر��ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_CLOSE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ȡ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_READ(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����λ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����λ�ļ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_SEEK_BY_TIME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ѯ��Ƶ����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_QVIDEO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�������I֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_ONLY_IFRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�������ָ�ȫ֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_FILE_RECOVER_ALLFRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//����Э���¼�����ʼ�����Խ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_START(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼���ֹͣ�����Խ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_TALK_STOP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_GUARD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E2_UNGUARD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼����޸��û�����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_USER_PWD(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ȡ���ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼����������ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_SET_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����ȡȱʡ���ò���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_GET_DEF_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_IMP_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼�����������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_IEC_EXP_CONFIG(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);



//����Э���¼�����ѯ������Ϣ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_QUERY_NET_INFO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//����Э���¼����޸������ַ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_MODIFY_NET_ADDR(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//-----------------------------------------------------------------------------------
//�򿪴���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_OPEN(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�رմ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_CLOSE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��������(�ͻ��˷��͸��豸��)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SEND_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�豸��������(�豸�˷��͸��ͻ���)(��Ӧ��)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_COM_SUBS_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//-----------------------------------------------------------------------------------
//�����û�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_ADD_USER(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//ɾ���û�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_DEL_USER(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ȡ�û�Ȩ���б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_GET_USER_POP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�����û�Ȩ���б�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E3_UNS_SET_USER_POP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//-----------------------------------------------------------------------------------
//���ƹ���
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_CUSTOM(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//-----------------------------------------------------------------------------------
//��ѯ������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_QUERY_ABILITY(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�����豸(�ް���)(��Ӧ����Ϣ)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_REBOOT(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//ֹͣ�豸(�ް���)(��Ӧ����Ϣ)
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_RMY_STOP(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);



//-----------------------------------------------------------------------------------
//��ѯ�豸�汾��Ϣ
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_DEV_VER_INFO(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_REQU_UPGRADE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ѯ��������
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_PROGRESS(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ѯ����λ��
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_QUERY_TRANS_POS(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�������ݰ�
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_EVENT_E7_DUP_UPGRADE_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);



//-----------------------------------------------------------------------------------
//����Э���¼�����Ƶ֡����
NPC_VOID	NPC_F_UMSP_MC_DoProEvent_MEDIA_E8_AUDIO_FRAME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//-----------------------------------------------------------------------------------
//���֡���ͣ�����֡���ͣ�0��δ��⵽��1��I֡��2��P֡
NPC_INT		NPC_F_UMSP_MC_CheckFrameType(
	IN		PNPC_BYTE								in_pFrameDataBuf,			//֡���ݻ�����
	IN		NPC_INT									in_iFrameDataLen			//֡���ݳ���
	);


//-----------------------------------------------------------------------------------
//��ʼ¼��
NPC_BOOL	NPC_F_UMSP_MC_StartRecord(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData,				//���������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iFrameRate				//֡��
	);

//ֹͣ¼��
NPC_VOID	NPC_F_UMSP_MC_StopRecord(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData				//���������
	);


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
	);

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
	);


//��ȡ¼���ļ�ʱ�䷶Χ
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
	);

//��ѯ�ļ�,��ȡ��һ���ļ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_NspFindFirstFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo,				//������
	IN		PNPC_S_TD_DATE_TIME						in_pStartTime,				//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME						in_pEndTime,				//����ʱ��
	INOUT	PNPC_S_MON_MPS_FILE_HEAD_INFO			io_pFileInfo				//�ļ���Ϣ
	);

//��ȡ¼���ļ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_ReadRecFileInfo(
	IN		PNPC_CHAR								in_pFileName,				//�ļ���������·��
	OUT		PNPC_S_NAV_AV_FORMAT					out_pAvFormat,				//�ļ���ʽ
	OUT		PNPC_CHAR								out_pRecBeginTime,			//¼�ƿ�ʼʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_CHAR								out_pRecEndTime,			//¼�ƽ���ʱ�䣬��ʽΪ��YYYY-MM-DD HH:MM:SS
	OUT		PNPC_DWORD								out_pRecTimeLen				//¼��ʱ�����룩
	);


//-----------------------------------------------------------------------------------
//���ļ���������ΪNPC_D_MON_CSD_DPS_ERROR_CODE_*
NPC_INT		NPC_F_UMSP_MC_File_OpenFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_CHAR								in_pFileFlag,				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
	IN		NPC_DWORD								in_dwStartOffsetDataPos,	//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
	IN		NPC_DWORD								in_dwStartOffsetTimePos,	//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
	OUT		PNPC_DWORD								out_pFileReadId,			//�����ļ���ȡID
	OUT		PNPC_S_MON_MPS_FILE_INFO				out_pFileInfo				//�ļ���Ϣ
	);

//���ļ�����ʱ�䷽ʽ����������ΪNPC_D_MON_CSD_DPS_ERROR_CODE_*
NPC_INT		NPC_F_UMSP_MC_File_OpenFile_BY_TIME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_CHAR								in_pFileFlag,				//�ļ���ʶ��Ψһ��ʶ���ļ������ļ�ʱ����ԭ������
	IN		NPC_DWORD								in_dwStartOffsetDataPos,	//��ʼ��ȡ����λ�ã���λ�ֽڣ���ָԭʼ�ļ��Ķ�ȡλ��
	IN		NPC_DWORD								in_dwStartOffsetTimePos,	//��ʼ��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ�䣬���ֵ�����ļ���ʱ�������ʧ��
	OUT		PNPC_DWORD								out_pFileReadId,			//�����ļ���ȡID
	OUT		PNPC_S_MON_MPS_FILE_INFO				out_pFileInfo				//�ļ���Ϣ
	);

//�ر��ļ�
NPC_VOID	NPC_F_UMSP_MC_File_CloseFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId				//�ļ���ȡID
	);

//��λ�ļ���������ΪNPC_D_MON_CSD_DPS_ERROR_CODE_*
NPC_INT		NPC_F_UMSP_MC_File_SeekFile(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId,			//�ļ���ȡID
	IN		NPC_DWORD								in_dwOffsetTimePos			//��ȡʱ��λ�ã���λ�룩��Ϊ���ʱ��
	);

//��ȡ�ļ�����Ƶ����
NPC_BOOL	NPC_F_UMSP_MC_File_GetFileVideoParam(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId,			//�ļ���ȡID
	OUT		PNPC_INT								out_pFrameRate,				//֡��
	OUT		PNPC_INT								out_pGOP					//GOP
	);

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
	);

//��ѯ�ļ��������ݣ������ļ���ID��
PNPC_S_UMSP_FILE_WORK_DATA		NPC_F_UMSP_MC_File_QueryFileWorkDataByFileReadId(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_DWORD								in_dwFileReadId				//�ļ���ȡID
	);


//-----------------------------------------------------------------------------------
//�����ļ���С
NPC_LONG	NPC_F_UMSP_MC_ComputeFileSize(
	IN		PNPC_CHAR								in_pFileName				//�ļ���������·����
	);


//-----------------------------------------------------------------------------------
//������״̬
NPC_VOID	NPC_F_UMSP_MC_DoAlarmState(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);

//���ͱ�����Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendAlarmMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_UMSP_CAMERA_DATA					in_pCameraData,				//���������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼�
	IN		NPC_INT									in_iAlarmState				//����״̬
	);

//���͹ر�ý������Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendCloseMediaStreamMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iStreamNo				//����
	);

//���͹رնԽ���Ϣ
NPC_BOOL	NPC_F_UMSP_MC_SendCloseTalkMsg(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo					//ͨ����
	);


//-----------------------------------------------------------------------------------
//�޸��û����룬����0��ʾ�ɹ���1���û�������2��ԭ�������9������ʧ��
NPC_INT		NPC_F_UMSP_MC_ModifyUserPwd(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_CHAR								in_pUserName,				//�û���
	IN		PNPC_CHAR								in_pOldPwd,					//ԭ����
	IN		PNPC_CHAR								in_pNewPwd					//������
	);

//��ѯ������Ϣ
NPC_INT		NPC_F_UMSP_MC_QueryNetInfo(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	OUT		PNPC_INT								out_pNetCardNum,			//������
	OUT		PNPC_BYTE								out_ppNetCardDataBuf,		//�������ݻ�������ΪNPC_S_DPS_MSG_BODY_EVENT_E3_NET_CARD_INFO����
	OUT		PNPC_INT								out_pNetCardDataLen			//�������ݳ���
	);


//------------------------------------------------------------------------------------------
//��ѯMP3�ļ��б�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_QUERY_MP3_FILE_LIST(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//ɾ��MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_DELETE_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ʼ����MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_START_PLAY_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//ֹͣ����MP3�ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_STOP_PLAY_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��������
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_CTRL_VOLUME(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//��ʼ�ϴ��ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_START_UPLOAD_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//ֹͣ�ϴ��ļ�
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_STOP_UPLOAD_MP3_FILE(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);

//�ϴ��ļ�����
NPC_BOOL	NPC_F_UMSP_MC_DoCustomEvent_UPLOAD_FILE_DATA(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		PNPC_S_DPS_MSG_HEAD						in_pMsgHead,				//��Ϣͷ
	IN		PNPC_BYTE								in_pMsgDataBuf,				//��Ϣ���ݻ�����������NPC_S_DPS_MSG_HEAD
	IN		NPC_INT									in_iMsgDataLen				//��Ϣ���ݳ���
	);


//------------------------------------------------------------------------------------------
//�ر�������Ƶ��
NPC_BOOL	NPC_F_UMSP_MC_CloseVideoStream(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData				//���ط�������
	);


//------------------------------------------------------------------------------------------
//��������ID
NPC_VOID	NPC_F_UMSP_MC_CreateAlarmId(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	OUT		PNPC_CHAR								out_pAlarmId				//����ID
	);

//���ͱ�����Ϣ
NPC_VOID	NPC_F_UMSP_MC_SendAlarmInfo(
	IN		PNPC_S_UMSP_MCSRV_DATA					in_pMcSrvData,				//���ط�������
	IN		NPC_INT									in_iChNo,					//ͨ����
	IN		NPC_INT									in_iAlarmEvent,				//�����¼�
	IN		PNPC_CHAR								in_pAlarmInfo				//������Ϣ
	);


#endif


