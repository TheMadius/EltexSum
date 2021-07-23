#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int isDigit(char x)
{
    return x >= '0' && x <= '9'; 
}

struct data
{
    int n1;
    int n2;
    int flag;
    int len;
};

void strcat_c(char *str, char c)
{
    for (;*str;str++);
    *str++=c;
    *str++='\0';
}

struct data findPatern(char * str, int start)
{
    struct data pos;
    int fN1 = 0;
    int len = 0;
    char *patern = (char*)malloc(sizeof(str));
    strcpy(patern,"");

    for(;;)
    {
        if(isDigit(str[start]))
        {
            strcat_c(patern,str[start]);
            start++;
            len++; 
            continue;
        }
        
        if(str[start] == ',')
        {
            pos.n1 = atoi(patern);
            patern[0] = '\0';
            fN1 = 1;
            start++;
            len++;
        }
        else
        {
            if(patern[0] == '\0')
            {
                pos.flag = 0;
            }
            else
            {
                pos.n2 = atoi(patern);
                pos.flag = fN1;
            }
            pos.len = len;
            patern[0] = '\0';

            return pos;
        }
    }
} 

char * praseIn(char *str)
{
    char *newStr = (char*)malloc(sizeof(str));
    strcpy(newStr,"");

    for(int i = 0; i < strlen(str); i++)
    {
        if(isDigit(str[i]) )
        {
            struct data d = findPatern(str,i);
            if(d.flag)
            {
                char *rStr = (char*)malloc(sizeof(char)*(d.n2 + 1));
                i+= d.len;
                
                for(int j = 0; j < d.n2; j++ )
                {
                    if(str[i + j] == '\0')
                        return NULL;
                    rStr[j] = str[i + j];
                }
                rStr[d.n2] = '\0';
                
                for(int j = 0; j < d.n1; j++ )
                    strcat(newStr,rStr);

                i--;
                free(rStr);
            }
            else
                strcat_c(newStr,str[i]);
        }
        else
            strcat_c(newStr,str[i]);
    }
    return newStr;
} 

int main(int argc, char **argv)
{
    char *str = (char*)malloc(sizeof(char)*256);
    char *newStr = (char*)malloc(sizeof(char)*256);
    printf("Enter string: ");
    scanf("%s", str);

    newStr = praseIn(str);

    if(newStr == NULL)
        printf("Error!!!\n");
    else
        printf("New string: %s\n",newStr);
        
    free(str);
    free(newStr);
    return 0;
}