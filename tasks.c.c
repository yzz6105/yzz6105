#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Task
{
    char label[100];
    char opcode[100];
    char operand[100];


};



void writeToFile(FILE* fp2,int hex,char* label,char* opcode, char* operand)
{
    fprintf(fp2,"%x\t%s\t%s\t%s\n",hex,label,opcode,operand);
}

void main()
{
    FILE *fp1,*fp2,*fp3,*fp4;

    struct Task s[100];

    const char* temp[3]={" "};
    char delimitter[]=" \t\r\n\v\f";

    fp1=fopen("SIC_input.txt","r");
    fp2=fopen("SIC_intermediate.txt","w");
    fp3=fopen("SIC_symbol.txt","w");
    fp4=fopen("optab.txt","r");

    if(fp1 == NULL)
        perror("File can't be opened!");
    else
        printf("File opened successfully!\n");

    char datatoread[100],compare[100];
    int lc=0;
    int hex=4096,var=0,l,j,count,y;
    int startAddres;
    while((fgets(datatoread,30,fp1))!= NULL)

    {
        lc++;
        count =0;
        temp[0] = temp[1] = temp[2] = " ";
        char* token = strtok(datatoread,delimitter);
        while (token != NULL)
        {

            temp[count]=token;
            count++;
            token = strtok(NULL,delimitter);
        }

        if(count == 3)
        {
            strcpy(s[lc].label,temp[0]);
            strcpy(s[lc].opcode,temp[1]);
            strcpy(s[lc].operand,temp[2]);

            printf("%s   %s   %s \n",s[lc].label,s[lc].opcode,s[lc].operand);
            if( var == 0)
            {

                fprintf(fp2,"LOCCTR\tLabel\tOpcode\tOperand\n");



                    writeToFile(fp2,hex,s[lc].label,s[lc].opcode,s[lc].operand);


                startAddres=atoi(s[lc].label);
                fprintf(fp3,"LOCCTR\tLabel\n");
                fprintf(fp3,"%x\t%s\n",hex,s[lc].label);
            }

            else
            {


                    writeToFile(fp2,hex,s[lc].label,s[lc].opcode,s[lc].operand);

                fprintf(fp3,"%x\t%s\n",hex,s[lc].label);
                strcpy(compare,s[lc].opcode);
                if(!strcmp(compare,"RESW"))
                {
                    l=atoi(s[lc].operand);
                    hex=hex+(l*3);
                }
                else if(!strcmp(compare,"RESB"))
                {
                    l=atoi(s[lc].operand);
                    hex=hex+l;
                }
                else if(!strcmp(compare,"BYTE"))
                {
                    l=strlen(s[lc].operand);
                    hex=hex+(l-3);
                }
                else
                {
                    hex+=3;
                }
            }

            var++;


        }
        if(count == 2)
        {

            strcpy(s[lc].opcode,temp[0]);
            strcpy(s[lc].operand,temp[1]);
            printf("\t%s\t%s\n ",s[lc].opcode,s[lc].operand);

                   writeToFile(fp2,hex,s[lc].label,s[lc].opcode,s[lc].operand);


            hex+=3;

        }
        if(count == 1)
        {

            strcpy(s[lc].opcode,temp[0]);

            printf("\t%s\n ",s[lc].opcode);

                   writeToFile(fp2,hex,s[lc].label,s[lc].opcode,s[lc].operand);

            hex+=3;
        }
    }

    fprintf(fp2,"Length is %x\n",hex-4096-3);



    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}
