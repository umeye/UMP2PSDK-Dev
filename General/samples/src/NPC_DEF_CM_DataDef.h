/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_DEF_CM_DataDef.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2011-08-21
 * Description   :  ͨ�ó�������
 *----------------------------------------------------------------------------*/

#ifndef __NPC_DEF_CM_DATADEF_H
#define __NPC_DEF_CM_DATADEF_H


#define NPC_D_DEF_CM_IPADDR_BUFSIZE						40			//IP��ַ��������С
#define NPC_D_DEF_CM_DEVID_BUFSIZE						16			//�豸ID��������С
#define NPC_D_DEF_CM_DEVNAME_BUFSIZE					64			//�豸���ƻ�������С
#define NPC_D_DEF_CM_USERNAME_BUFSIZE					64			//�û�����������С
#define NPC_D_DEF_CM_USERPWD_BUFSIZE					64			//���뻺������С
#define NPC_D_DEF_CM_EXTEND_PARAM_BUFSIZE				512			//��չ������������С
#define NPC_D_DEF_CM_BILLID_BUFSIZE						32			//������־ID��������С
#define NPC_D_DEF_CM_VEDIOFORMAT_BUFSIZE				32			//��Ƶ��ʽ��������С
#define NPC_D_DEF_CM_FILENAME_BUFSIZE					64			//�ļ�����������С

#define NPC_D_DEF_CM_H264_SPS_BUFSIZE					32			//H264������������������С
#define NPC_D_DEF_CM_H264_PPS_BUFSIZE					16			//H264ͼ���������������С

#define NPC_D_DEF_CM_VEDIO_PARAMS_BUFSIZE				64			//��Ƶ������������С
#define NPC_D_DEF_CM_AUDIO_PARAMS_BUFSIZE				32			//��Ƶ������������С


//--------------------------------------------------------------------------------
#define NPC_D_CMGW_MAX_DEV_VENDOR_NUM					2048		//����豸����������
#define NPC_D_CMGW_MAX_DEV_NUM							1024		//����豸������DVR��IPC��
#define NPC_D_CMGW_MAX_CH_NUM							64			//�豸�����ͨ����

#define NPC_D_CMGW_MAX_FILEVOD_NUM						1024		//����ļ��㲥��


//--------------------------------------------------------------------------------
//�豸���̶���
#define NPC_D_DISP_DEV_VENDOR_HIK						0			//����
#define NPC_D_DISP_DEV_VENDOR_DH						1			//��
#define NPC_D_DISP_DEV_VENDOR_FILECAM					2			//�ļ������
#define NPC_D_DISP_DEV_VENDOR_HKS						3			//������ý�������

//�豸���Ͷ���
#define NPC_D_DISP_DEV_TYPE_DVR							0			//DVR
#define NPC_D_DISP_DEV_TYPE_IPC							1			//IPC
#define NPC_D_DISP_DEV_TYPE_PLATFORM					2			//ƽ̨

#define NPC_D_DISP_DEV_TYPE_CAMERA						10			//�����

//--------------------------------------------------------------------------------
//��־���Ͷ���
#define NPC_D_LOGTYPE_SEVERITY							0			//����
#define NPC_D_LOGTYPE_IMPORTANCE						1			//��Ҫ
#define NPC_D_LOGTYPE_GENERAL							2			//һ��
#define NPC_D_LOGTYPE_PROMPT							3			//��ʾ��Ϣ



#endif
