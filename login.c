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

    const gchar *temp3 = "";
    const gchar *temp4 = "";
    int tempSizeUsername = sizeof(username);
    int tempSizePassword = sizeof(password);
    printf("username=%d\npassword=%d\n", tempSizeUsername, tempSizePassword);
    if (strcmp(username, temp1) == 0 && strcmp(password, temp2) == 0 || strcmp(username, temp3) == 0 && strcmp(password, temp4) == 0) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Užívateľ už existuje!");
    } else if (tempSizePassword < 4 || tempSizeUsername < 4) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Nesprávne zadané meno alebo heslo!");
    }
    else {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Úspešne vytvorený účet!");
        temp3 = username;
        temp4 = password;
        printf("username=%s\npassword=%s\n",temp3,temp4);
    }


}

G_MODULE_EXPORT void on_buttonLogin_clicked() {
    const gchar *username, *password;
    username = gtk_entry_get_text(GTK_ENTRY(usernameEntry));
    password = gtk_entry_get_text(GTK_ENTRY(passwordEntry));
    const gchar *temp1 = "ahoj";
    const gchar *temp2 = "ahoj";
    if (!strcmp(username, temp1) && !strcmp(password, temp2)) {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Správne zadané údaje!");
        gtk_widget_hide(windowLogin);
        chatScreen();
    } else {
        gtk_label_set_text(GTK_LABEL(errorMessage), "Nesprávne zadané údaje!");
    }
    printf("username=%s\npassword=%s\n",username,password);
}

