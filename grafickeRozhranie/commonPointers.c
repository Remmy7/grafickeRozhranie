#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

GtkBuilder *builder;
GtkWidget *windowChat;
GtkWidget *gtkViewText;
GtkWidget *gtkSendText;
GtkWidget *buttonSendMessage;

GtkWidget *windowLogin;
GtkWidget *errorMessage;
GtkWidget *usernameEntry;
GtkWidget *passwordEntry;

GtkWidget *buttonLogin;
GtkWidget *buttonRegister;
GtkWidget *buttonHistory;

GtkTextBuffer *chatTextBuffer;


