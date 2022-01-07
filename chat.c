GtkTextIter iter;
GtkTextMark *mark;

void chatScreen() {
    builder = gtk_builder_new_from_file("chat.glade");
    gtk_builder_connect_signals(builder, NULL);

    windowChat = GTK_WIDGET(gtk_builder_get_object(builder, "windowChat"));
    gtkViewText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkViewText"));
    gtkSendText = GTK_WIDGET(gtk_builder_get_object(builder, "gtkSendText"));
    buttonSendMessage = GTK_WIDGET(gtk_builder_get_object(builder, "buttonSendMessage"));

    gtk_window_set_default_size(GTK_WINDOW(windowChat),600,450);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(gtkViewText), FALSE);
    // TODO pridať emoji
    g_signal_connect(windowChat, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(windowChat);
    gtk_main();




}

G_MODULE_EXPORT void on_buttonSendMessage_clicked() {
    const gchar *textInsert;

//TODO fix names
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));
    printf("sent!\n");
    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
    if (gtk_text_buffer_get_char_count(chatTextBuffer))
        gtk_text_buffer_insert (chatTextBuffer, &iter, "\n", 1);
    gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);

    //gtk_text_buffer_delete(chatTextBuffer, &startp, &endp);
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);


}

G_MODULE_EXPORT void on_buttonReceiveMessage_clicked() { // TODO DELETE, JUST FOR TESTING!!!!!

    const gchar *textInsert;

    printf("received!\n");
    chatTextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkViewText));
    textInsert = gtk_entry_get_text(GTK_ENTRY(gtkSendText));

    mark = gtk_text_buffer_get_insert (chatTextBuffer);
    //gtk_text_buffer_get_mark(chatTextBuffer, (const gchar*)mark2);
    gtk_text_buffer_get_iter_at_mark (chatTextBuffer, &iter, mark);
    if (gtk_text_buffer_get_char_count(chatTextBuffer))
        gtk_text_buffer_insert (chatTextBuffer, &iter, "\n",     1);
    gtk_text_buffer_insert (chatTextBuffer, &iter, textInsert, -1);
    //gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0, 0, 1, 1);
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(gtkViewText), mark, 0.0, FALSE, 1, 1);




}