#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int p2c[2];//父写子读
    int c2p[2];//child to parent
    char buf;//storage for ping pong
    pipe(p2c);
    pipe(c2p);

    int pid = fork();

    if(pid==0){
        close(p2c[1]);//child doesn't write to parent
        close(c2p[0]);//child doesn't write to parent
        read(p2c[0],&buf,1);//read from parent's ping
        printf("%d: received ping\n", getpid());
        write(c2p[1],"pong",4);//send pong to parent
        close(p2c[0]);
        close(c2p[1]);
        exit(0);
    }else{
        close(p2c[0]);//parent doesn't read from child
        close(c2p[1]);//parent doesn't write to child
        write(p2c[1],"ping",4);//send ping to child
        read(c2p[0],&buf,1);//read pong from child
        printf("%d: received pong\n", getpid());
        close(p2c[1]);
        close(c2p[0]);
        wait(0);
    }
    exit(0);
}