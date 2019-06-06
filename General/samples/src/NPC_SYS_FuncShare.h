/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_SYS_FuncShare.h
 * Version       :  1.1
 * Author        :  CCH
 * DateTime      :  2012-01-05
 * Description   :  NPCϵͳ���ù���ģ��
 *----------------------------------------------------------------------------*/

#ifndef __NPC_SYS_FUNCSHARE_H
#define __NPC_SYS_FUNCSHARE_H

#include "NPC_TypeDef.h"


//��ȡ����ʱ�������룩
NPC_DWORD	NPC_F_SYS_GetTickCount();

//�߳�����N����
NPC_VOID	NPC_F_SYS_Sleep(
	IN		NPC_INT							in_iTimeLen				//����ʱ�������룩
	);

//��time_t���͵�ʱ�䣬��ʽ��ΪYYYY-MM-DD HH24:MI:SS�͵��ַ���
NPC_VOID	NPC_F_SYS_Time_To_Str(
	IN		time_t							in_tTimeValue,			//ʱ��ֵ
	OUT		PNPC_CHAR						out_pTimeStr			//ʱ���ַ���
	);

//��YYYY-MM-DD HH24:MI:SS��ʽ��ʱ���ַ�����ת��Ϊtime_t�͵�ʱ��
time_t		NPC_F_SYS_Str_To_Time(
	IN		PNPC_CHAR						in_pTimeStr				//ʱ���ַ���
	);

//��ʱ�����ת��Ϊtime_t
time_t		NPC_F_SYS_TimeParam_To_Timet(
	IN		NPC_INT							in_iYear,				//��
	IN		NPC_INT							in_iMonth,				//��
	IN		NPC_INT							in_iDay,				//��
	IN		NPC_INT							in_iHour,				//ʱ
	IN		NPC_INT							in_iMinute,				//��
	IN		NPC_INT							in_iSecond				//��
	);

//��time_tת��Ϊʱ�����
NPC_VOID	NPC_F_SYS_Timet_To_TimeParam(
	IN		time_t							in_tTimeValue,			//ʱ��ֵ
	OUT		PNPC_INT						out_pYear,				//��
	OUT		PNPC_INT						out_pMonth,				//��
	OUT		PNPC_INT						out_pDay,				//��
	OUT		PNPC_INT						out_pHour,				//ʱ
	OUT		PNPC_INT						out_pMinute,			//��
	OUT		PNPC_INT						out_pSecond				//��
	);

//��time_tת��ΪNPC_S_TD_DATE_TIMEʱ��
NPC_VOID	NPC_F_SYS_Timet_To_TdTime(
	IN		time_t							in_tTimeValue,			//ʱ��ֵ
	OUT		PNPC_S_TD_DATE_TIME				out_pTdTime				//TDʱ��
	);

//���ֶδ�ʱ��ת��ΪNPC_S_TD_DATE_TIMEʱ��
NPC_VOID	NPC_F_SYS_StrTime_To_TdTime(
	IN		PNPC_CHAR						in_pTimeStr,			//ʱ���ַ�������ʽΪ��YYYY-MM-DD HH24:MI:SS
	OUT		PNPC_S_TD_DATE_TIME				out_pTdTime				//TDʱ��
	);

//��NPC_S_TD_DATE_TIMEת��Ϊtime_tʱ��
time_t		NPC_F_SYS_TdTime_To_Timet(
	IN		PNPC_S_TD_DATE_TIME				in_pTdTime				//TDʱ��
	);

//��NPC_S_TD_DATE_TIMEת��Ϊʱ���ַ���
NPC_VOID	NPC_F_SYS_TdTime_To_TimeStr(
	IN		PNPC_S_TD_DATE_TIME				in_pTdTime,				//TDʱ��
	OUT		PNPC_CHAR						out_pTimeStr			//ʱ���ַ���
	);

//��ʱ���ַ���ת��ΪNPC_S_TD_TIME
NPC_VOID	NPC_F_SYS_Str_To_Time(
	IN		PNPC_CHAR						in_pTimeStr,				//ʱ���ַ�������ʽΪ��HH:MM:SS
	OUT		PNPC_S_TD_TIME					out_pTimeObj				//ʱ�����
	);

//��NPC_S_TD_TIMEת��ʱ���ַ���
NPC_VOID	NPC_F_SYS_Time_To_Str(
	IN		PNPC_S_TD_TIME					in_pTimeObj,				//ʱ�����
	OUT		PNPC_CHAR						out_pTimeStr				//ʱ���ַ�������ʽΪ��HH:MM:SS
	);

//��������ʱ��֮���ʱ��
NPC_DWORD	NPC_F_SYS_ComputeTdTimeLen(
	IN		PNPC_S_TD_DATE_TIME				in_pBeginTime,			//��ʼʱ��
	IN		PNPC_S_TD_DATE_TIME				in_pEndTime				//����ʱ��
	);

//��������
NPC_USHORT	NPC_F_SYS_CheckSum(
	IN		PNPC_BYTE						in_pDataBuf,			//���ݻ�����
	IN		NPC_INT							in_iDataLen				//���ݳ���
	);

//��ȡIP��ַ������IP��ֵַ����˳��
NPC_VOID	NPC_F_SYS_GetIpaddrStrByHost(
	IN		NPC_DWORD						in_dwIpaddr,			//IP��ֵַ
	OUT		PNPC_CHAR						out_pIpaddrStr			//IP��ַ�ַ���
	);

//���ַ���IP��ַת��������˳���IP��ֵַ
NPC_DWORD	NPC_F_SYS_IpaddrStrToHostIpaddr(
	IN		PNPC_CHAR						in_pIpaddrStr			//IP��ַ�ַ���
	);

//��������MAC��ַת�����ַ���MAC��ַ
NPC_VOID	NPC_F_SYS_GetStringMacAddr(
	IN		PNPC_BYTE						in_pBitMac,				//������MAC��ַ
	OUT		PNPC_CHAR						out_pStrMac				//�ַ���MAC��ַ
	);

//���ַ���MAC��ַת���ɶ�����MAC��ַ
NPC_VOID	NPC_F_SYS_GetBitMacAddr(
	IN		PNPC_CHAR						in_pStrMac,				//�ַ���MAC��ַ
	OUT		PNPC_BYTE						out_pBitMac				//������MAC��ַ
	);

//�����ַ���MAC��ַ��ʽ�Ƿ���ȷ
NPC_BOOL	NPC_F_SYS_CheckMacStrAddr(
	IN		PNPC_CHAR						in_pStrMac				//�ַ���MAC��ַ����ʽΪXX-XX-XX-XX-XX-XX
	);

//����������������ת����ʮ�������ַ���
NPC_BOOL	NPC_F_SYS_BitDataToHexStr(
	IN		PNPC_BYTE						in_pBitDataBuf,			//���������ݻ�����
	IN		NPC_INT							in_iBitDataLen,			//���������ݳ���
	OUT		PNPC_CHAR*						out_ppHexStrBuf			//ʮ�������ַ������������ɸú��������ڴ棬�ϲ��ͷ��ڴ�
	);

//��ʮ�������ַ���ת�����޷�������ֵ
NPC_DWORD	NPC_F_SYS_HexStrToDWORD(
	IN		PNPC_CHAR						in_pHexStrBuf			//ʮ�������ַ�������������0x12345678����12345678
	);

//�滻�ַ����е�ָ��λ��
NPC_BOOL	NPC_F_SYS_ReplaceString(
	IN		PNPC_CHAR						in_pStrBuf,				//�ַ���������
	IN		NPC_INT							in_iBeginPos,			//��ʼλ��
	IN		NPC_INT							in_iOldLen,				//ԭ����
	IN		PNPC_CHAR						in_pNewValue			//��ֵ
	);

//�滻JSON�Ľ��ֵ��ֻ�滻��һ������ֵ
NPC_BOOL	NPC_F_SYS_ReplaceJsonValue(
	IN		PNPC_CHAR						in_pJsonDocBuf,			//JSON�ĵ�������
	IN		PNPC_CHAR						in_pNodeName,			//�������
	IN		PNPC_CHAR						in_pNodeNewValue		//�����ֵ������ֵ������
	);

//�滻�ַ���
NPC_BOOL	NPC_F_SYS_ReplaceStringEx(
	IN		PNPC_CHAR						in_pStrBuf,				//�ַ���������
	IN		PNPC_CHAR						in_pOldStr,				//Դ�ַ���
	IN		PNPC_CHAR						in_pNewStr				//���ַ���
	);

//���Դ�Сд�Ƚ��ַ���
NPC_INT		NPC_F_SYS_StrCaseCmp(
	IN		PNPC_CHAR						in_pStr1,				//�ַ���1
	IN		PNPC_CHAR						in_pStr2				//�ַ���2
	);

//�����ո��TAB��
NPC_VOID	NPC_F_SYS_StrOp_JumpSpace(
	INOUT	PNPC_CHAR*						inout_ppStr				//�ַ���
	);

//��ȡһ���ַ���������0��ʾ�ɹ���1��ʾδ�ҵ���2��ʾ���ػ�����̫С
NPC_INT		NPC_F_SYS_StrOp_GetSectString(
	INOUT	PNPC_CHAR*						inout_ppSrcStr,			//ԭ�ַ�����������ȡ֮���λ��
	IN		PNPC_CHAR						in_pFindStr,			//��ѯ�ַ���
	IN		NPC_INT							in_iGetStrBufSize,		//���ص��ַ�����������С
	OUT		PNPC_CHAR						out_pGetStrBuf			//���ص��ַ��������������ϲ����
	);

//ȥ����ո��TAB��
NPC_VOID	NPC_F_SYS_RemoveLeftSpace(
	IN		PNPC_CHAR						in_pStr					//�ַ���
	);

//ȥ���ҿո��TAB��
NPC_VOID	NPC_F_SYS_RemoveRightSpace(
	IN		PNPC_CHAR						in_pStr					//�ַ���
	);

//ȥ�����ҿո��TAB��
NPC_VOID	NPC_F_SYS_RemoveTwoWaySpace(
	IN		PNPC_CHAR						in_pStr					//�ַ���
	);


//--------------------------------------------------------------------------------------------------
//��ȡһ��BIT
NPC_BYTE	NPC_F_SYS_MG_get_one_bit(NPC_BYTE* &ppBytePos, NPC_INT &iBitPos, NPC_INT &iSyByteNum);

//��ȡһ��BIT
NPC_UINT	NPC_F_SYS_MG_read_bits(NPC_BYTE* &ppBytePos, NPC_INT &iBitPos, NPC_INT &iSyByteNum, NPC_INT iReadBitNum);

//��ȡUE
NPC_UINT	NPC_F_SYS_MG_get_ue(NPC_BYTE* &ppBytePos, NPC_INT &iBitPos, NPC_INT &iSyByteNum);


//--------------------------------------------------------------------------------------------------
//��ȡ�����
NPC_UINT	NPC_F_SYS_GetRandomNumber();

//�����Ʊ���
NPC_BOOL	NPC_F_SYS_BIT_Encode(
	IN		PNPC_BYTE						in_pBitDataBuf,			//���������ݻ�����
	IN		NPC_INT							in_iBitDataLen,			//���������ݳ���
	IN		PNPC_CHAR						in_pMapTable,			//ӳ���
	OUT		PNPC_CHAR						out_pCodecStrBuf		//�����ַ������ռ�Ϊin_iBitDataLen*2
	);

//��������Ϊ����������
NPC_BOOL	NPC_F_SYS_BIT_Decode(
	IN		PNPC_CHAR						in_pCodecStr,			//�����ַ���
	IN		PNPC_CHAR						in_pMapTable,			//ӳ���
	OUT		PNPC_BYTE						out_pBitDataBuf,		//���������ݻ�����
	OUT		PNPC_INT						out_pBitDataLen			//���������ݳ���
	);


//--------------------------------------------------------------------------------
//��ѯ�ַ���
NPC_BOOL	NPC_F_SYS_QueryStr(
	IN		PNPC_BYTE						in_pFindDataBuf,		//����ѯ�����ݻ�����
	IN		NPC_INT							in_iFindDataLen,		//����ѯ�����ݳ���
	IN		PNPC_CHAR						in_pFindStr,			//��ѯ�ַ���
	OUT		PNPC_BYTE*						out_ppFindPos,			//��ѯ����λ��
	OUT		PNPC_INT						out_pSyDataLen			//ʣ�����ݳ���
	);

//��ȡһ������
NPC_BOOL	NPC_F_SYS_GetLineData(
	IN		PNPC_BYTE						in_pFindDataBuf,		//����ѯ�����ݻ�����
	IN		NPC_INT							in_iFindDataLen,		//����ѯ�����ݳ���
	OUT		PNPC_INT						out_pLineDataLen,		//�����ݳ���
	OUT		PNPC_BYTE*						out_ppNextFindPos,		//��һ����ѯλ��
	OUT		PNPC_INT						out_pSyDataLen			//ʣ�����ݳ���
	);


#endif

