#include <glib.h>
#include "commonPointers.c"
#include <string.h>
GtkTextIter iter;
GtkTextMark *mark, *mark2;
const gchar* tempName = "jano";
const gchar* tempName2 = "tibor";


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




}
