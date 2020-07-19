/*************************************************************************
	> File Name: tiaoshi.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月17日 星期五 21时48分10秒
 ************************************************************************/

#include <gtk/gtk.h>  
  
  int main(int argc, char *argv[])  
  {  
      GtkWidget *window;  
    
      gtk_init(&argc, &argv);  
    
      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    
      gtk_window_set_title(GTK_WINDOW(window), "Hello World");  
    
      g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
      gtk_widget_show_all(window);  
    
      gtk_main();  
    
      return 0;  
  }  
