#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct hashTAB HASH;


typedef struct  hashTAB
{
	char *ident;
	char Description[7000];
    HASH *suiv;

}HASH;
//............................................................................................................................................................;;

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
{int i=1,lgmot=strlen(M),nbr=0;

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
		{code=str[0]+2*str[1];}
	
	      else
		{
		  for(i=0;i<strlen(str);i++)
              {
                hash=hash+puiss(449*nbrdevoi(str),i)*str[i]*nbrdevoi(str)+nbrdecharavleprvoi(str);
                }
                
                code=hash%86037;
             if(code<0)
               code=code*(-1);
	    }
          
           }
             return code;
}
//............................................................................................................................................................;;

 HASH *remplirestruct(FILE *fichier,HASH *H)
{char caract;int nbr=0;HASH *H1;
	int i,j;char*tmp=(char*)malloc(sizeof(char));char*tmp2=(char*)malloc(sizeof(char));int code=0;
   	if(fichier!=NULL)
    {    	do
		 {     
		  

		 	caract=fgetc(fichier);
		 
			 
		 	if (caract=='\n')
		 	 {  
			  caract=fgetc(fichier);
			  if (caract==EOF) {return H;}
			   while(caract!=':')

		 	 	  {  
		 	 	     tmp[i]=caract;
		 	 	     caract=fgetc(fichier);
		 	 	    
		 	 	     
		 	 	     i++;
		 	 	     tmp=(char*)realloc(tmp,sizeof(char)+1);
		 	 	  	
		 	 	  }
		 	 	  
		 	 	  tmp[i]='\0';
//		 	    printf("%s\n",tmp);
		 	 	  
                   
                   
                   code=Hashing(tmp);
//                  printf("%d\n",code);
                   fseek(fichier,-1,SEEK_CUR);	
		 	 	  if(H[code].ident==" ")
		 	 	  { //printf("je suis dans if\n");
		 	 	    
		 	 	        H[code].ident=(char*)malloc(sizeof(char)*strlen(tmp));
		 	 	        strcpy(H[code].ident,tmp);
		 	 	    
		 	 	      //  printf("%s",H[code].ident);
		 	 	         
		 	            fgets(H[code].Description,7000,fichier);    
		 	              
		 	        
		 	          
		 	               
		 	    
		 	            fseek(fichier,-1,SEEK_CUR);
					   //	printf("%s",H[code].Description);	
		 	                H[code].suiv=NULL;
		 	                 
		 	       // printf("je suis plus dans if\n");

		 	          
		 	 	  }
		     	else
			     { H1=(HASH*)malloc(sizeof(HASH));
				// printf("je suis dans else\n");
				 H1->ident=(char*)malloc(sizeof(char)*strlen(tmp));
			       strcpy(H1->ident,tmp);
			     //  printf("%s",H1->ident);
                  fgets(H1->Description,7000,fichier);    
		 	              
		 	        
		 	         
		 	               
		 	    
		 	        fseek(fichier,-1,SEEK_CUR);
		 	        // printf("%s",H1->Description);
			       H1->suiv=H[code].suiv;
			       H[code].suiv=H1;
			       
			       //	printf("je suis sortie du else\n");
				 }
				 
                       }
			i=0;
		
			 
		 
		 }while(caract!=EOF);

}


}
//............................................................................................................................................................;;
int trouver(HASH *H,char *M)
{ int code=0 ;HASH *H1=NULL;
	code=Hashing(M);


	 if (strcmp(H[code].ident,M)==0) return 1;
	 else
	 { H1=H[code].suiv;
	 	while(H1!=NULL)   
        {
        	if(strcmp(H1->ident,M)==0 )return 1;
            H1=H1->suiv;

        }

        return 0;

     }   
    if (H[code].ident==" ") return 0;
	
   
}
//............................................................................................................................................................;;
void ajout(FILE *fichier,char *ligne,HASH *H)
{ HASH *H1;int lg=strlen(ligne),i=0;char *tmp=(char*)malloc(sizeof(char));char caract;char*ligne2;char *P;
 
  P=strchr(ligne,':');
 
strncpy(tmp,ligne,P-ligne);
tmp[strlen(tmp)]='\0';
//printf("%s\n",tmp);

  
   if (trouver(H,tmp)==1){ printf("wshbik srx wshbik\n"); }
   else
   {
 
	ligne2=(char*)malloc(sizeof(char)*(strlen(ligne)+1));
	strcpy(ligne2,ligne);

    printf("%s",ligne2);
    
	fputs(ligne2, fichier);
 
	
      }
   }



//............................................................................................................................................................;;
int suprimer(HASH *H,char *M)
{int code;HASH *H1, *H2;int i;
    
    
	code=Hashing(M);
	H1=H[code].suiv;
	if (strcmp(H[code].ident,M)==0)
	{   
	  if(H1!=NULL)
	  {
	    //  printf("%s\n",H[code].Description);
	    strcpy(H[code].Description,H1->Description);	
	   //printf("%s\n",H[code].Description);
        H[code].ident=H1->ident;
        H[code].suiv = H1->suiv;
    
	    return 1;
	}
	else
	{
	  H[code].ident=" ";
	  
	    H[code].suiv=NULL;
	 return 1;
	}
	}
	
	else 
	{  
		  
	    
		while(H1!=NULL && strcmp(H1->ident,M)!=0)
		  {
		  	
		  	H2=H1;
            H1=H1->suiv;
		  }
		if (H1==NULL)
		  {
			return 0;// le mot nexiste pas.
		  }
		else
		  {
		  
            H2->suiv=H1->suiv;
            H1->ident=" ";
            free(H1);
            return 1;
		  }
	}

}
//............................................................................................................................................................;;

int main(int argc, char const *argv[])
{char *mot,*def;int code;HASH *H=(HASH*)malloc(sizeof(HASH)*86037);
	FILE*fichier;int i;int exis=0;
		fichier=fopen("C:\\Users\\TRETEC\\Desktop\\Doctionary.txt","r");

for (i=0;i<86037;i++)
{
 	H[i].ident=" ";
 	H[i].suiv=NULL;
}
	H=remplirestruct(fichier,H);
        mot=(char*)malloc(sizeof(char)*36);
        printf("Donnez le mot a suprimer:\n");
        scanf("%[^\n]",mot);
         printf("VERIFICATION DE L EXISTANCE DU MOT AVEC LA FONCTION 'TROUVER' <1> existe <0> nexiste pas:\n");
           exis=trouver(H,mot);
           printf("<%d>\n",exis);
          printf("DANS LE CAS :<1> LE MOTS A ETE BIEN SUPRIMER <0> nexiste pas:\n");
           exis=suprimer(H,mot);
        printf("<%d>\n",exis);
        printf("VERIFICATION DE LA SUPRESSION AVEC LA FONCTION 'TROUVER' <1> existe <0> nexiste pas:\n");
            exis=trouver(H,mot);
         printf("<%d>\n",exis);	 
	fclose(fichier);

	return 0;
}
