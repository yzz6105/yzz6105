#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define BUFFER_SIZE 1024

struct token{
char col1[10];
char col2[10];
char col3[10];
}a[100];


struct tok{
char row[10];
char row2[10];
char row3[10];
}r[100];

const char *delimiter_characters = " ";
const char *delim2="\n";
const char *filename = "SIC_input.txt";
char buffer[ BUFFER_SIZE ];
char *last_token;
char *last_token1;

FILE *input_file,*fp, *sym;

void read_file()
{
    input_file = fopen( filename, "r" );
    fp = fopen( "SIC_output.txt","w");
    sym=fopen("SIC_symbol.txt","w");
}

int check_err()
{
    if( input_file == NULL )
    {

        fprintf( stderr, "Unable to open file %s\n", filename );
        return 0;

    }
    else
        return 1;
}

struct attributes
{   char *add;
    char *label;
    char *opcode;
    char *operand;
}c;


void symbol()
{
    //int p=4096;
    if( ferror(sym) )
    {
        perror( "The following error occurred" );
        fclose( sym );
    }
    FILE *col=fopen("SIC_output.txt","r");
    if( ferror(col) )
    {
        perror( "The following error occurred" );
        fclose(col);
    }
    printf("\n The Symbol \n");
    printf("------------\n");
    while( fgets(buffer, BUFFER_SIZE, col) != NULL )
    {

        const char *delimiter = "\t";
        //printf("%x\t", i);
        c.add=strtok( buffer, delimiter);
        c.label = strtok( NULL, delimiter );
        c.opcode = strtok( NULL, delimiter);
        c.operand = strtok( NULL, delimiter);

        if(c.operand!= NULL)
        {
                fprintf(sym,"%s\t%s\n",c.add,c.label);
                printf("%s\t%s\n",c.add,c.label);
        }

    }
    /*
    for(int x=0; x<=s; x++)
    {
        strcpy(col2,a[x].col1 );
        if(col2!=NULL)
            fprintf(sym,"%x\t%s\n",p,col2);

        if (x!=0)
            p=p+3;
    }
    */

    fclose( sym );
    fclose( col );
}

int last(int z)
{
    int p=4096, op,l;
    if( ferror(fp) )
    {
        perror( "The following error occurred" );
        fclose( fp );
    }

    printf("\nThe\tLabel\tOpcode\tOperand\n");
    printf("-----\t-----\t------\t-------\n");
    for(int x=0;x<=z;x++)
    {
        printf("%d\t%s\t%s\t%s\n",x+1,a[x].col1,a[x].col2,a[x].col3 );
    }
    for(int x=0; x<=z; x++)
    {
        fprintf(fp,"%x\t%s\t%s\t%s\n",p,a[x].col1,a[x].col2,a[x].col3 );
        //printf("%s\n",a[x].col2);

        if(!(strcmp(a[x].col2,"RESW")))
        {
            //printf("I have been executed..........");
            op=atoi(a[x].col3);
            p+=3*op;
            //printf("%d,%x",3*op,p);
        }
        else if(!(strcmp(a[x].col2,"RESB")))
        {
           op=atoi(a[x].col3);
           p+=op;
        }
        else if(!strcmp(a[x].col2,"BYTE"))
                {
                    l=strlen(a[x].col3);
                    p=p+(l-3);
                }

        else if(x!=0)
            p=p+3;

    }

    fclose( fp );
}

void token()
{
    int i=0,j=1,k=0,l=1,z=-1;
    int q;
    q=check_err();
    if(q==1)
    {

        while(fgets(buffer, BUFFER_SIZE, input_file) != NULL )
        {
            i=0;

            last_token1 = strtok( buffer, delim2 );
            while(last_token1!=NULL)
            {
                z++;
                last_token = strtok( last_token1, " \t" );
                while( last_token != NULL )
                {
                    strcpy(r[k].row,last_token);
                    k++;
                    last_token = strtok( NULL," \t" );
                }
                if(k==1)
                {
                    strcpy(a[z].col2,r[0].row);
                    printf("%d-\t%s\t%s\t%s\n",k,a[z].col1,a[z].col2,a[z].col3);

                }
                else if(k==2)
                {
                    strcpy(a[z].col2,r[0].row);
                    strcpy(a[z].col3,r[1].row);
                    printf("%d-\t%s\t%s\t%s\n",k,a[z].col1,a[z].col2,a[z].col3);
                }
                else if(k==3)
                {
                    strcpy(a[z].col2,r[1].row);
                    strcpy(a[z].col3,r[2].row);
                    strcpy(a[z].col1,r[0].row);
                    printf("%d-\t%s\t%s\t%s\n",k,a[z].col1,a[z].col2,a[z].col3);
                }
                last_token1 = strtok( NULL, delim2 );
                k=0;
            }
        }
    }
    last(z);
}

int main()
{
    read_file();
    token();
    symbol();


    return 0;
}
