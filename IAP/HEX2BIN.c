#include "main.h"



bool ReadLineInBuff(char *strLine, char* pBuff, UINT nSize, bool bInit)
{
    static UINT nStart;
    static UINT nPos;   
    static UINT nRemain = 0; //��һ�����µ�����
    UINT len;
    if(bInit)
    {
         nStart = 0;
         nPos = 0;
         return TRUE;	
    }

if( nStart == 0 && nPos == 0  && nRemain)
    {
	   for(nPos=nStart; nPos<nSize; nPos++)
    {
	if(pBuff[nPos] == '\n' &&  strLine[nRemain-1] == '\r')
        {
             len = nPos - nStart;
             strLine[nRemain-1] ='\0';
             nStart = nPos+1;
	      nRemain = 0;
             return TRUE;
        }   
	
        if(pBuff[nPos] == '\r' && pBuff[nPos+1] == '\n')
        {	
             len = nPos - nStart;
		if(len >=60)
			{
			return false;
			}
             memcpy(strLine+nRemain, pBuff+nStart, len);
		strLine[len+nRemain] = '\0';
             nStart = nPos+2;
	      nRemain = 0;
             return TRUE;
        }        
    } 
   }

    if(nStart >= nSize)
    {
        return false;
    }


    for(nPos=nStart; nPos<nSize; nPos++)
    {
        if(pBuff[nPos] == '\r' && pBuff[nPos+1] == '\n')
        {
             len = nPos - nStart;
		if(len >=60)
			{
			return false;
			}
             memcpy(strLine, pBuff+nStart, len);
	       strLine[len] = '\0';
             nStart = nPos+2;
	     	nRemain = 0;
             return TRUE;
        }        
    }
    //���һ��û"\r\n"
    len  = nPos-nStart;
   if(len >=60)
   {
   return false;
   }
    memcpy(strLine, pBuff+nStart,len); //��������
     strLine[len] = '\0';
//	 printf("%s\n",strLine);
    nRemain = len;
    nStart = nSize;
    return false;
}

//�������ַ�ת��Ϊһ���ֽ���

char Hex2Bin(char* pChar)
 {

     char h,l;
     h=pChar[0];//��λ
     l=pChar[1];//��λ

     if(l>='0'&&l<='9')
         l=l-'0';
     else if(l>='a' && l<='f')
         l=l-'a'+0xa;
     else if(l>='A' && l<='F')
         l=l-'A'+0xa;

     if(h>='0'&&h<='9')
         h=h-'0';
     else if(h>='a' && h<='f')
         h=h-'a'+0xa;
     else if(h>='A' &&h <='F')
         h=h-'A'+0xa;

     return (char)h*16+l;

}

//------------------------------------------------------------------------------
//ת��HEX�뵽����������,������Щ����д��ָ�������е�ָ��λ�ã���λ��ͬHEX�ĵ�ָ���������ṩһ��������ָ��pData
BOOL CheckHexFile(char *source,  UINT MaxDataSize ,char *hexLineBuffer)
{ 
 char binBuffer[30];
 U16 lenTemp,loopTemp;
 U16 checksum ;
 U32 bootAdd;
 //static char hexLineBuffer[60];
 

if(MaxDataSize == 0 || source == NULL)
{       
    return false; //����Ч�洢�ռ�
}
ReadLineInBuff(hexLineBuffer, source, MaxDataSize, true);//��ʼ��

while(ReadLineInBuff(hexLineBuffer, source, MaxDataSize, false))
{
lenTemp = strlen(hexLineBuffer);//printf("%x %d",hexLineBuffer[0],lenTemp);
    if(hexLineBuffer[0] != ':' || lenTemp<11)
    {
        return false; //���ַ���Ϊ":",�﷨����
    }
    checksum = 0;
    for(loopTemp = 0; loopTemp<(lenTemp/2); loopTemp++)
    {
    binBuffer[loopTemp]  =  Hex2Bin(hexLineBuffer+(loopTemp*2)+1);
    checksum += binBuffer[loopTemp];
   // printf("%2x ",binBuffer[loopTemp]);
    }
   if(checksum & 0xff)
		{
		printf("check sun is wrong!!!!");
		return false;
		}
	//printf("\r\n") ;
if(0x05 == binBuffer[3])
	{
	bootAdd = (U32)binBuffer[4] << 24 | (U32)binBuffer[5] << 16 | (U32)binBuffer[6] << 8 | (U32)binBuffer[7] ;
	if((bootAdd & BOOTADD) == BOOTADD)
		{
		printf("0x%x \r",bootAdd);
		return TRUE;
		}
	else
		{
		printf("boot Addrss is wrong %x \r",bootAdd);
		return false;
		}
	}

 }
return 	TRUE;
}
// U16 buffAddress = 0;
 //U16 Page = 0;
bool SD2ROM(char *source,  UINT MaxDataSize ,char *hexLineBuffer,char *stringBuff)
{
	char binBuffer[30];
	U16 lenTemp,loopTemp;
	U16 checksum ;
	
	U16 tempOne;

	U8 lineType,byteCount;


	static U16 buffAddress = 0;
	static U16 Page = 0;
 

	if(MaxDataSize == 0 || source == NULL){
		return false; //����Ч�洢�ռ�
	}
	ReadLineInBuff(hexLineBuffer, source, MaxDataSize, true);//��ʼ��

	while(ReadLineInBuff(hexLineBuffer, source, MaxDataSize, false)){
		lenTemp = strlen(hexLineBuffer);
		if(hexLineBuffer[0] != ':' || lenTemp<11){
			return false; //���ַ���Ϊ":",�﷨����
		}
		checksum = 0;
		for(loopTemp = 0; loopTemp<(lenTemp/2); loopTemp++){
			binBuffer[loopTemp]  =  Hex2Bin(hexLineBuffer+(loopTemp*2)+1);
			checksum += binBuffer[loopTemp];
		}
		if(checksum & 0xff){
			printf("check sun is wrong!!!!");
			return false;
		}else{
			lineType = binBuffer[3];
			byteCount =  binBuffer[0];

			switch(lineType)
			{
			case 0: //���ݼ�¼
				{
				if(buffAddress + byteCount >= STM_SECTOR_SIZE)      //���м���û����
				{
				tempOne =STM_SECTOR_SIZE - buffAddress;  
				byteCount = byteCount - tempOne;
				memcpy(stringBuff+buffAddress, binBuffer+4,tempOne);
				//for(buffAddress = 0 ;buffAddress<STM_SECTOR_SIZE ;buffAddress++);
				printf("%2x ",stringBuff[buffAddress]);
				STMFLASH_WriteOnePage(BOOTADD+Page*STM_SECTOR_SIZE,(U16*)stringBuff,STM_SECTOR_SIZE/2);
				buffAddress = 0;
				Page++;
				}
			 memcpy(stringBuff+buffAddress, binBuffer+4+tempOne, byteCount);
			if(tempOne)
				{
				tempOne = 0;
				}
			 buffAddress += byteCount;	       
				break;
			case 1:
			tempOne = buffAddress;
			STMFLASH_WriteOnePage(BOOTADD+STM_SECTOR_SIZE*Page,(U16*)stringBuff,(tempOne+1)/2);
			return true;
			 //HEX�ļ�������¼
			case 2: //������չ��ַ,������4λ
				break;
			case 4: //������չ��ַ,������16λ
				break;
			case 3:
				break;
			default:
				break;
		}        
	}

	}
	}
	return TRUE;
}
