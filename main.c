#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float numbers[100];
int mainFlag=1, i, j, k, operatorsLen; 
int contN, cacheCont, contOp, nP1, nP2, flagOp;
char buffer[100], operators[100], numberCache[100];

char *myGets(char *s){
	fgets(s, 100, stdin);

	if(strlen(s)>0 && s[strlen(s)-1]=='\n')
		s[strlen(s)-1]='\0';

	fflush(stdin);
}

int main(){
	while(mainFlag){
	printf("> ");
	myGets(buffer);

	//Check the buffer for a exit command
	if(strcmp(buffer, "exit")==0){
		printf("Leaving. . .\n");
		break;
	}

	//Split numbers and operator from main string in two arrays
	for(i=0; i<strlen(buffer); i++){
		if(i==0){
			for(j=0; j<100; j++) 
				numbers[j]='\0'; //limpar array de numeros
			
			memset(operators,0,strlen(operators)); //clear operators string
			memset(numberCache,0,strlen(numberCache)); //clear cache string
			
			contN=0;	
			contOp=0;
			cacheCont=0;
			flagOp=1;
			nP2=0;
			nP1=0;
		}
		
		if((buffer[i]=='+' 
			|| buffer[i]=='-' 
			|| buffer[i]=='*' 
			|| buffer[i]=='/') 
			&& flagOp==0)
		{			
			operators[contOp]=buffer[i];

			numbers[contN]=atof(numberCache); //atof - string->float
			memset(numberCache,0,strlen(numberCache)); //clear cache string
			
			contN++;
			contOp++;
			cacheCont=0;
			flagOp=1;
		}else{
			if((buffer[i]>='0' && buffer[i]<='9') 
				|| buffer[i]=='-' 
				|| buffer[i]=='+' 
				|| buffer[i]=='.'
				|| buffer[i]==',')
			{
				if(buffer[i]==','){
					numberCache[cacheCont]='.';
					cacheCont++;
					flagOp=0;
				}else{
					numberCache[cacheCont]=buffer[i];
					cacheCont++;
					flagOp=0;
				}
			}else if(buffer[i]=='(' || buffer[i]==')'){
				//do nothing, ignore "()"
			}else{
				printf("SYNTAX ERROR !!!!\n");
				break;
			}			
		}

		if(i==strlen(buffer)-1)
			numbers[contN]=atof(numberCache);			
	}

	operatorsLen=strlen(operators);

	//Check how many operator with high priority (p2) or low priority (p1)
	for(i=0; i<operatorsLen; i++){
		if(operators[i]=='+' || operators[i]=='-'){
			nP1++;
		}else if(operators[i]=='*' || operators[i]=='/'){
			nP2++;
		}
	}

	//do high priority operations
	for(i=0; i<nP2; i++){
		for(j=0; j<operatorsLen; j++){
			if(operators[j]=='*'){
				numbers[j]= numbers[j] * numbers[j+1];

				for(k=j; k<operatorsLen; k++){
					operators[k]=operators[k+1];
					numbers[k+1]=numbers[k+2];
				}

				break;
			}else if(operators[j]=='/'){
				numbers[j]=numbers[j] / numbers[j+1];
				
				for(k=j; k<operatorsLen; k++){
					operators[k]=operators[k+1];
					numbers[k+1]=numbers[k+2];
				}
				
				break;
			}
		}
	}

	//do low priority operations
	for(i=0; i<nP1; i++){
		for(j=0; j<operatorsLen; j++){
			if(operators[j]=='+'){
				numbers[j] = numbers[j] + numbers[j+1];

				for(k=j; k<operatorsLen; k++){
					operators[k]=operators[k+1];
					numbers[k+1]=numbers[k+2];
				}
				
				break;
			}else if(operators[j]=='-'){
				numbers[j] = numbers[j] - numbers[j+1];

				for(k=j; k<operatorsLen; k++){
					operators[k]=operators[k+1];
					numbers[k+1]=numbers[k+2];
				}

				break;
			}
		}
	}

	printf("Result: %.2f\n\n", numbers[0]);		
	
	}
	
	return 0;
}