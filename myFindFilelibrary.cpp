#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
struct arg_struct{

    char* arg1=(char*)"/";
    char* arg2;
    int thread_count;
};
char findfile(const char* dirname, const char* key, int thread_count){
    DIR *dir=opendir(dirname);
    if (dir==NULL){
        return 0;
    }
    struct dirent *entry;
    entry=readdir(dir);
    while(entry!=NULL){
        //printf("Thread%d %hhd %s\n",thread_count,entry->d_type,entry->d_name);
        char path[1024]={ 0 };
        strcat(path, dirname);
        if(strcmp(entry->d_name, key)==0){
            strcat(path, "/");
            strcat(path,key);
            printf("FILE FOUND! %s\n", path);
            for(int i=0;i<8;i++){
            if(i==thread_count){continue;}
            pthread_cancel(threads[i]);
            }
            return 0;
        }
        if(entry->d_type==DT_DIR && strcmp(entry->d_name, ".") !=0 && strcmp(entry->d_name, "..") !=0 ){
            strcat(path, "/");
            strcat(path,entry->d_name);
            char a=findfile(path,key, thread_count);
            if(a==1){
                return 1;
            }
        }
        entry=readdir(dir);
    }
    closedir(dir);
    return 0;
}
void *findfile_multithread(void *arguments){
    struct arg_struct *args = (arg_struct *)arguments;
    findfile(args->arg1, args->arg2, args->thread_count);
    return nullptr;
}
void search(char toFind[]){
    struct arg_struct args;
    args.arg2=toFind;
    pthread_t threads[8];
    for(int i=0;i<8;i++){
        args.thread_count=i;
        pthread_create(&(threads[i]), NULL, &findfile_multithread, (void *)&args);
        printf("Thread %d created\n", i );
        sleep(0.1);
    }
    for(int i=0;i<8;i++){
        pthread_join(threads[i],NULL);
    }
}/*
int main(){
    char str1[16];
    printf("Print the file name to find:");
    scanf("%15s", str1);
    search(str1);
}*/
