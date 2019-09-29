// diagTestInfoLogic.h: interface for the CDiagTestInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_)
#define AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagTestInfoLogic : public CLogicBase, public ISingleTon<CDiagTestInfoLogic>   
{
public:
	CDiagTestInfoLogic();
	virtual ~CDiagTestInfoLogic();
	
	//CLogicBase
public:	 	
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc();
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/
    virtual void Clear();

protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
private:
	/** ����:  �յ���ϲ��Խ������Ϣ��Ӧ(��Ƶ)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVideoDiagInfoInd( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ���ϲ��Խ������Ϣ��Ӧ(��Ƶ)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnAudioDiagInfoInd( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ���ϲ��Խ������Ϣ��Ӧ(domodal����)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnDomodalDiagTestWnd( WPARAM wparam, LPARAM lparam);
	/** ����:  �յ�ֹͣ��ϲ��ԵĽ��(����domodal����)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnStopAVMatrixRsp( WPARAM wparam, LPARAM lparam);
	/** ����:  ��һҳ��ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnNextPage( const IArgs & arg );
	/** ����:  ��һҳ��ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnPrePage( const IArgs & arg );
	/** ����:  �رմ��ڰ�ť(���Ͻǲ��)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnCloseDiagTest( const IArgs & arg );
	/** ����:  �������水ť
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnExRePort( const IArgs & arg );
	/** ����:  ��ȡ������ķֱ��ʼ�֡����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String GetVideoInfo( TTPVideoPortInfo& tVideoPortInfo );
	/** ����:  ���յ��ķֱ�����Ϣת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String ChangeResToString( EmTpVideoResolution& emVideoRes );
	/** ����:  ���յ�����ʾԴ����ӿ���Ϣת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String VgaInToString( EmVgaType& emDualInput );
	/** ����:  ���յ�����ʾԴ����ӿ���Ϣת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String VgaOutToString( EmDualOutputType& emDualOutput );
	/** ����:  ��ȡ��Ƶ����豸��������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   				
	*/
	String GetAudioOutInfo( TTpAudioPortInfo& tAudioPortInfo );
	/** ����:  ��ȡ��Ƶ����ӿڵ����
	*  @param[in] 
	*  @return  ��ȡ��Ƶ�ӿڵ���Ŀ
	*  @remarks   
	*/
	u32 GetAudioNum();
	/** ����:  �����������ֵת��Ϊstring����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	String CommonToStr( u32 u );
	/** ����:  �ж�check���Ƿ�ѡ��
	*  @param[in] strWnd  �ؼ�����
	*  @return 
	*  @remarks   
	*/
	s32 GetCheckState( String strWnd );
	/** ����:  ��ȡ����ӿ���Ϣ
	*  @param[in] strWnd  �ؼ�����
	*  @return 
	*  @remarks   
	*/
	String GetAVPortInfo();

private:
	TTPAudioDiagInfo m_tAudioDiagInfo;

	String  m_strDiagInVideo;
	String	m_strDiagInAudio;

	String  m_strDiagOutVideo1;
	String  m_strDiagOutVideo2;
	String  m_strDiagOutVideo3;
	String  m_strDiagOutVideo4;
	
	String	m_strDiagOutAudio1;
	String	m_strDiagOutAudio2;
	String	m_strDiagOutAudio3;
	s32 m_bIsUse[10];							//������ž������ĸ���ũ��˷类ѡ��
	const String m_strCamera1;					//�����1	
	const String m_strCamera2;					//�����2
	const String m_strCamera3;					//�����3
	const String m_StrShowCameraInfo;			//ѡ�����ʾԴ	
	const String m_strShowCamera;				//��ʾԴ������Ϣ	
	const String m_strDisPlay1;					//��ʾ��1
	const String m_strCheckDisPlay1;			//�����ʾ��1�Ƿ���ͼ��
	const String m_strDisPlay2;					//��ʾ��2
	const String m_strCheckDisPlay2;			//�����ʾ��2�Ƿ���ͼ��
	const String m_strDisPlay3;					//��ʾ��3
	const String m_strCheckDisPlay3;			//�����ʾ��3�Ƿ���ͼ��
	const String m_strVoiceBox1;				//������1
	const String m_strCheckVoiceBox1;			//���������1�Ƿ�������
	const String m_strVoiceBox2;				//������2
	const String m_strCheckVoiceBox2;			//���������2�Ƿ�������
	const String m_strVoiceBox3;				//������3
	const String m_strCheckVoiceBox3;			//���������3�Ƿ�������
	const String m_strShowScreenInfo;			//ѡ�����ʾ��
	const String m_strShowScreen;				//��ʾ����Ϣ
	const String m_strCheckShowScreen;			//�����ʾ���Ƿ���ͼ��

};

#endif // !defined(AFX_DIAGTESTINFOLOGIC_H__E8B828B0_B1CB_4078_894A_621307F79C0B__INCLUDED_)
