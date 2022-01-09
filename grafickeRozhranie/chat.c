#include <glib.h>
#include "commonPointers.c"
#include <string.h>
GtkTextIter iter;
GtkTextMark *mark;



typedef struct msg {
    char text[256];
    int socketfd;
}MSG;

MSG msg1;
MSG msg2;
pthread_t communication;
pthread_cond_t pokracuj;
pthread_mutex_t mutex;


void *mWrite(void *d){
    MSG *msg = d;
    int n;
    char buffer[256];

    while(1){

        bzero(buffer,256);
        //fgets(buffer, 255, stdin);


        if(strlen(msg1.text) == 0) {
            pthread_cond_wait(&pokracuj, &mutex);
            continue;
        } else {
            strcpy(buffer, msg->text);
            printf("text: %s", msg->text);
            bzero(msg1.text, 256);
        }
        printf("\n");
        printf("vypis obsahu buffera z write thready: %s",buffer);
        printf("pocet znakov(aj s koncovym bielim znakom): %d\n",(int)strlen(buffer));

        char *dup = strdup(buffer);
        char* command;
        command = strtok(dup, " ");
        if(!strcmp(command, "msgC")){
            printf("je to msgC\n");
            char* komu;
            char text[201];

            komu = strtok(NULL, " ");
            printf("komu: %s\n",komu);

            char * token = strtok(NULL, " ");
            printf("token: %s\n", token);
            bzero(text,201);

            while(token != NULL){
                strcat(text, token);
                strcat(text, " ");
                token = strtok(NULL, " ");

                printf("token: %s\n", token);
            }
            text[strlen(text)-1] = 0;
            printf("text: %s\n", text);
            printf("text dlzka(aj s novym riadkom nakonci): %d\n", (int)strlen(text));

            //cezar
            for(int i=0; i < strlen(text)-1; i++) {
                text[i] += 1;
            }
            //shift podla pozicie
            int shift;
            for(int i=0; i < strlen(text)-1; i++) {
                shift = i % 4;
                text[i] += shift;
            }
            //vymen znaky vedla seba

            if((strlen(text)-1) % 2 == 0){
                for(int i=0; i<strlen(text)-1; i+=2){
                    char c = text[i];
                    text[i] = text[i+1];
                    text[i+1] = c;
                }
            }else{
                for(int i=0; i<strlen(text)-2; i+=2){
                    char c = text[i];
                    text[i] = text[i+1];
                    text[i+1] = c;
                }
            }


            char crypted[300];
            bzero(crypted,300);
            strcat(crypted, command);
            strcat(crypted, " ");
            strcat(crypted, komu);
            strcat(crypted, " ");
            strcat(crypted, text);
            printf("original: %s", buffer);
            printf("    copy: %s\n", crypted);

            n = (int)write(msg->socketfd, crypted, strlen(crypted)+1);
            if (n < 0) {
                perror("Error writing to socket");
                exit(5);
            }
        }else{
            n = (int)write(msg->socketfd, buffer, strlen(buffer)+1);
            if (n < 0) {
                perror("Error writing to socket");
                exit(5);
            }
            if(!strcmp(buffer, "quit\n")){
                break;
            }

        }
        free(dup);
    }
}

void *mRead(void* d){
    int *sockfd = (int*)d;
    //const gchar *textInsert;
    //textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));


    int n;
    char buffer[256];

    while(1){
        bzero(buffer,256);
        n = (int)read(*sockfd, buffer, 255);
        strcpy(msg2.text, buffer);

        chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));

        printf("received!\n");
        mark = gtk_text_buffer_get_insert (chatTextBuffer);
        gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
//        if (strlen(buffer) > 0) {
//            printf("Nice.");
            //gtk_text_buffer_insert (chatTextBuffer, &iter, tempName, 1);

//        } else {
//            printf("Not nice.");
//            continue;
//        }

        gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);
        //gtk_entry_set_text(GTK_ENTRY(gtkSendText), ""); maze obsah rozpisanej spravy

        if (n < 0) {
            perror("Error reading from socket");
            exit(6);
        }

        if(!strcmp(buffer, "terminujem ta")){

            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, buffer, -1);
            break;
        }

        printf("sprava ktora prisla: %s\n",buffer);

        char* command;
        command = strtok(buffer, " ");
        printf("command: %s\n", command);
        if(!strcmp(command, "s")){
            printf("dekodovanie: \n");

            char* odkial;
            char text[201];
            bzero(text,201);
            odkial = strtok(NULL, " ");
            printf("odkial %s\n", odkial);

            char * token = strtok(NULL, " ");
            printf("token: %s\n",token);

            while(token != NULL){
                strcat(text, token);
                strcat(text, " ");
                token = strtok(NULL, " ");
            }
            text[strlen(text)-1] = 0;

            if((strlen(text)-1) % 2 == 0){
                for(int i=0; i<strlen(text)-1; i+=2){
                    char c = text[i];
                    text[i] = text[i+1];
                    text[i+1] = c;
                }
            }else{
                for(int i=0; i<strlen(text)-2; i+=2){
                    char c = text[i];
                    text[i] = text[i+1];
                    text[i+1] = c;
                }
            }
            int shift;
            for(int i=0; i < strlen(text)-1; i++) {
                shift = i % 4;
                text[i] -= shift;
            }
            for(int i=0; i < strlen(text)-1; i++){
                text[i] -= 1;
            }

            char decrypted[300];
            bzero(decrypted,300);
//            strcat(decrypted, command);

//            strcat(decrypted, " ");
            strcat(decrypted, odkial);
            strcat(decrypted, " ");
//            printf("text: %s\n",text);
            strcat(decrypted, text);
//            printf("%s\n", decrypted);

            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, decrypted, -1);
            continue;
        }else if (!strcmp(command, "n")){
            printf("nesifrovana sprava:\n");

            char* odkial;
            char text[201];
            odkial = strtok(NULL, " ");
            char * token = strtok(NULL, " ");
            bzero(text,201);


            while(token != NULL){
                strcat(text, token);
                strcat(text, " ");
                token = strtok(NULL, " ");
            }
            text[strlen(text)-1] = 0;
            char final[300];
            bzero(final, 300);
            strcat(final,odkial);
            strcat(final," ");
            strcat(final,text);
//            printf("%s\n", final);

            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, final, -1);
            continue;
        }else if(!strcmp(command, "show")){

            char text[300];
            char * token = strtok(NULL, " ");
            bzero(text,300);
            strcat(text, "online su: ");
            while(token != NULL){
                strcat(text, token);
                strcat(text, " ");
                token = strtok(NULL, " ");
            }
            text[strlen(text)-1] = 0;
//            printf("online su: %s\n", text);
            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, text, -1);
            continue;
        }
        else if(!strcmp(command, "friendRequest")){
            char newfriend[60];
            char* temp = "";
            bzero(newfriend, 60);

            temp = strtok(NULL, " ");
            strcat(newfriend, temp);
            strcat(newfriend,  " si ta chce pridat ako priatela!");

            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, newfriend, -1);
//            printf("%s si ta chce pridat ako priatela!\n",newfriend);
            continue;
        } else if(!strcmp(command, "noFriendsForYou")){
            char newfriend[60];
            char* temp = "";
            bzero(newfriend, 60);

            temp = strtok(NULL, " ");
            strcat(newfriend, temp);
            strcat(newfriend,  "  tvoj friend request odmietol!");

            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, newfriend, -1);

            //printf("%s tvoj friend request odmietol!\n", strtok(NULL, " "));
            continue;
        }

        gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
        gtk_text_buffer_insert (chatTextBuffer, &iter, buffer, -1);
    }
}




void* start(void * d){
    printf("Zapol som sa\n");
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];


    server = gethostbyname("localhost");

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );

    int portt = 26100;
    serv_addr.sin_port = htons(portt);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Error creating socket");
        exit (3);
    }
    msg1.socketfd = sockfd;
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        portt++;
        serv_addr.sin_port = htons(portt);
        if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error connecting to socket");
            exit(4);
        }
    }

    pthread_t tRead;
    pthread_t tWrite;

    pthread_create(&tRead, NULL, &mRead, &sockfd);
    pthread_create(&tWrite, NULL, &mWrite, &msg1);

    pthread_join(tRead, NULL);
    pthread_join(tWrite, NULL);

    close(sockfd);
};

void on_buttonQuit_clicked() {
    strcpy(msg1.text, "quit\n");
    pthread_cond_signal(&pokracuj);
    gtk_widget_hide(windowChat);
    gtk_main_quit();


}

void on_gtkViewText_button_press_event() {

}

void on_buttonHistory_clicked () {
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));

    strcpy(msg1.text, "history\n");
    pthread_cond_signal(&pokracuj);

    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);

    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);

}

void on_buttonSendMessage_clicked() {
    const gchar *textInsert;
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));

    //printf("sent!\n");
    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
    if (strlen(textInsert) > 0) {
        //printf("Nice.");
        gtk_text_buffer_insert (chatTextBuffer, &iter, ("\n :"), 1);
        gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);

        char temp[256];
        bzero(temp, 256);
        strcpy(temp, textInsert);
        strcat(temp, "\n");
        strcpy(msg1.text, temp);
        pthread_cond_signal(&pokracuj);

    } else {
        //rintf("Not nice.");
    }
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);
    gtk_entry_set_text(GTK_ENTRY(gtkSendText), "");
}
void chatScreen() {
    builder = gtk_builder_new_from_file("grafickeRozhranie/chat.glade");
    gtk_builder_connect_signals(builder, NULL);

    windowChat = GTK_WIDGET(gtk_builder_get_object(builder, "windowChat"));
    gtkViewText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkViewText"));
    gtkSendText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkSendText"));
    buttonSendMessage = GTK_WIDGET(gtk_builder_get_object(builder, "buttonSendMessage"));
    buttonHistory = GTK_WIDGET(gtk_builder_get_object(builder, "buttonHistory"));
    buttonQuit = GTK_WIDGET(gtk_builder_get_object(builder, "buttonQuit"));


    gtk_text_view_set_editable(GTK_TEXT_VIEW(gtkViewText), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(gtkViewText), FALSE);
    g_signal_connect(windowChat, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(gtkSendText, "activate", G_CALLBACK(on_buttonSendMessage_clicked), NULL);
    g_signal_connect(gtkViewText, "button-press-event", G_CALLBACK(on_gtkViewText_button_press_event), windowChat);
    g_signal_connect(buttonSendMessage, "clicked", G_CALLBACK(on_buttonSendMessage_clicked), windowChat);
    g_signal_connect(buttonHistory, "clicked", G_CALLBACK(on_buttonHistory_clicked), windowChat);
    g_signal_connect(buttonQuit, "clicked", G_CALLBACK(on_buttonQuit_clicked), windowChat);

    gtk_widget_show_all(windowChat);

    gtk_main();

    pthread_join(communication, NULL);
    pthread_cond_destroy(&pokracuj);
    pthread_mutex_destroy(&mutex);
}
