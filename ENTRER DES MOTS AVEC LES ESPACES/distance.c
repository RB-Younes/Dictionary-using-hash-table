  #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hashTAB HASH;
typedef struct  hashTAB
{
	char *ident;
	char Description[7000];
    HASH *suiv;

}HASH;

typedef struct freq freq;
struct freq
{
	char car;
	int occ;
};

//.........................................................................................
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

  
   if (trouver(H,tmp)==1){ printf("le mot existe deja\n"); }
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
//.........................................................................................

int freqchar(char *m, char c)
{
	int oc, i;
    oc=0;
	for(i=0; i<strlen(m); i++)
	{
		if (m[i]==c)
		{
			oc++;
		}
	}
	return oc;
}

//.........................................................................................
freq* frequences(char* s)
{
	int i, j, trouve, n;
	freq* tabocc;
	tabocc=(freq*)calloc(strlen(s), sizeof(freq));
	tabocc[0].car = s[0];
	tabocc[0].occ = freqchar(s, s[0]);
    n=1;
	 i=1;
	 trouve=0;
	while (i< strlen(s))
	{
		j=0;
		trouve=0;
		while ((j<n) && (trouve==0))
		{
			if(tabocc[j].car==s[i])
			{
				trouve=1;
			}
			j++;
		}
		if(trouve==0)
	    {
		    tabocc[n].car= s[i];
	     	tabocc[n].occ= freqchar(s, s[i]);
	    	n++;
	    	i++;
		}
		if(trouve==1)
		{
	    	i++;
		}
	}
	tabocc[n].car= '\0';
	tabocc[n].occ= 0;
	return tabocc;
}

//.....................................................................................
//.....................................................................................

//....................................................................................
//....................................................................................
char *strnchr(char *s,char c,int n)
{
    char *pos;
    int i=0;
    while(i<n)
    {
        pos=strchr(s,c);
        if(!pos)
        {
            return pos;
        }
        s=pos+1;
        i++;
    }
    return pos;
}

//.......................................................................................
//.......................................................................................
int Distance(char* a, char* b) {
	freq *c = frequences(a), *d = frequences(b);
	int i, j ,dis, trouve;
	dis= 0;
	i=0;
 printf("je suis dans distance\n");
	while ((i< strlen(a)) && (c[i].car!='\0'))
	 {
	 	trouve=0;
	 	j=0;
		while ((j < strlen(b)) && (d[j].car!='\0') && (trouve==0))
		{
			if (c[i].car==d[j].car)
			{
				if (c[i].occ > d[j].occ)
				{
				  dis=dis+ (c[i].occ-d[j].occ);
				  trouve=1;
		    	}
		    	else
		    	{
		    	  dis=dis+ (d[j].occ-c[i].occ);
				  trouve=1;
				}
			}
			j++;
		}
		if(trouve!=1)
       	{
			dis=dis+c[i].occ;
    	}
    	i++;
		
	}
	i=0;
		while ((i< strlen(b)) && (d[i].car!='\0'))
	 {
	 	trouve=0;
	 	j=0;
		while ((j < strlen(a)) && (c[j].car!='\0') && (trouve==0))
		{
			if (d[i].car==c[j].car)
			{
		    	trouve=1;
			}
			j++;
		}
		if(trouve!=1)
       	{
			dis=dis+d[i].occ;
    	}
    	i++;
		
	}
	return dis;

}
 //.......................................................................................
void Distance2 (FILE *fichier,char *A,int k)
{char caract;int nbr=0;HASH *H1;
	int i,j;char*tmp=(char*)malloc(sizeof(char));char*tmp2=(char*)malloc(sizeof(char));int code=0;int dis;
	   
	   
	  
   	if(fichier!=NULL)
    {    	do
		 {     
		  

		 	caract=fgetc(fichier);
		 
			 
		 	if (caract=='\n')
		 	 {  
			  caract=fgetc(fichier);
			  if (caract==EOF) {return 0;}
			   while(caract!=':')

		 	 	  {  
		 	 	     tmp[i]=caract;
		 	 	     caract=fgetc(fichier);
		 	 	    
		 	 	     
		 	 	     i++;
		 	 	     tmp=(char*)realloc(tmp,sizeof(char)+1);
		 	 	  	
		 	 	  }
		 	 	  
		 	 	  tmp[i]='\0';
		 	 	  printf("%s\n",tmp);
		 	 	  nbr++;
		 	 	  printf("nbr=%d\n",nbr);
                  dis=Distance(A,tmp);
	   
	             if (dis<k) {printf("%s.\n",tmp);}

       
          }

		i=0;		
		 }while(caract!=EOF);


}



}
 //.......................................................................................
int main(int argc, char const *argv[])
{ char *mot,*def;int code;HASH *H=(HASH*)malloc(sizeof(HASH)*86037);char*mot1=(char*)malloc(sizeof(char)*36);int dif;
	FILE*fichier;int i;int exis=0;int k;
		fichier=fopen("C:\\Users\\TRETEC\\Desktop\\Doctionary.txt","r");


        mot=(char*)malloc(sizeof(char)*36);
          printf("Donnez le mot:\n");
        scanf("%s",mot);
        printf("Donnez la difference maximale:\n");
        scanf("%d",&dif);
        
        Distance2(fichier,mot,dif);
        
   fclose(fichier);
  
        
    return 0;
        
}
