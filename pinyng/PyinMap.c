#include <stdio.h>
#include "PyinMap.h"
//#include "qdebug.h"


uint8_t PY_EN_CH = 0x00;



// 比较两个字符串的匹配情况
//返回值:0xff,表示完全匹配.
//        其他,匹配的字符数
uint8_t str_match(uint8_t *str1,uint8_t *str2)
{
   uint8_t i=0;
   while(1)
    {
        if(*str1=='\0' && *str2=='\0'){i=0XFF;break;}//完全匹配
        if(*str1!=*str2)break;        //部分匹配
        i++; str1++; str2++;
    }
   return i;//两个字符串相等
}

uint8_t get_matched_pymb(uint8_t *strin,char **matchpy,char **matchlist)
{
   T9PY_IDX *bestmatch;//最佳匹配
   uint16_t pyindex_len;
   uint16_t i;
   uint8_t temp,mcnt=0;
//    if(PY_EN_CH == 0x03)
    {
        bestmatch=(T9PY_IDX*)&t9PY_index[0];//默认为a 的匹配
       pyindex_len=sizeof(t9PY_index)/sizeof(t9PY_index[0]);//得到py 索引表的大小.
       for(i=0;i<pyindex_len;i++)
        {
            temp=str_match(strin,(uint8_t*)t9PY_index[i].T9);
            if(temp)
            {
                 if(temp==0XFF)  //完全匹配
                 {
                     matchpy[mcnt]=(char *)t9PY_index[i].PY;
                     matchlist[mcnt]=(char *)t9PY_index[i].MB;
                     mcnt++;
                 }
            }
        }
    }

    return mcnt;//返回匹配的个数
}
uint8_t get_matched_pymb_26Key(uint8_t *strin,char **matchpy,char **matchlist)
{
   T9PY_IDX *bestmatch;//最佳匹配
   uint16_t pyindex_len;
   uint16_t i;
   uint8_t temp,mcnt=0;
//    if(PY_EN_CH == 0x03)
    {
        bestmatch=(T9PY_IDX*)&t9PY_index[0];//默认为a 的匹配
       pyindex_len=sizeof(t9PY_index)/sizeof(t9PY_index[1]);//得到py 索引表的大小.
       for(i=0;i<pyindex_len;i++)
        {
            temp=str_match(strin,(uint8_t*)t9PY_index[i].PY);
            if(temp)
            {
                 if(temp==0XFF)  //完全匹配
                 {
//                     matchpy[mcnt]=(char *)t9PY_index[i].PY;
                     matchlist[mcnt]=(char *)t9PY_index[i].MB;
                     mcnt++;
                     break;
                 }
            }
        }
    }

    return mcnt;//返回匹配的个数
}

char  *py_list[50];
char  *ch_charlist[50];
uint8_t get_pymb(uint8_t* str)
{
    return get_matched_pymb(str,py_list,ch_charlist);
}
//char  *py_list_26Key[50];
//char  *ch_charlist_26Key[50];
//uint8_t get_pymb_26Key(uint8_t* str)
//{
//    return get_matched_pymb_26Key(str,py_list_26Key,ch_charlist_26Key);
//}


char g_py_dbuf[6];

void test_py(uint8_t *inputstr)
{
    uint16_t i,j;
    j = get_pymb(inputstr) ;
    printf("=========================================================================\r\n");
    for(i = 0;i<j;i++)
    {
        printf("%s=%s \r\n",py_list[i],ch_charlist[i]);
        printf("检索到长度 = %d\r\n",strlen(ch_charlist[i]));
    }
//    printf("拼音组合个数 = %d\r\n",g_py_listnum);
//	printf("检索到长度 = %d\r\n",strlen(ch_charlist[1]));
    printf("T9输入法数字组合: ");
    printf((void *)g_py_dbuf);
    printf("\r\n");
}

