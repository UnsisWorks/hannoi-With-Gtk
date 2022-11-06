#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "Pila.c"
GtkWidget *mainWindow, *windowClose, *combo;
//Create global variables
gint countDisc = 0;
Pila torreA;
Pila torreB;
Pila torreC;

GtkWidget *buttons[MAXI];
GtkWidget *buttonsBox[MAXI];
GtkWidget *imagesButtons[MAXI];

int idButtons[MAXI];

// create struct for resize image
struct _resize_widgets {
   GtkWidget *image;
   GdkPixbuf *pixbuf;
};
typedef struct _resize_widgets ResizeWidgets;


static void create_pila(){

    imagesButtons[0]=gtk_image_new_from_file("./image/discos/Disco8");
    imagesButtons[1]=gtk_image_new_from_file("./image/discos/Disco7");
    imagesButtons[2]=gtk_image_new_from_file("./image/discos/Disco6");
    imagesButtons[3]=gtk_image_new_from_file("./image/discos/Disco5");
    imagesButtons[4]=gtk_image_new_from_file("./image/discos/Disco4");
    imagesButtons[5]=gtk_image_new_from_file("./image/discos/Disco3");
    imagesButtons[6]=gtk_image_new_from_file("./image/discos/Disco2");
    imagesButtons[7]=gtk_image_new_from_file("./image/discos/Disco1");
    PilaVacia(&torreA);
    int id;
    for (int i = 0; i < countDisc; i++)
    {
        id=i;
        Push(id, &torreA);
    }
    for (int i = 0; i < id; i++)
    {
        buttons[i]=gtk_button_new();
        gtk_button_set_image(GTK_BUTTON(buttons[i]),imagesButtons[i]); 
        buttonsBox[i]= gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add(GTK_CONTAINER(buttonsBox[i]),buttons[i]);

        // Set Class at buttons for reference int css
        gtk_style_context_add_class(gtk_widget_get_style_context(buttons[i]), "button-disc");


    }
    

}



void funtionCloseGameYes(GtkWidget *witget, gpointer user_data){
    exit(-1);
}
static void funtionCloseGameNo(GtkWidget *witget, gpointer user_data){
    gtk_widget_destroy(GTK_WIDGET(windowClose));
}

// Window the confirm exit game
static void closeGame() {
    GtkWidget *fixed, *label, *box;
    GtkWidget *buttBoxYes, *buttBoxNo, *buttonYes, *buttonNo;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    fixed = gtk_fixed_new();

    // Create window
    windowClose = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(windowClose), 250, 150);
    gtk_window_set_resizable(GTK_WINDOW(windowClose), FALSE);

    // Create buttos and buttons box
    buttBoxNo = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttBoxYes = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    buttonNo = gtk_button_new_with_label("No");
    buttonYes = gtk_button_new_with_label("Yes");

    g_signal_connect(buttonYes, "clicked", G_CALLBACK(funtionCloseGameYes), NULL);
    g_signal_connect(buttonNo, "clicked", G_CALLBACK(funtionCloseGameNo), NULL);

    // Add buttons at buttons box
    gtk_container_add(GTK_CONTAINER(buttBoxNo), buttonNo);
    gtk_container_add(GTK_CONTAINER(buttBoxYes), buttonYes);
    gtk_container_add(GTK_CONTAINER(windowClose), box);
    label = gtk_label_new("Close Game?");

    // Add widgets at window
    gtk_fixed_put(GTK_FIXED(fixed), label, 90, 30);
    gtk_fixed_put(GTK_FIXED(fixed), buttBoxNo, 30, 60);
    gtk_fixed_put(GTK_FIXED(fixed), buttBoxYes, 150, 60);

    // Add class for CSS at widgets
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonYes), "button-close");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonNo), "button-close");
    gtk_style_context_add_class(gtk_widget_get_style_context(label), "label-close");
    //gtk_style_context_add_class(gtk_widget_get_style_context(fixed), "");
    gtk_widget_set_name(GTK_WIDGET(box), "box-close");
    gtk_box_set_center_widget(GTK_BOX(box), fixed);

    gtk_widget_show_all(windowClose);
}

/**
 * It gets the number of discs from the combo box and sets the global variable countDisc to that number
 * 
 * @param widget The widget that received the signal.
 * @param user_data This is a pointer to the data that you want to pass to the callback function.
 */
static void selectedNumberCombo(GtkWidget *widget, gpointer user_data) {
    countDisc = gtk_combo_box_get_active(GTK_COMBO_BOX(combo)) + 1;
    gtk_widget_destroy(GTK_WIDGET(windowClose));
    g_print("numero: %d", countDisc);
    create_pila();

}

// Window the confirm exit game
static void numberDisc() {
    GtkWidget *fixed, *label, *box, *buttBox, *button;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    fixed = gtk_fixed_new();

    // Create window
    windowClose = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(windowClose), 350, 250);
    gtk_window_set_position(GTK_WINDOW(windowClose), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_resizable(GTK_WINDOW(windowClose), FALSE);

    // Create checkBox for selected number disc
    combo = gtk_combo_box_text_new();

    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t3");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t4");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t5");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t6");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t7");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "\t8");

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    // Add buttons at buttons box
    label = gtk_label_new("Número de discos");
    buttBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    button = gtk_button_new_with_label("Aceptar");
    gtk_container_add(GTK_CONTAINER(buttBox), button);
    gtk_container_add(GTK_CONTAINER(windowClose), box);

    g_signal_connect(button, "clicked", G_CALLBACK(selectedNumberCombo), NULL);

    // Add widgets at window
    gtk_fixed_put(GTK_FIXED(fixed), label, 40, 30);
    gtk_fixed_put(GTK_FIXED(fixed), combo, 100, 90);
    gtk_fixed_put(GTK_FIXED(fixed), buttBox, 125, 165);

    // Add class for CSS at widgets
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button-disc");
    gtk_style_context_add_class(gtk_widget_get_style_context(label), "label-disc");
    //gtk_style_context_add_class(gtk_widget_get_style_context(fixed), "");
    gtk_widget_set_name(GTK_WIDGET(box), "box-close");
    gtk_box_set_center_widget(GTK_BOX(box), fixed);

    gtk_widget_show_all(windowClose);
}
// Thread for timer
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
}
static void acercaDe () {
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    gtk_widget_show_all(GTK_WIDGET(window));
}

static void showtower(GtkWidget *container){
    GtkWidget *stick = gtk_image_new_from_file("./image/discos/Palo.png");
    GtkWidget *buttonstick = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(buttonstick),stick);
    GtkWidget *buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);


    
}

static void initGame(GtkWidget *widget, GtkWidget *gData) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    // Create and start threead for timer
    pthread_t initTimer;
    // pthread_create(&initTimer, NULL, &timer, NULL);

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
    g_signal_connect(window, "destroyed", G_CALLBACK(closeGame), NULL);
    g_signal_connect(container, "size-allocate", G_CALLBACK(resize_image), widgets);

    // Resize window.
    gtk_widget_show_all(GTK_WIDGET(window));

    gtk_widget_show_all(GTK_WIDGET(window));
    numberDisc();
    
}

// Window for show table score
static void windowScore (GtkWidget *widget, gpointer user_data) {
    GtkWidget *window, *box, *table;
    GtkWidget *label;

    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    table = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    // gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    // Create labels for container table
    label = gtk_label_new("LABEEEEEEEEEL");


    // Create window for 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Set selectors 
    gtk_style_context_add_class(gtk_widget_get_style_context(table), "table-score");
    gtk_widget_set_name(GTK_WIDGET(box), "box-score");
    
    gtk_box_set_center_widget(GTK_BOX(box), table);
    gtk_container_add(GTK_CONTAINER(table), label);
    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}

// funtion main construct
static void activate (GtkApplication *app, gpointer user_data) {
    
    GtkWidget *buttBoxAcer, *buttBoxPlay, *buttBoxHelp, *buttBoxScore, *buttBoxExit, *box;
    GtkWidget *buttonAcer, *buttonPlay, *buttonHelp, *buttonScore, *buttonExit;
    GtkWidget *imageExit, *imageAcer, *imagePlay, *imageScore, *imageSett;
    GtkCssProvider *cssProvider;
    // Load images for buttons
    imagePlay = gtk_image_new_from_file("./image/PLAY.png");
    imageScore = gtk_image_new_from_file("./image/SCORE.png");
    imageAcer = gtk_image_new_from_file("./image/CREDITS.png");
    imageExit = gtk_image_new_from_file("./image/EXIT.png");
    imageSett = gtk_image_new_from_file("./image/SETTINGS.png");

    cssProvider = gtk_css_provider_new();

    // Create container fixed
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
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
    gtk_button_set_image(GTK_BUTTON(buttonHelp), imageSett);
    gtk_button_set_image(GTK_BUTTON(buttonAcer), imageAcer);
    gtk_button_set_image(GTK_BUTTON(buttonExit), imageExit);


    // Add signals at buttons
    g_signal_connect(buttonPlay, "clicked", G_CALLBACK(initGame), NULL);
    g_signal_connect(buttonAcer, "clicked", G_CALLBACK(acercaDe), NULL);
    g_signal_connect(buttonScore, "clicked", G_CALLBACK(windowScore), NULL);

    // Add buttons  at button box
    gtk_container_add(GTK_CONTAINER(buttBoxAcer), buttonAcer);
    gtk_container_add(GTK_CONTAINER(buttBoxHelp), buttonHelp);
    gtk_container_add(GTK_CONTAINER(buttBoxPlay), buttonPlay);
    gtk_container_add(GTK_CONTAINER(buttBoxScore), buttonScore);
    gtk_container_add(GTK_CONTAINER(buttBoxExit), buttonExit);
    
    // Add buttons at box
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
    gtk_window_set_title (GTK_WINDOW (mainWindow), "torreAs");
    gtk_window_set_default_size (GTK_WINDOW (mainWindow), 650, 850);
    gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);


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