#include "Header.h"

time_t init;
time_t end;
time_t at_start;
time_t at_end;
/*------------------------------------------------comunicaçao---------------------------------------------------------*/
int sim_socket;

/*------------------------------------------------variavel local------------------------------------------------------*/
int flag;
int nr_employee_needed;
int nr_employee_now;
int nr_client_now;
int rest;
double simTime;
double atTime_aux;
int atTime_aux2;
int atTime;
int sec;
int min;
char info[BUFFER_SIZE];

/*------------------------------------------------sincronizaçao-------------------------------------------------------*/
mutex mutex_id;
mutex mutex_com;
mutex mutex_nr_cl;
mutex mutex_stock;
mutex mutex_withdrawal;
mutex mutex_employeenow;
mutex mutex_time;
mutex mutex_print_sim;
sem_t semaf_client;
sem_t sem_com;
sem_t sem_prio;
/*-------------------------------------------variaveis globais--------------------------------------------------------*/

/*----------------------------------------main------------------------------------------------------------------------*/
int main()
{	
	rest=0;
	nr_employee_now=1;
	nr_client_now=0;
	nr_employee_needed=1;
	flag=1;
    	id_client=0;
	nr_cl_prio=0;
	nr_cl_nprio=0;
	start=0;	
	client_served=0;
	num_client[0]=0;
	num_client[1]=0;
	withdrawal_nr=0;
	simTime=0;
	atTime=0;
	atTime_aux=0;
	atTime_aux2=0;
   	setbuf(stdout,NULL);
   	setbuf(stderr,NULL);
	srand(time(NULL));  
 readConfFile(&s_conf);
 sim_socket = createSockectSimulator();

	array_sell_prod[0]=s_conf.stock_prod;
	array_sell_prod[1]=s_conf.stock_prod;
	array_sell_prod[2]=s_conf.stock_prod;

	array_stock_prod[0]=s_conf.stock_shop;
	array_stock_prod[1]=s_conf.stock_shop;
	array_stock_prod[2]=s_conf.stock_shop;
	
	array_flag_stock[0]=1;
	array_flag_stock[1]=1;
	array_flag_stock[2]=1;
//inicializa trincos
	initMutex(&mutex_id);
	initMutex(&mutex_com);
	initMutex(&mutex_nr_cl);
	initMutex(&mutex_stock);
	initMutex(&mutex_withdrawal);
	initMutex(&mutex_employeenow);
	initMutex(&mutex_print_sim);
	
//inicialização semaforos
	initSem(&semaf_client,0);
	initSem(&sem_com,0);
	initSem(&sem_prio,0);
	
	writeIntegerMonitor(0);
time(&init);	

while(!start)
{
	start = s_conf.sim_begin;
}
time(&init);
employee_create();
employee_stock_create();

while(start==1)
{

if(flag==1)
{
for(int i=0; i<s_conf.nr_total_clients;i++)
{	
	int a=0;
	sleep(1);
	client_create();
	sleep(1);
	a=create_employee();
	closeM(&mutex_employeenow);
	nr_employee_needed=a;
	closeM(&mutex_com);
	writeIntegerMonitor(8);
	writeIntegerMonitor(nr_employee_now);
	openM(&mutex_com);
	if(nr_employee_now<nr_employee_needed)
	{
		nr_employee_now++;
		closeM(&mutex_com);
		writeIntegerMonitor(8);
		writeIntegerMonitor(nr_employee_now);
		openM(&mutex_com);
		openM(&mutex_employeenow);
		employee_create();
	}
	else
	{
		openM(&mutex_employeenow);
	}
}
flag=0;
}	
}

	time(&end);
	simTime=difftime(end, init);
	min=(int)simTime/60;
	sec=(int)simTime%60;
	printf("\n\nFim de simulação\n\n");
	printf("\n\nSimulação demorou %i min e %i sec\n\n", min,sec);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n\nFim de simulação\n\n");
	writeSimInfo(info);
	sprintf(info,"\n\nSimulação demorou %i min e %i sec\n\n", min,sec);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	return 0;
}

/*---------------------------------------funçoes auxiliares-----------------------------------------------------------*/
void *client_data()
{
	client_struct client;
	closeM(&mutex_id);
	client.client_num=id_client;
	openM(&mutex_id);
	int mC=0;
  	int sC=0;
	float prob=s_conf.priority_prob;
	prob/=100;
	
	float p = s_conf.withdrawal_prob;
	p/=100;
	
	client.mode=randProb(p);
        client.priority=randProb(prob); 
        client.wait_time=0;	
        client.prod_buy=rand()%4+1;
	int wait_time=rand()%5+1;	
	
//probabilidade de o cliente ser prioritário
	if(client.priority==1)
{
	atTime=0;
	time(&at_start);
	closeM(&mutex_time);
	time(&end);
	simTime=difftime(end, init);
	min=(int)simTime/60;
	sec=(int)simTime%60;
	mC = min;
	sC=	sec;
	printf("(%i:%i) ", min,sec);
	openM(&mutex_time);
	printf("Cliente prioritário numero %i chegou á loja\n", client.client_num);
	closeM(&mutex_print_sim);	
	sprintf(info,"(%i:%i) Cliente prioritário numero %i chegou á loja\n",mC,sC ,client.client_num);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	closeM(&mutex_nr_cl);
	num_client[1]++;
	nr_cl_prio++;
	openM(&mutex_nr_cl);
	closeM(&mutex_com);
	writeIntegerMonitor(2); //diz que tem cliente prioritario
	writeIntegerMonitor(nr_cl_prio);
	openM(&mutex_com);
	client_give_up(client.mode,client.prod_buy, client.priority, client.client_num);
	closeM(&mutex_time);
	time(&at_end);
	atTime_aux=difftime(at_end,at_start);
	atTime_aux2+=(int)atTime_aux;
	closeM(&mutex_withdrawal);
	int a=withdrawal_nr;
	openM(&mutex_withdrawal);
	closeM(&mutex_nr_cl);
	atTime=atTime_aux2/(client_served+a);
	openM(&mutex_nr_cl);	
	closeM(&mutex_com);
	writeIntegerMonitor(9); 
	writeIntegerMonitor(atTime);
	openM(&mutex_com);
	openM(&mutex_time);
	
	
}
	

else //caso nao seja prioritario
{
	atTime=0;
	time(&at_start);
	closeM(&mutex_time);
	time(&end);
	simTime=difftime(end, init);
	min=(int)simTime/60;
	sec=(int)simTime%60;
	mC = min;
	sC=	sec;
	printf("(%i:%i) ", min,sec);
	openM(&mutex_time);
	printf("Cliente numero %i chegou á loja\n", client.client_num);
	closeM(&mutex_print_sim);	
	sprintf(info,"(%i:%i) Cliente numero %i chegou á loja\n",mC,sC ,client.client_num);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	closeM(&mutex_nr_cl);
	num_client[0]++;
	nr_cl_nprio++;
	openM(&mutex_nr_cl);
	closeM(&mutex_com);
	writeIntegerMonitor(3); //diz que tem cliente não prioritario
	writeIntegerMonitor(nr_cl_nprio);
	openM(&mutex_com);
	client_give_up(client.mode,client.prod_buy, client.priority, client.client_num);
	closeM(&mutex_time);
	time(&at_end);
	atTime_aux=difftime(at_end,at_start);
	atTime_aux2+=(int)atTime_aux;
	closeM(&mutex_withdrawal);
	int a=withdrawal_nr;
	openM(&mutex_withdrawal);	
	closeM(&mutex_nr_cl);
	atTime=atTime_aux2/(client_served+a);
	openM(&mutex_nr_cl);
	closeM(&mutex_com);
	writeIntegerMonitor(9); 
	writeIntegerMonitor(atTime);
	openM(&mutex_com);
	openM(&mutex_time);
	
}
}
//funçao que imprime o produto escolhido
int prodChosen(int p, int c)
{

int mC = 0;
int sC = 0;

int i =0;
	switch(p)
{
		case 1:
			closeM(&mutex_stock);
			if(array_flag_stock[0]==1)
			{
			if(array_sell_prod[0]>0)
			{
			sleep(s_conf.service_time_prodA);
			array_sell_prod[0]--;
			//openM(&mutex_stock);
			i=1;
			closeM(&mutex_time);
			time(&end);
			simTime=difftime(end, init);
			min=(int)simTime/60;
			sec=(int)simTime%60;
			mC = min;
			sC=	sec;
			printf("(%i:%i) ", min,sec);
			openM(&mutex_time);
			printf("Cliente numero %i escolheu o produto A\n",c);
			closeM(&mutex_print_sim);	
			sprintf(info,"(%i:%i) Cliente numero %i escolheu o produto A\n",mC, sC, c);
			writeSimInfo(info);
			openM(&mutex_print_sim);
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(1);//seleciona prod A
			writeIntegerMonitor(array_sell_prod[0]);
			openM(&mutex_com);		
			openM(&mutex_stock);
			}
			else
			{
				array_flag_stock[0]=0;
				openM(&mutex_stock);
				closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
				printf("Cliente numero %i tentou escolher o produto A mas não havia stock\n",c);
				printf("\n\nStock do produto A acabou\n\n");
				closeM(&mutex_print_sim);	
				sprintf(info,"(%i:%i) Cliente numero %i tentou escolher o produto A mas não havia stock\n",mC,sC,c);
				writeSimInfo(info);
				sprintf(info,"\n\n(%i:%i) Stock do produto A acabou\n\n",mC,sC);
				writeSimInfo(info);
				openM(&mutex_print_sim);
				i = 0;
			}
			}
			else
			{
				openM(&mutex_stock);
				i=0;
			}
			break;
		case 2:
			closeM(&mutex_stock);
			if(array_flag_stock[1]==1)
			{
			if(array_sell_prod[1]>0)
			{
			sleep(s_conf.service_time_prodB);
			array_sell_prod[1]--;
			//openM(&mutex_stock);
			i=1;
			closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
			printf("Cliente numero %i escolheu o produto B\n",c);
			closeM(&mutex_print_sim);	
			sprintf(info,"(%i:%i) Cliente numero %i escolheu o produto B\n",mC,sC,c);
			writeSimInfo(info);
			openM(&mutex_print_sim);			
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(2);//seleciona prod B
			writeIntegerMonitor(array_sell_prod[1]);
			openM(&mutex_com);
			openM(&mutex_stock);
			
			}
			else
			{
				array_flag_stock[1]=0;
				openM(&mutex_stock);
				closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
				printf("Cliente numero %i tentou escolher o produto B mas não havia stock\n",c);
				printf("\n\nStock do produto B acabou\n\n");
				closeM(&mutex_print_sim);	
				sprintf(info,"(%i:%i) Cliente numero %i tentou escolher o produto B mas não havia stock\n",mC,sC,c);
				writeSimInfo(info);
				sprintf(info,"\n\n(%i:%i) Stock do produto B acabou\n\n",mC,sC);
				writeSimInfo(info);
				openM(&mutex_print_sim);
				i = 0;
			}
			}
			else
			{
				openM(&mutex_stock);
				i=0;
			}
			break;
		case 3:
			closeM(&mutex_stock);
			if(array_flag_stock[2]==1)
			{
			if(array_sell_prod[2]>0)
			{	
			sleep(s_conf.service_time_prodC);
			array_sell_prod[2]--;
			//openM(&mutex_stock);
			i=1;
			closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
			printf("Cliente numero %i escolheu o produto C\n",c);
			closeM(&mutex_print_sim);	
			sprintf(info,"(%i:%i) Cliente numero %i escolheu o produto C\n",mC,sC,c);
			writeSimInfo(info);
			openM(&mutex_print_sim);
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(3);//seleciona prod C
			writeIntegerMonitor(array_sell_prod[2]);
			openM(&mutex_com);
			openM(&mutex_stock);
			}
			else
			{
				array_flag_stock[2]=0;
				openM(&mutex_stock);
				closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
				printf("Cliente numero %i tentou escolher o produto C mas não havia stock\n",c);
				printf("\n\nStock do produto C acabou\n\n");
				closeM(&mutex_print_sim);	
				sprintf(info,"(%i:%i) Cliente numero %i tentou escolher o produto C mas não havia stock\n",mC,sC,c);
				writeSimInfo(info);
				sprintf(info,"\n\n(%i:%i) Stock do produto C acabou\n\n",mC,sC);
				writeSimInfo(info);
				openM(&mutex_print_sim);
				i = 0;
			}
			}
			else
			{
				openM(&mutex_stock);
				i=0;
			}
			break;
		case 4:
			sleep(s_conf.service_time_prodD);
				closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				printf("(%i:%i) ", min,sec);
				openM(&mutex_time);
			printf("Cliente numero %i escolheu o produto D\n",c);
			closeM(&mutex_print_sim);	
			sprintf(info,"(%i:%i) Cliente numero %i escolheu o produto D\n",mC,sC,c);
			writeSimInfo(info);
			openM(&mutex_print_sim);			
			i=1;
			break;

}
return i;
}

//função que verifica que se o cliente desistiu
void client_give_up(int mode,int prod, int prio, int c)
{
	int mC=0;
	int sC=0;
	int i=0;
	if(mode==0)	
	{	
	while(!i)
	{
	prod=rand()%4+1;
	i=prodChosen(prod,c);
	}
	if(prio==1)
	{
	wait(&sem_prio);
	closeM(&mutex_id);
	nr_client_now--;
	update_client_shop(nr_client_now);
	openM(&mutex_id);
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Cliente %i prioritario atendido!\n\n",mC,sC, c);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Cliente %i prioritario atendido!\n\n",mC,sC, c);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	}
	else
	{
	wait(&semaf_client);
	closeM(&mutex_id);
	nr_client_now--;
	update_client_shop(nr_client_now);	
	openM(&mutex_id);
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Cliente %i nao prioritario atendido!\n\n",mC,sC, c);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Cliente %i nao prioritario atendido!\n\n",mC,sC, c);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	}
	closeM(&mutex_nr_cl);
	client_served++;
	closeM(&mutex_com);
	writeIntegerMonitor(7);
	writeIntegerMonitor(client_served);
	openM(&mutex_com);
	openM(&mutex_nr_cl);
}
	else //se cliente desistiu
{
	closeM(&mutex_withdrawal);
	withdrawal_nr++;
	openM(&mutex_withdrawal);
	closeM(&mutex_com);
	writeIntegerMonitor(5);
	writeIntegerMonitor(withdrawal_nr);
	openM(&mutex_com);
	closeM(&mutex_id);
	nr_client_now--;
	update_client_shop(nr_client_now);
	openM(&mutex_id);	
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Cliente %i desistiu!\n\n",mC,sC, c);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Cliente %i desistiu!\n\n",mC,sC, c);
	writeSimInfo(info);
	openM(&mutex_print_sim);
}
}

//função criação de um novo cliente
void client_create()
{
	
	closeM(&mutex_id);
	id_client++;
	nr_client_now++;
	update_client_shop(nr_client_now);
	openM(&mutex_id);

	pthread_t client;
	pthread_create(&client,NULL,client_data,(void*) NULL);
	//pthread_join(client,NULL);		
}


//escreve mensagem na socket para ser lida pelo monitor
void writeMonitor(char message[])
{
    write(sim_socket, message, BUFFER_SIZE);
}
//transforma int em string para escrever na socket
void writeIntegerMonitor(int n)
{
    char message[BUFFER_SIZE];
    sprintf(message,"%i", n);
    writeMonitor(message);
}

int randProb(float p)
{
int i=0;
	float random_number = rand() % 100 +1;
	random_number /=100;
	if(random_number<p)
	{
		i=1;
	}
	else
	{
		i=0;
	}
	return i;
}

void *employee_data()
{
	
	while(1)
	{
	closeM(&mutex_employeenow);	
	if(nr_employee_now>nr_employee_needed)
	{
		nr_employee_now--;
		openM(&mutex_employeenow);
		pthread_cancel(pthread_self());
		
	}
	else
	{
		openM(&mutex_employeenow);
	}
	sleep(1);	
	closeM(&mutex_nr_cl);
	if(num_client[1]>0)//clientes prioritarios
{
	sleep(3);
	num_client[1]--;
	openM(&mutex_nr_cl);
	post(&sem_prio);
}
else
{
	openM(&mutex_nr_cl);

closeM(&mutex_nr_cl);
if(num_client[0]>0&&num_client[1]==0)//se for cliente nao prioritario
{
	sleep(2);
	num_client[0]--;
	openM(&mutex_nr_cl);
	post(&semaf_client);
}
else
{
	openM(&mutex_nr_cl);
}

}
	closeM(&mutex_withdrawal);
	int a=withdrawal_nr;
	openM(&mutex_withdrawal);

	closeM(&mutex_nr_cl);
	if(client_served+a==s_conf.nr_total_clients)
	{
		openM(&mutex_nr_cl);
		closeM(&mutex_com);
		writeIntegerMonitor(1); //manda sinal que acabou a simulação
		openM(&mutex_com);
		start=0;
	}
	else
	{
		openM(&mutex_nr_cl);
	}

}



}
void employee_create()
{
	int mC=0;
	int sC=0;
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	closeM(&mutex_employeenow);	
	printf("\n(%i:%i) Caixa Número %i Disponivel\n",mC,sC, nr_employee_now);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Caixa Número %i Disponivel\n",mC,sC, nr_employee_now);
	writeSimInfo(info);
	openM(&mutex_print_sim);
	openM(&mutex_employeenow);
	pthread_t employee;
	pthread_create(&employee,NULL,employee_data,(void*) NULL);
	//pthread_join(teste,NULL);		
}

void employee_stock_create()
{
	pthread_t employee_stock_r;
	pthread_create(&employee_stock_r,NULL,employee_stock,(void*) NULL);
}

void *employee_stock()
{
	int mC=0;
	int sC=0;
	while(1)
	{
	//sleep(1);
	closeM(&mutex_stock);
	if(array_sell_prod[0]<7&&array_stock_prod[0]>0)
		{
			sleep(1);
			array_sell_prod[0]+=10;
			array_stock_prod[0]-=10;	
	//openM(&mutex_stock);
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(1);//seleciona prod A
			writeIntegerMonitor(array_sell_prod[0]);
			openM(&mutex_com);
	openM(&mutex_stock);
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Foi reposto o produto A com 10 unidades\n\n",mC,sC);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Foi reposto o produto A com 10 unidades\n\n",mC,sC);
	writeSimInfo(info);
	openM(&mutex_print_sim);
		}
	else
	{
		openM(&mutex_stock);
	}

	closeM(&mutex_stock);
	if(array_sell_prod[1]<7&&array_stock_prod[1]>0)
		{
			sleep(1);
			array_sell_prod[1]+=10;
			array_stock_prod[1]-=10;
	//openM(&mutex_stock);
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(2);//seleciona prod B
			writeIntegerMonitor(array_sell_prod[1]);
			openM(&mutex_com);
	openM(&mutex_stock);
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Foi reposto o produto B com 10 unidades\n\n",mC,sC);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Foi reposto o produto B com 10 unidades\n\n",mC,sC);
	writeSimInfo(info);
	openM(&mutex_print_sim);
		}
	else
	{
		openM(&mutex_stock);
	}

	closeM(&mutex_stock);
	if(array_sell_prod[2]<7&&array_stock_prod[2]>0)
		{
			sleep(1);
			array_sell_prod[2]+=10;
			array_stock_prod[2]-=10;
			//openM(&mutex_stock);
			closeM(&mutex_com);
			writeIntegerMonitor(4); // atulizar stock prod
			writeIntegerMonitor(3);//seleciona prod C
			writeIntegerMonitor(array_sell_prod[2]);
			openM(&mutex_com);
			openM(&mutex_stock);
	closeM(&mutex_time);
				time(&end);
				simTime=difftime(end, init);
				min=(int)simTime/60;
				sec=(int)simTime%60;
				mC = min;
				sC=	sec;
				openM(&mutex_time);
	printf("\n(%i:%i) Foi reposto o produto C com 10 unidades\n\n",mC,sC);
	closeM(&mutex_print_sim);	
	sprintf(info,"\n(%i:%i) Foi reposto o produto C com 10 unidades\n\n",mC,sC);
	writeSimInfo(info);
	openM(&mutex_print_sim);
		}
	else
	{
		openM(&mutex_stock);
	}
	}
}

int create_employee()
{
	int a=0;
	closeM(&mutex_employeenow);	
	a=nr_client_now/10;
	rest=nr_client_now%10;
	openM(&mutex_employeenow);
	if (rest!=0)
	{
		return a+1;
	}
	else
	{
		return a;
	}
}

//funçao que comunica ao monitor o numero de clientes na loja 
void update_client_shop(int nr_client)
{
	closeM(&mutex_com);
	writeIntegerMonitor(6);
	writeIntegerMonitor(nr_client);
	openM(&mutex_com);
}

//função responsavel por escrever as informações do simulador num ficheiro 
void writeSimInfo(char info[])
{
	FILE *sim_info = fopen("Sim_info.txt","a");
	fprintf(sim_info,"%s\n",info);
	fclose(sim_info);
}
