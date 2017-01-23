#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "download.h"
#include "build.h"

char name[] = "BuildToolsGUI";

GtkTextBuffer *output;
GtkTextIter iter;

GtkComboBoxText *version;

char* stradd(const char* a, const char* b) {
    size_t len = strlen(a) + strlen(b);

    char *ret = (char*) malloc(len * (sizeof(char) + 1));
    *ret = '\0';

    return strcat(strcat(ret, a), b);
}

void appendOutput(char toAppend[]) {
    gtk_text_buffer_insert(output, &iter, stradd(toAppend, "\n"), -1);
}

static void winClosed() {
    exit(EXIT_SUCCESS);
}

static void buildCallBack() {
    runBuildTools(gtk_combo_box_text_get_active_text(version));
}

static void updateCallBack() {
    downloadBuildTools();
}

static void connectButtonListeners(GtkBuilder *builder) {
    GtkButton *build = (GtkButton *) gtk_builder_get_object(builder, "build");
    GtkButton *update = (GtkButton *) gtk_builder_get_object(builder, "update");

    g_signal_connect(build, "clicked", G_CALLBACK(buildCallBack), NULL);
    g_signal_connect(update, "clicked", G_CALLBACK(updateCallBack), NULL);
}

static void createWin() {
    GtkWidget *window;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_file("glade/main.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    gtk_window_set_title(GTK_WINDOW(window), name);

    gtk_builder_connect_signals(builder, NULL);
    g_signal_connect(window, "delete_event", G_CALLBACK(winClosed), NULL);

    connectButtonListeners(builder);

    version = (GtkComboBoxText *) gtk_builder_get_object(builder, "version");

    output = gtk_text_view_get_buffer((GtkTextView *) gtk_builder_get_object(builder, "output"));

    gtk_text_buffer_get_end_iter(output, &iter);

    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    GtkApplication *app;

    gtk_init(&argc, &argv);

    app = gtk_application_new(stradd("at.michael1011", name), G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(createWin), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}