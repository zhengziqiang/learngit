/*==============================================================================
    > File Name: 翻转单词顺序.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 09时43分39秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
void Reverse(char *pBegin, char *pEnd)
{
      if(pBegin == NULL || pEnd == NULL)
            return;

      while(pBegin < pEnd)
      {
            char temp = *pBegin;
            *pBegin = *pEnd;
            *pEnd = temp;

            pBegin ++, pEnd --;
      }
}

///////////////////////////////////////////////////////////////////////
// Reverse the word order in a sentence, but maintain the character
// order inside a word
// Input: pData - the sentence to be reversed
///////////////////////////////////////////////////////////////////////
char* ReverseSentence(char *pData)
{
      if(pData == NULL)
            return NULL;

      char *pBegin = pData;
      char *pEnd = pData;

      while(*pEnd != '\0')
            pEnd ++;
      pEnd--;

      // Reverse the whole sentence
      Reverse(pBegin, pEnd);

      // Reverse every word in the sentence
      pBegin = pEnd = pData;
      while(*pBegin != '\0')
      {
            if(*pBegin == ' ')
            {
                  pBegin ++;
                  pEnd ++;
                  continue;
            }
            // A word is between with pBegin and pEnd, reverse it
            else if(*pEnd == ' ' || *pEnd == '\0')
            {
                  Reverse(pBegin, --pEnd);
                  pBegin = ++pEnd;
            }
            else
            {
                  pEnd ++;
            }
     }

      return pData;
}
int main(){
	char str[225];
	cout<<"please input a string"<<endl;
	cin>>str;
	char *ptr=&str;
	string *ans;
	ans=ReverseSentence(ptr);
	cout<<*ans<<endl;
	return 0;

}
