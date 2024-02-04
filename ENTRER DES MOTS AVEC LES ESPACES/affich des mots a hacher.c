#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void affich (FILE *fichier)
{char caract;int nbr=0;char*tmp=(char*)malloc(sizeof(char));int i;
	if(fichier!=NULL)
    {    	do
		 {  
		 	caract=fgetc(fichier);
		 	 
		 	if (caract=='\n')
		 	 {  caract=fgetc(fichier);
			   while(caract!=':')

		 	 	  {  
		 	 	     tmp[i]=caract;
		 	 	     caract=fgetc(fichier);
		 	 	     
		 	 	     i++;
		 	 	     tmp=(char*)realloc(tmp,sizeof(char)+1);
		 	 	  	
		 	 	  }
		 	 	  
		 	 	  tmp[i]='\0';
		 	 	  printf("%s\n",tmp );
		 	 	  
		 	 	  
		 	 	
		 	 			 	 }
			i=0;					 
		 }while(caract!=EOF);

	
}
}


int main()
{
 int n;char *M;

	FILE*fichier;
	fichier=fopen("C:\\Users\\TRETEC\\Desktop\\doctionary.txt","r");

	affich(fichier);
	
	fclose(fichier);
	return 0;
	
	
	
}
