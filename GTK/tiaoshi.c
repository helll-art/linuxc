/*************************************************************************
	> File Name: tiaoshi.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月18日 星期六 14时18分19秒
 ************************************************************************/

#include<stdio.h>
#include<gtk/gtk.h>

int main(int argc,char **argv)
{
    GtkWidget *window;
    GtkWidget *table;
    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_border_width(GTK_CONTAINER(window),30);
    table = gtk_table_new(2,2,FALSE);
    gtk_container_add(GTK_CONTAINER(window),table);
    gtk_widget_show(table);
    gtk_widget_show(window);
    gtk_main();
}
