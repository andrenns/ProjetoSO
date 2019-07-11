#include "Header.h"

/*---------------------------------------------sincronização----------------------------------------------------------*/
//funções para uso dos semaforos
void initSem(sem_t * sem, int v)
{
    sem_init(sem,0,v);
}

void wait(sem_t * sem)
{
    sem_wait(sem);
}

void post(sem_t * sem)
{
    sem_post(sem);
}

void destroySem(sem_t * sem)
{
    sem_destroy(sem);
}

//funçoes para o uso dos trincos(mutex)

void initMutex(mutex * m)
{
    pthread_mutex_init(m, NULL);
}

void closeM(mutex * m)
{
    pthread_mutex_lock(m);
}

void openM(mutex * m)
{
    pthread_mutex_unlock(m);
}

void destroyMutex(mutex * m)
{
    pthread_mutex_destroy(m);
}

/*---------------------------------------------comunicação------------------------------------------------------------*/
/*--------------------------------------Verifica erro na criação da socket--------------------------------------------*/
void checkSocketError(int state)
{
    //caso dê erro
    if(state == -1)
    {
        printf("Erro associado às Socket!");
        //espera pelo enter
        getchar();
        //acaba o programa
        exit(-1);
    }
}

int createSocket()
{
    int socket_descriptor = socket(AF_UNIX,SOCK_STREAM,0); //retorna o file descriptor da socket criada
    checkSocketError(socket_descriptor); //verifica se deu erro na criação da socket
    return socket_descriptor;
}

sockaddr_un createSocketCon()
{
    sockaddr_un serv_addr;
    //limpeza preventiva
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //Dados para o socket stream: tipo + nome que identifica o servidor
    serv_addr.sun_family=AF_UNIX;
    strcpy(serv_addr.sun_path, UNIXSTR_PATH);
    return serv_addr;
}

/*------------------------------------------Simulador-----------------------------------------------------------------*/
int createSockectSimulator()
{
    int s_simulator_descriptor = createSocket(); //cria socket
    sockaddr_un simulator_addr = createSocketCon(); //estrtutura do endereço do simulador

    int connection_state = connect(s_simulator_descriptor, (sockaddr*) &simulator_addr, sizeof(sockaddr_un)); //tentativa de conexão
    checkSocketError(connection_state); //verifica se ocorreu um erro

    return s_simulator_descriptor;
}

/*--------------------------------------------Monitor-----------------------------------------------------------------*/
int waitForSimConnection()
{
    int s_monitor_descriptor = createSocket(); //cria socket
    sockaddr_un monitor_addr = createSocketCon(); //estrutura do endereço do monitor
    unlink(UNIXSTR_PATH); //apaga o ficheiro partilhado

    int bind_state = bind(s_monitor_descriptor, (sockaddr*) &monitor_addr, sizeof(sockaddr_un)); //atribui endereço á socket
    checkSocketError(bind_state); //verficia se existiu erro

    int listen_state = listen(s_monitor_descriptor,1); //espera pela ligação com 1 cliente, neste caso o simulador
    checkSocketError(listen_state);

    sockaddr_un sim_addr; //estrutura do endereço do cliente, neste caso o simulador
    int sim_len = sizeof(sim_addr);
    int sim = accept(s_monitor_descriptor, (sockaddr*) &sim_addr, &sim_len); //aceita a conexao com o cliente, neste caso o simulador
    checkSocketError(sim);

    return sim;

}


void readConfFile(sim_config *s_conf)
{
    FILE * configFile = fopen(SIMULATOR_FILE,READ_MODE);
    int values[12];
    char line_data[BUFFER_SIZE];
    char value[BUFFER_SIZE];

    //apenas é feito pois a cima jja percorreu o documento todo
    configFile = fopen(SIMULATOR_FILE,READ_MODE);
    int inc_array=0;

    while(fgets(line_data,BUFFER_SIZE,configFile))
    {
        //Limpa o line_data, esta é feita por precaução
        bzero(value,sizeof(value));

        int i =0;
        //Percorre até encontrar igual
        for(i=0; line_data[i] != '=' ;i++);
        //Retira o valor

        strncpy(value,line_data+i+1,strlen(line_data)-i-1);


        values[inc_array]=atoi(value);
        inc_array++;
    }

    s_conf->sim_begin = values[0];
    s_conf->sim_time = values[1];
    s_conf->nr_total_clients = values[2];
    s_conf->nr_prod = values[3];
    s_conf->stock_prod = values[4];
	s_conf->stock_shop = values[5];
    s_conf->service_time_prodA = values[6];
    s_conf->service_time_prodB = values[7];
    s_conf->service_time_prodC = values[8];
    s_conf->service_time_prodD = values[9];
    s_conf->withdrawal_prob = values[10];
    s_conf->priority_prob = values[11];

}
