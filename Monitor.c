#include "Header.h"

/*------------------------------------------------comunicaçao---------------------------------------------------------*/

/*---------------------------------array que guarda as strings para escrever no ficheiro stats------------------------*/
char stats[10][BUFFER_SIZE];
int wait_sim;
int num_client_prio=0;
int num_client_nprio=0;
int num_prod=0;
int prod_s=0;
int nr_withdrawal=0;
int nr_clients=0;
int nr_clients_at=0;
int nr_employee_shop=0;
int time_at=0;
/*---------------------------------variaveis globais------------------------------------------------------------------*/
int end=0;
int state=0;

pthread_t thread_write_on_screen;
pthread_t thread_wait;

void main()
{
    wait_sim = waitForSimConnection();
	

	


//inicialzação das stats
strcpy(stats[0], "Numero de clientes não prioritários = 0");
strcpy(stats[1], "Numero de clientes prioritários = 0");
strcpy(stats[2], "Numero de desistências =  = 0");
strcpy(stats[3], "Numero de clientes na loja = 0");
strcpy(stats[4], "Numero de clientes atendidos = 0");
strcpy(stats[5], "Numero de empregados = 0");
strcpy(stats[6], "Numero de stock prod A = 0");
strcpy(stats[7], "Numero de stock prod B = 0");
strcpy(stats[8], "Numero de stock prod C = 0");
strcpy(stats[9], "Tempo médio atendimento = 0");



do
{ 
	state = readIntegerFromSimulator();
	switch(state)
	{
		case 0: //inicio da simulação
		printf("%s\n","Estado da Loja ==> Inicio da Simulação");
		sprintf(stats[0], "Numero de clientes não prioritários = %i\n",0);
		sprintf(stats[1], "Numero de clientes prioritários = %i\n",0);
		sprintf(stats[2], "Numero de desistências =  = %i\n",0);
		sprintf(stats[3], "Numero de clientes na loja = %i\n",0);
		sprintf(stats[4], "Numero de clientes atendidos = %i\n",0);
		sprintf(stats[5], "Numero de empregados = %i\n",1);
		sprintf(stats[6], "Numero de stock prod A = %i\n",10);
		sprintf(stats[7], "Numero de stock prod B = %i\n",10);
		sprintf(stats[8], "Numero de stock prod C = %i\n",10);
		sprintf(stats[9], "Tempo médio atendimento = %i\n",0);	
		writeStatsOnScreen();
		end=1;
		break;

		case 1: //fim da simulação
		writeStatsOnScreen();
		writeStatsFile();
		end=0;		
		break;
		
		case 2://quando tem cliente prioritario atualiza estatistica no ecra
		num_client_prio=readIntegerFromSimulator();
		sprintf(stats[1], "Numero de clientes prioritários = %i\n",num_client_prio);
		writeStatsOnScreen();
		end=1;
		break;

		case 3://quando tem cliente nao prioritario atualiza estatistica no ecra
		num_client_nprio=readIntegerFromSimulator();
		sprintf(stats[0], "Numero de clientes não prioritários = %i\n",num_client_nprio);
		writeStatsOnScreen();
		end=1;
		break;

		case 4: //quando tem atualização do valor do stock para fazer
			num_prod = readIntegerFromSimulator();
			switch(num_prod)
			{
				case 1: //prod A
				prod_s=readIntegerFromSimulator();
				sprintf(stats[6], "Numero de stock prod A = %i\n",prod_s);
				writeStatsOnScreen();
				break;
				
				case 2: //prod B
				prod_s=readIntegerFromSimulator();
				sprintf(stats[7], "Numero de stock prod B = %i\n",prod_s);
				writeStatsOnScreen();
				break;

				case 3: //prod C
				prod_s=readIntegerFromSimulator();
				sprintf(stats[8], "Numero de stock prod C = %i\n",prod_s);
				writeStatsOnScreen();
				break;
		
			}
			break;

		case 5: //atualiza numero de desistencias
			nr_withdrawal=readIntegerFromSimulator();	
			sprintf(stats[2], "Numero de desistências =  = %i\n",nr_withdrawal);
			writeStatsOnScreen();
			break;

		case 6: //atualia nr de clientes na loja
			nr_clients=readIntegerFromSimulator();	
			sprintf(stats[3], "Numero de clientes na loja = %i\n",nr_clients);
			writeStatsOnScreen();
			break;
		
		case 7: //atualia nr de clientes atendidos
			nr_clients_at=readIntegerFromSimulator();	
			sprintf(stats[4], "Numero de clientes atendidos = %i\n",nr_clients_at);
			writeStatsOnScreen();
			break;

		case 8: //atualia nr de empregados na loja
			nr_employee_shop=readIntegerFromSimulator();	
			sprintf(stats[5], "Numero de empregados = %i\n",nr_employee_shop);
			writeStatsOnScreen();
			break;

		case 9: //atualia tempo médio de atendimento
			time_at=readIntegerFromSimulator();	
			sprintf(stats[9], "Tempo médio atendimento = %i\n",time_at);
			writeStatsOnScreen();
			break;
	}
}
while(end!=0);
}

/*
void * printOnScreen(void* buff)
{
    char * buffer = (char *) buff;
    printf(STRING_FORM,buffer);
}

void * readWriteFile()
{
    FILE * readFile = fopen(MONITOR_FILE,READ_MODE);

    if(!readFile)
    {
        printf(READ_ERROR);
        exit(1);
    }

    FILE * writeFile = fopen(SIMULATOR_FILE,WRITE_MODE);

    char * buffer = (char *) malloc(sizeof(char)* BUFFER_SIZE);

    while(fgets(buffer,BUFFER_SIZE,readFile))
    {
        fprintf(writeFile, STRING_FORM, buffer);
        pthread_create(&thread_wait,NULL ,printOnScreen, (void*)buffer);
        pthread_join(thread_wait, NULL);
    }

    fclose(readFile);
    fclose(writeFile);
}
*/

/*---------------------------------------funçoes auxiliares-----------------------------------------------------------*/
//apresenta estatisticas no monitor
void writeStatsOnScreen()
{

/*sprintf(stats[0], "Numero de clientes não prioritários = %i\n",4);
sprintf(stats[1], "Numero de clientes prioritários = %i\n",3);
sprintf(stats[2], "Numero de desistências =  = %i\n",2);
sprintf(stats[3], "Numero de empregados = %i\n",1);
sprintf(stats[4], "Numero de stock prod A = %i\n",10);
sprintf(stats[5], "Numero de stock prod B = %i\n",10);
sprintf(stats[6], "Numero de stock prod C = %i\n",10);
sprintf(stats[7], "Numero de stock prod D = %i\n",10);
sprintf(stats[8], "Tempo médio atendimento = %i\n",2);*/
printf("%s\n", "**********************************************************************");
printf("%s\n", "*************************Estatisticas da Loja*************************");
printf("%s\n", "**********************************************************************");
printf("%s",stats[0]);
printf("%s",stats[1]);
printf("%s",stats[2]);
printf("%s",stats[3]);
printf("%s",stats[4]);
printf("%s",stats[5]);
printf("%s",stats[6]);
printf("%s",stats[7]);
printf("%s",stats[8]);
printf("%s",stats[9]);
printf("%s\n", "**********************************************************************");
printf("%s\n", "*********************************FIM**********************************");
printf("%s\n", "**********************************************************************\n\n");

}
//escreve estatisticas no ficheiro
void writeStatsFile()
{	
	FILE * writeStats = fopen(STATS_FILE, WRITE_MODE);
	
fprintf(writeStats, STRING_FORM, "**********************************************************************\n");
fprintf(writeStats, STRING_FORM, "*************************Estatisticas da Loja*************************\n");
fprintf(writeStats, STRING_FORM, "**********************************************************************\n");
fprintf(writeStats, STRING_FORM, stats[0]);
fprintf(writeStats, STRING_FORM, stats[1]);
fprintf(writeStats, STRING_FORM, stats[2]);
fprintf(writeStats, STRING_FORM, stats[4]);
fprintf(writeStats, STRING_FORM, stats[5]);
fprintf(writeStats, STRING_FORM, stats[6]);
fprintf(writeStats, STRING_FORM, stats[7]);
fprintf(writeStats, STRING_FORM, stats[8]);
fprintf(writeStats, STRING_FORM, stats[9]);
fprintf(writeStats, STRING_FORM, "**********************************************************************\n");
fprintf(writeStats, STRING_FORM, "**********************************FIM*********************************\n");
fprintf(writeStats, STRING_FORM, "**********************************************************************\n");
fclose(writeStats);

}

//le mensagens do simulador
char* readFromSimulator()
{
    char* message = (char*) malloc(sizeof(char)*BUFFER_SIZE);
    read(wait_sim,message,BUFFER_SIZE);
    return message;
}
//converte para inteiro
int readIntegerFromSimulator()
{
    return atoi(readFromSimulator());
}

