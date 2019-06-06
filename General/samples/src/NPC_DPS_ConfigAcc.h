/*----------------------------------------------------------------------------
 * Copyright(c)  :  CORPORTAION  All Rights Reserved                       
 * FileName      :  NPC_DPS_ConfigAcc.h
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-12-24
 * Description   :  NPCϵͳ���ö�д�ӿ�
 *----------------------------------------------------------------------------*/

#ifndef __NPC_DPS_CONFIGACC_H
#define __NPC_DPS_CONFIGACC_H

#include "NPC_TypeDef.h"

#ifdef _WIN32
	#ifdef _NPC_DPS_CONFIGACC_EXPORTS
		#define NPC_CONFIGACC_API __declspec(dllexport)
	#else
		#ifdef _NPC_DPS_CONFIGACC_NON
			#define NPC_CONFIGACC_API
		#else
			#define NPC_CONFIGACC_API __declspec(dllimport)
		#endif
	#endif
#else
	#define NPC_CONFIGACC_API
#endif


///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
{
#endif

//��ȡ�ַ�������
NPC_CONFIGACC_API	NPC_BOOL	NPC_F_DPS_CA_GetString(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		PNPC_CHAR					in_pDefaultValue,		//ȱʡֵ
	OUT		PNPC_CHAR					out_pReturnBuf,			//���ػ�����
	IN		NPC_INT						in_iBufSize,			//��������С
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);

//��ȡ����ֵ
NPC_CONFIGACC_API	NPC_INT		NPC_F_DPS_CA_GetInt(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		NPC_INT						in_iDefaultValue,		//ȱʡֵ
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);

//��ȡ����ֵ
NPC_CONFIGACC_API	NPC_DOUBLE	NPC_F_DPS_CA_GetDouble(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		NPC_DOUBLE					in_dDefaultValue,		//ȱʡֵ
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);


//--------------------------------------------------------------------------------
//���ã�д���ַ���ֵ
NPC_CONFIGACC_API	NPC_BOOL	NPC_F_DPS_CA_SetString(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		PNPC_CHAR					in_pKeyValue,			//��ֵ
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);

//���ã�д������ֵ
NPC_CONFIGACC_API	NPC_BOOL	NPC_F_DPS_CA_SetInt(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		NPC_INT						in_iKeyValue,			//��ֵ
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);

//���ã�д������ֵ
NPC_CONFIGACC_API	NPC_BOOL	NPC_F_DPS_CA_SetDouble(
	IN		PNPC_CHAR					in_pMainKeyName,		//��������
	IN		PNPC_CHAR					in_pSubKeyName,			//�Ӽ�����
	IN		NPC_DOUBLE					in_dKeyValue,			//��ֵ
	IN		PNPC_CHAR					in_pFileName			//���ò����ļ�����
	);


#ifdef __cplusplus
}
#endif

#endif

