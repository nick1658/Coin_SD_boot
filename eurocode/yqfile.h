


#ifndef __TQ2416_YQFILE_H__
#define __TQ2416_YQFILE_H__

#include "def.h"
extern S8 alertflag;  //�����־λ
extern  S8 spinvalue;    //sample in pin value  ���������� ֵ






//rmb
#define IV100  "/home/yq_yiyuan"     //Identify value of 1yuan
#define IV5  "/home/yq_wufen" 
#define IVD10  "/home/yq_yijiaod" 
#define IV2  "/home/yq_erfen" 
#define IV1  "/home/yq_yifen" 
#define IVT50  "/home/yq_wujiaot" 
#define IVG50  "/home/yq_wujiaog" 
#define IVG10  "/home/yq_yijiaoxg" 
#define IVL10  "/home/yq_yijiaoxl" 

//euro
#define FEUR200  "/home/feur200"     //Identify value of 1yuan
#define FEUR100  "/home/feur100" 
#define FEUR50  "/home/feur50" 
#define FEUR20  "/home/feur20" 
#define FEUR10  "/home/feur10" 
#define FEUR5  "/home/feur5" 
#define FEUR2  "/home/feur2" 
#define FEUR1  "/home/feur1" 

//dollar

#define FDOL100   "/home/fdol100"     //Identify value of 1yuan
#define FDOL50   "/home/fdol50" 
#define FDOL25   "/home/fdol25" 
#define FDOL10   "/home/fdol10" 
#define FDOL5   "/home/fdol5" 
#define FDOL1   "/home/fdol1" 

//pound
#define FPND200   "/home/fpnd200"    
#define FPND100   "/home/fpnd100"     
#define FPND50   "/home/fpnd50"   
#define FPND20   "/home/fpnd20"   
#define FPND10   "/home/fpnd10"   
#define FPND5   "/home/fpnd5"   
#define FPND2   "/home/fpnd2"   
#define FPND1   "/home/fpnd1"   


#define IVTB  "/home/yq_kick"    //canshu tibi delay 
#define FCOIN  "/home/precoingh"  //��ǰ���� ����

#define VRMB  "/home/yq_prermb"    //value pre ����� 
#define VEUR  "/home/yq_preeur"    //value pre ŷԪ
#define VDOL  "/home/yq_predol"    //value pre ��Ԫ
#define VPND  "/home/yq_prepnd"    //value pre ŷԪ


//rmb
#define JZ100  "/home/yq_stdyiyuan"    //value  of jizhun
#define JZ5  "/home/yq_stdwufen"    //value  of jizhun
#define JZD10  "/home/yq_stdyijiaod"    //value  of jizhun
#define JZ2  "/home/yq_stderfen"    //value  of jizhun
#define JZ1  "/home/yq_stdyifen"    //value  of jizhun
#define JZT50  "/home/yq_stdwujiaot"    //value  of jizhun
#define JZG50  "/home/yq_stdwujiaog"    //value  of jizhun
#define JZG10  "/home/yq_stdyijiaoxg"    //value  of jizhun
#define JZL10  "/home/yq_stdyijiaoxl"    //value  of jizhun
//euro
#define STDEUR200  "/home/seur200"     //Identify value of 1yuan
#define STDEUR100  "/home/seur100" 
#define STDEUR50  "/home/seur50" 
#define STDEUR20  "/home/seur20" 
#define STDEUR10  "/home/seur10" 
#define STDEUR5  "/home/seur5" 
#define STDEUR2  "/home/seur2" 
#define STDEUR1  "/home/seur1" 
//dollar
#define STDDOL100   "/home/sdol100"     //Identify value of 1yuan
#define STDDOL50   "/home/sdol50" 
#define STDDOL25   "/home/sdol25" 
#define STDDOL10   "/home/sdol10" 
#define STDDOL5   "/home/sdol5" 
#define STDDOL1   "/home/sdol1" 

//POUND
#define STDPND200   "/home/spnd200"    
#define STDPND100   "/home/spnd100"     
#define STDPND50   "/home/spnd50"   
#define STDPND20   "/home/spnd20"   
#define STDPND10   "/home/spnd10"   
#define STDPND5   "/home/spnd5"   
#define STDPND2   "/home/spnd2"   
#define STDPND1   "/home/spnd1"   



//������  Ӳ�Ҳ���  ��ȡ�� ���� �������� 
#define BITNUM 60  //��ȡÿ���ļ���ֵλ��



//���ݱ��� ���� ����ֵ
//���ֶ���
#define CN0 0   // �����
#define CN1 1   // ŷԪ
#define CN2 2   // ��Ԫ
#define CN3 3   // Ӣ��

///////tubiao number of coin name 
#define CNNM0 0   // 1Ԫ
#define CNNM1 1		// 5��ͭ
#define CNNM2 2		// 5�Ǹ� 
#define CNNM3 3		// 1�Ǵ���
#define CNNM4 4		// 1��С��
#define CNNM5 5		// 5��
#define CNNM6 6		// 2��
#define CNNM7 7		// 1��
#define CNNM8 8		// 1��С��




#define MAXNUM0 15
#define MINNUM0 15
#define MAXNUM1 15
#define MINNUM1 15
#define MAXNUM2 15
#define MINNUM2 15

extern U8 coinchoose;    // ����ѡ��
#define WKTFORS 0x00  // 2*0.25S // ��ҵ�� ���ֹͣ  ʱ��
void yqi2c_init(void);   //Ӳ����ֻ� I2C��ʼ�� 



struct coinamount    
{
	U16 db_total_item_num;
	U32 ze_coin;
	U32 zs_coin;
	U32 fg_coin;
};
//extern  struct coinamount accoinamount[COINCNUM];

struct stdval_coin      //������ѧϰ   ���׼ֵ
{
	U16 stdnum;
	U16 std0;
	U16 std1;
	U16 std2;
};
extern  struct stdval_coin stdvalue_coin[COINCNUM][9];  //���ݱ��־���  ���� ��ֵ �Ļ�׼����ֵ

//////////////////////////////////////////////////////////////
struct preval_coin      //������ѧϰ    �����ֵ ��Сֵ  
{
	S16 coinnum;
	S16 coin_max0;
	S16 coin_min0;
	S16 coin_max1;
	S16 coin_min1;
	S16 coin_max2;
	S16 coin_min2;
};
extern struct preval_coin prevalue_coin[COINCNUM][9];// ���ݱ��־��� ��ǰ�ı��� Ӳ�� ��ѧϰֵ��Χ 

struct learndvalue
{
	U16 d0value;
	U16 d1value;
	U16 d2value;
};
//extern struct learndvalue prelearndvalue[COINCNUM][9];	   //���ݱ��ּ���� ѡ��Ƚ� ����ѧϰֵ�Ĳ�ֵ��Χ
//


#define COIN0STD0  pre_value.country[coinchoose].coin[CNNM0].data.std0
#define COIN0STD1  pre_value.country[coinchoose].coin[CNNM0].data.std1
#define COIN0STD2  pre_value.country[coinchoose].coin[CNNM0].data.std2


#define COIN1STD0  pre_value.country[coinchoose].coin[CNNM1].data.std0
#define COIN1STD1  pre_value.country[coinchoose].coin[CNNM1].data.std1
#define COIN1STD2  pre_value.country[coinchoose].coin[CNNM1].data.std2


#define COIN2STD0  pre_value.country[coinchoose].coin[CNNM2].data.std0
#define COIN2STD1  pre_value.country[coinchoose].coin[CNNM2].data.std1
#define COIN2STD2  pre_value.country[coinchoose].coin[CNNM2].data.std2


#define COIN3STD0  pre_value.country[coinchoose].coin[CNNM3].data.std0
#define COIN3STD1  pre_value.country[coinchoose].coin[CNNM3].data.std1
#define COIN3STD2  pre_value.country[coinchoose].coin[CNNM3].data.std2


#define COIN4STD0  pre_value.country[coinchoose].coin[CNNM4].data.std0
#define COIN4STD1  pre_value.country[coinchoose].coin[CNNM4].data.std1
#define COIN4STD2  pre_value.country[coinchoose].coin[CNNM4].data.std2


#define COIN5STD0  pre_value.country[coinchoose].coin[CNNM5].data.std0
#define COIN5STD1  pre_value.country[coinchoose].coin[CNNM5].data.std1
#define COIN5STD2  pre_value.country[coinchoose].coin[CNNM5].data.std2


#define  COIN6STD0  pre_value.country[coinchoose].coin[CNNM6].data.std0
#define  COIN6STD1  pre_value.country[coinchoose].coin[CNNM6].data.std1
#define  COIN6STD2  pre_value.country[coinchoose].coin[CNNM6].data.std2


#define COIN7STD0  pre_value.country[coinchoose].coin[CNNM7].data.std0
#define COIN7STD1  pre_value.country[coinchoose].coin[CNNM7].data.std1
#define COIN7STD2  pre_value.country[coinchoose].coin[CNNM7].data.std2


#define COIN8STD0  pre_value.country[coinchoose].coin[CNNM8].data.std0
#define COIN8STD1  pre_value.country[coinchoose].coin[CNNM8].data.std1
#define COIN8STD2  pre_value.country[coinchoose].coin[CNNM8].data.std2

//void Write_value(int coinsellect);    //д�� ����ֵ ��׼ֵ  ���ݱ���д
//void ini_picaddr(void);  //�����л�ʱ�� ��ʼ����ַ����
extern U8 dgus_readt[6];  // only need y-m-d h:m  ��ʱ��
void print_func(void);   //��ӡ ���� 


// ����������ŵĸ�ֵ JM11 JM01 JM21L04 JM21L03 EM02 EM01 �� EM03
#define  SONUM 8     		 //������� ����   

#define  EM_STOP  7 	//EM03   SDDATA1/GPE8

#define EM_P04I1   5  //EM02  SDDATA0/GPE7
#define EM_P05I0   4  //EM02  SDDATA0/GPE7

#define  EM_KICK  4		//EM02  SDDATA0/GPE7
#define  EM_KICKBACK  5		//EM01 SDCMD/GPE6 

#define  MT_STORE  1	//JM01 chuansong SPIMOSI/GPE12 
#define  MT_PUSH  0	//JM11 PRESS nCD_SD/EINT16/GPG8 
#define  MT_PANRIGHT  2		//JM21 L03  SDDATA2/GPE9
#define  MT_PANLEFT  3	 //JM21 L04  SDDATA3/GPE10


#define DEVSTARTRUN 0	// �豸���� 
#define DEVSTOPRUN 1	// �豸ֹͣ���� 

#define BEEPSTARTRUN 1	// �豸���� 
#define BEEPSTOPRUN 0	// �豸ֹͣ���� 

// ���� ���� 1 �� ���� 1 ת���� ѹ�� ����  ���� 
#define SINUM 8     //  �������������� ����






#endif
