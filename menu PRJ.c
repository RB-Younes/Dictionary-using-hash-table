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

int nbrmot (FILE *fichier)
{char caract;int nbr;
	if(fichier!=NULL)
    {    	do
		 {
		 	caract=fgetc(fichier);
		 	 if (caract==EOF) return nbr;
		 	if (caract=='\n')
		 	 {

		 	 	   nbr++;
		 	 	
		 	 			 	 } 
		 }while(caract!=EOF);
}
	return nbr;
}
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

		 	 	  
                   
                   
                   code=Hashing(tmp);
                   fseek(fichier,-1,SEEK_CUR);	
		 	 	  if(H[code].ident==" ")
		 	 	  { 
		 	 	    
		 	 	        H[code].ident=(char*)malloc(sizeof(char)*strlen(tmp));
		 	 	        strcpy(H[code].ident,tmp);
		 	 	    
		 	 	      
		 	 	         
		 	            fgets(H[code].Description,7000,fichier);    
		 	              
		 	        
		 	          
		 	               
		 	    
		 	            fseek(fichier,-1,SEEK_CUR);
		 	                H[code].suiv=NULL;
		 	                 

		 	          
		 	 	  }
		     	else
			     { H1=(HASH*)malloc(sizeof(HASH));
				 H1->ident=(char*)malloc(sizeof(char)*strlen(tmp));
			       strcpy(H1->ident,tmp);
                  fgets(H1->Description,7000,fichier);    
		 	              
		 	        
		 	         
		 	               
		 	    
		 	        fseek(fichier,-1,SEEK_CUR);
			       H1->suiv=H[code].suiv;
			       H[code].suiv=H1;
			       
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
	//printf("%d\n",code);
	//printf("%s\n",H[code].ident);

	 if (strcmp(H[code].ident,M)==0) return 1;
	 else
	 { H1=H[code].suiv;
	 	while(H1!=NULL)   
        {// printf("je suis dans while ^^");
          //	printf("%s\n",H1->ident);
        	if(strcmp(H1->ident,M)==0 ) return 1;
            H1=H1->suiv;

        }
//        printf("rani 9BEL return ");
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


  
   if (trouver(H,tmp)==1){ printf("CE MOT EXISTE DEJA!!!!!\n"); }
   else
   {
 
	ligne2=(char*)malloc(sizeof(char)*(strlen(ligne)+1));
	strcpy(ligne2,ligne);

    
    
	fputs(ligne2, fichier);
    fputc('\n',fichier);
	
      }
	  printf("le mot a ete bien ajouter\n");
   }
//......................................................................................................................................................................
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
{char *mot,*ligne;int code;HASH *H=(HASH*)malloc(sizeof(HASH)*86037);int X,n=0,nbr=0;
	FILE*fichier;int i;int exis;
	fichier=fopen("C:\\Users\\TRETEC\\Desktop\\DocTIONARY.txt","r+");
//initialisation de la table:
for (i=0;i<86037;i++)
{
 	H[i].ident=" ";
}
printf("[1]--------------<existance dun mot>--------------------[1]\n");
printf("[2]-------------------<ajout mot>-----------------------[2]\n");
printf("[3]-----------------<suppression>-----------------------[3]\n");
printf("[4]-------------------<distance>------------------------[4]\n");
printf("DONNEZ LE NUMERO DE LA LIGNE:");
      scanf("%d",&X);
    switch(X){

    case 1: 
        
	H=remplirestruct(fichier,H);
        mot=(char*)malloc(sizeof(char)*36);
        printf("Donnez le mot a rehercher:\n");
        scanf("%s",mot);
        exis=trouver(H,mot);
        if (exis==1){printf("le mot existe.\n");}
		else printf("le mot nexiste pas.\n");
		printf("pour la saise avec des espaces veuiller consulter le fichier 'recherche lexistance dun mot.c'.\n");
        break;
    case 2 :
    	H=remplirestruct(fichier,H);
        ligne=(char*)malloc(sizeof(char)*7036);
        printf("Donnez la ligne a ajouter:\n");
        scanf("%s",ligne);
        ajout(fichier,ligne,H);
        	printf("pour la saise avec des espaces veuiller consulter le fichier 'ajout dun mot.c'.\n");
        break;
    case 3:
    		H=remplirestruct(fichier,H);
        mot=(char*)malloc(sizeof(char)*36);
        printf("Donnez le mot a suprimer:\n");
        scanf("%s",mot);
         printf("VERIFICATION DE L EXISTANCE DU MOT AVEC LA FONCTION 'TROUVER' <1> existe <0> nexiste pas:\n");
           exis=trouver(H,mot);
           printf("<%d>\n",exis);
          printf("DANS LE CAS :<1> LE MOTS A ETE BIEN SUPRIMER <0> nexiste pas:\n");
           exis=suprimer(H,mot);
        printf("<%d>\n",exis);
        printf("VERIFICATION DE LA SUPRESSION AVEC LA FONCTION 'TROUVER' <1> existe <0> nexiste pas:\n");
            exis=trouver(H,mot);
         printf("<%d>\n",exis);	 
         	printf("pour la saise avec des espaces veuiller consulter le fichier 'suppression dun mot.c'.\n");
    case 4:
        printf("DISTANCE CE TROUVE DANS FICHIER DISTANCE.C MERCI ^^.\n");
        break;
    default: 

	 printf("Out of range");
                break;
        	}
		fclose(fichier);		
     return 0;
 }




  

