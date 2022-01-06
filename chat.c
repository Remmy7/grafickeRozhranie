
void chatScreen() {
    builder = gtk_builder_new_from_file("chat.glade");
    gtk_builder_connect_signals(builder, NULL);

    windowChat = GTK_WIDGET(gtk_builder_get_object(builder, "windowChat"));
    gtkViewText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkViewText"));
    gtkSendText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkSendText"));
    buttonSendMessage = GTK_WIDGET(gtk_builder_get_object(builder, "buttonSendMessage"));

    gtk_window_set_default_size(GTK_WINDOW(windowChat),600,450);

    // TODO pridať emoji
    g_signal_connect(windowChat, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(windowChat);
    gtk_main();

}

G_MODULE_EXPORT void on_buttonSendMessage_clicked() {
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkSendText));
    GtkTextIter startp, endp;


    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(chatTextBuffer), &startp, &endp);

    const GtkTextIter startIter = startp, endIter = endp;

    //printf(chatTextBuffer);


}