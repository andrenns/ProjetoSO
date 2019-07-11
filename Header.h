/*------------------------------------Bibliotecas---------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <math.h>
/*--------------------------------constantes para as sockets----------------------------------------------------------*/
#define UNIXSTR_PATH "/tmp/s.unixstr"
#define UNIXDG_PATH "/tmp/s.unixdgx"
#define UNIXDG_TMP "/tmp/dgXXXXXXX"

/*-----------------------------------constantes globais---------------------------------------------------------------*/
#define STATS_FILE "stats.txt"
#define SIMULATOR_FILE "Simulator.txt"
#define READ_ERROR "Erro na leitura do ficheiro "
#define STRING_FORM "%s"
#define READ_MODE "r+"
#define WRITE_MODE "w+"
#define BUFFER_SIZE 255

/*----------------------------------------Renomeaçoes-----------------------------------------------------------------*/
typedef pthread_mutex_t mutex; //trinco
typedef struct sockaddr_un sockaddr_un;
typedef struct sockaddr sockaddr;



/*------------------------------funçoes para escrever no ficheiro e para escrever no ecra-----------------------------*/
void * printOnScreen(void * buff);
void * readWriteFile();

/*--------------------------------------estrutura config--------------------------------------------------------------*/
typedef struct sim_config
{
    int sim_begin;
    int sim_time;
    int nr_total_clients;
    int nr_prod;
    int stock_prod;
	int stock_shop;
    int service_time_prodA;
    int service_time_prodB;
    int service_time_prodC;
    int service_time_prodD;
    int withdrawal_prob;
    int priority_prob;
} sim_config;
static sim_config s_conf;

/*--------------------------------------estrutura cliente-------------------------------------------------------------*/
typedef struct client_struct
{
    int client_num; //para diferenciar os clientes
    int priority; //1 tem prioridade e 0 nao tem prioridade
    int mode; //0 se não desistiu, 1 se desistiu
    int wait_time;
    int prod_buy; //1 se for A, 2 se for B, 3 se for C e 4 se for D
} client_struct;

/*--------------------------------------estrutura empregado------------------------------------------------------------*/
typedef struct emp_struct
{
    int emp_num; //para diferenciar os empregados
    int type; // 0 se for empregado normal, 1 se for empregado da fila prioritaria
    int num_client_prio_served; //nnumero de clientes com prioridade atendidos pelo empregado
} emp_struct;


/*--------------------------------------funçoes util------------------------------------------------------------------*/
void checkSocketError(int state);
void readConfFile(sim_config *s_conf);

/*------------------------------------------sincronização-------------------------------------------------------------*/
//semaforo
void initSem(sem_t * sem, int v);
void wait(sem_t * sem);
void post(sem_t * sem);
void destroySem(sem_t * sem);
//trinco mutex
void initMutex(mutex * m);
void closeM(mutex * m);
void openM(mutex * m);
void destroyMutex(mutex * m);

/*------------------------------------------------comunicação---------------------------------------------------------*/
int createSocket();
sockaddr_un createSocketCon();
int createSockectSimulator();
int waitForSimConnection();

/*--------------------------------------simulador---------------------------------------------------------------------*/
void writeMonitor(char message[]);
void writeIntegerMonitor(int n);
int randProb(float p);
void *client_data();
void client_create();
void employee_create();
void *employee_data();
int prodChosen(int p, int c);
void *employee_stock();
void employee_stock_create();
int create_employee();
void client_give_up(int mode,int prod, int prio, int c);
void update_client_shop(int nr_client);
void writeSimInfo(char info[]);
/*----------------------------------------monitor---------------------------------------------------------------------*/
char* readFromSimulator();
int readIntegerFromSimulator();
void writeStatsOnScreen();
void writeStatsFile();

/*------------------------------------var globais---------------------------------------------------------------------*/
int num_client[2]; //posição [0] é clientes não prioritarios e a [1] é para prioritários;
int num_employees;
int num_prod_sell;
int array_sell_prod[3];
int array_stock_prod[3];
int array_flag_stock[3];
float avg_time;
int id_client;
int nr_cl_prio;
int nr_cl_nprio;
int start;
int client_served;
int withdrawal_nr;


