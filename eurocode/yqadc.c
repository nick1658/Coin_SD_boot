////
#include "s3c2416.h"

s_coin_env coin_env;// (std_ad0-40)  //�����½� ��ֵ  990   950  ��ǰ��׼�½�40  


void adcsininget(U16 ad0,U16 ad1,U16 ad2)
{
	
	coin_env.std_down_value0= (ad0-50);  //�����½� ��ֵ 40  	
	coin_env.std_up_value0= (ad0-30);  //���λָ� 20
	//my_println( "up: %d", coin_env.std_down_value0);
	//my_println( "dn: %d", coin_env.std_up_value0);
}

void setStdValue (void)
{
	U16 is;
		////////////////////////////////////
	U16 ad0_std[AD0STDNUM];
	U16 ad2_std[AD2STDNUM];
	U16 ad1_std[AD1STDNUM];

	for(is=0;is<AD0STDNUM;is++)
	{
		ad0_std[is] = ReadAdc0();
	}
	std_ad0 = (ad0_std[2]  +ad0_std[4]+ad0_std[5]+ad0_std[7]+ad0_std[9])/5;

	
/////////////////////////
	for(is =0;is<AD2STDNUM;is++)
	{
		ad2_std[is] = ReadAdc2();	
	}
	std_ad2 = (ad2_std[2]+ad2_std[3]+ad2_std[4] +ad2_std[5] +ad2_std[6] +ad2_std[7]+ad2_std[8] +ad2_std[9])/8;
	/////////////////////////////////////////
	for(is=0;is<AD1STDNUM;is++)
	{
		ad1_std[is] = ReadAdc1();
	}
	std_ad1  = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
//	Uart0_Printf("A0 :%d   A1 :%d  A2 :%d  \r\n",std_ad0,std_ad1,std_ad2);
	
	/////////////////////////ÿ��Ӳ�� �������в��� 
	
	adcsininget(std_ad0,std_ad1,std_ad2);//AD ���ν��� �ķ�ֵ
}

volatile U32 adtime = 0;    //��ʱ�ж��� ��ʱ

//////////////////////////////////////////////////////
 U16 ad0_mintemp = 0;    // = AD0STDVALUE;		//��Ϊ ��ad1_ad_value ֵ���бȽϵ�ֵ��Ϊ��ȡ�ò������ֵ
 U16 ad0_maxtemp = 0;   //���λָ�  �ο��Ƚ�ֵ
 U16 wave0down_flagone = 0;
 U16 wave0up_flagone = 0;    //�������� �ο��Ƚ�ֵ
 U16 wave0up_flag = 0;
 U16 wave0down_flagtwo =0;   //˫��ʱ�������жϵڶ�����
 U32 ch0_count =0;  //ͨ��0 ͨ����Ӳ�Ҽ��� 
 U32 ch0_pre_count =0;  //ͨ��0 ��Ӳ�� ���  
 U32 ch0_coin_come =0;  //ͨ�� ��Ӳ�� ���
 U16 ch0_coin_leave = 0;
 volatile U16 blockflag = 0;      //ʹ�ü�α������ ���±�
 U16 ad0_min = 0;     //����ÿöӲ�ҹ�ȥ��� ���ֵ
 
 
//S16 coin_env.ad0_averaged_value = 0;    //�����й����� ��ADSAMPNUM�� value�����ֵ
 S16 ad0_ad_value = 0;  //�����й����� ��ADSAMPNUM�� value�ĺ�ֵ��ƽ��ֵ


 S16 ad0_temp_value = 0;  //����ƽ��ֵʱ�õ�����ʱ ����
 S16 ad0_samp_number = 0;   // ad value sample times 
 S16 ad1_temp_value = 0;  //����ƽ��ֵʱ�õ�����ʱ ����
 S16 ad1_samp_number = 0;   // ad value sample times 
 S16 ad2_temp_value = 0;  //����ƽ��ֵʱ�õ�����ʱ ����
 S16 ad2_samp_number = 0;   // ad value sample times 
 
 S16 ad0_ad_value_buf[ADSAMPNUM0];	//ad value sample  ADSAMPNUM times 
 S16 ad1_ad_value_buf[ADSAMPNUM0];	//ad value sample  ADSAMPNUM times 
 S16 ad2_ad_value_buf[ADSAMPNUM0];	//ad value sample  ADSAMPNUM times 



 U16 ad1_ad_value= 0;	//ad value sample  ADSAMPNUM times 
 U16 ad1_mintemp = 0;// = AD1STDVALUE;		//��Ϊ ��ad1_ad_value ֵ���бȽϵ�ֵ��Ϊ��ȡ�ò������ֵ
 U16 ad1_maxtemp = 0;   //���λָ�  �ο��Ƚ�ֵ
 U16 wave1down_flagone = 0;
 U16 wave1up_flagone = 0;    //�������� �ο��Ƚ�ֵ
 U16 wave1up_flagtwo = 0;
 U16 wave1down_flagtwo = 0;   //˫��ʱ�������жϵڶ�����
 U32 ch1_count =0;  //ͨ��1 ͨ����Ӳ�Ҽ��� 
// U32 ch1_come =0;  //ͨ�� ��Ӳ�� ���
 U16 ad1_min = 0;     //����ÿöӲ�ҹ�ȥ��� ���ֵ
 U32 ch1_coin_come =0;  //ͨ��0 ��Ӳ�� ���


 U16 ad2_ad_value = 0;	//ad value sample  ADSAMPNUM times 
 U16 ad2_mintemp = 0;		//��Ϊ ��ad2_ad_value ֵ���бȽϵ�ֵ��Ϊ��ȡ�ò������ֵ
 U16 wave2up_flagone =0;    //�������� �ο��Ƚ�ֵ
 U32 ch2_count =0;  //ͨ��2 ͨ����Ӳ�Ҽ��� 
 U32 ch2_coin_come =0;  //ͨ��0 ��Ӳ�� ���
// U32 ch2_chonetemp =0;  //ͨ��1 ��Ӳ�� ���
 U16 ad2_min = 0;     //����ÿöӲ�ҹ�ȥ��� ���ֵ
 U32 ch1_count1temp =0;  //ͨ��1 ��Ӳ�� ���  


//ģ��ת��  0  ����
//Ŀǰ��������ƽ���˲��㷨���д��� N= 10 ���һ�����������˲������д����жϲ��ε�����
//////���Գ���һ����λֵƽ���˲�����
//////���߳���һ����λֵ�˲�����

void coin_env_init (void)
{
	int i;
	S8 *p = (S8 *) &coin_env;
	for (i = 0; i < sizeof(s_coin_env); i++)
	{
		*(p++) = 0;
	}	
}

void AD_Sample_All (void)
{
	//Read AD 0 ////////////////////////////////////////////////////////////////////////////////////////
	rADCMUX = 0;		//setup channel
	rADCCON|=0x1;									//start ADC
	while(rADCCON & 0x1);							//check if Enable_start is low
	
	//PreProcess AD 0 Start*********************************************************************
	ad0_temp_value = ad0_ad_value_buf[ad0_samp_number];//old ad0_samp_number = 0����һ�β���ֵ,����2
	coin_env.ad0_averaged_value -= ad0_temp_value;//��ͼ�ȥ��һ��ADֵ
	//PreProcess AD 0 End**********************************************************************
	
	while(!(rADCCON & 0x8000));						//check if EC(End of Conversion) flag is high
	ad0_ad_value_buf[ad0_samp_number] = ((int)rADCDAT0 & 0x3ff);
	
	//Read AD 1 ////////////////////////////////////////////////////////////////////////////////////////
	rADCMUX = 0x01;		//setup channel
	rADCCON|=0x1;									//start ADC
	while(rADCCON & 0x1);							//check if Enable_start is low
	
	//Process AD 0 Start ***********************************************************************
	/*coin_env.ad0_averaged_value �����*/
	coin_env.ad0_averaged_value += ad0_ad_value_buf[ad0_samp_number];//coin_env.ad0_averaged_value ��ֵ�����				
	ad0_ad_value = (coin_env.ad0_averaged_value)/ADSAMPNUM0;   //��ǰ�����ܺͺ���ƽ��ֵ
	Detect_AD_Value_buf[detect_sample_data_buf_index].AD0 = ad0_ad_value; // save ad to buf
	ad0_samp_number++;
	if( (ad0_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������10
	{
		ad0_samp_number = 0;
	}
	//Process AD 0 End ***********************************************************************
	
	//PreProcess AD 1 Start*********************************************************************
	ad1_temp_value = ad1_ad_value_buf[ad1_samp_number];//old ad1_samp_number = 0����һ�β���ֵ,����2
	coin_env.ad1_averaged_value -= ad1_temp_value;//��ͼ�ȥ��һ��ADֵ
	//PreProcess AD 1 End**********************************************************************
	
	while(!(rADCCON & 0x8000));						//check if EC(End of Conversion) flag is high

	ad1_ad_value_buf[ad1_samp_number] = ((int)rADCDAT0 & 0x3ff);
	
	//Read AD 2 ////////////////////////////////////////////////////////////////////////////////////////
	rADCMUX = 0x02;		//setup channel
	rADCCON|=0x1;									//start ADC
	while(rADCCON & 0x1);							//check if Enable_start is low
	
	//Process AD 1 Start ***********************************************************************
	/*coin_env.ad1_averaged_value �����*/
	coin_env.ad1_averaged_value += ad1_ad_value_buf[ad1_samp_number];//coin_env.ad1_averaged_value ��ֵ�����				
	ad1_ad_value = (coin_env.ad1_averaged_value)/ADSAMPNUM0;   //��ǰ�����ܺͺ���ƽ��ֵ
	Detect_AD_Value_buf[detect_sample_data_buf_index].AD1 = ad1_ad_value; // save ad to buf
	ad1_samp_number++;
	if( (ad1_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������10
	{
		ad1_samp_number = 0;
	}
	//Process AD 1 End ***********************************************************************
	
	//PreProcess AD 2 Start*********************************************************************
	ad2_temp_value = ad2_ad_value_buf[ad2_samp_number];//old ad2_samp_number = 0����һ�β���ֵ,����2
	coin_env.ad2_averaged_value -= ad2_temp_value;//��ͼ�ȥ��һ��ADֵ
	//PreProcess AD 2 End**********************************************************************
	
	while(!(rADCCON & 0x8000));						//check if EC(End of Conversion) flag is high
	ad2_ad_value_buf[ad2_samp_number] = ((int)rADCDAT0 & 0x3ff);
	
	//Process AD 2 Start ***********************************************************************
	/*coin_env.ad2_averaged_value �����*/
	coin_env.ad2_averaged_value += ad2_ad_value_buf[ad2_samp_number];//coin_env.ad2_averaged_value ��ֵ�����				
	ad2_ad_value = (coin_env.ad2_averaged_value)/ADSAMPNUM0;   //��ǰ�����ܺͺ���ƽ��ֵ
	Detect_AD_Value_buf[detect_sample_data_buf_index].AD2 = ad2_ad_value; // save ad to buf
	ad2_samp_number++;
	if( (ad2_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������10
	{
		ad2_samp_number = 0;
	}
	//Process AD 2 End ***********************************************************************
	
	detect_sample_data_buf_index++;
	if (detect_sample_data_buf_index >= DATA_BUF_LENGTH){
		detect_sample_data_buf_index = 0;
	}
}

U32 coin_cross_time = 0;
	
void my_ad0_valueget(void)
{
	//S16 std0_offset, std1_offset, std2_offset;
	//U16 is;
	switch(coin_env.ad0_step)
	{ 
/*Ԥ���ӳ�,��ʼ��ֵ*/
		case 0: 
		{
			cmd();
			my_println ("Start Detect");
			cmd();
			
			ch0_count = 0;
			ch0_counttemp = ch0_count;
			ch0_pre_count = ch0_count;
			
			ch0_coin_leave = 0;
			ch0_coin_come = 0;
			
			wave0down_flagone = 0;
			wave0up_flagone = 0;
			wave0down_flagtwo = 0;	
			
			detect_sample_data_buf_index = 0;
			
			ad0_samp_number = 0;
			coin_env.ad0_averaged_value = 0;

			ad0_ad_value = AD0STDSET;
			ad0_mintemp = AD0STDSET;//900
			ad0_min = AD0STDSET;//900
			
			blockflag = ADBLOCKT;	   //ʹ�ü�α������ ���±� �±�ʱ��5
			coin_env.ad0_step = 2;
			break;
		}
/*��ȡͨ��0,ad0_ad_value����10����Ϊ��ֵ*/
		case 2:
		{
			//my_println ("Start Sample AD0");
			ad0_ad_value_buf[ad0_samp_number] = ReadAdc0();
			coin_env.ad0_averaged_value += ad0_ad_value_buf[ad0_samp_number];   //��ǰ�����ܺ�
			ad0_samp_number++;
			blockflag = ADBLOCKT;//�±�ʱ��5
			if( (ad0_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������ 10
			{
				ad0_samp_number = 0;
				ad0_ad_value = coin_env.ad0_averaged_value/ADSAMPNUM0;   //��ǰ�����ƽ��ֵ
				coin_env.ad0_step = 3; //10 �βŻ���������3
					
				dbg ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
			}
			break;
		}
/*�����Ա�,�ɲ���10��ֵ-�ɲ���ĳ��ֵ+��ǰ����ֵ/����*/
		case 3: 
		{
			AD_Sample_All ();
			blockflag = ADBLOCKT;	   //ʹ�ü�α������ ���±�
			coin_env.ad0_step = 6;
			ch0_coin_leave = 0;
			/* 
			if ((detect_sample_data_buf_index) > para_set_value.data.adj_offset_position){
				detect_sample_data_buf_index -= 3000;
//					Uart0_Printf("%d	%d	%d	\n",
//								Detect_AD_Value_buf[detect_sample_data_buf_index].AD0, 
//								Detect_AD_Value_buf[detect_sample_data_buf_index].AD1,
//								Detect_AD_Value_buf[detect_sample_data_buf_index].AD2);
				for (is = 0; is < COIN_TYPE_NUM; is++){ //����ֵ
					std0_offset = Detect_AD_Value_buf[detect_sample_data_buf_index].AD0 - pre_value.country[coinchoose].coin[is].data.std0;
					std1_offset = Detect_AD_Value_buf[detect_sample_data_buf_index].AD1 - pre_value.country[coinchoose].coin[is].data.std1;
					std2_offset = Detect_AD_Value_buf[detect_sample_data_buf_index].AD2 - pre_value.country[coinchoose].coin[is].data.std2;
				#ifdef SAMPLE_METHOD_0
					coin_cmp_value[is].compare_max0 = (pre_value.country[coinchoose].coin[is].data.max0 + pre_value.country[coinchoose].coin[is].data.offsetmax0 + 
													  std0_offset);
					coin_cmp_value[is].compare_min0 = (pre_value.country[coinchoose].coin[is].data.min0 + pre_value.country[coinchoose].coin[is].data.offsetmin0 + 
													  std0_offset);
					
					coin_cmp_value[is].compare_max1 = (pre_value.country[coinchoose].coin[is].data.max1 + pre_value.country[coinchoose].coin[is].data.offsetmax1 + 
													  std1_offset - std0_offset);
					coin_cmp_value[is].compare_min1 = (pre_value.country[coinchoose].coin[is].data.min1 + pre_value.country[coinchoose].coin[is].data.offsetmin1 + 
													  std1_offset - std0_offset);
					
					coin_cmp_value[is].compare_max2 = (pre_value.country[coinchoose].coin[is].data.max2 + pre_value.country[coinchoose].coin[is].data.offsetmax2 + 
													  std2_offset - std1_offset);
					coin_cmp_value[is].compare_min2 = (pre_value.country[coinchoose].coin[is].data.min2 + pre_value.country[coinchoose].coin[is].data.offsetmin2 + 
													  std2_offset - std1_offset);
				#endif
				#ifdef SAMPLE_METHOD_1
					coin_cmp_value[is].compare_max0 = (pre_value.country[coinchoose].coin[is].data.max0 + pre_value.country[coinchoose].coin[is].data.offsetmax0 + 
													  std0_offset);
					coin_cmp_value[is].compare_min0 = (pre_value.country[coinchoose].coin[is].data.min0 + pre_value.country[coinchoose].coin[is].data.offsetmin0 + 
													  std0_offset);
					
					coin_cmp_value[is].compare_max1 = (pre_value.country[coinchoose].coin[is].data.max1 + pre_value.country[coinchoose].coin[is].data.offsetmax1 + 
													  std1_offset);
					coin_cmp_value[is].compare_min1 = (pre_value.country[coinchoose].coin[is].data.min1 + pre_value.country[coinchoose].coin[is].data.offsetmin1 + 
													  std1_offset);
					
					coin_cmp_value[is].compare_max2 = (pre_value.country[coinchoose].coin[is].data.max2 + pre_value.country[coinchoose].coin[is].data.offsetmax2 + 
													  std2_offset);
					coin_cmp_value[is].compare_min2 = (pre_value.country[coinchoose].coin[is].data.min2 + pre_value.country[coinchoose].coin[is].data.offsetmin2 + 
													  std2_offset);
				#endif
				}
				detect_sample_data_buf_index = 0;
			}*/
			break;
		}
/*��ȡ��ֵ��ο�ֵ�Աȼ��仯�Ĳ���ִ��*/
		case 6: 					//read in ad value ADSAMPNUM times 
				{
					blockflag = ADBLOCKT;	   //ʹ�ü�α������ ���±�5
					/*��ǰ����3�Ĳ���ֵС�ڱ�׼�ο�ֵʱ coin_env.std_down_value0 ad0-50 ,ad0 ����8�ξ�ֵ*/
					if( (ad0_ad_value < coin_env.std_down_value0)	)  //std_value	standard value for detect  ��ƽ��ֵ�ļ���Ϊ��ǰֵ�ļ��
					{
						wave0down_flagone++;    //С�ڲο�ֵ  ���ʾ��Ӳ�ҹ���
					}
					/*��ֵ���ڲο�ֵʱ*/
					else if((ad0_ad_value > coin_env.std_down_value0))
					{
						wave0down_flagone = 0;
					}
					/*����ֵС�ڲο�ֵ,������WAVEUP0�����ϣ���������*/	
					if(  wave0down_flagone > WAVEUP0)     //WAVEUP0 4
					{
						coin_env.ad0_step  = 9;
						coin_cross_time = 0;//��ʼ��ʱ
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
						wave0down_flagone = 0;
						detect_sample_data_buf_index = 0;
						break;
					}
					/*���ز���3�ɼ�*/
					else
					{	
						coin_env.ad0_step  = 3;	
						detect_sample_data_buf_index = 0;
						
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);					
					}
					break;
				} 
/*���ȱ���,������Сֵ*/
		case 9:   ///�˴�����ȥ������Ϊ˫�����������
			{
				ad0_mintemp = ad0_ad_value;
				ch0_coin_come++;  //ͨ�� 0 ��Ӳ��  ֪ͨ����ͨ��
				coin_env.ad0_step  = 10;
				//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
				break;
			}
/*�ٴ���;�ֵ*/
		case 10:						//ad0 value get
				{
					AD_Sample_All ();
					coin_env.ad0_step = 16;
					//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
					break;
				}
/*ȷ����Сֵ,���λ���*/
		case 16:						//read in ad value ADSAMPNUM times 
				{

					//step9 ad0_mintemp �ٶ���Сֵ
					if( ad0_mintemp > ad0_ad_value )  //���γ���  �½���  �˴�ʹ�õ� �Ƚϲ����ǳ���Ҫ��ԭ����ad0_ad_value_buf[ad0_samp_number] ��һ��ad0_ad_value
					{
						ad0_mintemp =ad0_ad_value;	//;ad0_ad_value_buf[ad0_samp_number],������Сֵ
						coin_env.AD_min_index[0] = detect_sample_data_buf_index;
						wave0up_flagone = 0;
					}
					else if((ad0_ad_value > ad0_mintemp )&&((ad0_ad_value - ad0_mintemp )>50))     //����    ����  
					{
						wave0up_flagone++;
					}

					/*������8��,���λ���*/
					if( wave0up_flagone  > WAVEMAX0)     //ȷ�ϲ��η�ֵ  WAVEMAX0  8
					{
						coin_env.ad0_step = 19;	
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
						wave0up_flagone = 0;
					}
					/*����step10 ������ֵ����*/
				    else
					{
						coin_env.ad0_step = 10;
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
					}
					break;
				}
/*�Ѿ�ȷ����Сֵ���϶��о���һöӲ�ң��������ֵ*/
		case 19:				
				{
					ad0_min = ad0_mintemp;
//					my_println("adtempcount0 = %d",ch0_counttemp);
					ch0_count++;    //if ch0_count != ch_counttemp ,���ʾͨ��0�ɼ���һö
					ad0_maxtemp = ad0_ad_value ;//ad0_ad_value��;�ֵ
					coin_env.ad0_step = 25; ///25
//					my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
					break;
				}	
/*��ȡADת��ֵ,����ֵ*/
		case 25:						//read in ad value ADSAMPNUM times 
				{
					AD_Sample_All ();
					
					coin_env.ad0_step = 31; ///25
					//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
					break;
				}
/*�ж��Ƿ���ο�ֵ��ͬ�����,ȷ��������ֵ,���λָ����ο�ֵ*/
		case 31:						//ad0 value get
				{
					/*��ֵ���ڲο�ֵ,��ʾһö�Ѿ���ȥ*/
					if( (ad0_ad_value >= coin_env.std_up_value0) ){    //��� ���λָ����ο�ֵ����ʾһö����
						wave0up_flag++;
						wave0down_flagtwo = 0;
						ad0_maxtemp = ad0_ad_value ;
					}else if( (ad0_ad_value < coin_env.std_down_value0)&&(ad0_maxtemp>ad0_ad_value)&&((ad0_maxtemp-ad0_ad_value)>70) ){ /*�����������*/ //����ʱ������ȥ�󻹻�����һ����壬ad0_ad_value_buf[ad0_samp_number] 
						wave0down_flagtwo++;
					}else if(ad0_ad_value >= ad0_maxtemp){/*������λ�������������ȷ�����ֵ*/		
						wave0down_flagtwo = 0;
						ad0_maxtemp = ad0_ad_value ;
					}
					
					/*�Ѿ��ָ��ο�ֵ,���س�ʼ����*/
					if( wave0up_flag > WAVE0fall){// WAVE0fall 2
						coin_env.ad0_step = 3; //
						ch0_coin_leave = 1;
						my_env.coin_cross_time = coin_cross_time;
						blockflag = ADBLOCKT;      //ʹ�ü�α������ ���±� 5
						wave0up_flag =0;
						wave0down_flagtwo = 0;	
						break;
					}
						/*����˫����,����״̬9*/
					if( (wave0down_flagtwo > WAVEUPT0)) {    //��ʾ˫������ WAVEUPT0 8
						coin_env.ad0_step = 9;
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
						//my_println("more than two coin come");
//						coin_env.ad0_step = 38; //
						blockflag = ADBLOCKT;      //ʹ�ü�α������ ���±� 5
						wave0up_flag =0;
						wave0down_flagtwo = 0;	
						break;
					}else{/*��û�лָ�Ҳû���������������*/
						coin_env.ad0_step = 25;	
						//my_println ("go to  coin_env.ad0_step %d", coin_env.ad0_step);
					}								
					break;
				}

	}
	return;
}

////////////////////////////////////////////////////////////////////////////////


//ģ��ת��  1  ����
void my_ad1_valueget(void)
{					
	switch(coin_env.ad1_step)
	{
		case 0: 
		{
			ch1_count = 0;
			ch1_counttemp = ch1_count;
			
			ch1_coin_come = ch0_coin_come;
			
			wave1down_flagone = 0;
			wave1up_flagone =0;
			wave1down_flagtwo =0;
			
			ad1_ad_value = AD1STDSET;
			ad1_mintemp = AD1STDSET;
			ad1_min = AD1STDSET;
			
			ad1_samp_number = 0;
			coin_env.ad1_averaged_value = 0;

			coin_env.ad1_step = 2;
			break;
		}
		case 2:
		{
			//**********************************************************************
			//my_println ("Start Sample AD1");
			//*************************************************************************
			ad1_ad_value_buf[ad1_samp_number] = ReadAdc1();
			coin_env.ad1_averaged_value = coin_env.ad1_averaged_value + ad1_ad_value_buf[ad1_samp_number];   //��ǰ�����ܺ�
			ad1_samp_number++;
			if( (ad1_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������ 10
			{
				ad1_samp_number = 0;
				ad1_ad_value = coin_env.ad1_averaged_value/ADSAMPNUM0;   //��ǰ�����ƽ��ֵ
				coin_env.ad1_step = 3; //10 �βŻ���������3
				dbg ("go to  coin_env.ad1_step %d", coin_env.ad0_step);
			}
			break;
		}
		case 3: 						//����Ӳ�Ҽ��
		{						
			if(( ch1_coin_come != ch0_coin_come))//Ӳ������,+1ֵ��һ��
			{
				coin_env.ad1_step = 5;
				ad1_mintemp =  ad1_ad_value;
				ch1_coin_come  =  ch0_coin_come;
				break;
			}
			break;
		}
		case 5: 						//����Ӳ�Ҽ��
		{						

			if(ad1_mintemp >ad1_ad_value)
			{
				ad1_mintemp =  ad1_ad_value;
				coin_env.AD_min_index[1] = detect_sample_data_buf_index;
			}
			/**/
 			if((ch0_pre_count != ch0_count))	 //���0ͨ�������ˡ�
			{
				coin_env.ad1_step = 3;
  				ad1_min = ad1_mintemp;
	//			Uart0_Printf("1min %d\r\n",ad1_mintemp);
				ad1_mintemp = AD1STDSET;
				ch1_count++;    //if ch1_count != ch_counttemp ,���ʾͨ��1�ɼ���һö
				break;
			}
 			break;
		}
	}
}

//ģ��ת��  2  ����
#define AD2CHANG 6
void my_ad2_valueget(void)
{
	switch(coin_env.ad2_step)
	{
		/*��ʼ��ֵ*/
		case 0: 
		{	
			ch2_count = 0;
			ch2_counttemp = ch2_count;
			
			ch2_coin_come = ch0_coin_come;
			
			ad2_ad_value = AD2STDSET;//900
			ad2_mintemp = AD2STDSET;//900
			ad2_min = AD2STDSET;//900
			
			ad2_samp_number = 0;
			coin_env.ad2_averaged_value = 0;
			
			coin_env.ad2_step = 2;
			break;
		}
		case 2:
		{
			//**********************************************************************
			//my_println ("Start Sample AD2");
			ad2_ad_value_buf[ad2_samp_number] = ReadAdc2();
			coin_env.ad2_averaged_value = coin_env.ad2_averaged_value + ad2_ad_value_buf[ad2_samp_number];   //��ǰ�����ܺ�
			ad2_samp_number++;
			if( (ad2_samp_number > (ADSAMPNUM0-1)) )   //����ɼ�����ADSAMPNUM������ 10
			{
				ad2_samp_number = 0;
				ad2_ad_value = coin_env.ad2_averaged_value/ADSAMPNUM0;   //��ǰ�����ƽ��ֵ
				coin_env.ad2_step = 3; //10 �βŻ���������3
					
				dbg ("go to  coin_env.ad2_step %d", coin_env.ad0_step);
			}
			//*************************************************************************
			break;
		}
		case 3: 	    //����Ӳ�� ��� 					
		{			
			if(( ch2_coin_come != ch0_coin_come))
			{
				coin_env.ad2_step	 = 5;
				ad2_mintemp =ad2_ad_value; 
				ch2_coin_come = ch0_coin_come;
				break;
			}
			break;
		}
		case 5: 	    //����Ӳ�� ��� 					
		{

			if( ad2_mintemp > ad2_ad_value ) 
			{
				ad2_mintemp =ad2_ad_value;
				coin_env.AD_min_index[2] = detect_sample_data_buf_index;
			}
				
			if((ch0_pre_count != ch0_count)){
				coin_env.ad2_step	 = 3;
				ad2_min =  ad2_mintemp;
				ch2_count++;	//if ch2_count != ch_counttemp ,���ʾͨ��2�ɼ���һö
				ad2_mintemp = AD2STDSET;//900
				ch0_pre_count = ch0_count;
				if (my_env.print_wave_to_pc == 0){
					detect_sample_data_buf_index = 0;
				}
				break;
			}
			break;
		}

	}
	return;
}

	
////////////////////////////////////////////////////////////////////////////////
S16 std_ad0 = 0;
S16 std_ad1 = 0;
S16 std_ad2 = 0;
S16 std_ad3= 0;

 int temperstd = 281;   //20��  20*10 +600  = 800MV;  800/3300 *1024 = 248.24
 int temperpre = 250;
 int dexvaule = 13;   //  �൱��1.3��
#define GETTEMPERCP 0 //std_ad3 - temperstd) // 0  //(((std_ad3 - temperstd)*10)/22)
#define GETTEMPER2CP 0 //(std_ad3 - temperstd)  //0  //(((std_ad3 - temperstd)*10)/40) //((( std_ad3 - temperpre)*15)/10)


//����û��Ӳ��ͨ��ʱ DA0 DA1 DA2 ͨ���ĵ�ǰֵ�Ƿ���ϼ���Ҫ��
U16 adstd_test(void)
{
	unsigned int is;
	int adstdtest0,adstdtest1,adstdtest2;
	int ad2_std[AD2STDNUM];
	int ad1_std[AD1STDNUM];
	int ad0_std[AD0STDNUM];

	std_ad3 = ReadAdc3();//�¶�AD������ֵ
	/*��׼ֵ*/
	/**********************************************************************
	**����AD2��ƽ��ֵ
	**ȥ���������������ADֵ(�տ�ʼ��ֵ���ܲ�׼ȷ)
	**********************************************************************/
	for(is =0;is<AD2STDNUM;is++) //AD2STDNUM 10
	{
		ad2_std[is] = ReadAdc2();
	}
	std_ad2 = (ad2_std[2]+ad2_std[3]+ad2_std[4] +ad2_std[5] +ad2_std[6] +ad2_std[7]+ad2_std[8] +ad2_std[9])/8; 
	Uart0_Printf("std_ad2:%d \r\n",std_ad2);
	/////////////////////////////////////////
	/**********************************************************************
	**����AD1��ƽ��ֵ
	**ȥ���������������ADֵ(�տ�ʼ��ֵ���ܲ�׼ȷ)
	**********************************************************************/
	for(is=0;is<AD1STDNUM;is++)
	{
		ad1_std[is] = ReadAdc1();
	}
	/*��׼ֵ*/
	std_ad1 = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
	Uart0_Printf("std_ad1:%d \r\n",std_ad1);
	////////////////////////////////////
	/**********************************************************************
	**����AD0��ƽ��ֵ
	**ȥ���������������ADֵ(�տ�ʼ��ֵ���ܲ�׼ȷ)
	**********************************************************************/
	for(is=0;is<AD0STDNUM;is++)
	{
		ad0_std[is] = ReadAdc0();
	}
	/*��׼ֵ*/
	std_ad0 = (ad0_std[2] +ad0_std[3] +ad0_std[4]+ad0_std[5]+ad0_std[6]+ad0_std[7]+ad0_std[8]+ad0_std[9])/8;
	Uart0_Printf("std_ad0:%d \r\n",std_ad0);
	//�¶Ȳ����Ժ� ��ֵ�� 930  950 ֮��ſ�������
	adstdtest0  = std_ad0;
	adstdtest1  = std_ad1;
	adstdtest2  = std_ad2;
	adcsininget(std_ad0,std_ad1,std_ad2);//AD ���ν��� �ķ�ֵ
	/*ƫ�ƻ�׼ֵ��Ҫ���µ�������������ʹ֮����Ҫ�����ܿ�ʼ���м��*/
	if( (adstdtest0 > (pre_value.country[coinchoose].coin[0].data.std0 + ADOFFSET)) || (adstdtest0< (pre_value.country[coinchoose].coin[0].data.std0 - ADOFFSET)) ||
		(adstdtest1 > (pre_value.country[coinchoose].coin[0].data.std1 + ADOFFSET)) || (adstdtest1< (pre_value.country[coinchoose].coin[0].data.std1 - ADOFFSET)) ||
		(adstdtest2 > (pre_value.country[coinchoose].coin[0].data.std2 + ADOFFSET)) || (adstdtest2< (pre_value.country[coinchoose].coin[0].data.std2 - ADOFFSET)))
		{
			Uart0_Printf("Pleas check the sensor\r\n");
			return 1;
		}
	return 1;
	////////////////////////////////////
							
}

///////////////////////////////////////

// ͨ����չ�ķ�Χ �����   ŷԪ  ��Ԫ   ���ݱ��־���
 U8 cn0copmaxc0[COINCNUM] = {15,33,40,10}; //20 //����ֵ 100Ԫ��  200ŷ  100��Ԫ  200Ӣ�� 
 U8 cn0copminc0[COINCNUM] = {30,65,40,20};  //20 
 U8 cn0copmaxc1[COINCNUM] = {15,40,40,10};  //60
 U8 cn0copminc1[COINCNUM] = {30,50,40,20}; //30
 U8 cn0copmaxc2[COINCNUM] = {15,40,40,10}; //40
 U8 cn0copminc2[COINCNUM] = {50,40,40,20}; //40
//1Ԫ��   ������Χֵ
 short int offset0_cnn0[5];
 short int offset1_cnn0[5];
 short int offset2_cnn0[5];

 S32 compcoin0max0 = 0;			  //compensate //����Χֵ 0 100Ԫ��  200ŷ  100��Ԫ  200Ӣ��
 S32 compcoin0min0 = 0;			 
 S32 compcoin0max1 = 0;	
 S32 compcoin0min1 = 0;			 
 S32 compcoin0max2 = 0;	
 S32 compcoin0min2 = 0;	

 s_coin_compare_value coin_cmp_value[COIN_TYPE_NUM];
//
 
//////
 U8  cn1copmaxc0[COINCNUM] = {70,40,40,20}; //����ֵ 50ͭ    100��  50����  100��ʿ 
 U8  cn1copminc0[COINCNUM] = {35,34,40,40};  
 U8  cn1copmaxc1[COINCNUM] = {40,40,40,20};  
 U8  cn1copminc1[COINCNUM] = {40,40,40,40};  
 U8  cn1copmaxc2[COINCNUM] = {50,50,40,20}; 
 U8  cn1copminc2[COINCNUM] = {40,50,40,80};   
 
 short int offset0_cnn1[5];
 short int offset1_cnn1[5];
 short int offset2_cnn1[5];

 S32 compcoin1max0 = 0;			  //compensate //����Χֵ 1 5��ͭ 
 S32 compcoin1min0 = 0;			 
 S32 compcoin1max1 = 0;	
 S32 compcoin1min1 = 0;			 
 S32 compcoin1max2 = 0;	
 S32 compcoin1min2 = 0;	

///////

 U8 cn2copmaxc0[COINCNUM] = {20,20,20,20}; //����ֵ    50��   50��  25���� 50��ʿ
 U8 cn2copminc0[COINCNUM] = {65,65,40,10};  
 U8 cn2copmaxc1[COINCNUM] = {40,20,20,20};  
 U8 cn2copminc1[COINCNUM] = {40,40,40,20};  
 U8 cn2copmaxc2[COINCNUM] = {45,40,45,20};  
 U8 cn2copminc2[COINCNUM] = {45,60,40,20};  

 short int offset0_cnn2[5];
 short int offset1_cnn2[5];
 short int offset2_cnn2[5];

 S32 compcoin2max0 = 0;			  //compensate //����Χֵ 2 
 S32 compcoin2min0 = 0;			 
 S32 compcoin2max1 = 0;	
 S32 compcoin2min1 = 0;			 
 S32 compcoin2max2 = 0;	
 S32 compcoin2min2 = 0;	
//////
 U8 cn3copmaxc0[COINCNUM] = {20,40,50,20};//����ֵ 10  ����   20��  50���� 50��ʿ
 U8 cn3copminc0[COINCNUM] = {20,25,60,20}; 
 U8 cn3copmaxc1[COINCNUM] = {20,40,40,20}; 
 U8 cn3copminc1[COINCNUM] = {20,26,30,20}; 
 U8 cn3copmaxc2[COINCNUM] = {80,60,80,20}; 
 U8 cn3copminc2[COINCNUM] = {80,60,80,20}; 

 short int offset0_cnn3[5];
 short int offset1_cnn3[5];
 short int offset2_cnn3[5];

 S32 compcoin3max0 = 0;			  //compensate //����Χֵ 3 
 S32 compcoin3min0 = 0;			 
 S32 compcoin3max1 = 0;	
 S32 compcoin3min1 = 0;			 
 S32 compcoin3max2 = 0;	
 S32 compcoin3min2 = 0;	
///////
 S8  cn4copmaxc0[COINCNUM] = {30,50,40,20}; //50 //����ֵ 1��С��   2��  25����  1Ӣ�� 
 S8  cn4copminc0[COINCNUM] = {20,18,30,20};
 S8  cn4copmaxc1[COINCNUM] = {20,60,40,20};
 S8  cn4copminc1[COINCNUM] = {20,18,40,20};
 S8  cn4copmaxc2[COINCNUM] = {30,30,40,20};
 S8  cn4copminc2[COINCNUM] = {20,30,40,20};
 short int offset0_cnn4[5];
 short int offset1_cnn4[5];
 short int offset2_cnn4[5];

 S32 compcoin4max0 = 0;			  //compensate //����Χֵ 4 
 S32 compcoin4min0 = 0;			 
 S32 compcoin4max1 = 0;	
 S32 compcoin4min1 = 0;			 
 S32 compcoin4max2 = 0;	
 S32 compcoin4min2 = 0;	
///////
 U8 cn5copmaxc0[COINCNUM] = {20,40,40,20};//15//����ֵ 1��С��   1��  10����   20��ʿ 
 U8 cn5copminc0[COINCNUM] = {25,40,20,20};
 U8 cn5copmaxc1[COINCNUM] = {15,40,50,20};
 U8 cn5copminc1[COINCNUM] = {20,40,25,20};//30
 U8 cn5copmaxc2[COINCNUM] = {40,70,40,20}; //20
 U8 cn5copminc2[COINCNUM] = {40,40,40,20}; //30

 short int offset0_cnn5[5];
 short int offset1_cnn5[5];
 short int offset2_cnn5[5];

 S32 compcoin5max0 = 0;			  //compensate //����Χֵ 5 
 S32 compcoin5min0 = 0;			 
 S32 compcoin5max1 = 0;	
 S32 compcoin5min1 = 0;			 
 S32 compcoin5max2 = 0;	
 S32 compcoin5min2 = 0;	
//////
 U8 cn6copmaxc0[COINCNUM] = {20,30,30,20};//����ֵ 5����        10��ʿ
 U8 cn6copminc0[COINCNUM] = {20,20,20,20};
 U8 cn6copmaxc1[COINCNUM] = {20,40,40,20};
 U8 cn6copminc1[COINCNUM] = {20,20,20,20};
 U8 cn6copmaxc2[COINCNUM] = {70,60,60,20};//60
 U8 cn6copminc2[COINCNUM] = {70,60,60,20};//60  

 short int offset0_cnn6[5];
 short int offset1_cnn6[5];
 short int offset2_cnn6[5];

 S32 compcoin6max0 = 0;			  //compensate //����Χֵ 6 
 S32 compcoin6min0 = 0;			 
 S32 compcoin6max1 = 0;	
 S32 compcoin6min1 = 0;			 
 S32 compcoin6max2 = 0;	
 S32 compcoin6min2 = 0;	
/////
 U8 cn7copmaxc0[COINCNUM] = {30,15,0,20};//����ֵ 2��   10��  1�� 
 U8 cn7copminc0[COINCNUM] = {40,40,0,20};//
 U8 cn7copmaxc1[COINCNUM] = {20,20,0,20};//
 U8 cn7copminc1[COINCNUM] = {70,40,0,20};//
 U8 cn7copmaxc2[COINCNUM] = {50,30,0,20};//
 U8 cn7copminc2[COINCNUM] = {40,30,0,20};//

 short int offset0_cnn7[5];
 short int offset1_cnn7[5];
 short int offset2_cnn7[5];

 S32 compcoin7max0 = 0;			  //compensate //����Χֵ 7 
 S32 compcoin7min0 = 0;			 
 S32 compcoin7max1 = 0;	
 S32 compcoin7min1 = 0;			 
 S32 compcoin7max2 = 0;	
 S32 compcoin7min2 = 0;	
////
 U8 cn8copmaxc0[COINCNUM] = {30,0,0,0};//����ֵ 1��   
 U8 cn8copminc0[COINCNUM] = {20,0,0,0}; 
 U8 cn8copmaxc1[COINCNUM] = {30,0,0,0}; 
 U8 cn8copminc1[COINCNUM] = {20,0,0,0}; 
 U8 cn8copmaxc2[COINCNUM] = {40,0,0,0}; 
 U8 cn8copminc2[COINCNUM] = {40,0,0,0}; 

 short int offset0_cnn8[5];
 short int offset1_cnn8[5];
 short int offset2_cnn8[5];

S32 compcoin8max0 = 0;			  //compensate //����Χֵ 8 
S32 compcoin8min0 = 0;			 
S32 compcoin8max1 = 0;	
S32 compcoin8min1 = 0;			 
S32 compcoin8max2 = 0;	
S32 compcoin8min2 = 0;	
#define CHUSHU (3)
 
void print_std_value(void)    //  ��� ��׼ֵ   �в���ƫ����в���
{
	U16 is = 0;
	U16 ad2_std[AD2STDNUM];
	U16 ad1_std[AD1STDNUM];
	U16 ad0_std[AD0STDNUM];
	U16 ad2countis = 10;
	std_ad3 = ReadAdc3();

	for(is =0;is<ad2countis;is++)
	{
		ad2_std[is] = ReadAdc2(); 
	}	
	std_ad2 = 0;
	for(is =0;is<ad2countis;is++)
	{
		std_ad2 = std_ad2+ad2_std[is]; 
	}	
	
	std_ad2 =std_ad2/ad2countis;
	/////////////////////////////////////////
	for(is=0;is<AD1STDNUM;is++)
	{
		ad1_std[is] = ReadAdc1();
	}
	std_ad1 = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
	////////////////////////////////////
	for(is=0;is<AD0STDNUM;is++)
	{
		ad0_std[is] = ReadAdc0();
	}
	std_ad0 = (ad0_std[2] +ad0_std[3] +ad0_std[4]+ad0_std[5]+ad0_std[6]+ad0_std[7]+ad0_std[8]+ad0_std[9])/8;
}

U16 adstd_offset()    //  ��� ��׼ֵ   �в���ƫ����в���
{
	U16 is;
		////////////////////////////////////
	U16 ad0_std[AD0STDNUM];
	U16 ad2_std[AD2STDNUM];
	U16 ad1_std[AD1STDNUM];
	
	S16 std0_offset, std1_offset, std2_offset;


	for(is=0;is<AD0STDNUM;is++){
		ad0_std[is] = ReadAdc0();
	}
	std_ad0 = (ad0_std[2] +ad0_std[3] +ad0_std[4]+ad0_std[5]+ad0_std[6]+ad0_std[7]+ad0_std[8]+ad0_std[9])/8;
//	std_ad0 = (ad0_std[2]  +ad0_std[4]+ad0_std[5]+ad0_std[7]+ad0_std[9])/5;

	
/////////////////////////
	for(is =0;is<AD2STDNUM;is++){
		ad2_std[is] = ReadAdc2();	
	}
	std_ad2 = (ad2_std[2]+ad2_std[3]+ad2_std[4] +ad2_std[5] +ad2_std[6] +ad2_std[7]+ad2_std[8] +ad2_std[9])/8;
	/////////////////////////////////////////
	for(is=0;is<AD1STDNUM;is++){
		ad1_std[is] = ReadAdc1();
	}
	std_ad1  = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
//	Uart0_Printf("A0 :%d   A1 :%d  A2 :%d  \r\n",std_ad0,std_ad1,std_ad2);
	//offset_ad0 = std_ad0 - AD0STDSET;
	/////////////////////////ÿ��Ӳ�� �������в��� 
	std_ad3 = ReadAdc3();
	if( ( ((std_ad0-GETTEMPERCP) < (pre_value.country[coinchoose].coin[0].data.std0 + OFFSETMAX))) && 
		  ((std_ad0-GETTEMPERCP) > (pre_value.country[coinchoose].coin[0].data.std0 - OFFSETMIN)) ){        //���  ��990  1020֮�� ���Խ��в���	
	}else {
		return 2;
	}	

	
	/////////////   
	my_println ("real     std0 = %4d          std1 = %4d     std2 = %4d", std_ad0, std_ad1, std_ad2);
	for (is = 0; is < COIN_TYPE_NUM; is++){ //����ֵ
		std0_offset = std_ad0 - pre_value.country[coinchoose].coin[is].data.std0;
		std1_offset = std_ad1 - pre_value.country[coinchoose].coin[is].data.std1;
		std2_offset = std_ad2 - pre_value.country[coinchoose].coin[is].data.std2;
	#ifdef SAMPLE_METHOD_0
		coin_cmp_value[is].compare_max0 = (pre_value.country[coinchoose].coin[is].data.max0 + pre_value.country[coinchoose].coin[is].data.offsetmax0 + 
										  std0_offset);
		coin_cmp_value[is].compare_min0 = (pre_value.country[coinchoose].coin[is].data.min0 + pre_value.country[coinchoose].coin[is].data.offsetmin0 + 
										  std0_offset);
		
		coin_cmp_value[is].compare_max1 = (pre_value.country[coinchoose].coin[is].data.max1 + pre_value.country[coinchoose].coin[is].data.offsetmax1 + 
										  std1_offset - std0_offset);
		coin_cmp_value[is].compare_min1 = (pre_value.country[coinchoose].coin[is].data.min1 + pre_value.country[coinchoose].coin[is].data.offsetmin1 + 
										  std1_offset - std0_offset);
		
		coin_cmp_value[is].compare_max2 = (pre_value.country[coinchoose].coin[is].data.max2 + pre_value.country[coinchoose].coin[is].data.offsetmax2 + 
										  std2_offset - std1_offset);
		coin_cmp_value[is].compare_min2 = (pre_value.country[coinchoose].coin[is].data.min2 + pre_value.country[coinchoose].coin[is].data.offsetmin2 + 
										  std2_offset - std1_offset);
	#endif
	#ifdef SAMPLE_METHOD_1
		coin_cmp_value[is].compare_max0 = (pre_value.country[coinchoose].coin[is].data.max0 + pre_value.country[coinchoose].coin[is].data.offsetmax0 + 
										  std0_offset);
		coin_cmp_value[is].compare_min0 = (pre_value.country[coinchoose].coin[is].data.min0 + pre_value.country[coinchoose].coin[is].data.offsetmin0 + 
										  std0_offset);
		
		coin_cmp_value[is].compare_max1 = (pre_value.country[coinchoose].coin[is].data.max1 + pre_value.country[coinchoose].coin[is].data.offsetmax1 + 
										  std1_offset);
		coin_cmp_value[is].compare_min1 = (pre_value.country[coinchoose].coin[is].data.min1 + pre_value.country[coinchoose].coin[is].data.offsetmin1 + 
										  std1_offset);
		
		coin_cmp_value[is].compare_max2 = (pre_value.country[coinchoose].coin[is].data.max2 + pre_value.country[coinchoose].coin[is].data.offsetmax2 + 
										  std2_offset);
		coin_cmp_value[is].compare_min2 = (pre_value.country[coinchoose].coin[is].data.min2 + pre_value.country[coinchoose].coin[is].data.offsetmin2 + 
										  std2_offset);
	
	#endif
	}
	adcsininget(std_ad0,std_ad1,std_ad2);//AD ���ν��� �ķ�ֵ

	return 1;
	////////////////////////////////////
}


volatile U32 start_sample = 0;
static		U16  minTempAD0 = 1000;
static		U16  minTempAD1 = 1000;
static		U16  minTempAD2 = 1000;



volatile AD_Value AD_Value_buf[DATA_BUF_LENGTH];
volatile AD_Value Detect_AD_Value_buf[DATA_BUF_LENGTH];
//volatile AD_Value Adj_AD_Value_buf[ADJ_BUF_LENGTH];
volatile AD_Value NG_value_buf[NG_BUF_LENGTH];
volatile AD_Value GOOD_value_buf[NG_BUF_LENGTH];
volatile U32 ng_value_index = 0;
volatile U32 good_value_index = 0;
volatile U32  sample_data_buf_index = 0;
volatile U32 detect_sample_data_buf_index = 0;

/////////////////////////////////

extern void Uart_SendByte(int data);

int L_H_min = 1024;
int L_M_min = 1024;
int M_H_min = 1024;
	
int L_H_max = 0;
int L_M_max = 0;
int M_H_max = 0;

void send_sample_data (volatile AD_Value ad_value_buf[DATA_BUF_LENGTH], int counter)
{
	int i = 0;
	int L_H_Temp = 0;
	int L_M_Temp = 0;
	int M_H_Temp = 0;
	
	int H_min_index = 0;
	int M_min_index = 0;
	int L_min_index = 0;
	//if (start_sample)
	{
		Uart0_Printf ("start\n");
		for (i = 0; i < counter; i++)
		{
			if (minTempAD0 > ad_value_buf[i].AD0)
			{
				minTempAD0 = ad_value_buf[i].AD0;
				H_min_index = i;
			}
			if (minTempAD1 > ad_value_buf[i].AD1)
			{
				minTempAD1 = ad_value_buf[i].AD1;
				M_min_index = i;
			}
			if (minTempAD2 > ad_value_buf[i].AD2)
			{
				minTempAD2 = ad_value_buf[i].AD2;
				L_min_index = i;
			}
			Uart0_Printf("%d	%d	%d	\n",ad_value_buf[i].AD0, ad_value_buf[i].AD1, ad_value_buf[i].AD2);
		}
		
		Uart0_Printf ("end\n");
		dgus_tf1word(ADDR_STDH, (minTempAD0)); //	high frequence
		dgus_tf1word(ADDR_STDM,  minTempAD1); //	middle frequence
		dgus_tf1word(ADDR_STDL, (minTempAD2)); //	low frequence	
//		dgus_tf1word(ADDR_STDT,((std_ad3*3300)/1024-600)); //	low frequence	
		
		
		if ( minTempAD1 > 20)
		{
			L_H_Temp = ad_value_buf[H_min_index].AD2 - ad_value_buf[H_min_index].AD0;
			L_M_Temp = ad_value_buf[H_min_index].AD2 - ad_value_buf[H_min_index].AD1;
			M_H_Temp = ad_value_buf[H_min_index].AD1 - ad_value_buf[H_min_index].AD0;
		}
		else if (minTempAD0 >20)
		{
			L_H_Temp = ad_value_buf[M_min_index].AD2 - ad_value_buf[M_min_index].AD0;
			L_M_Temp = ad_value_buf[M_min_index].AD2 - ad_value_buf[M_min_index].AD1;
			M_H_Temp = ad_value_buf[M_min_index].AD1 - ad_value_buf[M_min_index].AD0;
		}
		else
		{
			L_H_Temp = ad_value_buf[L_min_index].AD2 - ad_value_buf[L_min_index].AD0;
			L_M_Temp = ad_value_buf[L_min_index].AD2 - ad_value_buf[L_min_index].AD1;
			M_H_Temp = ad_value_buf[L_min_index].AD1 - ad_value_buf[L_min_index].AD0;
		}
		
		if (L_H_Temp < L_H_min)
		{
			L_H_min = L_H_Temp;
		}
		if (L_H_Temp > L_H_max)
		{
			L_H_max = L_H_Temp;
		}
		
		if (L_M_Temp < L_M_min)
		{
			L_M_min = L_M_Temp;
		}
		if (L_M_Temp > L_M_max)
		{
			L_M_max = L_M_Temp;
		}
		
		if (M_H_Temp < M_H_min)
		{
			M_H_min = M_H_Temp;
		}
		if (M_H_Temp > M_H_max)
		{
			M_H_max = M_H_Temp;
		}
		
		minTempAD0 = 1024;
		minTempAD1 = 1024;
		minTempAD2 = 1024;
	}
}
U16 adstd_adj(void)    //��׼ֵ����  
{
	U16 is = 0;
	U16 ad2_std[AD2STDNUM];
	U16 ad1_std[AD1STDNUM];
	U16 ad0_std[AD0STDNUM];
//	U16 ad2countis = 10;

	for(is=0;is<AD0STDNUM;is++)
	{
		ad0_std[is] = ReadAdc0();
		ad1_std[is] = ReadAdc1();
		ad2_std[is] = ReadAdc2();
	}
	std_ad0 = (ad0_std[2] +ad0_std[3] +ad0_std[4]+ad0_std[5]+ad0_std[6]+ad0_std[7]+ad0_std[8]+ad0_std[9])/8;
	std_ad1 = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
	std_ad2 = (ad2_std[2] +ad2_std[3] +ad2_std[4]+ad2_std[5]+ad1_std[6]+ad2_std[7]+ad2_std[8]+ad2_std[9])/8;
	
	/////////////
	//hzf change begin 
	//if(adtime ==0)
	if ((std_ad0 < 850) && (start_sample == 0))
	{
		//Uart0_Printf ("here %d sample_data_buf_index %d\n", start_sample, sample_data_buf_index);
		start_sample = 1;
		sample_data_buf_index = 0;
	}
	else if (start_sample)
	{
		if ((sample_data_buf_index < 1200))
		{
			//Uart0_Printf ("here1 %d sample_data_buf_index %d\n", start_sample, sample_data_buf_index);
			AD_Value_buf[sample_data_buf_index].AD0 = std_ad0;
			AD_Value_buf[sample_data_buf_index].AD1 = std_ad1;
			AD_Value_buf[sample_data_buf_index].AD2 = std_ad2;
			//adtime = ADADJACTERTIME;
			adtime = 0;
			sample_data_buf_index++;
			if (sample_data_buf_index >= DATA_BUF_LENGTH){
				sample_data_buf_index = 0;
			}
		}
		else
		{
			send_sample_data (AD_Value_buf, sample_data_buf_index);
			start_sample = 0;
			sample_data_buf_index = 0;

		}
	}
	//hzf change end
	
	
		
//	Uart0_Printf("adstd_adjtime = %d\r\n",adstd_adjtime);
	return 1;
}

U16 adstd_adj_old(void)    //?????  
{
	U16 is = 0;
	U16 ad2_std[AD2STDNUM];
	U16 ad1_std[AD1STDNUM];
	U16 ad0_std[AD0STDNUM];
	U16 ad2countis = 10;
	std_ad3 = ReadAdc3();

	for(is =0;is<ad2countis;is++)
	{
		ad2_std[is] = ReadAdc2(); 
	}	
	std_ad2 = 0;
	for(is =0;is<ad2countis;is++)
	{
		std_ad2 = std_ad2+ad2_std[is]; 
	}	
	
	std_ad2 =std_ad2/ad2countis;
	/////////////////////////////////////////
	for(is=0;is<AD1STDNUM;is++)
	{
		ad1_std[is] = ReadAdc1();
	}
	std_ad1 = (ad1_std[2] +ad1_std[3] +ad1_std[4]+ad1_std[5]+ad1_std[6]+ad1_std[7]+ad1_std[8]+ad1_std[9])/8;
	////////////////////////////////////
	for(is=0;is<AD0STDNUM;is++)
	{
		ad0_std[is] = ReadAdc0();
	}
	std_ad0 = (ad0_std[2] +ad0_std[3] +ad0_std[4]+ad0_std[5]+ad0_std[6]+ad0_std[7]+ad0_std[8]+ad0_std[9])/8;
	/////////////
	if(adtime ==0)
		{
			dgus_tf1word(ADDR_STDH,(std_ad0 - GETTEMPERCP)); //	high frequence
			dgus_tf1word(ADDR_STDM,std_ad1); //	middle frequence
			dgus_tf1word(ADDR_STDL,(std_ad2+GETTEMPER2CP)); //	low frequence	
//			dgus_tf1word(ADDR_STDT,((std_ad3*3300)/1024-600)); //	low frequence	
			my_println ("\nNick-Cmd:%4d %4d %4d %4d",std_ad0,std_ad1,std_ad2,std_ad3);
			adtime = ADADJACTERTIME;
		}
//	Uart0_Printf("adstd_adjtime = %d\r\n",adstd_adjtime);
	return 1;
}

////////////////////////////////////////////////
U16 adstd_ini(void)    //��׼ֵ����  
{
	
	U16 ad3_std[6];

//	ad0_mintemp = AD0STDVALUE;		//��Ϊ ��ad1_ad_value ֵ���бȽϵ�ֵ��Ϊ��ȡ�ò������ֵ
//	ad1_mintemp = AD1STDVALUE;		//��Ϊ ��ad1_ad_value ֵ���бȽϵ�ֵ��Ϊ��ȡ�ò������ֵ

	while( 1)
	{
		ad3_std[0] = ReadAdc3();
		if(ad3_std[0] >100)
		{		
			temperpre = ( ad3_std[0] - temperstd);
				
			Uart0_Printf("%d	%d\r\n",temperpre,ad3_std[0]);
			return (ad3_std[0]);
		}			
	}
}

