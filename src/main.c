#include <gtk/gtk.h>
#include <stdlib.h>
#include <memory.h>

char name[] = "BuildToolsGUI";

char* stradd(const char* a, const char* b){
    size_t len = strlen(a) + strlen(b);

    char *ret = (char*) malloc(len * (sizeof(char) + 1));
    *ret = '\0';

    return strcat(strcat(ret, a), b);
}

static void winClosed() {
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/main.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    g_signal_connect(window, "delete_event", G_CALLBACK(winClosed), NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();

    return 0;
}