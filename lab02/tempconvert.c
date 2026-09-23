# include <stdio.h>

void far2cel (float tempIn)
{
	float tempOut = (tempIn - 32) * 5 / 9;

	printf("Temp is  %.2f degrees Celsius\n",tempOut);
	return;
}

void cel2far (float tempIn)
{
        float tempOut = (tempIn * 9 / 5) + 32;

        printf("Temp is  %.2f degrees Fahrenheit\n",tempOut);
	return;
}

int main(void)
{
	int select = 0;
	do
	{

		printf("Welcome to the Temperature Converter!\n");
		printf("Please select how you want to convert your temperature.\n");
		printf("1. Convert from Celsius to Fahrenheit.\n");
		printf("2. Convert from Fahrenheit to Celsius.\n");
		printf("3. Exit program.\n");

		scanf("%d",&select);

		if(select == 1)
		{
			printf("Please input temperature.\n");

			float temp = 0.0;
			scanf("%f", &temp);
			cel2far(temp);
		}
		else if(select == 2)
                {
                        printf("Please input temperature.\n");

                        float temp = 0.0;
                        scanf("%f", &temp);
                        far2cel(temp);
                }
		else if(select == 3)
		{
			printf("Exiting...\n");
		}
		else
		{
			printf("Try again\n");
		}

	}
	while(select != 3);
	printf("Thank you for your time and have a nice day.\n");

}

