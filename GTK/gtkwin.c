/*************************************************************************
	> File Name: gtkwin.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月17日 星期五 21时32分56秒
 ************************************************************************/

#include<gtk/gtk.h>
void hello(GtkWidget *widget,gpointer *data)
{
    g_print("button clicked and data = %s\n",(char *)data);
}

void destroy(GtkWidget *widget,gpointer *data)
{
    gtk_main_quit();
}
int main(int argc,char **argv)
{

    //定义指向控件的指针
    GtkWidget *window;
    GtkWidget *button;
    //初始化图形显示环境
    gtk_init(&argc,&argv);

    
    //创建窗口，并设置当关闭窗口时，要执行的回调函数
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destroy),NULL);

    //设置窗口的属性
    gtk_container_border_width(GTK_CONTAINER(window),20);

    //创建按钮，并设置当单击按钮时，要执行的回调函数
    button = gtk_button_new_with_label("Hello World");
    g_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(hello),"I am from button");
    gtk_container_add(GTK_CONTAINER(window),button);

    gtk_widget_show(button);
    gtk_widget_show(window);

    gtk_main();

    
    return 0;
}
