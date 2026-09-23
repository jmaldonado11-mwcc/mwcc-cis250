# include <stdio.h>

void far2cel(float temp){
	float tempOut = (temp - 32) * 5 /9;
	printf("Temp is %.2f degrees celsius\n", tempOut);
}

void cel2far(float temp){
	float tempOut = (temp * 9 /5) + 32;
        printf("Temp is %.2f degrees fahrenheit\n" , tempOut);
}

int main(void){
	int select = 0;
	do{
		printf("Welcome to Temp Converter!\n");
                printf("Please select an option.\n");
                printf("1. Convert from Fahrenheit to Celsius.\n");
                printf("2. Convert from Celsius to Fahrenheit.\n");
                printf("3. Exit the program.\n");
		scanf("%d", &select);
		if(select == 1){
			float temp = 0;
			printf("Please input a temperature value\n");
			scanf("%f" ,&temp);
			far2cel(temp);
		}
		else if(select == 2){
                        float temp = 0;
                        printf("Please input a temperature value\n");
                        scanf("%f" ,&temp);
                        cel2far(temp);
                }else if(select == 3){
			printf("Exiting program...\n");
			break;
		}
		else{
			printf("Try again\n");
		}
	}while(select != 3);
	printf("Thank you for your time and have a nice day.\n");

}
