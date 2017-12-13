#ifndef __YQDRIVE_H__
#define __YQDRIVE_H__


#define _MY_DEBUG_NO_DOOR_CHECK_
#define _MY_DEBUG_NO_PAN_BLOCK_ERROR_
#define _MY_DEBUG_NO_CHANEL_BLOCK_ERROR_
#define _MY_DEBUG_NO_KICK_ERROR_
//��� �˿�
#define STARTRUN 0
#define STOPRUN 1

////////////////////////////////////new pcb open this
//////////////////////////

	
#define OUT7(x)		(rGPGDAT = (rGPGDAT & (~0x8)) |(x<<3))	//EINT11/GPG3
#define OUT6(x) 	(rGPBDAT = (rGPBDAT & (~0x2)) |(x<<1))	 	//TOUT1/GPB1
#define OUT5(x) 	(rGPBDAT = (rGPBDAT & (~0x1)) |(x))	 	//TOUT0/GPB0
#define OUT4(x) 	(rGPHDAT = (rGPHDAT & (~0x2000)) |(x<<13))	//CLKOUT0/GPH13	
#define OUT3(x) 	(rGPHDAT = (rGPHDAT & (~0x4000)) |(x<<14))	//CLKOUT1/GPH14	
#define OUT2(x) 	(rGPGDAT = (rGPGDAT & (~0x80)) |(x<<7))	//EINT15/GPG7 
#define OUT1(x) 	(rGPFDAT = (rGPFDAT & (~0x2)) |(x<<1))	//EINT1/GPF1/sd0_CDN
#define OUT0(x) 	(rGPEDAT = (rGPEDAT & (~0x20)) |(x<<5))	//SD0_CLK/GPE5
				  
#define  PAN_MOTOR_LEFT(x) 	 OUT7(x)			//P2^0; 	//EINT11/GPG3 //  ת�̷�ת
#define  PAN_MOTOR_RIGHT(x)  OUT6(x)			//P2^1; TOUT1/GPB1  //  ת����ת PAN_MOTOR_RIGHT(x)
#define  PRESS_MOTOR(x) 	 OUT5(x)			//P2^2; TOUT0/GPB0  //ѹ�ҵ��

#define  STORAGE_MOTOR(x) 	 OUT1(x)			//P2^3; CLKOUT0/GPH13  //��������
#define  EMKICK1(x) 		 OUT3(x)			//P2^4; CLKOUT1/GPH14      // kick out 
#define  EMKICK2(x) 		 OUT2(x)			//P2^5; //EINT15/GPG7   //kick back
//#define  STOPCOIN_ELECMAG(x) OUT1(x) 			//P2^6; EINT1/GPF1/SD0_CDn  // ת����ҵ����



//���� �˿�
#define DUINOWU 1       //���� ���� Ϊ��ƽ 0  ��������Ϊ 1
#define DUIHAVE 0       //���� ���� Ϊ��ƽ 1 

#define A0IN7 	((rGPEDAT & 0x40)>>6)	//SD0_CMD/GPE6
#define A0IN6 	((rGPEDAT & 0x80)>>7)	//SD0_DAT0/GPE7
#define A0IN5 	((rGPEDAT & 0x100)>>8)	//SD0_DAT1/GPE8
#define A0IN4 	((rGPEDAT & 0x200)>>9)	//SD0_DAT2/GPE9
#define A0IN3 	((rGPEDAT & 0x400)>>10)	//SD0_DAT3/GPE10

////////////////////////////////////old pcb open this
//#define A0IN0 	((rGPGDAT & 0x10)>>4)	//EINT12/GPG4
//#define A0IN1 	((rGPGDAT & 0x20)>>5)	//EINT13/GPG5
//#define A0IN0 	((rGPGDAT & 0x40)>>6)	//EINT14/GPG6
////////////////////////////////////new pcb open this
#define A0IN2 	((rGPGDAT & 0x40)>>6)	//EINT14/GPG6
#define A0IN1 	((rGPGDAT & 0x20)>>5)	//EINT13/GPG5
#define A0IN0 	((rGPGDAT & 0x10)>>4)	//EINT12/GPG4


#ifdef _MY_DEBUG_NO_DOOR_CHECK_
	#define COIN_DETECT      1	//P0^0;  //ת�̲��ʹ�����       EINT12/GPG4  	
	#define PANCOIN_OVER  0	//P0^1;  //ת�����Ҷ��䴫����   EINT13/GPG5 
	#define DC_COINOVER   1	//P0^2;  // ��� ���� ������    EINT14/GPG6 
	#define DOOR_MAG      0	//P0^3;  //ѹ�Ҵ��� ������      SD0_DAT3/GPE10
	#define DOOR_PAN      0	//P0^4;  //ת���� ������  	    SD0_DAT2/GPE9
	#define PRESS_MICROSW 0	//P0^5; //ѹ�Ҵ�ѹ�ϴ�����   	SD0_DAT1/GPE8
	#define DT_METAL      1	//P0^6; //��ٱҽ���������   	SD0_DAT0/GPE7
	#define DT_NOMETAL    1	//P0^7 ;  // ��϶����������  	SD0_CMD/GPE6
#else
	#define COIN_DETECT      A0IN0	//P0^0;  //ת�̲��ʹ�����       EINT12/GPG4  	
	#define PANCOIN_OVER  A0IN1	//P0^1;  //ת�����Ҷ��䴫����   EINT13/GPG5 
	#define DC_COINOVER   A0IN2	//P0^2;  // ��� ���� ������    EINT14/GPG6 
	#define DOOR_MAG      A0IN3	//P0^3;  //ѹ�Ҵ��� ������      SD0_DAT3/GPE10
	#define DOOR_PAN      A0IN4	//P0^4;  //ת���� ������  	    SD0_DAT2/GPE9
	#define PRESS_MICROSW A0IN5	//P0^5; //ѹ�Ҵ�ѹ�ϴ�����   	SD0_DAT1/GPE8
	#define DT_METAL      A0IN6	//P0^6; //��ٱҽ���������   	SD0_DAT0/GPE7
	#define DT_NOMETAL    A0IN7	//P0^7 ;  // ��϶����������  	SD0_CMD/GPE6
#endif

////////////////////////////
void deviceinit(void);	//�����Ȱ�ͨ���ϵıҵ���ȥ 

#define METALSTATIONNO  1
#define METALSTATIONYES 0

#define PRETIME 50//50*20MS			//���� ����  ����ʱ��  �о��ǵ�ת��ֹͣ��ѹ�Ҵ�����ֹͣ��ʱ��
#define PANLEFTNUM 40  //ת�̵�ת�Ĵ���
#define TESTNOCOINTIME 2 //������Ƕ±� û�� ��ת�Ĵ���
#define STOPCYTIME 2    //ת�̵���� ����ʱ��	2*20MS
#define PANDCTESTTIME 12   //ת�̲��ͼ���תʱ�� 12*20MS
#define COINTESTSECOND 100    //��ʱ��û��  ��ת�����ߵ�ʱ�� 100*20MS
#define PANSTOPTIME 41   //ת�� ͣ��ʱ��   41*20ms
#define ADTESTTIME 75 //֪ͨ��׼ ʵʱ��� ���  75*20MS
#define NOCOINADBEGIN  3   //��ô��ʱ���� ��϶������������û�м�⵽Ӳ�� �ͽ���AD��ƫ

#define STOP_TIME para_set_value.data.motor_idle_t//�ޱ�ͣ��ʱ��10��



extern volatile U32 runtime;   // // ִ�м� �õļ�ʱ
extern volatile U32 coininmttime;   //��ҵ���õļ�ʱ
extern volatile U32 panruntime;   //ת���õ� ��ʱ
extern volatile U32 pressnocointime;    //��ʱ���ޱ�ͨ���� ��ʱ
extern volatile U32 nocoindtmetal ;  //2������������ʱ��û��  

extern unsigned short int runstep;  //  �������������
extern unsigned short int panlefttime;  //ת����ת ʱ�����
extern unsigned int cannotputcoin; // ��� �� ���� ״̬��ʾ
 
extern unsigned short int kickstep;
extern unsigned short int forgeflag;
extern volatile U32 time;   // //�߱ҵ���� �õļ�ʱ



void coin_detect_func(void);    //  �������
void runfunction(void);   //������������
void detectforge(void);	 //�߱ҳ���










#endif /*__YQDRIVE_H__*/
