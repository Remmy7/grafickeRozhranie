#include <glib.h>
#include "commonPointers.c"
#include <string.h>
GtkTextIter iter;
GtkTextMark *mark, *mark2;
const gchar* tempName = "jano";
const gchar* tempName2 = "tibor";


typedef struct msg {
    char text[256];
    int socketfd;
}MSG;

MSG msg1;
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
            //printf("SOM TU!");
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
            int shift = 0;
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


            char* crypted[300];
            bzero(crypted,300);
            strcat(crypted, command);
            strcat(crypted, " ");
            strcat(crypted, komu);
            strcat(crypted, " ");
            strcat(crypted, text);
            printf("original: %s", buffer);
            printf("    copy: %s\n", crypted);

            n = write(msg->socketfd, crypted, strlen(crypted)+1);
            if (n < 0) {
                perror("Error writing to socket");
                return 5;
            }
        }else{
            n = write(msg->socketfd, buffer, strlen(buffer)+1);
            if (n < 0) {
                perror("Error writing to socket");
                return 5;
            }
            if(!strcmp(buffer, "quit\n")){
                break;
            }

        }
        free(dup);
    }
}

void *mRead(int sockfd){

    //const gchar *textInsert;
    //textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));


    int n;
    char buffer[256];

    while(1){
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);

        chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));

        printf("received!\n");
        mark = gtk_text_buffer_get_insert (chatTextBuffer);
        gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
        if (strlen(buffer) > 0) {
            printf("Nice.");
            gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
            //gtk_text_buffer_insert (chatTextBuffer, &iter, tempName, 1);
            gtk_text_buffer_insert (chatTextBuffer, &iter, buffer, -1);
        } else {
            printf("Not nice.");
        }

        gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);
        gtk_entry_set_text(GTK_ENTRY(gtkSendText), "");

        if (n < 0) {
            perror("Error reading from socket");
            return 6;
        }

        if(!strcmp(buffer, "terminujem ta")){
            //printf("reeeeeeeeeeeeeeeee\n");
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
            int shift = 0;
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
            printf("text: %s\n",text);
            strcat(decrypted, text);
            printf("%s\n", decrypted);

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
            printf("%s\n", final);
        }else if(!strcmp(command, "show")){
            printf("I AM HERE BITCHES!\n");

            char text[300];
            char * token = strtok(NULL, " ");
            bzero(text,300);
            while(token != NULL){
                strcat(text, token);
                strcat(text, " ");
                token = strtok(NULL, " ");
            }
            text[strlen(text)-1] = 0;
            printf("online su: %s\n", text);
        }
        else if(!strcmp(command, "friendRequest")){
            char* newfriend;
            newfriend = strtok(NULL, " ");
            printf("%s si ta chce pridat ako priatela!\n",newfriend);
        } else if(!strcmp(command, "noFriendsForYou")){
            printf("%s tvoj friend request odmietol!\n", strtok(NULL, " "));

        }

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
        return 3;
    }
    msg1.socketfd = sockfd;
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        portt++;
        serv_addr.sin_port = htons(portt);
        if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error connecting to socket");
            return 4;
        }
    }

    pthread_t tRead;
    pthread_t tWrite;

    pthread_create(&tRead, NULL, &mRead, sockfd);
    pthread_create(&tWrite, NULL, &mWrite, &msg1);

    pthread_join(tRead, NULL);
    pthread_join(tWrite, NULL);

    close(sockfd);
};


void on_buttonSendMessage_clicked(GtkButton *button, gpointer user_data) {
    const gchar *textInsert;
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));

    printf("sent!\n");
    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
    if (strlen(textInsert) > 0) {
        printf("Nice.");
        gtk_text_buffer_insert (chatTextBuffer, &iter, ("\n :"), 1);
        gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);
        bzero(msg1.text, 256);
        strcpy(msg1.text, textInsert);
        pthread_cond_signal(&pokracuj);

    } else {
        printf("Not nice.");
    }
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);
    gtk_entry_set_text(GTK_ENTRY(gtkSendText), "");

}

void on_buttonReceiveMessage_clicked(GtkButton *button, gpointer user_data) { // TODO DELETE, JUST FOR TESTING!!!!!

    const gchar *textInsert;
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));
    printf("received!\n");
    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
    if (strlen(textInsert) > 0) {
        printf("Nice.");
        gtk_text_buffer_insert (chatTextBuffer, &iter, "\n: ", 1);
        //gtk_text_buffer_insert (chatTextBuffer, &iter, tempName, 1);
        gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);
    } else {
        printf("Not nice.");
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
    buttonReceiveMessage = GTK_WIDGET(gtk_builder_get_object(builder, "buttonReceiveMessage"));

    gtk_window_set_default_size(GTK_WINDOW(windowChat),600,450);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(gtkViewText), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(gtkViewText), FALSE);
    // TODO pridať emoji
    g_signal_connect(windowChat, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(buttonSendMessage, "clicked", G_CALLBACK(on_buttonSendMessage_clicked), windowChat);
    g_signal_connect(buttonReceiveMessage, "clicked", G_CALLBACK(on_buttonReceiveMessage_clicked), windowChat);
    g_signal_connect(gtkSendText, "activate", G_CALLBACK(on_buttonSendMessage_clicked), NULL);
    gtk_widget_show_all(windowChat);

    gtk_main();

    pthread_join(communication, NULL);
    pthread_cond_destroy(&pokracuj);
    pthread_mutex_destroy(&mutex);
}
