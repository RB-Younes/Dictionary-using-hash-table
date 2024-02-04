#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int puiss(int n,int i)
{
    int d;int j=n;
    for(d=0;d<i-1;d++)
    {
        j=j*n;
    }
    return j;
}

 //............................................................................................................................................................;;
 int nbrdecharavleprvoi(char*M)
{int i=0,lgmot=strlen(M),nbr=0;

	while(M[i]!='A' && M[i]!='O' && M[i]!='Y' && M[i]!='U' && M[i]!='I' && M[i]!='E' )
	{
	i++;
	nbr++;
	}


	return nbr;
}
//............................................................................................................................................................;;
int nbrdevoi(char*M)
{int i,lgmot=strlen(M),nbr=0;
for (i = 0; i < lgmot; ++i)
	{
	if(M[i]=='A' ||M[i]=='O'|| M[i]=='Y' ||M[i]=='U' ||M[i]=='I' ||M[i]=='E' ) nbr++;

	}
	return nbr;
}
//............................................................................................................................................................;;

int Hashing(char *str)
{ 
    int i;
    int code,hash;
    hash=0;
 if (strlen(str)==1) code=str[0];
    else{
	      if(strlen(str)==2)
		{code=(str[0]+2*str[1])*nbrdevoi(str);}

	      else
	   
		{
		  for(i=0;i<strlen(str);i++)
              {
                hash=hash+puiss(449*nbrdevoi(str),i)*str[i]+nbrdevoi(str)*nbrdecharavleprvoi(str);
                }
                //NBRDEVOI c le nbr de voyelles et nbrdecharavleprvoi c le nbr de consonnes avant la premire voyelles.
                code=hash%86037;
             if(code<0)
               code=code*(-1);
	    }

           }
             return code;
}


void affich (FILE *fichier,int *TAB)
{int caract;int nbr=0;char*tmp=(char*)malloc(sizeof(char));int i,j,colision;int hache,code;int MAX=0;

   	if(fichier!=NULL)
    {    	do
		 {


		 	caract=fgetc(fichier);

		 	if (caract=='\n')
		 	 {
			  caract=fgetc(fichier);
			  if (caract==EOF) { printf("le nbr max de colsions (dans la meme ligne) est: %d",MAX);}
			   while(caract!=':')

		 	 	  {
		 	 	     tmp[i]=caract;
		 	 	     caract=fgetc(fichier);

		 	 	     i++;
		 	 	     tmp=(char*)realloc(tmp,sizeof(char)+1);
		 	 	  }
		 	 	  tmp[i]='\0';
//		 	 	  printf("%s:",tmp);
                  code=Hashing(tmp);
//                  printf("%d\n",code);
                  TAB[code]=TAB[code]+1;
                 
                  


				 if (TAB[code]>MAX){MAX=TAB[code];};
				 } 


		 	 			 	
			i=0;
            hache=0;
            code=0;
		 }while(caract!=EOF);


}


}
int main()
{
 int n,k;char *M;int *TAB=(int*)malloc(sizeof(int)*86038);

	FILE*fichier;
	fichier=fopen("C:\\Users\\TRETEC\\Desktop\\doctionary.txt","r");
 for(n=0;n<86038;n++)
 {TAB[n]=0;
 }

	affich(fichier,TAB);
   

	fclose(fichier);
	return 0;
}


