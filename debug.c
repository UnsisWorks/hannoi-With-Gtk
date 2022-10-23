#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

struct _resize_widgets {
   GtkWidget *image;
   GdkPixbuf *pixbuf;
};

typedef struct _resize_widgets ResizeWidgets;

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

int main(int argc, char **argv) {
   GtkWidget *window = NULL;
   GtkWidget *image = NULL;
   GtkWidget *container = NULL;
   GdkPixbuf *pixbuf = NULL;
   ResizeWidgets *widgets;

   gtk_init(&argc, &argv);

   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);
   container = gtk_layout_new(NULL, NULL);
   image = gtk_image_new();

   pixbuf = gdk_pixbuf_new_from_file ("./image/wallpaperPrincipal.jpg", NULL);
   if (pixbuf == NULL) {
      g_printerr("Failed to resize image\n");
      return 1;
   }

   widgets = g_new0(ResizeWidgets, 1);
   widgets->image = image;
   widgets->pixbuf = pixbuf;

   gtk_container_add(GTK_CONTAINER(window), container);
   gtk_layout_put(GTK_LAYOUT(container), image, 0, 0);

   gtk_widget_set_size_request (GTK_WIDGET(window), 20, 20);

   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(container, "size-allocate", G_CALLBACK(resize_image), widgets);

   gtk_widget_show_all(GTK_WIDGET(window));

   gtk_main();

   g_object_unref (pixbuf);
   g_free(widgets);

   return 0;
}