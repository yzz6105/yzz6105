#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
    char label[100];
    char opcode[100];
    char operand[100];
};

struct str
{
    char *stt;
};

struct opc
{
    char op[100];
    char hex[3];
};

struct sym
{
    char lab[100];
    char addr[100];
};

int main()
{
    FILE *fp,*fp1,*fp2,*fp3,*fp4;
    int LOCCTR=0,start,prgmlen,lc=0,oc=0,sc=0,flag=0,value,j,k;
    char word[100],l[100];
    char delimeter[]=" \t\n";
    struct str sample[1000];
    struct data list[200];
    struct opc opdata[200];
    struct sym s[100];

    fp=fopen("optab.txt","r");
    if(fp==NULL)
    {
        printf("Failed to open file!\n");
    }
    else
    {
        printf("File opening success!\n");
    }

    while(fgets(word,30,fp)!=NULL)
    {
        oc++;
        int count1=0;
        char *token=strtok(word,delimeter);
        while(token!= NULL)
        {
            count1++;
            sample[count1].stt=token;
            token = strtok(NULL,delimeter);
        }
        if(count1==2)
        {
            strcpy(opdata[oc].op,sample[1].stt);
            strcpy(opdata[oc].hex,sample[2].stt);
        }
        printf("%s\t%s\n",opdata[oc].op,opdata[oc].hex);
    }

    printf("\n\n\n");
    fp2=fopen("intermediate.txt","w");
    fp3=fopen("SYMTAB.txt","r");
    fp4=fopen("SYMTAB.txt","w");
    fp1=fopen("SIC_input.txt","r");
    if(fp1==NULL)
    {
        printf("Failed to open file!\n");
    }
    else
    {
        printf("File opening success!\n");
    }

    while(fgets(word,30,fp1)!=NULL)
    {
        lc++;
        int count2=0;
        char *token=strtok(word,delimeter);
        while(token!=NULL)
        {
            count2++;
            sample[count2].stt=token;
            token = strtok(NULL,delimeter);
        }
        if(count2==3)
        {
            strcpy(list[lc].label,sample[1].stt);
            strcpy(list[lc].opcode,sample[2].stt);
            strcpy(list[lc].operand,sample[3].stt);
        }
        if(count2==2)
        {
            strcpy(list[lc].opcode,sample[1].stt);
            strcpy(list[lc].operand,sample[2].stt);
        }
        if(count2==1)
        {
            strcpy(list[lc].opcode,sample[1].stt);
        }
    }

    int c=1;
    while(c<lc)
    {
        if(!strcmp(list[c].opcode,"START"))
        {
            LOCCTR=hextodec(list[c].operand);
            start=hextodec(list[c].operand);
            printf("\t%s\t%s\t%s\n",list[c].label,list[c].opcode,list[c].operand);
            fprintf(fp2,"\t%s\t%s\t%s\n",list[c].label,list[c].opcode,list[c].operand);
            c++;
        }
        if(strcmp(list[c].opcode,"END"))
        {
            printf("%x\t%s\t%s\t%s\n",LOCCTR,list[c].label,list[c].opcode,list[c].operand);
            fprintf(fp2,"%x\t%s\t%s\t%s\n",LOCCTR,list[c].label,list[c].opcode,list[c].operand);
            if(strcmp(list[c].label,""))
            {
                while(fgets(word,30,fp3)!=NULL)
                {
                    sc++;
                    int count3=0;
                    char *token=strtok(word,delimeter);
                    while(token!=NULL)
                    {
                        count3++;
                        sample[count3].stt=token;
                    }
                    if(count3==2)
                    {
                        strcpy(s[sc].lab,sample[1].stt);
                        strcpy(s[sc].addr,sample[2].stt);
                    }
                }
                if(sc>0)
                {
                    for(k=1; k<=sc; k++)
                    {
                        if(!strcmp(list[c].label,s[k].lab))
                        {
                            flag=1;
                            printf("\nLabel already exists!\n");
                        }
                    }
                }
                if(flag==0)
                {
                    fprintf(fp4,"%s\t%x\n",list[c].label,LOCCTR);
                }
            }
            for( j=0; j<=oc; j++)
            {
                if(!strcmp(list[c].opcode,opdata[j].op))
                {
                    LOCCTR=LOCCTR+3;
                }
            }
            if(!strcmp(list[c].opcode,"RESW"))
            {
                value=atoi(list[c].operand);
                LOCCTR=LOCCTR+(value*3);
            }
            else if(!strcmp(list[c].opcode,"RESB"))
            {
                value=atoi(list[c].operand);
                LOCCTR=LOCCTR+value;
            }
            else if(!strcmp(list[c].opcode,"BYTE"))
            {
                if(list[c].operand[0]=='C')
                {
                    value=strlen(list[c].operand);
                    LOCCTR=LOCCTR+(value-3);
                }
                if(list[c].operand[0]=='X')
                {
                    value=strlen(list[c].operand);
                    value=value-3;
                    LOCCTR=LOCCTR+(value/2);
                }
            }
            else if(!strcmp(list[c].opcode,"WORD"))
            {
                LOCCTR=LOCCTR+3;
            }
            else
            {
                LOCCTR=LOCCTR+0;
            }
            c++;
        }
    }

    printf("%x\t%s\t%s\t%s\n",LOCCTR,list[lc].label,list[lc].opcode,list[lc].operand);
    fprintf(fp2,"%x\t%s\t%s\t%s\n",LOCCTR,list[lc].label,list[lc].opcode,list[lc].operand);

    prgmlen=LOCCTR-start;
    printf("Program length is %x",prgmlen);

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}

int hextodec(char hex[100])
{
    long int decimal=0,i,base=1;
    int length=strlen(hex);
    for(i = length--; i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }
    }
    return decimal;
}
