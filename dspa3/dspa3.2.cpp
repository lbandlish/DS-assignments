#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/time.h>
#include<pthread.h>

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

pthread_mutex_t condition_mutex[10000];
pthread_mutex_t count_mutex; 
int c;
// int locked[10000];
float balance[10000];
int statements=0;
int no_of_txn;
typedef struct txn{
    int txn_seq;
    int type;
    float amount;
    int ac1;
    int ac2;
}transaction;

transaction Transactions[10];

void* func(){
    int txn_seq;
    int type;
    float amount;
    int ac1;
    int ac2;

    while(1)
    {
        pthread_mutex_lock(&count_mutex);
        printf("%d ", c + 1);
        if(c >= no_of_txn) break;
        txn_seq=Transactions[c].txn_seq;
        type= Transactions[c].type;
        amount=Transactions[c].amount;
        ac1=Transactions[c].ac1;
        ac2 = Transactions[c].ac2;
        c++;
        pthread_mutex_unlock(&count_mutex);

        pthread_mutex_lock(&condition_mutex[ac1 - 1001]);
        if(type == 1)
        {
            balance[ac1-1001]=balance[ac1-1001]+amount*0.99;
        }
        if(type==2){
            balance[ac1-1001]=balance[ac1-1001]-amount*1.01;
        }

        if(type==3){
            balance[ac1-1001]+=balance[ac1-1001]*0.071;
        }
        if(type == 4)
        {
            pthread_mutex_lock(&condition_mutex[ac2 - 1001]);
            balance[ac1-1001]-=amount*1.01;
            balance[ac2-1001]+=amount*0.99;
            pthread_mutex_unlock(&condition_mutex[ac2 - 1001]);
        }
        pthread_mutex_unlock(&condition_mutex[ac1 - 1001]);
    }
    pthread_exit(NULL); 
}

int main(int argc, char **argv){
    c=0;
    no_of_txn=atoi(argv[3]);
    int Threads=atoi(argv[4]);
    pthread_t threads[Threads];
    struct timeval start, end;
    if(argc!= 5){
        printf("Usage: %s <fileneme>\n,%s {Account_file},%s {Transaction_file},%s {#of Transactions},%s {#of Threads}", argv[0],argv[1],argv[2],argv[3],argv[4]);
        exit(-1);         
    }
    FILE* fd1=fopen(argv[1],"r+");
    int cnt=0;
    while(1){
        int val1;
        float val2;
        int ret=fscanf(fd1,"%d %f",&val1,&val2);
        if(ret==2){
            balance[cnt]=val2;
            cnt++;
        }
        else break;
    }
    fclose(fd1);

    cnt=0;
    fd1=fopen(argv[2],"r+");
    while(1){
        int val1;
        int val2;
        int ac_1;
        int ac_2;
        float val3;
        int ret=fscanf(fd1,"%d %d %f %d %d",&val1,&val2,&val3,&ac_1,&ac_2);
        if(ret==5){
            Transactions[cnt].txn_seq=val1;
            Transactions[cnt].type=val2;
            Transactions[cnt].amount=val3;
            Transactions[cnt].ac1=ac_1;
            Transactions[cnt].ac2=ac_2;
            cnt++;
        }
        else break;
    }
    fclose(fd1);
    for(int i=0;i<10000;i++){
        locked[i]=0;
    }
    gettimeofday(&start, NULL);
    for (int i = 0; i < 10000; i ++)
    {
        pthread_mutex_init(&condition_mutex[i], NULL);
    }
    pthread_mutex_init(&count_mutex, NULL);
    int ctr;
    for(ctr=0; ctr < Threads; ++ctr){
        if(pthread_create(&threads[ctr],NULL,func,NULL) != 0){
            perror("pthread_create");
            exit(-1);
        }
    }

    for(ctr=0; ctr < Threads; ++ctr)
        pthread_join(threads[ctr], NULL);

    for(ctr=0; ctr < 10000; ++ctr)
        printf("%d %.2f\n",ctr+1001,balance[ctr]); 
    gettimeofday(&end, NULL);
    printf("Time taken = %ld microsecs\n", TDIFF(start, end));
    return 0;
}