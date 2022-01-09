#include "commonPointers.c"
#include "chat.c"
#include <string.h>



void on_buttonRegister_clicked(GtkButton *button, gpointer user_data) {

    const gchar *username, *password;
    username = gtk_entry_get_text(GTK_ENTRY(usernameEntry));
    password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    const gchar *temp1 = "tibor";
    const gchar *temp2 = "michalov";
    //\printf("\n\n\nusernameA=%s\npassword=%s\n", username, password);
    if (strcmp(username, temp1) == 0 && strcmp(password, temp2) == 0) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Užívateľ už existuje!");
    } else {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Úspešne vytvorený účet!");
    }
}

void on_buttonLogin_clicked(GtkButton *button, gpointer user_data) {

    const gchar *username, *password;
    username = gtk_entry_get_text(GTK_ENTRY(usernameEntry));
    password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    //const gchar *temp1 = "matej";
    //const gchar *temp2 = "hubocan";
    //if (strcmp(username, temp1) == 0 && strcmp(password, temp2) == 0) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Správne zadané údaje!");
        gtk_widget_hide(windowLogin);
        //printf("matej");
        //printf("hubocan");

    char temp[60];
    bzero(temp, 60);

    strcat(temp, "log");
    strcat(temp, " ");
    strcat(temp, username);
    strcat(temp, " ");
    strcat(temp, password);

//        printf("Temp: %s\n", temp);
    strcpy(msg1.text , temp);
    pthread_cond_signal(&pokracuj);
//        printf("Temp: %s\n",msg1.text);


    gtk_main_quit();
    chatScreen();

   // } else if (strcmp(username, temp3) == 0 && strcmp(password, temp4) == 0) {
        //printf("logged in via random new user");
        //gtk_widget_hide(windowLogin);
       // chatScreen(); // TODO DELETE, TESTING
     //           printf("logged in");
   // } *else {
       // gtk_label_set_text(GTK_LABEL(errorMessage), "Nesprávne zadané údaje!");
    //}
    //printf("username=%s\npassword=%s\n",username,password);
}
void loginScreen(){
    builder = gtk_builder_new_from_file("grafickeRozhranie/login.glade");
    gtk_builder_connect_signals(builder, NULL);

    //gtk_builder_add_from_file(builder, "login.glade", NULL);
    printf("hello\n");

    windowLogin = GTK_WIDGET(gtk_builder_get_object(builder, "windowLogin"));

    usernameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameEntry"));
    passwordEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordEntry"));
    errorMessage = GTK_WIDGET(gtk_builder_get_object(builder, "errorMessage"));

    buttonLogin = GTK_WIDGET(gtk_builder_get_object(builder, "buttonLogin"));
    buttonRegister = GTK_WIDGET(gtk_builder_get_object(builder, "buttonRegister"));


    g_signal_connect(windowLogin, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(buttonLogin, "clicked", G_CALLBACK(on_buttonLogin_clicked), windowLogin);
    g_signal_connect(buttonRegister, "clicked", G_CALLBACK(on_buttonRegister_clicked), windowLogin);
    g_signal_connect(usernameEntry, "activate", G_CALLBACK(on_buttonLogin_clicked), NULL);
    g_signal_connect(passwordEntry, "activate", G_CALLBACK(on_buttonLogin_clicked), NULL);

    gtk_widget_show(windowLogin);

    pthread_create(&communication, NULL, start, NULL);
    pthread_cond_init(&pokracuj, NULL);
    pthread_mutex_init(&mutex, NULL);

    gtk_main();

    //return EXIT_SUCCESS;
}
//TODO ZADAJ HESLO ZNOVU
