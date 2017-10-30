#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
#include<omp.h>
#include<stdlib.h>


using namespace std;

int algo1(char cipher[],char key[]){
	
	
    char message[100], ch;
    int i, key1;
	int flag=0;
 	strcpy(message,cipher);


///////////////////main loop for key iteration///////////////////////////
//	#pragma omp parallel for ordered  
	//#pragma omp for ordered 
   for(int ii=0;ii<30;ii++){
   	if(flag==0){
	   
    int tmp=0;
    tmp=key[ii];
    key1=tmp;
   // cout<<"key been used "<<key1<<endl;
    strcpy(message,cipher);
    
     int count=strlen(message);
    #pragma omp parallel for ordered num_threads(9)
    for(i = 0; i<=count; ++i){
        ch = message[i];

        if(ch >= 'a' && ch <= 180)
		{
            ch = ch - key1;

            if(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
            }
            
           

            message[i] = ch;

        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch - key1;

            if(ch < 'A'){
                ch = ch + 'Z' - 'A' + 1;
            }

            message[i] = ch;
        }
    }
   // cout<<"Decrypted "<<message<<endl;
   
    count=count-1;
    
    char *output=NULL;
    output = strstr(message,"hailhitler");
    if(output){
    	cout<<"!!!!!!!!!!!FOUND  AND KEY IS "<<key1<<" and message is "<<message;
    	
    	flag=1;
    	return 1;
    	exit(0);
	}
	}
   }
    return 0;


}


////////////algo2/////////////////////
int algo2(char cipher[],char key[]){
int a[26][26],m;	
	for(int i=0;i<26;i++)
	{ m=i;
 		for(int j=0;j<26;j++)
 		{ if(m<=25)
   			{a[i][j]=m+97;
   				m++;
   			}
   		else
   			{a[i][j]=97;
   				m=1;
   			}
 		}
	}
	char key1;
	int plen,klen;
	char e[100],d[100];
	strcpy(e,cipher);

	plen=strlen(e);	
	char *output=NULL;
	
	

	
	
	
//	printf("\n Decrypted text::::");
	#pragma omp parallel for num_threads(9)
	for(int ii=0;ii<30;ii++){
		key1=key[ii];
//		cout<<"key been used"<<key1<<endl;;
		for(int i=0;i<plen;i++)
	{	 if(e[i]<key1)
  		{
		  d[i]=a[0][27-abs(e[i]-key1)];
  		}

  		else
  			d[i]=a[0][e[i]-key1];

	//	printf(" %c\n",d[i]);
	//	key1=key[i];
	
	}
	 
   
}
	output = strstr(d,"hail");
    if(output){
    	cout<<"!!!!!!!!!!!FOUND key is "<<key1<<" and message is "<<d;
    	return 1;
    	
    	exit(0);
    
	}
	
}


//////////////main///////////////////
int main()
{
    FILE *fptr,*fkey;
    char filename[15];
    char ch,ch1,ch2;
    char cipher[100];
    char key[128];
   ///////////////////cipher section////////////////////////////
    fptr = fopen("cipher.txt", "r");

    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    int z=0;
    while (ch != EOF)
    {
        ch = fgetc(fptr);
        cipher[z]=ch;
        z++;

    }

    //////////////////key section/////////////////
        fkey = fopen("key.txt", "r");

    if (fkey == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    z=0;

  char line[128];
  while ( fgets ( line, sizeof line, fkey ) != NULL ){
  	  
	  key[z]=atoi(line);
  	z++;
  }
////////////////call alogorithm////////////////////////
int a,b;
#pragma omp parallel sections num_threads(2)
{

#pragma omp section
a=algo1(cipher,key);

#pragma omp section
b=algo2(cipher,key);

}
if(a==1){
	cout<<"\n!!!!!!!!!!!FINAL DECRYPTION RESULT"<<endl<<"ALGORITHM USED IS CAESER!!!!!!!!!!!!!!!!!!";
}
else if(b=1){
	cout<<"\n!!!!!!!!!!!FINAL DECRYPTION RESULT"<<endl<<"ALGORITHM USED IS POLYALPHABATIC!!!!!!!!!!!!!!!!!!";
}
else{
	cout<<"ERROR";
}
return 0;
}
