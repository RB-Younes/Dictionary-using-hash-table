#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int nbrmot (FILE *fichier)
{char caract;int nbr;
	if(fichier!=NULL)
    {    	do
		 {
		 	caract=fgetc(fichier);
		 	 
		 	if (caract=='\n')
		 	 {

		 	 	   nbr++;
		 	 	
		 	 			 	 } 
		 }while(caract!=EOF);
}
	return nbr;
}


int main()
{
 int n;

	FILE*fichier;
	fichier=fopen("C:\\Users\\TRETEC\\Desktop\\doctionary.txt","r");

	n=nbrmot(fichier);
	printf("le nbr de mots total est :%d\n", n);
	fclose(fichier);
return 0;
}
	
	
