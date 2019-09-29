#ifndef _TP_COMMON_XML_STRUCT_H_
#define _TP_COMMON_XML_STRUCT_H_

#include "xmlengine.h"
#include "msgmgr.h"
#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "tpcommonxmltype.h"

const char XmlTpStructVersion[] = "2017-12-22 10:12:18";

#define XML_TP_TYPE_NUM      292
#define XML_TP_STRUCT_NUM    370

#define ENUMTYPE( type )\
	const TXDATAINFO type##membertable[] = {#type,emx_##type,"enum",4,1,0,0,(char*)#type};

#define TYPESTRUCT_BEGIN( s )\
	const TXDATAINFO s##membertable[]={
#define TYPESTRUCT_MEMBER( s,type ,m )\
	{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),0,XML_OffSetOf(s,m),(char*)#m},
#define TYPESTRUCT_MATRIX( s,type ,m )\
	{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),XML_SizeOfMatrix(s,type,m),XML_OffSetOf(s,m),(char*)#m},
#define TYPESTRUCT_END( s )\
	{#s,emxDataTypeEnd,0,sizeof(s),0,0,0,#s}};

ENUMTYPE(EmTPDevRegUpdateSer);
ENUMTYPE(EmTPUpdateType);
ENUMTYPE(EmWiFiLinkStat);
ENUMTYPE(EmWiFiSelType);
ENUMTYPE(EmWiFiNetType);
ENUMTYPE(EmWiFiEncryptType);
ENUMTYPE(EmWiFiEncryptArithmetic);
ENUMTYPE(EmVODRejCode);
ENUMTYPE(EmVODState);
ENUMTYPE(EmTextAlign);
ENUMTYPE(EmRollMode);
ENUMTYPE(EmRollSpeed);
ENUMTYPE(EmStopBits);
ENUMTYPE(EmParityCheck);
ENUMTYPE(EmSerialType);
ENUMTYPE(EmLanguage);
ENUMTYPE(EmConfProtocol);
ENUMTYPE(EmEncodeMode);
ENUMTYPE(EmLostPackageRestore);
ENUMTYPE(EmMatrixType);
ENUMTYPE(EmDualVideoShowMode);
ENUMTYPE(EmDisplayRatio);
ENUMTYPE(EmVideoType);
ENUMTYPE(EmVideoStandard);
ENUMTYPE(EmVideoInterface);
ENUMTYPE(EmMtVideoPort);
ENUMTYPE(EmTripMode);
ENUMTYPE(EmLabelType);
ENUMTYPE(EmDLProtocol);
ENUMTYPE(EmAuthenticationType);
ENUMTYPE(EmFrameUnitType);
ENUMTYPE(EmMediaType);
ENUMTYPE(EmVideoFormat);
ENUMTYPE(EmAudioFormat);
ENUMTYPE(EmVideoResolution);
ENUMTYPE(EmQoS);
ENUMTYPE(EmTOS);
ENUMTYPE(EmSite);
ENUMTYPE(EmChanType);
ENUMTYPE(EmCodecComponent);
ENUMTYPE(EmMtModel);
ENUMTYPE(EmFileSys);
ENUMTYPE(EmEncryptArithmetic);
ENUMTYPE(EmAction);
ENUMTYPE(EmOptRet);
ENUMTYPE(EmConfMode);
ENUMTYPE(EmMtAddrType);
ENUMTYPE(EmCallMode);
ENUMTYPE(EmDirection);
ENUMTYPE(EmCallState);
ENUMTYPE(EmCallSiteState);
ENUMTYPE(EmTransMode);
ENUMTYPE(EmDualSrcType);
ENUMTYPE(EmMtInstType);
ENUMTYPE(EmVMPStyle);
ENUMTYPE(EmVMPMmbType);
ENUMTYPE(EmSMSType);
ENUMTYPE(EmMtFile);
ENUMTYPE(EmCallRate);
ENUMTYPE(EmPCCapFormat);
ENUMTYPE(EmPiPMode);
ENUMTYPE(EmDVBComponent);
ENUMTYPE(EmUIPosion);
ENUMTYPE(EmCallDisconnectReason);
ENUMTYPE(EmMCMode);
ENUMTYPE(EmInnerVMPStyle);
ENUMTYPE(EmVMPComponent);
ENUMTYPE(EmCapType);
ENUMTYPE(EmPPPoEState);
ENUMTYPE(EmDhcpState);
ENUMTYPE(EmAddrGroupOptType);
ENUMTYPE(EmHotKeyType);
ENUMTYPE(EmMtOSType);
ENUMTYPE(EmFxoState);
ENUMTYPE(EmMtLoudspeakerVal);
ENUMTYPE(EmNetType);
ENUMTYPE(EmSysRunSuccessFlag);
ENUMTYPE(EmMcuNtfMsgType);
ENUMTYPE(EmAutoTestType);
ENUMTYPE(EmGKRegFailedReason);
ENUMTYPE(EmSleepState);
ENUMTYPE(EmMtAppName);
ENUMTYPE(HD_PORT_MASK);
ENUMTYPE(EmHDAudPortIn);
ENUMTYPE(EmHDAudPortOut);
ENUMTYPE(EmLogStatus);
ENUMTYPE(EmLogExportResult);
ENUMTYPE(EmFecModeType);
ENUMTYPE(EmLabelPosType);
ENUMTYPE(EmMtcBoxCallIndex);
ENUMTYPE(EmSipRegFailedReason);
ENUMTYPE(EMtRecChnnlState);
ENUMTYPE(EMtRecChnnlType);
ENUMTYPE(EMtRecMode);
ENUMTYPE(EMtRecEnum);
ENUMTYPE(EmMtRegResult);
ENUMTYPE(EmTpRet);
ENUMTYPE(EmTpHduPlayNackReason);
ENUMTYPE(EmTpLoginUmsRet);
ENUMTYPE(EmTpAliasType);
ENUMTYPE(EmTpOprType);
ENUMTYPE(EmConfAddEpRet);
ENUMTYPE(EmTpIFrameCheckType);
ENUMTYPE(EmTPEncryptType);
ENUMTYPE(EmTPRcvAlignType);
ENUMTYPE(EmCnsCallReason);
ENUMTYPE(EmTPChannelReason);
ENUMTYPE(EmTpCnsType);
ENUMTYPE(EmTpCnsRegUms);
ENUMTYPE(EmTpConfTemplateRet);
ENUMTYPE(EmTpStartConfRet);
ENUMTYPE(EmTpApplySpeakerRet);
ENUMTYPE(EmTpDropConfRet);
ENUMTYPE(EmTpApplySpeakRet);
ENUMTYPE(EmUmsConfNodeState);
ENUMTYPE(EmFlowCtrlOpr);
ENUMTYPE(EMBrdType);
ENUMTYPE(EMEqpType);
ENUMTYPE(EMEqpModleType);
ENUMTYPE(EMOsType);
ENUMTYPE(EMVmpStyle);
ENUMTYPE(EmTpVideoFormat);
ENUMTYPE(EmTpEncodeMode);
ENUMTYPE(EmTpVideoQualityLevel);
ENUMTYPE(EmTpVideoResolution);
ENUMTYPE(EmTpMediaType);
ENUMTYPE(EmTpPCCapFormat);
ENUMTYPE(EmTpCodecComponent);
ENUMTYPE(EmTpAudioFormat);
ENUMTYPE(EmTpLostPackageRestore);
ENUMTYPE(EmTpCallMode);
ENUMTYPE(EmTpConnectionType);
ENUMTYPE(EmTpConfProtocol);
ENUMTYPE(EmTPAddrType);
ENUMTYPE(EmTPEndpointType);
ENUMTYPE(EmTPSipLevel);
ENUMTYPE(EmCALLSTATE);
ENUMTYPE(EmCallType);
ENUMTYPE(EmTPVideoType);
ENUMTYPE(EmTPVideoPort);
ENUMTYPE(EmTPCNSInfoRst);
ENUMTYPE(EmTPRegResult);
ENUMTYPE(EmCnMtRegResult);
ENUMTYPE(EmCnModel);
ENUMTYPE(EmFocusMode);
ENUMTYPE(EmFocus);
ENUMTYPE(EmZoom);
ENUMTYPE(EmCnAction);
ENUMTYPE(EmOSDShow);
ENUMTYPE(EmWBMode);
ENUMTYPE(EmExpMode);
ENUMTYPE(EmGain);
ENUMTYPE(EmShutSpd);
ENUMTYPE(EmBackLightType);
ENUMTYPE(EmPicSceMode);
ENUMTYPE(EmGamma);
ENUMTYPE(EmStmClean);
ENUMTYPE(Em3DNR);
ENUMTYPE(EmCamPowerMode);
ENUMTYPE(EmCenSchMode);
ENUMTYPE(EmTvPowerMode);
ENUMTYPE(EmTvSrcPowerMode);
ENUMTYPE(EmTVAudVisMode);
ENUMTYPE(EmTVDisplayMode);
ENUMTYPE(EmTVInputSelect);
ENUMTYPE(EmDCamWBMode);
ENUMTYPE(EmDCamAFMode);
ENUMTYPE(EmDCamPower);
ENUMTYPE(EmDCamZoom);
ENUMTYPE(EmDCamPresetNum);
ENUMTYPE(EmDCamRecallNum);
ENUMTYPE(EmSchPower);
ENUMTYPE(EmSchLight);
ENUMTYPE(EmSchMidLight);
ENUMTYPE(EmSchScrLight);
ENUMTYPE(EmSchArgus);
ENUMTYPE(EmCentreACPower);
ENUMTYPE(EmCentreACAirVol);
ENUMTYPE(EmCentreACMode);
ENUMTYPE(EmCurAction);
ENUMTYPE(EmCurChannelMode);
ENUMTYPE(EmSchGatewayType);
ENUMTYPE(EmTpMixStatus);
ENUMTYPE(EmTPDualReason);
ENUMTYPE(EmTPPayloadType);
ENUMTYPE(EmTPPosStatus);
ENUMTYPE(EmTPPollResult);
ENUMTYPE(EmTPViewResult);
ENUMTYPE(EmTPViewLocalResult);
ENUMTYPE(EmTPDisOprType);
ENUMTYPE(EMPosPic);
ENUMTYPE(EMDSCREATETYPE);
ENUMTYPE(EmTPAddDualRcvResult);
ENUMTYPE(EmTPDeleteDualRcvResult);
ENUMTYPE(EmTPMtModel);
ENUMTYPE(EmDsType);
ENUMTYPE(EmCnAudioMixID);
ENUMTYPE(EmGetRegInfoType);
ENUMTYPE(EmGetRegInfoOpr);
ENUMTYPE(EmTPChanType);
ENUMTYPE(EmTPAACSampleFreq);
ENUMTYPE(EmTPG7221Rate);
ENUMTYPE(EmTPAACChnlCfg);
ENUMTYPE(EmTPTpApplySpeakerRet);
ENUMTYPE(EmTPChanSubType);
ENUMTYPE(EmMakeCallType);
ENUMTYPE(EmTpRegType);
ENUMTYPE(EmDisListOprType);
ENUMTYPE(EmDisListOprReslt);
ENUMTYPE(EmVgaType);
ENUMTYPE(EmDualInputType);
ENUMTYPE(EmDualOutputType);
ENUMTYPE(EmVgaSwitchResult);
ENUMTYPE(EmVgaSwitchReason);
ENUMTYPE(EmCnState);
ENUMTYPE(EmTPCapSign);
ENUMTYPE(EmSwitchState);
ENUMTYPE(EmTpBoardRet);
ENUMTYPE(EmHduOutPort);
ENUMTYPE(EmHduZoomRate);
ENUMTYPE(EmHduOutMode);
ENUMTYPE(EmHduShowMode);
ENUMTYPE(EmModifyNMServerRet);
ENUMTYPE(EmModifyVcrRet);
ENUMTYPE(EmModifyHduRet);
ENUMTYPE(EmUpdateHduRet);
ENUMTYPE(EmMPCodec);
ENUMTYPE(EmTPHDAudPortIn);
ENUMTYPE(EmTPHDDualAudPortIn);
ENUMTYPE(EmTPHDAudPortOut);
ENUMTYPE(EmTPMtVideoPort);
ENUMTYPE(EmTPMtVideoOutPort);
ENUMTYPE(EmTPAutoTestType);
ENUMTYPE(EmTPHduRunStatus);
ENUMTYPE(EmTPLoudspeakerVal);
ENUMTYPE(EmTPFrameUnitType);
ENUMTYPE(EmTPVideoStandard);
ENUMTYPE(EmTPLabelType);
ENUMTYPE(EmTPLabelPosType);
ENUMTYPE(EmTPDualVideoShowMode);
ENUMTYPE(EmTPDisplayRatio);
ENUMTYPE(EmTPFecModeType);
ENUMTYPE(EmTPNetType);
ENUMTYPE(EmTPEqualizerRate);
ENUMTYPE(EmTPPIPMode);
ENUMTYPE(EmTPDVIMode);
ENUMTYPE(EmTPMCMode);
ENUMTYPE(EmCnsUpdateState);
ENUMTYPE(EmTPCnLoginUpdateRet);
ENUMTYPE(EmTPFileSrvUsedVersion);
ENUMTYPE(EmTPFileSrvFileType);
ENUMTYPE(EmTPOSType);
ENUMTYPE(EmMPAudEncCodec);
ENUMTYPE(EmToolType);
ENUMTYPE(EmProducetestType);
ENUMTYPE(EmMdyRecFileRes);
ENUMTYPE(EmUseReccorderRes);
ENUMTYPE(EmRecorderType);
ENUMTYPE(EmConfRecState);
ENUMTYPE(EmTpProfile);
ENUMTYPE(EmTPHandleCfgType);
ENUMTYPE(EmTpCodecType);
ENUMTYPE(EmToolState);
ENUMTYPE(EmTPAudPlayMode);
ENUMTYPE(EmTPAudDualInMode);
ENUMTYPE(EmTPDualType);
ENUMTYPE(EmTPDsNode);
ENUMTYPE(EMScreenLooked);
ENUMTYPE(EmTPDVIOutPortType);
ENUMTYPE(EmTPMOONOutMode);
ENUMTYPE(EmTPImageAdjust);
ENUMTYPE(EmTPMOOMMode);
ENUMTYPE(EmTPManualMode);
ENUMTYPE(EmTPZOOM);
ENUMTYPE(EmTPExpGain);
ENUMTYPE(EmTPSOrThShutter);
ENUMTYPE(EmTPFOrTwShutter);
ENUMTYPE(EmTPAperture);
ENUMTYPE(EmTPReduNoise);
ENUMTYPE(EmTPImagePara);
ENUMTYPE(EmImageMosaicType);
ENUMTYPE(EmTPFpgaReduNoise);
ENUMTYPE(EmMOONProductTestType);
ENUMTYPE(EmTPLVDSBaud);
ENUMTYPE(EmTPCorrect);
ENUMTYPE(EmTpVer);
ENUMTYPE(EmTPCorrectChange);
ENUMTYPE(EmTPCamNoiseLevel);
ENUMTYPE(EmTPMechanism);
ENUMTYPE(EmH650Gamma);
ENUMTYPE(EmTPColorConsistency);
ENUMTYPE(EmTPDistortPosition);

TXDATAINFO* g_tTpEnumData[]={
	(TXDATAINFO*)EmTPDevRegUpdateSermembertable,
	(TXDATAINFO*)EmTPUpdateTypemembertable,
	(TXDATAINFO*)EmWiFiLinkStatmembertable,
	(TXDATAINFO*)EmWiFiSelTypemembertable,
	(TXDATAINFO*)EmWiFiNetTypemembertable,
	(TXDATAINFO*)EmWiFiEncryptTypemembertable,
	(TXDATAINFO*)EmWiFiEncryptArithmeticmembertable,
	(TXDATAINFO*)EmVODRejCodemembertable,
	(TXDATAINFO*)EmVODStatemembertable,
	(TXDATAINFO*)EmTextAlignmembertable,
	(TXDATAINFO*)EmRollModemembertable,
	(TXDATAINFO*)EmRollSpeedmembertable,
	(TXDATAINFO*)EmStopBitsmembertable,
	(TXDATAINFO*)EmParityCheckmembertable,
	(TXDATAINFO*)EmSerialTypemembertable,
	(TXDATAINFO*)EmLanguagemembertable,
	(TXDATAINFO*)EmConfProtocolmembertable,
	(TXDATAINFO*)EmEncodeModemembertable,
	(TXDATAINFO*)EmLostPackageRestoremembertable,
	(TXDATAINFO*)EmMatrixTypemembertable,
	(TXDATAINFO*)EmDualVideoShowModemembertable,
	(TXDATAINFO*)EmDisplayRatiomembertable,
	(TXDATAINFO*)EmVideoTypemembertable,
	(TXDATAINFO*)EmVideoStandardmembertable,
	(TXDATAINFO*)EmVideoInterfacemembertable,
	(TXDATAINFO*)EmMtVideoPortmembertable,
	(TXDATAINFO*)EmTripModemembertable,
	(TXDATAINFO*)EmLabelTypemembertable,
	(TXDATAINFO*)EmDLProtocolmembertable,
	(TXDATAINFO*)EmAuthenticationTypemembertable,
	(TXDATAINFO*)EmFrameUnitTypemembertable,
	(TXDATAINFO*)EmMediaTypemembertable,
	(TXDATAINFO*)EmVideoFormatmembertable,
	(TXDATAINFO*)EmAudioFormatmembertable,
	(TXDATAINFO*)EmVideoResolutionmembertable,
	(TXDATAINFO*)EmQoSmembertable,
	(TXDATAINFO*)EmTOSmembertable,
	(TXDATAINFO*)EmSitemembertable,
	(TXDATAINFO*)EmChanTypemembertable,
	(TXDATAINFO*)EmCodecComponentmembertable,
	(TXDATAINFO*)EmMtModelmembertable,
	(TXDATAINFO*)EmFileSysmembertable,
	(TXDATAINFO*)EmEncryptArithmeticmembertable,
	(TXDATAINFO*)EmActionmembertable,
	(TXDATAINFO*)EmOptRetmembertable,
	(TXDATAINFO*)EmConfModemembertable,
	(TXDATAINFO*)EmMtAddrTypemembertable,
	(TXDATAINFO*)EmCallModemembertable,
	(TXDATAINFO*)EmDirectionmembertable,
	(TXDATAINFO*)EmCallStatemembertable,
	(TXDATAINFO*)EmCallSiteStatemembertable,
	(TXDATAINFO*)EmTransModemembertable,
	(TXDATAINFO*)EmDualSrcTypemembertable,
	(TXDATAINFO*)EmMtInstTypemembertable,
	(TXDATAINFO*)EmVMPStylemembertable,
	(TXDATAINFO*)EmVMPMmbTypemembertable,
	(TXDATAINFO*)EmSMSTypemembertable,
	(TXDATAINFO*)EmMtFilemembertable,
	(TXDATAINFO*)EmCallRatemembertable,
	(TXDATAINFO*)EmPCCapFormatmembertable,
	(TXDATAINFO*)EmPiPModemembertable,
	(TXDATAINFO*)EmDVBComponentmembertable,
	(TXDATAINFO*)EmUIPosionmembertable,
	(TXDATAINFO*)EmCallDisconnectReasonmembertable,
	(TXDATAINFO*)EmMCModemembertable,
	(TXDATAINFO*)EmInnerVMPStylemembertable,
	(TXDATAINFO*)EmVMPComponentmembertable,
	(TXDATAINFO*)EmCapTypemembertable,
	(TXDATAINFO*)EmPPPoEStatemembertable,
	(TXDATAINFO*)EmDhcpStatemembertable,
	(TXDATAINFO*)EmAddrGroupOptTypemembertable,
	(TXDATAINFO*)EmHotKeyTypemembertable,
	(TXDATAINFO*)EmMtOSTypemembertable,
	(TXDATAINFO*)EmFxoStatemembertable,
	(TXDATAINFO*)EmMtLoudspeakerValmembertable,
	(TXDATAINFO*)EmNetTypemembertable,
	(TXDATAINFO*)EmSysRunSuccessFlagmembertable,
	(TXDATAINFO*)EmMcuNtfMsgTypemembertable,
	(TXDATAINFO*)EmAutoTestTypemembertable,
	(TXDATAINFO*)EmGKRegFailedReasonmembertable,
	(TXDATAINFO*)EmSleepStatemembertable,
	(TXDATAINFO*)EmMtAppNamemembertable,
	(TXDATAINFO*)HD_PORT_MASKmembertable,
	(TXDATAINFO*)EmHDAudPortInmembertable,
	(TXDATAINFO*)EmHDAudPortOutmembertable,
	(TXDATAINFO*)EmLogStatusmembertable,
	(TXDATAINFO*)EmLogExportResultmembertable,
	(TXDATAINFO*)EmFecModeTypemembertable,
	(TXDATAINFO*)EmLabelPosTypemembertable,
	(TXDATAINFO*)EmMtcBoxCallIndexmembertable,
	(TXDATAINFO*)EmSipRegFailedReasonmembertable,
	(TXDATAINFO*)EMtRecChnnlStatemembertable,
	(TXDATAINFO*)EMtRecChnnlTypemembertable,
	(TXDATAINFO*)EMtRecModemembertable,
	(TXDATAINFO*)EMtRecEnummembertable,
	(TXDATAINFO*)EmMtRegResultmembertable,
	(TXDATAINFO*)EmTpRetmembertable,
	(TXDATAINFO*)EmTpHduPlayNackReasonmembertable,
	(TXDATAINFO*)EmTpLoginUmsRetmembertable,
	(TXDATAINFO*)EmTpAliasTypemembertable,
	(TXDATAINFO*)EmTpOprTypemembertable,
	(TXDATAINFO*)EmConfAddEpRetmembertable,
	(TXDATAINFO*)EmTpIFrameCheckTypemembertable,
	(TXDATAINFO*)EmTPEncryptTypemembertable,
	(TXDATAINFO*)EmTPRcvAlignTypemembertable,
	(TXDATAINFO*)EmCnsCallReasonmembertable,
	(TXDATAINFO*)EmTPChannelReasonmembertable,
	(TXDATAINFO*)EmTpCnsTypemembertable,
	(TXDATAINFO*)EmTpCnsRegUmsmembertable,
	(TXDATAINFO*)EmTpConfTemplateRetmembertable,
	(TXDATAINFO*)EmTpStartConfRetmembertable,
	(TXDATAINFO*)EmTpApplySpeakerRetmembertable,
	(TXDATAINFO*)EmTpDropConfRetmembertable,
	(TXDATAINFO*)EmTpApplySpeakRetmembertable,
	(TXDATAINFO*)EmUmsConfNodeStatemembertable,
	(TXDATAINFO*)EmFlowCtrlOprmembertable,
	(TXDATAINFO*)EMBrdTypemembertable,
	(TXDATAINFO*)EMEqpTypemembertable,
	(TXDATAINFO*)EMEqpModleTypemembertable,
	(TXDATAINFO*)EMOsTypemembertable,
	(TXDATAINFO*)EMVmpStylemembertable,
	(TXDATAINFO*)EmTpVideoFormatmembertable,
	(TXDATAINFO*)EmTpEncodeModemembertable,
	(TXDATAINFO*)EmTpVideoQualityLevelmembertable,
	(TXDATAINFO*)EmTpVideoResolutionmembertable,
	(TXDATAINFO*)EmTpMediaTypemembertable,
	(TXDATAINFO*)EmTpPCCapFormatmembertable,
	(TXDATAINFO*)EmTpCodecComponentmembertable,
	(TXDATAINFO*)EmTpAudioFormatmembertable,
	(TXDATAINFO*)EmTpLostPackageRestoremembertable,
	(TXDATAINFO*)EmTpCallModemembertable,
	(TXDATAINFO*)EmTpConnectionTypemembertable,
	(TXDATAINFO*)EmTpConfProtocolmembertable,
	(TXDATAINFO*)EmTPAddrTypemembertable,
	(TXDATAINFO*)EmTPEndpointTypemembertable,
	(TXDATAINFO*)EmTPSipLevelmembertable,
	(TXDATAINFO*)EmCALLSTATEmembertable,
	(TXDATAINFO*)EmCallTypemembertable,
	(TXDATAINFO*)EmTPVideoTypemembertable,
	(TXDATAINFO*)EmTPVideoPortmembertable,
	(TXDATAINFO*)EmTPCNSInfoRstmembertable,
	(TXDATAINFO*)EmTPRegResultmembertable,
	(TXDATAINFO*)EmCnMtRegResultmembertable,
	(TXDATAINFO*)EmCnModelmembertable,
	(TXDATAINFO*)EmFocusModemembertable,
	(TXDATAINFO*)EmFocusmembertable,
	(TXDATAINFO*)EmZoommembertable,
	(TXDATAINFO*)EmCnActionmembertable,
	(TXDATAINFO*)EmOSDShowmembertable,
	(TXDATAINFO*)EmWBModemembertable,
	(TXDATAINFO*)EmExpModemembertable,
	(TXDATAINFO*)EmGainmembertable,
	(TXDATAINFO*)EmShutSpdmembertable,
	(TXDATAINFO*)EmBackLightTypemembertable,
	(TXDATAINFO*)EmPicSceModemembertable,
	(TXDATAINFO*)EmGammamembertable,
	(TXDATAINFO*)EmStmCleanmembertable,
	(TXDATAINFO*)Em3DNRmembertable,
	(TXDATAINFO*)EmCamPowerModemembertable,
	(TXDATAINFO*)EmCenSchModemembertable,
	(TXDATAINFO*)EmTvPowerModemembertable,
	(TXDATAINFO*)EmTvSrcPowerModemembertable,
	(TXDATAINFO*)EmTVAudVisModemembertable,
	(TXDATAINFO*)EmTVDisplayModemembertable,
	(TXDATAINFO*)EmTVInputSelectmembertable,
	(TXDATAINFO*)EmDCamWBModemembertable,
	(TXDATAINFO*)EmDCamAFModemembertable,
	(TXDATAINFO*)EmDCamPowermembertable,
	(TXDATAINFO*)EmDCamZoommembertable,
	(TXDATAINFO*)EmDCamPresetNummembertable,
	(TXDATAINFO*)EmDCamRecallNummembertable,
	(TXDATAINFO*)EmSchPowermembertable,
	(TXDATAINFO*)EmSchLightmembertable,
	(TXDATAINFO*)EmSchMidLightmembertable,
	(TXDATAINFO*)EmSchScrLightmembertable,
	(TXDATAINFO*)EmSchArgusmembertable,
	(TXDATAINFO*)EmCentreACPowermembertable,
	(TXDATAINFO*)EmCentreACAirVolmembertable,
	(TXDATAINFO*)EmCentreACModemembertable,
	(TXDATAINFO*)EmCurActionmembertable,
	(TXDATAINFO*)EmCurChannelModemembertable,
	(TXDATAINFO*)EmSchGatewayTypemembertable,
	(TXDATAINFO*)EmTpMixStatusmembertable,
	(TXDATAINFO*)EmTPDualReasonmembertable,
	(TXDATAINFO*)EmTPPayloadTypemembertable,
	(TXDATAINFO*)EmTPPosStatusmembertable,
	(TXDATAINFO*)EmTPPollResultmembertable,
	(TXDATAINFO*)EmTPViewResultmembertable,
	(TXDATAINFO*)EmTPViewLocalResultmembertable,
	(TXDATAINFO*)EmTPDisOprTypemembertable,
	(TXDATAINFO*)EMPosPicmembertable,
	(TXDATAINFO*)EMDSCREATETYPEmembertable,
	(TXDATAINFO*)EmTPAddDualRcvResultmembertable,
	(TXDATAINFO*)EmTPDeleteDualRcvResultmembertable,
	(TXDATAINFO*)EmTPMtModelmembertable,
	(TXDATAINFO*)EmDsTypemembertable,
	(TXDATAINFO*)EmCnAudioMixIDmembertable,
	(TXDATAINFO*)EmGetRegInfoTypemembertable,
	(TXDATAINFO*)EmGetRegInfoOprmembertable,
	(TXDATAINFO*)EmTPChanTypemembertable,
	(TXDATAINFO*)EmTPAACSampleFreqmembertable,
	(TXDATAINFO*)EmTPG7221Ratemembertable,
	(TXDATAINFO*)EmTPAACChnlCfgmembertable,
	(TXDATAINFO*)EmTPTpApplySpeakerRetmembertable,
	(TXDATAINFO*)EmTPChanSubTypemembertable,
	(TXDATAINFO*)EmMakeCallTypemembertable,
	(TXDATAINFO*)EmTpRegTypemembertable,
	(TXDATAINFO*)EmDisListOprTypemembertable,
	(TXDATAINFO*)EmDisListOprResltmembertable,
	(TXDATAINFO*)EmVgaTypemembertable,
	(TXDATAINFO*)EmDualInputTypemembertable,
	(TXDATAINFO*)EmDualOutputTypemembertable,
	(TXDATAINFO*)EmVgaSwitchResultmembertable,
	(TXDATAINFO*)EmVgaSwitchReasonmembertable,
	(TXDATAINFO*)EmCnStatemembertable,
	(TXDATAINFO*)EmTPCapSignmembertable,
	(TXDATAINFO*)EmSwitchStatemembertable,
	(TXDATAINFO*)EmTpBoardRetmembertable,
	(TXDATAINFO*)EmHduOutPortmembertable,
	(TXDATAINFO*)EmHduZoomRatemembertable,
	(TXDATAINFO*)EmHduOutModemembertable,
	(TXDATAINFO*)EmHduShowModemembertable,
	(TXDATAINFO*)EmModifyNMServerRetmembertable,
	(TXDATAINFO*)EmModifyVcrRetmembertable,
	(TXDATAINFO*)EmModifyHduRetmembertable,
	(TXDATAINFO*)EmUpdateHduRetmembertable,
	(TXDATAINFO*)EmMPCodecmembertable,
	(TXDATAINFO*)EmTPHDAudPortInmembertable,
	(TXDATAINFO*)EmTPHDDualAudPortInmembertable,
	(TXDATAINFO*)EmTPHDAudPortOutmembertable,
	(TXDATAINFO*)EmTPMtVideoPortmembertable,
	(TXDATAINFO*)EmTPMtVideoOutPortmembertable,
	(TXDATAINFO*)EmTPAutoTestTypemembertable,
	(TXDATAINFO*)EmTPHduRunStatusmembertable,
	(TXDATAINFO*)EmTPLoudspeakerValmembertable,
	(TXDATAINFO*)EmTPFrameUnitTypemembertable,
	(TXDATAINFO*)EmTPVideoStandardmembertable,
	(TXDATAINFO*)EmTPLabelTypemembertable,
	(TXDATAINFO*)EmTPLabelPosTypemembertable,
	(TXDATAINFO*)EmTPDualVideoShowModemembertable,
	(TXDATAINFO*)EmTPDisplayRatiomembertable,
	(TXDATAINFO*)EmTPFecModeTypemembertable,
	(TXDATAINFO*)EmTPNetTypemembertable,
	(TXDATAINFO*)EmTPEqualizerRatemembertable,
	(TXDATAINFO*)EmTPPIPModemembertable,
	(TXDATAINFO*)EmTPDVIModemembertable,
	(TXDATAINFO*)EmTPMCModemembertable,
	(TXDATAINFO*)EmCnsUpdateStatemembertable,
	(TXDATAINFO*)EmTPCnLoginUpdateRetmembertable,
	(TXDATAINFO*)EmTPFileSrvUsedVersionmembertable,
	(TXDATAINFO*)EmTPFileSrvFileTypemembertable,
	(TXDATAINFO*)EmTPOSTypemembertable,
	(TXDATAINFO*)EmMPAudEncCodecmembertable,
	(TXDATAINFO*)EmToolTypemembertable,
	(TXDATAINFO*)EmProducetestTypemembertable,
	(TXDATAINFO*)EmMdyRecFileResmembertable,
	(TXDATAINFO*)EmUseReccorderResmembertable,
	(TXDATAINFO*)EmRecorderTypemembertable,
	(TXDATAINFO*)EmConfRecStatemembertable,
	(TXDATAINFO*)EmTpProfilemembertable,
	(TXDATAINFO*)EmTPHandleCfgTypemembertable,
	(TXDATAINFO*)EmTpCodecTypemembertable,
	(TXDATAINFO*)EmToolStatemembertable,
	(TXDATAINFO*)EmTPAudPlayModemembertable,
	(TXDATAINFO*)EmTPAudDualInModemembertable,
	(TXDATAINFO*)EmTPDualTypemembertable,
	(TXDATAINFO*)EmTPDsNodemembertable,
	(TXDATAINFO*)EMScreenLookedmembertable,
	(TXDATAINFO*)EmTPDVIOutPortTypemembertable,
	(TXDATAINFO*)EmTPMOONOutModemembertable,
	(TXDATAINFO*)EmTPImageAdjustmembertable,
	(TXDATAINFO*)EmTPMOOMModemembertable,
	(TXDATAINFO*)EmTPManualModemembertable,
	(TXDATAINFO*)EmTPZOOMmembertable,
	(TXDATAINFO*)EmTPExpGainmembertable,
	(TXDATAINFO*)EmTPSOrThShuttermembertable,
	(TXDATAINFO*)EmTPFOrTwShuttermembertable,
	(TXDATAINFO*)EmTPAperturemembertable,
	(TXDATAINFO*)EmTPReduNoisemembertable,
	(TXDATAINFO*)EmTPImageParamembertable,
	(TXDATAINFO*)EmImageMosaicTypemembertable,
	(TXDATAINFO*)EmTPFpgaReduNoisemembertable,
	(TXDATAINFO*)EmMOONProductTestTypemembertable,
	(TXDATAINFO*)EmTPLVDSBaudmembertable,
	(TXDATAINFO*)EmTPCorrectmembertable,
	(TXDATAINFO*)EmTpVermembertable,
	(TXDATAINFO*)EmTPCorrectChangemembertable,
	(TXDATAINFO*)EmTPCamNoiseLevelmembertable,
	(TXDATAINFO*)EmTPMechanismmembertable,
	(TXDATAINFO*)EmH650Gammamembertable,
	(TXDATAINFO*)EmTPColorConsistencymembertable,
	(TXDATAINFO*)EmTPDistortPositionmembertable,
	(TXDATAINFO*)NULL
};

//TTPFTPFileInfo
TYPESTRUCT_BEGIN( TTPFTPFileInfo )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u32_ip, dwSerIP )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u16, wSerPort )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byUserNameLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byPasswordLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, u8, byFilePathLen )
    TYPESTRUCT_MEMBER( TTPFTPFileInfo, s8, achFilePath )
TYPESTRUCT_END(  TTPFTPFileInfo )

//TTPDev
TYPESTRUCT_BEGIN( TTPDev )
    TYPESTRUCT_MEMBER( TTPDev, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPDev, s8, m_achDevVersion )
    TYPESTRUCT_MEMBER( TTPDev, TTPFTPFileInfo, m_tDevVerFileInfo )
    TYPESTRUCT_MEMBER( TTPDev, EmTPUpdateType, m_emTPUpdateType )
TYPESTRUCT_END(  TTPDev )

//TTPDevVerInfo
TYPESTRUCT_BEGIN( TTPDevVerInfo )
    TYPESTRUCT_MEMBER( TTPDevVerInfo, TTPDev, m_atDev )
TYPESTRUCT_END(  TTPDevVerInfo )

//TTPLocalVerInfo
TYPESTRUCT_BEGIN( TTPLocalVerInfo )
    TYPESTRUCT_MEMBER( TTPLocalVerInfo, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPLocalVerInfo, s8, m_achDevVersion )
TYPESTRUCT_END(  TTPLocalVerInfo )

//TTPLocalDevVerInfo
TYPESTRUCT_BEGIN( TTPLocalDevVerInfo )
    TYPESTRUCT_MEMBER( TTPLocalDevVerInfo, EmTPDevRegUpdateSer, m_emDevRegUpdateSer )
    TYPESTRUCT_MEMBER( TTPLocalDevVerInfo, TTPLocalVerInfo, m_atLocalVerInfo )
TYPESTRUCT_END(  TTPLocalDevVerInfo )

//TTPTPadVerInfo
TYPESTRUCT_BEGIN( TTPTPadVerInfo )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, EmTPUpdateType, m_emTPUpdateType )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, TTPFTPFileInfo, m_tPadVerFileInfo )
    TYPESTRUCT_MEMBER( TTPTPadVerInfo, s8, m_achTPadVersion )
TYPESTRUCT_END(  TTPTPadVerInfo )

//TH323Cfg
TYPESTRUCT_BEGIN( TH323Cfg )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achMtAlias )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achE164 )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsUseGk )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achGKPwd )
    TYPESTRUCT_MEMBER( TH323Cfg, u32_ip, dwGkIp )
    TYPESTRUCT_MEMBER( TH323Cfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsH239Enable )
    TYPESTRUCT_MEMBER( TH323Cfg, BOOL, bIsEnctyptEnable )
    TYPESTRUCT_MEMBER( TH323Cfg, EmEncryptArithmetic, emEncrptMode )
    TYPESTRUCT_MEMBER( TH323Cfg, u16, wRoundTrip )
TYPESTRUCT_END(  TH323Cfg )

//TGuideCfg
TYPESTRUCT_BEGIN( TGuideCfg )
    TYPESTRUCT_MEMBER( TGuideCfg, EmLanguage, emLanguage )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bIsDHCPEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TGuideCfg, u32_ip, dwGateWay )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bH323Enable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bH320Enable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bSIPEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bSATEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, TH323Cfg, tH323Info )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bUserCfgPwdEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, s8, achUserCfgPwd )
    TYPESTRUCT_MEMBER( TGuideCfg, BOOL, bNetCfgPwdEnable )
    TYPESTRUCT_MEMBER( TGuideCfg, s8, achNetCfgPwd )
TYPESTRUCT_END(  TGuideCfg )

//TSymboPoint
TYPESTRUCT_BEGIN( TSymboPoint )
    TYPESTRUCT_MEMBER( TSymboPoint, u16, X )
    TYPESTRUCT_MEMBER( TSymboPoint, u16, Y )
TYPESTRUCT_END(  TSymboPoint )

//TOsdCfg
TYPESTRUCT_BEGIN( TOsdCfg )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsAutoPip )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowConfLapse )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowSysTime )
    TYPESTRUCT_MEMBER( TOsdCfg, BOOL, bIsShowState )
    TYPESTRUCT_MEMBER( TOsdCfg, EmLabelType, emLabelType )
    TYPESTRUCT_MEMBER( TOsdCfg, TSymboPoint, tLableCoordinate )
    TYPESTRUCT_MEMBER( TOsdCfg, EmLabelPosType, emLabelPosType )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDualVideoShowMode, emDualMode )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDisplayRatio, emPrimaryDisplayRatio )
    TYPESTRUCT_MEMBER( TOsdCfg, EmDisplayRatio, emSecondDisplayRatio )
TYPESTRUCT_END(  TOsdCfg )

//TMtKdvTime
TYPESTRUCT_BEGIN( TMtKdvTime )
    TYPESTRUCT_MEMBER( TMtKdvTime, u16, m_wYear )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMonth )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMDay )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byHour )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_byMinute )
    TYPESTRUCT_MEMBER( TMtKdvTime, u8, m_bySecond )
TYPESTRUCT_END(  TMtKdvTime )

//TUserCfg
TYPESTRUCT_BEGIN( TUserCfg )
    TYPESTRUCT_MEMBER( TUserCfg, EmTripMode, emAnswerMode )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsAutoCallEnable )
    TYPESTRUCT_MEMBER( TUserCfg, s8, achTerminal )
    TYPESTRUCT_MEMBER( TUserCfg, u16, wCallRate )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsRmtCtrlEnbale )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bIsSleepEnable )
    TYPESTRUCT_MEMBER( TUserCfg, u16, wSleepTime )
    TYPESTRUCT_MEMBER( TUserCfg, BOOL, bDisableTelephone )
TYPESTRUCT_END(  TUserCfg )

//TVgaOutCfg
TYPESTRUCT_BEGIN( TVgaOutCfg )
    TYPESTRUCT_MEMBER( TVgaOutCfg, BOOL, bVgaOut )
    TYPESTRUCT_MEMBER( TVgaOutCfg, u16, wRefreshRate )
TYPESTRUCT_END(  TVgaOutCfg )

//TMtEquipmentCapset
TYPESTRUCT_BEGIN( TMtEquipmentCapset )
    TYPESTRUCT_MEMBER( TMtEquipmentCapset, BOOL, bMicAdjustSupport )
    TYPESTRUCT_MEMBER( TMtEquipmentCapset, BOOL, bMcSupport )
TYPESTRUCT_END(  TMtEquipmentCapset )

//TInnerMcCfg
TYPESTRUCT_BEGIN( TInnerMcCfg )
    TYPESTRUCT_MEMBER( TInnerMcCfg, BOOL, bUseMc )
    TYPESTRUCT_MEMBER( TInnerMcCfg, EmMCMode, emMode )
    TYPESTRUCT_MEMBER( TInnerMcCfg, BOOL, bAutoVMP )
TYPESTRUCT_END(  TInnerMcCfg )

//TEthnetInfo
TYPESTRUCT_BEGIN( TEthnetInfo )
    TYPESTRUCT_MEMBER( TEthnetInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TEthnetInfo, BOOL, bIsUserAssignBandWidth )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32, dwUpBandWidth )
    TYPESTRUCT_MEMBER( TEthnetInfo, u32, dwDownBandWidth )
TYPESTRUCT_END(  TEthnetInfo )

//TE1Unit
TYPESTRUCT_BEGIN( TE1Unit )
    TYPESTRUCT_MEMBER( TE1Unit, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwE1TSMask )
    TYPESTRUCT_MEMBER( TE1Unit, EmDLProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwEchoInterval )
    TYPESTRUCT_MEMBER( TE1Unit, u32, dwEchoMaxRetry )
TYPESTRUCT_END(  TE1Unit )

//TE1Config
TYPESTRUCT_BEGIN( TE1Config )
    TYPESTRUCT_MEMBER( TE1Config, u8, byUnitNum )
    TYPESTRUCT_MEMBER( TE1Config, BOOL, bIsBind )
    TYPESTRUCT_MEMBER( TE1Config, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TE1Config, u32_ip, dwIPMask )
    TYPESTRUCT_MEMBER( TE1Config, EmAuthenticationType, emAuthenticationType )
    TYPESTRUCT_MEMBER( TE1Config, u32, dwFragMinPackageLen )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSvrUsrName )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSvrUsrPwd )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSentUsrName )
    TYPESTRUCT_MEMBER( TE1Config, s8, achSentUsrPwd )
    TYPESTRUCT_MEMBER( TE1Config, TE1Unit, atE1Unit )
TYPESTRUCT_END(  TE1Config )

//TSerialCfg
TYPESTRUCT_BEGIN( TSerialCfg )
    TYPESTRUCT_MEMBER( TSerialCfg, u32, dwBaudRate )
    TYPESTRUCT_MEMBER( TSerialCfg, u8, byByteSize )
    TYPESTRUCT_MEMBER( TSerialCfg, EmParityCheck, emCheck )
    TYPESTRUCT_MEMBER( TSerialCfg, EmStopBits, emStopBits )
TYPESTRUCT_END(  TSerialCfg )

//TRouteCfg
TYPESTRUCT_BEGIN( TRouteCfg )
    TYPESTRUCT_MEMBER( TRouteCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwDstNet )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwDstNetMask )
    TYPESTRUCT_MEMBER( TRouteCfg, u32_ip, dwNextIP )
    TYPESTRUCT_MEMBER( TRouteCfg, u32, dwPri )
TYPESTRUCT_END(  TRouteCfg )

//TPPPOECfg
TYPESTRUCT_BEGIN( TPPPOECfg )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyUserName )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyPassword )
    TYPESTRUCT_MEMBER( TPPPOECfg, s8, abyServerName )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bAutoDialEnable )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bDefaultRouteEnable )
    TYPESTRUCT_MEMBER( TPPPOECfg, BOOL, bDebug )
    TYPESTRUCT_MEMBER( TPPPOECfg, u32, dwAutoDialInterval )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wDialRetryTimes )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wLcpEchoSendInterval )
    TYPESTRUCT_MEMBER( TPPPOECfg, u16, wLcpEchoRetryTimes )
    TYPESTRUCT_MEMBER( TPPPOECfg, u8, byEthID )
TYPESTRUCT_END(  TPPPOECfg )

//TPPPoEStates
TYPESTRUCT_BEGIN( TPPPoEStates )
    TYPESTRUCT_MEMBER( TPPPoEStates, BOOL, bPppoeRunning )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLocalIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPeerIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEStates, s8, abyServerName )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLinkKeepTimes )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwLinkDownTimes )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPktsSend )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwPktsRecv )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwBytesSend )
    TYPESTRUCT_MEMBER( TPPPoEStates, u32, dwBytesRecv )
TYPESTRUCT_END(  TPPPoEStates )

//TPPPoEAuthFailed
TYPESTRUCT_BEGIN( TPPPoEAuthFailed )
    TYPESTRUCT_MEMBER( TPPPoEAuthFailed, s8, abyUserName )
    TYPESTRUCT_MEMBER( TPPPoEAuthFailed, s8, abyPassword )
TYPESTRUCT_END(  TPPPoEAuthFailed )

//TPPPoEConnNotify
TYPESTRUCT_BEGIN( TPPPoEConnNotify )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwOurIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwPeerIpAddr )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwDnsServer1 )
    TYPESTRUCT_MEMBER( TPPPoEConnNotify, u32, dwDnsServer2 )
TYPESTRUCT_END(  TPPPoEConnNotify )

//TPPPoENoServer
TYPESTRUCT_BEGIN( TPPPoENoServer )
    TYPESTRUCT_MEMBER( TPPPoENoServer, s8, abyServerName )
TYPESTRUCT_END(  TPPPoENoServer )

//TSNMPCfg
TYPESTRUCT_BEGIN( TSNMPCfg )
    TYPESTRUCT_MEMBER( TSNMPCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSNMPCfg, u32_ip, dwTrapServerIp )
TYPESTRUCT_END(  TSNMPCfg )

//TIPQoS
TYPESTRUCT_BEGIN( TIPQoS )
    TYPESTRUCT_MEMBER( TIPQoS, EmQoS, emType )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abySignalling )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyData )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyAudio )
    TYPESTRUCT_MEMBER( TIPQoS, u8, abyVideo )
    TYPESTRUCT_MEMBER( TIPQoS, EmTOS, emTOS )
TYPESTRUCT_END(  TIPQoS )

//TStreamMedia
TYPESTRUCT_BEGIN( TStreamMedia )
    TYPESTRUCT_MEMBER( TStreamMedia, BOOL, bUse )
    TYPESTRUCT_MEMBER( TStreamMedia, BOOL, bForwardLocalVideo )
    TYPESTRUCT_MEMBER( TStreamMedia, u32_ip, dwMCIP )
    TYPESTRUCT_MEMBER( TStreamMedia, u16, wPort )
    TYPESTRUCT_MEMBER( TStreamMedia, u8, byTTL )
    TYPESTRUCT_MEMBER( TStreamMedia, s8, achChannelName )
    TYPESTRUCT_MEMBER( TStreamMedia, s8, achPassword )
TYPESTRUCT_END(  TStreamMedia )

//TVideoParam
TYPESTRUCT_BEGIN( TVideoParam )
    TYPESTRUCT_MEMBER( TVideoParam, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, EmFrameUnitType, emFrameUnit )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byQualMaxValue )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byQualMinValue )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wIKeyRate )
    TYPESTRUCT_MEMBER( TVideoParam, EmEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TVideoParam, EmLostPackageRestore, emRestoreType )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wH264IKeyRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byH264QualMaxValue )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byH264QualMinValue )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wWidth )
    TYPESTRUCT_MEMBER( TVideoParam, u16, wHeight )
    TYPESTRUCT_MEMBER( TVideoParam, EmMediaType, emCapType )
    TYPESTRUCT_MEMBER( TVideoParam, EmPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TVideoParam, u8, by720pFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byVgaFrameRate )
    TYPESTRUCT_MEMBER( TVideoParam, u8, byD1FrameRate )
TYPESTRUCT_END(  TVideoParam )

//TAVPriorStrategy
TYPESTRUCT_BEGIN( TAVPriorStrategy )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TAVPriorStrategy, EmVideoResolution, emVideoResolution )
TYPESTRUCT_END(  TAVPriorStrategy )

//TLostPackResend
TYPESTRUCT_BEGIN( TLostPackResend )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUse )
    TYPESTRUCT_MEMBER( TLostPackResend, EmNetType, emNetType )
    TYPESTRUCT_MEMBER( TLostPackResend, u8, byResendLevel )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wRejectTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, u16, wSendBufTimeSpan )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUseSmoothSend )
    TYPESTRUCT_MEMBER( TLostPackResend, BOOL, bUseAdaptSend )
TYPESTRUCT_END(  TLostPackResend )

//TCameraTypeInfo
TYPESTRUCT_BEGIN( TCameraTypeInfo )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, s8, achName )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, u8, byMaxAddr )
    TYPESTRUCT_MEMBER( TCameraTypeInfo, u8, byMaxSpeedLevel )
TYPESTRUCT_END(  TCameraTypeInfo )

//TCameraCfg
TYPESTRUCT_BEGIN( TCameraCfg )
    TYPESTRUCT_MEMBER( TCameraCfg, BOOL, bUse )
    TYPESTRUCT_MEMBER( TCameraCfg, s8, achCamera )
    TYPESTRUCT_MEMBER( TCameraCfg, u8, byAddr )
    TYPESTRUCT_MEMBER( TCameraCfg, u8, bySpeedLevel )
    TYPESTRUCT_MEMBER( TCameraCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCameraCfg, u32_ip, dwSerialServerIP )
    TYPESTRUCT_MEMBER( TCameraCfg, u16, wSerialServerPort )
TYPESTRUCT_END(  TCameraCfg )

//TVideoStandard
TYPESTRUCT_BEGIN( TVideoStandard )
    TYPESTRUCT_MEMBER( TVideoStandard, EmVideoType, emVideoType )
    TYPESTRUCT_MEMBER( TVideoStandard, BOOL, bIsInPort )
    TYPESTRUCT_MEMBER( TVideoStandard, EmVideoStandard, emStandard )
TYPESTRUCT_END(  TVideoStandard )

//TVideoSource
TYPESTRUCT_BEGIN( TVideoSource )
    TYPESTRUCT_MEMBER( TVideoSource, EmVideoInterface, emMainCam )
    TYPESTRUCT_MEMBER( TVideoSource, u8, byCPortIndex )
    TYPESTRUCT_MEMBER( TVideoSource, EmVideoInterface, emVideoOut )
    TYPESTRUCT_MEMBER( TVideoSource, u8, byFrequency )
TYPESTRUCT_END(  TVideoSource )

//TSnapInfo
TYPESTRUCT_BEGIN( TSnapInfo )
    TYPESTRUCT_MEMBER( TSnapInfo, BOOL, bResult )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwMaxSize )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwUsedSize )
    TYPESTRUCT_MEMBER( TSnapInfo, u32, dwPicNum )
TYPESTRUCT_END(  TSnapInfo )

//TBannerInfo
TYPESTRUCT_BEGIN( TBannerInfo )
    TYPESTRUCT_MEMBER( TBannerInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwTextClr )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwBkgClr )
    TYPESTRUCT_MEMBER( TBannerInfo, EmTextAlign, emTextAlign )
    TYPESTRUCT_MEMBER( TBannerInfo, EmRollMode, emRollMode )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byTransParent )
    TYPESTRUCT_MEMBER( TBannerInfo, EmRollSpeed, emRollSpeed )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byRollNum )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, byStayTime )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwStartXPos )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwStartYPos )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwDisplayWidth )
    TYPESTRUCT_MEMBER( TBannerInfo, u32, dwDisplayHeight )
    TYPESTRUCT_MEMBER( TBannerInfo, u8, achWinInfo )
    TYPESTRUCT_MEMBER( TBannerInfo, s8, achBannerText )
TYPESTRUCT_END(  TBannerInfo )

//TMtId
TYPESTRUCT_BEGIN( TMtId )
    TYPESTRUCT_MEMBER( TMtId, u8, byMcuNo )
    TYPESTRUCT_MEMBER( TMtId, u8, byTerNo )
TYPESTRUCT_END(  TMtId )

//TConfBaseInfo
TYPESTRUCT_BEGIN( TConfBaseInfo )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfId )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfNumber )
    TYPESTRUCT_MEMBER( TConfBaseInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bNeedPassword )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u16, wConfDuration )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoResolution, emResolution )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TConfBaseInfo, BOOL, bIsMix )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u8, bySecVideoFormat )
    TYPESTRUCT_MEMBER( TConfBaseInfo, EmVideoResolution, emSecVidRes )
    TYPESTRUCT_MEMBER( TConfBaseInfo, u8, bySecVidFps )
TYPESTRUCT_END(  TConfBaseInfo )

//TConfListInfo
TYPESTRUCT_BEGIN( TConfListInfo )
    TYPESTRUCT_MEMBER( TConfListInfo, u8, byConfNum )
    TYPESTRUCT_MEMBER( TConfListInfo, TConfBaseInfo, atConfInfo )
TYPESTRUCT_END(  TConfListInfo )

//TMtInfo
TYPESTRUCT_BEGIN( TMtInfo )
    TYPESTRUCT_MEMBER( TMtInfo, TMtId, tLabel )
    TYPESTRUCT_MEMBER( TMtInfo, s8, achAlias )
TYPESTRUCT_END(  TMtInfo )

//TMtVideoCodecStatus
TYPESTRUCT_BEGIN( TMtVideoCodecStatus )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, BOOL, bRuning )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, u16, wBitrate )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, u16, wAverageBitrate )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, BOOL, IsEncrypt )
    TYPESTRUCT_MEMBER( TMtVideoCodecStatus, EmEncryptArithmetic, emArithmetic )
TYPESTRUCT_END(  TMtVideoCodecStatus )

//TTerStatus
TYPESTRUCT_BEGIN( TTerStatus )
    TYPESTRUCT_MEMBER( TTerStatus, EmMtModel, emMtModel )
    TYPESTRUCT_MEMBER( TTerStatus, EmFileSys, emFileSys )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byEncVol )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byDecVol )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsMute )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsQuiet )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsLoopBack )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInMixing )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bRegGkStat )
    TYPESTRUCT_MEMBER( TTerStatus, EmAction, emPollStat )
    TYPESTRUCT_MEMBER( TTerStatus, EmSite, emCamCtrlSrc )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byLocalCamCtrlNo )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byRemoteCamCtrlNo )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byE1UnitNum )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bFECCEnalbe )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bLocalIsVAG )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bPVHasVideo )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bSVHasVideo )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsAudioPowerTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsLocalImageTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsRemoteImageTest )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInConf )
    TYPESTRUCT_MEMBER( TTerStatus, EmConfMode, emConfMode )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bCallByGK )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bMatrixStatus )
    TYPESTRUCT_MEMBER( TTerStatus, u8, byCamNum )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bCamStatus )
    TYPESTRUCT_MEMBER( TTerStatus, EmMtVideoPort, emVideoSrc )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsEncrypt )
    TYPESTRUCT_MEMBER( TTerStatus, EmAudioFormat, emADecFormat )
    TYPESTRUCT_MEMBER( TTerStatus, EmAudioFormat, emAEncFormat )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tPVEncStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tSVEncStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tPVDecStatus )
    TYPESTRUCT_MEMBER( TTerStatus, TMtVideoCodecStatus, tSVDecStatus )
    TYPESTRUCT_MEMBER( TTerStatus, u16, wSysSleep )
    TYPESTRUCT_MEMBER( TTerStatus, BOOL, bIsInVOD )
    TYPESTRUCT_MEMBER( TTerStatus, EmUIPosion, byVodUser )
TYPESTRUCT_END(  TTerStatus )

//TMtMixParam
TYPESTRUCT_BEGIN( TMtMixParam )
    TYPESTRUCT_MEMBER( TMtMixParam, u8, byMixNum )
    TYPESTRUCT_MEMBER( TMtMixParam, u8, byDIscussMode )
    TYPESTRUCT_MEMBER( TMtMixParam, TMtId, atMtMixItem )
TYPESTRUCT_END(  TMtMixParam )

//TMtVmpItem
TYPESTRUCT_BEGIN( TMtVmpItem )
    TYPESTRUCT_MEMBER( TMtVmpItem, TMtId, tMt )
    TYPESTRUCT_MEMBER( TMtVmpItem, EmVMPMmbType, emMmbType )
    TYPESTRUCT_MEMBER( TMtVmpItem, u32, adwReserved )
TYPESTRUCT_END(  TMtVmpItem )

//TMtVMPParam
TYPESTRUCT_BEGIN( TMtVMPParam )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsCustomVMP )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtVMPParam, BOOL, bIsBroadcast )
    TYPESTRUCT_MEMBER( TMtVMPParam, EmVMPStyle, emStyle )
    TYPESTRUCT_MEMBER( TMtVMPParam, TMtVmpItem, atMtVmpItem )
TYPESTRUCT_END(  TMtVMPParam )

//TMtPollInfo
TYPESTRUCT_BEGIN( TMtPollInfo )
    TYPESTRUCT_MEMBER( TMtPollInfo, EmMediaType, emMode )
    TYPESTRUCT_MEMBER( TMtPollInfo, EmAction, emStat )
    TYPESTRUCT_MEMBER( TMtPollInfo, u16, wKeepTime )
    TYPESTRUCT_MEMBER( TMtPollInfo, u8, byMtNum )
    TYPESTRUCT_MEMBER( TMtPollInfo, TMtInfo, atMtInfo )
TYPESTRUCT_END(  TMtPollInfo )

//TMtPollSchemeNameSet
TYPESTRUCT_BEGIN( TMtPollSchemeNameSet )
    TYPESTRUCT_MATRIX( TMtPollSchemeNameSet, s8, achMtPollSchemeName )
TYPESTRUCT_END(  TMtPollSchemeNameSet )

//TMtViewPollInfo
TYPESTRUCT_BEGIN( TMtViewPollInfo )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, EmMediaType, emMode )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, EmAction, emStat )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, u16, wKeepTime )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, u8, byMtNum )
    TYPESTRUCT_MEMBER( TMtViewPollInfo, TMtInfo, atMtInfo )
TYPESTRUCT_END(  TMtViewPollInfo )

//TMtSimpConfInfo
TYPESTRUCT_BEGIN( TMtSimpConfInfo )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, TMtId, tSpeaker )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, TMtId, tChairMan )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsVAC )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsDisc )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtSimpConfInfo, BOOL, bIsCustomVMP )
TYPESTRUCT_END(  TMtSimpConfInfo )

//TMtConfInfo
TYPESTRUCT_BEGIN( TMtConfInfo )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, chConfId )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtKdvTime, tStartTime )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wDuration )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wBitRate )
    TYPESTRUCT_MEMBER( TMtConfInfo, u16, wSecBitRate )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emMainVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emSecondVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, EmVideoResolution, emDoubleVideoResolution )
    TYPESTRUCT_MEMBER( TMtConfInfo, u8, byTalkHoldTime )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TMtConfInfo, s8, achConfE164 )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsAudioPowerSel )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsDiscussMode )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsCustomVMP )
    TYPESTRUCT_MEMBER( TMtConfInfo, BOOL, bIsForceBroadcast )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtId, tChairman )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtId, tSpeaker )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtPollInfo, tPollInfo )
    TYPESTRUCT_MEMBER( TMtConfInfo, TMtVMPParam, tVMPParam )
TYPESTRUCT_END(  TMtConfInfo )

//TIPTransAddr
TYPESTRUCT_BEGIN( TIPTransAddr )
    TYPESTRUCT_MEMBER( TIPTransAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TIPTransAddr, u16, wPort )
TYPESTRUCT_END(  TIPTransAddr )

//TMtAddr
TYPESTRUCT_BEGIN( TMtAddr )
    TYPESTRUCT_MEMBER( TMtAddr, EmMtAddrType, emType )
    TYPESTRUCT_MEMBER( TMtAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TMtAddr, s8, achAlias )
TYPESTRUCT_END(  TMtAddr )

//TConfId
TYPESTRUCT_BEGIN( TConfId )
    TYPESTRUCT_MEMBER( TConfId, u8, byGuid )
    TYPESTRUCT_MEMBER( TConfId, TMtAddr, tAlias )
TYPESTRUCT_END(  TConfId )

//TDialParam
TYPESTRUCT_BEGIN( TDialParam )
    TYPESTRUCT_MEMBER( TDialParam, EmCallMode, emCallType )
    TYPESTRUCT_MEMBER( TDialParam, EmConfProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TDialParam, u16, wCallRate )
    TYPESTRUCT_MEMBER( TDialParam, TMtAddr, tCallingAddr )
    TYPESTRUCT_MEMBER( TDialParam, TMtAddr, tCalledAddr )
    TYPESTRUCT_MEMBER( TDialParam, BOOL, bCreateConf )
    TYPESTRUCT_MEMBER( TDialParam, TConfBaseInfo, tConfInfo )
    TYPESTRUCT_MEMBER( TDialParam, u8, byTerNum )
    TYPESTRUCT_MEMBER( TDialParam, TMtAddr, atList )
TYPESTRUCT_END(  TDialParam )

//TLinkState
TYPESTRUCT_BEGIN( TLinkState )
    TYPESTRUCT_MEMBER( TLinkState, EmCallState, emCallState )
    TYPESTRUCT_MEMBER( TLinkState, u32_ip, dwIpAddr )
    TYPESTRUCT_MEMBER( TLinkState, s8, achAlias )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bCalling )
    TYPESTRUCT_MEMBER( TLinkState, EmCallDisconnectReason, emReason )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bGetChairToken )
    TYPESTRUCT_MEMBER( TLinkState, BOOL, bSeenByAll )
    TYPESTRUCT_MEMBER( TLinkState, u16, wCallRate )
    TYPESTRUCT_MEMBER( TLinkState, EmMtModel, emPeerMtModel )
TYPESTRUCT_END(  TLinkState )

//TEmbedFwNatProxy
TYPESTRUCT_BEGIN( TEmbedFwNatProxy )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u32_ip, dwFwNatProxyServIP )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, s8, achPrxySrvName )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u16, wFwNatProxyServListenPort )
    TYPESTRUCT_MEMBER( TEmbedFwNatProxy, u16, wStreamBasePort )
TYPESTRUCT_END(  TEmbedFwNatProxy )

//TNATMapAddr
TYPESTRUCT_BEGIN( TNATMapAddr )
    TYPESTRUCT_MEMBER( TNATMapAddr, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TNATMapAddr, u32_ip, dwIP )
TYPESTRUCT_END(  TNATMapAddr )

//TSipRegistrarCfg
TYPESTRUCT_BEGIN( TSipRegistrarCfg )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achPassword )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TSipRegistrarCfg, u16, wHostPort )
TYPESTRUCT_END(  TSipRegistrarCfg )

//TGKCfg
TYPESTRUCT_BEGIN( TGKCfg )
    TYPESTRUCT_MEMBER( TGKCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TGKCfg, u32_ip, dwGKIP )
    TYPESTRUCT_MEMBER( TGKCfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TGKCfg, s8, achGKPasswd )
TYPESTRUCT_END(  TGKCfg )

//TInnerGKCfg
TYPESTRUCT_BEGIN( TInnerGKCfg )
    TYPESTRUCT_MEMBER( TInnerGKCfg, BOOL, bGKUsed )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TInnerGKCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TInnerGKCfg )

//TInnerProxyCfg
TYPESTRUCT_BEGIN( TInnerProxyCfg )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, BOOL, bInnerProxyUsed )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TInnerProxyCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TInnerProxyCfg )

//TWiFiNetCfg
TYPESTRUCT_BEGIN( TWiFiNetCfg )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, BOOL, bWiFiUsed )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, BOOL, bDHCP )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TWiFiNetCfg, u32_ip, dwGateWay )
TYPESTRUCT_END(  TWiFiNetCfg )

//TMonitorService
TYPESTRUCT_BEGIN( TMonitorService )
    TYPESTRUCT_MEMBER( TMonitorService, BOOL, bSwitchEnable )
    TYPESTRUCT_MEMBER( TMonitorService, u32, dwSwitchTimeout )
TYPESTRUCT_END(  TMonitorService )

//TRect
TYPESTRUCT_BEGIN( TRect )
    TYPESTRUCT_MEMBER( TRect, u16, wLeft )
    TYPESTRUCT_MEMBER( TRect, u16, wTop )
    TYPESTRUCT_MEMBER( TRect, u16, wWidth )
    TYPESTRUCT_MEMBER( TRect, u16, wHeight )
TYPESTRUCT_END(  TRect )

//TDualRation
TYPESTRUCT_BEGIN( TDualRation )
    TYPESTRUCT_MEMBER( TDualRation, BOOL, bSecondSendRateType )
    TYPESTRUCT_MEMBER( TDualRation, BOOL, bSecondRecvRateType )
    TYPESTRUCT_MEMBER( TDualRation, u8, bySecondSendRate )
    TYPESTRUCT_MEMBER( TDualRation, u8, bySecondRecvRate )
    TYPESTRUCT_MEMBER( TDualRation, u8, byPrimaryRecvRate )
TYPESTRUCT_END(  TDualRation )

//TImageAdjustParam
TYPESTRUCT_BEGIN( TImageAdjustParam )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wBrightness )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wContrast )
    TYPESTRUCT_MEMBER( TImageAdjustParam, u8, wSaturation )
TYPESTRUCT_END(  TImageAdjustParam )

//TVideoEncodeParameter
TYPESTRUCT_BEGIN( TVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byMaxQuant )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byMinQuant )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, BOOL, bFramePerSecond )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, m_wWidth )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, u16, m_wHeight )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmMediaType, emCapType )
    TYPESTRUCT_MEMBER( TVideoEncodeParameter, EmPCCapFormat, emPCCapFormat )
TYPESTRUCT_END(  TVideoEncodeParameter )

//TEncryptKey
TYPESTRUCT_BEGIN( TEncryptKey )
    TYPESTRUCT_MEMBER( TEncryptKey, u8, byLen )
    TYPESTRUCT_MEMBER( TEncryptKey, u8, byKey )
TYPESTRUCT_END(  TEncryptKey )

//TVideoChanParam
TYPESTRUCT_BEGIN( TVideoChanParam )
    TYPESTRUCT_MEMBER( TVideoChanParam, EmVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TVideoChanParam, EmVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TVideoChanParam, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TVideoChanParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TVideoChanParam, TEncryptKey, tKey )
    TYPESTRUCT_MEMBER( TVideoChanParam, BOOL, bIsH239 )
    TYPESTRUCT_MEMBER( TVideoChanParam, u8, byFrameRate )
TYPESTRUCT_END(  TVideoChanParam )

//TAudioChanParam
TYPESTRUCT_BEGIN( TAudioChanParam )
    TYPESTRUCT_MEMBER( TAudioChanParam, EmAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TAudioChanParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TAudioChanParam, TEncryptKey, tKey )
TYPESTRUCT_END(  TAudioChanParam )

//TVODUserInfo
TYPESTRUCT_BEGIN( TVODUserInfo )
    TYPESTRUCT_MEMBER( TVODUserInfo, TIPTransAddr, m_tIp )
    TYPESTRUCT_MEMBER( TVODUserInfo, s8, m_achUserName )
    TYPESTRUCT_MEMBER( TVODUserInfo, s8, m_achUserPass )
    TYPESTRUCT_MEMBER( TVODUserInfo, BOOL, m_bRecordNamePass )
TYPESTRUCT_END(  TVODUserInfo )

//TVODFile
TYPESTRUCT_BEGIN( TVODFile )
    TYPESTRUCT_MEMBER( TVODFile, s8, achName )
    TYPESTRUCT_MEMBER( TVODFile, BOOL, bIsFile )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwFileSize )
    TYPESTRUCT_MEMBER( TVODFile, BOOL, bIsInfoValid )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwRecordTime )
    TYPESTRUCT_MEMBER( TVODFile, u32, dwDuration )
    TYPESTRUCT_MEMBER( TVODFile, EmAudioFormat, emAudio )
    TYPESTRUCT_MEMBER( TVODFile, EmVideoFormat, emPrimoVideo )
    TYPESTRUCT_MEMBER( TVODFile, EmVideoFormat, emSecondVideo )
TYPESTRUCT_END(  TVODFile )

//TE1Group
TYPESTRUCT_BEGIN( TE1Group )
    TYPESTRUCT_MEMBER( TE1Group, u8, byGroupIndex )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwE1Mask )
    TYPESTRUCT_MEMBER( TE1Group, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TE1Group, u32_ip, dwIPMask )
    TYPESTRUCT_MEMBER( TE1Group, EmDLProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TE1Group, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TE1Group, EmAuthenticationType, emAuthenticationType )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwFragMinPackageLen )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSvrUsrName )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSvrUsrPwd )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSentUsrName )
    TYPESTRUCT_MEMBER( TE1Group, s8, achSentUsrPwd )
    TYPESTRUCT_MEMBER( TE1Group, u32, dwVal )
TYPESTRUCT_END(  TE1Group )

//TVideoSourceInfo
TYPESTRUCT_BEGIN( TVideoSourceInfo )
    TYPESTRUCT_MEMBER( TVideoSourceInfo, EmMtVideoPort, emVideoPort )
    TYPESTRUCT_MEMBER( TVideoSourceInfo, s8, achPortName )
TYPESTRUCT_END(  TVideoSourceInfo )

//TExternalMatrixInfo
TYPESTRUCT_BEGIN( TExternalMatrixInfo )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, s8, TypeName )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, u8, OutPort )
    TYPESTRUCT_MEMBER( TExternalMatrixInfo, u8, InPortTotal )
TYPESTRUCT_END(  TExternalMatrixInfo )

//TAVInnerMatrixScheme
TYPESTRUCT_BEGIN( TAVInnerMatrixScheme )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, EmMatrixType, emType )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, s8, achName )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, u8, byIndex )
    TYPESTRUCT_MEMBER( TAVInnerMatrixScheme, u8, abyOutPort2InPort )
    TYPESTRUCT_MATRIX( TAVInnerMatrixScheme, s8, achOutPortName )
    TYPESTRUCT_MATRIX( TAVInnerMatrixScheme, s8, achInPortName )
TYPESTRUCT_END(  TAVInnerMatrixScheme )

//TBitRateAdjust
TYPESTRUCT_BEGIN( TBitRateAdjust )
    TYPESTRUCT_MEMBER( TBitRateAdjust, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wInterval )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wLostTimes )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wDescRatio )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wLowDescRatio )
    TYPESTRUCT_MEMBER( TBitRateAdjust, u16, wDelayInterval )
TYPESTRUCT_END(  TBitRateAdjust )

//TCodecPackStat
TYPESTRUCT_BEGIN( TCodecPackStat )
    TYPESTRUCT_MEMBER( TCodecPackStat, u16, wBitrate )
    TYPESTRUCT_MEMBER( TCodecPackStat, u16, wAvrBitrate )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwLostPacks )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwTotalPacks )
    TYPESTRUCT_MEMBER( TCodecPackStat, u32, dwFrames )
    TYPESTRUCT_MEMBER( TCodecPackStat, u8, byLostFrameRate )
TYPESTRUCT_END(  TCodecPackStat )

//TVideoStatistics
TYPESTRUCT_BEGIN( TVideoStatistics )
    TYPESTRUCT_MEMBER( TVideoStatistics, BOOL, bH239 )
    TYPESTRUCT_MEMBER( TVideoStatistics, EmVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TVideoStatistics, EmVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TVideoStatistics, TCodecPackStat, tPack )
TYPESTRUCT_END(  TVideoStatistics )

//TAudioStatistics
TYPESTRUCT_BEGIN( TAudioStatistics )
    TYPESTRUCT_MEMBER( TAudioStatistics, EmAudioFormat, emFormat )
    TYPESTRUCT_MEMBER( TAudioStatistics, TCodecPackStat, tPack )
TYPESTRUCT_END(  TAudioStatistics )

//TCapType
TYPESTRUCT_BEGIN( TCapType )
    TYPESTRUCT_MEMBER( TCapType, s8, m_achCapFileName )
    TYPESTRUCT_MEMBER( TCapType, EmCapType, emCapType )
TYPESTRUCT_END(  TCapType )

//TCallInfoStatistics
TYPESTRUCT_BEGIN( TCallInfoStatistics )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, u16, wCallBitrate )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, EmEncryptArithmetic, emRecvEncrypt )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, EmEncryptArithmetic, emSendEncrypt )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TAudioStatistics, tRecvAudio )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TAudioStatistics, tSendAudio )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tPrimoRecvVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tPrimoSendVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tSencodRecvVideo )
    TYPESTRUCT_MEMBER( TCallInfoStatistics, TVideoStatistics, tSecondSendVideo )
TYPESTRUCT_END(  TCallInfoStatistics )

//TDualStreamBoxInfo
TYPESTRUCT_BEGIN( TDualStreamBoxInfo )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, BOOL, m_bUsed )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, u32_ip, m_dwIp )
    TYPESTRUCT_MEMBER( TDualStreamBoxInfo, u16, m_wPort )
TYPESTRUCT_END(  TDualStreamBoxInfo )

//TFileTransfer
TYPESTRUCT_BEGIN( TFileTransfer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wProtocolIdentifer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wFileSliceNo )
    TYPESTRUCT_MEMBER( TFileTransfer, u8, byType )
    TYPESTRUCT_MEMBER( TFileTransfer, u8, byRspInfo )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wFileIdentifer )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wPakageMaxLen )
    TYPESTRUCT_MEMBER( TFileTransfer, u16, wDataLen )
TYPESTRUCT_END(  TFileTransfer )

//TDVBNetSession
TYPESTRUCT_BEGIN( TDVBNetSession )
    TYPESTRUCT_MEMBER( TDVBNetSession, u32_ip, m_dwRTPAddr )
    TYPESTRUCT_MEMBER( TDVBNetSession, u16, m_wRTPPort )
    TYPESTRUCT_MEMBER( TDVBNetSession, u32_ip, m_dwRTCPAddr )
    TYPESTRUCT_MEMBER( TDVBNetSession, u16, m_wRTCPPort )
TYPESTRUCT_END(  TDVBNetSession )

//TDVBNetSndParam
TYPESTRUCT_BEGIN( TDVBNetSndParam )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, u8, m_byNum )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, TDVBNetSession, m_tLocalNet )
    TYPESTRUCT_MEMBER( TDVBNetSndParam, TDVBNetSession, m_tRemoteNet )
TYPESTRUCT_END(  TDVBNetSndParam )

//TDVBLocalNetParam
TYPESTRUCT_BEGIN( TDVBLocalNetParam )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, TDVBNetSession, m_tLocalNet )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, u32_ip, m_dwRtcpBackAddr )
    TYPESTRUCT_MEMBER( TDVBLocalNetParam, u16, m_wRtcpBackPort )
TYPESTRUCT_END(  TDVBLocalNetParam )

//TDVBVideoEncParam
TYPESTRUCT_BEGIN( TDVBVideoEncParam )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byEncType )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byRcMode )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byMaxQuant )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byMinQuant )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved1 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved2 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved3 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wReserved4 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u32, m_dwSndNetBand )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u32, m_dwReserved5 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byPalNtsc )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byCapPort )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrameRate )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byImageQulity )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byReserved6 )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wVideoWidth )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u16, m_wVideoHeight )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrameFmt )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrmRateCanSet )
    TYPESTRUCT_MEMBER( TDVBVideoEncParam, u8, m_byFrmRateLittleThanOne )
TYPESTRUCT_END(  TDVBVideoEncParam )

//TSitecallInformation
TYPESTRUCT_BEGIN( TSitecallInformation )
    TYPESTRUCT_MEMBER( TSitecallInformation, BOOL, m_bIsCustomConf )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfPwd )
    TYPESTRUCT_MEMBER( TSitecallInformation, BOOL, m_bLocalPay )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfCard )
    TYPESTRUCT_MEMBER( TSitecallInformation, s8, m_achConfCardPwd )
    TYPESTRUCT_MEMBER( TSitecallInformation, u8, m_byMultiPicCount )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmCallRate, m_emRate )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmVideoFormat, m_emVideoType )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmVideoResolution, m_emVideoFormat )
    TYPESTRUCT_MEMBER( TSitecallInformation, EmAudioFormat, m_emAudioFormat )
    TYPESTRUCT_MEMBER( TSitecallInformation, u8, m_byTerninalCount )
    TYPESTRUCT_MEMBER( TSitecallInformation, TMtAddr, m_atTerminalE164Info )
    TYPESTRUCT_MEMBER( TSitecallInformation, TMtAddr, m_atTerminalH323Info )
TYPESTRUCT_END(  TSitecallInformation )

//TTransparentSerial
TYPESTRUCT_BEGIN( TTransparentSerial )
    TYPESTRUCT_MEMBER( TTransparentSerial, EmSerialType, m_emComType )
    TYPESTRUCT_MEMBER( TTransparentSerial, u32, m_nDataLen )
    TYPESTRUCT_MEMBER( TTransparentSerial, s8, m_achData )
TYPESTRUCT_END(  TTransparentSerial )

//TPeerCapabilityInfo
TYPESTRUCT_BEGIN( TPeerCapabilityInfo )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bMix )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bVAC )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bCustomVMP )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bAutoVMP )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bEndConf )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bInvateMt )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bDropMt )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSpeaker )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelChair )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSource )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bFECC )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bQuiet )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bMute )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bConfReq )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bOnlineList )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bOfflineList )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bPicSwitch )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bSelSpeakingUser )
    TYPESTRUCT_MEMBER( TPeerCapabilityInfo, BOOL, m_bForceBroadcast )
TYPESTRUCT_END(  TPeerCapabilityInfo )

//TRapidKey
TYPESTRUCT_BEGIN( TRapidKey )
    TYPESTRUCT_MEMBER( TRapidKey, EmMtVideoPort, emMainVidSrcBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emRedBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emYellowBtn )
    TYPESTRUCT_MEMBER( TRapidKey, EmHotKeyType, emGreenBtn )
TYPESTRUCT_END(  TRapidKey )

//TVerFileInfo
TYPESTRUCT_BEGIN( TVerFileInfo )
    TYPESTRUCT_MEMBER( TVerFileInfo, EmMtOSType, m_emFileType )
    TYPESTRUCT_MEMBER( TVerFileInfo, u32, m_dwFileSize )
    TYPESTRUCT_MEMBER( TVerFileInfo, s8, m_szFileName )
TYPESTRUCT_END(  TVerFileInfo )

//TVerInfo
TYPESTRUCT_BEGIN( TVerInfo )
    TYPESTRUCT_MEMBER( TVerInfo, u8, m_byFileNum )
    TYPESTRUCT_MEMBER( TVerInfo, s8, m_achBugReport )
    TYPESTRUCT_MEMBER( TVerInfo, s8, m_achSoftVer )
    TYPESTRUCT_MEMBER( TVerInfo, TVerFileInfo, m_atVerFile )
TYPESTRUCT_END(  TVerInfo )

//TFecInfo
TYPESTRUCT_BEGIN( TFecInfo )
    TYPESTRUCT_MEMBER( TFecInfo, BOOL, m_bEnableFec )
    TYPESTRUCT_MEMBER( TFecInfo, u8, m_byAlgorithm )
    TYPESTRUCT_MEMBER( TFecInfo, u16, m_wPackLen )
    TYPESTRUCT_MEMBER( TFecInfo, BOOL, m_bIntraFrame )
    TYPESTRUCT_MEMBER( TFecInfo, u32, m_dwDataPackNum )
    TYPESTRUCT_MEMBER( TFecInfo, u32, m_dwCrcPackNum )
TYPESTRUCT_END(  TFecInfo )

//TVInnerMatrixScheme
TYPESTRUCT_BEGIN( TVInnerMatrixScheme )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, byIndex )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, s8, achName )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, abyOutPort2InPort )
    TYPESTRUCT_MEMBER( TVInnerMatrixScheme, u8, abyDVIMode )
    TYPESTRUCT_MATRIX( TVInnerMatrixScheme, s8, achOutPortName )
    TYPESTRUCT_MATRIX( TVInnerMatrixScheme, s8, achInPortName )
TYPESTRUCT_END(  TVInnerMatrixScheme )

//TAddrEntry
TYPESTRUCT_BEGIN( TAddrEntry )
    TYPESTRUCT_MEMBER( TAddrEntry, s8, m_achEntryName )
    TYPESTRUCT_MEMBER( TAddrEntry, s8, m_achIpaddr )
    TYPESTRUCT_MEMBER( TAddrEntry, u32, m_dwCallTime )
    TYPESTRUCT_MEMBER( TAddrEntry, u16, m_wCallRate )
    TYPESTRUCT_MEMBER( TAddrEntry, BOOL, m_bTeleCall )
TYPESTRUCT_END(  TAddrEntry )

//TPxyIPCfg
TYPESTRUCT_BEGIN( TPxyIPCfg )
    TYPESTRUCT_MEMBER( TPxyIPCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TPxyIPCfg, u32_ip, dwGateway )
TYPESTRUCT_END(  TPxyIPCfg )

//TWifiLinkInfo
TYPESTRUCT_BEGIN( TWifiLinkInfo )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, s8, achSSID )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, s8, achBssMacAddr )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwSignalLevel )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwLinkRate )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byAuthType )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byEncrytoType )
    TYPESTRUCT_MEMBER( TWifiLinkInfo, u8, byNetType )
TYPESTRUCT_END(  TWifiLinkInfo )

//TWifiScanResult
TYPESTRUCT_BEGIN( TWifiScanResult )
    TYPESTRUCT_MEMBER( TWifiScanResult, u32, dwBssNum )
    TYPESTRUCT_MEMBER( TWifiScanResult, TWifiLinkInfo, tLinkInfo )
TYPESTRUCT_END(  TWifiScanResult )

//TWifiLinkCfgItem
TYPESTRUCT_BEGIN( TWifiLinkCfgItem )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, u32, dwId )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achCfgName )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, TWifiLinkInfo, tWifiLinkInfo )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey1 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey2 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey3 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWepKey4 )
    TYPESTRUCT_MEMBER( TWifiLinkCfgItem, s8, achWpaPasswd )
TYPESTRUCT_END(  TWifiLinkCfgItem )

//TWiFiBSSIDInfo
TYPESTRUCT_BEGIN( TWiFiBSSIDInfo )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u8, byPSKOFF )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiNetType, emNetType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiEncryptType, emEncryptType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, EmWiFiEncryptArithmetic, emArithType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, BOOL, bEncrypt )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwBeaconInterval )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwLinkRate )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, u32, dwSignalLevel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achBSSMacAddr )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achSSID )
    TYPESTRUCT_MEMBER( TWiFiBSSIDInfo, s8, achPasswd )
TYPESTRUCT_END(  TWiFiBSSIDInfo )

//TWiFiBSSIDCfg
TYPESTRUCT_BEGIN( TWiFiBSSIDCfg )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u8, byPSKOFF )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiNetType, emNetType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiEncryptType, emEncryptType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, EmWiFiEncryptArithmetic, emArithType )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, BOOL, bEncrypt )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u32, dwCfgPri )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, u32, dwChannel )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, s8, achSSID )
    TYPESTRUCT_MEMBER( TWiFiBSSIDCfg, s8, achPassword )
TYPESTRUCT_END(  TWiFiBSSIDCfg )

//TGkRegInfo
TYPESTRUCT_BEGIN( TGkRegInfo )
    TYPESTRUCT_MEMBER( TGkRegInfo, BOOL, bRegisted )
    TYPESTRUCT_MEMBER( TGkRegInfo, EmGKRegFailedReason, emReason )
TYPESTRUCT_END(  TGkRegInfo )

//TSipRegResult
TYPESTRUCT_BEGIN( TSipRegResult )
    TYPESTRUCT_MEMBER( TSipRegResult, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TSipRegResult, EmSipRegFailedReason, emReason )
TYPESTRUCT_END(  TSipRegResult )

//THdAudioPort
TYPESTRUCT_BEGIN( THdAudioPort )
    TYPESTRUCT_MEMBER( THdAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( THdAudioPort, u8, abHdAudPortOut )
TYPESTRUCT_END(  THdAudioPort )

//TMiscCfg
TYPESTRUCT_BEGIN( TMiscCfg )
    TYPESTRUCT_MEMBER( TMiscCfg, BOOL, bUseSlice )
TYPESTRUCT_END(  TMiscCfg )

//TVideoDisplayFrm
TYPESTRUCT_BEGIN( TVideoDisplayFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw1080PFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw1080IFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dwVGAFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dw720PFrm )
    TYPESTRUCT_MEMBER( TVideoDisplayFrm, u32, m_dwSDFrm )
TYPESTRUCT_END(  TVideoDisplayFrm )

//TDownLoadPara
TYPESTRUCT_BEGIN( TDownLoadPara )
    TYPESTRUCT_MEMBER( TDownLoadPara, u8, byFileType )
    TYPESTRUCT_MEMBER( TDownLoadPara, u8, byFileCount )
    TYPESTRUCT_MEMBER( TDownLoadPara, s8, m_achFileName )
TYPESTRUCT_END(  TDownLoadPara )

//TSecurePwd
TYPESTRUCT_BEGIN( TSecurePwd )
    TYPESTRUCT_MEMBER( TSecurePwd, BOOL, bUserCfgPwd )
    TYPESTRUCT_MEMBER( TSecurePwd, s8, achUserCfgPwd )
TYPESTRUCT_END(  TSecurePwd )

//TMtBackBGDColor
TYPESTRUCT_BEGIN( TMtBackBGDColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, RColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, GColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, BColor )
    TYPESTRUCT_MEMBER( TMtBackBGDColor, u8, u8Transparency )
TYPESTRUCT_END(  TMtBackBGDColor )

//TSipCfg
TYPESTRUCT_BEGIN( TSipCfg )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achUserName )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achPassword )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wHostPort )
    TYPESTRUCT_MEMBER( TSipCfg, BOOL, bUseRegistrar )
    TYPESTRUCT_MEMBER( TSipCfg, u32_ip, dwRegistrarIp )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wRegistrarPort )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achRegistrarDomain )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TSipCfg, BOOL, bUseProxy )
    TYPESTRUCT_MEMBER( TSipCfg, u32_ip, dwProxyIp )
    TYPESTRUCT_MEMBER( TSipCfg, u16, wProxyPort )
    TYPESTRUCT_MEMBER( TSipCfg, s8, achProxyDomain )
TYPESTRUCT_END(  TSipCfg )

//TMtAddBannerParam
TYPESTRUCT_BEGIN( TMtAddBannerParam )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwXPos )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwYPos )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBMPWight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBMPHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBannerCharHeight )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, TMtBackBGDColor, tBackBGDColor )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwBGDClarity )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwPicClarity )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunMode )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunSpeed )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwRunTimes )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, bRunForever )
    TYPESTRUCT_MEMBER( TMtAddBannerParam, u32, dwHaltTime )
TYPESTRUCT_END(  TMtAddBannerParam )

//TMtBmpInfo
TYPESTRUCT_BEGIN( TMtBmpInfo )
    TYPESTRUCT_MEMBER( TMtBmpInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMtBmpInfo, u32, dwHeight )
TYPESTRUCT_END(  TMtBmpInfo )

//TMtFullBannerParam
TYPESTRUCT_BEGIN( TMtFullBannerParam )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, TMtBmpInfo, tBmpInfo )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, TMtAddBannerParam, tBannerParam )
    TYPESTRUCT_MEMBER( TMtFullBannerParam, u32, Reserver )
TYPESTRUCT_END(  TMtFullBannerParam )

//TMTBmpInfo
TYPESTRUCT_BEGIN( TMTBmpInfo )
    TYPESTRUCT_MEMBER( TMTBmpInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMTBmpInfo, u32, dwHeight )
TYPESTRUCT_END(  TMTBmpInfo )

//TMTAddLogoParam
TYPESTRUCT_BEGIN( TMTAddLogoParam )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwXPos )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwYPos )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwLogoWidth )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, u32, dwLogoHeight )
    TYPESTRUCT_MEMBER( TMTAddLogoParam, TMtBackBGDColor, tBackBGDColor )
TYPESTRUCT_END(  TMTAddLogoParam )

//TMTFullLogoParam
TYPESTRUCT_BEGIN( TMTFullLogoParam )
    TYPESTRUCT_MEMBER( TMTFullLogoParam, TMTBmpInfo, tBmpInfo )
    TYPESTRUCT_MEMBER( TMTFullLogoParam, TMTAddLogoParam, tLogoParam )
TYPESTRUCT_END(  TMTFullLogoParam )

//TMtcBoxCallCfg
TYPESTRUCT_BEGIN( TMtcBoxCallCfg )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u8, byUseIndex )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u32_ip, dwIp )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, s8, achE164 )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, s8, achMtAlias )
    TYPESTRUCT_MEMBER( TMtcBoxCallCfg, u16, wCallRate )
TYPESTRUCT_END(  TMtcBoxCallCfg )

//TMTRSParam
TYPESTRUCT_BEGIN( TMTRSParam )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TMTRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TMTRSParam )

//TMtRecStartParam
TYPESTRUCT_BEGIN( TMtRecStartParam )
    TYPESTRUCT_MEMBER( TMtRecStartParam, EmSite, emSite )
    TYPESTRUCT_MEMBER( TMtRecStartParam, BOOL, bIsRecSecVideo )
    TYPESTRUCT_MEMBER( TMtRecStartParam, u8, m_byPublishMode )
    TYPESTRUCT_MEMBER( TMtRecStartParam, s8, achFileName )
TYPESTRUCT_END(  TMtRecStartParam )

//TMtRecRegParam
TYPESTRUCT_BEGIN( TMtRecRegParam )
    TYPESTRUCT_MEMBER( TMtRecRegParam, u32_ip, dwRecIp )
    TYPESTRUCT_MEMBER( TMtRecRegParam, u32_ip, dwHostIp )
    TYPESTRUCT_MEMBER( TMtRecRegParam, s8, achDirName )
TYPESTRUCT_END(  TMtRecRegParam )

//TMtRecParam
TYPESTRUCT_BEGIN( TMtRecParam )
    TYPESTRUCT_MEMBER( TMtRecParam, u8, byState )
    TYPESTRUCT_MEMBER( TMtRecParam, TMtRecRegParam, tMtRecRegParam )
    TYPESTRUCT_MEMBER( TMtRecParam, TMtRecStartParam, tMtRecStartParam )
TYPESTRUCT_END(  TMtRecParam )

//TMtCnsParam
TYPESTRUCT_BEGIN( TMtCnsParam )
    TYPESTRUCT_MEMBER( TMtCnsParam, u32_ip, dwCnsIp )
    TYPESTRUCT_MEMBER( TMtCnsParam, s8, achRoomName )
    TYPESTRUCT_MEMBER( TMtCnsParam, u16, wPos )
    TYPESTRUCT_MEMBER( TMtCnsParam, u16, wPosCount )
    TYPESTRUCT_MEMBER( TMtCnsParam, BOOL, bIsDual )
TYPESTRUCT_END(  TMtCnsParam )

//TLoginRet
TYPESTRUCT_BEGIN( TLoginRet )
    TYPESTRUCT_MEMBER( TLoginRet, EmTpLoginUmsRet, m_emRet )
    TYPESTRUCT_MEMBER( TLoginRet, u32, m_dwUserID )
    TYPESTRUCT_MEMBER( TLoginRet, u32, m_dwErrorCode )
TYPESTRUCT_END(  TLoginRet )

//TTPTransAddr
TYPESTRUCT_BEGIN( TTPTransAddr )
    TYPESTRUCT_MEMBER( TTPTransAddr, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( TTPTransAddr, u16, m_wPort )
TYPESTRUCT_END(  TTPTransAddr )

//TTPName
TYPESTRUCT_BEGIN( TTPName )
    TYPESTRUCT_MEMBER( TTPName, s8, m_abyAlias )
TYPESTRUCT_END(  TTPName )

//TTPAlias
TYPESTRUCT_BEGIN( TTPAlias )
    TYPESTRUCT_MEMBER( TTPAlias, EmTpAliasType, m_byType )
    TYPESTRUCT_MEMBER( TTPAlias, s8, m_abyAlias )
TYPESTRUCT_END(  TTPAlias )

//TTpEncryptKey
TYPESTRUCT_BEGIN( TTpEncryptKey )
    TYPESTRUCT_MEMBER( TTpEncryptKey, u8, byLen )
    TYPESTRUCT_MEMBER( TTpEncryptKey, u8, byKey )
TYPESTRUCT_END(  TTpEncryptKey )

//TTPMediaTransAddr
TYPESTRUCT_BEGIN( TTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tRtpAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tRtcpAddr )
    TYPESTRUCT_MEMBER( TTPMediaTransAddr, TTPTransAddr, m_tBackRtcpAddr )
TYPESTRUCT_END(  TTPMediaTransAddr )

//TTPVideoCap
TYPESTRUCT_BEGIN( TTPVideoCap )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_byMaxFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPVideoCap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPVideoCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPVideoCap, EmTpVideoQualityLevel, emTpVideoQualityLevel )
TYPESTRUCT_END(  TTPVideoCap )

//TTPAudCap
TYPESTRUCT_BEGIN( TTPAudCap )
    TYPESTRUCT_MEMBER( TTPAudCap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPAudCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPAudCap, TTpEncryptKey, m_tEnc )
TYPESTRUCT_END(  TTPAudCap )

//TUmsVidFormat
TYPESTRUCT_BEGIN( TUmsVidFormat )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TUmsVidFormat, u16, m_wFrameRate )
    TYPESTRUCT_MEMBER( TUmsVidFormat, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TUmsVidFormat, EmTpVideoQualityLevel, m_emQualityLvl )
TYPESTRUCT_END(  TUmsVidFormat )

//TUmsRSParam
TYPESTRUCT_BEGIN( TUmsRSParam )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TUmsRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TUmsRSParam )

//TEpAddr
TYPESTRUCT_BEGIN( TEpAddr )
    TYPESTRUCT_MEMBER( TEpAddr, TTPAlias, m_tAlias )
    TYPESTRUCT_MEMBER( TEpAddr, TTPAlias, m_tE164 )
    TYPESTRUCT_MEMBER( TEpAddr, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( TEpAddr, u16, m_wEpID )
TYPESTRUCT_END(  TEpAddr )

//TAuxMixList
TYPESTRUCT_BEGIN( TAuxMixList )
    TYPESTRUCT_MEMBER( TAuxMixList, u16, m_wSpeakerIndex )
    TYPESTRUCT_MEMBER( TAuxMixList, u16, m_awList )
    TYPESTRUCT_MEMBER( TAuxMixList, BOOL32, m_bAudMixOn )
TYPESTRUCT_END(  TAuxMixList )

//TConfAuxMixInfo
TYPESTRUCT_BEGIN( TConfAuxMixInfo )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, BOOL32, m_bStart )
    TYPESTRUCT_MEMBER( TConfAuxMixInfo, TAuxMixList, m_atAuxMixList )
TYPESTRUCT_END(  TConfAuxMixInfo )

//TTPPollInfo
TYPESTRUCT_BEGIN( TTPPollInfo )
    TYPESTRUCT_MEMBER( TTPPollInfo, BOOL, bIsPoll )
    TYPESTRUCT_MEMBER( TTPPollInfo, u16, wPollExpire )
TYPESTRUCT_END(  TTPPollInfo )

//TTPConfBaseInfo
TYPESTRUCT_BEGIN( TTPConfBaseInfo )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfId )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfName )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfNumber )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, s8, achConfPwd )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bNeedPassword )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wConfDuration )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoFormat, emTpVideoFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpAudioFormat, emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoResolution, emTpResolution )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bIsAutoVMP )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, BOOL32, bIsMix )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, bySecVideoFormat )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoResolution, emTpSecVidRes )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, bySecVidFps )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoQualityLevel, emPriVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, EmTpVideoQualityLevel, emDualVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u8, byPriVidFps )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wCallRate )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, u16, wDualCallRate )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, TTPPollInfo, tPollInfo )
    TYPESTRUCT_MEMBER( TTPConfBaseInfo, TConfAuxMixInfo, tConfAudMixInfo )
TYPESTRUCT_END(  TTPConfBaseInfo )

//TUmsConfBase
TYPESTRUCT_BEGIN( TUmsConfBase )
    TYPESTRUCT_MEMBER( TUmsConfBase, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TUmsConfBase, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TUmsConfBase, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TUmsConfBase, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TUmsConfBase, EmTpAudioFormat, m_emTpAudioFormat )
    TYPESTRUCT_MEMBER( TUmsConfBase, EmTpAudioFormat, m_emSecAudFormat )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TUmsConfBase, EmTPEncryptType, m_byEncryptModel )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TUmsConfBase, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TUmsConfBase, TUmsVidFormat, m_atTpMinorVideoRes )
TYPESTRUCT_END(  TUmsConfBase )

//TChairConfInfo
TYPESTRUCT_BEGIN( TChairConfInfo )
    TYPESTRUCT_MEMBER( TChairConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TChairConfInfo, time_t, m_tBeginTime )
    TYPESTRUCT_MEMBER( TChairConfInfo, TTPAlias, m_tConfName )
    TYPESTRUCT_MEMBER( TChairConfInfo, TTPAlias, m_tChairName )
TYPESTRUCT_END(  TChairConfInfo )

//TEpAddrList
TYPESTRUCT_BEGIN( TEpAddrList )
    TYPESTRUCT_MEMBER( TEpAddrList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TEpAddrList, TEpAddr, m_tCnsList )
TYPESTRUCT_END(  TEpAddrList )

//TConfTurnList
TYPESTRUCT_BEGIN( TConfTurnList )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_wInterval )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfTurnList, u16, m_awList )
    TYPESTRUCT_MEMBER( TConfTurnList, BOOL32, m_bPollOn )
TYPESTRUCT_END(  TConfTurnList )

//TTPConfTemplate
TYPESTRUCT_BEGIN( TTPConfTemplate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TTPConfTemplate, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TTPConfTemplate, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TTPConfTemplate, EmTpAudioFormat, m_emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPConfTemplate, EmTpAudioFormat, m_emSecAudFormat )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TTPConfTemplate, EmTPEncryptType, m_byEncryptModel )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TUmsVidFormat, m_atTpMinorVideoRes )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u16, m_wID )
    TYPESTRUCT_MEMBER( TTPConfTemplate, u32, m_dwTimeID )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TEpAddrList, m_atEpList )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TAuxMixList, m_atAuxMixList )
    TYPESTRUCT_MEMBER( TTPConfTemplate, TConfTurnList, m_tTurnList )
TYPESTRUCT_END(  TTPConfTemplate )

//TOprConfTmpResult
TYPESTRUCT_BEGIN( TOprConfTmpResult )
    TYPESTRUCT_MEMBER( TOprConfTmpResult, u16, m_wID )
    TYPESTRUCT_MEMBER( TOprConfTmpResult, EmTpConfTemplateRet, m_emReason )
TYPESTRUCT_END(  TOprConfTmpResult )

//TDelRefreshConfTemplate
TYPESTRUCT_BEGIN( TDelRefreshConfTemplate )
    TYPESTRUCT_MEMBER( TDelRefreshConfTemplate, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TDelRefreshConfTemplate, u16, m_awTmpList )
TYPESTRUCT_END(  TDelRefreshConfTemplate )

//TConfEpID
TYPESTRUCT_BEGIN( TConfEpID )
    TYPESTRUCT_MEMBER( TConfEpID, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfEpID, u16, m_wEpID )
TYPESTRUCT_END(  TConfEpID )

//TConfEpIDInfo
TYPESTRUCT_BEGIN( TConfEpIDInfo )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TConfEpIDInfo, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TConfEpIDInfo )

//TConfCallEpAddr
TYPESTRUCT_BEGIN( TConfCallEpAddr )
    TYPESTRUCT_MEMBER( TConfCallEpAddr, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfCallEpAddr, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TConfCallEpAddr )

//TCnsInfo
TYPESTRUCT_BEGIN( TCnsInfo )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wParentEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wChildEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wBrotherEpID )
    TYPESTRUCT_MEMBER( TCnsInfo, EmTPEndpointType, m_emEpType )
    TYPESTRUCT_MEMBER( TCnsInfo, TTPAlias, m_tCalledAddr )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bOnline )
    TYPESTRUCT_MEMBER( TCnsInfo, EmCnsCallReason, m_emCallReason )
    TYPESTRUCT_MEMBER( TCnsInfo, s8, m_achRoomName )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wLevel )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bQuiet )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bIsSpeaker )
    TYPESTRUCT_MEMBER( TCnsInfo, BOOL32, m_bIsChair )
    TYPESTRUCT_MEMBER( TCnsInfo, u16, m_wSpeakerNum )
    TYPESTRUCT_MATRIX( TCnsInfo, s8, m_achSpeakerName )
TYPESTRUCT_END(  TCnsInfo )

//TTPConfInfo
TYPESTRUCT_BEGIN( TTPConfInfo )
    TYPESTRUCT_MEMBER( TTPConfInfo, s8, m_achConfName )
    TYPESTRUCT_MEMBER( TTPConfInfo, s8, m_achConfE164 )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wBpConfBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wHpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wBpDualBitRate )
    TYPESTRUCT_MEMBER( TTPConfInfo, u32, m_dwPersistenceTime )
    TYPESTRUCT_MEMBER( TTPConfInfo, time_t, m_tStartTime )
    TYPESTRUCT_MEMBER( TTPConfInfo, EmTpAudioFormat, m_emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPConfInfo, EmTpAudioFormat, m_emSecAudFormat )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsRSParam, m_tRsParam )
    TYPESTRUCT_MEMBER( TTPConfInfo, EmTPEncryptType, m_byEncryptModel )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wDefaultChairMan )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wMainNum )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsVidFormat, m_atTpMainVideoRes )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wMinorNum )
    TYPESTRUCT_MEMBER( TTPConfInfo, TUmsVidFormat, m_atTpMinorVideoRes )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wSpeaker )
    TYPESTRUCT_MEMBER( TTPConfInfo, u16, m_wDual )
TYPESTRUCT_END(  TTPConfInfo )

//TAddConfList
TYPESTRUCT_BEGIN( TAddConfList )
    TYPESTRUCT_MEMBER( TAddConfList, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TAddConfList, TTPConfInfo, m_atTmpList )
TYPESTRUCT_END(  TAddConfList )

//TDelConfList
TYPESTRUCT_BEGIN( TDelConfList )
    TYPESTRUCT_MEMBER( TDelConfList, u16, m_wRefreshNum )
    TYPESTRUCT_MEMBER( TDelConfList, u16, m_awConfIDList )
TYPESTRUCT_END(  TDelConfList )

//TStartConfResult
TYPESTRUCT_BEGIN( TStartConfResult )
    TYPESTRUCT_MEMBER( TStartConfResult, EmTpStartConfRet, m_emReason )
    TYPESTRUCT_MEMBER( TStartConfResult, u16, m_wConfTemplateID )
    TYPESTRUCT_MEMBER( TStartConfResult, u16, m_wConfID )
TYPESTRUCT_END(  TStartConfResult )

//TConfCnsInfo
TYPESTRUCT_BEGIN( TConfCnsInfo )
    TYPESTRUCT_MEMBER( TConfCnsInfo, EmTpOprType, m_emOpr )
    TYPESTRUCT_MEMBER( TConfCnsInfo, BOOL32, m_bLastPack )
    TYPESTRUCT_MEMBER( TConfCnsInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfCnsInfo, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfCnsInfo, TCnsInfo, m_tConfCnsList )
TYPESTRUCT_END(  TConfCnsInfo )

//TConfTurnInfo
TYPESTRUCT_BEGIN( TConfTurnInfo )
    TYPESTRUCT_MEMBER( TConfTurnInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TConfTurnInfo, TConfTurnList, m_atTurnList )
TYPESTRUCT_END(  TConfTurnInfo )

//TApplaySpeakRet
TYPESTRUCT_BEGIN( TApplaySpeakRet )
    TYPESTRUCT_MEMBER( TApplaySpeakRet, TConfEpID, m_tID )
    TYPESTRUCT_MEMBER( TApplaySpeakRet, EmTpApplySpeakRet, m_emReason )
TYPESTRUCT_END(  TApplaySpeakRet )

//TUmsConfStatus
TYPESTRUCT_BEGIN( TUmsConfStatus )
    TYPESTRUCT_MEMBER( TUmsConfStatus, BOOL32, m_bIsStartAudMix )
TYPESTRUCT_END(  TUmsConfStatus )

//TTPUmsReasonInd
TYPESTRUCT_BEGIN( TTPUmsReasonInd )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReason )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve1 )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve2 )
    TYPESTRUCT_MEMBER( TTPUmsReasonInd, u32, m_dwReserve3 )
TYPESTRUCT_END(  TTPUmsReasonInd )

//TTPMtVideoEncodeParameter
TYPESTRUCT_BEGIN( TTPMtVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpVideoFormat, emVideoFormat )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, byMaxKeyFrameInterval )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byMaxQuant )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byMinQuant )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, BOOL, bFramePerSecond )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpVideoResolution, emVideoResolution )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, m_wWidth )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u16, m_wHeight )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpMediaType, emCapType )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, EmTpPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwAvgQpI )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwAvgQpP )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u8, m_byLoopFilterMask )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwProfile )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwCabacDisable )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwSilceMbCont )
    TYPESTRUCT_MEMBER( TTPMtVideoEncodeParameter, u32, m_dwRateControlAlg )
TYPESTRUCT_END(  TTPMtVideoEncodeParameter )

//TTpCodecComponent
TYPESTRUCT_BEGIN( TTpCodecComponent )
    TYPESTRUCT_MEMBER( TTpCodecComponent, u16, wPos )
    TYPESTRUCT_MEMBER( TTpCodecComponent, EmTpCodecComponent, emCope )
TYPESTRUCT_END(  TTpCodecComponent )

//TTPCnMediaTransPort
TYPESTRUCT_BEGIN( TTPCnMediaTransPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tRtpPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tRtcpPort )
    TYPESTRUCT_MEMBER( TTPCnMediaTransPort, TTPTransAddr, m_tBackRtcpPort )
TYPESTRUCT_END(  TTPCnMediaTransPort )

//TMtMPAddr
TYPESTRUCT_BEGIN( TMtMPAddr )
    TYPESTRUCT_MEMBER( TMtMPAddr, u16, wPos )
    TYPESTRUCT_MEMBER( TMtMPAddr, EmTpCodecComponent, emCope )
    TYPESTRUCT_MEMBER( TMtMPAddr, TTPCnMediaTransPort, m_tAddr )
TYPESTRUCT_END(  TMtMPAddr )

//TMtMPParam
TYPESTRUCT_BEGIN( TMtMPParam )
    TYPESTRUCT_MEMBER( TMtMPParam, u16, m_wMpType )
    TYPESTRUCT_MEMBER( TMtMPParam, TTPCnMediaTransPort, m_tAddr )
TYPESTRUCT_END(  TMtMPParam )

//TMtTPEpParam
TYPESTRUCT_BEGIN( TMtTPEpParam )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, wLen )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndPrimarAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvPrimarAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndSecondAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvSecondAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tSndAudioAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvAudioAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvPrimarLeftAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, TMtMPParam, m_tRcvPrimarRightAddr )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, m_wPosCount )
    TYPESTRUCT_MEMBER( TMtTPEpParam, u16, m_wPos )
    TYPESTRUCT_MEMBER( TMtTPEpParam, s8, achRoomName )
    TYPESTRUCT_MEMBER( TMtTPEpParam, EmTPMtModel, m_emTPMtModel )
TYPESTRUCT_END(  TMtTPEpParam )

//TMtVDecParam
TYPESTRUCT_BEGIN( TMtVDecParam )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtVDecParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpLostPackageRestore, emLost )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TMtVDecParam, EmTpVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TMtVDecParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtVDecParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtVDecParam, u16, wPos )
TYPESTRUCT_END(  TMtVDecParam )

//TMtVEncParam
TYPESTRUCT_BEGIN( TMtVEncParam )
    TYPESTRUCT_MEMBER( TMtVEncParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTPMtVideoEncodeParameter, tVideoEncodeParameter )
    TYPESTRUCT_MEMBER( TMtVEncParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtVEncParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtVEncParam, u16, wPos )
TYPESTRUCT_END(  TMtVEncParam )

//TCnVideoParam
TYPESTRUCT_BEGIN( TCnVideoParam )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TCnVideoParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpVideoFormat, emFormat )
    TYPESTRUCT_MEMBER( TCnVideoParam, EmTpVideoResolution, emRes )
    TYPESTRUCT_MEMBER( TCnVideoParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TCnVideoParam, u32, wChanMaxBitrate )
    TYPESTRUCT_MEMBER( TCnVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TCnVideoParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TCnVideoParam, u32, m_dwProfile )
TYPESTRUCT_END(  TCnVideoParam )

//TEpId
TYPESTRUCT_BEGIN( TEpId )
    TYPESTRUCT_MEMBER( TEpId, u8, byCnNo )
    TYPESTRUCT_MEMBER( TEpId, u8, byEpNo )
TYPESTRUCT_END(  TEpId )

//TTPRegName
TYPESTRUCT_BEGIN( TTPRegName )
    TYPESTRUCT_MEMBER( TTPRegName, EmTPAddrType, emPAAddrType )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPRegName, s8, achDisplayName )
TYPESTRUCT_END(  TTPRegName )

//TTPRegNameRepeatInfo
TYPESTRUCT_BEGIN( TTPRegNameRepeatInfo )
    TYPESTRUCT_MEMBER( TTPRegNameRepeatInfo, u32, dwsize )
    TYPESTRUCT_MEMBER( TTPRegNameRepeatInfo, TTPRegName, atTPRegName )
TYPESTRUCT_END(  TTPRegNameRepeatInfo )

//TTPSipRegistrarCfg
TYPESTRUCT_BEGIN( TTPSipRegistrarCfg )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, TTPRegName, atTPRegName )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s32, nTPRegNameSize )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u16, wHostPort )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, EmTPEndpointType, m_emEndType )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, m_softversion )
    TYPESTRUCT_MEMBER( TTPSipRegistrarCfg, s8, m_compileTime )
TYPESTRUCT_END(  TTPSipRegistrarCfg )

//TTPGkRegistrarCfg
TYPESTRUCT_BEGIN( TTPGkRegistrarCfg )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, TTPRegName, atTPRegName )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s32, nTPRegNameSize )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u32_ip, dwHostIP )
    TYPESTRUCT_MEMBER( TTPGkRegistrarCfg, u16, wHostPort )
TYPESTRUCT_END(  TTPGkRegistrarCfg )

//TTPGKCfg
TYPESTRUCT_BEGIN( TTPGKCfg )
    TYPESTRUCT_MEMBER( TTPGKCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPGKCfg, u32_ip, dwGKIP )
    TYPESTRUCT_MEMBER( TTPGKCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGKCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TTPGKCfg, BOOL, bRegistered )
    TYPESTRUCT_MEMBER( TTPGKCfg, s8, achGkIpName )
    TYPESTRUCT_MEMBER( TTPGKCfg, s8, achGKPasswd )
TYPESTRUCT_END(  TTPGKCfg )

//TTPSipRegPackInfo
TYPESTRUCT_BEGIN( TTPSipRegPackInfo )
    TYPESTRUCT_MEMBER( TTPSipRegPackInfo, u16, m_wPackSeq )
    TYPESTRUCT_MEMBER( TTPSipRegPackInfo, u16, m_wTotalPackNum )
TYPESTRUCT_END(  TTPSipRegPackInfo )

//TTPSipRegInfo
TYPESTRUCT_BEGIN( TTPSipRegInfo )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPSipRegInfo, EmTPEndpointType, m_emSelfType )
TYPESTRUCT_END(  TTPSipRegInfo )

//TTPSipPack
TYPESTRUCT_BEGIN( TTPSipPack )
    TYPESTRUCT_MEMBER( TTPSipPack, TTPSipRegPackInfo, m_tSipRegPackInfo )
    TYPESTRUCT_MEMBER( TTPSipPack, TTPSipRegInfo, m_tSipRegInfo )
TYPESTRUCT_END(  TTPSipPack )

//TTPAddrNtyUser
TYPESTRUCT_BEGIN( TTPAddrNtyUser )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, u32, m_dwIID )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, u32, m_wUserData )
    TYPESTRUCT_MEMBER( TTPAddrNtyUser, EmGetRegInfoType, m_emType )
TYPESTRUCT_END(  TTPAddrNtyUser )

//TUCSipRegResult
TYPESTRUCT_BEGIN( TUCSipRegResult )
    TYPESTRUCT_MEMBER( TUCSipRegResult, EmTpCnsRegUms, m_emTpCnsRegUms )
    TYPESTRUCT_MEMBER( TUCSipRegResult, TTPAlias, m_atTPAlias )
    TYPESTRUCT_MEMBER( TUCSipRegResult, s32, m_nAliasNum )
TYPESTRUCT_END(  TUCSipRegResult )

//TCnAddr
TYPESTRUCT_BEGIN( TCnAddr )
    TYPESTRUCT_MEMBER( TCnAddr, EmTPAddrType, emType )
    TYPESTRUCT_MEMBER( TCnAddr, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TCnAddr, u16, wPort )
    TYPESTRUCT_MEMBER( TCnAddr, s8, achAlias )
    TYPESTRUCT_MEMBER( TCnAddr, s8, achE164 )
TYPESTRUCT_END(  TCnAddr )

//TTPDialParam
TYPESTRUCT_BEGIN( TTPDialParam )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpConnectionType, emTpConnectionType )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpCallMode, emCallType )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTpConfProtocol, emProtocol )
    TYPESTRUCT_MEMBER( TTPDialParam, u16, wCallRate )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, tCallingAddr )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, tCalledAddr )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TTPDialParam, BOOL32, m_bIsEncrypt )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nProductIdSize )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, m_abyProductId )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nVerIdSize )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, m_abyVersionId )
    TYPESTRUCT_MEMBER( TTPDialParam, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TTPDialParam, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achDisplayName )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achUserName )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achPassword )
    TYPESTRUCT_MEMBER( TTPDialParam, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TTPDialParam, BOOL, bCreateConf )
    TYPESTRUCT_MEMBER( TTPDialParam, TTPConfBaseInfo, tConfInfo )
    TYPESTRUCT_MEMBER( TTPDialParam, u8, byTerNum )
    TYPESTRUCT_MEMBER( TTPDialParam, TCnAddr, atList )
    TYPESTRUCT_MEMBER( TTPDialParam, EmTPSipLevel, m_emSipLevel )
    TYPESTRUCT_MEMBER( TTPDialParam, s32, m_nScreenNum )
TYPESTRUCT_END(  TTPDialParam )

//TTPCnsInfo
TYPESTRUCT_BEGIN( TTPCnsInfo )
    TYPESTRUCT_MEMBER( TTPCnsInfo, s8, m_achRoomName )
    TYPESTRUCT_MEMBER( TTPCnsInfo, s8, m_achE164 )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTPCnsInfo, EmTPSipLevel, m_emLevel )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u8, m_byDualPos )
    TYPESTRUCT_MEMBER( TTPCnsInfo, u32_ip, m_adwIP )
    TYPESTRUCT_MEMBER( TTPCnsInfo, BOOL, m_bIsShowRoomName )
TYPESTRUCT_END(  TTPCnsInfo )

//TTPTime
TYPESTRUCT_BEGIN( TTPTime )
    TYPESTRUCT_MEMBER( TTPTime, u16, m_wYear )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMonth )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMDay )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byHour )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_byMinute )
    TYPESTRUCT_MEMBER( TTPTime, u8, m_bySecond )
TYPESTRUCT_END(  TTPTime )

//TTPCnsConfStatus
TYPESTRUCT_BEGIN( TTPCnsConfStatus )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmCALLSTATE, emState )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, u16, wConfID )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, s8, achConfName )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, time_t, m_tmStartTime )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmCallType, m_emCallType )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, BOOL32, m_bMixMotive )
    TYPESTRUCT_MEMBER( TTPCnsConfStatus, EmTpConfProtocol, m_emConfProtocal )
TYPESTRUCT_END(  TTPCnsConfStatus )

//TTPDualInfo
TYPESTRUCT_BEGIN( TTPDualInfo )
    TYPESTRUCT_MEMBER( TTPDualInfo, EmTPPayloadType, m_emPayload )
    TYPESTRUCT_MEMBER( TTPDualInfo, EmTpVideoResolution, m_emReslution )
    TYPESTRUCT_MEMBER( TTPDualInfo, u16, m_wFrameRate )
    TYPESTRUCT_MEMBER( TTPDualInfo, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TTPDualInfo, s32, m_nScreenNo )
    TYPESTRUCT_MEMBER( TTPDualInfo, s32, m_nEpId )
    TYPESTRUCT_MEMBER( TTPDualInfo, s8, m_achCascade )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tRtp )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tRtcp )
    TYPESTRUCT_MEMBER( TTPDualInfo, TTPTransAddr, m_tBackRtp )
TYPESTRUCT_END(  TTPDualInfo )

//TTPDualRequest
TYPESTRUCT_BEGIN( TTPDualRequest )
    TYPESTRUCT_MEMBER( TTPDualRequest, s8, m_achCascade )
    TYPESTRUCT_MEMBER( TTPDualRequest, s32, m_nEpId )
TYPESTRUCT_END(  TTPDualRequest )

//TTPDualInfoAck
TYPESTRUCT_BEGIN( TTPDualInfoAck )
    TYPESTRUCT_MEMBER( TTPDualInfoAck, BOOL, m_bAccept )
    TYPESTRUCT_MEMBER( TTPDualInfoAck, TTPDualInfo, m_tDualInfo )
TYPESTRUCT_END(  TTPDualInfoAck )

//TTPAudioInfo
TYPESTRUCT_BEGIN( TTPAudioInfo )
    TYPESTRUCT_MEMBER( TTPAudioInfo, u8, m_byInputVolume )
    TYPESTRUCT_MEMBER( TTPAudioInfo, u8, m_byOutputVolume )
TYPESTRUCT_END(  TTPAudioInfo )

//TTPHduRegInfo
TYPESTRUCT_BEGIN( TTPHduRegInfo )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, BOOL32, m_bIsOnline )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u32_ip, m_dwIpAddr )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_wStartPort )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, s8, m_achAlias )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_dwChannelHandle )
    TYPESTRUCT_MEMBER( TTPHduRegInfo, u16, m_wScreenNum )
TYPESTRUCT_END(  TTPHduRegInfo )

//TTPHduPlayReq
TYPESTRUCT_BEGIN( TTPHduPlayReq )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, s8, m_achAlias )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTPHduPlayReq, u16, m_nChannelHandle )
TYPESTRUCT_END(  TTPHduPlayReq )

//TTPCnLoginfo
TYPESTRUCT_BEGIN( TTPCnLoginfo )
    TYPESTRUCT_MEMBER( TTPCnLoginfo, s32, nVersion )
TYPESTRUCT_END(  TTPCnLoginfo )

//TTPCn
TYPESTRUCT_BEGIN( TTPCn )
    TYPESTRUCT_MEMBER( TTPCn, u8, byInsId )
    TYPESTRUCT_MEMBER( TTPCn, s8, achName )
TYPESTRUCT_END(  TTPCn )

//TTPCnList
TYPESTRUCT_BEGIN( TTPCnList )
    TYPESTRUCT_MEMBER( TTPCnList, u16, wNum )
    TYPESTRUCT_MEMBER( TTPCnList, TTPCn, tCn )
TYPESTRUCT_END(  TTPCnList )

//TAudMixStat
TYPESTRUCT_BEGIN( TAudMixStat )
    TYPESTRUCT_MEMBER( TAudMixStat, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TAudMixStat, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAudMixStat, BOOL32, m_bIsStart )
    TYPESTRUCT_MEMBER( TAudMixStat, EmTpMixStatus, m_emMixStatus )
TYPESTRUCT_END(  TAudMixStat )

//TTPDisScreenStat
TYPESTRUCT_BEGIN( TTPDisScreenStat )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, BOOL32, m_bInDiscard )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_wEpIDDst )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_awScreenNum )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, u16, m_awSpeakerIndx )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPDisScreenStat, EmTPDisOprType, m_emOprType )
TYPESTRUCT_END(  TTPDisScreenStat )

//TTPGetRegInfo
TYPESTRUCT_BEGIN( TTPGetRegInfo )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, EmGetRegInfoType, emType )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u32, dwRegIP )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u16, wRegPort )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u32, dwLocalIP )
    TYPESTRUCT_MEMBER( TTPGetRegInfo, u16, wLocalPort )
TYPESTRUCT_END(  TTPGetRegInfo )

//TTPAacCap
TYPESTRUCT_BEGIN( TTPAacCap )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPAacCap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPAacCap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTPAACSampleFreq, emPASampleFreq )
    TYPESTRUCT_MEMBER( TTPAacCap, EmTPAACChnlCfg, emPAChnlCfg )
TYPESTRUCT_END(  TTPAacCap )

//TTPG7221Cap
TYPESTRUCT_BEGIN( TTPG7221Cap )
    TYPESTRUCT_MEMBER( TTPG7221Cap, EmTpAudioFormat, m_emFormat )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wStaticPayload )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wDynamicPayload )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TTPG7221Cap, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TTPG7221Cap, u8, byBitRateType )
TYPESTRUCT_END(  TTPG7221Cap )

//TTPMediaStream
TYPESTRUCT_BEGIN( TTPMediaStream )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, bActive )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTpMediaType, emTPMediaType )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tLocalRtp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tRemPAoteRtp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tSendRtcp )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPTransAddr, tRecvRtcp )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TTPMediaStream, u8, byMediaCount )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPAudCap, tACap )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TTPMediaStream, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPPayloadType, emTPActivePT )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPEncryptType, emTPEncryptType )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nBitRate )
    TYPESTRUCT_MEMBER( TTPMediaStream, u32, dwLocalIp )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPMediaStream, s32, nPeerScreenNo )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPCapSign, m_emTPCapSign )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, bDual )
    TYPESTRUCT_MEMBER( TTPMediaStream, EmTPChanType, emTPChanType )
    TYPESTRUCT_MEMBER( TTPMediaStream, BOOL32, m_bAudMix )
TYPESTRUCT_END(  TTPMediaStream )

//TTPCapMap
TYPESTRUCT_BEGIN( TTPCapMap )
    TYPESTRUCT_MEMBER( TTPCapMap, TTPMediaStream, cMeadiaStream )
    TYPESTRUCT_MEMBER( TTPCapMap, s32, nChannelId )
TYPESTRUCT_END(  TTPCapMap )

//TTPCapPack
TYPESTRUCT_BEGIN( TTPCapPack )
    TYPESTRUCT_MEMBER( TTPCapPack, u16, wTotalPackNum )
    TYPESTRUCT_MEMBER( TTPCapPack, u16, wCurPackIndex )
    TYPESTRUCT_MEMBER( TTPCapPack, u16, wValidCapNum )
    TYPESTRUCT_MEMBER( TTPCapPack, TTPCapMap, atTPCapMap )
TYPESTRUCT_END(  TTPCapPack )

//TTPCnStream
TYPESTRUCT_BEGIN( TTPCnStream )
    TYPESTRUCT_MEMBER( TTPCnStream, u16, wIndex )
    TYPESTRUCT_MEMBER( TTPCnStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPChanType, emChanType )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPChanSubType, emChanSubType )
    TYPESTRUCT_MEMBER( TTPCnStream, TTPMediaTransAddr, tTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPCnStream, EmTPCapSign, m_emTPCapSign )
TYPESTRUCT_END(  TTPCnStream )

//TTPCnUnpackStream
TYPESTRUCT_BEGIN( TTPCnUnpackStream )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, u16, wIndex )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, s32, nScreenNo )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPChanType, emChanType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPChanSubType, emChanSubType )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, TTPMediaTransAddr, tTPMediaTransAddr )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, EmTPCapSign, m_emTPCapSign )
    TYPESTRUCT_MEMBER( TTPCnUnpackStream, u8, byMediaTransAddrIndex )
TYPESTRUCT_END(  TTPCnUnpackStream )

//TTPDualCap
TYPESTRUCT_BEGIN( TTPDualCap )
    TYPESTRUCT_MEMBER( TTPDualCap, u16, wDualVidCapNum )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TTPDualCap, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TTPDualCap, TTPCnStream, tCnDualStream )
TYPESTRUCT_END(  TTPDualCap )

//TCnsCapset
TYPESTRUCT_BEGIN( TCnsCapset )
    TYPESTRUCT_MEMBER( TCnsCapset, EmTPEncryptType, emEncryptBits )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wFECBits )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wMaxBitRate )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPVideoCap, tVidCap )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TCnsCapset, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TCnsCapset, TTPCnStream, tCnStream )
    TYPESTRUCT_MEMBER( TCnsCapset, u16, wChannelCount )
    TYPESTRUCT_MEMBER( TCnsCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsCapset )

//TTPYouAreSeeing
TYPESTRUCT_BEGIN( TTPYouAreSeeing )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u32, m_dwVideoNum )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u32, m_dwAudioNum )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u16, m_CNSId )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, BOOL32, m_bExist )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, s8, m_achMeetingName )
    TYPESTRUCT_MEMBER( TTPYouAreSeeing, u16, m_wSpeakerIndex )
TYPESTRUCT_END(  TTPYouAreSeeing )

//TTPTerLabel
TYPESTRUCT_BEGIN( TTPTerLabel )
    TYPESTRUCT_MEMBER( TTPTerLabel, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TTPTerLabel, u8, m_byTerNo )
TYPESTRUCT_END(  TTPTerLabel )

//TPModuleTerminalInfo
TYPESTRUCT_BEGIN( TPModuleTerminalInfo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byTerNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, u8, m_byConfNo )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, s8, m_achTerminalId )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bIsChair )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bIsFloor )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bLastPack )
    TYPESTRUCT_MEMBER( TPModuleTerminalInfo, BOOL32, m_bOnline )
TYPESTRUCT_END(  TPModuleTerminalInfo )

//TTPPollDstName
TYPESTRUCT_BEGIN( TTPPollDstName )
    TYPESTRUCT_MEMBER( TTPPollDstName, s8, m_abyAlias )
    TYPESTRUCT_MEMBER( TTPPollDstName, u32, m_nScreenNum )
TYPESTRUCT_END(  TTPPollDstName )

//TMtADecParam
TYPESTRUCT_BEGIN( TMtADecParam )
    TYPESTRUCT_MEMBER( TMtADecParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtADecParam, EmTpAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TMtADecParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtADecParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TMtADecParam, TTPAacCap, tAaclc )
    TYPESTRUCT_MEMBER( TMtADecParam, u16, wPos )
TYPESTRUCT_END(  TMtADecParam )

//TMtAEncParam
TYPESTRUCT_BEGIN( TMtAEncParam )
    TYPESTRUCT_MEMBER( TMtAEncParam, EmTpCodecComponent, emComp )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPCnMediaTransPort, tAddr )
    TYPESTRUCT_MEMBER( TMtAEncParam, EmTpAudioFormat, emAudioFormat )
    TYPESTRUCT_MEMBER( TMtAEncParam, u8, byPayload )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTpEncryptKey, tEncryptKey )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TMtAEncParam, TTPAacCap, tAaclc )
    TYPESTRUCT_MEMBER( TMtAEncParam, u16, wPos )
TYPESTRUCT_END(  TMtAEncParam )

//TTPChanSelecteCascadRes
TYPESTRUCT_BEGIN( TTPChanSelecteCascadRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadRes, u32, nRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadRes, s8, achName )
TYPESTRUCT_END(  TTPChanSelecteCascadRes )

//TTPChanSelecteCascadCancelRes
TYPESTRUCT_BEGIN( TTPChanSelecteCascadCancelRes )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadCancelRes, s32, nPeerID )
    TYPESTRUCT_MEMBER( TTPChanSelecteCascadCancelRes, u32, nRes )
TYPESTRUCT_END(  TTPChanSelecteCascadCancelRes )

//TTerminalLabel
TYPESTRUCT_BEGIN( TTerminalLabel )
    TYPESTRUCT_MEMBER( TTerminalLabel, u8, m_byMcuNo )
    TYPESTRUCT_MEMBER( TTerminalLabel, u8, m_byTerNo )
TYPESTRUCT_END(  TTerminalLabel )

//TTPDisListOpr
TYPESTRUCT_BEGIN( TTPDisListOpr )
    TYPESTRUCT_MEMBER( TTPDisListOpr, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPDisListOpr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPDisListOpr, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTPDisListOpr, EmDisListOprType, m_emOprType )
    TYPESTRUCT_MEMBER( TTPDisListOpr, EmDisListOprReslt, m_emOprReslt )
TYPESTRUCT_END(  TTPDisListOpr )

//TTPRegistReq
TYPESTRUCT_BEGIN( TTPRegistReq )
    TYPESTRUCT_MEMBER( TTPRegistReq, s8, m_atH323Alias )
    TYPESTRUCT_MEMBER( TTPRegistReq, s8, m_atE164 )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tLocalAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tGKAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, TTPTransAddr, m_tRegAddress )
    TYPESTRUCT_MEMBER( TTPRegistReq, s32, m_nTimeToLive )
TYPESTRUCT_END(  TTPRegistReq )

//TCnsAVCapset
TYPESTRUCT_BEGIN( TCnsAVCapset )
    TYPESTRUCT_MEMBER( TCnsAVCapset, EmTPEncryptType, emEncryptBits )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wFECBits )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wMaxBitRate )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u16, wVidCapNum )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPVideoCap, atVidCap )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAacCap, tAacCap )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG711a )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG711u )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tG719 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPG7221Cap, tG7221 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAudCap, tMP3 )
    TYPESTRUCT_MEMBER( TCnsAVCapset, TTPAacCap, taaclc )
    TYPESTRUCT_MEMBER( TCnsAVCapset, EmTPPayloadType, aemTPMediaPT )
    TYPESTRUCT_MEMBER( TCnsAVCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsAVCapset )

//TCnsAddrCapset
TYPESTRUCT_BEGIN( TCnsAddrCapset )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, TTPCnStream, tCnStream )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, u16, wChannelCount )
    TYPESTRUCT_MEMBER( TCnsAddrCapset, u32, dwCnsIp )
TYPESTRUCT_END(  TCnsAddrCapset )

//TVgaInfo
TYPESTRUCT_BEGIN( TVgaInfo )
    TYPESTRUCT_MEMBER( TVgaInfo, EmVgaType, m_emVgaType )
    TYPESTRUCT_MEMBER( TVgaInfo, s8, m_achAlias )
TYPESTRUCT_END(  TVgaInfo )

//TTPNatCfg
TYPESTRUCT_BEGIN( TTPNatCfg )
    TYPESTRUCT_MEMBER( TTPNatCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TTPNatCfg, u32_ip, dwNatIP )
TYPESTRUCT_END(  TTPNatCfg )

//TUmsVersion
TYPESTRUCT_BEGIN( TUmsVersion )
    TYPESTRUCT_MEMBER( TUmsVersion, s8, m_abSoftVersion )
    TYPESTRUCT_MEMBER( TUmsVersion, s8, m_abHardVersion )
TYPESTRUCT_END(  TUmsVersion )

//TToolSysInfo
TYPESTRUCT_BEGIN( TToolSysInfo )
    TYPESTRUCT_MEMBER( TToolSysInfo, u32, m_dwCpuRate )
    TYPESTRUCT_MEMBER( TToolSysInfo, u32, m_dwMemRate )
TYPESTRUCT_END(  TToolSysInfo )

//THduChanInfo
TYPESTRUCT_BEGIN( THduChanInfo )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduOutPort, m_emOutPortType )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduOutMode, m_emOutModeType )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduZoomRate, m_emZoomRate )
    TYPESTRUCT_MEMBER( THduChanInfo, EmHduShowMode, m_emShowMode )
TYPESTRUCT_END(  THduChanInfo )

//THduInfo
TYPESTRUCT_BEGIN( THduInfo )
    TYPESTRUCT_MEMBER( THduInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduInfo, EMBrdType, m_emBrdType )
    TYPESTRUCT_MEMBER( THduInfo, THduChanInfo, m_atChanInfo )
    TYPESTRUCT_MEMBER( THduInfo, TTPName, m_tName )
TYPESTRUCT_END(  THduInfo )

//THduCfg
TYPESTRUCT_BEGIN( THduCfg )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduCfg, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( THduCfg, u8, m_byChanNum )
    TYPESTRUCT_MEMBER( THduCfg, THduChanInfo, m_atChanInfo )
    TYPESTRUCT_MEMBER( THduCfg, TTPName, m_tName )
    TYPESTRUCT_MEMBER( THduCfg, BOOL32, m_bReg )
    TYPESTRUCT_MEMBER( THduCfg, BOOL32, m_bServiceReg )
TYPESTRUCT_END(  THduCfg )

//THduStyleUnit
TYPESTRUCT_BEGIN( THduStyleUnit )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduStyleUnit, u8, m_byChanIndex )
    TYPESTRUCT_MEMBER( THduStyleUnit, TTPName, m_tName )
TYPESTRUCT_END(  THduStyleUnit )

//THduStyleData
TYPESTRUCT_BEGIN( THduStyleData )
    TYPESTRUCT_MEMBER( THduStyleData, u8, m_byRow )
    TYPESTRUCT_MEMBER( THduStyleData, u8, m_byCol )
    TYPESTRUCT_MEMBER( THduStyleData, THduStyleUnit, m_atUnits )
TYPESTRUCT_END(  THduStyleData )

//THduPlanUnit
TYPESTRUCT_BEGIN( THduPlanUnit )
    TYPESTRUCT_MEMBER( THduPlanUnit, BOOL32, m_bReged )
    TYPESTRUCT_MEMBER( THduPlanUnit, TTPName, m_tName )
    TYPESTRUCT_MEMBER( THduPlanUnit, u16, m_wConfID )
    TYPESTRUCT_MEMBER( THduPlanUnit, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( THduPlanUnit, BOOL32, m_bValid )
    TYPESTRUCT_MEMBER( THduPlanUnit, u16, m_wIndex )
    TYPESTRUCT_MEMBER( THduPlanUnit, EmTPHduRunStatus, m_emStatus )
    TYPESTRUCT_MEMBER( THduPlanUnit, TTPName, m_tHduName )
    TYPESTRUCT_MEMBER( THduPlanUnit, u16, m_wChannel )
TYPESTRUCT_END(  THduPlanUnit )

//THduPlanData
TYPESTRUCT_BEGIN( THduPlanData )
    TYPESTRUCT_MEMBER( THduPlanData, u8, m_byRow )
    TYPESTRUCT_MEMBER( THduPlanData, u8, m_byCol )
    TYPESTRUCT_MEMBER( THduPlanData, THduPlanUnit, m_atUnits )
TYPESTRUCT_END(  THduPlanData )

//THduStyleInfo
TYPESTRUCT_BEGIN( THduStyleInfo )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduStyleInfo, u8, m_byChanIndex )
    TYPESTRUCT_MEMBER( THduStyleInfo, TTPName, m_tName )
TYPESTRUCT_END(  THduStyleInfo )

//TTPNMServerCfg
TYPESTRUCT_BEGIN( TTPNMServerCfg )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u32_ip, dwNMServerIP )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, wNMGetSetPort )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, WNMTrapPort )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, s8, achNMReadCommunity )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, s8, achNMWriteCommunity )
    TYPESTRUCT_MEMBER( TTPNMServerCfg, u16, wNMServerNO )
TYPESTRUCT_END(  TTPNMServerCfg )

//TTPSysInfo
TYPESTRUCT_BEGIN( TTPSysInfo )
    TYPESTRUCT_MEMBER( TTPSysInfo, u8, m_byCpuRate )
    TYPESTRUCT_MEMBER( TTPSysInfo, u32, m_dwTotalByte )
    TYPESTRUCT_MEMBER( TTPSysInfo, u32, m_dwAllocByte )
TYPESTRUCT_END(  TTPSysInfo )

//TTPTPadList
TYPESTRUCT_BEGIN( TTPTPadList )
    TYPESTRUCT_MEMBER( TTPTPadList, u32_ip, m_adwTPadIP )
    TYPESTRUCT_MEMBER( TTPTPadList, u8, m_byTPadNum )
    TYPESTRUCT_MEMBER( TTPTPadList, u8, m_byUserId )
    TYPESTRUCT_MEMBER( TTPTPadList, u32, m_dwTPadNode )
    TYPESTRUCT_MATRIX( TTPTPadList, s8, m_aachTPadVersion )
TYPESTRUCT_END(  TTPTPadList )

//TTPSingleAudioPortCfg
TYPESTRUCT_BEGIN( TTPSingleAudioPortCfg )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, u8, byMicVolume )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, BOOL, bIsSimplexPoweringOpened )
    TYPESTRUCT_MEMBER( TTPSingleAudioPortCfg, u8, byAudioBNA )
TYPESTRUCT_END(  TTPSingleAudioPortCfg )

//TTpAudioPortInfo
TYPESTRUCT_BEGIN( TTpAudioPortInfo )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, u8, m_byGroupIndex )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, BOOL, m_abAudioPort )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, u8, m_abyVolume )
    TYPESTRUCT_MEMBER( TTpAudioPortInfo, TTPSingleAudioPortCfg, m_atSingleAudioPortCfg )
TYPESTRUCT_END(  TTpAudioPortInfo )

//TTPVideoPortInfo
TYPESTRUCT_BEGIN( TTPVideoPortInfo )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, EmSwitchState, emVideoState )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, EmTpVideoResolution, m_emRes )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, u8, m_byFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, BOOL, m_bIsHaveVideoSrcOutput )
    TYPESTRUCT_MEMBER( TTPVideoPortInfo, u8, m_byVolum )
TYPESTRUCT_END(  TTPVideoPortInfo )

//TTPVideoDiagInfo
TYPESTRUCT_BEGIN( TTPVideoDiagInfo )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_atPrimVideoInputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_atPrimVideoOutputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, u8, m_byInputDemoIndex )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_tDemoVideoInputPort )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, u8, m_byOutputDemoIndex )
    TYPESTRUCT_MEMBER( TTPVideoDiagInfo, TTPVideoPortInfo, m_tDemoVideoOutputPort )
TYPESTRUCT_END(  TTPVideoDiagInfo )

//TTPAudioDiagInfo
TYPESTRUCT_BEGIN( TTPAudioDiagInfo )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, TTpAudioPortInfo, m_atPrimAudioInputPort )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, TTpAudioPortInfo, m_atPrimAudioOutputPort )
    TYPESTRUCT_MEMBER( TTPAudioDiagInfo, BOOL, m_abDemoAudioPort )
TYPESTRUCT_END(  TTPAudioDiagInfo )

//TTPUpDownNetSpeedInfo
TYPESTRUCT_BEGIN( TTPUpDownNetSpeedInfo )
    TYPESTRUCT_MEMBER( TTPUpDownNetSpeedInfo, u32, m_dwInputByteDvalue )
    TYPESTRUCT_MEMBER( TTPUpDownNetSpeedInfo, u32, m_dwOutputByteDvalue )
TYPESTRUCT_END(  TTPUpDownNetSpeedInfo )

//TTPUpDownSpeedInfo
TYPESTRUCT_BEGIN( TTPUpDownSpeedInfo )
    TYPESTRUCT_MEMBER( TTPUpDownSpeedInfo, u16, m_wUpSpeed )
    TYPESTRUCT_MEMBER( TTPUpDownSpeedInfo, u16, m_wDownSpeed )
TYPESTRUCT_END(  TTPUpDownSpeedInfo )

//TTPVgaMixInfo
TYPESTRUCT_BEGIN( TTPVgaMixInfo )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, EmVgaType, m_emCurrentType )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, EmDualOutputType, m_emDualOutputType )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, s8, m_achVgaOutputFstName )
    TYPESTRUCT_MEMBER( TTPVgaMixInfo, s8, m_achVgaOutputSndName )
TYPESTRUCT_END(  TTPVgaMixInfo )

//TCnCameraCfg
TYPESTRUCT_BEGIN( TCnCameraCfg )
    TYPESTRUCT_MEMBER( TCnCameraCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TCnCameraCfg, s8, achCamera )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byAddr )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u32_ip, dwSerialServerIP )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSerialServerPort )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wZoom )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmOSDShow, emOSDShow )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmExpMode, emExpMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmGain, emGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmShutSpd, emShutSpd )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmBackLightType, emBackLightType )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byMulti )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byApt )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmWBMode, emWBMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wRGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wBGain )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmPicSceMode, emPicMode )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmGamma, emGamma )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u8, byPicApt )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wContrast )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wHue )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wSaturat )
    TYPESTRUCT_MEMBER( TCnCameraCfg, u16, wBright )
    TYPESTRUCT_MEMBER( TCnCameraCfg, EmStmClean, emStmClean )
    TYPESTRUCT_MEMBER( TCnCameraCfg, Em3DNR, em3DNR )
TYPESTRUCT_END(  TCnCameraCfg )

//TCentreTVCfg
TYPESTRUCT_BEGIN( TCentreTVCfg )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmTvPowerMode, emTvPowerMode )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmTVAudVisMode, emAudVisMode )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmTVDisplayMode, emDisMode )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmTVInputSelect, emInpSelect )
    TYPESTRUCT_MEMBER( TCentreTVCfg, EmTvSrcPowerMode, emTvSrcPowerMode )
TYPESTRUCT_END(  TCentreTVCfg )

//TTVAct
TYPESTRUCT_BEGIN( TTVAct )
    TYPESTRUCT_MEMBER( TTVAct, u16, wEvent )
    TYPESTRUCT_MEMBER( TTVAct, u8, byemType )
    TYPESTRUCT_MEMBER( TTVAct, u8, byTVIndx )
    TYPESTRUCT_MEMBER( TTVAct, time_t, ttime )
TYPESTRUCT_END(  TTVAct )

//TCenDevSleepInfo
TYPESTRUCT_BEGIN( TCenDevSleepInfo )
    TYPESTRUCT_MEMBER( TCenDevSleepInfo, BOOL, bSleepUsed )
    TYPESTRUCT_MEMBER( TCenDevSleepInfo, u32, wSleepWaitTime )
TYPESTRUCT_END(  TCenDevSleepInfo )

//TCentreCurName
TYPESTRUCT_BEGIN( TCentreCurName )
    TYPESTRUCT_MEMBER( TCentreCurName, s8, achCurName )
TYPESTRUCT_END(  TCentreCurName )

//TCentreDCamCfg
TYPESTRUCT_BEGIN( TCentreDCamCfg )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamPower, emDCamPowerMode )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamAFMode, emDCamAFMode )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamWBMode, emDCamWBMode )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, EmDCamRecallNum, emDCamRecallNum )
    TYPESTRUCT_MEMBER( TCentreDCamCfg, BOOL, bRecallPresetOne )
TYPESTRUCT_END(  TCentreDCamCfg )

//TCentreSchCfg
TYPESTRUCT_BEGIN( TCentreSchCfg )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchGatewayType, emCenSchGateType )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSerialType, emSerialType )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchPower, emSchPower )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchLight, emSchLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchMidLight, emSchMidLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, EmSchScrLight, emSchScrLight )
    TYPESTRUCT_MEMBER( TCentreSchCfg, u16, wSchTem )
TYPESTRUCT_END(  TCentreSchCfg )

//TCentreACCfg
TYPESTRUCT_BEGIN( TCentreACCfg )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, byID )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmSerialType, emSerType )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACPower, emACPower )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, bySetTemp )
    TYPESTRUCT_MEMBER( TCentreACCfg, u8, byCurTemp )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACAirVol, emACAirVol )
    TYPESTRUCT_MEMBER( TCentreACCfg, EmCentreACMode, emACMode )
TYPESTRUCT_END(  TCentreACCfg )

//TOprBoardResult
TYPESTRUCT_BEGIN( TOprBoardResult )
    TYPESTRUCT_MEMBER( TOprBoardResult, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TOprBoardResult, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TOprBoardResult, EmTpBoardRet, m_emReason )
TYPESTRUCT_END(  TOprBoardResult )

//TTPBrdPos
TYPESTRUCT_BEGIN( TTPBrdPos )
    TYPESTRUCT_MEMBER( TTPBrdPos, EMBrdType, m_emBrdType )
    TYPESTRUCT_MEMBER( TTPBrdPos, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TTPBrdPos, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TTPBrdPos, u32_ip, m_dwBrdIP )
TYPESTRUCT_END(  TTPBrdPos )

//TTPBrdCfg
TYPESTRUCT_BEGIN( TTPBrdCfg )
    TYPESTRUCT_MEMBER( TTPBrdCfg, u8, m_byBrdID )
    TYPESTRUCT_MEMBER( TTPBrdCfg, TTPBrdPos, m_tBrdPos )
TYPESTRUCT_END(  TTPBrdCfg )

//TTPEqpCfg
TYPESTRUCT_BEGIN( TTPEqpCfg )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPEqpCfg, EMEqpType, m_emEqpType )
    TYPESTRUCT_MEMBER( TTPEqpCfg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPEqpCfg, s8, m_szEqpAlias )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdID )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdLayer )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byBrdSlot )
    TYPESTRUCT_MEMBER( TTPEqpCfg, u8, m_byAudmixNum )
TYPESTRUCT_END(  TTPEqpCfg )

//TTPMdlCfg
TYPESTRUCT_BEGIN( TTPMdlCfg )
    TYPESTRUCT_MEMBER( TTPMdlCfg, EMEqpType, m_emEqpType )
    TYPESTRUCT_MEMBER( TTPMdlCfg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPMdlCfg, s8, m_szEqpAlias )
    TYPESTRUCT_MEMBER( TTPMdlCfg, u16, m_wEqpId )
    TYPESTRUCT_MEMBER( TTPMdlCfg, u8, m_byAudmixNum )
TYPESTRUCT_END(  TTPMdlCfg )

//TTPBrdInfo
TYPESTRUCT_BEGIN( TTPBrdInfo )
    TYPESTRUCT_MEMBER( TTPBrdInfo, TTPBrdCfg, m_tBrdCfg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, TTPMdlCfg, m_tBrdMode )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_bReg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_abEqpReg )
    TYPESTRUCT_MEMBER( TTPBrdInfo, BOOL32, m_bBrdUsed )
TYPESTRUCT_END(  TTPBrdInfo )

//TTPBrdMdlInfo
TYPESTRUCT_BEGIN( TTPBrdMdlInfo )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, u8, m_byIndex )
    TYPESTRUCT_MEMBER( TTPBrdMdlInfo, TTPMdlCfg, m_atMdlCfg )
TYPESTRUCT_END(  TTPBrdMdlInfo )

//TTPBrdUsedInfo
TYPESTRUCT_BEGIN( TTPBrdUsedInfo )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, EMEqpType, m_emType )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, u16, m_wRegNum )
    TYPESTRUCT_MEMBER( TTPBrdUsedInfo, u16, m_wUsedNum )
TYPESTRUCT_END(  TTPBrdUsedInfo )

//TTPBrdUpGrade
TYPESTRUCT_BEGIN( TTPBrdUpGrade )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, u8, m_byLayer )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, u8, m_bySlot )
    TYPESTRUCT_MEMBER( TTPBrdUpGrade, s8, m_szFileName )
TYPESTRUCT_END(  TTPBrdUpGrade )

//TTPAudPower
TYPESTRUCT_BEGIN( TTPAudPower )
    TYPESTRUCT_MEMBER( TTPAudPower, u8, abyInput )
    TYPESTRUCT_MEMBER( TTPAudPower, u32, adwOutput )
TYPESTRUCT_END(  TTPAudPower )

//TTPHdAudioPort
TYPESTRUCT_BEGIN( TTPHdAudioPort )
    TYPESTRUCT_MEMBER( TTPHdAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( TTPHdAudioPort, u8, byPos )
TYPESTRUCT_END(  TTPHdAudioPort )

//TTPHdAudioOutPort
TYPESTRUCT_BEGIN( TTPHdAudioOutPort )
    TYPESTRUCT_MEMBER( TTPHdAudioOutPort, u8, abHdAudPortOut )
    TYPESTRUCT_MEMBER( TTPHdAudioOutPort, u8, byPos )
TYPESTRUCT_END(  TTPHdAudioOutPort )

//TTPHdDualAudioPort
TYPESTRUCT_BEGIN( TTPHdDualAudioPort )
    TYPESTRUCT_MEMBER( TTPHdDualAudioPort, u8, abHdAudPortIn )
    TYPESTRUCT_MEMBER( TTPHdDualAudioPort, u8, byPos )
TYPESTRUCT_END(  TTPHdDualAudioPort )

//TTPMPAudioInfo
TYPESTRUCT_BEGIN( TTPMPAudioInfo )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsAECEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsAGCEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, BOOL, m_bIsANSEnable )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, EmTpAudioFormat, m_emAudioFormatPriorStrategy )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, u8, m_byInputVolume )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, u8, m_byOutputVolume )
    TYPESTRUCT_MEMBER( TTPMPAudioInfo, EmTPLoudspeakerVal, m_emLoudspeakerVal )
TYPESTRUCT_END(  TTPMPAudioInfo )

//TTPVideoDisplayFrm
TYPESTRUCT_BEGIN( TTPVideoDisplayFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw1080PFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw1080IFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dwVGAFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dw720PFrm )
    TYPESTRUCT_MEMBER( TTPVideoDisplayFrm, u32, m_dwSDFrm )
TYPESTRUCT_END(  TTPVideoDisplayFrm )

//TTPVideoParam
TYPESTRUCT_BEGIN( TTPVideoParam )
    TYPESTRUCT_MEMBER( TTPVideoParam, BOOL, bUseFixedFrame )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTPFrameUnitType, emFrameUnit )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byQualMaxValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byQualMinValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wIKeyRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpEncodeMode, emEncodeMode )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpLostPackageRestore, emRestoreType )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wH264IKeyRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byH264QualMaxValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byH264QualMinValue )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wWidth )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wHeight )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpMediaType, emCapType )
    TYPESTRUCT_MEMBER( TTPVideoParam, EmTpPCCapFormat, emPCCapFormat )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, by720pFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byVgaFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u8, byD1FrameRate )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwProfile )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwAvgQpI )
    TYPESTRUCT_MEMBER( TTPVideoParam, u32, dwAvgQpP )
    TYPESTRUCT_MEMBER( TTPVideoParam, u16, wChanMaxBitrate )
TYPESTRUCT_END(  TTPVideoParam )

//TTPImageAdjustParam
TYPESTRUCT_BEGIN( TTPImageAdjustParam )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wBrightness )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wContrast )
    TYPESTRUCT_MEMBER( TTPImageAdjustParam, u8, wSaturation )
TYPESTRUCT_END(  TTPImageAdjustParam )

//TTPVideoInfo
TYPESTRUCT_BEGIN( TTPVideoInfo )
    TYPESTRUCT_MEMBER( TTPVideoInfo, TTPImageAdjustParam, m_tImageAdjustParam )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTpVideoFormat, m_emVideoFormatPriorStrategy )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTpVideoResolution, m_emVideoResolvePriorStrategy )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTPVideoStandard, m_emOutVideoStandard )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTPVideoStandard, m_emInVideoStandard )
    TYPESTRUCT_MEMBER( TTPVideoInfo, EmTPVideoPort, m_emVideoSource )
TYPESTRUCT_END(  TTPVideoInfo )

//TTPSymboPoint
TYPESTRUCT_BEGIN( TTPSymboPoint )
    TYPESTRUCT_MEMBER( TTPSymboPoint, u16, X )
    TYPESTRUCT_MEMBER( TTPSymboPoint, u16, Y )
TYPESTRUCT_END(  TTPSymboPoint )

//TTPVgaOutCfg
TYPESTRUCT_BEGIN( TTPVgaOutCfg )
    TYPESTRUCT_MEMBER( TTPVgaOutCfg, BOOL, bVgaOut )
    TYPESTRUCT_MEMBER( TTPVgaOutCfg, u16, wRefreshRate )
TYPESTRUCT_END(  TTPVgaOutCfg )

//TTPFecInfo
TYPESTRUCT_BEGIN( TTPFecInfo )
    TYPESTRUCT_MEMBER( TTPFecInfo, BOOL, m_bEnableFec )
    TYPESTRUCT_MEMBER( TTPFecInfo, u8, m_byAlgorithm )
    TYPESTRUCT_MEMBER( TTPFecInfo, u16, m_wPackLen )
    TYPESTRUCT_MEMBER( TTPFecInfo, BOOL, m_bIntraFrame )
    TYPESTRUCT_MEMBER( TTPFecInfo, u32, m_dwDataPackNum )
    TYPESTRUCT_MEMBER( TTPFecInfo, u32, m_dwCrcPackNum )
TYPESTRUCT_END(  TTPFecInfo )

//TTPLostPackResend
TYPESTRUCT_BEGIN( TTPLostPackResend )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUse )
    TYPESTRUCT_MEMBER( TTPLostPackResend, EmTPNetType, emNetType )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u8, byResendLevel )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wRejectTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, u16, wSendBufTimeSpan )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUseSmoothSend )
    TYPESTRUCT_MEMBER( TTPLostPackResend, BOOL, bUseAdaptSend )
TYPESTRUCT_END(  TTPLostPackResend )

//TTPBitRateAdjust
TYPESTRUCT_BEGIN( TTPBitRateAdjust )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wInterval )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wLostTimes )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wDescRatio )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wLowDescRatio )
    TYPESTRUCT_MEMBER( TTPBitRateAdjust, u16, wDelayInterval )
TYPESTRUCT_END(  TTPBitRateAdjust )

//TTPVideoStandard
TYPESTRUCT_BEGIN( TTPVideoStandard )
    TYPESTRUCT_MEMBER( TTPVideoStandard, EmTPVideoType, emVideoType )
    TYPESTRUCT_MEMBER( TTPVideoStandard, BOOL, bIsInPort )
    TYPESTRUCT_MEMBER( TTPVideoStandard, EmTPVideoStandard, emStandard )
TYPESTRUCT_END(  TTPVideoStandard )

//TTPVideoPort
TYPESTRUCT_BEGIN( TTPVideoPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPMtVideoPort, emTPMtVideoPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPMtVideoOutPort, emTPMtVideoOutPort )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPDVIMode, emTPDVIInMode )
    TYPESTRUCT_MEMBER( TTPVideoPort, EmTPDVIMode, emTPDVIOutMode )
TYPESTRUCT_END(  TTPVideoPort )

//TTPAutoTestMsg
TYPESTRUCT_BEGIN( TTPAutoTestMsg )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, EmTPAutoTestType, m_emAutoTestType )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, BOOL, m_bAutoTestStart )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, EmTPVideoType, m_emVideoType )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPVideoPort, tTPVideoPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdAudioPort, tTPHdAudioPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdDualAudioPort, tTPHdDualAudioPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, TTPHdAudioOutPort, tTPHdAudioOutPort )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPAutoTestMsg, u8, byMPCodecNum )
TYPESTRUCT_END(  TTPAutoTestMsg )

//TTPEqualizer
TYPESTRUCT_BEGIN( TTPEqualizer )
    TYPESTRUCT_MEMBER( TTPEqualizer, s32, anEqualizerGain )
    TYPESTRUCT_MEMBER( TTPEqualizer, BOOL, bEqualizer )
    TYPESTRUCT_MEMBER( TTPEqualizer, u8, byIndex )
TYPESTRUCT_END(  TTPEqualizer )

//TTPPIPMod
TYPESTRUCT_BEGIN( TTPPIPMod )
    TYPESTRUCT_MEMBER( TTPPIPMod, EmTPPIPMode, emTPPIPMode )
    TYPESTRUCT_MEMBER( TTPPIPMod, u8, byIndex )
TYPESTRUCT_END(  TTPPIPMod )

//TTPLostFrameRate
TYPESTRUCT_BEGIN( TTPLostFrameRate )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, u8, byLostFrameRate )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPLostFrameRate, BOOL, bvalid )
TYPESTRUCT_END(  TTPLostFrameRate )

//TTPVideoRecv
TYPESTRUCT_BEGIN( TTPVideoRecv )
    TYPESTRUCT_MEMBER( TTPVideoRecv, u8, abyVEncRecv )
    TYPESTRUCT_MEMBER( TTPVideoRecv, u8, abyVDecRecv )
TYPESTRUCT_END(  TTPVideoRecv )

//TTPVideoEncDecRes
TYPESTRUCT_BEGIN( TTPVideoEncDecRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, EmTpVideoResolution, enRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPVideoEncDecRes, BOOL, bvalid )
TYPESTRUCT_END(  TTPVideoEncDecRes )

//TTPVideoEncDecResPack
TYPESTRUCT_BEGIN( TTPVideoEncDecResPack )
    TYPESTRUCT_MEMBER( TTPVideoEncDecResPack, TTPVideoEncDecRes, atVideoRes )
    TYPESTRUCT_MEMBER( TTPVideoEncDecResPack, u8, byNum )
TYPESTRUCT_END(  TTPVideoEncDecResPack )

//TTPVideoFrameRate
TYPESTRUCT_BEGIN( TTPVideoFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, u16, wFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, TTpCodecComponent, tTpCodc )
    TYPESTRUCT_MEMBER( TTPVideoFrameRate, BOOL, bvalid )
TYPESTRUCT_END(  TTPVideoFrameRate )

//TTPVideoFrameRatePack
TYPESTRUCT_BEGIN( TTPVideoFrameRatePack )
    TYPESTRUCT_MEMBER( TTPVideoFrameRatePack, TTPVideoFrameRate, atVideoFrameRate )
    TYPESTRUCT_MEMBER( TTPVideoFrameRatePack, u8, byNum )
TYPESTRUCT_END(  TTPVideoFrameRatePack )

//TTPCodecPackStat
TYPESTRUCT_BEGIN( TTPCodecPackStat )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoFrameRatePack, tTPVideoFrameRatePack )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoEncDecResPack, tTPVideoEncDecResPack )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPVideoRecv, tTPVideoRecv )
    TYPESTRUCT_MEMBER( TTPCodecPackStat, TTPAudPower, tTPAudPower )
TYPESTRUCT_END(  TTPCodecPackStat )

//TTPCnDsData
TYPESTRUCT_BEGIN( TTPCnDsData )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tRcvFromAddr )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tSndToAddr )
    TYPESTRUCT_MEMBER( TTPCnDsData, TTPTransAddr, m_tMapedAddr )
TYPESTRUCT_END(  TTPCnDsData )

//TTPCnNetBufPara
TYPESTRUCT_BEGIN( TTPCnNetBufPara )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_wSndAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRcvRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRcvRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRmtRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, TTPTransAddr, m_tRmtRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnNetBufPara, u32, m_Handle )
TYPESTRUCT_END(  TTPCnNetBufPara )

//TTPCnRSParam
TYPESTRUCT_BEGIN( TTPCnRSParam )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wFirstTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wSecondTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wThirdTimeSpan )
    TYPESTRUCT_MEMBER( TTPCnRSParam, u16, m_wRejectTimeSpan )
TYPESTRUCT_END(  TTPCnRSParam )

//TTPAllConfCnsInfo
TYPESTRUCT_BEGIN( TTPAllConfCnsInfo )
    TYPESTRUCT_MEMBER( TTPAllConfCnsInfo, TCnsInfo, m_tCnsInfo )
    TYPESTRUCT_MEMBER( TTPAllConfCnsInfo, u16, m_wNum )
TYPESTRUCT_END(  TTPAllConfCnsInfo )

//TCnDsType
TYPESTRUCT_BEGIN( TCnDsType )
    TYPESTRUCT_MEMBER( TCnDsType, u32, dwHandle )
    TYPESTRUCT_MEMBER( TCnDsType, u16, wDsType )
    TYPESTRUCT_MEMBER( TCnDsType, u16, wSubDsType )
TYPESTRUCT_END(  TCnDsType )

//TTPCnMixAddr
TYPESTRUCT_BEGIN( TTPCnMixAddr )
    TYPESTRUCT_MEMBER( TTPCnMixAddr, TTPMediaTransAddr, m_tRcv )
    TYPESTRUCT_MEMBER( TTPCnMixAddr, TTPMediaTransAddr, m_tSnd )
TYPESTRUCT_END(  TTPCnMixAddr )

//TTPCnMixChan
TYPESTRUCT_BEGIN( TTPCnMixChan )
    TYPESTRUCT_MEMBER( TTPCnMixChan, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTPCnMixChan, TTPCnMixAddr, m_tMixAddr )
TYPESTRUCT_END(  TTPCnMixChan )

//TTPCnMixParam
TYPESTRUCT_BEGIN( TTPCnMixParam )
    TYPESTRUCT_MEMBER( TTPCnMixParam, u16, m_wCurSpeaker )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPCnMixChan, m_atAudMix )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNSndRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNSndMixBackRtcpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNRcvRtpAddr )
    TYPESTRUCT_MEMBER( TTPCnMixParam, TTPTransAddr, m_tNRcvBackRtcpAddr )
TYPESTRUCT_END(  TTPCnMixParam )

//TTPNetAddress
TYPESTRUCT_BEGIN( TTPNetAddress )
    TYPESTRUCT_MEMBER( TTPNetAddress, u32, dwIp )
    TYPESTRUCT_MEMBER( TTPNetAddress, u16, wPort )
TYPESTRUCT_END(  TTPNetAddress )

//TTPMixerChannelParam
TYPESTRUCT_BEGIN( TTPMixerChannelParam )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tSrcNetAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tRtcpBackAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tRtcpLocalAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tLocalNetAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tLocalNetRtcpAddr )
    TYPESTRUCT_MEMBER( TTPMixerChannelParam, TTPNetAddress, m_tDstNetAddr )
TYPESTRUCT_END(  TTPMixerChannelParam )

//TTPCallSerInfo
TYPESTRUCT_BEGIN( TTPCallSerInfo )
    TYPESTRUCT_MEMBER( TTPCallSerInfo, u32_ip, dwCallServiceIP )
TYPESTRUCT_END(  TTPCallSerInfo )

//TTPVidSrcCutLines
TYPESTRUCT_BEGIN( TTPVidSrcCutLines )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u32, dwLCutLine )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u32, dwRCutline )
    TYPESTRUCT_MEMBER( TTPVidSrcCutLines, u8, byPos )
TYPESTRUCT_END(  TTPVidSrcCutLines )

//TVcrCfg
TYPESTRUCT_BEGIN( TVcrCfg )
    TYPESTRUCT_MEMBER( TVcrCfg, s8, m_achName )
    TYPESTRUCT_MEMBER( TVcrCfg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TVcrCfg, u32_ip, m_dwIP )
TYPESTRUCT_END(  TVcrCfg )

//TAdjustFrameRate
TYPESTRUCT_BEGIN( TAdjustFrameRate )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAdjustFrameRate, u16, m_wFrameRate )
TYPESTRUCT_END(  TAdjustFrameRate )

//TAdjustVidRes
TYPESTRUCT_BEGIN( TAdjustVidRes )
    TYPESTRUCT_MEMBER( TAdjustVidRes, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAdjustVidRes, u32, m_dwVidRes )
TYPESTRUCT_END(  TAdjustVidRes )

//TTPVGAInfo
TYPESTRUCT_BEGIN( TTPVGAInfo )
    TYPESTRUCT_MEMBER( TTPVGAInfo, u32, m_adwVGA_DF_PC )
    TYPESTRUCT_MEMBER( TTPVGAInfo, u32, m_adwVGA_DF_FS )
TYPESTRUCT_END(  TTPVGAInfo )

//TTPBmpInfo
TYPESTRUCT_BEGIN( TTPBmpInfo )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwWidth )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwHeight )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u8, m_achBMP )
    TYPESTRUCT_MEMBER( TTPBmpInfo, u32, m_dwBmpLen )
TYPESTRUCT_END(  TTPBmpInfo )

//TTPAddLogoPos
TYPESTRUCT_BEGIN( TTPAddLogoPos )
    TYPESTRUCT_MEMBER( TTPAddLogoPos, u32, m_dwXPos )
    TYPESTRUCT_MEMBER( TTPAddLogoPos, u32, m_dwYPos )
TYPESTRUCT_END(  TTPAddLogoPos )

//TTPTranspDColor
TYPESTRUCT_BEGIN( TTPTranspDColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byRColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byGColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byBColor )
    TYPESTRUCT_MEMBER( TTPTranspDColor, u8, m_byTransparency )
TYPESTRUCT_END(  TTPTranspDColor )

//TTPAddLogoParam
TYPESTRUCT_BEGIN( TTPAddLogoParam )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwXPos )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwYPos )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwLogoWidth )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, u32, m_dwLogoHeight )
    TYPESTRUCT_MEMBER( TTPAddLogoParam, TTPTranspDColor, m_tBackBGDColor )
TYPESTRUCT_END(  TTPAddLogoParam )

//TTPFullLogoParam
TYPESTRUCT_BEGIN( TTPFullLogoParam )
    TYPESTRUCT_MEMBER( TTPFullLogoParam, TTPBmpInfo, m_tBmpInfo )
    TYPESTRUCT_MEMBER( TTPFullLogoParam, TTPAddLogoParam, m_tLogoParam )
TYPESTRUCT_END(  TTPFullLogoParam )

//TCnProduceTestMsg
TYPESTRUCT_BEGIN( TCnProduceTestMsg )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u16, m_wVersionNum )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, EmProducetestType, m_emProduceTestType )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, BOOL, m_bProduceTestStart )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, BOOL, m_bProduceTestReult )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u16, m_byErrorReason )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u32_ip, m_adwLocalIp )
    TYPESTRUCT_MEMBER( TCnProduceTestMsg, u32_ip, m_adwDstIp )
TYPESTRUCT_END(  TCnProduceTestMsg )

//TRecBaseInfo
TYPESTRUCT_BEGIN( TRecBaseInfo )
    TYPESTRUCT_MEMBER( TRecBaseInfo, s8, m_achName )
    TYPESTRUCT_MEMBER( TRecBaseInfo, u32, m_dwFreeSize )
    TYPESTRUCT_MEMBER( TRecBaseInfo, u32, m_dwTotalSize )
TYPESTRUCT_END(  TRecBaseInfo )

//TRecFileListInfo
TYPESTRUCT_BEGIN( TRecFileListInfo )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u16, m_wTotalSize )
    TYPESTRUCT_MEMBER( TRecFileListInfo, u16, m_wCurSize )
    TYPESTRUCT_MATRIX( TRecFileListInfo, s8, m_achFileName )
TYPESTRUCT_END(  TRecFileListInfo )

//TRecFileInfo
TYPESTRUCT_BEGIN( TRecFileInfo )
    TYPESTRUCT_MEMBER( TRecFileInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecFileInfo, s8, m_szFilelName )
TYPESTRUCT_END(  TRecFileInfo )

//TRecorderConfInfo
TYPESTRUCT_BEGIN( TRecorderConfInfo )
    TYPESTRUCT_MEMBER( TRecorderConfInfo, TUmsVidFormat, m_tConfFormat )
TYPESTRUCT_END(  TRecorderConfInfo )

//TRecorderMTInfo
TYPESTRUCT_BEGIN( TRecorderMTInfo )
    TYPESTRUCT_MEMBER( TRecorderMTInfo, u16, m_wMtID )
TYPESTRUCT_END(  TRecorderMTInfo )

//TRecConfInfo
TYPESTRUCT_BEGIN( TRecConfInfo )
    TYPESTRUCT_MEMBER( TRecConfInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecConfInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecConfInfo, EmRecorderType, m_emType )
    TYPESTRUCT_MEMBER( TRecConfInfo, s8, m_achFileName )
    TYPESTRUCT_MEMBER( TRecConfInfo, BOOL32, m_bRecDual )
    TYPESTRUCT_MEMBER( TRecConfInfo, TUmsVidFormat, m_tDualFormat )
    TYPESTRUCT_MEMBER( TRecConfInfo, TRecorderConfInfo, m_tConfRecInfo )
    TYPESTRUCT_MEMBER( TRecConfInfo, TRecorderMTInfo, m_tMtRecInfo )
TYPESTRUCT_END(  TRecConfInfo )

//TConRecState
TYPESTRUCT_BEGIN( TConRecState )
    TYPESTRUCT_MEMBER( TConRecState, TRecConfInfo, m_tInfo )
    TYPESTRUCT_MEMBER( TConRecState, EmConfRecState, m_emState )
    TYPESTRUCT_MEMBER( TConRecState, u32, m_dwRecTime )
TYPESTRUCT_END(  TConRecState )

//TRecConfRes
TYPESTRUCT_BEGIN( TRecConfRes )
    TYPESTRUCT_MEMBER( TRecConfRes, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecConfRes, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecConfRes, EmRecorderType, m_emType )
    TYPESTRUCT_MEMBER( TRecConfRes, u16, m_wMtID )
TYPESTRUCT_END(  TRecConfRes )

//TRecPlayInfo
TYPESTRUCT_BEGIN( TRecPlayInfo )
    TYPESTRUCT_MEMBER( TRecPlayInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TRecPlayInfo, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TRecPlayInfo, BOOL32, m_bPlayInDual )
    TYPESTRUCT_MEMBER( TRecPlayInfo, s8, m_szFileName )
    TYPESTRUCT_MEMBER( TRecPlayInfo, TUmsVidFormat, m_tConfFormat )
    TYPESTRUCT_MEMBER( TRecPlayInfo, TUmsVidFormat, m_tDualFormat )
TYPESTRUCT_END(  TRecPlayInfo )

//TPlayStatusMdyInfo
TYPESTRUCT_BEGIN( TPlayStatusMdyInfo )
    TYPESTRUCT_MEMBER( TPlayStatusMdyInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TPlayStatusMdyInfo, u16, m_wConfID )
TYPESTRUCT_END(  TPlayStatusMdyInfo )

//TConfPlayStatus
TYPESTRUCT_BEGIN( TConfPlayStatus )
    TYPESTRUCT_MEMBER( TConfPlayStatus, EmConfRecState, m_emState )
    TYPESTRUCT_MEMBER( TConfPlayStatus, TRecPlayInfo, m_tInfo )
    TYPESTRUCT_MEMBER( TConfPlayStatus, u32, m_dwTotalTime )
    TYPESTRUCT_MEMBER( TConfPlayStatus, u32, m_dwCurTime )
TYPESTRUCT_END(  TConfPlayStatus )

//TTPUpgradeSer
TYPESTRUCT_BEGIN( TTPUpgradeSer )
    TYPESTRUCT_MEMBER( TTPUpgradeSer, u32_ip, dwSerIP )
TYPESTRUCT_END(  TTPUpgradeSer )

//TTPSnapInfo
TYPESTRUCT_BEGIN( TTPSnapInfo )
    TYPESTRUCT_MEMBER( TTPSnapInfo, u8, byPos )
    TYPESTRUCT_MEMBER( TTPSnapInfo, s8, achSnapName )
    TYPESTRUCT_MEMBER( TTPSnapInfo, BOOL, bShow )
TYPESTRUCT_END(  TTPSnapInfo )

//TTPSingleLoopInfo
TYPESTRUCT_BEGIN( TTPSingleLoopInfo )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, EmTpMediaType, emMediaType )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, BOOL, bLoop )
    TYPESTRUCT_MEMBER( TTPSingleLoopInfo, u8, byPos )
TYPESTRUCT_END(  TTPSingleLoopInfo )

//TTPAllLoopInfo
TYPESTRUCT_BEGIN( TTPAllLoopInfo )
    TYPESTRUCT_MEMBER( TTPAllLoopInfo, u8, byPos )
    TYPESTRUCT_MEMBER( TTPAllLoopInfo, TTPSingleLoopInfo, tSingleLoopInfo )
TYPESTRUCT_END(  TTPAllLoopInfo )

//TTPMtTerminal
TYPESTRUCT_BEGIN( TTPMtTerminal )
    TYPESTRUCT_MEMBER( TTPMtTerminal, u32_ip, m_dwIp )
    TYPESTRUCT_MEMBER( TTPMtTerminal, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPMtTerminal, EmTPEndpointType, m_emType )
TYPESTRUCT_END(  TTPMtTerminal )

//TTPMtOnLineList
TYPESTRUCT_BEGIN( TTPMtOnLineList )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, TTPMtTerminal, m_atTerminal )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, BOOL32, m_bIsEnd )
    TYPESTRUCT_MEMBER( TTPMtOnLineList, u32_ip, m_dwIP )
TYPESTRUCT_END(  TTPMtOnLineList )

//TTPMtRegInfo
TYPESTRUCT_BEGIN( TTPMtRegInfo )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, TTPMtTerminal, m_atTerminal )
    TYPESTRUCT_MEMBER( TTPMtRegInfo, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TTPMtRegInfo )

//TTPMcuRegInfo
TYPESTRUCT_BEGIN( TTPMcuRegInfo )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, u16, m_wListNum )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, BOOL32, m_bIsEnd )
    TYPESTRUCT_MEMBER( TTPMcuRegInfo, u32_ip, m_dwIP )
TYPESTRUCT_END(  TTPMcuRegInfo )

//TRegPackInfoEx
TYPESTRUCT_BEGIN( TRegPackInfoEx )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, TTPSipRegPackInfo, m_tPackInfo )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, EmGetRegInfoType, m_emType )
    TYPESTRUCT_MEMBER( TRegPackInfoEx, EmTPEndpointType, m_emEndpointType )
TYPESTRUCT_END(  TRegPackInfoEx )

//TUmsRegInfoEx
TYPESTRUCT_BEGIN( TUmsRegInfoEx )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, TTPTransAddr, m_atContactAddr )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u32, m_dwExpires )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, s8, m_softversion )
    TYPESTRUCT_MEMBER( TUmsRegInfoEx, s8, m_compileTime )
TYPESTRUCT_END(  TUmsRegInfoEx )

//TUmsRegPackEx
TYPESTRUCT_BEGIN( TUmsRegPackEx )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, u16, m_wSize )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, TUmsRegInfoEx, m_atRegInfo )
    TYPESTRUCT_MEMBER( TUmsRegPackEx, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TUmsRegPackEx )

//TCnsRegInfoEx
TYPESTRUCT_BEGIN( TCnsRegInfoEx )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u16, m_wAliasNum )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, TTPAlias, m_atAlias )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, TTPTransAddr, m_atContactAddr )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u32, m_dwExpires )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, EmTPEndpointType, m_emEndpointType )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, u32_ip, m_locolIP )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, s8, m_softversion )
    TYPESTRUCT_MEMBER( TCnsRegInfoEx, s8, m_compileTime )
TYPESTRUCT_END(  TCnsRegInfoEx )

//TCnsRegPackEx
TYPESTRUCT_BEGIN( TCnsRegPackEx )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, u16, m_wSize )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, TCnsRegInfoEx, m_atRegInfo )
    TYPESTRUCT_MEMBER( TCnsRegPackEx, BOOL32, m_bIsEnd )
TYPESTRUCT_END(  TCnsRegPackEx )

//TTPAudPlayMode
TYPESTRUCT_BEGIN( TTPAudPlayMode )
    TYPESTRUCT_MEMBER( TTPAudPlayMode, u8, abChnID )
TYPESTRUCT_END(  TTPAudPlayMode )

//TTPSmallPicRectInfo
TYPESTRUCT_BEGIN( TTPSmallPicRectInfo )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, BOOL32, bUsrCfg )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwMergeStyle )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwPosIndex )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleX )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleY )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleW )
    TYPESTRUCT_MEMBER( TTPSmallPicRectInfo, u32, dwScaleH )
TYPESTRUCT_END(  TTPSmallPicRectInfo )

//TTPRecMtFormat
TYPESTRUCT_BEGIN( TTPRecMtFormat )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, u16, m_wMtID )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, BOOL32, m_bValid )
    TYPESTRUCT_MEMBER( TTPRecMtFormat, TUmsVidFormat, m_tVidFormat )
TYPESTRUCT_END(  TTPRecMtFormat )

//TTPRebootTime
TYPESTRUCT_BEGIN( TTPRebootTime )
    TYPESTRUCT_MEMBER( TTPRebootTime, BOOL, bReboot )
    TYPESTRUCT_MEMBER( TTPRebootTime, u8, byHour )
TYPESTRUCT_END(  TTPRebootTime )

//TTPVidForamt
TYPESTRUCT_BEGIN( TTPVidForamt )
    TYPESTRUCT_MEMBER( TTPVidForamt, EmTpVideoQualityLevel, emTpVideoQualityLevel )
    TYPESTRUCT_MEMBER( TTPVidForamt, EmTpVideoResolution, emTpVideoResolution )
    TYPESTRUCT_MEMBER( TTPVidForamt, u16, wVidFrameRate )
TYPESTRUCT_END(  TTPVidForamt )

//TTPVidOffsetParam
TYPESTRUCT_BEGIN( TTPVidOffsetParam )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, EmTPMtVideoPort, emPort )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, s32, nHoff )
    TYPESTRUCT_MEMBER( TTPVidOffsetParam, s32, nVoff )
TYPESTRUCT_END(  TTPVidOffsetParam )

//TTPAllVidOffsetParam
TYPESTRUCT_BEGIN( TTPAllVidOffsetParam )
    TYPESTRUCT_MEMBER( TTPAllVidOffsetParam, TTPVidOffsetParam, tVidOffsetParam )
TYPESTRUCT_END(  TTPAllVidOffsetParam )

//TTPCnConfInfo
TYPESTRUCT_BEGIN( TTPCnConfInfo )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, TCnVideoParam, tCnVideoParam )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, EmTpAudioFormat, emTpAudioFormat )
    TYPESTRUCT_MEMBER( TTPCnConfInfo, u16, wDualCallBit )
TYPESTRUCT_END(  TTPCnConfInfo )

//TTPDisplayType
TYPESTRUCT_BEGIN( TTPDisplayType )
    TYPESTRUCT_MEMBER( TTPDisplayType, EmTVInputSelect, emTPT300Type )
    TYPESTRUCT_MEMBER( TTPDisplayType, EmTVInputSelect, emTPHduType )
TYPESTRUCT_END(  TTPDisplayType )

//TChairSingleStreenInfo
TYPESTRUCT_BEGIN( TChairSingleStreenInfo )
    TYPESTRUCT_MEMBER( TChairSingleStreenInfo, EMScreenLooked, emScreenInfo )
    TYPESTRUCT_MEMBER( TChairSingleStreenInfo, u16, wEpId )
TYPESTRUCT_END(  TChairSingleStreenInfo )

//TChanViewRes
TYPESTRUCT_BEGIN( TChanViewRes )
    TYPESTRUCT_MEMBER( TChanViewRes, EmTPViewResult, m_emRes )
    TYPESTRUCT_MEMBER( TChanViewRes, TTPAlias, m_tAlias )
TYPESTRUCT_END(  TChanViewRes )

//TChairStreenInfo
TYPESTRUCT_BEGIN( TChairStreenInfo )
    TYPESTRUCT_MEMBER( TChairStreenInfo, TConfEpID, tConfID )
    TYPESTRUCT_MEMBER( TChairStreenInfo, u16, wStreenNum )
    TYPESTRUCT_MEMBER( TChairStreenInfo, TChairSingleStreenInfo, tChairStreenInfo )
TYPESTRUCT_END(  TChairStreenInfo )

//TTPEthnetInfo
TYPESTRUCT_BEGIN( TTPEthnetInfo )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, BOOL, bEnable )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwIP )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwMask )
    TYPESTRUCT_MEMBER( TTPEthnetInfo, u32_ip, dwGateWay )
TYPESTRUCT_END(  TTPEthnetInfo )

//TTPMoonCamInfo
TYPESTRUCT_BEGIN( TTPMoonCamInfo )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, s8, achDescription )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, BOOL, bIsUsed )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, BOOL, bIsPreUsed )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwZoom )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPMOOMMode, emFocusMode )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwFocusValue )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPMOOMMode, emExpMode )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPExpGain, emGain )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPSOrThShutter, emSOrThShutSpd )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPFOrTwShutter, emFOrTwShutSpd )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPAperture, emAper )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPMOOMMode, emWBMode )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwRGain )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwBGain )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, BOOL, bIsBLCSwitch )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwContrast )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwSharp )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwSaturat )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwBright )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPFpgaReduNoise, emReduNoise )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, BOOL, bIsCorrect )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwCorrectLevel )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwStretchRegion )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwHorizonCorrect )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwHorizonStretch )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwVerticalCorrect )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwVerticalStretch )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmH650Gamma, emGamma )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPReduNoise, em2DNoiseLevle )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, EmTPReduNoise, em3DNoiseLevle )
    TYPESTRUCT_MEMBER( TTPMoonCamInfo, u32, dwZoomPos )
TYPESTRUCT_END(  TTPMoonCamInfo )

//TTPCamPre
TYPESTRUCT_BEGIN( TTPCamPre )
    TYPESTRUCT_MEMBER( TTPCamPre, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPCamPre, u8, byPre )
    TYPESTRUCT_MEMBER( TTPCamPre, BOOL, bIsUsed )
    TYPESTRUCT_MEMBER( TTPCamPre, s8, achachDescription )
TYPESTRUCT_END(  TTPCamPre )

//TTPPreParam
TYPESTRUCT_BEGIN( TTPPreParam )
    TYPESTRUCT_MEMBER( TTPPreParam, TTPCamPre, atPreParam )
TYPESTRUCT_END(  TTPPreParam )

//TTPOutModeInfo
TYPESTRUCT_BEGIN( TTPOutModeInfo )
    TYPESTRUCT_MEMBER( TTPOutModeInfo, EmTPMOONOutMode, emOutPortFormat )
    TYPESTRUCT_MEMBER( TTPOutModeInfo, EmTPSOrThShutter, emSOrThShutSpd )
    TYPESTRUCT_MEMBER( TTPOutModeInfo, EmTPFOrTwShutter, emFOrTwShutter )
TYPESTRUCT_END(  TTPOutModeInfo )

//TTPSnapshotInfo
TYPESTRUCT_BEGIN( TTPSnapshotInfo )
    TYPESTRUCT_MEMBER( TTPSnapshotInfo, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPSnapshotInfo, s8, achFileNme )
TYPESTRUCT_END(  TTPSnapshotInfo )

//TTPMosaicInfo
TYPESTRUCT_BEGIN( TTPMosaicInfo )
    TYPESTRUCT_MEMBER( TTPMosaicInfo, u16, m_wWidth )
    TYPESTRUCT_MEMBER( TTPMosaicInfo, u16, m_wHeight )
TYPESTRUCT_END(  TTPMosaicInfo )

//TMoonSerialInfo
TYPESTRUCT_BEGIN( TMoonSerialInfo )
    TYPESTRUCT_MEMBER( TMoonSerialInfo, u32, dwNo )
    TYPESTRUCT_MEMBER( TMoonSerialInfo, u32, dwType )
    TYPESTRUCT_MEMBER( TMoonSerialInfo, u32, dwUsage )
    TYPESTRUCT_MEMBER( TMoonSerialInfo, u32, dwFixBaudrate )
    TYPESTRUCT_MEMBER( TMoonSerialInfo, s8, achName )
TYPESTRUCT_END(  TMoonSerialInfo )

//TMoonVidStd
TYPESTRUCT_BEGIN( TMoonVidStd )
    TYPESTRUCT_MEMBER( TMoonVidStd, u32, dwWidth )
    TYPESTRUCT_MEMBER( TMoonVidStd, u32, dwHeight )
    TYPESTRUCT_MEMBER( TMoonVidStd, BOOL32, bProgressive )
    TYPESTRUCT_MEMBER( TMoonVidStd, u32, dwFrameRate )
    TYPESTRUCT_MEMBER( TMoonVidStd, u32, dwColorSpace )
TYPESTRUCT_END(  TMoonVidStd )

//TTPNsfParam
TYPESTRUCT_BEGIN( TTPNsfParam )
    TYPESTRUCT_MEMBER( TTPNsfParam, u32, dwNsfLevel )
    TYPESTRUCT_MEMBER( TTPNsfParam, u32, dwNsfType )
TYPESTRUCT_END(  TTPNsfParam )

//TTPDistortParam
TYPESTRUCT_BEGIN( TTPDistortParam )
    TYPESTRUCT_MEMBER( TTPDistortParam, u32, dwCorrectLevel )
    TYPESTRUCT_MEMBER( TTPDistortParam, u32, dwStretchRegion )
    TYPESTRUCT_MEMBER( TTPDistortParam, u32, dwEnable )
TYPESTRUCT_END(  TTPDistortParam )

//TMOONProduceTestMsg
TYPESTRUCT_BEGIN( TMOONProduceTestMsg )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, u16, m_wVersionNum )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, EmMOONProductTestType, m_emProduceTestType )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, BOOL, m_bProduceTestStart )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, BOOL, m_bProduceTestReult )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, u16, m_byErrorReason )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, u32_ip, m_adwLocalIp )
    TYPESTRUCT_MEMBER( TMOONProduceTestMsg, u32_ip, m_adwDstIp )
TYPESTRUCT_END(  TMOONProduceTestMsg )

//TTPMoonRectRegion
TYPESTRUCT_BEGIN( TTPMoonRectRegion )
    TYPESTRUCT_MEMBER( TTPMoonRectRegion, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPMoonRectRegion, u32, dwXCoordinate )
    TYPESTRUCT_MEMBER( TTPMoonRectRegion, u32, dwYCoordinate )
    TYPESTRUCT_MEMBER( TTPMoonRectRegion, u32, dwLenth )
    TYPESTRUCT_MEMBER( TTPMoonRectRegion, u32, dwWidth )
TYPESTRUCT_END(  TTPMoonRectRegion )

//TTPColorRGBCoeff
TYPESTRUCT_BEGIN( TTPColorRGBCoeff )
    TYPESTRUCT_MEMBER( TTPColorRGBCoeff, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPColorRGBCoeff, EmTPColorConsistency, emColorType )
    TYPESTRUCT_MEMBER( TTPColorRGBCoeff, u32, dwValue )
TYPESTRUCT_END(  TTPColorRGBCoeff )

//TTPDistortInfo
TYPESTRUCT_BEGIN( TTPDistortInfo )
    TYPESTRUCT_MEMBER( TTPDistortInfo, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPDistortInfo, EmTPDistortPosition, emDistortType )
    TYPESTRUCT_MEMBER( TTPDistortInfo, u32, dwValue )
TYPESTRUCT_END(  TTPDistortInfo )

//TMoonRectRGB
TYPESTRUCT_BEGIN( TMoonRectRGB )
    TYPESTRUCT_MEMBER( TMoonRectRGB, u8, byIndex )
    TYPESTRUCT_MEMBER( TMoonRectRGB, u32, dwRed )
    TYPESTRUCT_MEMBER( TMoonRectRGB, u32, dwGreen )
    TYPESTRUCT_MEMBER( TMoonRectRGB, u32, dwBlue )
TYPESTRUCT_END(  TMoonRectRGB )

//TTPColorCoeff
TYPESTRUCT_BEGIN( TTPColorCoeff )
    TYPESTRUCT_MEMBER( TTPColorCoeff, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPColorCoeff, u32, dwRed )
    TYPESTRUCT_MEMBER( TTPColorCoeff, u32, dwGreen )
    TYPESTRUCT_MEMBER( TTPColorCoeff, u32, dwBlue )
TYPESTRUCT_END(  TTPColorCoeff )

//TTPDistortPoint
TYPESTRUCT_BEGIN( TTPDistortPoint )
    TYPESTRUCT_MEMBER( TTPDistortPoint, u32, dwX )
    TYPESTRUCT_MEMBER( TTPDistortPoint, u32, dwY )
TYPESTRUCT_END(  TTPDistortPoint )

//TTPDistortRoate
TYPESTRUCT_BEGIN( TTPDistortRoate )
    TYPESTRUCT_MEMBER( TTPDistortRoate, u32, dwRoateAngle )
    TYPESTRUCT_MEMBER( TTPDistortRoate, u32, dwEnable )
    TYPESTRUCT_MEMBER( TTPDistortRoate, u32, dwDirection )
TYPESTRUCT_END(  TTPDistortRoate )

//TTPDistortCorrectInfo
TYPESTRUCT_BEGIN( TTPDistortCorrectInfo )
    TYPESTRUCT_MEMBER( TTPDistortCorrectInfo, u32, dwWidth )
    TYPESTRUCT_MEMBER( TTPDistortCorrectInfo, u32, dwHeight )
    TYPESTRUCT_MEMBER( TTPDistortCorrectInfo, u32, dwEnable )
    TYPESTRUCT_MEMBER( TTPDistortCorrectInfo, TTPDistortPoint, tDistortPoint )
    TYPESTRUCT_MEMBER( TTPDistortCorrectInfo, TTPDistortRoate, tDistortRoate )
TYPESTRUCT_END(  TTPDistortCorrectInfo )

//TTPAllDistortParam
TYPESTRUCT_BEGIN( TTPAllDistortParam )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwUperLeftHorizon )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwUperLeftVertical )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwUperRightHorizon )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwUperRightVertical )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwLowerRightHorizon )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwLowerRightVertical )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwLowerLeftHorizon )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwLowerLeftVertical )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwLeftSide )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwRightSide )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwTopSide )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwBottomSide )
    TYPESTRUCT_MEMBER( TTPAllDistortParam, u32, dwCenterRotate )
TYPESTRUCT_END(  TTPAllDistortParam )

//TTPSecBoundaryInfo
TYPESTRUCT_BEGIN( TTPSecBoundaryInfo )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, TTPColorCoeff, tColorCoeff )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, TTPMoonRectRegion, tRectRegion )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, TTPAllDistortParam, tAllDistortParam )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, BOOL, bShowRectSwich )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, BOOL, bDistortSwich )
    TYPESTRUCT_MEMBER( TTPSecBoundaryInfo, BOOL, bColorSwitch )
TYPESTRUCT_END(  TTPSecBoundaryInfo )

//TTPPreCamInfo
TYPESTRUCT_BEGIN( TTPPreCamInfo )
    TYPESTRUCT_MEMBER( TTPPreCamInfo, TTPMoonCamInfo, atPreCamInfo )
    TYPESTRUCT_MEMBER( TTPPreCamInfo, TTPColorCoeff, atColorCoeff )
    TYPESTRUCT_MEMBER( TTPPreCamInfo, TTPAllDistortParam, atAllDistortParam )
TYPESTRUCT_END(  TTPPreCamInfo )

//TTPRectCoord
TYPESTRUCT_BEGIN( TTPRectCoord )
    TYPESTRUCT_MEMBER( TTPRectCoord, u32, dwPosX )
    TYPESTRUCT_MEMBER( TTPRectCoord, u32, dwPosY )
    TYPESTRUCT_MEMBER( TTPRectCoord, u32, dwWidth )
    TYPESTRUCT_MEMBER( TTPRectCoord, u32, dwHeight )
    TYPESTRUCT_MEMBER( TTPRectCoord, u32, dwEnable )
TYPESTRUCT_END(  TTPRectCoord )

//TTPColorEn
TYPESTRUCT_BEGIN( TTPColorEn )
    TYPESTRUCT_MEMBER( TTPColorEn, u32, dwindex )
    TYPESTRUCT_MEMBER( TTPColorEn, u32, dwenable )
TYPESTRUCT_END(  TTPColorEn )

//TTPMechVer
TYPESTRUCT_BEGIN( TTPMechVer )
    TYPESTRUCT_MEMBER( TTPMechVer, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPMechVer, s8, achMechHWVer )
    TYPESTRUCT_MEMBER( TTPMechVer, s8, achMechSWVer )
TYPESTRUCT_END(  TTPMechVer )

//TTPFpgaDelay
TYPESTRUCT_BEGIN( TTPFpgaDelay )
    TYPESTRUCT_MEMBER( TTPFpgaDelay, u8, byIndex )
    TYPESTRUCT_MEMBER( TTPFpgaDelay, u32, dwDelay )
TYPESTRUCT_END(  TTPFpgaDelay )

//通讯数据结构编码表
TXDATAINFO* g_tTpStructData[]={
	(TXDATAINFO*)TTPFTPFileInfomembertable,
	(TXDATAINFO*)TTPDevmembertable,
	(TXDATAINFO*)TTPDevVerInfomembertable,
	(TXDATAINFO*)TTPLocalVerInfomembertable,
	(TXDATAINFO*)TTPLocalDevVerInfomembertable,
	(TXDATAINFO*)TTPTPadVerInfomembertable,
	(TXDATAINFO*)TH323Cfgmembertable,
	(TXDATAINFO*)TGuideCfgmembertable,
	(TXDATAINFO*)TSymboPointmembertable,
	(TXDATAINFO*)TOsdCfgmembertable,
	(TXDATAINFO*)TMtKdvTimemembertable,
	(TXDATAINFO*)TUserCfgmembertable,
	(TXDATAINFO*)TVgaOutCfgmembertable,
	(TXDATAINFO*)TMtEquipmentCapsetmembertable,
	(TXDATAINFO*)TInnerMcCfgmembertable,
	(TXDATAINFO*)TEthnetInfomembertable,
	(TXDATAINFO*)TE1Unitmembertable,
	(TXDATAINFO*)TE1Configmembertable,
	(TXDATAINFO*)TSerialCfgmembertable,
	(TXDATAINFO*)TRouteCfgmembertable,
	(TXDATAINFO*)TPPPOECfgmembertable,
	(TXDATAINFO*)TPPPoEStatesmembertable,
	(TXDATAINFO*)TPPPoEAuthFailedmembertable,
	(TXDATAINFO*)TPPPoEConnNotifymembertable,
	(TXDATAINFO*)TPPPoENoServermembertable,
	(TXDATAINFO*)TSNMPCfgmembertable,
	(TXDATAINFO*)TIPQoSmembertable,
	(TXDATAINFO*)TStreamMediamembertable,
	(TXDATAINFO*)TVideoParammembertable,
	(TXDATAINFO*)TAVPriorStrategymembertable,
	(TXDATAINFO*)TLostPackResendmembertable,
	(TXDATAINFO*)TCameraTypeInfomembertable,
	(TXDATAINFO*)TCameraCfgmembertable,
	(TXDATAINFO*)TVideoStandardmembertable,
	(TXDATAINFO*)TVideoSourcemembertable,
	(TXDATAINFO*)TSnapInfomembertable,
	(TXDATAINFO*)TBannerInfomembertable,
	(TXDATAINFO*)TMtIdmembertable,
	(TXDATAINFO*)TConfBaseInfomembertable,
	(TXDATAINFO*)TConfListInfomembertable,
	(TXDATAINFO*)TMtInfomembertable,
	(TXDATAINFO*)TMtVideoCodecStatusmembertable,
	(TXDATAINFO*)TTerStatusmembertable,
	(TXDATAINFO*)TMtMixParammembertable,
	(TXDATAINFO*)TMtVmpItemmembertable,
	(TXDATAINFO*)TMtVMPParammembertable,
	(TXDATAINFO*)TMtPollInfomembertable,
	(TXDATAINFO*)TMtPollSchemeNameSetmembertable,
	(TXDATAINFO*)TMtViewPollInfomembertable,
	(TXDATAINFO*)TMtSimpConfInfomembertable,
	(TXDATAINFO*)TMtConfInfomembertable,
	(TXDATAINFO*)TIPTransAddrmembertable,
	(TXDATAINFO*)TMtAddrmembertable,
	(TXDATAINFO*)TConfIdmembertable,
	(TXDATAINFO*)TDialParammembertable,
	(TXDATAINFO*)TLinkStatemembertable,
	(TXDATAINFO*)TEmbedFwNatProxymembertable,
	(TXDATAINFO*)TNATMapAddrmembertable,
	(TXDATAINFO*)TSipRegistrarCfgmembertable,
	(TXDATAINFO*)TGKCfgmembertable,
	(TXDATAINFO*)TInnerGKCfgmembertable,
	(TXDATAINFO*)TInnerProxyCfgmembertable,
	(TXDATAINFO*)TWiFiNetCfgmembertable,
	(TXDATAINFO*)TMonitorServicemembertable,
	(TXDATAINFO*)TRectmembertable,
	(TXDATAINFO*)TDualRationmembertable,
	(TXDATAINFO*)TImageAdjustParammembertable,
	(TXDATAINFO*)TVideoEncodeParametermembertable,
	(TXDATAINFO*)TEncryptKeymembertable,
	(TXDATAINFO*)TVideoChanParammembertable,
	(TXDATAINFO*)TAudioChanParammembertable,
	(TXDATAINFO*)TVODUserInfomembertable,
	(TXDATAINFO*)TVODFilemembertable,
	(TXDATAINFO*)TE1Groupmembertable,
	(TXDATAINFO*)TVideoSourceInfomembertable,
	(TXDATAINFO*)TExternalMatrixInfomembertable,
	(TXDATAINFO*)TAVInnerMatrixSchememembertable,
	(TXDATAINFO*)TBitRateAdjustmembertable,
	(TXDATAINFO*)TCodecPackStatmembertable,
	(TXDATAINFO*)TVideoStatisticsmembertable,
	(TXDATAINFO*)TAudioStatisticsmembertable,
	(TXDATAINFO*)TCapTypemembertable,
	(TXDATAINFO*)TCallInfoStatisticsmembertable,
	(TXDATAINFO*)TDualStreamBoxInfomembertable,
	(TXDATAINFO*)TFileTransfermembertable,
	(TXDATAINFO*)TDVBNetSessionmembertable,
	(TXDATAINFO*)TDVBNetSndParammembertable,
	(TXDATAINFO*)TDVBLocalNetParammembertable,
	(TXDATAINFO*)TDVBVideoEncParammembertable,
	(TXDATAINFO*)TSitecallInformationmembertable,
	(TXDATAINFO*)TTransparentSerialmembertable,
	(TXDATAINFO*)TPeerCapabilityInfomembertable,
	(TXDATAINFO*)TRapidKeymembertable,
	(TXDATAINFO*)TVerFileInfomembertable,
	(TXDATAINFO*)TVerInfomembertable,
	(TXDATAINFO*)TFecInfomembertable,
	(TXDATAINFO*)TVInnerMatrixSchememembertable,
	(TXDATAINFO*)TAddrEntrymembertable,
	(TXDATAINFO*)TPxyIPCfgmembertable,
	(TXDATAINFO*)TWifiLinkInfomembertable,
	(TXDATAINFO*)TWifiScanResultmembertable,
	(TXDATAINFO*)TWifiLinkCfgItemmembertable,
	(TXDATAINFO*)TWiFiBSSIDInfomembertable,
	(TXDATAINFO*)TWiFiBSSIDCfgmembertable,
	(TXDATAINFO*)TGkRegInfomembertable,
	(TXDATAINFO*)TSipRegResultmembertable,
	(TXDATAINFO*)THdAudioPortmembertable,
	(TXDATAINFO*)TMiscCfgmembertable,
	(TXDATAINFO*)TVideoDisplayFrmmembertable,
	(TXDATAINFO*)TDownLoadParamembertable,
	(TXDATAINFO*)TSecurePwdmembertable,
	(TXDATAINFO*)TMtBackBGDColormembertable,
	(TXDATAINFO*)TSipCfgmembertable,
	(TXDATAINFO*)TMtAddBannerParammembertable,
	(TXDATAINFO*)TMtBmpInfomembertable,
	(TXDATAINFO*)TMtFullBannerParammembertable,
	(TXDATAINFO*)TMTBmpInfomembertable,
	(TXDATAINFO*)TMTAddLogoParammembertable,
	(TXDATAINFO*)TMTFullLogoParammembertable,
	(TXDATAINFO*)TMtcBoxCallCfgmembertable,
	(TXDATAINFO*)TMTRSParammembertable,
	(TXDATAINFO*)TMtRecStartParammembertable,
	(TXDATAINFO*)TMtRecRegParammembertable,
	(TXDATAINFO*)TMtRecParammembertable,
	(TXDATAINFO*)TMtCnsParammembertable,
	(TXDATAINFO*)TLoginRetmembertable,
	(TXDATAINFO*)TTPTransAddrmembertable,
	(TXDATAINFO*)TTPNamemembertable,
	(TXDATAINFO*)TTPAliasmembertable,
	(TXDATAINFO*)TTpEncryptKeymembertable,
	(TXDATAINFO*)TTPMediaTransAddrmembertable,
	(TXDATAINFO*)TTPVideoCapmembertable,
	(TXDATAINFO*)TTPAudCapmembertable,
	(TXDATAINFO*)TUmsVidFormatmembertable,
	(TXDATAINFO*)TUmsRSParammembertable,
	(TXDATAINFO*)TEpAddrmembertable,
	(TXDATAINFO*)TAuxMixListmembertable,
	(TXDATAINFO*)TConfAuxMixInfomembertable,
	(TXDATAINFO*)TTPPollInfomembertable,
	(TXDATAINFO*)TTPConfBaseInfomembertable,
	(TXDATAINFO*)TUmsConfBasemembertable,
	(TXDATAINFO*)TChairConfInfomembertable,
	(TXDATAINFO*)TEpAddrListmembertable,
	(TXDATAINFO*)TConfTurnListmembertable,
	(TXDATAINFO*)TTPConfTemplatemembertable,
	(TXDATAINFO*)TOprConfTmpResultmembertable,
	(TXDATAINFO*)TDelRefreshConfTemplatemembertable,
	(TXDATAINFO*)TConfEpIDmembertable,
	(TXDATAINFO*)TConfEpIDInfomembertable,
	(TXDATAINFO*)TConfCallEpAddrmembertable,
	(TXDATAINFO*)TCnsInfomembertable,
	(TXDATAINFO*)TTPConfInfomembertable,
	(TXDATAINFO*)TAddConfListmembertable,
	(TXDATAINFO*)TDelConfListmembertable,
	(TXDATAINFO*)TStartConfResultmembertable,
	(TXDATAINFO*)TConfCnsInfomembertable,
	(TXDATAINFO*)TConfTurnInfomembertable,
	(TXDATAINFO*)TApplaySpeakRetmembertable,
	(TXDATAINFO*)TUmsConfStatusmembertable,
	(TXDATAINFO*)TTPUmsReasonIndmembertable,
	(TXDATAINFO*)TTPMtVideoEncodeParametermembertable,
	(TXDATAINFO*)TTpCodecComponentmembertable,
	(TXDATAINFO*)TTPCnMediaTransPortmembertable,
	(TXDATAINFO*)TMtMPAddrmembertable,
	(TXDATAINFO*)TMtMPParammembertable,
	(TXDATAINFO*)TMtTPEpParammembertable,
	(TXDATAINFO*)TMtVDecParammembertable,
	(TXDATAINFO*)TMtVEncParammembertable,
	(TXDATAINFO*)TCnVideoParammembertable,
	(TXDATAINFO*)TEpIdmembertable,
	(TXDATAINFO*)TTPRegNamemembertable,
	(TXDATAINFO*)TTPRegNameRepeatInfomembertable,
	(TXDATAINFO*)TTPSipRegistrarCfgmembertable,
	(TXDATAINFO*)TTPGkRegistrarCfgmembertable,
	(TXDATAINFO*)TTPGKCfgmembertable,
	(TXDATAINFO*)TTPSipRegPackInfomembertable,
	(TXDATAINFO*)TTPSipRegInfomembertable,
	(TXDATAINFO*)TTPSipPackmembertable,
	(TXDATAINFO*)TTPAddrNtyUsermembertable,
	(TXDATAINFO*)TUCSipRegResultmembertable,
	(TXDATAINFO*)TCnAddrmembertable,
	(TXDATAINFO*)TTPDialParammembertable,
	(TXDATAINFO*)TTPCnsInfomembertable,
	(TXDATAINFO*)TTPTimemembertable,
	(TXDATAINFO*)TTPCnsConfStatusmembertable,
	(TXDATAINFO*)TTPDualInfomembertable,
	(TXDATAINFO*)TTPDualRequestmembertable,
	(TXDATAINFO*)TTPDualInfoAckmembertable,
	(TXDATAINFO*)TTPAudioInfomembertable,
	(TXDATAINFO*)TTPHduRegInfomembertable,
	(TXDATAINFO*)TTPHduPlayReqmembertable,
	(TXDATAINFO*)TTPCnLoginfomembertable,
	(TXDATAINFO*)TTPCnmembertable,
	(TXDATAINFO*)TTPCnListmembertable,
	(TXDATAINFO*)TAudMixStatmembertable,
	(TXDATAINFO*)TTPDisScreenStatmembertable,
	(TXDATAINFO*)TTPGetRegInfomembertable,
	(TXDATAINFO*)TTPAacCapmembertable,
	(TXDATAINFO*)TTPG7221Capmembertable,
	(TXDATAINFO*)TTPMediaStreammembertable,
	(TXDATAINFO*)TTPCapMapmembertable,
	(TXDATAINFO*)TTPCapPackmembertable,
	(TXDATAINFO*)TTPCnStreammembertable,
	(TXDATAINFO*)TTPCnUnpackStreammembertable,
	(TXDATAINFO*)TTPDualCapmembertable,
	(TXDATAINFO*)TCnsCapsetmembertable,
	(TXDATAINFO*)TTPYouAreSeeingmembertable,
	(TXDATAINFO*)TTPTerLabelmembertable,
	(TXDATAINFO*)TPModuleTerminalInfomembertable,
	(TXDATAINFO*)TTPPollDstNamemembertable,
	(TXDATAINFO*)TMtADecParammembertable,
	(TXDATAINFO*)TMtAEncParammembertable,
	(TXDATAINFO*)TTPChanSelecteCascadResmembertable,
	(TXDATAINFO*)TTPChanSelecteCascadCancelResmembertable,
	(TXDATAINFO*)TTerminalLabelmembertable,
	(TXDATAINFO*)TTPDisListOprmembertable,
	(TXDATAINFO*)TTPRegistReqmembertable,
	(TXDATAINFO*)TCnsAVCapsetmembertable,
	(TXDATAINFO*)TCnsAddrCapsetmembertable,
	(TXDATAINFO*)TVgaInfomembertable,
	(TXDATAINFO*)TTPNatCfgmembertable,
	(TXDATAINFO*)TUmsVersionmembertable,
	(TXDATAINFO*)TToolSysInfomembertable,
	(TXDATAINFO*)THduChanInfomembertable,
	(TXDATAINFO*)THduInfomembertable,
	(TXDATAINFO*)THduCfgmembertable,
	(TXDATAINFO*)THduStyleUnitmembertable,
	(TXDATAINFO*)THduStyleDatamembertable,
	(TXDATAINFO*)THduPlanUnitmembertable,
	(TXDATAINFO*)THduPlanDatamembertable,
	(TXDATAINFO*)THduStyleInfomembertable,
	(TXDATAINFO*)TTPNMServerCfgmembertable,
	(TXDATAINFO*)TTPSysInfomembertable,
	(TXDATAINFO*)TTPTPadListmembertable,
	(TXDATAINFO*)TTPSingleAudioPortCfgmembertable,
	(TXDATAINFO*)TTpAudioPortInfomembertable,
	(TXDATAINFO*)TTPVideoPortInfomembertable,
	(TXDATAINFO*)TTPVideoDiagInfomembertable,
	(TXDATAINFO*)TTPAudioDiagInfomembertable,
	(TXDATAINFO*)TTPUpDownNetSpeedInfomembertable,
	(TXDATAINFO*)TTPUpDownSpeedInfomembertable,
	(TXDATAINFO*)TTPVgaMixInfomembertable,
	(TXDATAINFO*)TCnCameraCfgmembertable,
	(TXDATAINFO*)TCentreTVCfgmembertable,
	(TXDATAINFO*)TTVActmembertable,
	(TXDATAINFO*)TCenDevSleepInfomembertable,
	(TXDATAINFO*)TCentreCurNamemembertable,
	(TXDATAINFO*)TCentreDCamCfgmembertable,
	(TXDATAINFO*)TCentreSchCfgmembertable,
	(TXDATAINFO*)TCentreACCfgmembertable,
	(TXDATAINFO*)TOprBoardResultmembertable,
	(TXDATAINFO*)TTPBrdPosmembertable,
	(TXDATAINFO*)TTPBrdCfgmembertable,
	(TXDATAINFO*)TTPEqpCfgmembertable,
	(TXDATAINFO*)TTPMdlCfgmembertable,
	(TXDATAINFO*)TTPBrdInfomembertable,
	(TXDATAINFO*)TTPBrdMdlInfomembertable,
	(TXDATAINFO*)TTPBrdUsedInfomembertable,
	(TXDATAINFO*)TTPBrdUpGrademembertable,
	(TXDATAINFO*)TTPAudPowermembertable,
	(TXDATAINFO*)TTPHdAudioPortmembertable,
	(TXDATAINFO*)TTPHdAudioOutPortmembertable,
	(TXDATAINFO*)TTPHdDualAudioPortmembertable,
	(TXDATAINFO*)TTPMPAudioInfomembertable,
	(TXDATAINFO*)TTPVideoDisplayFrmmembertable,
	(TXDATAINFO*)TTPVideoParammembertable,
	(TXDATAINFO*)TTPImageAdjustParammembertable,
	(TXDATAINFO*)TTPVideoInfomembertable,
	(TXDATAINFO*)TTPSymboPointmembertable,
	(TXDATAINFO*)TTPVgaOutCfgmembertable,
	(TXDATAINFO*)TTPFecInfomembertable,
	(TXDATAINFO*)TTPLostPackResendmembertable,
	(TXDATAINFO*)TTPBitRateAdjustmembertable,
	(TXDATAINFO*)TTPVideoStandardmembertable,
	(TXDATAINFO*)TTPVideoPortmembertable,
	(TXDATAINFO*)TTPAutoTestMsgmembertable,
	(TXDATAINFO*)TTPEqualizermembertable,
	(TXDATAINFO*)TTPPIPModmembertable,
	(TXDATAINFO*)TTPLostFrameRatemembertable,
	(TXDATAINFO*)TTPVideoRecvmembertable,
	(TXDATAINFO*)TTPVideoEncDecResmembertable,
	(TXDATAINFO*)TTPVideoEncDecResPackmembertable,
	(TXDATAINFO*)TTPVideoFrameRatemembertable,
	(TXDATAINFO*)TTPVideoFrameRatePackmembertable,
	(TXDATAINFO*)TTPCodecPackStatmembertable,
	(TXDATAINFO*)TTPCnDsDatamembertable,
	(TXDATAINFO*)TTPCnNetBufParamembertable,
	(TXDATAINFO*)TTPCnRSParammembertable,
	(TXDATAINFO*)TTPAllConfCnsInfomembertable,
	(TXDATAINFO*)TCnDsTypemembertable,
	(TXDATAINFO*)TTPCnMixAddrmembertable,
	(TXDATAINFO*)TTPCnMixChanmembertable,
	(TXDATAINFO*)TTPCnMixParammembertable,
	(TXDATAINFO*)TTPNetAddressmembertable,
	(TXDATAINFO*)TTPMixerChannelParammembertable,
	(TXDATAINFO*)TTPCallSerInfomembertable,
	(TXDATAINFO*)TTPVidSrcCutLinesmembertable,
	(TXDATAINFO*)TVcrCfgmembertable,
	(TXDATAINFO*)TAdjustFrameRatemembertable,
	(TXDATAINFO*)TAdjustVidResmembertable,
	(TXDATAINFO*)TTPVGAInfomembertable,
	(TXDATAINFO*)TTPBmpInfomembertable,
	(TXDATAINFO*)TTPAddLogoPosmembertable,
	(TXDATAINFO*)TTPTranspDColormembertable,
	(TXDATAINFO*)TTPAddLogoParammembertable,
	(TXDATAINFO*)TTPFullLogoParammembertable,
	(TXDATAINFO*)TCnProduceTestMsgmembertable,
	(TXDATAINFO*)TRecBaseInfomembertable,
	(TXDATAINFO*)TRecFileListInfomembertable,
	(TXDATAINFO*)TRecFileInfomembertable,
	(TXDATAINFO*)TRecorderConfInfomembertable,
	(TXDATAINFO*)TRecorderMTInfomembertable,
	(TXDATAINFO*)TRecConfInfomembertable,
	(TXDATAINFO*)TConRecStatemembertable,
	(TXDATAINFO*)TRecConfResmembertable,
	(TXDATAINFO*)TRecPlayInfomembertable,
	(TXDATAINFO*)TPlayStatusMdyInfomembertable,
	(TXDATAINFO*)TConfPlayStatusmembertable,
	(TXDATAINFO*)TTPUpgradeSermembertable,
	(TXDATAINFO*)TTPSnapInfomembertable,
	(TXDATAINFO*)TTPSingleLoopInfomembertable,
	(TXDATAINFO*)TTPAllLoopInfomembertable,
	(TXDATAINFO*)TTPMtTerminalmembertable,
	(TXDATAINFO*)TTPMtOnLineListmembertable,
	(TXDATAINFO*)TTPMtRegInfomembertable,
	(TXDATAINFO*)TTPMcuRegInfomembertable,
	(TXDATAINFO*)TRegPackInfoExmembertable,
	(TXDATAINFO*)TUmsRegInfoExmembertable,
	(TXDATAINFO*)TUmsRegPackExmembertable,
	(TXDATAINFO*)TCnsRegInfoExmembertable,
	(TXDATAINFO*)TCnsRegPackExmembertable,
	(TXDATAINFO*)TTPAudPlayModemembertable,
	(TXDATAINFO*)TTPSmallPicRectInfomembertable,
	(TXDATAINFO*)TTPRecMtFormatmembertable,
	(TXDATAINFO*)TTPRebootTimemembertable,
	(TXDATAINFO*)TTPVidForamtmembertable,
	(TXDATAINFO*)TTPVidOffsetParammembertable,
	(TXDATAINFO*)TTPAllVidOffsetParammembertable,
	(TXDATAINFO*)TTPCnConfInfomembertable,
	(TXDATAINFO*)TTPDisplayTypemembertable,
	(TXDATAINFO*)TChairSingleStreenInfomembertable,
	(TXDATAINFO*)TChanViewResmembertable,
	(TXDATAINFO*)TChairStreenInfomembertable,
	(TXDATAINFO*)TTPEthnetInfomembertable,
	(TXDATAINFO*)TTPMoonCamInfomembertable,
	(TXDATAINFO*)TTPCamPremembertable,
	(TXDATAINFO*)TTPPreParammembertable,
	(TXDATAINFO*)TTPOutModeInfomembertable,
	(TXDATAINFO*)TTPSnapshotInfomembertable,
	(TXDATAINFO*)TTPMosaicInfomembertable,
	(TXDATAINFO*)TMoonSerialInfomembertable,
	(TXDATAINFO*)TMoonVidStdmembertable,
	(TXDATAINFO*)TTPNsfParammembertable,
	(TXDATAINFO*)TTPDistortParammembertable,
	(TXDATAINFO*)TMOONProduceTestMsgmembertable,
	(TXDATAINFO*)TTPMoonRectRegionmembertable,
	(TXDATAINFO*)TTPColorRGBCoeffmembertable,
	(TXDATAINFO*)TTPDistortInfomembertable,
	(TXDATAINFO*)TMoonRectRGBmembertable,
	(TXDATAINFO*)TTPColorCoeffmembertable,
	(TXDATAINFO*)TTPDistortPointmembertable,
	(TXDATAINFO*)TTPDistortRoatemembertable,
	(TXDATAINFO*)TTPDistortCorrectInfomembertable,
	(TXDATAINFO*)TTPAllDistortParammembertable,
	(TXDATAINFO*)TTPSecBoundaryInfomembertable,
	(TXDATAINFO*)TTPPreCamInfomembertable,
	(TXDATAINFO*)TTPRectCoordmembertable,
	(TXDATAINFO*)TTPColorEnmembertable,
	(TXDATAINFO*)TTPMechVermembertable,
	(TXDATAINFO*)TTPFpgaDelaymembertable,
	(TXDATAINFO*)NULL
};

const TXENUMINFO enumEmTPDevRegUpdateSerDescript[]={
	{ "emDevInvalid", (int)emDevInvalid },
	{ "emTPTPad_Win7", (int)emTPTPad_Win7 },
	{ "emTPTPad_Android", (int)emTPTPad_Android },
	{ "emTPTPad_IOS", (int)emTPTPad_IOS },
	{ "emTPCns_T300A", (int)emTPCns_T300A },
	{ "emTPCns_T300B", (int)emTPCns_T300B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPUpdateTypeDescript[]={
	{ "emTPUpdateForced", (int)emTPUpdateForced },
	{ "emTPUpdateSelected", (int)emTPUpdateSelected },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiLinkStatDescript[]={
	{ "emWiFiIdle", (int)emWiFiIdle },
	{ "emWiFiConnecting", (int)emWiFiConnecting },
	{ "emWiFiConnectFailed", (int)emWiFiConnectFailed },
	{ "emWiFiConnected", (int)emWiFiConnected },
	{ "emWiFiDisconnecting", (int)emWiFiDisconnecting },
	{ "emWiFiDisconnected", (int)emWiFiDisconnected },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiSelTypeDescript[]={
	{ "emWiFiCfgSel", (int)emWiFiCfgSel },
	{ "emWiFiScanSel", (int)emWiFiScanSel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiNetTypeDescript[]={
	{ "emWiFiAdHoc", (int)emWiFiAdHoc },
	{ "emWiFiInfra", (int)emWiFiInfra },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiEncryptTypeDescript[]={
	{ "emWiFiEncryptNone", (int)emWiFiEncryptNone },
	{ "emWiFiEncryptWep", (int)emWiFiEncryptWep },
	{ "emWiFiEncryptWpa", (int)emWiFiEncryptWpa },
	{ "emWiFiEncryptWpa2", (int)emWiFiEncryptWpa2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWiFiEncryptArithmeticDescript[]={
	{ "emWiFiArithNone", (int)emWiFiArithNone },
	{ "emWiFiArithWep40", (int)emWiFiArithWep40 },
	{ "emWiFiArithTkip", (int)emWiFiArithTkip },
	{ "emWiFiArithWrap", (int)emWiFiArithWrap },
	{ "emWiFiArithAes", (int)emWiFiArithAes },
	{ "emWiFiArithWep104", (int)emWiFiArithWep104 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVODRejCodeDescript[]={
	{ "emVODNoReason", (int)emVODNoReason },
	{ "emVODFileNotFound", (int)emVODFileNotFound },
	{ "emVODPalyNotStarted", (int)emVODPalyNotStarted },
	{ "emVODMaxUser", (int)emVODMaxUser },
	{ "emVODUserNotExist", (int)emVODUserNotExist },
	{ "emVODUserLogined", (int)emVODUserLogined },
	{ "emVODInvalidedPassword", (int)emVODInvalidedPassword },
	{ "emVODMEDIAVODInvalidedFileNameType", (int)emVODMEDIAVODInvalidedFileNameType },
	{ "emVODPlayBusy", (int)emVODPlayBusy },
	{ "emConnectFailed", (int)emConnectFailed },
	{ "emDisconnect", (int)emDisconnect },
	{ "emVODNoError", (int)emVODNoError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVODStateDescript[]={
	{ "emVODIdle", (int)emVODIdle },
	{ "emVODLogin", (int)emVODLogin },
	{ "emVODFileListQuery", (int)emVODFileListQuery },
	{ "emVODFileInfoQuery", (int)emVODFileInfoQuery },
	{ "emVODPlay", (int)emVODPlay },
	{ "emVODPause", (int)emVODPause },
	{ "emVODStop", (int)emVODStop },
	{ "emVODSeek", (int)emVODSeek },
	{ "emVODActiveEnd", (int)emVODActiveEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTextAlignDescript[]={
	{ "emAlignLeft", (int)emAlignLeft },
	{ "emAlignCenter", (int)emAlignCenter },
	{ "emAlignRight", (int)emAlignRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollModeDescript[]={
	{ "emStatic", (int)emStatic },
	{ "emRight2Left", (int)emRight2Left },
	{ "emDown2Up", (int)emDown2Up },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRollSpeedDescript[]={
	{ "emSlower", (int)emSlower },
	{ "emSlow", (int)emSlow },
	{ "emNormal", (int)emNormal },
	{ "emFast", (int)emFast },
	{ "emFaster", (int)emFaster },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmStopBitsDescript[]={
	{ "em1StopBit", (int)em1StopBit },
	{ "em1HalfStopBits", (int)em1HalfStopBits },
	{ "em2StopBits", (int)em2StopBits },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmParityCheckDescript[]={
	{ "emNoCheck", (int)emNoCheck },
	{ "emOddCheck", (int)emOddCheck },
	{ "emEvenCheck", (int)emEvenCheck },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSerialTypeDescript[]={
	{ "emRS232", (int)emRS232 },
	{ "emRS422", (int)emRS422 },
	{ "emRS485", (int)emRS485 },
	{ "emSerialTcpip", (int)emSerialTcpip },
	{ "emRS422_1", (int)emRS422_1 },
	{ "emRS422_2", (int)emRS422_2 },
	{ "emRS422_3", (int)emRS422_3 },
	{ "emRSCom_1", (int)emRSCom_1 },
	{ "emRSCom_2", (int)emRSCom_2 },
	{ "emRSCom_3", (int)emRSCom_3 },
	{ "emRSCom_4", (int)emRSCom_4 },
	{ "emRSCom_5", (int)emRSCom_5 },
	{ "emRSCom_6", (int)emRSCom_6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLanguageDescript[]={
	{ "emEnglish", (int)emEnglish },
	{ "emChineseSB", (int)emChineseSB },
	{ "emLangeEnd", (int)emLangeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfProtocolDescript[]={
	{ "emH323", (int)emH323 },
	{ "emH320", (int)emH320 },
	{ "emSIP", (int)emSIP },
	{ "emSat", (int)emSat },
	{ "emInvalidConfProtocel", (int)emInvalidConfProtocel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmEncodeModeDescript[]={
	{ "emQualityFirst", (int)emQualityFirst },
	{ "emSpeedFirst", (int)emSpeedFirst },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLostPackageRestoreDescript[]={
	{ "emLPQualityFirst", (int)emLPQualityFirst },
	{ "emLPSpeedSlow", (int)emLPSpeedSlow },
	{ "emLPSpeedNormal", (int)emLPSpeedNormal },
	{ "emLPSpeedFast", (int)emLPSpeedFast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMatrixTypeDescript[]={
	{ "emMatrixInner", (int)emMatrixInner },
	{ "emMatrixOuter", (int)emMatrixOuter },
	{ "emMatrixVas", (int)emMatrixVas },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualVideoShowModeDescript[]={
	{ "emDualVideoOnSigleScreen", (int)emDualVideoOnSigleScreen },
	{ "emEachVideoOwnScreen", (int)emEachVideoOwnScreen },
	{ "emTripleVideoOnSingleScn", (int)emTripleVideoOnSingleScn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisplayRatioDescript[]={
	{ "emDR4to3", (int)emDR4to3 },
	{ "emDR16to9", (int)emDR16to9 },
	{ "emDRAuto", (int)emDRAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoTypeDescript[]={
	{ "emPriomVideo", (int)emPriomVideo },
	{ "emSecondVideo", (int)emSecondVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoStandardDescript[]={
	{ "emPAL", (int)emPAL },
	{ "emNTSC", (int)emNTSC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoInterfaceDescript[]={
	{ "emVGA", (int)emVGA },
	{ "emSVideo", (int)emSVideo },
	{ "emCVideo", (int)emCVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtVideoPortDescript[]={
	{ "emMtVGA", (int)emMtVGA },
	{ "emMtSVid", (int)emMtSVid },
	{ "emMtPC", (int)emMtPC },
	{ "emMtC1Vid", (int)emMtC1Vid },
	{ "emMtC2Vid", (int)emMtC2Vid },
	{ "emMtC3Vid", (int)emMtC3Vid },
	{ "emMtC4Vid", (int)emMtC4Vid },
	{ "emMtC5Vid", (int)emMtC5Vid },
	{ "emMtC6Vid", (int)emMtC6Vid },
	{ "emMtExternalVid", (int)emMtExternalVid },
	{ "emMtVideoMaxCount", (int)emMtVideoMaxCount },
	{ "emMtVidInvalid", (int)emMtVidInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTripModeDescript[]={
	{ "emTripModeAuto", (int)emTripModeAuto },
	{ "emTripModeManu", (int)emTripModeManu },
	{ "emTripModeNegative", (int)emTripModeNegative },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLabelTypeDescript[]={
	{ "emLabelAuto", (int)emLabelAuto },
	{ "emLabelUserDef", (int)emLabelUserDef },
	{ "emLabelOff", (int)emLabelOff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDLProtocolDescript[]={
	{ "emPPP", (int)emPPP },
	{ "emHDLC", (int)emHDLC },
	{ "emPPPOE", (int)emPPPOE },
	{ "emMP", (int)emMP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAuthenticationTypeDescript[]={
	{ "emPAP", (int)emPAP },
	{ "emCHAP", (int)emCHAP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFrameUnitTypeDescript[]={
	{ "emFrameSecond", (int)emFrameSecond },
	{ "emSecondFrame", (int)emSecondFrame },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMediaTypeDescript[]={
	{ "emMediaVideo", (int)emMediaVideo },
	{ "emMediaAudio", (int)emMediaAudio },
	{ "emMediaAV", (int)emMediaAV },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoFormatDescript[]={
	{ "emVH261", (int)emVH261 },
	{ "emVH262", (int)emVH262 },
	{ "emVH263", (int)emVH263 },
	{ "emVH263plus", (int)emVH263plus },
	{ "emVH264", (int)emVH264 },
	{ "emVMPEG4", (int)emVMPEG4 },
	{ "emVEnd", (int)emVEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAudioFormatDescript[]={
	{ "emAG711a", (int)emAG711a },
	{ "emAG711u", (int)emAG711u },
	{ "emAG722", (int)emAG722 },
	{ "emAG7231", (int)emAG7231 },
	{ "emAG728", (int)emAG728 },
	{ "emAG729", (int)emAG729 },
	{ "emAMP3", (int)emAMP3 },
	{ "emAG721", (int)emAG721 },
	{ "emAG7221", (int)emAG7221 },
	{ "emAG719", (int)emAG719 },
	{ "emAMpegAACLC", (int)emAMpegAACLC },
	{ "emAMpegAACLD", (int)emAMpegAACLD },
	{ "emAEnd", (int)emAEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVideoResolutionDescript[]={
	{ "emVResolutionAuto", (int)emVResolutionAuto },
	{ "emVSQCIF", (int)emVSQCIF },
	{ "emVQCIF", (int)emVQCIF },
	{ "emVCIF", (int)emVCIF },
	{ "emV2CIF", (int)emV2CIF },
	{ "emV4CIF", (int)emV4CIF },
	{ "emV16CIF", (int)emV16CIF },
	{ "emVHD480i720x480", (int)emVHD480i720x480 },
	{ "emVHD480p720x480", (int)emVHD480p720x480 },
	{ "emVHD576i720x576", (int)emVHD576i720x576 },
	{ "emVHD576p720x576", (int)emVHD576p720x576 },
	{ "emVHD720p1280x720", (int)emVHD720p1280x720 },
	{ "emVHD1080i1920x1080", (int)emVHD1080i1920x1080 },
	{ "emVHD1080p1920x1080", (int)emVHD1080p1920x1080 },
	{ "emVGA352x240", (int)emVGA352x240 },
	{ "emVGA704x480", (int)emVGA704x480 },
	{ "emVGA640x480", (int)emVGA640x480 },
	{ "emVGA800x600", (int)emVGA800x600 },
	{ "emVGA1024x768", (int)emVGA1024x768 },
	{ "emVGA1280x768", (int)emVGA1280x768 },
	{ "emVGA1280x800", (int)emVGA1280x800 },
	{ "emVGA1366x768", (int)emVGA1366x768 },
	{ "emVGA1280x854", (int)emVGA1280x854 },
	{ "emVGA1440x900", (int)emVGA1440x900 },
	{ "emVGA1280x1024", (int)emVGA1280x1024 },
	{ "emVGA1680x1050", (int)emVGA1680x1050 },
	{ "emVGA1600x1200", (int)emVGA1600x1200 },
	{ "emVGA1920x1200", (int)emVGA1920x1200 },
	{ "emVSQCIF112x96", (int)emVSQCIF112x96 },
	{ "emVSQCIF96x80", (int)emVSQCIF96x80 },
	{ "emV320x192", (int)emV320x192 },
	{ "emV432x240", (int)emV432x240 },
	{ "emV480x272", (int)emV480x272 },
	{ "emV640x368", (int)emV640x368 },
	{ "emV864x480", (int)emV864x480 },
	{ "emV960x544", (int)emV960x544 },
	{ "emV1440x816", (int)emV1440x816 },
	{ "emVResEnd", (int)emVResEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmQoSDescript[]={
	{ "emDiffServ", (int)emDiffServ },
	{ "emIPPrecedence", (int)emIPPrecedence },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTOSDescript[]={
	{ "emTOSNone", (int)emTOSNone },
	{ "emTOSMinCost", (int)emTOSMinCost },
	{ "emTOSMaxReliable", (int)emTOSMaxReliable },
	{ "emTOSMaxThruput", (int)emTOSMaxThruput },
	{ "emTOSMinDelay", (int)emTOSMinDelay },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSiteDescript[]={
	{ "emLocal", (int)emLocal },
	{ "emRemote", (int)emRemote },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmChanTypeDescript[]={
	{ "emChanSendAudio", (int)emChanSendAudio },
	{ "emChanSendPrimoVideo", (int)emChanSendPrimoVideo },
	{ "emChanSendSecondVideo", (int)emChanSendSecondVideo },
	{ "emChanSendFecc", (int)emChanSendFecc },
	{ "emChanSendT120", (int)emChanSendT120 },
	{ "emChanRecvAudio", (int)emChanRecvAudio },
	{ "emChanRecvPrimoVideo", (int)emChanRecvPrimoVideo },
	{ "emChanRecvSecondVideo", (int)emChanRecvSecondVideo },
	{ "emChanRecvFecc", (int)emChanRecvFecc },
	{ "emChanRecvT120", (int)emChanRecvT120 },
	{ "emChanTypeEnd", (int)emChanTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCodecComponentDescript[]={
	{ "emPriomVideoEncoder", (int)emPriomVideoEncoder },
	{ "emPriomVideoDecoder", (int)emPriomVideoDecoder },
	{ "emSecondVideoEncoder", (int)emSecondVideoEncoder },
	{ "emSecondVideoDecoder", (int)emSecondVideoDecoder },
	{ "emAudioEncoder", (int)emAudioEncoder },
	{ "emAudioDecoder", (int)emAudioDecoder },
	{ "emCodecComponentEnd", (int)emCodecComponentEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtModelDescript[]={
	{ "emUnknownMtModel", (int)emUnknownMtModel },
	{ "emPCMT", (int)emPCMT },
	{ "em8010", (int)em8010 },
	{ "em8010A", (int)em8010A },
	{ "em8010Aplus", (int)em8010Aplus },
	{ "em8010C", (int)em8010C },
	{ "em8010C1", (int)em8010C1 },
	{ "emIMT", (int)emIMT },
	{ "em8220A", (int)em8220A },
	{ "em8220B", (int)em8220B },
	{ "em8220C", (int)em8220C },
	{ "em8620A", (int)em8620A },
	{ "emTS6610E", (int)emTS6610E },
	{ "emTS6210", (int)emTS6210 },
	{ "em8010A_2", (int)em8010A_2 },
	{ "em8010A_4", (int)em8010A_4 },
	{ "em8010A_8", (int)em8010A_8 },
	{ "em7210", (int)em7210 },
	{ "em7610", (int)em7610 },
	{ "emTS5610", (int)emTS5610 },
	{ "emTS6610", (int)emTS6610 },
	{ "em7810", (int)em7810 },
	{ "em7910", (int)em7910 },
	{ "em7620_A", (int)em7620_A },
	{ "em7620_B", (int)em7620_B },
	{ "em7820_A", (int)em7820_A },
	{ "em7820_B", (int)em7820_B },
	{ "em7920_A", (int)em7920_A },
	{ "em7920_B", (int)em7920_B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFileSysDescript[]={
	{ "emRAWFS", (int)emRAWFS },
	{ "emTFFS", (int)emTFFS },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmEncryptArithmeticDescript[]={
	{ "emEncryptNone", (int)emEncryptNone },
	{ "emDES", (int)emDES },
	{ "emAES", (int)emAES },
	{ "emEncryptAuto", (int)emEncryptAuto },
	{ "emEncryptEnd", (int)emEncryptEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmActionDescript[]={
	{ "emActStart", (int)emActStart },
	{ "emActStop", (int)emActStop },
	{ "emActPause", (int)emActPause },
	{ "emActResume", (int)emActResume },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmOptRetDescript[]={
	{ "emEnable", (int)emEnable },
	{ "emDisable", (int)emDisable },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfModeDescript[]={
	{ "emP2PConf", (int)emP2PConf },
	{ "emMCCConf", (int)emMCCConf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtAddrTypeDescript[]={
	{ "emIPAddr", (int)emIPAddr },
	{ "emE164", (int)emE164 },
	{ "emH323id", (int)emH323id },
	{ "emDialNum", (int)emDialNum },
	{ "emSipAddr", (int)emSipAddr },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallModeDescript[]={
	{ "emJoin", (int)emJoin },
	{ "emCreate", (int)emCreate },
	{ "emInvite", (int)emInvite },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDirectionDescript[]={
	{ "emUP", (int)emUP },
	{ "emDown", (int)emDown },
	{ "emLeft", (int)emLeft },
	{ "emRight", (int)emRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallStateDescript[]={
	{ "emCS_Idle", (int)emCS_Idle },
	{ "emCS_Calling", (int)emCS_Calling },
	{ "emCS_P2P", (int)emCS_P2P },
	{ "emCS_MCC", (int)emCS_MCC },
	{ "emCS_Hanup", (int)emCS_Hanup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallSiteStateDescript[]={
	{ "emCSS_IDLE", (int)emCSS_IDLE },
	{ "emCSS_Init", (int)emCSS_Init },
	{ "emCSS_Waiting", (int)emCSS_Waiting },
	{ "emCSS_Connected", (int)emCSS_Connected },
	{ "emCSS_Failed", (int)emCSS_Failed },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTransModeDescript[]={
	{ "emUnicast", (int)emUnicast },
	{ "emBroadcast", (int)emBroadcast },
	{ "emMulticast", (int)emMulticast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualSrcTypeDescript[]={
	{ "emDualVGA", (int)emDualVGA },
	{ "emDualVideo", (int)emDualVideo },
	{ "emDualPC", (int)emDualPC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtInstTypeDescript[]={
	{ "emMtService", (int)emMtService },
	{ "emMtUI", (int)emMtUI },
	{ "emMtConsole", (int)emMtConsole },
	{ "emMtH323Service", (int)emMtH323Service },
	{ "emMtH320Service", (int)emMtH320Service },
	{ "emMtSipService", (int)emMtSipService },
	{ "emMtH323StackIn", (int)emMtH323StackIn },
	{ "emMtH323StackOut", (int)emMtH323StackOut },
	{ "emMtMP", (int)emMtMP },
	{ "emMtDevice", (int)emMtDevice },
	{ "emMtAgent", (int)emMtAgent },
	{ "emMtSipStackIn", (int)emMtSipStackIn },
	{ "emMtSipStackOut", (int)emMtSipStackOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPStyleDescript[]={
	{ "emVMPDynamic", (int)emVMPDynamic },
	{ "emVMPOne", (int)emVMPOne },
	{ "emVMPVTwo", (int)emVMPVTwo },
	{ "emVMPHTwo", (int)emVMPHTwo },
	{ "emVMPThree", (int)emVMPThree },
	{ "emVMPFour", (int)emVMPFour },
	{ "emVMPSix", (int)emVMPSix },
	{ "emVMPEight", (int)emVMPEight },
	{ "emVMPNine", (int)emVMPNine },
	{ "emVMPTen", (int)emVMPTen },
	{ "emVMPThirteen", (int)emVMPThirteen },
	{ "emVMPSixteen", (int)emVMPSixteen },
	{ "emVMPSpecFour", (int)emVMPSpecFour },
	{ "emVMPSeven", (int)emVMPSeven },
	{ "emVMPSpecThirteen", (int)emVMPSpecThirteen },
	{ "emVMPTwenty", (int)emVMPTwenty },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPMmbTypeDescript[]={
	{ "emVMPMmbMCSspec", (int)emVMPMmbMCSspec },
	{ "emVMPMmbSpeaker", (int)emVMPMmbSpeaker },
	{ "emVMPMmbChairman", (int)emVMPMmbChairman },
	{ "emVMPMmbPoll", (int)emVMPMmbPoll },
	{ "emVMPMmbVAC", (int)emVMPMmbVAC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSMSTypeDescript[]={
	{ "emSMSSingleLine", (int)emSMSSingleLine },
	{ "emSMSPageTitle", (int)emSMSPageTitle },
	{ "emSMSRollTitle", (int)emSMSRollTitle },
	{ "emSMSStaticTitle", (int)emSMSStaticTitle },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtFileDescript[]={
	{ "emMtFileBegin", (int)emMtFileBegin },
	{ "emMtConfigFile", (int)emMtConfigFile },
	{ "emMtOldConfigBakFile", (int)emMtOldConfigBakFile },
	{ "emMtDebugConfiFile", (int)emMtDebugConfiFile },
	{ "emMtCameraCommandFile", (int)emMtCameraCommandFile },
	{ "emMtCameraPresetPostionFile", (int)emMtCameraPresetPostionFile },
	{ "emMtExternMaxtrixCommandFile", (int)emMtExternMaxtrixCommandFile },
	{ "emMtExternMaxtrixPortNameFile", (int)emMtExternMaxtrixPortNameFile },
	{ "emMtInnerMaxtrixSchemeFile", (int)emMtInnerMaxtrixSchemeFile },
	{ "emMtStreamMediaHtmlFile", (int)emMtStreamMediaHtmlFile },
	{ "emMtResourceFile", (int)emMtResourceFile },
	{ "emMtZipResourceFile", (int)emMtZipResourceFile },
	{ "emMtSymbolFile", (int)emMtSymbolFile },
	{ "emMtBannerFile", (int)emMtBannerFile },
	{ "emMtStaticPicFile", (int)emMtStaticPicFile },
	{ "emMtResInBin", (int)emMtResInBin },
	{ "emMtAddressBookEx", (int)emMtAddressBookEx },
	{ "emMtUpdateSysFile", (int)emMtUpdateSysFile },
	{ "emMtMinitorFile", (int)emMtMinitorFile },
	{ "emMtZipFile", (int)emMtZipFile },
	{ "emMtHintFile", (int)emMtHintFile },
	{ "emMtKeyFile", (int)emMtKeyFile },
	{ "emMtInnerPxyFile", (int)emMtInnerPxyFile },
	{ "emMtThreadBlockFile", (int)emMtThreadBlockFile },
	{ "emMtLogFile", (int)emMtLogFile },
	{ "emMtUserWordFile", (int)emMtUserWordFile },
	{ "emMtKdvLog", (int)emMtKdvLog },
	{ "emMtFileEnd", (int)emMtFileEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallRateDescript[]={
	{ "emRaten64", (int)emRaten64 },
	{ "emRaten2m64", (int)emRaten2m64 },
	{ "emRaten3m64", (int)emRaten3m64 },
	{ "emRaten4m64", (int)emRaten4m64 },
	{ "emRaten5m64", (int)emRaten5m64 },
	{ "emRaten6m64", (int)emRaten6m64 },
	{ "emRater384", (int)emRater384 },
	{ "emRater1536", (int)emRater1536 },
	{ "emRater1920", (int)emRater1920 },
	{ "emRater128", (int)emRater128 },
	{ "emRater192", (int)emRater192 },
	{ "emRater256", (int)emRater256 },
	{ "emRater320", (int)emRater320 },
	{ "emRater512", (int)emRater512 },
	{ "emRater768", (int)emRater768 },
	{ "emRater1152", (int)emRater1152 },
	{ "emRater1472", (int)emRater1472 },
	{ "emRater3M", (int)emRater3M },
	{ "emRater4M", (int)emRater4M },
	{ "emRater6M", (int)emRater6M },
	{ "emRater8M", (int)emRater8M },
	{ "emRaterLastOne", (int)emRaterLastOne },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPCCapFormatDescript[]={
	{ "emCapPCFrameBMP", (int)emCapPCFrameBMP },
	{ "emCapPCFrameUYUY", (int)emCapPCFrameUYUY },
	{ "emCapPCFrameI420", (int)emCapPCFrameI420 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPiPModeDescript[]={
	{ "emPiPClose", (int)emPiPClose },
	{ "emPiPRightBottom", (int)emPiPRightBottom },
	{ "emPiPLeftBottom", (int)emPiPLeftBottom },
	{ "emPiPLeftTop", (int)emPiPLeftTop },
	{ "emPiPRightTop", (int)emPiPRightTop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDVBComponentDescript[]={
	{ "emDVBEncoder", (int)emDVBEncoder },
	{ "emDVBPriomVideoDecoder", (int)emDVBPriomVideoDecoder },
	{ "emDVBSecondVideoDecoder", (int)emDVBSecondVideoDecoder },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUIPosionDescript[]={
	{ "emMT", (int)emMT },
	{ "emMTC", (int)emMTC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallDisconnectReasonDescript[]={
	{ "emDisconnect_Busy", (int)emDisconnect_Busy },
	{ "emDisconnect_Normal", (int)emDisconnect_Normal },
	{ "emDisconnect_Rejected", (int)emDisconnect_Rejected },
	{ "emDisconnect_Unreachable", (int)emDisconnect_Unreachable },
	{ "emDisconnect_Local", (int)emDisconnect_Local },
	{ "emDisconnect_Nnknown", (int)emDisconnect_Nnknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMCModeDescript[]={
	{ "emMcSpeech", (int)emMcSpeech },
	{ "emMcDiscuss", (int)emMcDiscuss },
	{ "emMcModeEnd", (int)emMcModeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmInnerVMPStyleDescript[]={
	{ "emInnerVMPAuto", (int)emInnerVMPAuto },
	{ "emInnerVMPOne", (int)emInnerVMPOne },
	{ "emInnerVMPTwo", (int)emInnerVMPTwo },
	{ "emInnerVMPThree", (int)emInnerVMPThree },
	{ "emInnerVMPFour", (int)emInnerVMPFour },
	{ "emInnerVMPFive", (int)emInnerVMPFive },
	{ "emInnerVMPSix", (int)emInnerVMPSix },
	{ "emInnerVMPTwoBigLittle", (int)emInnerVMPTwoBigLittle },
	{ "emInnerVMPThreeBigLittle", (int)emInnerVMPThreeBigLittle },
	{ "emInnerVMPFourBigLittle", (int)emInnerVMPFourBigLittle },
	{ "emInnerVMPEnd", (int)emInnerVMPEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVMPComponentDescript[]={
	{ "emVMPDecNull", (int)emVMPDecNull },
	{ "emVMPDec1th", (int)emVMPDec1th },
	{ "emVMPDec2th", (int)emVMPDec2th },
	{ "emVMPDec3th", (int)emVMPDec3th },
	{ "emVMPDec4th", (int)emVMPDec4th },
	{ "emVMPDec5th", (int)emVMPDec5th },
	{ "emVMPDecLocal", (int)emVMPDecLocal },
	{ "emVMPEnd", (int)emVMPEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCapTypeDescript[]={
	{ "emAudioOnly", (int)emAudioOnly },
	{ "emCameraOnly", (int)emCameraOnly },
	{ "emACBoth", (int)emACBoth },
	{ "emDesktopOnly", (int)emDesktopOnly },
	{ "emADBoth", (int)emADBoth },
	{ "emFileAVBoth", (int)emFileAVBoth },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPPPoEStateDescript[]={
	{ "emFree", (int)emFree },
	{ "emLinking", (int)emLinking },
	{ "emLinkup", (int)emLinkup },
	{ "emLinkdown", (int)emLinkdown },
	{ "emUserError", (int)emUserError },
	{ "emTimeOut", (int)emTimeOut },
	{ "emAgentError", (int)emAgentError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDhcpStateDescript[]={
	{ "emDhcpFree", (int)emDhcpFree },
	{ "emDhcpLinkup", (int)emDhcpLinkup },
	{ "emDhcpLinkdown", (int)emDhcpLinkdown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAddrGroupOptTypeDescript[]={
	{ "emCallIn", (int)emCallIn },
	{ "emCallOut", (int)emCallOut },
	{ "emUserDef", (int)emUserDef },
	{ "emTemplate", (int)emTemplate },
	{ "emSiteCall", (int)emSiteCall },
	{ "emMissed", (int)emMissed },
	{ "emUserDefExt0", (int)emUserDefExt0 },
	{ "emUserDefExt1", (int)emUserDefExt1 },
	{ "emUserDefExt2", (int)emUserDefExt2 },
	{ "emUserDefExt3", (int)emUserDefExt3 },
	{ "emUserDefExt4", (int)emUserDefExt4 },
	{ "emUserDefExt5", (int)emUserDefExt5 },
	{ "emInvalid", (int)emInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHotKeyTypeDescript[]={
	{ "emApplySpeak", (int)emApplySpeak },
	{ "emApplyChair", (int)emApplyChair },
	{ "emPrevPage", (int)emPrevPage },
	{ "emNextPage", (int)emNextPage },
	{ "emBack", (int)emBack },
	{ "emLoop", (int)emLoop },
	{ "emHotkeyEnd", (int)emHotkeyEnd },
	{ "emAEC", (int)emAEC },
	{ "emDial", (int)emDial },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtOSTypeDescript[]={
	{ "emWindows", (int)emWindows },
	{ "emVxworks", (int)emVxworks },
	{ "emLinux", (int)emLinux },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFxoStateDescript[]={
	{ "emFxoIdle", (int)emFxoIdle },
	{ "emFxoCalling", (int)emFxoCalling },
	{ "emFxoConnect", (int)emFxoConnect },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtLoudspeakerValDescript[]={
	{ "emLoudspeakerLow", (int)emLoudspeakerLow },
	{ "emLoudspeakerMiddle", (int)emLoudspeakerMiddle },
	{ "emLoudspeakerHigh", (int)emLoudspeakerHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmNetTypeDescript[]={
	{ "emInternet", (int)emInternet },
	{ "emSpecial", (int)emSpecial },
	{ "emVPN", (int)emVPN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSysRunSuccessFlagDescript[]={
	{ "emSysNoUpdateOperation", (int)emSysNoUpdateOperation },
	{ "emSysUpdateVersionRollBack", (int)emSysUpdateVersionRollBack },
	{ "emSysUpdateVersionSuccess", (int)emSysUpdateVersionSuccess },
	{ "emSysSetUpdateFlagFailed", (int)emSysSetUpdateFlagFailed },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMcuNtfMsgTypeDescript[]={
	{ "emMsgNoneNtf", (int)emMsgNoneNtf },
	{ "emMsgBePolledNextNtf", (int)emMsgBePolledNextNtf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmAutoTestTypeDescript[]={
	{ "emAutoTestTypeBegin", (int)emAutoTestTypeBegin },
	{ "emAutoTestEth0Func", (int)emAutoTestEth0Func },
	{ "emAutoTestEth1Func", (int)emAutoTestEth1Func },
	{ "emAutoTestE1Func", (int)emAutoTestE1Func },
	{ "emAutoTestAudioLoopBackFunc", (int)emAutoTestAudioLoopBackFunc },
	{ "emAutoTestVideoLoopBackFunc", (int)emAutoTestVideoLoopBackFunc },
	{ "emAutoTestSDI1InAllOutFunc", (int)emAutoTestSDI1InAllOutFunc },
	{ "emAutoTestSDI2InAllOutFunc", (int)emAutoTestSDI2InAllOutFunc },
	{ "emAutoTestDVI1InAllOutFunc", (int)emAutoTestDVI1InAllOutFunc },
	{ "emAutoTestDVI2InAllOutFunc", (int)emAutoTestDVI2InAllOutFunc },
	{ "emAutoTestDVI3InAllOutFunc", (int)emAutoTestDVI3InAllOutFunc },
	{ "emAuotTestCInAllOutFunc", (int)emAuotTestCInAllOutFunc },
	{ "emAutoTestDVI1InAllOutFunc_YPbPr", (int)emAutoTestDVI1InAllOutFunc_YPbPr },
	{ "emAutoTestDVI1InAllOutFunc_OSDYPbPr", (int)emAutoTestDVI1InAllOutFunc_OSDYPbPr },
	{ "emAutoTestBluerayHDMIFunc", (int)emAutoTestBluerayHDMIFunc },
	{ "emAutoTestBluerayHDMI2Func", (int)emAutoTestBluerayHDMI2Func },
	{ "emAutoTestBluerayHDMI3Func", (int)emAutoTestBluerayHDMI3Func },
	{ "emAutoTestBluerayRCAFunc", (int)emAutoTestBluerayRCAFunc },
	{ "emAutoTestCanonMICFunc", (int)emAutoTestCanonMICFunc },
	{ "emAutoTestDigMICFunc", (int)emAutoTestDigMICFunc },
	{ "emAutoTestLoudspeakerFunc", (int)emAutoTestLoudspeakerFunc },
	{ "emAutoTestCameraRotaFor232Func", (int)emAutoTestCameraRotaFor232Func },
	{ "emAutoTestCameraRotaFor485Func", (int)emAutoTestCameraRotaFor485Func },
	{ "emAutoTestRTCFunc", (int)emAutoTestRTCFunc },
	{ "emAutoTestLightFunc", (int)emAutoTestLightFunc },
	{ "emAutoTestRemoteCtrlFunc", (int)emAutoTestRemoteCtrlFunc },
	{ "emAutoTestSetDefault", (int)emAutoTestSetDefault },
	{ "emAutoTestRebootSysFunc", (int)emAutoTestRebootSysFunc },
	{ "emAutoTestTypeEnd", (int)emAutoTestTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGKRegFailedReasonDescript[]={
	{ "emNone", (int)emNone },
	{ "emGKUnReachable", (int)emGKUnReachable },
	{ "emInvalidAliase", (int)emInvalidAliase },
	{ "emDupAlias", (int)emDupAlias },
	{ "emInvalidCallAddress", (int)emInvalidCallAddress },
	{ "emResourceUnavailable", (int)emResourceUnavailable },
	{ "emUnknown", (int)emUnknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSleepStateDescript[]={
	{ "emSleepFail", (int)emSleepFail },
	{ "emWaitSleeping", (int)emWaitSleeping },
	{ "emSleeping", (int)emSleeping },
	{ "emSleeped", (int)emSleeped },
	{ "emWaking", (int)emWaking },
	{ "emWakeup", (int)emWakeup },
	{ "emWaitWaking", (int)emWaitWaking },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtAppNameDescript[]={
	{ "emMtAgentApp", (int)emMtAgentApp },
	{ "emMtServiceApp", (int)emMtServiceApp },
	{ "emMtGuardApp", (int)emMtGuardApp },
	{ "emMtUEApp", (int)emMtUEApp },
	{ "emMtStackInApp", (int)emMtStackInApp },
	{ "emMtStackOutApp", (int)emMtStackOutApp },
	{ "emMtRcpApp", (int)emMtRcpApp },
	{ "emMtH320StackApp", (int)emMtH320StackApp },
	{ "emMtRcSimApp", (int)emMtRcSimApp },
	{ "emMtMcApp", (int)emMtMcApp },
	{ "emMtSnmpApp", (int)emMtSnmpApp },
	{ "emMtConfigApp", (int)emMtConfigApp },
	{ "emMtUIApp", (int)emMtUIApp },
	{ "emMtDeviceApp", (int)emMtDeviceApp },
	{ "emMtCodecApp", (int)emMtCodecApp },
	{ "emMtConsoleApp", (int)emMtConsoleApp },
	{ "emMtSysApp", (int)emMtSysApp },
	{ "emMtH323ServiceApp", (int)emMtH323ServiceApp },
	{ "emMtH320ServiceApp", (int)emMtH320ServiceApp },
	{ "emMtSipServiceApp", (int)emMtSipServiceApp },
	{ "emMtDvbApp", (int)emMtDvbApp },
	{ "emMtDvbssnApp", (int)emMtDvbssnApp },
	{ "emMtVodClientApp", (int)emMtVodClientApp },
	{ "emMtPcdualvideoApp", (int)emMtPcdualvideoApp },
	{ "emMtUpgradeApp", (int)emMtUpgradeApp },
	{ "emMtbApp", (int)emMtbApp },
	{ "emMtAutotestApp", (int)emMtAutotestApp },
	{ "emMtAutotestClientApp", (int)emMtAutotestClientApp },
	{ "emMtRemoteSimApp", (int)emMtRemoteSimApp },
	{ "emMtThreadDetectApp", (int)emMtThreadDetectApp },
	{ "emMtLogRecvApp", (int)emMtLogRecvApp },
	{ "emMtLogIOApp", (int)emMtLogIOApp },
	{ "emMtProxyClientApp", (int)emMtProxyClientApp },
	{ "emMtSipStackInApp", (int)emMtSipStackInApp },
	{ "emMtSipStackOutApp", (int)emMtSipStackOutApp },
	{ "emMtSatServiceApp", (int)emMtSatServiceApp },
	{ "emMtTpRegApp", (int)emMtTpRegApp },
	{ "emMtAppEnd", (int)emMtAppEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumHD_PORT_MASKDescript[]={
	{ "PORT_SDI", (int)PORT_SDI },
	{ "PORT_HDMI", (int)PORT_HDMI },
	{ "PORT_YPrPb1", (int)PORT_YPrPb1 },
	{ "PORT_YPrPb2", (int)PORT_YPrPb2 },
	{ "PORT_VGA", (int)PORT_VGA },
	{ "PORT_C0", (int)PORT_C0 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHDAudPortInDescript[]={
	{ "emAudInCL", (int)emAudInCL },
	{ "emAudInCR", (int)emAudInCR },
	{ "emAudInCanonL", (int)emAudInCanonL },
	{ "emAudInCanonR", (int)emAudInCanonR },
	{ "emAudInHDMI1", (int)emAudInHDMI1 },
	{ "emAudInHDMI2", (int)emAudInHDMI2 },
	{ "emAudInHDMI3", (int)emAudInHDMI3 },
	{ "emAudInMic1", (int)emAudInMic1 },
	{ "emAudInMic2", (int)emAudInMic2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHDAudPortOutDescript[]={
	{ "emAudOutCCanon", (int)emAudOutCCanon },
	{ "emAudOutHDMI1", (int)emAudOutHDMI1 },
	{ "emAudOutHDMI2", (int)emAudOutHDMI2 },
	{ "emAudOutHDMI3", (int)emAudOutHDMI3 },
	{ "emAudOutReproducer", (int)emAudOutReproducer },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLogStatusDescript[]={
	{ "emLogClose", (int)emLogClose },
	{ "emLogOpen", (int)emLogOpen },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLogExportResultDescript[]={
	{ "emLogExportFailed", (int)emLogExportFailed },
	{ "emLogExportSuccess", (int)emLogExportSuccess },
	{ "emLogExportNoDisk", (int)emLogExportNoDisk },
	{ "emLogExportNoFile", (int)emLogExportNoFile },
	{ "emLogExportTransing", (int)emLogExportTransing },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFecModeTypeDescript[]={
	{ "emMTFECTYPENONE", (int)emMTFECTYPENONE },
	{ "emMTFECTYPERAID5", (int)emMTFECTYPERAID5 },
	{ "emMTFECTYPERAID5INTERLEAVE", (int)emMTFECTYPERAID5INTERLEAVE },
	{ "emMTFECTYPERAID6", (int)emMTFECTYPERAID6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmLabelPosTypeDescript[]={
	{ "emTopLeft", (int)emTopLeft },
	{ "emTopRight", (int)emTopRight },
	{ "emBottomLeft", (int)emBottomLeft },
	{ "emBottomRight", (int)emBottomRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtcBoxCallIndexDescript[]={
	{ "emShortCutCall1", (int)emShortCutCall1 },
	{ "emShortCutCall2", (int)emShortCutCall2 },
	{ "emShortCutCall3", (int)emShortCutCall3 },
	{ "emShortCutCall4", (int)emShortCutCall4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSipRegFailedReasonDescript[]={
	{ "emLocalNormalUnreg", (int)emLocalNormalUnreg },
	{ "emInvalidUserNameAndPassword", (int)emInvalidUserNameAndPassword },
	{ "emRegistrarUnReachable", (int)emRegistrarUnReachable },
	{ "emInvalidAlias", (int)emInvalidAlias },
	{ "emUnknownReason", (int)emUnknownReason },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecChnnlStateDescript[]={
	{ "STATE_IDLE", (int)STATE_IDLE },
	{ "STATE_RECREADY", (int)STATE_RECREADY },
	{ "STATE_RECORDING", (int)STATE_RECORDING },
	{ "STATE_RECPAUSE", (int)STATE_RECPAUSE },
	{ "STATE_PLAYREADY", (int)STATE_PLAYREADY },
	{ "STATE_PLAYREADYPLAY", (int)STATE_PLAYREADYPLAY },
	{ "STATE_PLAYING", (int)STATE_PLAYING },
	{ "STATE_PLAYPAUSE", (int)STATE_PLAYPAUSE },
	{ "STATE_FF", (int)STATE_FF },
	{ "STATE_FB", (int)STATE_FB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecChnnlTypeDescript[]={
	{ "TYPE_UNUSE", (int)TYPE_UNUSE },
	{ "TYPE_RECORD", (int)TYPE_RECORD },
	{ "TYPE_PLAY", (int)TYPE_PLAY },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecModeDescript[]={
	{ "MODE_SKIPFRAME", (int)MODE_SKIPFRAME },
	{ "MODE_REALTIME", (int)MODE_REALTIME },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMtRecEnumDescript[]={
	{ "MT_MAXNUM_RECORDER_CHNNL", (int)MT_MAXNUM_RECORDER_CHNNL },
	{ "MT_MAXLEN_RECORD_NAME", (int)MT_MAXLEN_RECORD_NAME },
	{ "MT_MAXLEN_CONFNAME", (int)MT_MAXLEN_CONFNAME },
	{ "MT_RECLIST_PACKSIZE", (int)MT_RECLIST_PACKSIZE },
	{ "MT_MAX_REC_NAME", (int)MT_MAX_REC_NAME },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMtRegResultDescript[]={
	{ "emMtRegSuccess", (int)emMtRegSuccess },
	{ "emMtRegPosError", (int)emMtRegPosError },
	{ "emMtRegTimeOut", (int)emMtRegTimeOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpRetDescript[]={
	{ "tp_Ret_FAILED", (int)tp_Ret_FAILED },
	{ "tp_Ret_Success", (int)tp_Ret_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpHduPlayNackReasonDescript[]={
	{ "em_hdu_play_success", (int)em_hdu_play_success },
	{ "em_Hdu_Invalid_Index", (int)em_Hdu_Invalid_Index },
	{ "em_Hdu_Invalid_ID", (int)em_Hdu_Invalid_ID },
	{ "em_Hdu_No_Reged", (int)em_Hdu_No_Reged },
	{ "em_Hdu_Illegal", (int)em_Hdu_Illegal },
	{ "em_Alias_Illegal", (int)em_Alias_Illegal },
	{ "em_Monitor_Fial", (int)em_Monitor_Fial },
	{ "em_Hdu_PlayNack", (int)em_Hdu_PlayNack },
	{ "em_Same_Alias", (int)em_Same_Alias },
	{ "em_unknown", (int)em_unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpLoginUmsRetDescript[]={
	{ "tp_LoginUms_sucess", (int)tp_LoginUms_sucess },
	{ "tp_LoginUms_NameError", (int)tp_LoginUms_NameError },
	{ "tp_LoginUms_PwdError", (int)tp_LoginUms_PwdError },
	{ "tp_LoginUms_MaxLogin", (int)tp_LoginUms_MaxLogin },
	{ "tp_LoginUms_Logged", (int)tp_LoginUms_Logged },
	{ "tp_LoginUms_SysIniting", (int)tp_LoginUms_SysIniting },
	{ "tp_LoginUms_steals_sucess", (int)tp_LoginUms_steals_sucess },
	{ "tp_LoginUms_steals_quit", (int)tp_LoginUms_steals_quit },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpAliasTypeDescript[]={
	{ "tp_Alias_Unknow", (int)tp_Alias_Unknow },
	{ "tp_Alias_e164", (int)tp_Alias_e164 },
	{ "tp_Alias_h323", (int)tp_Alias_h323 },
	{ "tp_Alias_IP", (int)tp_Alias_IP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpOprTypeDescript[]={
	{ "tp_OprType_Add", (int)tp_OprType_Add },
	{ "tp_OprType_Del", (int)tp_OprType_Del },
	{ "tp_OprType_Update", (int)tp_OprType_Update },
	{ "tp_OprType_NULL", (int)tp_OprType_NULL },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfAddEpRetDescript[]={
	{ "TP_ConfAddEpRet_Unknow", (int)TP_ConfAddEpRet_Unknow },
	{ "TP_ConfAddEpRet_Success", (int)TP_ConfAddEpRet_Success },
	{ "TP_ConfAddEpRet_MaxNum", (int)TP_ConfAddEpRet_MaxNum },
	{ "TP_ConfAddEpRet_AliasReapeat", (int)TP_ConfAddEpRet_AliasReapeat },
	{ "TP_ConfAddEpRet_ParamError", (int)TP_ConfAddEpRet_ParamError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpIFrameCheckTypeDescript[]={
	{ "TP_IFrameCheck_Speaker", (int)TP_IFrameCheck_Speaker },
	{ "TP_IFrameCheck_SingleSpeaker", (int)TP_IFrameCheck_SingleSpeaker },
	{ "TP_IFrameCheck_Poll", (int)TP_IFrameCheck_Poll },
	{ "TP_IFrameCheck_ChairWait", (int)TP_IFrameCheck_ChairWait },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEncryptTypeDescript[]={
	{ "emTPEncryptTypeNone", (int)emTPEncryptTypeNone },
	{ "emTPEncryptTypeDES", (int)emTPEncryptTypeDES },
	{ "emTPEncryptTypeAES", (int)emTPEncryptTypeAES },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPRcvAlignTypeDescript[]={
	{ "emTPRcvAlignTypeMidAlign", (int)emTPRcvAlignTypeMidAlign },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnsCallReasonDescript[]={
	{ "EmCnsCallReason_success", (int)EmCnsCallReason_success },
	{ "EmCnsCallReason_hungup", (int)EmCnsCallReason_hungup },
	{ "EmCnsCallReason_Unreachable", (int)EmCnsCallReason_Unreachable },
	{ "EmCnsCallReason_resourcefull", (int)EmCnsCallReason_resourcefull },
	{ "EmCnsCallReason_dstnotfind", (int)EmCnsCallReason_dstnotfind },
	{ "EmCnsCallReason_Busy", (int)EmCnsCallReason_Busy },
	{ "EmCnsCallReason_Local", (int)EmCnsCallReason_Local },
	{ "EmCnsCallReason_NoConf", (int)EmCnsCallReason_NoConf },
	{ "EmCnsCallReason_Exist", (int)EmCnsCallReason_Exist },
	{ "EmCnsCallReason_Rejected", (int)EmCnsCallReason_Rejected },
	{ "EmCnsCallReason_peerhungup", (int)EmCnsCallReason_peerhungup },
	{ "EmCnsCallReason_Abnormal", (int)EmCnsCallReason_Abnormal },
	{ "EmCnsCallReason_PeerAbnormal", (int)EmCnsCallReason_PeerAbnormal },
	{ "EmCnsCallReason_ConfOver", (int)EmCnsCallReason_ConfOver },
	{ "EmCnsCallReason_cncallexception", (int)EmCnsCallReason_cncallexception },
	{ "EmCnsCallReason_ConfExist", (int)EmCnsCallReason_ConfExist },
	{ "EmCnsCallReason_unknown", (int)EmCnsCallReason_unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChannelReasonDescript[]={
	{ "emTPChannelReasonBegin", (int)emTPChannelReasonBegin },
	{ "emTPChannelDisconnectNormal", (int)emTPChannelDisconnectNormal },
	{ "emTPDualOffLine", (int)emTPDualOffLine },
	{ "emTPForceStop", (int)emTPForceStop },
	{ "emTPDualNotSend", (int)emTPDualNotSend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCnsTypeDescript[]={
	{ "tp_CnsType_Unkonw", (int)tp_CnsType_Unkonw },
	{ "tp_CnsType_FiveScreen_FiveSpeeker", (int)tp_CnsType_FiveScreen_FiveSpeeker },
	{ "tp_CnsType_FiveScreen_ThreeSpeeker", (int)tp_CnsType_FiveScreen_ThreeSpeeker },
	{ "tp_CnsType_ThreeScreen_ThreeSpeeker", (int)tp_CnsType_ThreeScreen_ThreeSpeeker },
	{ "tp_CnsType_OneScreen_OneSpeeker", (int)tp_CnsType_OneScreen_OneSpeeker },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCnsRegUmsDescript[]={
	{ "tp_CnsRegRet_Unknow", (int)tp_CnsRegRet_Unknow },
	{ "tp_CnsRegRet_Success", (int)tp_CnsRegRet_Success },
	{ "tp_CnsRegRet_MaxRegNum", (int)tp_CnsRegRet_MaxRegNum },
	{ "tp_CnsRegRet_MaxAliasNum", (int)tp_CnsRegRet_MaxAliasNum },
	{ "tp_CnsRegRet_MsgError", (int)tp_CnsRegRet_MsgError },
	{ "tp_CnsRegRet_AliasRepeat", (int)tp_CnsRegRet_AliasRepeat },
	{ "tp_CnsRegRet_UnReg", (int)tp_CnsRegRet_UnReg },
	{ "tp_CnsRegRet_SysError", (int)tp_CnsRegRet_SysError },
	{ "tp_CnsRegRet_NotFind", (int)tp_CnsRegRet_NotFind },
	{ "tp_CnsRegRet_Fail", (int)tp_CnsRegRet_Fail },
	{ "tp_CnsRegRet_Unreachable", (int)tp_CnsRegRet_Unreachable },
	{ "tp_CnsRegRet_UnRegister", (int)tp_CnsRegRet_UnRegister },
	{ "tp_CnsRegRet_E164Repeat", (int)tp_CnsRegRet_E164Repeat },
	{ "tp_CnsRegRet_NameDup", (int)tp_CnsRegRet_NameDup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConfTemplateRetDescript[]={
	{ "TP_ConfTemplate_UnKonw", (int)TP_ConfTemplate_UnKonw },
	{ "TP_ConfTemplate_AddSuccess", (int)TP_ConfTemplate_AddSuccess },
	{ "TP_ConfTemplate_DelSuccess", (int)TP_ConfTemplate_DelSuccess },
	{ "TP_ConfTemplate_UpdateSuccess", (int)TP_ConfTemplate_UpdateSuccess },
	{ "TP_ConfTemplate_MaxNum", (int)TP_ConfTemplate_MaxNum },
	{ "TP_ConfTemplate_E164Repeat", (int)TP_ConfTemplate_E164Repeat },
	{ "TP_ConfTemplate_UnFindConf", (int)TP_ConfTemplate_UnFindConf },
	{ "TP_ConfTemplate_ParamInValid", (int)TP_ConfTemplate_ParamInValid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpStartConfRetDescript[]={
	{ "TP_StartConf_UnKonw", (int)TP_StartConf_UnKonw },
	{ "TP_StartConf_Success", (int)TP_StartConf_Success },
	{ "TP_StartConf_ConfTemplateUnExist", (int)TP_StartConf_ConfTemplateUnExist },
	{ "TP_StartConf_ConfFull", (int)TP_StartConf_ConfFull },
	{ "TP_StartConf_ConfExist", (int)TP_StartConf_ConfExist },
	{ "TP_StartConf_SipUnReg", (int)TP_StartConf_SipUnReg },
	{ "TP_StartConf_ResourceFull", (int)TP_StartConf_ResourceFull },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpApplySpeakerRetDescript[]={
	{ "TP_ApplySpeaker_Success", (int)TP_ApplySpeaker_Success },
	{ "TP_ApplySpeaker_ConfUnExist", (int)TP_ApplySpeaker_ConfUnExist },
	{ "TP_ApplySpeaker_EpIDError", (int)TP_ApplySpeaker_EpIDError },
	{ "TP_ApplySpeaker_EpStateError", (int)TP_ApplySpeaker_EpStateError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpDropConfRetDescript[]={
	{ "TP_DropConf_Success", (int)TP_DropConf_Success },
	{ "TP_DropConf_ConfUnExit", (int)TP_DropConf_ConfUnExit },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpApplySpeakRetDescript[]={
	{ "TP_ApplySpeak_UnKonw", (int)TP_ApplySpeak_UnKonw },
	{ "TP_ApplySpeak_Success", (int)TP_ApplySpeak_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUmsConfNodeStateDescript[]={
	{ "ums_UmsConfNodeState_unused", (int)ums_UmsConfNodeState_unused },
	{ "ums_UmsConfNodeState_uncall", (int)ums_UmsConfNodeState_uncall },
	{ "ums_UmsConfNodeState_calling", (int)ums_UmsConfNodeState_calling },
	{ "ums_UmsConfNodeState_callfailed", (int)ums_UmsConfNodeState_callfailed },
	{ "ums_UmsConfNodeState_online", (int)ums_UmsConfNodeState_online },
	{ "ums_UmsConfNodeState_stopcall", (int)ums_UmsConfNodeState_stopcall },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFlowCtrlOprDescript[]={
	{ "emFlowCtrl_Speaker", (int)emFlowCtrl_Speaker },
	{ "emFlowCtrl_Chair", (int)emFlowCtrl_Chair },
	{ "emFlowCtrl_Poll", (int)emFlowCtrl_Poll },
	{ "emFlowCtrl_TvWall", (int)emFlowCtrl_TvWall },
	{ "emFlowCtrl_View", (int)emFlowCtrl_View },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMBrdTypeDescript[]={
	{ "em_unknow_brd", (int)em_unknow_brd },
	{ "em_eapu_brd", (int)em_eapu_brd },
	{ "em_mpc_brd", (int)em_mpc_brd },
	{ "em_mpu2ecard_brd", (int)em_mpu2ecard_brd },
	{ "em_hdu2_brd", (int)em_hdu2_brd },
	{ "em_is22_brd", (int)em_is22_brd },
	{ "em_cri2_brd", (int)em_cri2_brd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMEqpTypeDescript[]={
	{ "em_unknow_mdl", (int)em_unknow_mdl },
	{ "em_adapter_mdl", (int)em_adapter_mdl },
	{ "em_dataswitch_mdl", (int)em_dataswitch_mdl },
	{ "em_netbuf_mdl", (int)em_netbuf_mdl },
	{ "em_audmix_mdl", (int)em_audmix_mdl },
	{ "em_mpc_mdl", (int)em_mpc_mdl },
	{ "em_bas_mdl", (int)em_bas_mdl },
	{ "em_vmp_mdl", (int)em_vmp_mdl },
	{ "em_hdu_mdl", (int)em_hdu_mdl },
	{ "em_regserver_mdl", (int)em_regserver_mdl },
	{ "em_recorder_mdl", (int)em_recorder_mdl },
	{ "em_max_mdl", (int)em_max_mdl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMEqpModleTypeDescript[]={
	{ "em_unknow_eqp_mdl", (int)em_unknow_eqp_mdl },
	{ "em_bas_basic_eqp_mdl", (int)em_bas_basic_eqp_mdl },
	{ "em_bas_enhanced_eqp_mdl", (int)em_bas_enhanced_eqp_mdl },
	{ "em_vmp_basic_eqp_mdl", (int)em_vmp_basic_eqp_mdl },
	{ "em_vmp_enhanced_eqp_mdl", (int)em_vmp_enhanced_eqp_mdl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMOsTypeDescript[]={
	{ "em_unknow_OsType", (int)em_unknow_OsType },
	{ "em_Win32_OsType", (int)em_Win32_OsType },
	{ "em_Linux_OsType", (int)em_Linux_OsType },
	{ "em_82xx_OsType", (int)em_82xx_OsType },
	{ "em_85xx_OsType", (int)em_85xx_OsType },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMVmpStyleDescript[]={
	{ "tp_VmpStyle_DYNAMIC", (int)tp_VmpStyle_DYNAMIC },
	{ "tp_VmpStyle_ONE", (int)tp_VmpStyle_ONE },
	{ "tp_VmpStyle_VTWO", (int)tp_VmpStyle_VTWO },
	{ "tp_VmpStyle_HTWO", (int)tp_VmpStyle_HTWO },
	{ "tp_VmpStyle_THREE", (int)tp_VmpStyle_THREE },
	{ "tp_VmpStyle_FOUR", (int)tp_VmpStyle_FOUR },
	{ "tp_VmpStyle_SIX", (int)tp_VmpStyle_SIX },
	{ "tp_VmpStyle_EIGHT", (int)tp_VmpStyle_EIGHT },
	{ "tp_VmpStyle_NINE", (int)tp_VmpStyle_NINE },
	{ "tp_VmpStyle_TEN", (int)tp_VmpStyle_TEN },
	{ "tp_VmpStyle_THIRTEEN", (int)tp_VmpStyle_THIRTEEN },
	{ "tp_VmpStyle_SIXTEEN", (int)tp_VmpStyle_SIXTEEN },
	{ "tp_VmpStyle_SPECFOUR", (int)tp_VmpStyle_SPECFOUR },
	{ "tp_VmpStyle_SEVEN", (int)tp_VmpStyle_SEVEN },
	{ "tp_VmpStyle_TWENTY", (int)tp_VmpStyle_TWENTY },
	{ "tp_VmpStyle_TEN_H", (int)tp_VmpStyle_TEN_H },
	{ "tp_VmpStyle_SIX_L2UP_S4DOWN", (int)tp_VmpStyle_SIX_L2UP_S4DOWN },
	{ "tp_VmpStyle_FOURTEEN", (int)tp_VmpStyle_FOURTEEN },
	{ "tp_VmpStyle_TEN_M", (int)tp_VmpStyle_TEN_M },
	{ "tp_VmpStyle_THIRTEEN_M", (int)tp_VmpStyle_THIRTEEN_M },
	{ "tp_VmpStyle_FIFTEEN", (int)tp_VmpStyle_FIFTEEN },
	{ "tp_VmpStyle_SIX_DIVIDE", (int)tp_VmpStyle_SIX_DIVIDE },
	{ "tp_VmpStyle_leftBig", (int)tp_VmpStyle_leftBig },
	{ "tp_VmpStyle_MidBig", (int)tp_VmpStyle_MidBig },
	{ "tp_VmpStyle_RightBig", (int)tp_VmpStyle_RightBig },
	{ "tp_VmpStyle_3VERTICAL", (int)tp_VmpStyle_3VERTICAL },
	{ "tp_VmpStyle_FOUR_3BOTTOMMIDDLE", (int)tp_VmpStyle_FOUR_3BOTTOMMIDDLE },
	{ "tp_VmpStyle_TWENTYFIVE", (int)tp_VmpStyle_TWENTYFIVE },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoFormatDescript[]={
	{ "emTPVH261", (int)emTPVH261 },
	{ "emTPVH262", (int)emTPVH262 },
	{ "emTPVH263", (int)emTPVH263 },
	{ "emTPVH263plus", (int)emTPVH263plus },
	{ "emTPVH264", (int)emTPVH264 },
	{ "emTPVMPEG4", (int)emTPVMPEG4 },
	{ "emTPVEnd", (int)emTPVEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpEncodeModeDescript[]={
	{ "emTPQualityFirst", (int)emTPQualityFirst },
	{ "emTPSpeedFirst", (int)emTPSpeedFirst },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoQualityLevelDescript[]={
	{ "emTPH264BP", (int)emTPH264BP },
	{ "emTPH264HP", (int)emTPH264HP },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVideoResolutionDescript[]={
	{ "emTPVResolutionAuto", (int)emTPVResolutionAuto },
	{ "emTPVSQCIF", (int)emTPVSQCIF },
	{ "emTPVQCIF", (int)emTPVQCIF },
	{ "emTPVCIF", (int)emTPVCIF },
	{ "emTPV2CIF", (int)emTPV2CIF },
	{ "emTPV4CIF", (int)emTPV4CIF },
	{ "emTPV16CIF", (int)emTPV16CIF },
	{ "emTPVHD480i720x480", (int)emTPVHD480i720x480 },
	{ "emTPVHD480p720x480", (int)emTPVHD480p720x480 },
	{ "emTPVHD576i720x576", (int)emTPVHD576i720x576 },
	{ "emTPVHD576p720x576", (int)emTPVHD576p720x576 },
	{ "emTPVHD720p1280x720", (int)emTPVHD720p1280x720 },
	{ "emTPVHD1080i1920x1080", (int)emTPVHD1080i1920x1080 },
	{ "emTPVHD1080p1920x1080", (int)emTPVHD1080p1920x1080 },
	{ "emTPVGA352x240", (int)emTPVGA352x240 },
	{ "emTPVGA704x480", (int)emTPVGA704x480 },
	{ "emTPVGA640x480", (int)emTPVGA640x480 },
	{ "emTPVGA800x600", (int)emTPVGA800x600 },
	{ "emTPVGA1024x768", (int)emTPVGA1024x768 },
	{ "emTPVGA1280x768", (int)emTPVGA1280x768 },
	{ "emTPVGA1280x800", (int)emTPVGA1280x800 },
	{ "emTPVGA1366x768", (int)emTPVGA1366x768 },
	{ "emTPVGA1280x854", (int)emTPVGA1280x854 },
	{ "emTPVGA1440x900", (int)emTPVGA1440x900 },
	{ "emTPVGA1280x1024", (int)emTPVGA1280x1024 },
	{ "emTPVGA1680x1050", (int)emTPVGA1680x1050 },
	{ "emTPVGA1600x1200", (int)emTPVGA1600x1200 },
	{ "emTPVGA1920x1200", (int)emTPVGA1920x1200 },
	{ "emTPVSQCIF112x96", (int)emTPVSQCIF112x96 },
	{ "emTPVSQCIF96x80", (int)emTPVSQCIF96x80 },
	{ "emTPV320x192", (int)emTPV320x192 },
	{ "emTPV432x240", (int)emTPV432x240 },
	{ "emTPV480x272", (int)emTPV480x272 },
	{ "emTPV640x368", (int)emTPV640x368 },
	{ "emTPV864x480", (int)emTPV864x480 },
	{ "emTPV960x544", (int)emTPV960x544 },
	{ "emTPV1440x816", (int)emTPV1440x816 },
	{ "emTPVResEnd", (int)emTPVResEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpMediaTypeDescript[]={
	{ "emTPMediaVideo", (int)emTPMediaVideo },
	{ "emTPMediaAudio", (int)emTPMediaAudio },
	{ "emTPMediaAV", (int)emTPMediaAV },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpPCCapFormatDescript[]={
	{ "emTPCapPCFrameBMP", (int)emTPCapPCFrameBMP },
	{ "emTPCapPCFrameUYUY", (int)emTPCapPCFrameUYUY },
	{ "emTPCapPCFrameI420", (int)emTPCapPCFrameI420 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCodecComponentDescript[]={
	{ "emTPPriomVideoEncoder", (int)emTPPriomVideoEncoder },
	{ "emTPPriomVideoDecoder", (int)emTPPriomVideoDecoder },
	{ "emTPSecondVideoEncoder", (int)emTPSecondVideoEncoder },
	{ "emTPSecondVideoDecoder", (int)emTPSecondVideoDecoder },
	{ "emTPAudioEncoder", (int)emTPAudioEncoder },
	{ "emTPAudioDecoder", (int)emTPAudioDecoder },
	{ "emTPSecondAudioEncoder", (int)emTPSecondAudioEncoder },
	{ "emTPSecondAudioDecoder", (int)emTPSecondAudioDecoder },
	{ "emTPPriomLeftVideoDecoder", (int)emTPPriomLeftVideoDecoder },
	{ "emTPPriomRightVideoDecoder", (int)emTPPriomRightVideoDecoder },
	{ "emTPCodecComponentEnd", (int)emTPCodecComponentEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpAudioFormatDescript[]={
	{ "emTPAG711a", (int)emTPAG711a },
	{ "emTPAG711u", (int)emTPAG711u },
	{ "emTPAG722", (int)emTPAG722 },
	{ "emTPAG7231", (int)emTPAG7231 },
	{ "emTPAG728", (int)emTPAG728 },
	{ "emTPAG729", (int)emTPAG729 },
	{ "emTPAMP3", (int)emTPAMP3 },
	{ "emTPAG721", (int)emTPAG721 },
	{ "emTPAG7221", (int)emTPAG7221 },
	{ "emTPAG719", (int)emTPAG719 },
	{ "emTPAMpegAACLC", (int)emTPAMpegAACLC },
	{ "emTPAMpegAACLD", (int)emTPAMpegAACLD },
	{ "emTPAEnd", (int)emTPAEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpLostPackageRestoreDescript[]={
	{ "emTPLPQualityFirst", (int)emTPLPQualityFirst },
	{ "emTPLPSpeedSlow", (int)emTPLPSpeedSlow },
	{ "emTPLPSpeedNormal", (int)emTPLPSpeedNormal },
	{ "emTPLPSpeedFast", (int)emTPLPSpeedFast },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCallModeDescript[]={
	{ "emTpJoin", (int)emTpJoin },
	{ "emTpCreate", (int)emTpCreate },
	{ "emTpInvite", (int)emTpInvite },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConnectionTypeDescript[]={
	{ "emTPConnectionBegin", (int)emTPConnectionBegin },
	{ "emTPTCPConnection", (int)emTPTCPConnection },
	{ "emTPUDPConnection", (int)emTPUDPConnection },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpConfProtocolDescript[]={
	{ "emTpInvalidConfProtocel", (int)emTpInvalidConfProtocel },
	{ "emTpH323", (int)emTpH323 },
	{ "emTpH320", (int)emTpH320 },
	{ "emTpSIP", (int)emTpSIP },
	{ "emTpSat", (int)emTpSat },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAddrTypeDescript[]={
	{ "emTpUnknown", (int)emTpUnknown },
	{ "emTpIPAddr", (int)emTpIPAddr },
	{ "emTpDomain", (int)emTpDomain },
	{ "emTpAlias", (int)emTpAlias },
	{ "emTpE164Num", (int)emTpE164Num },
	{ "emTpIP6Addr", (int)emTpIP6Addr },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEndpointTypeDescript[]={
	{ "emTPEndpointTypeUnknown", (int)emTPEndpointTypeUnknown },
	{ "emTPEndpointTypeCNS", (int)emTPEndpointTypeCNS },
	{ "emTPEndpointTypeUMS", (int)emTPEndpointTypeUMS },
	{ "emTPEndpointTypeRegister", (int)emTPEndpointTypeRegister },
	{ "emTPEndpointH323MT", (int)emTPEndpointH323MT },
	{ "emTPEndpointH323MCU", (int)emTPEndpointH323MCU },
	{ "emTPEndpointH323SingleMCU", (int)emTPEndpointH323SingleMCU },
	{ "emTPEndpointH323G400", (int)emTPEndpointH323G400 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPSipLevelDescript[]={
	{ "emTPSipCounty", (int)emTPSipCounty },
	{ "emTPSipCity", (int)emTPSipCity },
	{ "emTPSipProvince", (int)emTPSipProvince },
	{ "emTPSipUnKnown", (int)emTPSipUnKnown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCALLSTATEDescript[]={
	{ "em_CALL_IDLE", (int)em_CALL_IDLE },
	{ "em_CALL_CALLING", (int)em_CALL_CALLING },
	{ "em_CALL_CONNECTED", (int)em_CALL_CONNECTED },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCallTypeDescript[]={
	{ "emCallType_Invalid", (int)emCallType_Invalid },
	{ "emCallType_P2P", (int)emCallType_P2P },
	{ "emCallType_Conf", (int)emCallType_Conf },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoTypeDescript[]={
	{ "emTpPriomVideo", (int)emTpPriomVideo },
	{ "emTpMiniVideo", (int)emTpMiniVideo },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoPortDescript[]={
	{ "emTpVGA", (int)emTpVGA },
	{ "emTpSVid", (int)emTpSVid },
	{ "emTpPC", (int)emTpPC },
	{ "emTpC1Vid", (int)emTpC1Vid },
	{ "emTpC2Vid", (int)emTpC2Vid },
	{ "emTpC3Vid", (int)emTpC3Vid },
	{ "emTpC4Vid", (int)emTpC4Vid },
	{ "emTpC5Vid", (int)emTpC5Vid },
	{ "emTpC6Vid", (int)emTpC6Vid },
	{ "emTpExternalVid", (int)emTpExternalVid },
	{ "emTpVideoMaxCount", (int)emTpVideoMaxCount },
	{ "emTpVidInvalid", (int)emTpVidInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCNSInfoRstDescript[]={
	{ "emTPCNSInfoSuccess", (int)emTPCNSInfoSuccess },
	{ "emTPCNSRepeatE164", (int)emTPCNSRepeatE164 },
	{ "emTPCNSRepeatAliasName", (int)emTPCNSRepeatAliasName },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPRegResultDescript[]={
	{ "emTPRegResultBegin", (int)emTPRegResultBegin },
	{ "emTPRegResultReg", (int)emTPRegResultReg },
	{ "emTPRegResultUnReg", (int)emTPRegResultUnReg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnMtRegResultDescript[]={
	{ "emCnMtSuccess", (int)emCnMtSuccess },
	{ "emCnMtPosError", (int)emCnMtPosError },
	{ "emCnMtTimeOut", (int)emCnMtTimeOut },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnModelDescript[]={
	{ "emUnknownCnModel", (int)emUnknownCnModel },
	{ "em7920", (int)em7920 },
	{ "T300", (int)T300 },
	{ "Moon90", (int)Moon90 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFocusModeDescript[]={
	{ "emFocusAuto", (int)emFocusAuto },
	{ "emFocusManuel", (int)emFocusManuel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmFocusDescript[]={
	{ "emFar", (int)emFar },
	{ "emNear", (int)emNear },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmZoomDescript[]={
	{ "emTele", (int)emTele },
	{ "emWide", (int)emWide },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnActionDescript[]={
	{ "emCnStart", (int)emCnStart },
	{ "emCnStop", (int)emCnStop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmOSDShowDescript[]={
	{ "emOSDOff", (int)emOSDOff },
	{ "emOSDOn", (int)emOSDOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmWBModeDescript[]={
	{ "emWBAuto", (int)emWBAuto },
	{ "emWBManual", (int)emWBManual },
	{ "emOnePush", (int)emOnePush },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmExpModeDescript[]={
	{ "emExpAuto", (int)emExpAuto },
	{ "emExpManuel", (int)emExpManuel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGainDescript[]={
	{ "em0dB", (int)em0dB },
	{ "em3dB", (int)em3dB },
	{ "em6dB", (int)em6dB },
	{ "em9dB", (int)em9dB },
	{ "em12dB", (int)em12dB },
	{ "em15dB", (int)em15dB },
	{ "em18dB", (int)em18dB },
	{ "em21dB", (int)em21dB },
	{ "em24dB", (int)em24dB },
	{ "em27dB", (int)em27dB },
	{ "em30dB", (int)em30dB },
	{ "em33dB", (int)em33dB },
	{ "em36dB", (int)em36dB },
	{ "em39dB", (int)em39dB },
	{ "em42dB", (int)em42dB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmShutSpdDescript[]={
	{ "emShutSpd0", (int)emShutSpd0 },
	{ "emShutSpd1", (int)emShutSpd1 },
	{ "emShutSpd2", (int)emShutSpd2 },
	{ "emShutSpd3", (int)emShutSpd3 },
	{ "emShutSpd4", (int)emShutSpd4 },
	{ "emShutSpd5", (int)emShutSpd5 },
	{ "emShutSpd6", (int)emShutSpd6 },
	{ "emShutSpd7", (int)emShutSpd7 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmBackLightTypeDescript[]={
	{ "emBLOff", (int)emBLOff },
	{ "emBLmulti", (int)emBLmulti },
	{ "emBLcenter", (int)emBLcenter },
	{ "emBLfacedetect", (int)emBLfacedetect },
	{ "emBLAuto", (int)emBLAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmPicSceModeDescript[]={
	{ "emLamp", (int)emLamp },
	{ "emSun", (int)emSun },
	{ "emManuel", (int)emManuel },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGammaDescript[]={
	{ "emGammaOff", (int)emGammaOff },
	{ "emGammaOn", (int)emGammaOn },
	{ "emSmart1", (int)emSmart1 },
	{ "emSmart2", (int)emSmart2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmStmCleanDescript[]={
	{ "emNRoff", (int)emNRoff },
	{ "emNRlow", (int)emNRlow },
	{ "emNRmid", (int)emNRmid },
	{ "emNRhigh", (int)emNRhigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEm3DNRDescript[]={
	{ "em3DNROff", (int)em3DNROff },
	{ "em3DNROn", (int)em3DNROn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCamPowerModeDescript[]={
	{ "emCamPowerOn", (int)emCamPowerOn },
	{ "emCamPowerOff", (int)emCamPowerOff },
	{ "emCamPowerDowm", (int)emCamPowerDowm },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCenSchModeDescript[]={
	{ "emSchSleep", (int)emSchSleep },
	{ "emSchWakeup", (int)emSchWakeup },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTvPowerModeDescript[]={
	{ "emTVPowerOFF", (int)emTVPowerOFF },
	{ "emTVPowerON", (int)emTVPowerON },
	{ "emTVPowerDown", (int)emTVPowerDown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTvSrcPowerModeDescript[]={
	{ "emTVSrcPowerOFF", (int)emTVSrcPowerOFF },
	{ "emTVSrcPowerON", (int)emTVSrcPowerON },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVAudVisModeDescript[]={
	{ "emTVAVStandardMode", (int)emTVAVStandardMode },
	{ "emTVAVMovieMode", (int)emTVAVMovieMode },
	{ "emTVAVUserMode", (int)emTVAVUserMode },
	{ "emTVAVComputerMode", (int)emTVAVComputerMode },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVDisplayModeDescript[]={
	{ "emTVDisFullScrMode", (int)emTVDisFullScrMode },
	{ "emTVDisPanoramaMode", (int)emTVDisPanoramaMode },
	{ "emTVDisPointMode", (int)emTVDisPointMode },
	{ "emTVDisStandardMode", (int)emTVDisStandardMode },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTVInputSelectDescript[]={
	{ "emTVHDMI1", (int)emTVHDMI1 },
	{ "emTVHDMI2", (int)emTVHDMI2 },
	{ "emTVHDMI3", (int)emTVHDMI3 },
	{ "emTVHDMI4", (int)emTVHDMI4 },
	{ "emTVYpbPr", (int)emTVYpbPr },
	{ "emTVCVBS1", (int)emTVCVBS1 },
	{ "emTVCVBS2", (int)emTVCVBS2 },
	{ "emTVComputer", (int)emTVComputer },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamWBModeDescript[]={
	{ "emDcamWBAuto", (int)emDcamWBAuto },
	{ "emDCamWBManual", (int)emDCamWBManual },
	{ "emDCamOnePush", (int)emDCamOnePush },
	{ "emDCamWBInvalid", (int)emDCamWBInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamAFModeDescript[]={
	{ "emDcamAFOff", (int)emDcamAFOff },
	{ "emDCamAFOn", (int)emDCamAFOn },
	{ "emDCamAFToggle", (int)emDCamAFToggle },
	{ "emDCamAFInvalid", (int)emDCamAFInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamPowerDescript[]={
	{ "emDCamPowerOff", (int)emDCamPowerOff },
	{ "emDCamPowerOn", (int)emDCamPowerOn },
	{ "emDCamPowerToggle", (int)emDCamPowerToggle },
	{ "emDCamPowerDown", (int)emDCamPowerDown },
	{ "emDCamPowerInvalid", (int)emDCamPowerInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamZoomDescript[]={
	{ "emDCamZoomWide", (int)emDCamZoomWide },
	{ "emDCamZoomTele", (int)emDCamZoomTele },
	{ "emDCamZoomInvalid", (int)emDCamZoomInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamPresetNumDescript[]={
	{ "emDCamPresetOne", (int)emDCamPresetOne },
	{ "emDCamPresetTwo", (int)emDCamPresetTwo },
	{ "emDCamPresetThree", (int)emDCamPresetThree },
	{ "emDCamPresetInvalid", (int)emDCamPresetInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDCamRecallNumDescript[]={
	{ "emDCamRecallOne", (int)emDCamRecallOne },
	{ "emDCamRecallTwo", (int)emDCamRecallTwo },
	{ "emDCamRecallThree", (int)emDCamRecallThree },
	{ "emDCamRecallInvalid", (int)emDCamRecallInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchPowerDescript[]={
	{ "emSchPowerOff", (int)emSchPowerOff },
	{ "emSchPowerOn", (int)emSchPowerOn },
	{ "emSchPowerToggle", (int)emSchPowerToggle },
	{ "emSchPowerInvalid", (int)emSchPowerInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchLightDescript[]={
	{ "emSchLightOff", (int)emSchLightOff },
	{ "emSchLightOn", (int)emSchLightOn },
	{ "emSchLightInvalid", (int)emSchLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchMidLightDescript[]={
	{ "emSchMidLightOff", (int)emSchMidLightOff },
	{ "emSchMidLightOn", (int)emSchMidLightOn },
	{ "emSchMidLightInvalid", (int)emSchMidLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchScrLightDescript[]={
	{ "emSchScrLightOff", (int)emSchScrLightOff },
	{ "emSchScrLightOn", (int)emSchScrLightOn },
	{ "emSchScrLightInvalid", (int)emSchScrLightInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchArgusDescript[]={
	{ "emSchArgusUnlock", (int)emSchArgusUnlock },
	{ "emSchArgusLock", (int)emSchArgusLock },
	{ "emSchArgusInvalid", (int)emSchArgusInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACPowerDescript[]={
	{ "emCenACPowerOff", (int)emCenACPowerOff },
	{ "emCenACPowerOn", (int)emCenACPowerOn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACAirVolDescript[]={
	{ "emCenACVolAuto", (int)emCenACVolAuto },
	{ "emCenACVol1", (int)emCenACVol1 },
	{ "emCenACVol2", (int)emCenACVol2 },
	{ "emCenACVol3", (int)emCenACVol3 },
	{ "emCenACVol4", (int)emCenACVol4 },
	{ "emCenACVol5", (int)emCenACVol5 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCentreACModeDescript[]={
	{ "emCenACBlowIn", (int)emCenACBlowIn },
	{ "emCenACheat", (int)emCenACheat },
	{ "emCenAcref", (int)emCenAcref },
	{ "emCenACAuto", (int)emCenACAuto },
	{ "emCenACChaAir", (int)emCenACChaAir },
	{ "emCenACdeh", (int)emCenACdeh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCurActionDescript[]={
	{ "emCurUp", (int)emCurUp },
	{ "emCurDown", (int)emCurDown },
	{ "emCurStop", (int)emCurStop },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCurChannelModeDescript[]={
	{ "emCurChanFirst", (int)emCurChanFirst },
	{ "emCurChanSecond", (int)emCurChanSecond },
	{ "emCurChanFirASec", (int)emCurChanFirASec },
	{ "emCurChanThird", (int)emCurChanThird },
	{ "emCurChanFirAThi", (int)emCurChanFirAThi },
	{ "emCurChanSecAThi", (int)emCurChanSecAThi },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSchGatewayTypeDescript[]={
	{ "emGatewayOld", (int)emGatewayOld },
	{ "emGatewayNew", (int)emGatewayNew },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpMixStatusDescript[]={
	{ "emAudMixIdle", (int)emAudMixIdle },
	{ "emAudOpenChan_Fail", (int)emAudOpenChan_Fail },
	{ "emAudOpenChan_Success", (int)emAudOpenChan_Success },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualReasonDescript[]={
	{ "emTpDualAccept", (int)emTpDualAccept },
	{ "emTpDualBusy", (int)emTpDualBusy },
	{ "emTpDualPreemptive", (int)emTpDualPreemptive },
	{ "emTpDualPeerReject", (int)emTpDualPeerReject },
	{ "emTpDualPeerStop", (int)emTpDualPeerStop },
	{ "emTpDualNoVideo", (int)emTpDualNoVideo },
	{ "emTpDualLocalStop", (int)emTpDualLocalStop },
	{ "emTpDualSndFail", (int)emTpDualSndFail },
	{ "emTpDualInit", (int)emTpDualInit },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPayloadTypeDescript[]={
	{ "emTpPayloadTypeBegin", (int)emTpPayloadTypeBegin },
	{ "emTpAudioTypeBegin", (int)emTpAudioTypeBegin },
	{ "emTpG711a", (int)emTpG711a },
	{ "emTpG711u", (int)emTpG711u },
	{ "emTpG722", (int)emTpG722 },
	{ "emTpG7231", (int)emTpG7231 },
	{ "emTpG728", (int)emTpG728 },
	{ "emTpG729", (int)emTpG729 },
	{ "emTpMp3", (int)emTpMp3 },
	{ "emTpG723", (int)emTpG723 },
	{ "emTpG7221", (int)emTpG7221 },
	{ "emTpMpegaaclc", (int)emTpMpegaaclc },
	{ "emTpMpegaacld", (int)emTpMpegaacld },
	{ "emTpG719", (int)emTpG719 },
	{ "emTpAudioTypeEnd", (int)emTpAudioTypeEnd },
	{ "emTpVideoTypeBegin", (int)emTpVideoTypeBegin },
	{ "emTpH261", (int)emTpH261 },
	{ "emTpH263", (int)emTpH263 },
	{ "emTpH263plus", (int)emTpH263plus },
	{ "emTpH264", (int)emTpH264 },
	{ "emTpH262", (int)emTpH262 },
	{ "emTpMpeg4", (int)emTpMpeg4 },
	{ "emTpVideoTypeEnd", (int)emTpVideoTypeEnd },
	{ "emTpDataTypeBegin", (int)emTpDataTypeBegin },
	{ "emTpT120", (int)emTpT120 },
	{ "emTpH224", (int)emTpH224 },
	{ "emTpDataTypeEnd", (int)emTpDataTypeEnd },
	{ "emTpPayloadTypeEnd", (int)emTpPayloadTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPosStatusDescript[]={
	{ "emPosInAcitve", (int)emPosInAcitve },
	{ "emPosAcitve", (int)emPosAcitve },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPollResultDescript[]={
	{ "emPollSucceed", (int)emPollSucceed },
	{ "emPollFailUnKown", (int)emPollFailUnKown },
	{ "emPollInvalidEp", (int)emPollInvalidEp },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPViewResultDescript[]={
	{ "emViewSucceed", (int)emViewSucceed },
	{ "emViewFailUnKown", (int)emViewFailUnKown },
	{ "emViewFailStatusError", (int)emViewFailStatusError },
	{ "emViewFailOffline", (int)emViewFailOffline },
	{ "emViewFailNotChair", (int)emViewFailNotChair },
	{ "emViewFailNoResource", (int)emViewFailNoResource },
	{ "emViewFailDstNoVid", (int)emViewFailDstNoVid },
	{ "emViewRequesting", (int)emViewRequesting },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPViewLocalResultDescript[]={
	{ "emViewLocalSucceed", (int)emViewLocalSucceed },
	{ "emViewLocalFailUnKown", (int)emViewLocalFailUnKown },
	{ "emViewLocalFailStatusError", (int)emViewLocalFailStatusError },
	{ "emViewLocalFailOffline", (int)emViewLocalFailOffline },
	{ "emViewLocalFailIllegalPos", (int)emViewLocalFailIllegalPos },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDisOprTypeDescript[]={
	{ "emDisOprType_Idle", (int)emDisOprType_Idle },
	{ "emDisOprType_StartAll", (int)emDisOprType_StartAll },
	{ "emDisOprType_AddChnl", (int)emDisOprType_AddChnl },
	{ "emDisOprType_ChangeSeat", (int)emDisOprType_ChangeSeat },
	{ "emDisOprType_RemoveChnl", (int)emDisOprType_RemoveChnl },
	{ "emDisOprType_DisConnectChnl", (int)emDisOprType_DisConnectChnl },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMPosPicDescript[]={
	{ "emPic_Invalid", (int)emPic_Invalid },
	{ "emPic_Local", (int)emPic_Local },
	{ "emPic_Static", (int)emPic_Static },
	{ "emPic_Speaker", (int)emPic_Speaker },
	{ "emPic_Dual", (int)emPic_Dual },
	{ "emPic_Poll", (int)emPic_Poll },
	{ "emPic_SelView", (int)emPic_SelView },
	{ "emPic_SelDual", (int)emPic_SelDual },
	{ "emPic_SelLocal", (int)emPic_SelLocal },
	{ "emPic_Discuss", (int)emPic_Discuss },
	{ "emPic_SelTVS", (int)emPic_SelTVS },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMDSCREATETYPEDescript[]={
	{ "emDS_CreateType_Invalid", (int)emDS_CreateType_Invalid },
	{ "emDS_CreateType_SndBoundary", (int)emDS_CreateType_SndBoundary },
	{ "emDS_CreateType_RcvBoundary", (int)emDS_CreateType_RcvBoundary },
	{ "emDS_CreateType_SndAndRcvBoundary", (int)emDS_CreateType_SndAndRcvBoundary },
	{ "emDS_CreateType_NotBoundary", (int)emDS_CreateType_NotBoundary },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAddDualRcvResultDescript[]={
	{ "emAddDualRcvSucceed", (int)emAddDualRcvSucceed },
	{ "emAddDualRcvFailNoDual", (int)emAddDualRcvFailNoDual },
	{ "emAddDualRcvFailIllegalPos", (int)emAddDualRcvFailIllegalPos },
	{ "emAddDualRcvFailNoPos", (int)emAddDualRcvFailNoPos },
	{ "emAddDualRcvFailStatusError", (int)emAddDualRcvFailStatusError },
	{ "emAddDualRcvFailUnKown", (int)emAddDualRcvFailUnKown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDeleteDualRcvResultDescript[]={
	{ "emDeleteDualRcvSucceed", (int)emDeleteDualRcvSucceed },
	{ "emDeleteDualRcvFailNoDual", (int)emDeleteDualRcvFailNoDual },
	{ "emDeleteDualRcvFailIllegalPos", (int)emDeleteDualRcvFailIllegalPos },
	{ "emDeleteDualRcvFailUnKown", (int)emDeleteDualRcvFailUnKown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtModelDescript[]={
	{ "emTPUnknownMtModel", (int)emTPUnknownMtModel },
	{ "emTPPCMT", (int)emTPPCMT },
	{ "emTP8010", (int)emTP8010 },
	{ "emTP8010A", (int)emTP8010A },
	{ "emTP8010Aplus", (int)emTP8010Aplus },
	{ "emTP8010C", (int)emTP8010C },
	{ "emTP8010C1", (int)emTP8010C1 },
	{ "emTPIMT", (int)emTPIMT },
	{ "emTP8220A", (int)emTP8220A },
	{ "emTP8220B", (int)emTP8220B },
	{ "emTP8220C", (int)emTP8220C },
	{ "emTP8620A", (int)emTP8620A },
	{ "emTPTS6610E", (int)emTPTS6610E },
	{ "emTPTS6210", (int)emTPTS6210 },
	{ "emTP8010A_2", (int)emTP8010A_2 },
	{ "emTP8010A_4", (int)emTP8010A_4 },
	{ "emTP8010A_8", (int)emTP8010A_8 },
	{ "emTP7210", (int)emTP7210 },
	{ "emTP7610", (int)emTP7610 },
	{ "emTPTS5610", (int)emTPTS5610 },
	{ "emTPTS6610", (int)emTPTS6610 },
	{ "emTP7810", (int)emTP7810 },
	{ "emTP7910", (int)emTP7910 },
	{ "emTP7620_A", (int)emTP7620_A },
	{ "emTP7620_B", (int)emTP7620_B },
	{ "emTP7820_A", (int)emTP7820_A },
	{ "emTP7820_B", (int)emTP7820_B },
	{ "emTP7920_A", (int)emTP7920_A },
	{ "emTP7920_B", (int)emTP7920_B },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDsTypeDescript[]={
	{ "em_DsType_Invalid", (int)em_DsType_Invalid },
	{ "em_Ds_Remote_ASnd_0", (int)em_Ds_Remote_ASnd_0 },
	{ "em_Ds_Remote_ASnd_1", (int)em_Ds_Remote_ASnd_1 },
	{ "em_Ds_Remote_ASnd_2", (int)em_Ds_Remote_ASnd_2 },
	{ "em_Ds_Remote_ARcv_0", (int)em_Ds_Remote_ARcv_0 },
	{ "em_Ds_Remote_ARcv_1", (int)em_Ds_Remote_ARcv_1 },
	{ "em_Ds_Remote_ARcv_2", (int)em_Ds_Remote_ARcv_2 },
	{ "em_Ds_Remote_VSnd_0", (int)em_Ds_Remote_VSnd_0 },
	{ "em_Ds_Remote_VSnd_1", (int)em_Ds_Remote_VSnd_1 },
	{ "em_Ds_Remote_VSnd_2", (int)em_Ds_Remote_VSnd_2 },
	{ "em_Ds_Remote_VRcv_0", (int)em_Ds_Remote_VRcv_0 },
	{ "em_Ds_Remote_VRcv_1", (int)em_Ds_Remote_VRcv_1 },
	{ "em_Ds_Remote_VRcv_2", (int)em_Ds_Remote_VRcv_2 },
	{ "em_Ds_Remote_VSnd_0_Mini_0", (int)em_Ds_Remote_VSnd_0_Mini_0 },
	{ "em_Ds_Remote_VSnd_1_Mini_0", (int)em_Ds_Remote_VSnd_1_Mini_0 },
	{ "em_Ds_Remote_VSnd_2_Mini_0", (int)em_Ds_Remote_VSnd_2_Mini_0 },
	{ "em_Ds_Remote_VRcv_0_Mini_0", (int)em_Ds_Remote_VRcv_0_Mini_0 },
	{ "em_Ds_Remote_VRcv_0_Mini_1", (int)em_Ds_Remote_VRcv_0_Mini_1 },
	{ "em_Ds_Remote_VRcv_1_Mini_0", (int)em_Ds_Remote_VRcv_1_Mini_0 },
	{ "em_Ds_Remote_VRcv_1_Mini_1", (int)em_Ds_Remote_VRcv_1_Mini_1 },
	{ "em_Ds_Remote_VRcv_2_Mini_0", (int)em_Ds_Remote_VRcv_2_Mini_0 },
	{ "em_Ds_Remote_VRcv_2_Mini_1", (int)em_Ds_Remote_VRcv_2_Mini_1 },
	{ "em_Ds_Remote_Mix_Snd", (int)em_Ds_Remote_Mix_Snd },
	{ "em_Ds_Remote_Mix_Rcv", (int)em_Ds_Remote_Mix_Rcv },
	{ "em_Ds_RemoteDual_ASnd", (int)em_Ds_RemoteDual_ASnd },
	{ "em_Ds_RemoteDual_VSnd", (int)em_Ds_RemoteDual_VSnd },
	{ "em_Ds_RemoteDual_ARcv", (int)em_Ds_RemoteDual_ARcv },
	{ "em_Ds_RemoteDual_VRcv", (int)em_Ds_RemoteDual_VRcv },
	{ "em_Ds_VirRemote_ASnd_0", (int)em_Ds_VirRemote_ASnd_0 },
	{ "em_Ds_VirRemote_ASnd_1", (int)em_Ds_VirRemote_ASnd_1 },
	{ "em_Ds_VirRemote_ASnd_2", (int)em_Ds_VirRemote_ASnd_2 },
	{ "em_Ds_VirRemote_ARcv_0", (int)em_Ds_VirRemote_ARcv_0 },
	{ "em_Ds_VirRemote_ARcv_1", (int)em_Ds_VirRemote_ARcv_1 },
	{ "em_Ds_VirRemote_ARcv_2", (int)em_Ds_VirRemote_ARcv_2 },
	{ "em_Ds_VirRemote_VSnd_0", (int)em_Ds_VirRemote_VSnd_0 },
	{ "em_Ds_VirRemote_VSnd_1", (int)em_Ds_VirRemote_VSnd_1 },
	{ "em_Ds_VirRemote_VSnd_2", (int)em_Ds_VirRemote_VSnd_2 },
	{ "em_Ds_VirRemote_VRcv_0", (int)em_Ds_VirRemote_VRcv_0 },
	{ "em_Ds_VirRemote_VRcv_1", (int)em_Ds_VirRemote_VRcv_1 },
	{ "em_Ds_VirRemote_VRcv_2", (int)em_Ds_VirRemote_VRcv_2 },
	{ "em_Ds_VirRemote_VSnd_0_Mini_0", (int)em_Ds_VirRemote_VSnd_0_Mini_0 },
	{ "em_Ds_VirRemote_VSnd_1_Mini_0", (int)em_Ds_VirRemote_VSnd_1_Mini_0 },
	{ "em_Ds_VirRemote_VSnd_2_Mini_0", (int)em_Ds_VirRemote_VSnd_2_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_0_Mini_0", (int)em_Ds_VirRemote_VRcv_0_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_0_Mini_1", (int)em_Ds_VirRemote_VRcv_0_Mini_1 },
	{ "em_Ds_VirRemote_VRcv_1_Mini_0", (int)em_Ds_VirRemote_VRcv_1_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_1_Mini_1", (int)em_Ds_VirRemote_VRcv_1_Mini_1 },
	{ "em_Ds_VirRemote_VRcv_2_Mini_0", (int)em_Ds_VirRemote_VRcv_2_Mini_0 },
	{ "em_Ds_VirRemote_VRcv_2_Mini_1", (int)em_Ds_VirRemote_VRcv_2_Mini_1 },
	{ "em_Ds_VirRemote_Mix_Snd", (int)em_Ds_VirRemote_Mix_Snd },
	{ "em_Ds_VirRemote_Mix_Rcv", (int)em_Ds_VirRemote_Mix_Rcv },
	{ "em_Ds_VirRemote_End", (int)em_Ds_VirRemote_End },
	{ "em_Ds_MT_ASnd_0", (int)em_Ds_MT_ASnd_0 },
	{ "em_Ds_MT_ASnd_1", (int)em_Ds_MT_ASnd_1 },
	{ "em_Ds_MT_ASnd_2", (int)em_Ds_MT_ASnd_2 },
	{ "em_Ds_MT_ASnd_3", (int)em_Ds_MT_ASnd_3 },
	{ "em_Ds_MT_ARcv_0", (int)em_Ds_MT_ARcv_0 },
	{ "em_Ds_MT_ARcv_1", (int)em_Ds_MT_ARcv_1 },
	{ "em_Ds_MT_ARcv_2", (int)em_Ds_MT_ARcv_2 },
	{ "em_Ds_MT_ARcv_3", (int)em_Ds_MT_ARcv_3 },
	{ "em_Ds_MT_VSnd_0", (int)em_Ds_MT_VSnd_0 },
	{ "em_Ds_MT_VSnd_1", (int)em_Ds_MT_VSnd_1 },
	{ "em_Ds_MT_VSnd_2", (int)em_Ds_MT_VSnd_2 },
	{ "em_Ds_MT_VSnd_3", (int)em_Ds_MT_VSnd_3 },
	{ "em_Ds_MT_VRcv_0", (int)em_Ds_MT_VRcv_0 },
	{ "em_Ds_MT_VRcv_1", (int)em_Ds_MT_VRcv_1 },
	{ "em_Ds_MT_VRcv_2", (int)em_Ds_MT_VRcv_2 },
	{ "em_Ds_MT_VRcv_3", (int)em_Ds_MT_VRcv_3 },
	{ "em_Ds_MT_VSnd_0_Mini_0", (int)em_Ds_MT_VSnd_0_Mini_0 },
	{ "em_Ds_MT_VSnd_1_Mini_0", (int)em_Ds_MT_VSnd_1_Mini_0 },
	{ "em_Ds_MT_VSnd_2_Mini_0", (int)em_Ds_MT_VSnd_2_Mini_0 },
	{ "em_Ds_MT_VRcv_0_Mini_0", (int)em_Ds_MT_VRcv_0_Mini_0 },
	{ "em_Ds_MT_VRcv_0_Mini_1", (int)em_Ds_MT_VRcv_0_Mini_1 },
	{ "em_Ds_MT_VRcv_1_Mini_0", (int)em_Ds_MT_VRcv_1_Mini_0 },
	{ "em_Ds_MT_VRcv_1_Mini_1", (int)em_Ds_MT_VRcv_1_Mini_1 },
	{ "em_Ds_MT_VRcv_2_Mini_0", (int)em_Ds_MT_VRcv_2_Mini_0 },
	{ "em_Ds_MT_VRcv_2_Mini_1", (int)em_Ds_MT_VRcv_2_Mini_1 },
	{ "em_Ds_Mt_Mix_ASnd", (int)em_Ds_Mt_Mix_ASnd },
	{ "em_Ds_VirMt_ASnd_0", (int)em_Ds_VirMt_ASnd_0 },
	{ "em_Ds_VirMt_ASnd_1", (int)em_Ds_VirMt_ASnd_1 },
	{ "em_Ds_VirMt_ASnd_2", (int)em_Ds_VirMt_ASnd_2 },
	{ "em_Ds_VirMt_ARcv_0", (int)em_Ds_VirMt_ARcv_0 },
	{ "em_Ds_VirMt_ARcv_1", (int)em_Ds_VirMt_ARcv_1 },
	{ "em_Ds_VirMt_ARcv_2", (int)em_Ds_VirMt_ARcv_2 },
	{ "em_Ds_VirMt_VSnd_0", (int)em_Ds_VirMt_VSnd_0 },
	{ "em_Ds_VirMt_VSnd_1", (int)em_Ds_VirMt_VSnd_1 },
	{ "em_Ds_VirMt_VSnd_2", (int)em_Ds_VirMt_VSnd_2 },
	{ "em_Ds_VirMt_VRcv_0", (int)em_Ds_VirMt_VRcv_0 },
	{ "em_Ds_VirMt_VRcv_1", (int)em_Ds_VirMt_VRcv_1 },
	{ "em_Ds_VirMt_VRcv_2", (int)em_Ds_VirMt_VRcv_2 },
	{ "em_Ds_VirMt_VSnd_0_Mini_0", (int)em_Ds_VirMt_VSnd_0_Mini_0 },
	{ "em_Ds_VirMt_VSnd_0_Mini_1", (int)em_Ds_VirMt_VSnd_0_Mini_1 },
	{ "em_Ds_VirMt_VSnd_1_Mini_0", (int)em_Ds_VirMt_VSnd_1_Mini_0 },
	{ "em_Ds_VirMt_VSnd_1_Mini_1", (int)em_Ds_VirMt_VSnd_1_Mini_1 },
	{ "em_Ds_VirMt_VSnd_2_Mini_0", (int)em_Ds_VirMt_VSnd_2_Mini_0 },
	{ "em_Ds_VirMt_VSnd_2_Mini_1", (int)em_Ds_VirMt_VSnd_2_Mini_1 },
	{ "em_Ds_VirMt_VRcv_0_Mini_0", (int)em_Ds_VirMt_VRcv_0_Mini_0 },
	{ "em_Ds_VirMt_VRcv_0_Mini_1", (int)em_Ds_VirMt_VRcv_0_Mini_1 },
	{ "em_Ds_VirMt_VRcv_1_Mini_0", (int)em_Ds_VirMt_VRcv_1_Mini_0 },
	{ "em_Ds_VirMt_VRcv_1_Mini_1", (int)em_Ds_VirMt_VRcv_1_Mini_1 },
	{ "em_Ds_VirMt_VRcv_2_Mini_0", (int)em_Ds_VirMt_VRcv_2_Mini_0 },
	{ "em_Ds_VirMt_VRcv_2_Mini_1", (int)em_Ds_VirMt_VRcv_2_Mini_1 },
	{ "em_Ds_VirMt_Mix_ASnd", (int)em_Ds_VirMt_Mix_ASnd },
	{ "em_Ds_Mt_End", (int)em_Ds_Mt_End },
	{ "em_Ds_Innerspeaker_ASnd", (int)em_Ds_Innerspeaker_ASnd },
	{ "em_Ds_Innerspeaker_VSnd", (int)em_Ds_Innerspeaker_VSnd },
	{ "em_Ds_Innerspeaker_End", (int)em_Ds_Innerspeaker_End },
	{ "em_Ds_VirDual_ASnd", (int)em_Ds_VirDual_ASnd },
	{ "em_Ds_VirDual_VSnd", (int)em_Ds_VirDual_VSnd },
	{ "em_Ds_VirDual_ARcv", (int)em_Ds_VirDual_ARcv },
	{ "em_Ds_VirDual_VRcv", (int)em_Ds_VirDual_VRcv },
	{ "em_Ds_VirDual_Adapter_VSnd", (int)em_Ds_VirDual_Adapter_VSnd },
	{ "em_Ds_MtDual_Adapter", (int)em_Ds_MtDual_Adapter },
	{ "em_Ds_Dual_End", (int)em_Ds_Dual_End },
	{ "em_Ds_Addr_Type_End", (int)em_Ds_Addr_Type_End },
	{ "em_DsOtherType_Begin", (int)em_DsOtherType_Begin },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_0", (int)em_Ds_VirMtToInnerspeaker_ASnd_0 },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_1", (int)em_Ds_VirMtToInnerspeaker_ASnd_1 },
	{ "em_Ds_VirMtToInnerspeaker_ASnd_2", (int)em_Ds_VirMtToInnerspeaker_ASnd_2 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_0", (int)em_Ds_VirMtToInnerspeaker_VSnd_0 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_1", (int)em_Ds_VirMtToInnerspeaker_VSnd_1 },
	{ "em_Ds_VirMtToInnerspeaker_VSnd_2", (int)em_Ds_VirMtToInnerspeaker_VSnd_2 },
	{ "em_Ds_DualRcvToVirMt_Rcv_0", (int)em_Ds_DualRcvToVirMt_Rcv_0 },
	{ "em_Ds_DualRcvToVirMt_Rcv_1", (int)em_Ds_DualRcvToVirMt_Rcv_1 },
	{ "em_Ds_DualRcvToVirMt_Rcv_2", (int)em_Ds_DualRcvToVirMt_Rcv_2 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_0", (int)em_Ds_VirRemoteToVirMt_ASnd_0 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_1", (int)em_Ds_VirRemoteToVirMt_ASnd_1 },
	{ "em_Ds_VirRemoteToVirMt_ASnd_2", (int)em_Ds_VirRemoteToVirMt_ASnd_2 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_0", (int)em_Ds_VirRemoteToVirMt_VSnd_0 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_1", (int)em_Ds_VirRemoteToVirMt_VSnd_1 },
	{ "em_Ds_VirRemoteToVirMt_VSnd_2", (int)em_Ds_VirRemoteToVirMt_VSnd_2 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_0", (int)em_Ds_VirRemoteToVirMt_ARcv_0 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_1", (int)em_Ds_VirRemoteToVirMt_ARcv_1 },
	{ "em_Ds_VirRemoteToVirMt_ARcv_2", (int)em_Ds_VirRemoteToVirMt_ARcv_2 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0", (int)em_Ds_VirRemoteToVirMt_VRcv_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1", (int)em_Ds_VirRemoteToVirMt_VRcv_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2", (int)em_Ds_VirRemoteToVirMt_VRcv_2 },
	{ "em_Ds_VirDualNB_VRcv", (int)em_Ds_VirDualNB_VRcv },
	{ "em_Ds_VirDualNB_VSnd", (int)em_Ds_VirDualNB_VSnd },
	{ "em_Ds_VirDualNB_ARcv", (int)em_Ds_VirDualNB_ARcv },
	{ "em_Ds_VirDualNB_ASnd", (int)em_Ds_VirDualNB_ASnd },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0", (int)em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0 },
	{ "em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1", (int)em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1 },
	{ "em_Ds_VirRemoteToVirMt_Mix_ASnd", (int)em_Ds_VirRemoteToVirMt_Mix_ASnd },
	{ "em_Ds_VirRemoteToPad_VSnd", (int)em_Ds_VirRemoteToPad_VSnd },
	{ "em_Ds_VirRemoteToPad_ASnd", (int)em_Ds_VirRemoteToPad_ASnd },
	{ "em_Ds_VirDual_ARcv_Pad_Begin", (int)em_Ds_VirDual_ARcv_Pad_Begin },
	{ "em_Ds_VirDual_ARcv_Pad_End", (int)em_Ds_VirDual_ARcv_Pad_End },
	{ "em_Ds_VirDual_VRcv_Pad_Begin", (int)em_Ds_VirDual_VRcv_Pad_Begin },
	{ "em_Ds_VirDual_VRcv_Pad_End", (int)em_Ds_VirDual_VRcv_Pad_End },
	{ "em_Ds_VirDual_VSnd_Pad", (int)em_Ds_VirDual_VSnd_Pad },
	{ "em_Ds_Debug", (int)em_Ds_Debug },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnAudioMixIDDescript[]={
	{ "emCnAMix_INVALID", (int)emCnAMix_INVALID },
	{ "emCnAMix_Speaker", (int)emCnAMix_Speaker },
	{ "emCnAMix_Dual", (int)emCnAMix_Dual },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetRegInfoTypeDescript[]={
	{ "emGetRegInfoType_CNS", (int)emGetRegInfoType_CNS },
	{ "emGetRegInfoType_UMS", (int)emGetRegInfoType_UMS },
	{ "emGetRegInfoType_ALL", (int)emGetRegInfoType_ALL },
	{ "emGetRegInfoType_MT", (int)emGetRegInfoType_MT },
	{ "emGetRefInfoType_MCU", (int)emGetRefInfoType_MCU },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmGetRegInfoOprDescript[]={
	{ "emGetRegInfoOpr_Update", (int)emGetRegInfoOpr_Update },
	{ "emGetRegInfoOpr_Add", (int)emGetRegInfoOpr_Add },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChanTypeDescript[]={
	{ "emTPChanNone", (int)emTPChanNone },
	{ "emTPChanRecv", (int)emTPChanRecv },
	{ "emTPChanSend", (int)emTPChanSend },
	{ "emTPChanSendRecv", (int)emTPChanSendRecv },
	{ "emTPChanTypeEnd", (int)emTPChanTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAACSampleFreqDescript[]={
	{ "emTPFs96000", (int)emTPFs96000 },
	{ "emTPFs88200", (int)emTPFs88200 },
	{ "emTPFs64000", (int)emTPFs64000 },
	{ "emTPFs48000", (int)emTPFs48000 },
	{ "emTPFs44100", (int)emTPFs44100 },
	{ "emTPFs32000", (int)emTPFs32000 },
	{ "emTPFs24000", (int)emTPFs24000 },
	{ "emTPFs22050", (int)emTPFs22050 },
	{ "emTPFs16000", (int)emTPFs16000 },
	{ "emTPFs12000", (int)emTPFs12000 },
	{ "emTPFs11025", (int)emTPFs11025 },
	{ "emTPFs8000", (int)emTPFs8000 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPG7221RateDescript[]={
	{ "emTPG7221Rate24", (int)emTPG7221Rate24 },
	{ "emTPG7221Rate32", (int)emTPG7221Rate32 },
	{ "emTPG7221Rate48", (int)emTPG7221Rate48 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAACChnlCfgDescript[]={
	{ "emTPChnlCust", (int)emTPChnlCust },
	{ "emTPChnl1", (int)emTPChnl1 },
	{ "emTPChnl2", (int)emTPChnl2 },
	{ "emTPChnl3", (int)emTPChnl3 },
	{ "emTPChnl4", (int)emTPChnl4 },
	{ "emTPChnl5", (int)emTPChnl5 },
	{ "emTPChnl5dot1", (int)emTPChnl5dot1 },
	{ "emTPChnl7dot1", (int)emTPChnl7dot1 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPTpApplySpeakerRetDescript[]={
	{ "emTP_ApplySpeaker_Success", (int)emTP_ApplySpeaker_Success },
	{ "emTP_ApplySpeaker_ConfUnExist", (int)emTP_ApplySpeaker_ConfUnExist },
	{ "emTP_ApplySpeaker_EpIDError", (int)emTP_ApplySpeaker_EpIDError },
	{ "emTP_ApplySpeaker_EpStateError", (int)emTP_ApplySpeaker_EpStateError },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPChanSubTypeDescript[]={
	{ "EmTPChanSubType_Normal", (int)EmTPChanSubType_Normal },
	{ "EmTPChanSubType_Mini", (int)EmTPChanSubType_Mini },
	{ "EmTPChanSubType_Dual", (int)EmTPChanSubType_Dual },
	{ "EmTPChanSubType_AMix", (int)EmTPChanSubType_AMix },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMakeCallTypeDescript[]={
	{ "em_sip_call_type", (int)em_sip_call_type },
	{ "em_323_call_type", (int)em_323_call_type },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpRegTypeDescript[]={
	{ "em_sip_reg", (int)em_sip_reg },
	{ "em_323_reg", (int)em_323_reg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisListOprTypeDescript[]={
	{ "em_DisListOpr_Add", (int)em_DisListOpr_Add },
	{ "em_DisListOpr_Del", (int)em_DisListOpr_Del },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDisListOprResltDescript[]={
	{ "em_DisListOpr_Sucess", (int)em_DisListOpr_Sucess },
	{ "em_DisListOpr_Fail", (int)em_DisListOpr_Fail },
	{ "em_DisListOpr_Reject", (int)em_DisListOpr_Reject },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaTypeDescript[]={
	{ "emVgaTypeDocCamera", (int)emVgaTypeDocCamera },
	{ "emVgaType001", (int)emVgaType001 },
	{ "emVgaType002", (int)emVgaType002 },
	{ "emVgaType003", (int)emVgaType003 },
	{ "emVgaType004", (int)emVgaType004 },
	{ "emVgaType005", (int)emVgaType005 },
	{ "emVgaType006", (int)emVgaType006 },
	{ "emVgaTypeInValid", (int)emVgaTypeInValid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualInputTypeDescript[]={
	{ "emDualInputDocCamera", (int)emDualInputDocCamera },
	{ "emDualInput001", (int)emDualInput001 },
	{ "emDualInput002", (int)emDualInput002 },
	{ "emDualInput003", (int)emDualInput003 },
	{ "emDualInput004", (int)emDualInput004 },
	{ "emDualInput005", (int)emDualInput005 },
	{ "emDualInput006", (int)emDualInput006 },
	{ "emDualInputInvalid", (int)emDualInputInvalid },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmDualOutputTypeDescript[]={
	{ "emDualOutputInvalid", (int)emDualOutputInvalid },
	{ "emDualOutput001", (int)emDualOutput001 },
	{ "emDualOutput002", (int)emDualOutput002 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaSwitchResultDescript[]={
	{ "em_VgaSwitchInvalid", (int)em_VgaSwitchInvalid },
	{ "em_VgaSwitchFail", (int)em_VgaSwitchFail },
	{ "em_VgaSwitchSucc", (int)em_VgaSwitchSucc },
	{ "em_CurVgaNoSignal", (int)em_CurVgaNoSignal },
	{ "em_TpNoDual", (int)em_TpNoDual },
	{ "em_VgaBusying", (int)em_VgaBusying },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmVgaSwitchReasonDescript[]={
	{ "em_SwitchVgaInvalid", (int)em_SwitchVgaInvalid },
	{ "em_SwitchDemoVga", (int)em_SwitchDemoVga },
	{ "em_SwitchCurVga", (int)em_SwitchCurVga },
	{ "em_ResetVga", (int)em_ResetVga },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnStateDescript[]={
	{ "emCnsRunning", (int)emCnsRunning },
	{ "emCnsSleep", (int)emCnsSleep },
	{ "emCnsPoweroff", (int)emCnsPoweroff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCapSignDescript[]={
	{ "emTPCapBig", (int)emTPCapBig },
	{ "emTPCapLeft", (int)emTPCapLeft },
	{ "emTPCapRight", (int)emTPCapRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmSwitchStateDescript[]={
	{ "emStateON", (int)emStateON },
	{ "emStateOFF", (int)emStateOFF },
	{ "emStateStandby", (int)emStateStandby },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpBoardRetDescript[]={
	{ "emTP_Board_UnKonw", (int)emTP_Board_UnKonw },
	{ "emTP_Board_AddSuccess", (int)emTP_Board_AddSuccess },
	{ "emTP_Board_DelSuccess", (int)emTP_Board_DelSuccess },
	{ "emTP_Board_ModifySuccess", (int)emTP_Board_ModifySuccess },
	{ "emTP_Board_MaxNum", (int)emTP_Board_MaxNum },
	{ "emTP_Board_Mode_AddSuccess", (int)emTP_Board_Mode_AddSuccess },
	{ "emTP_Board_Mode_DelSuccess", (int)emTP_Board_Mode_DelSuccess },
	{ "emTP_Board_Mode_ModifySuccess", (int)emTP_Board_Mode_ModifySuccess },
	{ "emTP_Board_UnFind", (int)emTP_Board_UnFind },
	{ "emTP_Board_UnKnowLoc", (int)emTP_Board_UnKnowLoc },
	{ "emTP_Board_Repeat", (int)emTP_Board_Repeat },
	{ "emTP_BrdType_NotMatch_EqpType", (int)emTP_BrdType_NotMatch_EqpType },
	{ "emTP_BrdMode_Repeat", (int)emTP_BrdMode_Repeat },
	{ "emTP_BrdMode_MaxNum", (int)emTP_BrdMode_MaxNum },
	{ "emTP_BrdMode_NoConfig", (int)emTP_BrdMode_NoConfig },
	{ "emTp_BrdMode_Resource_Full", (int)emTp_BrdMode_Resource_Full },
	{ "emTp_BrdMode_AudMix_MaxNum", (int)emTp_BrdMode_AudMix_MaxNum },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduOutPortDescript[]={
	{ "em_hdu_outport_YPbPr", (int)em_hdu_outport_YPbPr },
	{ "em_hdu_outport_VGA", (int)em_hdu_outport_VGA },
	{ "em_hdu_outport_DVI", (int)em_hdu_outport_DVI },
	{ "em_hdu_outport_HDMI", (int)em_hdu_outport_HDMI },
	{ "em_hdu_outport_unknow", (int)em_hdu_outport_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduZoomRateDescript[]={
	{ "em_hdu_zoomrate_4_3", (int)em_hdu_zoomrate_4_3 },
	{ "em_hdu_zoomrate_16_9", (int)em_hdu_zoomrate_16_9 },
	{ "em_hdu_zoomrate_unknow", (int)em_hdu_zoomrate_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduOutModeDescript[]={
	{ "em_hdu_outmode_YPbPr_1080P_24fps", (int)em_hdu_outmode_YPbPr_1080P_24fps },
	{ "em_hdu_outmode_YPbPr_1080P_25fps", (int)em_hdu_outmode_YPbPr_1080P_25fps },
	{ "em_hdu_outmode_YPbPr_1080P_30fps", (int)em_hdu_outmode_YPbPr_1080P_30fps },
	{ "em_hdu_outmode_YPbPr_1080P_50fps", (int)em_hdu_outmode_YPbPr_1080P_50fps },
	{ "em_hdu_outmode_YPbPr_1080P_60fps", (int)em_hdu_outmode_YPbPr_1080P_60fps },
	{ "em_hdu_outmode_YPbPr_1080i_50HZ", (int)em_hdu_outmode_YPbPr_1080i_50HZ },
	{ "em_hdu_outmode_YPbPr_1080i_60HZ", (int)em_hdu_outmode_YPbPr_1080i_60HZ },
	{ "em_hdu_outmode_YPbPr_720P_60fps", (int)em_hdu_outmode_YPbPr_720P_60fps },
	{ "em_hdu_outmode_YPbPr_576i_50HZ", (int)em_hdu_outmode_YPbPr_576i_50HZ },
	{ "em_hdu_outmode_YPbPr_480i_60HZ", (int)em_hdu_outmode_YPbPr_480i_60HZ },
	{ "em_hdu_outmode_VGA_SXGA_60HZ", (int)em_hdu_outmode_VGA_SXGA_60HZ },
	{ "em_hdu_outmode_VGA_XGA_60HZ", (int)em_hdu_outmode_VGA_XGA_60HZ },
	{ "em_hdu_outmode_VGA_XGA_75HZ", (int)em_hdu_outmode_VGA_XGA_75HZ },
	{ "em_hdu_outmode_VGA_SVGA_60HZ", (int)em_hdu_outmode_VGA_SVGA_60HZ },
	{ "em_hdu_outmode_VGA_SVGA_75HZ", (int)em_hdu_outmode_VGA_SVGA_75HZ },
	{ "em_hdu_outmode_VGA_VGA_60HZ", (int)em_hdu_outmode_VGA_VGA_60HZ },
	{ "em_hdu_outmode_VGA_VGA_75HZ", (int)em_hdu_outmode_VGA_VGA_75HZ },
	{ "em_hdu_outmode_VGA_SXGA_75HZ", (int)em_hdu_outmode_VGA_SXGA_75HZ },
	{ "em_hdu_outmode_YPbPr_720P_50fps", (int)em_hdu_outmode_YPbPr_720P_50fps },
	{ "em_hdu_outmode_VGA_WXGA_1280_768_60HZ", (int)em_hdu_outmode_VGA_WXGA_1280_768_60HZ },
	{ "em_hdu_outmode_VGA_WXGA_1280_800_60HZ", (int)em_hdu_outmode_VGA_WXGA_1280_800_60HZ },
	{ "em_hdu_outmode_VGA_WSXGA_60HZ", (int)em_hdu_outmode_VGA_WSXGA_60HZ },
	{ "em_hdu_outmode_VGA_SXGAPlus_60HZ", (int)em_hdu_outmode_VGA_SXGAPlus_60HZ },
	{ "em_hdu_outmode_VGA_UXGA_60HZ", (int)em_hdu_outmode_VGA_UXGA_60HZ },
	{ "em_hdu_outmode_YPbPr_1080P_29970HZ", (int)em_hdu_outmode_YPbPr_1080P_29970HZ },
	{ "em_hdu_outmode_YPbPr_1080P_59940HZ", (int)em_hdu_outmode_YPbPr_1080P_59940HZ },
	{ "em_hdu_outmode_WXGA_1280_800_75HZ", (int)em_hdu_outmode_WXGA_1280_800_75HZ },
	{ "em_hdu_outmode_unknow", (int)em_hdu_outmode_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmHduShowModeDescript[]={
	{ "em_hdu_showmode_NONGEOMETRIC", (int)em_hdu_showmode_NONGEOMETRIC },
	{ "em_hdu_showmode_CUTEDGEGEOME", (int)em_hdu_showmode_CUTEDGEGEOME },
	{ "em_hdu_showmode_BLACKEDGEGEOME", (int)em_hdu_showmode_BLACKEDGEGEOME },
	{ "em_hdu_showmode_unknow", (int)em_hdu_showmode_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyNMServerRetDescript[]={
	{ "em_nmserver_modify_success", (int)em_nmserver_modify_success },
	{ "em_nmserver_resource_full", (int)em_nmserver_resource_full },
	{ "em_nmserver_invalid_handle", (int)em_nmserver_invalid_handle },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyVcrRetDescript[]={
	{ "em_vcr_modify_success", (int)em_vcr_modify_success },
	{ "em_vcr_invalid", (int)em_vcr_invalid },
	{ "em_vcr_full", (int)em_vcr_full },
	{ "em_vcr_no_exist", (int)em_vcr_no_exist },
	{ "em_vcr_exist", (int)em_vcr_exist },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmModifyHduRetDescript[]={
	{ "em_hdu_modify_success", (int)em_hdu_modify_success },
	{ "em_hdu_invalid_index", (int)em_hdu_invalid_index },
	{ "em_hdu_brd_no_cfg", (int)em_hdu_brd_no_cfg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUpdateHduRetDescript[]={
	{ "em_hdu_update_success", (int)em_hdu_update_success },
	{ "em_hdu_update_ing", (int)em_hdu_update_ing },
	{ "em_hdu_update_unreg", (int)em_hdu_update_unreg },
	{ "em_hdu_update_unknow", (int)em_hdu_update_unknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMPCodecDescript[]={
	{ "emMPCodec1", (int)emMPCodec1 },
	{ "emMPCodec2", (int)emMPCodec2 },
	{ "emMPCodec3", (int)emMPCodec3 },
	{ "emMPDualCodec", (int)emMPDualCodec },
	{ "emEndMPCodec", (int)emEndMPCodec },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDAudPortInDescript[]={
	{ "emTPAudInCanon1", (int)emTPAudInCanon1 },
	{ "emTPAudInCanon2", (int)emTPAudInCanon2 },
	{ "emTPAudInCanon3", (int)emTPAudInCanon3 },
	{ "emTPAudInCanon4", (int)emTPAudInCanon4 },
	{ "emTPAudInCanon5", (int)emTPAudInCanon5 },
	{ "emTPAudInCanon6", (int)emTPAudInCanon6 },
	{ "emTPAudInCanon7", (int)emTPAudInCanon7 },
	{ "emTPAudInCanon8", (int)emTPAudInCanon8 },
	{ "emTPAudInCanon9", (int)emTPAudInCanon9 },
	{ "emTPAudInCanon10", (int)emTPAudInCanon10 },
	{ "emTPAudInDigit0", (int)emTPAudInDigit0 },
	{ "emTPAudInDigit1", (int)emTPAudInDigit1 },
	{ "emTPAudInDigit2", (int)emTPAudInDigit2 },
	{ "emTPAudInEnd", (int)emTPAudInEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDDualAudPortInDescript[]={
	{ "emTPAudInTrs1", (int)emTPAudInTrs1 },
	{ "emTPAudInTrs2", (int)emTPAudInTrs2 },
	{ "emTPAudInTrs3", (int)emTPAudInTrs3 },
	{ "emTPAudInTrs4", (int)emTPAudInTrs4 },
	{ "emTPAudInRcaL", (int)emTPAudInRcaL },
	{ "emTPAudInRcaR", (int)emTPAudInRcaR },
	{ "emTPDualAudInEnd", (int)emTPDualAudInEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHDAudPortOutDescript[]={
	{ "emTPAudOutCCanon1", (int)emTPAudOutCCanon1 },
	{ "emTPAudOutCCanon2", (int)emTPAudOutCCanon2 },
	{ "emTPAudOutCCanon3", (int)emTPAudOutCCanon3 },
	{ "emTPAudOutCCanon4", (int)emTPAudOutCCanon4 },
	{ "emTPAudOutCCanon5", (int)emTPAudOutCCanon5 },
	{ "emTPAudOutReproducer", (int)emTPAudOutReproducer },
	{ "emTPAudOutEnd", (int)emTPAudOutEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtVideoPortDescript[]={
	{ "emTPC1Vid", (int)emTPC1Vid },
	{ "emTPC2Vid", (int)emTPC2Vid },
	{ "emTPC3Vid", (int)emTPC3Vid },
	{ "emTPC4Vid", (int)emTPC4Vid },
	{ "emTPC5Vid", (int)emTPC5Vid },
	{ "emTPC6Vid", (int)emTPC6Vid },
	{ "emTPC7Vid", (int)emTPC7Vid },
	{ "emTPC8Vid", (int)emTPC8Vid },
	{ "emTPC9Vid", (int)emTPC9Vid },
	{ "emTPC10Vid", (int)emTPC10Vid },
	{ "emTPC11Vid", (int)emTPC11Vid },
	{ "emTPVidEnd", (int)emTPVidEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMtVideoOutPortDescript[]={
	{ "emTPC1OutVid", (int)emTPC1OutVid },
	{ "emTPC2OutVid", (int)emTPC2OutVid },
	{ "emTPC3OutVid", (int)emTPC3OutVid },
	{ "emTPC4OutVid", (int)emTPC4OutVid },
	{ "emTPC5OutVid", (int)emTPC5OutVid },
	{ "emTPVidOutEnd", (int)emTPVidOutEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAutoTestTypeDescript[]={
	{ "emTPAutoTestBegin", (int)emTPAutoTestBegin },
	{ "emTPAutoTestAudioLoopBackFunc", (int)emTPAutoTestAudioLoopBackFunc },
	{ "emTPAutoTestPriomVideoLoopBackFunc", (int)emTPAutoTestPriomVideoLoopBackFunc },
	{ "emTPAutoTestSecondVideoLoopBackFunc", (int)emTPAutoTestSecondVideoLoopBackFunc },
	{ "emTPAutoTestEnd", (int)emTPAutoTestEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHduRunStatusDescript[]={
	{ "emTPHduIdle", (int)emTPHduIdle },
	{ "emTPHduWaiting", (int)emTPHduWaiting },
	{ "emTPHduPlaying", (int)emTPHduPlaying },
	{ "emTPHduUnknow", (int)emTPHduUnknow },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLoudspeakerValDescript[]={
	{ "emTPLoudspeakerLow", (int)emTPLoudspeakerLow },
	{ "emTPLoudspeakerMiddle", (int)emTPLoudspeakerMiddle },
	{ "emTPLoudspeakerHigh", (int)emTPLoudspeakerHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFrameUnitTypeDescript[]={
	{ "emTPFrameSecond", (int)emTPFrameSecond },
	{ "emTPSecondFrame", (int)emTPSecondFrame },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPVideoStandardDescript[]={
	{ "emTPPAL", (int)emTPPAL },
	{ "emTPNTSC", (int)emTPNTSC },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLabelTypeDescript[]={
	{ "emTPLabelAuto", (int)emTPLabelAuto },
	{ "emTPLabelUserDef", (int)emTPLabelUserDef },
	{ "emTPLabelOff", (int)emTPLabelOff },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLabelPosTypeDescript[]={
	{ "emTPTopLeft", (int)emTPTopLeft },
	{ "emTPTopRight", (int)emTPTopRight },
	{ "emTPBottomLeft", (int)emTPBottomLeft },
	{ "emTPBottomRight", (int)emTPBottomRight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualVideoShowModeDescript[]={
	{ "emTPDualVideoOnSigleScreen", (int)emTPDualVideoOnSigleScreen },
	{ "emTPEachVideoOwnScreen", (int)emTPEachVideoOwnScreen },
	{ "emTPTripleVideoOnSingleScn", (int)emTPTripleVideoOnSingleScn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDisplayRatioDescript[]={
	{ "emTPDR4to3", (int)emTPDR4to3 },
	{ "emTPDR16to9", (int)emTPDR16to9 },
	{ "emTPDRAuto", (int)emTPDRAuto },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFecModeTypeDescript[]={
	{ "emTPFECTYPENONE", (int)emTPFECTYPENONE },
	{ "emTPFECTYPERAID5", (int)emTPFECTYPERAID5 },
	{ "emTPFECTYPERAID5INTERLEAVE", (int)emTPFECTYPERAID5INTERLEAVE },
	{ "emTPFECTYPERAID6", (int)emTPFECTYPERAID6 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPNetTypeDescript[]={
	{ "emTPInternet", (int)emTPInternet },
	{ "emTPSpecial", (int)emTPSpecial },
	{ "emTPVPN", (int)emTPVPN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPEqualizerRateDescript[]={
	{ "emTPRate100", (int)emTPRate100 },
	{ "emTPRate200", (int)emTPRate200 },
	{ "emTPRate400", (int)emTPRate400 },
	{ "emTPRate600", (int)emTPRate600 },
	{ "emTPRate1k", (int)emTPRate1k },
	{ "emTPRate3k", (int)emTPRate3k },
	{ "emTPRate6k", (int)emTPRate6k },
	{ "emTPRate12k", (int)emTPRate12k },
	{ "emTPRate14k", (int)emTPRate14k },
	{ "emTPRate16k", (int)emTPRate16k },
	{ "emTPRateend", (int)emTPRateend },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPPIPModeDescript[]={
	{ "TP_VIDEO_PIPMODE_IDLE", (int)TP_VIDEO_PIPMODE_IDLE },
	{ "TP_VIDEO_PIPMODE_LOOP", (int)TP_VIDEO_PIPMODE_LOOP },
	{ "TP_VIDEO_PIPMODE_ONE_LOCAL", (int)TP_VIDEO_PIPMODE_ONE_LOCAL },
	{ "TP_VIDEO_PIPMODE_ONE_OTHER", (int)TP_VIDEO_PIPMODE_ONE_OTHER },
	{ "TP_VIDEO_PIPMODE_THREE_L_ONEBIG", (int)TP_VIDEO_PIPMODE_THREE_L_ONEBIG },
	{ "TP_VIDEO_PIPMODE_THREE_M_ONEBIG", (int)TP_VIDEO_PIPMODE_THREE_M_ONEBIG },
	{ "TP_VIDEO_PIPMODE_THREE_R_ONEBIG", (int)TP_VIDEO_PIPMODE_THREE_R_ONEBIG },
	{ "TP_VIDEO_PIPMODE_ONE_AUX_LOCAL", (int)TP_VIDEO_PIPMODE_ONE_AUX_LOCAL },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDVIModeDescript[]={
	{ "TP_DVI_MODE_HDMI", (int)TP_DVI_MODE_HDMI },
	{ "TP_DVI_MODE_VGA", (int)TP_DVI_MODE_VGA },
	{ "TP_DVI_MODE_DVI", (int)TP_DVI_MODE_DVI },
	{ "TP_DVI_MODE_Ypbpr", (int)TP_DVI_MODE_Ypbpr },
	{ "TP_DVI_MODE_INVALID", (int)TP_DVI_MODE_INVALID },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMCModeDescript[]={
	{ "emTPMcSpeech", (int)emTPMcSpeech },
	{ "emTPMcDiscuss", (int)emTPMcDiscuss },
	{ "emTPMcModeEnd", (int)emTPMcModeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmCnsUpdateStateDescript[]={
	{ "emCnsIdle", (int)emCnsIdle },
	{ "emCnsDownloading", (int)emCnsDownloading },
	{ "emCnsDownloaded", (int)emCnsDownloaded },
	{ "emCnsUpdating", (int)emCnsUpdating },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCnLoginUpdateRetDescript[]={
	{ "emTPCnLoginUpdateInvalid", (int)emTPCnLoginUpdateInvalid },
	{ "emTPCnLoginUpdateFail", (int)emTPCnLoginUpdateFail },
	{ "emTPCnLoginUpdateSuccess", (int)emTPCnLoginUpdateSuccess },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFileSrvUsedVersionDescript[]={
	{ "emTPFileSrvUsedVersion1", (int)emTPFileSrvUsedVersion1 },
	{ "emTPFileSrvUsedVersion2", (int)emTPFileSrvUsedVersion2 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFileSrvFileTypeDescript[]={
	{ "emTPFileSrvFileTypeUnknown", (int)emTPFileSrvFileTypeUnknown },
	{ "emTPFileSrvFileTypeService", (int)emTPFileSrvFileTypeService },
	{ "emTPFileSrvFileTypeConsole", (int)emTPFileSrvFileTypeConsole },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPOSTypeDescript[]={
	{ "emTPWindows", (int)emTPWindows },
	{ "emTPLinux", (int)emTPLinux },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMPAudEncCodecDescript[]={
	{ "emMPAudEncCodec1", (int)emMPAudEncCodec1 },
	{ "emMPAudEncCodec2", (int)emMPAudEncCodec2 },
	{ "emMPAudEncCodec3", (int)emMPAudEncCodec3 },
	{ "emMPAudEncDualCodec", (int)emMPAudEncDualCodec },
	{ "emMPAudEncMixCodec", (int)emMPAudEncMixCodec },
	{ "emEndMPAudEncCodec", (int)emEndMPAudEncCodec },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmToolTypeDescript[]={
	{ "emMainTerabceTool", (int)emMainTerabceTool },
	{ "emProTestTool", (int)emProTestTool },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmProducetestTypeDescript[]={
	{ "emProducetestTypeBegin", (int)emProducetestTypeBegin },
	{ "emTestVideoMAIN1InOut", (int)emTestVideoMAIN1InOut },
	{ "emTestVideoMAIN2InOut", (int)emTestVideoMAIN2InOut },
	{ "emTestVideoMAIN3InOut", (int)emTestVideoMAIN3InOut },
	{ "emTestVideoSUB1InMAIN3AUX12Out", (int)emTestVideoSUB1InMAIN3AUX12Out },
	{ "emTestDualSUB2InTurnHDMIAUX1Out", (int)emTestDualSUB2InTurnHDMIAUX1Out },
	{ "emTestDualAUX1InTurnHDMIAUX1Out", (int)emTestDualAUX1InTurnHDMIAUX1Out },
	{ "emTestDualAUX2InTurnHDMIAUX1Out", (int)emTestDualAUX2InTurnHDMIAUX1Out },
	{ "emTestDualAUX3InTurnHDMIAUX1Out", (int)emTestDualAUX3InTurnHDMIAUX1Out },
	{ "emTestDualAUX4InTurnHDMIAUX2Out", (int)emTestDualAUX4InTurnHDMIAUX2Out },
	{ "emTestDualAUX5InTurnHDMIAUX2Out", (int)emTestDualAUX5InTurnHDMIAUX2Out },
	{ "emTestDualAUX6InTurnHDMIAUX2Out", (int)emTestDualAUX6InTurnHDMIAUX2Out },
	{ "emTestDualSUB2InTurnVGAAUX1Out", (int)emTestDualSUB2InTurnVGAAUX1Out },
	{ "emTestDualAUX1InTurnVGAAUX1Out", (int)emTestDualAUX1InTurnVGAAUX1Out },
	{ "emTestDualAUX2InTurnVGAAUX1Out", (int)emTestDualAUX2InTurnVGAAUX1Out },
	{ "emTestDualAUX3InTurnVGAAUX1Out", (int)emTestDualAUX3InTurnVGAAUX1Out },
	{ "emTestDualAUX4InTurnVGAAUX2Out", (int)emTestDualAUX4InTurnVGAAUX2Out },
	{ "emTestDualAUX5InTurnVGAAUX2Out", (int)emTestDualAUX5InTurnVGAAUX2Out },
	{ "emTestDualAUX6InTurnVGAAUX2Out", (int)emTestDualAUX6InTurnVGAAUX2Out },
	{ "emTestAudioMIC1InMAIN1Out", (int)emTestAudioMIC1InMAIN1Out },
	{ "emTestAudioMIC2InMAIN2Out", (int)emTestAudioMIC2InMAIN2Out },
	{ "emTestAudioMIC3InMAIN3Out", (int)emTestAudioMIC3InMAIN3Out },
	{ "emTestAudioCANNON1InMAIN1Out", (int)emTestAudioCANNON1InMAIN1Out },
	{ "emTestAudioCANNON2InMAIN1Out", (int)emTestAudioCANNON2InMAIN1Out },
	{ "emTestAudioCANNON3InMAIN1Out", (int)emTestAudioCANNON3InMAIN1Out },
	{ "emTestAudioCANNON4InMAIN2Out", (int)emTestAudioCANNON4InMAIN2Out },
	{ "emTestAudioCANNON5InMAIN2Out", (int)emTestAudioCANNON5InMAIN2Out },
	{ "emTestAudioCANNON6InMAIN2Out", (int)emTestAudioCANNON6InMAIN2Out },
	{ "emTestAudioCANNON7InMAIN3Out", (int)emTestAudioCANNON7InMAIN3Out },
	{ "emTestAudioCANNON8InMAIN3Out", (int)emTestAudioCANNON8InMAIN3Out },
	{ "emTestAudioCANNON9InMAIN3Out", (int)emTestAudioCANNON9InMAIN3Out },
	{ "emTestAudioCANNON10InMAIN2Out", (int)emTestAudioCANNON10InMAIN2Out },
	{ "emTestAudioAUX1InAUX1Out", (int)emTestAudioAUX1InAUX1Out },
	{ "emTestAudioAUX2InAUX1Out", (int)emTestAudioAUX2InAUX1Out },
	{ "emTestAudioAUX3InAUX1Out", (int)emTestAudioAUX3InAUX1Out },
	{ "emTestAudioAUX4InAUX2Out", (int)emTestAudioAUX4InAUX2Out },
	{ "emTestAudioAUX5InAUX2Out", (int)emTestAudioAUX5InAUX2Out },
	{ "emTestAudioAUX6InAUX2Out", (int)emTestAudioAUX6InAUX2Out },
	{ "emTestUSB1Func", (int)emTestUSB1Func },
	{ "emTestUSB2Func", (int)emTestUSB2Func },
	{ "emTestRTCFunc", (int)emTestRTCFunc },
	{ "emTestLightFunc", (int)emTestLightFunc },
	{ "emTestLAN1Func", (int)emTestLAN1Func },
	{ "emTestLAN2Func", (int)emTestLAN2Func },
	{ "emTestRS232LoopbackFunc", (int)emTestRS232LoopbackFunc },
	{ "emTestRS422LoopbackFunc", (int)emTestRS422LoopbackFunc },
	{ "emTestRS485LoopbackFunc", (int)emTestRS485LoopbackFunc },
	{ "emTestRS232ANDCOM1LoopbackFunc", (int)emTestRS232ANDCOM1LoopbackFunc },
	{ "emTestRS422ANDCOM2LoopbackFunc", (int)emTestRS422ANDCOM2LoopbackFunc },
	{ "emTestCOM3ANDCOM4LoopbackFunc", (int)emTestCOM3ANDCOM4LoopbackFunc },
	{ "emTestCOM5ANDCOM6LoopbackFunc", (int)emTestCOM5ANDCOM6LoopbackFunc },
	{ "emTestInfraredRecFunc", (int)emTestInfraredRecFunc },
	{ "emTestInfraredSendFunc", (int)emTestInfraredSendFunc },
	{ "emTestALMLoopBackFunc", (int)emTestALMLoopBackFunc },
	{ "emTestAudioInMain1OutCannon1In", (int)emTestAudioInMain1OutCannon1In },
	{ "emTestAudioInMain1OutCannon2In", (int)emTestAudioInMain1OutCannon2In },
	{ "emTestAudioInMain1OutCannon3In", (int)emTestAudioInMain1OutCannon3In },
	{ "emTestAudioInMain1OutCannon4In", (int)emTestAudioInMain1OutCannon4In },
	{ "emTestAudioInMain1OutCannon5In", (int)emTestAudioInMain1OutCannon5In },
	{ "emTestAudioInMain1OutCannon6In", (int)emTestAudioInMain1OutCannon6In },
	{ "emTestAudioInMain1OutCannon7In", (int)emTestAudioInMain1OutCannon7In },
	{ "emTestAudioInMain1OutCannon8In", (int)emTestAudioInMain1OutCannon8In },
	{ "emTestAudioInMain1OutCannon9In", (int)emTestAudioInMain1OutCannon9In },
	{ "emTestAudioInMain1OutCannon10In", (int)emTestAudioInMain1OutCannon10In },
	{ "emTestAudioOutMainL1OutCannon1In", (int)emTestAudioOutMainL1OutCannon1In },
	{ "emTestAudioOutMainR1OutCannon1In", (int)emTestAudioOutMainR1OutCannon1In },
	{ "emTestAudioOutMainL2OutCannon1In", (int)emTestAudioOutMainL2OutCannon1In },
	{ "emTestAudioOutMainR2OutCannon1In", (int)emTestAudioOutMainR2OutCannon1In },
	{ "emTestAudioOutMainL3OutCannon1In", (int)emTestAudioOutMainL3OutCannon1In },
	{ "emTestAudioOutMainR3OutCannon1In", (int)emTestAudioOutMainR3OutCannon1In },
	{ "emProducetestTypeEnd", (int)emProducetestTypeEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMdyRecFileResDescript[]={
	{ "em_rec_file_unknow", (int)em_rec_file_unknow },
	{ "em_rec_file_success", (int)em_rec_file_success },
	{ "em_rec_file_longnamesize", (int)em_rec_file_longnamesize },
	{ "em_rec_file_inuse", (int)em_rec_file_inuse },
	{ "em_rec_file_nameexist", (int)em_rec_file_nameexist },
	{ "em_rec_file_invalidrecorder", (int)em_rec_file_invalidrecorder },
	{ "em_rec_file_noregisted", (int)em_rec_file_noregisted },
	{ "em_rec_file_invalid_info", (int)em_rec_file_invalid_info },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmUseReccorderResDescript[]={
	{ "em_rec_success", (int)em_rec_success },
	{ "em_rec_invalid", (int)em_rec_invalid },
	{ "em_rec_unregisted", (int)em_rec_unregisted },
	{ "em_rec_no_resource", (int)em_rec_no_resource },
	{ "em_rec_invalid_conf", (int)em_rec_invalid_conf },
	{ "em_rec_invalid_format", (int)em_rec_invalid_format },
	{ "em_rec_unknow_rectype", (int)em_rec_unknow_rectype },
	{ "em_rec_invalid_mt", (int)em_rec_invalid_mt },
	{ "em_rec_recordering", (int)em_rec_recordering },
	{ "em_rec_playing", (int)em_rec_playing },
	{ "em_rec_chair_playing", (int)em_rec_chair_playing },
	{ "em_rec_server_reject", (int)em_rec_server_reject },
	{ "em_rec_invalid_rec_info", (int)em_rec_invalid_rec_info },
	{ "em_rec_invalid_play_info", (int)em_rec_invalid_play_info },
	{ "em_rec_no_in_pause", (int)em_rec_no_in_pause },
	{ "em_rec_mt_offline", (int)em_rec_mt_offline },
	{ "em_rec_name_hasunderline", (int)em_rec_name_hasunderline },
	{ "em_rec_longnamesize", (int)em_rec_longnamesize },
	{ "em_rec_fileexist", (int)em_rec_fileexist },
	{ "em_rec_fileinuse", (int)em_rec_fileinuse },
	{ "em_rec_loadlib_failed", (int)em_rec_loadlib_failed },
	{ "em_rec_setrecmode_failed", (int)em_rec_setrecmode_failed },
	{ "em_rec_publicfailed", (int)em_rec_publicfailed },
	{ "em_rec_inrequesting", (int)em_rec_inrequesting },
	{ "em_rec_req_failed", (int)em_rec_req_failed },
	{ "em_rec_norecord", (int)em_rec_norecord },
	{ "em_rec_file_damange", (int)em_rec_file_damange },
	{ "em_rec_in_stopping", (int)em_rec_in_stopping },
	{ "em_rec_in_pausing", (int)em_rec_in_pausing },
	{ "em_rec_no_in_working", (int)em_rec_no_in_working },
	{ "em_rec_invalid_channel", (int)em_rec_invalid_channel },
	{ "em_rec_unmatch_format", (int)em_rec_unmatch_format },
	{ "em_rec_unknow_reason", (int)em_rec_unknow_reason },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmRecorderTypeDescript[]={
	{ "em_rec_recorder_unknow", (int)em_rec_recorder_unknow },
	{ "em_rec_recorder_conf", (int)em_rec_recorder_conf },
	{ "em_rec_recorder_mt", (int)em_rec_recorder_mt },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmConfRecStateDescript[]={
	{ "em_rec_unknow", (int)em_rec_unknow },
	{ "em_rec_init", (int)em_rec_init },
	{ "em_rec_working", (int)em_rec_working },
	{ "em_rec_pause", (int)em_rec_pause },
	{ "em_rec_finish", (int)em_rec_finish },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpProfileDescript[]={
	{ "emTpProfileBaseline", (int)emTpProfileBaseline },
	{ "emTpProfileMain", (int)emTpProfileMain },
	{ "emTpProfileExtend", (int)emTpProfileExtend },
	{ "emTpProfileHigh", (int)emTpProfileHigh },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPHandleCfgTypeDescript[]={
	{ "emTPShowCfg", (int)emTPShowCfg },
	{ "emTPSetCfg", (int)emTPSetCfg },
	{ "emTPPostCfg", (int)emTPPostCfg },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpCodecTypeDescript[]={
	{ "emTpVEnc", (int)emTpVEnc },
	{ "emTpVDec", (int)emTpVDec },
	{ "emTpAEnc", (int)emTpAEnc },
	{ "emTpADec", (int)emTpADec },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmToolStateDescript[]={
	{ "em_Tool_IDLE", (int)em_Tool_IDLE },
	{ "em_Tool_READY", (int)em_Tool_READY },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAudPlayModeDescript[]={
	{ "emTP_PLAY_FULL", (int)emTP_PLAY_FULL },
	{ "emTP_PLAY_SINGLE", (int)emTP_PLAY_SINGLE },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPAudDualInModeDescript[]={
	{ "emTP_AUD_DUAL_AUTO", (int)emTP_AUD_DUAL_AUTO },
	{ "emTP_AUD_DUAL_HDMI", (int)emTP_AUD_DUAL_HDMI },
	{ "emTP_AUD_DUAL_LINEIN", (int)emTP_AUD_DUAL_LINEIN },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDualTypeDescript[]={
	{ "emTP_TPad_DUAL_VEDIO", (int)emTP_TPad_DUAL_VEDIO },
	{ "emTP_DV_DUAL_VEDIO", (int)emTP_DV_DUAL_VEDIO },
	{ "emTP_NONE_DUAL_VEDIO", (int)emTP_NONE_DUAL_VEDIO },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDsNodeDescript[]={
	{ "emTp_Ds", (int)emTp_Ds },
	{ "emTp_Node", (int)emTp_Node },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEMScreenLookedDescript[]={
	{ "emScreenInvalid", (int)emScreenInvalid },
	{ "emScreenSelf", (int)emScreenSelf },
	{ "emScreenSpeaker", (int)emScreenSpeaker },
	{ "emScreenPoll", (int)emScreenPoll },
	{ "emScreenView", (int)emScreenView },
	{ "emScreenDiscard", (int)emScreenDiscard },
	{ "emScreenRecPlay", (int)emScreenRecPlay },
	{ "emScreenLookedEnd", (int)emScreenLookedEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDVIOutPortTypeDescript[]={
	{ "TPMOON_DVI_MODE_HDMI", (int)TPMOON_DVI_MODE_HDMI },
	{ "TPMOON_DVI_MODE_DVI", (int)TPMOON_DVI_MODE_DVI },
	{ "TPMOON_DVI_MODE_INVALID", (int)TPMOON_DVI_MODE_INVALID },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMOONOutModeDescript[]={
	{ "em_MoonOutMode_720P_60fps", (int)em_MoonOutMode_720P_60fps },
	{ "em_MoonOutMode_720P_50fps", (int)em_MoonOutMode_720P_50fps },
	{ "em_MoonOutMode_1080P_25fps", (int)em_MoonOutMode_1080P_25fps },
	{ "em_MoonOutMode_1080P_30fps", (int)em_MoonOutMode_1080P_30fps },
	{ "em_MoonOutMode_1080P_50fps", (int)em_MoonOutMode_1080P_50fps },
	{ "em_MoonOutMode_1080P_60fps", (int)em_MoonOutMode_1080P_60fps },
	{ "em_MoonOutMode_Unknown", (int)em_MoonOutMode_Unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPImageAdjustDescript[]={
	{ "emClosed", (int)emClosed },
	{ "emVertTurn", (int)emVertTurn },
	{ "emflatTurn", (int)emflatTurn },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMOOMModeDescript[]={
	{ "emAuto", (int)emAuto },
	{ "emManual", (int)emManual },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPManualModeDescript[]={
	{ "emFarth", (int)emFarth },
	{ "emNearth", (int)emNearth },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPZOOMDescript[]={
	{ "emEnlarge", (int)emEnlarge },
	{ "emReduce", (int)emReduce },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPExpGainDescript[]={
	{ "em_Gain_Nega10_5dB", (int)em_Gain_Nega10_5dB },
	{ "em_Gain_Nega9dB", (int)em_Gain_Nega9dB },
	{ "em_Gain_Nega7_5dB", (int)em_Gain_Nega7_5dB },
	{ "em_Gain_Nega6dB", (int)em_Gain_Nega6dB },
	{ "em_Gain_Nega4_5dB", (int)em_Gain_Nega4_5dB },
	{ "em_Gain_Nega3dB", (int)em_Gain_Nega3dB },
	{ "em_Gain_Nega1_5dB", (int)em_Gain_Nega1_5dB },
	{ "em_Gain_ZerodB", (int)em_Gain_ZerodB },
	{ "em_Gain_Posi1_5dB", (int)em_Gain_Posi1_5dB },
	{ "em_Gain_Posi3dB", (int)em_Gain_Posi3dB },
	{ "em_Gain_Posi4_5dB", (int)em_Gain_Posi4_5dB },
	{ "em_Gain_Posi6dB", (int)em_Gain_Posi6dB },
	{ "em_Gain_Posi7_5dB", (int)em_Gain_Posi7_5dB },
	{ "em_Gain_Posi9dB", (int)em_Gain_Posi9dB },
	{ "em_Gain_Posi10_5dB", (int)em_Gain_Posi10_5dB },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPSOrThShutterDescript[]={
	{ "em_Shutter_1Sp", (int)em_Shutter_1Sp },
	{ "em_Shutter_2Sp", (int)em_Shutter_2Sp },
	{ "em_Shutter_4Sp", (int)em_Shutter_4Sp },
	{ "em_Shutter_8Sp", (int)em_Shutter_8Sp },
	{ "em_Shutter_15Sp", (int)em_Shutter_15Sp },
	{ "em_Shutter_30Sp", (int)em_Shutter_30Sp },
	{ "em_Shutter_60Sp", (int)em_Shutter_60Sp },
	{ "em_Shutter_90Sp", (int)em_Shutter_90Sp },
	{ "em_Shutter_100Sp", (int)em_Shutter_100Sp },
	{ "em_Shutter_125Sp", (int)em_Shutter_125Sp },
	{ "em_Shutter_180Sp", (int)em_Shutter_180Sp },
	{ "em_Shutter_250Sp", (int)em_Shutter_250Sp },
	{ "em_Shutter_350Sp", (int)em_Shutter_350Sp },
	{ "em_Shutter_500Sp", (int)em_Shutter_500Sp },
	{ "em_Shutter_725Sp", (int)em_Shutter_725Sp },
	{ "em_Shutter_1000Sp", (int)em_Shutter_1000Sp },
	{ "em_Shutter_1500Sp", (int)em_Shutter_1500Sp },
	{ "em_Shutter_2000Sp", (int)em_Shutter_2000Sp },
	{ "em_Shutter_3000Sp", (int)em_Shutter_3000Sp },
	{ "em_Shutter_4000Sp", (int)em_Shutter_4000Sp },
	{ "em_Shutter_6000Sp", (int)em_Shutter_6000Sp },
	{ "em_Shutter_10000Sp", (int)em_Shutter_10000Sp },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFOrTwShutterDescript[]={
	{ "em_Shutter_1Spd", (int)em_Shutter_1Spd },
	{ "em_Shutter_2Spd", (int)em_Shutter_2Spd },
	{ "em_Shutter_3Spd", (int)em_Shutter_3Spd },
	{ "em_Shutter_6Spd", (int)em_Shutter_6Spd },
	{ "em_Shutter_12Spd", (int)em_Shutter_12Spd },
	{ "em_Shutter_25Spd", (int)em_Shutter_25Spd },
	{ "em_Shutter_50Spd", (int)em_Shutter_50Spd },
	{ "em_Shutter_75Spd", (int)em_Shutter_75Spd },
	{ "em_Shutter_100Spd", (int)em_Shutter_100Spd },
	{ "em_Shutter_120Spd", (int)em_Shutter_120Spd },
	{ "em_Shutter_150Spd", (int)em_Shutter_150Spd },
	{ "em_Shutter_215Spd", (int)em_Shutter_215Spd },
	{ "em_Shutter_300Spd", (int)em_Shutter_300Spd },
	{ "em_Shutter_425Spd", (int)em_Shutter_425Spd },
	{ "em_Shutter_600Spd", (int)em_Shutter_600Spd },
	{ "em_Shutter_1000Spd", (int)em_Shutter_1000Spd },
	{ "em_Shutter_1250Spd", (int)em_Shutter_1250Spd },
	{ "em_Shutter_1750Spd", (int)em_Shutter_1750Spd },
	{ "em_Shutter_2500Spd", (int)em_Shutter_2500Spd },
	{ "em_Shutter_3500Spd", (int)em_Shutter_3500Spd },
	{ "em_Shutter_6000Spd", (int)em_Shutter_6000Spd },
	{ "em_Shutter_10000Spd", (int)em_Shutter_10000Spd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPApertureDescript[]={
	{ "em_Aperture_OFF", (int)em_Aperture_OFF },
	{ "em_Aperture_F14", (int)em_Aperture_F14 },
	{ "em_Aperture_F11", (int)em_Aperture_F11 },
	{ "em_Aperture_F9_6", (int)em_Aperture_F9_6 },
	{ "em_Aperture_F8", (int)em_Aperture_F8 },
	{ "em_Aperture_F6_8", (int)em_Aperture_F6_8 },
	{ "em_Aperture_F5_6", (int)em_Aperture_F5_6 },
	{ "em_Aperture_F4_8", (int)em_Aperture_F4_8 },
	{ "em_Aperture_F4", (int)em_Aperture_F4 },
	{ "em_Aperture_F3_4", (int)em_Aperture_F3_4 },
	{ "em_Aperture_F2_8", (int)em_Aperture_F2_8 },
	{ "em_Aperture_F2_4", (int)em_Aperture_F2_4 },
	{ "em_Aperture_F2", (int)em_Aperture_F2 },
	{ "em_Aperture_F1_8", (int)em_Aperture_F1_8 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPReduNoiseDescript[]={
	{ "emClose", (int)emClose },
	{ "emLevelFist", (int)emLevelFist },
	{ "emLevelSecond", (int)emLevelSecond },
	{ "emLevelThird", (int)emLevelThird },
	{ "emLevelFourth", (int)emLevelFourth },
	{ "emLeVelFifth", (int)emLeVelFifth },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPImageParaDescript[]={
	{ "emBlight", (int)emBlight },
	{ "emContrast", (int)emContrast },
	{ "emSharp", (int)emSharp },
	{ "emSaturat", (int)emSaturat },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmImageMosaicTypeDescript[]={
	{ "em_Mosaic_Cut", (int)em_Mosaic_Cut },
	{ "em_Mosaic_Stretch", (int)em_Mosaic_Stretch },
	{ "em_Mosaic_Adjust", (int)em_Mosaic_Adjust },
	{ "em_Mosaic_Redunoise", (int)em_Mosaic_Redunoise },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPFpgaReduNoiseDescript[]={
	{ "emFpgaClose", (int)emFpgaClose },
	{ "emFpgaLow", (int)emFpgaLow },
	{ "emFpgaMid", (int)emFpgaMid },
	{ "emFpgaHight", (int)emFpgaHight },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmMOONProductTestTypeDescript[]={
	{ "emProducetestBegin", (int)emProducetestBegin },
	{ "emTestDVI1_HDMI", (int)emTestDVI1_HDMI },
	{ "emTestDVI2_HDMI", (int)emTestDVI2_HDMI },
	{ "emTestDVI3_HDMI", (int)emTestDVI3_HDMI },
	{ "emTestEth", (int)emTestEth },
	{ "emTestRS232", (int)emTestRS232 },
	{ "emTestGreenRedLight", (int)emTestGreenRedLight },
	{ "emTestGreenLight", (int)emTestGreenLight },
	{ "emTestZoom_DVI1_HDMI", (int)emTestZoom_DVI1_HDMI },
	{ "emTestZoom_DVI2_HDMI", (int)emTestZoom_DVI2_HDMI },
	{ "emTestZoom_DVI3_HDMI", (int)emTestZoom_DVI3_HDMI },
	{ "emTestThreeSnapShot", (int)emTestThreeSnapShot },
	{ "emTestCAM1_LvdsBaud", (int)emTestCAM1_LvdsBaud },
	{ "emTestCAM2_LvdsBaud", (int)emTestCAM2_LvdsBaud },
	{ "emTestCAM3_LvdsBaud", (int)emTestCAM3_LvdsBaud },
	{ "emProducetestEnd", (int)emProducetestEnd },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPLVDSBaudDescript[]={
	{ "em_LVDSBaud_9600bps", (int)em_LVDSBaud_9600bps },
	{ "em_LVDSBaud_19200bps", (int)em_LVDSBaud_19200bps },
	{ "em_LVDSBaud_38400bps", (int)em_LVDSBaud_38400bps },
	{ "em_LVDSBaud_115200bps", (int)em_LVDSBaud_115200bps },
	{ "em_LVDSBaud_Unknown", (int)em_LVDSBaud_Unknown },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCorrectDescript[]={
	{ "em_HorizonCorrect", (int)em_HorizonCorrect },
	{ "em_HorizonStretch", (int)em_HorizonStretch },
	{ "em_VerticalCorrect", (int)em_VerticalCorrect },
	{ "em_VerticalStretch", (int)em_VerticalStretch },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTpVerDescript[]={
	{ "tp_Ver_MOON90", (int)tp_Ver_MOON90 },
	{ "tp_Ver_MOON90H", (int)tp_Ver_MOON90H },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCorrectChangeDescript[]={
	{ "emCorrectEnlarge", (int)emCorrectEnlarge },
	{ "emCorrectReduce", (int)emCorrectReduce },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPCamNoiseLevelDescript[]={
	{ "emNoiseClose", (int)emNoiseClose },
	{ "emNoiseLevel1", (int)emNoiseLevel1 },
	{ "emNoiseLevel2", (int)emNoiseLevel2 },
	{ "emNoiseLevel3", (int)emNoiseLevel3 },
	{ "emNoiseLevel4", (int)emNoiseLevel4 },
	{ "emNoiseLevel5", (int)emNoiseLevel5 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPMechanismDescript[]={
	{ "emH650", (int)emH650 },
	{ "emSony", (int)emSony },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmH650GammaDescript[]={
	{ "emGamma1", (int)emGamma1 },
	{ "emGamma2", (int)emGamma2 },
	{ "emGamma3", (int)emGamma3 },
	{ "emGamma4", (int)emGamma4 },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPColorConsistencyDescript[]={
	{ "emColorRed", (int)emColorRed },
	{ "emColorBlue", (int)emColorBlue },
	{ "emColorGreen", (int)emColorGreen },
	{ (char*)NULL, (int)-1 }
};

const TXENUMINFO enumEmTPDistortPositionDescript[]={
	{ "emUperLeftHorizon", (int)emUperLeftHorizon },
	{ "emUperLeftVertical", (int)emUperLeftVertical },
	{ "emUperRightHorizon", (int)emUperRightHorizon },
	{ "emUperRightVertical", (int)emUperRightVertical },
	{ "emLowerRightHorizon", (int)emLowerRightHorizon },
	{ "emLowerRightVertical", (int)emLowerRightVertical },
	{ "emLowerLeftHorizon", (int)emLowerLeftHorizon },
	{ "emLowerLeftVertical", (int)emLowerLeftVertical },
	{ "emLeftSide", (int)emLeftSide },
	{ "emRightSide", (int)emRightSide },
	{ "emTopSide", (int)emTopSide },
	{ "emBottomSide", (int)emBottomSide },
	{ "emCenterRotate", (int)emCenterRotate },
	{ (char*)NULL, (int)-1 }
};

//枚举描述字符串表
TXENUMINFO* enumTpXDescript[]={
	(TXENUMINFO*)enumEmTPDevRegUpdateSerDescript, 
	(TXENUMINFO*)enumEmTPUpdateTypeDescript, 
	(TXENUMINFO*)enumEmWiFiLinkStatDescript, 
	(TXENUMINFO*)enumEmWiFiSelTypeDescript, 
	(TXENUMINFO*)enumEmWiFiNetTypeDescript, 
	(TXENUMINFO*)enumEmWiFiEncryptTypeDescript, 
	(TXENUMINFO*)enumEmWiFiEncryptArithmeticDescript, 
	(TXENUMINFO*)enumEmVODRejCodeDescript, 
	(TXENUMINFO*)enumEmVODStateDescript, 
	(TXENUMINFO*)enumEmTextAlignDescript, 
	(TXENUMINFO*)enumEmRollModeDescript, 
	(TXENUMINFO*)enumEmRollSpeedDescript, 
	(TXENUMINFO*)enumEmStopBitsDescript, 
	(TXENUMINFO*)enumEmParityCheckDescript, 
	(TXENUMINFO*)enumEmSerialTypeDescript, 
	(TXENUMINFO*)enumEmLanguageDescript, 
	(TXENUMINFO*)enumEmConfProtocolDescript, 
	(TXENUMINFO*)enumEmEncodeModeDescript, 
	(TXENUMINFO*)enumEmLostPackageRestoreDescript, 
	(TXENUMINFO*)enumEmMatrixTypeDescript, 
	(TXENUMINFO*)enumEmDualVideoShowModeDescript, 
	(TXENUMINFO*)enumEmDisplayRatioDescript, 
	(TXENUMINFO*)enumEmVideoTypeDescript, 
	(TXENUMINFO*)enumEmVideoStandardDescript, 
	(TXENUMINFO*)enumEmVideoInterfaceDescript, 
	(TXENUMINFO*)enumEmMtVideoPortDescript, 
	(TXENUMINFO*)enumEmTripModeDescript, 
	(TXENUMINFO*)enumEmLabelTypeDescript, 
	(TXENUMINFO*)enumEmDLProtocolDescript, 
	(TXENUMINFO*)enumEmAuthenticationTypeDescript, 
	(TXENUMINFO*)enumEmFrameUnitTypeDescript, 
	(TXENUMINFO*)enumEmMediaTypeDescript, 
	(TXENUMINFO*)enumEmVideoFormatDescript, 
	(TXENUMINFO*)enumEmAudioFormatDescript, 
	(TXENUMINFO*)enumEmVideoResolutionDescript, 
	(TXENUMINFO*)enumEmQoSDescript, 
	(TXENUMINFO*)enumEmTOSDescript, 
	(TXENUMINFO*)enumEmSiteDescript, 
	(TXENUMINFO*)enumEmChanTypeDescript, 
	(TXENUMINFO*)enumEmCodecComponentDescript, 
	(TXENUMINFO*)enumEmMtModelDescript, 
	(TXENUMINFO*)enumEmFileSysDescript, 
	(TXENUMINFO*)enumEmEncryptArithmeticDescript, 
	(TXENUMINFO*)enumEmActionDescript, 
	(TXENUMINFO*)enumEmOptRetDescript, 
	(TXENUMINFO*)enumEmConfModeDescript, 
	(TXENUMINFO*)enumEmMtAddrTypeDescript, 
	(TXENUMINFO*)enumEmCallModeDescript, 
	(TXENUMINFO*)enumEmDirectionDescript, 
	(TXENUMINFO*)enumEmCallStateDescript, 
	(TXENUMINFO*)enumEmCallSiteStateDescript, 
	(TXENUMINFO*)enumEmTransModeDescript, 
	(TXENUMINFO*)enumEmDualSrcTypeDescript, 
	(TXENUMINFO*)enumEmMtInstTypeDescript, 
	(TXENUMINFO*)enumEmVMPStyleDescript, 
	(TXENUMINFO*)enumEmVMPMmbTypeDescript, 
	(TXENUMINFO*)enumEmSMSTypeDescript, 
	(TXENUMINFO*)enumEmMtFileDescript, 
	(TXENUMINFO*)enumEmCallRateDescript, 
	(TXENUMINFO*)enumEmPCCapFormatDescript, 
	(TXENUMINFO*)enumEmPiPModeDescript, 
	(TXENUMINFO*)enumEmDVBComponentDescript, 
	(TXENUMINFO*)enumEmUIPosionDescript, 
	(TXENUMINFO*)enumEmCallDisconnectReasonDescript, 
	(TXENUMINFO*)enumEmMCModeDescript, 
	(TXENUMINFO*)enumEmInnerVMPStyleDescript, 
	(TXENUMINFO*)enumEmVMPComponentDescript, 
	(TXENUMINFO*)enumEmCapTypeDescript, 
	(TXENUMINFO*)enumEmPPPoEStateDescript, 
	(TXENUMINFO*)enumEmDhcpStateDescript, 
	(TXENUMINFO*)enumEmAddrGroupOptTypeDescript, 
	(TXENUMINFO*)enumEmHotKeyTypeDescript, 
	(TXENUMINFO*)enumEmMtOSTypeDescript, 
	(TXENUMINFO*)enumEmFxoStateDescript, 
	(TXENUMINFO*)enumEmMtLoudspeakerValDescript, 
	(TXENUMINFO*)enumEmNetTypeDescript, 
	(TXENUMINFO*)enumEmSysRunSuccessFlagDescript, 
	(TXENUMINFO*)enumEmMcuNtfMsgTypeDescript, 
	(TXENUMINFO*)enumEmAutoTestTypeDescript, 
	(TXENUMINFO*)enumEmGKRegFailedReasonDescript, 
	(TXENUMINFO*)enumEmSleepStateDescript, 
	(TXENUMINFO*)enumEmMtAppNameDescript, 
	(TXENUMINFO*)enumHD_PORT_MASKDescript, 
	(TXENUMINFO*)enumEmHDAudPortInDescript, 
	(TXENUMINFO*)enumEmHDAudPortOutDescript, 
	(TXENUMINFO*)enumEmLogStatusDescript, 
	(TXENUMINFO*)enumEmLogExportResultDescript, 
	(TXENUMINFO*)enumEmFecModeTypeDescript, 
	(TXENUMINFO*)enumEmLabelPosTypeDescript, 
	(TXENUMINFO*)enumEmMtcBoxCallIndexDescript, 
	(TXENUMINFO*)enumEmSipRegFailedReasonDescript, 
	(TXENUMINFO*)enumEMtRecChnnlStateDescript, 
	(TXENUMINFO*)enumEMtRecChnnlTypeDescript, 
	(TXENUMINFO*)enumEMtRecModeDescript, 
	(TXENUMINFO*)enumEMtRecEnumDescript, 
	(TXENUMINFO*)enumEmMtRegResultDescript, 
	(TXENUMINFO*)enumEmTpRetDescript, 
	(TXENUMINFO*)enumEmTpHduPlayNackReasonDescript, 
	(TXENUMINFO*)enumEmTpLoginUmsRetDescript, 
	(TXENUMINFO*)enumEmTpAliasTypeDescript, 
	(TXENUMINFO*)enumEmTpOprTypeDescript, 
	(TXENUMINFO*)enumEmConfAddEpRetDescript, 
	(TXENUMINFO*)enumEmTpIFrameCheckTypeDescript, 
	(TXENUMINFO*)enumEmTPEncryptTypeDescript, 
	(TXENUMINFO*)enumEmTPRcvAlignTypeDescript, 
	(TXENUMINFO*)enumEmCnsCallReasonDescript, 
	(TXENUMINFO*)enumEmTPChannelReasonDescript, 
	(TXENUMINFO*)enumEmTpCnsTypeDescript, 
	(TXENUMINFO*)enumEmTpCnsRegUmsDescript, 
	(TXENUMINFO*)enumEmTpConfTemplateRetDescript, 
	(TXENUMINFO*)enumEmTpStartConfRetDescript, 
	(TXENUMINFO*)enumEmTpApplySpeakerRetDescript, 
	(TXENUMINFO*)enumEmTpDropConfRetDescript, 
	(TXENUMINFO*)enumEmTpApplySpeakRetDescript, 
	(TXENUMINFO*)enumEmUmsConfNodeStateDescript, 
	(TXENUMINFO*)enumEmFlowCtrlOprDescript, 
	(TXENUMINFO*)enumEMBrdTypeDescript, 
	(TXENUMINFO*)enumEMEqpTypeDescript, 
	(TXENUMINFO*)enumEMEqpModleTypeDescript, 
	(TXENUMINFO*)enumEMOsTypeDescript, 
	(TXENUMINFO*)enumEMVmpStyleDescript, 
	(TXENUMINFO*)enumEmTpVideoFormatDescript, 
	(TXENUMINFO*)enumEmTpEncodeModeDescript, 
	(TXENUMINFO*)enumEmTpVideoQualityLevelDescript, 
	(TXENUMINFO*)enumEmTpVideoResolutionDescript, 
	(TXENUMINFO*)enumEmTpMediaTypeDescript, 
	(TXENUMINFO*)enumEmTpPCCapFormatDescript, 
	(TXENUMINFO*)enumEmTpCodecComponentDescript, 
	(TXENUMINFO*)enumEmTpAudioFormatDescript, 
	(TXENUMINFO*)enumEmTpLostPackageRestoreDescript, 
	(TXENUMINFO*)enumEmTpCallModeDescript, 
	(TXENUMINFO*)enumEmTpConnectionTypeDescript, 
	(TXENUMINFO*)enumEmTpConfProtocolDescript, 
	(TXENUMINFO*)enumEmTPAddrTypeDescript, 
	(TXENUMINFO*)enumEmTPEndpointTypeDescript, 
	(TXENUMINFO*)enumEmTPSipLevelDescript, 
	(TXENUMINFO*)enumEmCALLSTATEDescript, 
	(TXENUMINFO*)enumEmCallTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoPortDescript, 
	(TXENUMINFO*)enumEmTPCNSInfoRstDescript, 
	(TXENUMINFO*)enumEmTPRegResultDescript, 
	(TXENUMINFO*)enumEmCnMtRegResultDescript, 
	(TXENUMINFO*)enumEmCnModelDescript, 
	(TXENUMINFO*)enumEmFocusModeDescript, 
	(TXENUMINFO*)enumEmFocusDescript, 
	(TXENUMINFO*)enumEmZoomDescript, 
	(TXENUMINFO*)enumEmCnActionDescript, 
	(TXENUMINFO*)enumEmOSDShowDescript, 
	(TXENUMINFO*)enumEmWBModeDescript, 
	(TXENUMINFO*)enumEmExpModeDescript, 
	(TXENUMINFO*)enumEmGainDescript, 
	(TXENUMINFO*)enumEmShutSpdDescript, 
	(TXENUMINFO*)enumEmBackLightTypeDescript, 
	(TXENUMINFO*)enumEmPicSceModeDescript, 
	(TXENUMINFO*)enumEmGammaDescript, 
	(TXENUMINFO*)enumEmStmCleanDescript, 
	(TXENUMINFO*)enumEm3DNRDescript, 
	(TXENUMINFO*)enumEmCamPowerModeDescript, 
	(TXENUMINFO*)enumEmCenSchModeDescript, 
	(TXENUMINFO*)enumEmTvPowerModeDescript, 
	(TXENUMINFO*)enumEmTvSrcPowerModeDescript, 
	(TXENUMINFO*)enumEmTVAudVisModeDescript, 
	(TXENUMINFO*)enumEmTVDisplayModeDescript, 
	(TXENUMINFO*)enumEmTVInputSelectDescript, 
	(TXENUMINFO*)enumEmDCamWBModeDescript, 
	(TXENUMINFO*)enumEmDCamAFModeDescript, 
	(TXENUMINFO*)enumEmDCamPowerDescript, 
	(TXENUMINFO*)enumEmDCamZoomDescript, 
	(TXENUMINFO*)enumEmDCamPresetNumDescript, 
	(TXENUMINFO*)enumEmDCamRecallNumDescript, 
	(TXENUMINFO*)enumEmSchPowerDescript, 
	(TXENUMINFO*)enumEmSchLightDescript, 
	(TXENUMINFO*)enumEmSchMidLightDescript, 
	(TXENUMINFO*)enumEmSchScrLightDescript, 
	(TXENUMINFO*)enumEmSchArgusDescript, 
	(TXENUMINFO*)enumEmCentreACPowerDescript, 
	(TXENUMINFO*)enumEmCentreACAirVolDescript, 
	(TXENUMINFO*)enumEmCentreACModeDescript, 
	(TXENUMINFO*)enumEmCurActionDescript, 
	(TXENUMINFO*)enumEmCurChannelModeDescript, 
	(TXENUMINFO*)enumEmSchGatewayTypeDescript, 
	(TXENUMINFO*)enumEmTpMixStatusDescript, 
	(TXENUMINFO*)enumEmTPDualReasonDescript, 
	(TXENUMINFO*)enumEmTPPayloadTypeDescript, 
	(TXENUMINFO*)enumEmTPPosStatusDescript, 
	(TXENUMINFO*)enumEmTPPollResultDescript, 
	(TXENUMINFO*)enumEmTPViewResultDescript, 
	(TXENUMINFO*)enumEmTPViewLocalResultDescript, 
	(TXENUMINFO*)enumEmTPDisOprTypeDescript, 
	(TXENUMINFO*)enumEMPosPicDescript, 
	(TXENUMINFO*)enumEMDSCREATETYPEDescript, 
	(TXENUMINFO*)enumEmTPAddDualRcvResultDescript, 
	(TXENUMINFO*)enumEmTPDeleteDualRcvResultDescript, 
	(TXENUMINFO*)enumEmTPMtModelDescript, 
	(TXENUMINFO*)enumEmDsTypeDescript, 
	(TXENUMINFO*)enumEmCnAudioMixIDDescript, 
	(TXENUMINFO*)enumEmGetRegInfoTypeDescript, 
	(TXENUMINFO*)enumEmGetRegInfoOprDescript, 
	(TXENUMINFO*)enumEmTPChanTypeDescript, 
	(TXENUMINFO*)enumEmTPAACSampleFreqDescript, 
	(TXENUMINFO*)enumEmTPG7221RateDescript, 
	(TXENUMINFO*)enumEmTPAACChnlCfgDescript, 
	(TXENUMINFO*)enumEmTPTpApplySpeakerRetDescript, 
	(TXENUMINFO*)enumEmTPChanSubTypeDescript, 
	(TXENUMINFO*)enumEmMakeCallTypeDescript, 
	(TXENUMINFO*)enumEmTpRegTypeDescript, 
	(TXENUMINFO*)enumEmDisListOprTypeDescript, 
	(TXENUMINFO*)enumEmDisListOprResltDescript, 
	(TXENUMINFO*)enumEmVgaTypeDescript, 
	(TXENUMINFO*)enumEmDualInputTypeDescript, 
	(TXENUMINFO*)enumEmDualOutputTypeDescript, 
	(TXENUMINFO*)enumEmVgaSwitchResultDescript, 
	(TXENUMINFO*)enumEmVgaSwitchReasonDescript, 
	(TXENUMINFO*)enumEmCnStateDescript, 
	(TXENUMINFO*)enumEmTPCapSignDescript, 
	(TXENUMINFO*)enumEmSwitchStateDescript, 
	(TXENUMINFO*)enumEmTpBoardRetDescript, 
	(TXENUMINFO*)enumEmHduOutPortDescript, 
	(TXENUMINFO*)enumEmHduZoomRateDescript, 
	(TXENUMINFO*)enumEmHduOutModeDescript, 
	(TXENUMINFO*)enumEmHduShowModeDescript, 
	(TXENUMINFO*)enumEmModifyNMServerRetDescript, 
	(TXENUMINFO*)enumEmModifyVcrRetDescript, 
	(TXENUMINFO*)enumEmModifyHduRetDescript, 
	(TXENUMINFO*)enumEmUpdateHduRetDescript, 
	(TXENUMINFO*)enumEmMPCodecDescript, 
	(TXENUMINFO*)enumEmTPHDAudPortInDescript, 
	(TXENUMINFO*)enumEmTPHDDualAudPortInDescript, 
	(TXENUMINFO*)enumEmTPHDAudPortOutDescript, 
	(TXENUMINFO*)enumEmTPMtVideoPortDescript, 
	(TXENUMINFO*)enumEmTPMtVideoOutPortDescript, 
	(TXENUMINFO*)enumEmTPAutoTestTypeDescript, 
	(TXENUMINFO*)enumEmTPHduRunStatusDescript, 
	(TXENUMINFO*)enumEmTPLoudspeakerValDescript, 
	(TXENUMINFO*)enumEmTPFrameUnitTypeDescript, 
	(TXENUMINFO*)enumEmTPVideoStandardDescript, 
	(TXENUMINFO*)enumEmTPLabelTypeDescript, 
	(TXENUMINFO*)enumEmTPLabelPosTypeDescript, 
	(TXENUMINFO*)enumEmTPDualVideoShowModeDescript, 
	(TXENUMINFO*)enumEmTPDisplayRatioDescript, 
	(TXENUMINFO*)enumEmTPFecModeTypeDescript, 
	(TXENUMINFO*)enumEmTPNetTypeDescript, 
	(TXENUMINFO*)enumEmTPEqualizerRateDescript, 
	(TXENUMINFO*)enumEmTPPIPModeDescript, 
	(TXENUMINFO*)enumEmTPDVIModeDescript, 
	(TXENUMINFO*)enumEmTPMCModeDescript, 
	(TXENUMINFO*)enumEmCnsUpdateStateDescript, 
	(TXENUMINFO*)enumEmTPCnLoginUpdateRetDescript, 
	(TXENUMINFO*)enumEmTPFileSrvUsedVersionDescript, 
	(TXENUMINFO*)enumEmTPFileSrvFileTypeDescript, 
	(TXENUMINFO*)enumEmTPOSTypeDescript, 
	(TXENUMINFO*)enumEmMPAudEncCodecDescript, 
	(TXENUMINFO*)enumEmToolTypeDescript, 
	(TXENUMINFO*)enumEmProducetestTypeDescript, 
	(TXENUMINFO*)enumEmMdyRecFileResDescript, 
	(TXENUMINFO*)enumEmUseReccorderResDescript, 
	(TXENUMINFO*)enumEmRecorderTypeDescript, 
	(TXENUMINFO*)enumEmConfRecStateDescript, 
	(TXENUMINFO*)enumEmTpProfileDescript, 
	(TXENUMINFO*)enumEmTPHandleCfgTypeDescript, 
	(TXENUMINFO*)enumEmTpCodecTypeDescript, 
	(TXENUMINFO*)enumEmToolStateDescript, 
	(TXENUMINFO*)enumEmTPAudPlayModeDescript, 
	(TXENUMINFO*)enumEmTPAudDualInModeDescript, 
	(TXENUMINFO*)enumEmTPDualTypeDescript, 
	(TXENUMINFO*)enumEmTPDsNodeDescript, 
	(TXENUMINFO*)enumEMScreenLookedDescript, 
	(TXENUMINFO*)enumEmTPDVIOutPortTypeDescript, 
	(TXENUMINFO*)enumEmTPMOONOutModeDescript, 
	(TXENUMINFO*)enumEmTPImageAdjustDescript, 
	(TXENUMINFO*)enumEmTPMOOMModeDescript, 
	(TXENUMINFO*)enumEmTPManualModeDescript, 
	(TXENUMINFO*)enumEmTPZOOMDescript, 
	(TXENUMINFO*)enumEmTPExpGainDescript, 
	(TXENUMINFO*)enumEmTPSOrThShutterDescript, 
	(TXENUMINFO*)enumEmTPFOrTwShutterDescript, 
	(TXENUMINFO*)enumEmTPApertureDescript, 
	(TXENUMINFO*)enumEmTPReduNoiseDescript, 
	(TXENUMINFO*)enumEmTPImageParaDescript, 
	(TXENUMINFO*)enumEmImageMosaicTypeDescript, 
	(TXENUMINFO*)enumEmTPFpgaReduNoiseDescript, 
	(TXENUMINFO*)enumEmMOONProductTestTypeDescript, 
	(TXENUMINFO*)enumEmTPLVDSBaudDescript, 
	(TXENUMINFO*)enumEmTPCorrectDescript, 
	(TXENUMINFO*)enumEmTpVerDescript, 
	(TXENUMINFO*)enumEmTPCorrectChangeDescript, 
	(TXENUMINFO*)enumEmTPCamNoiseLevelDescript, 
	(TXENUMINFO*)enumEmTPMechanismDescript, 
	(TXENUMINFO*)enumEmH650GammaDescript, 
	(TXENUMINFO*)enumEmTPColorConsistencyDescript, 
	(TXENUMINFO*)enumEmTPDistortPositionDescript, 
	(TXENUMINFO*)NULL
};

#endif //_TP_COMMON_XML_STRUCT_H_
