
#ifndef __TQ2416_YQCOIN_H__
#define __TQ2416_YQCOIN_H__



#include "def.h"
#include "yqsqlite3.h"


typedef struct
{
	U32 total_money;
	U32 total_good;
	U32 total_ng;
	U32 total_coin;
	U32 coinnumber;
	S16 ad2_averaged_value;
}s_processed_coin_info;

extern s_processed_coin_info processed_coin_info;

#define COINCNUM 4     //Ŀǰ ���� ������ ���ұ���  �������� 
//#define RATIONCOINNUM 9   //ÿ�����ұ������9��
//extern U8 coine[COINCNUM][9];  // ���־��� 
extern int alertname[COIN_TYPE_NUM];// ���־��� 

extern U32 coin_num[COIN_TYPE_NUM];    //������ ��������
void coincount(void);	// get average value and print the value,then compare who is who 
void my_coincount(void);	// get average value and print the value,then compare who is who 
void my_precoincount(void);	// get average value and print the value,then compare who is who 
extern  U16 ccstep;


//extern unsigned int temp_coinnum;   //for compare the coin number, check 
#define NUMTIME 5  //ͨ����ͨ����� ����ʱ��

//#define ADTIMETWO   1400  //�����ʱ���� ֻ������AD�����仯�����߳��˱�  800
//#define ADTIMEALL 1600     //��������ʱ���ֻ��һ�������仯������仯 1000

extern  U32 ch0_counttemp;  // ǰһ��ͨ��0 ͨ����Ӳ�Ҽ��� 
extern  U32 ch1_counttemp;  // ǰһ��ͨ��1 ͨ����Ӳ�Ҽ��� 
extern  U32 ch2_counttemp;  // ǰһ��ͨ��2 ͨ����Ӳ�Ҽ��� 
extern  U32 coinlearnnumber;

void coinlearn(void);   //��ѧϰ�ĳ���
void my_coinlearn(void);   //��ѧϰ�ĳ���

extern  S16 coin_maxvalue0;
extern  S16 coin_minvalue0;
extern  S16 coin_maxvalue1;
extern  S16 coin_minvalue1;
extern  S16 coin_maxvalue2;
extern  S16 coin_minvalue2;


extern  U16 coine[COINCNUM][COIN_TYPE_NUM];

extern  U32 zs_precount;   //��ǰԤ�ü��� ����
extern  U32 ze_precount;   //��ǰԤ�ü��� �ܶ�
void precoincount(void);     //   Ԥ�� ����

#define DT_STORE 	0x01	//0x80	// manbi   ch02 duishe   EINT1/GPF1
#define DT_PAN  	0x02  	//caoxing   ch01 zhuanpan   EINT0/GPF0  
#define DT_PUSH  	0x04	//0x04	// yabitiao  ch07 EINT11/GPG3
#define DT_PANDOOR  0x80	//0x08	// zhuanpan men  ch05  EINT3/GPF3
#define DT_DOOR	 	0x40	//64	// men     ch03   EINT2/GPF2
#define DT_FORGE  	0x20	//32	// weibi   ch04  EINT4/GPF4
#define DT_COIN 	0x08		//0x80 // coin  cho5  
void detect_read(void);   

/*****************
����궨��    ����
*****************/

#define SWITCHERROR 11      //��û�й���
#define STORAGEERROR 12
#define DUIERROR 13     // �Ҷ��� 
#define PANBLOCKEDERROR 14     //ת�̶ı�
#define KICKCOINERROR 15
#define NEGATIVEERROR 16
#define PRESSMLOCKED  17      //ѹ�Ҵ��±�
#define ADSTDEEROR    20       //��ʾ���������б�
#define RTCREEROR    21       //��ʾREAD time wrong
#define READOUTDATA    22       // ����  ����  �ڴ���
#define COUNT_FINISHED 18  	// 1 MCU�ӵ� ����ֶ����� ֹͣ	


#define ALERT0 0  //���ַADDR_TTS ����"�����׼ֵ"
#define ALERT1 1   // //���ַADDR_TTS ����"�����׼ֵ"
#define ALERT3 3  //���ַADDR_TTS ����"ת�̶±�"
#define ALERT4 4   // //���ַADDR_TTS ����"ѹ�Ҵ��±�"
#define ALERT5 5   // �߱��쳣
#define ALERT6 6  //���ַADDR_TTS ����"�Ҷ���"
#define ALERT7 7   // //���ַADDR_TTS ����"ȷ���賤��1����Ч"
#define ALERT8 8   // //���ַADDR_TTS ����"�뵼�����ݣ��ڴ�����"
#define ALERT9 9   // //���ַADDR_TTS ����"��ֶ����� ��ȡ��"


#define ALERT20 20   // //���ַADDR_TTS ����"һԪԤ��ֵ�ѵ�"
#define ALERT21 21   // //���ַADDR_TTS ����"0.5ԪԤ��ֵ�ѵ�"
#define ALERT22 22   // //���ַADDR_TTS ����"0.1ԪԤ��ֵ�ѵ�"
#define ALERT23 23   // //���ַADDR_TTS ����"0.05ԪԤ��ֵ�ѵ�"
#define ALERT24 24   // //���ַADDR_TTS ����"0.02ԪԤ��ֵ�ѵ�"
#define ALERT25 25   // //���ַADDR_TTS ����"0.01ԪԤ��ֵ�ѵ�"
#define ALERT26 26   // //���ַADDR_TTS ����"10ԪԤ��ֵ�ѵ�"
#define ALERT27 27   // //���ַADDR_TTS ����"5ԪԤ��ֵ�ѵ�"

extern  U16 prepic_prenum;      // ���ڼ�¼ ����ǰ�Ľ��� 
void alertfuc(U16 alertflag); //����






#endif
