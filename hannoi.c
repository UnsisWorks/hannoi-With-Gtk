#include <gtk/gtk.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "Pila.c"
GtkWidget *mainWindow, *windowClose, *combo, *windowGame;
//Create global variables
int idButtons[MAXI];
gint countDisc = 0;
Pila torreA;
Pila torreB;
Pila torreC;
int selection = -1;
GtkWidget *container = NULL;

GtkWidget *buttons[MAXI];
GtkWidget *buttonsBox[MAXI];
GtkWidget *imagesButtons[MAXI];
// create struct for resize image
struct _resize_widgets {
   GtkWidget *image;
   GdkPixbuf *pixbuf;
};
typedef struct _resize_widgets ResizeWidgets;

/**
 * It creates a dialog window with a message and a title, and displays it
 * 
 * @param widget The widget that received the signal.
 * @param message The message to display.
 * @param title The title of the dialog window.
 */
static void showMessage (GtkWidget *widget, gchar *message, gchar *title) {
    GtkWidget *dialog, *label, *contentArea;
    GtkDialogFlags flags;

    // Create at window dialog with title, parent, flags, text in button
    dialog = gtk_dialog_new_with_buttons(title, NULL, flags, "Aceptar", GTK_RESPONSE_NONE, NULL);

    // Set properties at window dialog
    contentArea = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 200);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT );
    gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
    label = gtk_label_new(message);
    // gtk_label

    // Close window dialog to the price button accept
    g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
    // Add witget and show result
    gtk_container_add(GTK_CONTAINER(contentArea), label);
    gtk_widget_show_all(dialog);
}

/**
 * It checks if the tower C is full, if it is, it shows a message to the user
 */
static void winerGame () {
    if (torreC.tope == countDisc) {
        showMessage(NULL, "FELICIDAES, HAS GANADO!!!", "BIEN");
    }
}

/**
 * It checks if the entry is less than the top of the stack, if it is, it returns 0, otherwise it
 * pushes the entry to the stack and returns 1
 * 
 * @param entry the value of the disk that the user wants to move
 * @param pila The stack that the user is trying to push the disk to.
 * 
 * @return the value of the variable selection.
 */
static int validation (int entry,Pila *pila ) {

    g_print("entry %d > cima: %d\n", entry, Cima(pila));
    if (entry > Cima(pila)) {
        return 1;
    } else {
        //Push(entry,pila);
        showMessage(NULL, "No es posible colocar el disco en la torre", "Error");
        selection = -1;
        return 0;
    }
}

/**
 * It takes the widget that was clicked on and finds the index of that widget in the array of buttons
 * 
 * @param widget the widget that was clicked
 * @param used_data This is a pointer to the data that was passed to the g_signal_connect() function.
 */
static void buttonSelection(GtkWidget *widget, gpointer used_data){
   for (int i = 0; i <= countDisc; i++) {
      if (buttons[i] == widget) {
        selection = i;
        g_print("Selection: %d\n", selection);
      }
   }
    if (Cima(&torreA) == selection) {
        
    } else if (Cima(&torreB) == selection) {
        
    } else if (Cima(&torreC) == selection) {
        
    } else {
        puts("NO ES EL ULTIMO DISCO");
        selection = -1;
        // showMessage
    }
}
/**
 * It checks if there's a selected disk, and if there is, it calls the validacion function with the
 * selected disk and the tower A as parameters
 * 
 * @param widget The widget that received the signal.
 * @param used_data This is a pointer to the data that you passed to g_signal_connect().
 */
static void evtTowerA(GtkWidget *widget, gpointer used_data){
    if (selection != -1) {
        
        puts("Validar torre a");
        
        if (validation(selection, &torreA) == 1 ) {
            
            
            if (Cima(&torreA) == selection) {
                g_print("cima a: %d == %d selection - ", Cima(&torreA), selection);
                puts("POP TORRE A");
                Push(Pop(&torreA), &torreA);
            }
            else if (Cima(&torreB) == selection) {
                g_print("cima b: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE B");
                Push(Pop(&torreB), &torreA);
            }
            else if (Cima(&torreC) == selection) {
                g_print("cima c: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE C");
                Push(Pop(&torreC), &torreA);
            } else {
                puts("Torre no encontrada");
            }
            gtk_layout_move(GTK_LAYOUT(container), buttonsBox[selection], 250, 370);
            g_print("CIMA TORRE A UPDATE: %d \n\n", Cima(&torreA));
            winerGame();
        }
    } else {
        showMessage(NULL, "Primero debe seleccionar un disco", "Error");
    }
}
/**
 * It checks if there's a selected disk, and if there is, it calls the validacion function with the
 * selected disk and the tower A as parameters
 * 
 * @param widget The widget that received the signal.
 * @param used_data This is a pointer to the data that you passed to g_signal_connect().
 */
static void evtTowerB(GtkWidget *widget, gpointer used_data){
    if (selection != -1) {
        puts("Validar torre b");
        
        if (validation(selection, &torreB) == 1 ) {
            
            if (Cima(&torreA) == selection) {
                g_print("cima a: %d == %d selection - ", Cima(&torreA), selection);
                puts("POP TORRE A");
                Push(Pop(&torreA), &torreB);
            }
            else if (Cima(&torreB) == selection) {
                g_print("cima b: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE B");
                Push(Pop(&torreB), &torreB);
            }
            else if (Cima(&torreC) == selection) {
                g_print("cima c: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE C");
                Push(Pop(&torreC), &torreB);
            } else {
                puts("Torre no encontrada");
            }
            g_print("CIMA TORRE B UPDATE: %d \n\n", Cima(&torreB));
            gtk_layout_move(GTK_LAYOUT(container), buttonsBox[selection], 705, 370);
            winerGame();
        }
          
    } else {
        showMessage(NULL, "Primero debe seleccionar un disco", "Error");
    }
}
/**
 * It checks if there's a selected disk, and if there is, it calls the validacion function with the
 * selected disk and the tower A as parameters
 * 
 * @param widget The widget that received the signal.
 * @param used_data This is a pointer to the data that you passed to g_signal_connect().
 */
static void evtTowerC(GtkWidget *widget, gpointer used_data){
    if (selection != -1) {
        puts("Validar torre c");
        if (validation(selection, &torreC) == 1) {
            
            
            if (Cima(&torreA) == selection) {
                g_print("cima a: %d == %d selection - ", Cima(&torreA), selection);
                puts("POP TORRE A");
                Push(Pop(&torreA), &torreC);
            }
            else if (Cima(&torreB) == selection) {
                g_print("cima b: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE B");
                Push(Pop(&torreB), &torreC);
            }
            else if (Cima(&torreC) == selection) {
                g_print("cima c: %d == %d selection - ", Cima(&torreB), selection);
                puts("POP TORRE C");
                Push(Pop(&torreC), &torreC);
            } else {
                puts("Torre no encontrada");
            }

            gtk_layout_move(GTK_LAYOUT(container), buttonsBox[selection], 1210, 370);
            winerGame();
            g_print("CIMA TORRE C UPDATE: %d \n\n", Cima(&torreC));
        }
    } else {
        showMessage(NULL, "Primero debe seleccionar un disco", "Error");
    }
}
/**
 * It creates a button with an image of a stick and then creates a buttonbox with the stick button and
 * then creates a for loop that creates a buttonbox for each disc and then puts the buttonbox in the
 * container
 */
static void showtower(){
    GtkWidget *stick = gtk_image_new_from_file("./image/discos/Palo.png");
    GtkWidget *stickB = gtk_image_new_from_file("./image/discos/Palo.png");
    GtkWidget *stickC = gtk_image_new_from_file("./image/discos/Palo.png");
    GtkWidget *buttonStickA = gtk_button_new();

    // Create towers for disk
    GtkWidget *stickBoxA = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_set_image(GTK_BUTTON(buttonStickA),stick);
    gtk_container_add(GTK_CONTAINER(stickBoxA), buttonStickA);

    GtkWidget *buttonStickB = gtk_button_new();
    GtkWidget *stickBoxB = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_set_image(GTK_BUTTON(buttonStickB),stickB);
    gtk_container_add(GTK_CONTAINER(stickBoxB), buttonStickB);

    GtkWidget *buttonStickC = gtk_button_new();
    GtkWidget *stickBoxC = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_button_set_image(GTK_BUTTON(buttonStickC),stickC);
    gtk_container_add(GTK_CONTAINER(stickBoxC), buttonStickC);

    // Set Class for reference in file CSS
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonStickA), "container-button-disc");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonStickB), "container-button-disc");
    gtk_style_context_add_class(gtk_widget_get_style_context(buttonStickC), "container-button-disc");

    // Set signals at towers
    g_signal_connect(buttonStickA, "clicked", G_CALLBACK(evtTowerA), NULL);
    g_signal_connect(buttonStickB, "clicked", G_CALLBACK(evtTowerB), NULL);
    g_signal_connect(buttonStickC, "clicked", G_CALLBACK(evtTowerC), NULL);

    gtk_layout_put(GTK_LAYOUT(container), stickBoxA, 330, 115);
    gtk_layout_put(GTK_LAYOUT(container), stickBoxB, 750, 115);
    gtk_layout_put(GTK_LAYOUT(container), stickBoxC, 1270, 115);
    
    int y = 650;
    int x = 190;
    int sendX = 0;
    int sendY = 0;
    for (int i = 0; i <= countDisc; i++)  {
        gtk_layout_put(GTK_LAYOUT(container), buttonsBox[i], x, y);
        if (i == 0) {
            x += 10;
            y -= 5;
        } else if (i == 5){
            x+= 20;
        } else if (i == 6){
            x+= 7;
        } else {

            x += 23;
        }
        y -= 22;
    }
    //gtk_container_add(GTK_CONTAINER(container), fixed);
    gtk_widget_show_all(container);
}

/**
 * It creates a stack with the number of discs that the user has chosen, and then it creates a button
 * for each disc, and then it shows the tower
 */
static void create_pila(){
    PilaVacia(&torreA);
    PilaVacia(&torreB);
    PilaVacia(&torreC);

    imagesButtons[0]=gtk_image_new_from_file("./image/discos/Disco8.png");
    imagesButtons[1]=gtk_image_new_from_file("./image/discos/Disco7.png");
    imagesButtons[2]=gtk_image_new_from_file("./image/discos/Disco6.png");
    imagesButtons[3]=gtk_image_new_from_file("./image/discos/Disco5.png");
    imagesButtons[4]=gtk_image_new_from_file("./image/discos/Disco4.png");
    imagesButtons[5]=gtk_image_new_from_file("./image/discos/Disco3.png");
    imagesButtons[6]=gtk_image_new_from_file("./image/discos/Disco2.png");
    imagesButtons[7]=gtk_image_new_from_file("./image/discos/Disco1.png");

    int id;
    for (int i = 0; i <= countDisc; i++) {
        id=i;
        Push(id, &torreA);
        idButtons[i] = i;
        g_print("Indice %i: %d\n", i, i);
    }
    for (int i = 0; i <= countDisc; i++) {

        buttons[i] = gtk_button_new();
        gtk_button_set_image(GTK_BUTTON(buttons[i]), imagesButtons[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(buttonSelection), NULL);
        //gtk_button_set_image(GTK_BUTTON(buttons[i]),imagesButtons[i]); 
        buttonsBox[i]= gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add(GTK_CONTAINER(buttonsBox[i]),buttons[i]);

        // Set Class at buttons for reference int css
        gtk_style_context_add_class(gtk_widget_get_style_context(buttons[i]), "button-disc");
        gtk_style_context_add_class(gtk_widget_get_style_context(buttonsBox[i]), "container-button-disc");
    } 
    
    g_print("CIMA DE TORRE A: %d \n", Cima(&torreA));
    showtower();
}

void funtionCloseGameYes(GtkWidget *witget, gpointer user_data){
    exit(-1);
}
static void funtionCloseGameNo(GtkWidget *witget, gpointer user_data){
    gtk_widget_destroy(GTK_WIDGET(windowClose));
    // gtk_widget_destroy(GTK_WIDGET(windowGame));
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), TRUE);
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
    countDisc = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
    gtk_widget_destroy(GTK_WIDGET(windowClose));
    g_print("numero: %d", countDisc);
    create_pila();

}
static void closeNumDisc(GtkWidget *widget, gpointer user_data) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), TRUE);
    gtk_widget_destroy(GTK_WIDGET(windowGame));
}
/**
 * It creates a window with a combo box that allows the user to select the number of discs to be used
 * in the game
 */
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
    // g_signal_connect(windowClose, "destroy", G_CALLBACK(closeNumDisc), NULL);

    // Add widgets at window
    gtk_fixed_put(GTK_FIXED(fixed), label, 40, 30);
    gtk_fixed_put(GTK_FIXED(fixed), combo, 100, 90);
    gtk_fixed_put(GTK_FIXED(fixed), buttBox, 125, 165);

    // Add class for CSS at widgets
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "button-num-disc");
    gtk_style_context_add_class(gtk_widget_get_style_context(label), "label-disc");
    //gtk_style_context_add_class(gtk_widget_get_style_context(fixed), "");
    gtk_widget_set_name(GTK_WIDGET(box), "box-close");
    gtk_box_set_center_widget(GTK_BOX(box), fixed);

    gtk_widget_show_all(windowClose);
}

/**
 * It prints the time in the format of 00:00:00, and it does it every second
 * 
 * @param data This is the data that is passed to the thread.
 */
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

/**
 * It takes a pixbuf, scales it to fit the height of the widget, and then centers it horizontally
 * 
 * @param widget The widget that is being resized.
 * @param allocation The new size of the widget.
 * @param user_data a pointer to a ResizeWidgets structure.
 * 
 * @return FALSE
 */
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
    // g_print("exitt\n");
   g_object_unref (pxbscaled);

   return FALSE;
}

/**
 * It creates a new window, sets its size, and makes it unresizable
 * 
 * @param gidget The widget that received the signal.
 * @param user_data This is a pointer to the data that you passed to g_signal_connect().
 */
static void exit_data(GtkWidget *gidget, gpointer user_data) {
}
static void acercaDe () {
    GtkWidget *window, *image;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    image = gtk_image_new_from_file("./image/AVATARES.png");
    gtk_container_add(GTK_CONTAINER(window), image);
    gtk_widget_show_all(GTK_WIDGET(window));
}

/**
 * It creates a new window, sets the size, creates a layout, creates an image, loads the image, creates
 * a struct to hold the image and the pixbuf, adds the layout to the window, adds the image to the
 * layout, adds a signal to destroy the window, adds a signal to resize the image, and then shows the
 * window
 * 
 * @param widget The widget that received the signal.
 * @param gData This is the data that was passed to the callback function.
 */
static void initGame(GtkWidget *widget, GtkWidget *gData) {
    gtk_widget_set_visible(GTK_WIDGET(mainWindow), FALSE);
    // Create and start threead for timer
    pthread_t initTimer;
    // pthread_create(&initTimer, NULL, &timer, NULL);

    // Create widgets needed
    GtkWidget *image = NULL;
    
    GdkPixbuf *pixbuf = NULL;
    ResizeWidgets *widgets;

    // Create window
    windowGame = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(windowGame), 1700, 1000);
    container = gtk_layout_new(NULL, NULL);
    image = gtk_image_new();

    // Valid load image
    pixbuf = gdk_pixbuf_new_from_file ("./image/interfaz.png", NULL);
    if (pixbuf == NULL) {
        g_printerr("Failed to resize image\n");
    }

    // set values at struct for resize image
    widgets = g_new0(ResizeWidgets, 1);
    widgets->image = image;
    widgets->pixbuf = pixbuf;

    // Set layaut at window
    gtk_container_add(GTK_CONTAINER(windowGame), container);
    gtk_layout_put(GTK_LAYOUT(container), image, 0, 0);

    // Add signals for exit game and resize image bg
    g_signal_connect(windowGame, "destroy", G_CALLBACK(closeGame), NULL);
    g_signal_connect(container, "size-allocate", G_CALLBACK(resize_image), widgets);

    // Resize window.
    gtk_widget_show_all(GTK_WIDGET(windowGame));

    numberDisc();
    
}



/**
 * > This function creates a new window with a table inside a box inside a window
 * 
 * @param widget The widget that received the signal.
 * @param user_data This is a pointer to the data that you want to pass to the callback function.
 */
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



/**
 * It creates a window with a vertical box, which contains 5 buttons
 * 
 * @param app The GtkApplication instance.
 * @param user_data This is a pointer to any data you want to pass to the callback function.
 */
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
    // g_signal_connect(buttonScore, "clicked", G_CALLBACK(windowScore), NULL);
    g_signal_connect(buttonExit, "clicked", G_CALLBACK(closeGame), NULL);

    gtk_widget_set_sensitive (GTK_WIDGET(buttonScore), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonHelp), FALSE);

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