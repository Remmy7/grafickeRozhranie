
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
    GtkTextIter iter;
    GtkTextIter startp, endp;
    GtkTextMark *mark;
    const gchar *textInsert;

//TODO fix names
    //chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    //textInsert = gtk_text_view_get_buffer(gtkSendText);
    printf("xd!");
    //gtk_text_buffer_get_start_iter(chatTextBuffer, &startp);
    //endp = startp;
    //gtk_text_iter_forward_chars(&endp, 50);

    //gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(chatTextBuffer), &startp, &endp);
    //const GtkTextIter startIter = startp, endIter = endp;
    //gtk_text_buffer_get_text(GTK_TEXT_BUFFER(chatTextBuffer), &startp, &endp, FALSE);
    //mark = gtk_text_buffer_get_insert (chatTextBuffer);
    //gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);

    //gtk_text_buffer_delete(chatTextBuffer, &startp, &endp);


}

G_MODULE_EXPORT void on_buttonReceiveMessage_clicked() { // TODO DELETE, JUST FOR TESTING!!!!!
    GtkTextIter startp, endp;
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkSendText));

    //gtk_text_buffer_get_start_iter(chatTextBuffer, &startp);
    //endp = startp;
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(chatTextBuffer), &startp, &endp);

    gtk_text_buffer_get_text(GTK_TEXT_BUFFER(chatTextBuffer), &startp, &endp, FALSE);
    gtk_text_buffer_delete(chatTextBuffer, &startp, &endp);
}