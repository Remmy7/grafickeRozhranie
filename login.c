#include "commonPointers.c"
#include "chat.c"


void loginScreen(){
    builder = gtk_builder_new_from_file("login.glade");
    gtk_builder_connect_signals(builder, NULL);

    //gtk_builder_add_from_file(builder, "login.glade", NULL);

    windowLogin = GTK_WIDGET(gtk_builder_get_object(builder, "windowLogin"));

    usernameEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameEntry"));
    passwordEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordEntry"));
    errorMessage = GTK_WIDGET(gtk_builder_get_object(builder, "errorMessage"));

    buttonLogin = GTK_WIDGET(gtk_builder_get_object(builder, "buttonLogin"));
    buttonRegister = GTK_WIDGET(gtk_builder_get_object(builder, "buttonRegister"));

    g_signal_connect(windowLogin, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(windowLogin);
    gtk_main();


    //return EXIT_SUCCESS;
}
//TODO ZADAJ HESLO ZNOVU
G_MODULE_EXPORT void on_buttonRegister_clicked() {
    const gchar *username, *password;
    username = gtk_entry_get_text(GTK_ENTRY(usernameEntry));
    password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    const gchar *temp1 = "tibor";
    const gchar *temp2 = "michalov";
    printf("\n\n\nusernameA=%s\npassword=%s\n", username, password);
    if (strcmp(username, temp1) == 0 && strcmp(password, temp2) == 0) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Užívateľ už existuje!");
    } else {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Úspešne vytvorený účet!");
    }


}

G_MODULE_EXPORT void on_buttonLogin_clicked() {
    const gchar *username, *password;
    username = gtk_entry_get_text(GTK_ENTRY(usernameEntry));
    password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    const gchar *temp1 = "tibor";
    const gchar *temp2 = "michalov";
    if (strcmp(username, temp1) == 0 && strcmp(password, temp2) == 0) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Správne zadané údaje!");
        //printf("logged in via tibor");
        gtk_widget_hide(windowLogin);
        chatScreen();
    }/* else if (strcmp(username, temp3) == 0 && strcmp(password, temp4) == 0) {
        printf("logged in via random new user");
        gtk_widget_hide(windowLogin);
        chatScreen(); // TODO DELETE, TESTING
                printf("logged in");
    } */else {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Nesprávne zadané údaje!");
    }
    printf("username=%s\npassword=%s\n",username,password);
}