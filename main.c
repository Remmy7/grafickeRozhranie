#include "login.c"
#include "commonPointers.c"


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    loginScreen();
    printf("back");
    chatScreen();
    return 0;
}