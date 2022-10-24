#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
GtkWidget *mainWindow;

// create struct for resize image
struct _resize_widgets {
   GtkWidget *image;
   GdkPixbuf *pixbuf;
};
typedef struct _resize_widgets ResizeWidgets;

void *timer (void *data) {
    int seconds = 0;
    int minuts = 0;
    while (1) {
        seconds ++;
        if (seconds == 60) {
            seconds = 0;
            minuts++;
        }
        g_print("\n\n\n00:%d:%d", minuts, seconds);
        sleep(1);
        system("clear");
    }
    
}

// Funtion for resize image at window
gboolean resize_image(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {
   int x,y,w,h;
   GdkPixbuf *pxbscaled;
   GtkWidget *image = (GtkWidget *) ((ResizeWidgets *) user_data)->image; 
   GdkPixbuf *pixbuf= (GdkPixbuf *) ((ResizeWidgets *) user_data)->pixbuf; 

   x = 0;
   y = 0;

   h = allocation->height;
   w = (gdk_pixbuf_get_width(pixbuf) * h) / gdk_pixbuf_get_height(pixbuf);

   pxbscaled = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);

   if (w < allocation->width) {
      x = (allocation->width - w) / 2;
      gtk_layout_move(GTK_LAYOUT(widget), image, x, y);
   }

   gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
    g_print("exitt\n");
   g_object_unref (pxbscaled);

   return FALSE;
}

// Close game
static void exit_data(GtkWidget *gidget, gpointer user_data) {
    g_print("frferfre\n");
    exit(-1);
}
static void acercaDe () {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_widget_show_all(GTK_WIDGET(window));
}
static void initGame(GtkWidget *widget, GtkWidget *gData) {

    // Create and start threead for timer
    pthread_t initTimer;
    // pthread_create(&initTimer, NULL, &timer, NULL);
    // pthread_join(initTimer, NULL);

    // Create widgets needed
    GtkWidget *window = NULL;
    GtkWidget *image = NULL;
    GtkWidget *container = NULL;
    GdkPixbuf *pixbuf = NULL;
    ResizeWidgets *widgets;

    // Create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 900);
    container = gtk_layout_new(NULL, NULL);
    image = gtk_image_new();

    // Valid load image
    pixbuf = gdk_pixbuf_new_from_file ("./image/Interfaz.png", NULL);
    if (pixbuf == NULL) {
        g_printerr("Failed to resize image\n");
    }

    // set values at struct for resize image
    widgets = g_new0(ResizeWidgets, 1);
    widgets->image = image;
    widgets->pixbuf = pixbuf;

    // Set layaut at window
    gtk_container_add(GTK_CONTAINER(window), container);
    gtk_layout_put(GTK_LAYOUT(container), image, 0, 0);

    // Add signals for exit game and resize image bg
    g_signal_connect(window, "destroy", G_CALLBACK(exit_data), NULL);
    g_signal_connect(container, "size-allocate", G_CALLBACK(resize_image), widgets);
    g_signal_connect(container, "show", G_CALLBACK(resize_image), widgets);

    // Resize window.
    gtk_widget_show_all(GTK_WIDGET(window));

    gtk_main();

    g_object_unref (pixbuf);
    g_free(widgets);

        // g_signal_connect(window, "destroy", G_CALLBACK(exit_data), NULL);

        gtk_widget_show_all(GTK_WIDGET(window));
    
}
// funtion construct
static void activate (GtkApplication *app, gpointer user_data) {
    
    GtkWidget *buttBoxAcer, *buttBoxPlay, *buttBoxHelp, *buttBoxScore, *buttBoxExit, *box;
    GtkWidget *buttonAcer, *buttonPlay, *buttonHelp, *buttonScore, *buttonExit;
    GtkWidget *imageExit, *imageAcer, *imagePlay, *imageScore;
    GtkCssProvider *cssProvider;

    // Load images for buttons
    imagePlay = gtk_image_new_from_file("./image/PLAY.png");
    imageScore = gtk_image_new_from_file("./image/SCORE.png");
    imageAcer = gtk_image_new_from_file("./image/CREDITS.png");
    imageExit = gtk_image_new_from_file("./image/EXIT.png");

    cssProvider = gtk_css_provider_new();

    // Create container fixed
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 45);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    // Create box for buttons
    buttBoxAcer = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxPlay = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxHelp = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxScore = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxExit = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    // Create buttons and add at box container
    buttonAcer = gtk_button_new();
    buttonHelp = gtk_button_new();
    buttonPlay = gtk_button_new();
    buttonScore = gtk_button_new();
    buttonExit = gtk_button_new();

    gtk_button_set_image(GTK_BUTTON(buttonPlay), imagePlay);
    gtk_button_set_image(GTK_BUTTON(buttonScore), imageScore);
    // gtk_button_set_image(GTK_BUTTON(buttonHelp), image);
    gtk_button_set_image(GTK_BUTTON(buttonAcer), imageAcer);
    gtk_button_set_image(GTK_BUTTON(buttonExit), imageExit);


    // Add signals at buttons
    g_signal_connect(buttonPlay, "clicked", G_CALLBACK(initGame), NULL);
    g_signal_connect(buttonAcer, "clicked", G_CALLBACK(acercaDe), NULL);

    gtk_container_add(GTK_CONTAINER(buttBoxAcer), buttonAcer);
    gtk_container_add(GTK_CONTAINER(buttBoxHelp), buttonHelp);
    gtk_container_add(GTK_CONTAINER(buttBoxPlay), buttonPlay);
    gtk_container_add(GTK_CONTAINER(buttBoxScore), buttonScore);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    gtk_container_add(GTK_CONTAINER(box), buttBoxPlay);
    gtk_container_add(GTK_CONTAINER(box), buttBoxScore);
    gtk_container_add(GTK_CONTAINER(box), buttBoxHelp);
    gtk_container_add(GTK_CONTAINER(box), buttBoxAcer);
    gtk_container_add(GTK_CONTAINER(box), buttBoxExit);

    gtk_widget_set_size_request(GTK_WIDGET(buttonAcer), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonHelp), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonPlay), 240, 90);
    gtk_widget_set_size_request(GTK_WIDGET(buttonScore), 240, 90);
    
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonAcer), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonHelp), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonPlay), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonScore), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonExit), "button");
    gtk_style_context_add_class(gtk_widget_get_style_context(imageExit), "images");
        
    // Set properties for winow
    mainWindow = gtk_application_window_new (app);
    gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (mainWindow), "Window");
    gtk_window_set_default_size (GTK_WINDOW (mainWindow), 800, 900);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);

    // Set properties for button and button-box
    // button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    // button = gtk_button_new();
    // gtk_button_set_image(GTK_BUTTON(button), image);
    // gtk_style_context_add_class(gtk_widget_get_style_context(button), "disco");
    
    // gtk_container_add (GTK_CONTAINER (button_box), button);
    // gtk_fixed_put(GTK_FIXED(fixed), button_box, 1, 10);

    gtk_widget_set_name(GTK_WIDGET(box), "box");

    gtk_css_provider_load_from_path(cssProvider, "./style.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(cssProvider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_container_add(GTK_CONTAINER(mainWindow), box);
    gtk_widget_show_all (mainWindow);
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