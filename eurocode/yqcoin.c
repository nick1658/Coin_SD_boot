//////  ���������� ����  ��ѧϰ

#include "s3c2416.h"

/////////////////////////////////////////////////
 U16 ccstep = 0;
 U32 temp_coinnum =0;   //for compare the coin number, check 

S16 coin_value0 =0;
S16 coin_value1 =0;
S16 coin_value2 =0;

 U32 ch0_counttemp =0;  // ǰһ��ͨ��0 ͨ����Ӳ�Ҽ��� 
 U32 ch1_counttemp =0;  // ǰһ��ͨ��1 ͨ����Ӳ�Ҽ��� 
 U32 ch2_counttemp =0;  // ǰһ��ͨ��2 ͨ����Ӳ�Ҽ��� 

 S16 coin_maxvalue0 = AD0STDSET;
 S16 coin_minvalue0 = AD0STDSET;
 S16 coin_maxvalue1 = AD1STDSET;
 S16 coin_minvalue1 = AD1STDSET;
 S16 coin_maxvalue2 = AD2STDSET;
 S16 coin_minvalue2 = AD2STDSET;
s_processed_coin_info processed_coin_info;

//4*9
U16 coine[COINCNUM][COIN_TYPE_NUM]=     // �ɱ��־���
{
{100,	50,	50,10,10,5,2,1,10,1000,	500},	//����� ����ֵ ����  ���ڼ�����
{200,	100,50,20,10,5,2,1,0, 0, 	0},//ŷԪ�� ����ֵ ����
{100, 	50,	25,10, 5,1,0,0,0, 0, 	0},//��Ԫ�� ����ֵ ����	 ʵ������100����û����������ֱ����0
{200,	100,50,20,10,5,2,1,0, 0, 	0},//Ӣ���� ����ֵ ����
};


void prepare_coin_cmp_value (void)
{		
	if (ad1_min > 20){
		coin_env.cmp_use_index = 1;
	}else if ( ad0_min > 20){
		coin_env.cmp_use_index = 0;
	}else if (ad2_min > 20){
		coin_env.cmp_use_index = 2;
	}else{
		coin_env.cmp_use_index = 0;
	}	
#ifdef SAMPLE_METHOD_0
	coin_value0 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD0;
	coin_value1 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD1 - coin_value0;
	coin_value2 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD2 - Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD1;
#endif
#ifdef SAMPLE_METHOD_1
	coin_value0 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD0;
	coin_value1 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD1;
	coin_value2 = Detect_AD_Value_buf[coin_env.AD_min_index[coin_env.cmp_use_index]].AD2;
#endif
}

S16 is_good_coin (void)
{
	
	S16 i;
	for (i = 0; i < COIN_TYPE_NUM; i++){
		if   ( (( coin_value0 >= coin_cmp_value[i].compare_min0) && ( coin_value0 <= coin_cmp_value[i].compare_max0))
			&& (( coin_value1 >= coin_cmp_value[i].compare_min1) && ( coin_value1 <= coin_cmp_value[i].compare_max1))
			&& (( coin_value2 >= coin_cmp_value[i].compare_min2) && ( coin_value2 <= coin_cmp_value[i].compare_max2)))
		{
			if (my_env.save_good_data){
				GOOD_value_buf[good_value_index].AD0 = coin_value0;
				GOOD_value_buf[good_value_index].AD1 = coin_value1;
				GOOD_value_buf[good_value_index].AD2 = coin_value2;
				GOOD_value_buf[good_value_index].use_index = coin_env.cmp_use_index;
				good_value_index++;
				if (good_value_index >= GOOD_BUF_LENGTH)
					good_value_index = 0;
			}
			return i;
		}	
	}
	if (my_env.save_ng_data){
		NG_value_buf[ng_value_index].AD0 = coin_value0;
		NG_value_buf[ng_value_index].AD1 = coin_value1;
		NG_value_buf[ng_value_index].AD2 = coin_value2;
		NG_value_buf[ng_value_index].use_index = coin_env.cmp_use_index;
		ng_value_index++;
		if (ng_value_index >= NG_BUF_LENGTH)
			ng_value_index = 0;
	}
	return -1;
}

U32 coin_num[COIN_TYPE_NUM];    //������ ��������

//Ӳ�Ҽ�������
void my_coincount(void)
{
	switch(ccstep)
	{
		case 0:
		{	
			//ch0_count ͨ��0 1 2����,��ʼ��ֵ,		
			if ( (ch0_counttemp != ch0_count) && (ch1_counttemp != ch1_count) && (ch2_counttemp != ch2_count)){	//mean there is a coin come
				/*ad2_valueget step 0��ֵ,���︳ֵ*/
				ch0_counttemp = ch0_count;
				ch1_counttemp = ch1_count;
				ch2_counttemp = ch2_count;
				processed_coin_info.coinnumber++;
				prepare_coin_cmp_value ();
				/*����ѡ��*/
				ccstep = 8; 	
			}
			break;
		}	
		case 8:
		{
			S16 good_coin;
			good_coin = is_good_coin ();
			if (good_coin < 0){
				processed_coin_info.total_ng++;	
				forgeflag = 2;	//�ٱұ�־λ			
				coin_env.kick_remain++; //���޳��ٱ�������һ	
			}else{	
				coin_num[good_coin]++;
				processed_coin_info.total_money += pre_value.country[coinchoose].coin[good_coin].data.money;
				processed_coin_info.total_good++;
			}
			my_env.stop_time = STOP_TIME;//�ޱ�ͣ��ʱ��10��
			
			processed_coin_info.total_coin++;
			disp_allcount ();
			ccstep = 0; 
			return;
		}	
		default: ccstep = 0;break;
	}
	return;
}	



// ����ADֵ  Ԥ��  ����  �������  ���߳��ǵ�ǰ����  ���������� 


void my_precoincount(void)
{
	switch(ccstep)
	{
		case 0:
		{			
			if ( (ch0_counttemp != ch0_count) && (ch1_counttemp != ch1_count) && (ch2_counttemp != ch2_count))	//mean there is a coin come
			{
				ch0_counttemp = ch0_count;
				ch1_counttemp = ch1_count;
				ch2_counttemp = ch2_count;
				
				processed_coin_info.coinnumber++;
				
				prepare_coin_cmp_value ();
				ccstep = 8; 
			}
			break;
		}	
		case 8:
		{	 			
			S16 good_coin;
			good_coin = is_good_coin ();
			my_env.stop_time = STOP_TIME;//�ޱ�ͣ��ʱ��10��
			if (good_coin < 0){ //�ٱ� ����ֵС��0
				processed_coin_info.total_ng++;
				forgeflag = 2;	//�ٱұ�־λ	
			}else {
				if (*(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_set) == 9999){//ֻʹ����ֹ���
					coin_num[good_coin]++;
					processed_coin_info.total_money += pre_value.country[coinchoose].coin[good_coin].data.money;
					processed_coin_info.total_good++;
				}else if ((*(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_set) == 0) ||
							(*pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_full_flag == 1)){
					if (para_set_value.data.rej_position == 1){
						forgeflag = 2;	//�üٱ��޳���λ�޳�
					}else if (para_set_value.data.rej_position == 2){
						coin_env.coin_Q[coin_env.coin_Q_remain] = 2;//������޳���λ�޳�
					}
				}else{
					*(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_current) += 1;
					coin_num[good_coin]++;
					processed_coin_info.total_money += pre_value.country[coinchoose].coin[good_coin].data.money;
					processed_coin_info.total_good++;
					if( *(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_current) >= *(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_set)){// ��ǰ�ı���  ���� �ﵽ��Ԥ��ֵ
						*pre_value.country[COUNTRY_ID].coin[good_coin].data.p_pre_count_full_flag = 1; //����Ӳ��Ԥ���������������
						*(pre_value.country[COUNTRY_ID].coin[good_coin].data.p_coinval) += 1;
						coin_env.full_coin_stack[coin_env.full_stack_num] = good_coin;
						coin_env.full_stack_num++;
						if (coin_env.full_stack_num >= para_set_value.data.pre_count_stop_n){
							runstep = 20;   //��ʼͣ��
						}
					}
				}
				
				coin_env.coin_Q_remain++;
				if (coin_env.coin_Q_remain >= KICK_Q_LEN){
					coin_env.coin_Q_remain = 0;
				}
				if (coin_env.coin_Q_index == coin_env.coin_Q_remain){
					my_env.workstep =88;
				}
			}
			disp_allcount ();
			processed_coin_info.total_coin++;
			ccstep = 0;
			break;
		}		
	}
}







// ����ADֵ ������ȡ AD ���ֵ��Сֵ
U32 coinlearnnumber = 0;   //count the coin number all proceed
void my_coinlearn(void)
{
	switch(ccstep)
	{
		case 0:
		{			
			if ( (ch0_counttemp != ch0_count) && (ch1_counttemp != ch1_count) && (ch2_counttemp != ch2_count))	//mean there is a coin come
			{
				ch0_counttemp = ch0_count;
				ch1_counttemp = ch1_count;
				ch2_counttemp = ch2_count;
				processed_coin_info.coinnumber++;
				coinlearnnumber++;
				ccstep = 1;				
			}
			break;
		}	
		case 1:
		{						
			prepare_coin_cmp_value ();	
			ccstep = 8; 	
			break;
		}
		case 8:
		{	
			if( ( coin_value0 > coin_maxvalue0))     //0
			{
				coin_maxvalue0 = coin_value0;
			}
			if( ( coin_value0 < coin_minvalue0))
			{
				coin_minvalue0 = coin_value0;
			}
					
			if( ( coin_value1 > coin_maxvalue1))   //  1
			{
				coin_maxvalue1 = coin_value1;
			}
			if( ( coin_value1 < coin_minvalue1))
			{
				coin_minvalue1 = coin_value1;
			}
					
			if( ( coin_value2 > coin_maxvalue2))   //  2
			{
				coin_maxvalue2 = coin_value2;
			}
			if( ( coin_value2 < coin_minvalue2))
			{
				coin_minvalue2 = coin_value2;
			}
			ccstep = 11; 	
			break;
		}
		case 11:
		{
			dgus_tf1word(ADDR_A0MA,coin_maxvalue0);	//	 real time ,pre AD0  max
			dgus_tf1word(ADDR_A0MI,coin_minvalue0);	//	 real time ,pre AD0  min
			ccstep = 12; 
			break;	
		}
 		case 12:
		{
			dgus_tf1word(ADDR_A1MA,coin_maxvalue1);	//	 real time ,pre AD1  max	
			dgus_tf1word(ADDR_A1MI,coin_minvalue1);	//	 real time ,pre AD1  min
			ccstep = 13; 
			break;	
		}
		case 13:
		{
			dgus_tf1word(ADDR_A2MA,coin_maxvalue2);	//	 real time ,pre AD2  max
			dgus_tf1word(ADDR_A2MI,coin_minvalue2);	//	 real time ,pre AD2  min
			ccstep = 0; 
			break;			
		}	
											
	}
	return;
}
/*************************
**************************/

S8 spinvalue = 0x00;    //sample in pin value  ���������� ֵ
void detect_read(void)
{	
	if(PANCOIN_OVER == 0)    // 0x01 ����
		dgus_tf1word(ADDR_ZXD3,0);	 
	else
		dgus_tf1word(ADDR_ZXD3,1);	 
 	if(COIN_DETECT == 0)        //0x02 �� ���� 
		dgus_tf1word(ADDR_ZXD4,0);	 
	else
		dgus_tf1word(ADDR_ZXD4,1);	 
	if(PRESS_MICROSW == 0)   // 0x04 ѹ��
		dgus_tf1word(ADDR_ZXD2,0);	  
	else
		dgus_tf1word(ADDR_ZXD2,1);	 
	if(DC_COINOVER == 0)      // 0x08 �� ����
		dgus_tf1word(ADDR_ZXD7,0);	 
	else
		dgus_tf1word(ADDR_ZXD7,1);	
	if(DT_NOMETAL == 0)      // 0x10�� ����1
		dgus_tf1word(ADDR_ZXD8,0);	 
	else
		dgus_tf1word(ADDR_ZXD8,1);	
 	if(DT_METAL == 0)    // 0x20 �� ����
		dgus_tf1word(ADDR_ZXD5,0);	 
	else
		dgus_tf1word(ADDR_ZXD5,1);	 
	if(DOOR_MAG == 0)      // 0x40 ����
		dgus_tf1word(ADDR_ZXD1,0);	  
	else
		dgus_tf1word(ADDR_ZXD1,1);	  
	if(DOOR_PAN == 0)      // 0x80 �� ����
		dgus_tf1word(ADDR_ZXD6,0);	 
	else
		dgus_tf1word(ADDR_ZXD6,1);	
}

const char *coin_tips [] = {"һԪ", "���", "���", "һ��", "һ��", "һ��", "���", "����", "һ��"};

 U16 prepic_prenum =0;      // ���ڼ�¼ ����ǰ�Ľ��� 
void alertfuc(U16 errorflag) //����
{
	char str_buf[256];
	//dgus_tfbeep(TIMEBP2);	//beep on for 100*10ms
	switch(errorflag)
	{
		case SWITCHERROR:
			break;					
		case STORAGEERROR:
			break;
		case DUIERROR:
			break;		
		case PANBLOCKEDERROR:
			break;
		case KICKCOINERROR:
			ALERT_MSG ("��ʾ", "�޳����󣬵ڶ����޳���λ��������ⲻ��Ӳ�ң�");
			break;														
		case NEGATIVEERROR:
			break;		
		case PRESSMLOCKED:
			ALERT_MSG ("��ʾ", "����±ң��������򴫸������ٴ�����ǰ�������㣡");
			break;	
		case ADSTDEEROR:
			ALERT_MSG ("��ʾ", "�������쳣���������׼ֵ��Ȼ�����ԣ�");
			break;	
		case RTCREEROR:	
			break;	
		case READOUTDATA:
			break;	
		case COUNT_FINISHED:
			switch (coin_env.full_stack_num){
				case 1:
					if (coin_env.full_coin_stack[0] < 8){
						sprintf (str_buf, "�����%s��ֽͲ��", coin_tips[coin_env.full_coin_stack[0]]);
					}else{
						sprintf (str_buf, "����Խ��: %d", coin_env.full_coin_stack[0]);
					}
					break;
				case 2:
					if ((coin_env.full_coin_stack[0] < 8) && 
						(coin_env.full_coin_stack[1] < 8)){
						sprintf (str_buf, "�����%s��%s��ֽͲ��", 	coin_tips[coin_env.full_coin_stack[0]], 
																	coin_tips[coin_env.full_coin_stack[1]]);
					}else{
						sprintf (str_buf, "����Խ��: %d, %d", coin_env.full_coin_stack[0], coin_env.full_coin_stack[1]);
					}
					break;
				case 3:
					if ((coin_env.full_coin_stack[0] < 8) && 
						(coin_env.full_coin_stack[1] < 8) &&
						(coin_env.full_coin_stack[2] < 8)){
						sprintf (str_buf, "�����%s��%s��%s��ֽͲ��", 	coin_tips[coin_env.full_coin_stack[0]], 
																		coin_tips[coin_env.full_coin_stack[1]], 
																		coin_tips[coin_env.full_coin_stack[2]]);
					}else{
						sprintf (str_buf, "����Խ��: %d, %d, %d", coin_env.full_coin_stack[0], coin_env.full_coin_stack[1], coin_env.full_coin_stack[2]);
					}
					break;
				default:sprintf (str_buf, "ERROR: 1001");break;
			}
			ALERT_MSG ("��ʾ", str_buf);
			break;	
		default:
			break;
	}
	return;
}
	


