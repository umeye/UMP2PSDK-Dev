/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_MON_ConsDef.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-12
 * Description   :  ��������
 *----------------------------------------------------------------------------*/

#ifndef __NPC_MON_CONSDEF_H
#define __NPC_MON_CONSDEF_H

#include "NPC_TypeDef.h"


//-------------------------------------------------------------------------------
//��������
#define NPC_D_MON_CSD_MAX_FILE_FLAG_LEN								128				//����ļ���ʶ��

//-------------------------------------------------------------------------------
//����ID����
#define NPC_D_MON_CSD_CODEC_ID_UNKNOWN								0				//δ֪����

#define NPC_D_MON_CSD_CODEC_ID_VEDIO_H264							1				//H264
#define NPC_D_MON_CSD_CODEC_ID_VEDIO_MPEG4							2				//MPEG4
#define NPC_D_MON_CSD_CODEC_ID_VEDIO_MJPG							3				//MJPG
#define NPC_D_MON_CSD_CODEC_ID_VEDIO_H265							4				//H265

#define NPC_D_MON_CSD_CODEC_ID_AUDIO_AAC							1				//AAC
#define NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMA							2				//PCMA��G711A��
#define NPC_D_MON_CSD_CODEC_ID_AUDIO_PCMU							3				//PCMU��G711U��
#define NPC_D_MON_CSD_CODEC_ID_AUDIO_ADPCM							4				//ADPCM
#define NPC_D_MON_CSD_CODEC_ID_AUDIO_G726							5				//G726
#define NPC_D_MON_CSD_CODEC_ID_AUDIO_AMRNB							6				//AMRNB

//��Ƶ֡����
#define NPC_D_MON_CSD_VIDEO_FRAME_TYPE_UNKNOWN						0				//δ֪����
#define NPC_D_MON_CSD_VIDEO_FRAME_TYPE_I							1				//I֡
#define NPC_D_MON_CSD_VIDEO_FRAME_TYPE_P							2				//P֡
#define NPC_D_MON_CSD_VIDEO_FRAME_TYPE_B							3				//B֡

//��Ƶ�ֱ���
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_1080P						1				//1080P
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_720P							2				//720P
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_D1							3				//D1
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_HD1							4				//HD1
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_BCIF							5				//BCIF
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_CIF							6				//CIF
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_QCIF							7				//QCIF
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_VGA							8				//VGA
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_QVGA							9				//QVGA
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_SVCD							10				//SVCD
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_QQVGA						11				//QQVGA
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_SXVGA						12				//SXVGA
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_UXGA							13				//UXGA
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_960H							14				//960H
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_960P							15				//960P
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_3M							16				//3M:2304 * 1296
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_4M							17				//4M:2592 * 1520
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_5M							18				//5M:2592 * 1944
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_UHD4K						19				//UHD4K:3840 * 2160
#define NPC_D_MON_CSD_VEDIO_RESOLUTION_12M							20				//12M:4000 * 3000





//ͼƬ��ʽ����
#define NPC_D_MON_CSD_PIC_FORMAT_BMP								1				//BMP�ļ�
#define NPC_D_MON_CSD_PIC_FORMAT_JPEG								2				//JPEG�ļ�

//��������ģʽ
#define NPC_D_MON_CSD_BITRATECTRL_CBR								1				//�̶�����
#define NPC_D_MON_CSD_BITRATECTRL_VBR								2				//�ɱ�����
#define NPC_D_MON_CSD_BITRATECTRL_MBR								3				//�������

//PTZ�����
#define NPC_D_MON_CSD_PTZ_CMD_STOP									0				//ֹͣ�˶���ֹͣǰһ����������

#define NPC_D_MON_CSD_PTZ_CMD_SET_PRESET							8				//����Ԥ�õ㣬in_dwPtzDataΪԤ�õ����ţ�1��255��
#define NPC_D_MON_CSD_PTZ_CMD_CLE_PRESET							9				//���Ԥ�õ㣬in_dwPtzDataΪԤ�õ����ţ�1��255��

#define NPC_D_MON_CSD_PTZ_CMD_ZOOM_IN								11				//�������ٶ�SS��󣨱��ʱ�󣩣�in_dwPtzDataΪ�ٶȣ�1��10�����ƾ��ٶȳ�ʼֵΪ4��in_dwPtzExtParam1Ϊ�Ƿ��Զ�ֹͣ��1��0����in_dwPtzExtParam2Ϊ�Զ�ֹͣ�ļ��ʱ�䣨1��255�룩
#define NPC_D_MON_CSD_PTZ_CMD_ZOOM_OUT								12				//�������ٶ�SS��С�����ʱ�С����ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_FOCUS_NEAR							13  			//�������ٶ�SSǰ����ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_FOCUS_FAR								14  			//�������ٶ�SS�����ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_IRIS_OPEN								15  			//��Ȧ���ٶ�SS����ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_IRIS_CLOSE							16  			//��Ȧ���ٶ�SS��С��ͬ��

#define NPC_D_MON_CSD_PTZ_CMD_TILT_UP								21				//��̨��SS���ٶ�������in_dwPtzDataΪ�ٶȣ�1��10������̨�ٶȳ�ʼֵΪ4��in_dwPtzExtParam1Ϊ�Ƿ��Զ�ֹͣ��1��0����in_dwPtzExtParam2Ϊ�Զ�ֹͣ�ļ��ʱ�䣨1��255�룩
#define NPC_D_MON_CSD_PTZ_CMD_TILT_DOWN								22				//��̨��SS���ٶ��¸���ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_PAN_LEFT								23				//��̨��SS���ٶ���ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_PAN_RIGHT								24				//��̨��SS���ٶ���ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_UP_LEFT								25				//��̨��SS���ٶ���������ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_UP_RIGHT								26				//��̨��SS���ٶ���������ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_DOWN_LEFT								27				//��̨��SS���ٶ��¸�����ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_DOWN_RIGHT							28				//��̨��SS���ٶ��¸�����ת��ͬ��
#define NPC_D_MON_CSD_PTZ_CMD_PAN_AUTO								29				//��̨��SS���ٶ������Զ�ɨ�裬ͬ��

#define NPC_D_MON_CSD_PTZ_CMD_FILL_PRE_SEQ							30				//��Ԥ�õ����Ѳ�����У�in_dwPtzDataΪѲ��·���ţ�1��32����in_dwPtzExtParam1ΪѲ����ţ�1��32����in_dwPtzExtParam2ΪԤ�õ�ţ�1��255��
#define NPC_D_MON_CSD_PTZ_CMD_SET_SEQ_DWELL							31				//����Ѳ����ͣ��ʱ�䣬in_dwPtzDataΪѲ��·���ţ�1��32����in_dwPtzExtParam1ΪѲ����ţ�1��32����in_dwPtzExtParam2Ϊͣ��ʱ�䣨1��255�룩
#define NPC_D_MON_CSD_PTZ_CMD_SET_SEQ_SPEED							32				//����Ѳ���ٶȣ�in_dwPtzDataΪѲ��·���ţ�1��32����in_dwPtzExtParam1ΪѲ����ţ�1��32����in_dwPtzExtParam2Ϊ�ٶȣ�1��10��
#define NPC_D_MON_CSD_PTZ_CMD_CLE_PRE_SEQ							33				//��Ԥ�õ��Ѳ��������ɾ����in_dwPtzDataΪѲ��·���ţ�1��32����in_dwPtzExtParam1ΪѲ����ţ�1��32����in_dwPtzExtParam2ΪԤ�õ�ţ�1��255��
#define NPC_D_MON_CSD_PTZ_CMD_STA_MEM_CRUISE						34				//��ʼ��¼�켣�����޲���
#define NPC_D_MON_CSD_PTZ_CMD_STO_MEM_CRUISE						35				//ֹͣ��¼�켣���޲���
#define NPC_D_MON_CSD_PTZ_CMD_RUN_CRUISE							36				//��ʼ�켣���޲���
#define NPC_D_MON_CSD_PTZ_CMD_RUN_SEQ								37				//��ʼѲ����in_dwPtzDataΪѲ��·����
#define NPC_D_MON_CSD_PTZ_CMD_STOP_SEQ								38				//ֹͣѲ����in_dwPtzDataΪѲ��·����
#define NPC_D_MON_CSD_PTZ_CMD_GOTO_PRESET							39				//����ת��Ԥ�õ㣬in_dwPtzDataΪԤ�õ��
#define NPC_D_MON_PTZ_CMD_CLEAR_TOUR                                40				//���Ѳ����in_dwPtzDataΪѲ��·����

#define NPC_D_MON_CSD_PTZ_CMD_UTC_DETECT							101				//UTC ̽���Ƿ�֧��
#define NPC_D_MON_CSD_PTZ_CMD_UTC_SET								102				//UTC ����
#define NPC_D_MON_CSD_PTZ_CMD_UTC_UP								103				//UTC ��
#define NPC_D_MON_CSD_PTZ_CMD_UTC_DOWN								104				//UTC �� 
#define NPC_D_MON_CSD_PTZ_CMD_UTC_LEFT								105				//UTC ��
#define NPC_D_MON_CSD_PTZ_CMD_UTC_RIGHT								106				//UTC ��
#define NPC_D_MON_CSD_PTZ_CMD_UTC_FOCUS_NEER						107				//UTC �۽�
#define NPC_D_MON_CSD_PTZ_CMD_UTC_FOCUS_FAR							108				//UTC �۽�
#define NPC_D_MON_CSD_PTZ_CMD_UTC_ZOOM_WIDE							109				//UTC ZOOM
#define NPC_D_MON_CSD_PTZ_CMD_UTC_ZOOM_TELE							110				//UTC ZOOM
#define NPC_D_MON_CSD_PTZ_CMD_UTC_STOP								111				//UTC ֹͣ




//�ļ����Ͷ���
#define NPC_D_MON_CSD_FILE_TYPE_ALL									0				//�����ļ�����
#define NPC_D_MON_CSD_FILE_TYPE_RECORD								1				//¼���ļ�
#define NPC_D_MON_CSD_FILE_TYPE_PICTRUE								2				//�����ļ�

//�ļ�������ʽ����
#define NPC_D_MON_CSD_FILE_CREATE_MODE_ALL							0				//���з�ʽ
#define NPC_D_MON_CSD_FILE_CREATE_MODE_ALARM						1				//������ʽ
#define NPC_D_MON_CSD_FILE_CREATE_MODE_MANUAL						2				//�ֶ���ʽ
#define NPC_D_MON_CSD_FILE_CREATE_MODE_TIMER						3				//��ʱ��ʽ

//�����¼�����
#define NPC_D_MON_CSD_ALARM_EVENT_ALL								0				//���б����¼�
#define NPC_D_MON_CSD_ALARM_EVENT_FAULT								1				//�豸���ϱ���
#define NPC_D_MON_CSD_ALARM_EVENT_MOTION							2				//�ƶ���ⱨ��
#define NPC_D_MON_CSD_ALARM_EVENT_VIDEO_BLIND						3				//��Ƶ�ڵ�����
#define NPC_D_MON_CSD_ALARM_EVENT_VIDEO_LOSS						4				//��Ƶ��ʧ����
#define NPC_D_MON_CSD_ALARM_EVENT_PROBE								5				//̽ͷ�������ⲿ���뱨����
#define NPC_D_MON_CSD_ALARM_EVENT_PIR								6				//�����Ӧ����
#define NPC_D_MON_CSD_ALARM_EVENT_DOORBELL							7				//���屨��
#define NPC_D_MON_CSD_ALARM_EVENT_HDD_ERROR							8				//Ӳ�̴���
#define NPC_D_MON_CSD_ALARM_EVENT_HDD_FULL							9				//Ӳ����
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_CROSS_LINE				10				//Խ����ⱨ��
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_INTRUSION			11				//�������ֱ���
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_IN					12				//������뱨��
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_OUT				13				//�����뿪����
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_OBJECT_FORGET			14				//��Ʒ��������
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_OBJECT_PICKUP			15				//��Ʒʰȡ����
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_FAST					16				//�����ƶ�
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_FACE_RECOGNITION		17				//����ʶ��
#define NPC_D_MON_CSD_ALARM_EVENT_KNOCK								18				//���ű���
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_WANDER_DETECT           19              //�ǻ���ⱨ��
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_PARK               20              //ͣ����ⱨ��
#define NPC_D_MON_CSD_ALARM_EVENT_SMART_IPC_AREA_CROWD              21              //��Ա�ۼ�����


//DPSЭ������붨��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_SUCCESS						0				//�ɹ�

#define NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_OP					1				//��֧�ָò���
#define NPC_D_MON_CSD_DPS_ERROR_CODE_BAN_MODIFY						2				//��ֹ�޸�
#define NPC_D_MON_CSD_DPS_ERROR_CODE_MSGFUNC_ERROR					3				//��Ϣ���ܴ���
#define NPC_D_MON_CSD_DPS_ERROR_CODE_PARAM_ERROR					4				//��������
#define NPC_D_MON_CSD_DPS_ERROR_CODE_ID_ERROR						5				//ID����

#define NPC_D_MON_CSD_DPS_ERROR_CODE_OTHER							9				//����ԭ��

#define NPC_D_MON_CSD_DPS_ERROR_CODE_OPEN_STREAM_FAIL				20				//��ý����ʧ�ܣ���ʵʱԤ��ʧ�ܣ�
#define NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_SUBSTREAM			21				//��֧�ָ�������
#define NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_PTZ				22				//��֧����̨����
#define NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_FORCE_I_FRAME		23				//��֧��ǿ��I֡
#define NPC_D_MON_CSD_DPS_ERROR_CODE_NOT_SUPPORT_TALK				24				//��֧�������Խ�
#define NPC_D_MON_CSD_DPS_ERROR_CODE_CHANNEL_NO_ERROR				25				//ͨ���Ŵ���
#define NPC_D_MON_CSD_DPS_ERROR_CODE_SUB_STREAM_NO_ERROR			26				//�������Ŵ���
#define NPC_D_MON_CSD_DPS_ERROR_CODE_START_TALK_FAIL				27				//�����Խ�ʧ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_USERNAME_ERROR					28				//�û�������
#define NPC_D_MON_CSD_DPS_ERROR_CODE_PASSWORD_ERROR					29				//�������

#define NPC_D_MON_CSD_DPS_ERROR_CODE_WITHOUT_PERMISSION				101				//�޴�Ȩ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_NO_SUBSCRIBE					102				//û�ж���
#define NPC_D_MON_CSD_DPS_ERROR_CODE_QUERY_FILE_FAIL				103				//��ѯ�ļ�ʧ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_USED					104				//��Դ�ѱ�ռ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_OPEN				105				//��Դ��δ����
#define NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NO_IDLE				106				//�޿�����Դ��ʹ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_NOT_EXIST				107				//��Դ������
#define NPC_D_MON_CSD_DPS_ERROR_CODE_RESOURCE_OPEN_FAIL				108				//����Դʧ��
#define NPC_D_MON_CSD_DPS_ERROR_CODE_FILE_OP_FAIL					109				//�ļ�����ʧ��

#define NPC_D_MON_CSD_DPS_ERROR_CODE_SUCCESS_AND_RESTART			200				//�����ɹ�������Ҫ�����豸����Ч


//�Զ�������뷶Χ��150~179


#endif

