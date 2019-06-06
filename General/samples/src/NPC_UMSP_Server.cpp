/*----------------------------------------------------------------------------
 * Copyright(c)  :  NPC CORPORTAION All Rights Reserved                       
 * FileName      :  NPC_UMSP_Server.cpp
 * Version       :  1.0
 * Author        :  CCH
 * DateTime      :  2013-08-10
 * Description   :  UMSP������
 *----------------------------------------------------------------------------*/

#include "NPC_PT_Server.h"
#include "NPC_UMSP_McServer.h"

PNPC_S_UMSP_MCSRV_DATA pMcSrvData = NULL;

//��������
NPC_PT_API bool NPC_SR_StartService(int argc, char* argv[])
{
	bool bRet;

	//INIT AREA
	{
		bRet = true;
	}

	//CODE AREA
	{
		if ( pMcSrvData )
			return true;

		//�����Ƿ�ʹ��Ӣ����ʾ��־ͷ
		NPC_F_LOG_SR_SetIfShowEnglishLogHead(
			TRUE		//�Ƿ���ʾӢ����־ͷ
			);

		pMcSrvData = (PNPC_S_UMSP_MCSRV_DATA)malloc(sizeof(NPC_S_UMSP_MCSRV_DATA));
		if ( pMcSrvData == NULL )
		{
			bRet = false;
			goto _NPC_CLEAR;
		}
		memset(pMcSrvData, 0, sizeof(NPC_S_UMSP_MCSRV_DATA));

		//�������ط���
		if ( !NPC_F_UMSP_MC_StartMcServer(
			pMcSrvData			//���ط�������
			) )
		{
			bRet = false;
			goto _NPC_CLEAR;
		}

		//д��־
		NPC_F_LOG_SR_WriteLog("[UMSP]  Start service success.");
	}

	//CLEAR AREA
	_NPC_CLEAR:
	{
		if ( !bRet )
		{
			//ֹͣ����
			NPC_SR_StopService();
		}
	}

	return bRet;
}

//ֹͣ����
NPC_PT_API void NPC_SR_StopService()
{
	if ( pMcSrvData )
	{
		//ֹͣ���ط���
		NPC_F_UMSP_MC_StopMcServer(
			pMcSrvData			//���ط�������
			);

		free(pMcSrvData);
		pMcSrvData = NULL;

		//д��־
		NPC_F_LOG_SR_WriteLog("Stop service success.");
	}
}



