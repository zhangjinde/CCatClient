#ifndef CATTRANSACTION_h__
#define CATTRANSACTION_h__


#include "CatMessage.h"
#include "ZRStaticQueue.h"

#define MAX_TRANSCACTION_CHILD_NUM 200


typedef struct _CatTranscation CatTransaction;

typedef struct _CatTranscationInner
{
	ZRStaticQueue * m_children;
	unsigned long long m_durationStart; // �߾���ʱ�䣬��ȷ�����룬�������GetTime64 * 1000 * 1000ʵ����
	unsigned long long m_durationUs; 

	// �����Ҫ��CatMessageInner�����ϸ�һ��
	char m_msgType;
	char m_unused[3]; //4�ֽڶ���
	sds m_type;
	sds m_name;
	sds m_status;
	sds m_data;
	unsigned long long m_timeStamp; //ͳһ���壬sec*1000 + ms
	int m_completeFlag;
	void(*setCompleteFlag)  (CatMessage* message, int completeFlag);
	void *(*clear)   (CatMessage* message);


}CatTransactionInner;


struct _CatTranscation
{
	void(*addDataPair)   (CatMessage* message, const char *data);
	void(*addData)   (CatMessage* message, const char *dataKey, const char * dataValue);
	void(*setStatus) (CatMessage* message, const char *status);
	void(*setComplete)  (CatMessage* message);
	void *(*clear)   (CatMessage* message);
    void(*addChild)    (CatTransaction* message, CatMessage* childMsg);
    ZRStaticQueue *(*getChildren)    (CatTransaction* message);
};

CatTransaction * createCatTransaction(const char *type, const char * name);

CatTransaction * copyCatTransaction(CatTransaction * pSrcTrans);

unsigned long long getCatTranscationDurationUs(CatTransaction * trans);


#define getInnerTrans(pMsg) ((CatTransactionInner*)(((char*)(pMsg)) - sizeof(CatTransactionInner)))

#endif//CATTRANSACTION_h__