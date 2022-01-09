#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include "grafickeRozhranie/login.c"

void *generateRozhranie(void *d) {
    loginScreen();
}


int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);

    pthread_t rozhranie;
    pthread_create(&rozhranie, NULL, generateRozhranie, NULL);

    pthread_join(rozhranie, NULL);
    return 0;
}


