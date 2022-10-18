#include <gtk/gtk.h>
//#include "gtk_auto.h"

// funtion construct
static void activate (GtkApplication *app, gpointer user_data) {

    GtkWidget *window, *fixed;
    GtkWidget *button, *button_box;
    GtkWidget *image;

    // Cerate image
    image = gtk_image_new_from_file("./image/wallpaperPrincipal.jpg");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 200);
    gtk_image_set_from_icon_name(GTK_IMAGE(image), "wallpaper", 100);
    image = gtk_image_new_from_icon_name("name", GTK_ICON_SIZE_DIALOG);

    // Create container fixed
    fixed = gtk_fixed_new();
        
    // Set properties for winow
    window = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Set properties for button and button-box
    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(button), image);
    
    gtk_container_add (GTK_CONTAINER (button_box), button);
    gtk_fixed_put(GTK_FIXED(fixed), button_box, 170, 150);

    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all (window);
}

// funtion main
int main (int argc, char **argv) {
    GtkApplication *app;
    int status;
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}

// Compiler gcc `pkg-config --cflags gtk+-3.0` -o hannoi hannoi.c `pkg-config --libs gtk+-3.0`