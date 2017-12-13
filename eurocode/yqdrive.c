#include "s3c2416.h"
#define WUBITIMEBEISHU 50  //20m һ�ζ�ʱ ��ʱ���ޱҶ�ʱΪ1S������Ϊ 50
#define RUBIYANSHIBEISHU 10 //	 20m һ�ζ�ʱ ,��Ҷ���ʱ һ�����20*10m��������Ϊ10 
void deviceinit(void)	//�����Ȱ�ͨ���ϵıҵ���ȥ 
{
	int i = 0;
	int good_coin;
	
	my_println("begin init %d ...", coin_env.full_stack_num);
	for (i = 0; i < coin_env.full_stack_num; i++){
		my_println("begin init i %d", i);
		good_coin = coin_env.full_coin_stack[i];
		if (coin_num[good_coin] >= *pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_set){
			coin_num[good_coin] = 0;
			*(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_current) = 0;
			*pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_full_flag = 0;
		}
	}
	my_println("finish init 0");	
	disp_allcount();
	coin_env.full_stack_num = 0;
	ch0_count =0;
	ch1_count =0;
	ch2_count =0;
	coin_env.ad0_step = 0;		
	coin_env.ad1_step = 0;
	coin_env.ad2_step = 0;
	ccstep = 0;
	processed_coin_info.coinnumber = 0;
	blockflag = ADBLOCKT;
	kickstep = 0;   //�߱Ҽ�⺯�� �����
	runstep =0; //�������������	
	my_println("finish init 1");		
}

volatile U32 runtime = 0;   // // ִ�м� �õļ�ʱ
volatile U32 coininmttime = 0;   //��ҵ���õļ�ʱ
volatile U32 panruntime = 0;    //ת���õ� ��ʱ
volatile U32 pressnocointime = 0;    //��ʱ���ޱ�ͨ���� ��ʱ
volatile U32 nocoindtmetal = 0;



unsigned short int runstep = 0;   //  �������������
unsigned short int panlefttime =0;   //ת����ת ʱ�����
unsigned int cannotputcoin = 0; // ��� �� ���� ״̬��ʾ
unsigned short int testnocoinflag = 0;	 //�ޱ� ��ת���� ����
unsigned char panprestate = 0;   //ת��ǰһ��״̬
unsigned char metalprestate = 0;   //���������� ǰһ��״̬
 
unsigned short int kickstep = 0;	 //�߱ҳ��� �����
unsigned short int forgeflag = 0;  //�ٱ� �߱ҳ����־λ
volatile U32 time = 0;   // //�߱ҵ���� �õļ�ʱ

#define FCNOCOMET   195		//�궨��  ���ʱ�������������û��⵽�ұ��߱��쳣   1MS��ʱ
#define BACKTIME   38	//�߱ҵ����  �ջ� ����ʱ��	  1MS��ʱ



void detectforge(void)
{
	//switch(coin_env.kickstep){
		//case 0:
	if(forgeflag == 2){  
		forgeflag = 0;
		if (coin_env.kick_Q[coin_env.kick_Q_index] == 0){
			coin_env.kick_Q[coin_env.kick_Q_index] = para_set_value.data.kick_start_delay_t1;
			Timer3_Start();//����ʱ��3  	TIME�����涨ʱ
			coin_env.kick_remain++;
			coin_env.kick_total++;
			coin_env.kick_Q_index++;
			if (coin_env.kick_Q_index >= KICK_Q_LEN){
				coin_env.kick_Q_index = 0;
			}
		}else{
			my_println ("kick1 error %s, %d", __FILE__, __LINE__);
		}
	}
}

unsigned int coinintime = 0;	//�����ʱ��

void coin_detect_func(void)   
{
 	if(COIN_DETECT == 0){        //������ۼ�⵽Ӳ��
		if(coin_env.coin_Q[coin_env.coin_Q_index] == 2){  
			if (coin_env.full_kick_Q[coin_env.full_kick_Q_index] == 0){
				coin_env.full_kick_Q[coin_env.full_kick_Q_index] = para_set_value.data.kick_start_delay_t2;
				Timer3_Start();//����ʱ��3  	TIME�����涨ʱ
				coin_env.full_kick_remain++;
				coin_env.full_kick_total++;
				coin_env.full_kick_Q_index++;
				if (coin_env.full_kick_Q_index >= KICK_Q_LEN){
					coin_env.full_kick_Q_index = 0;
				}
			}else{
				my_println ("kick2 error %s, %d", __FILE__, __LINE__);
			}
		}
		coin_env.coin_Q[coin_env.coin_Q_index] = 0;
		coin_env.coin_Q_index++;
		if (coin_env.coin_Q_remain >= KICK_Q_LEN){
			coin_env.coin_Q_remain = 0;
			if (coin_env.coin_Q_remain == (KICK_Q_LEN - 1)){
				alertflag = KICKCOINERROR;
				my_env.workstep =88;
			}
		}
		if (coin_env.coin_Q_index > coin_env.coin_Q_remain){
			alertflag = KICKCOINERROR;
			my_env.workstep =88;
		}
	}else{
	}
}

void runfunction(void)   //������������
{
	switch (runstep){
		case 0:
			STORAGE_MOTOR(STARTRUN);	//  ת�̵��
			runstep = 1;
			break;
		case 1:
			break;
		case 20:
			STORAGE_MOTOR(STOPRUN);	//  ת�̵��
			runtime = 100; // 2��
			runstep = 100;
			break;
		case 40:
			STORAGE_MOTOR(STOPRUN);	//  ת�̵��
			runtime = 100; // 2��
			runstep = 120;
			break;
		case 100:
			if (runtime == 0){
				prepic_num = JSJM;
				alertflag = COUNT_FINISHED;
				my_env.workstep =88;
			}
			break;
		case 120:
			if (runtime == 0){
				comscreen(Disp_Indexpic[JSJM],Number_IndexpicB);	 // back to the  picture before alert
				my_env.workstep = 0;
			}
			break;
		default:break;
	}
}


