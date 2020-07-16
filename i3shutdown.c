/*
 *   i3shutdown.c: shutdown menu for the i3 window manager written with gtk+-3.0
 *
 *   Copyright (C) 2020  @venji10 <bennisteinir@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


static void shutdown (GtkWidget *widget, gpointer   data ) {

    system ("shutdown now");

}

static void reboot (GtkWidget *widget, gpointer   data ) {

    system ("reboot");

}

static void logout (GtkWidget *widget, gpointer   data ) {

    system ("i3-msg exit");

}

void toggleFloating () {

    system ("i3-msg floating toggle");

}

static void destroy (GtkWidget *widget, gpointer   data ) {

    gtk_main_quit ();

}


int main( int argc, char *argv[] ) {

    GtkWidget *window;
    GtkWidget *buttonBox;

    GtkWidget *shutdownButton;
    GtkWidget *rebootButton;
    GtkWidget *logoutButton;


    gtk_init(&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "delete-event", G_CALLBACK (destroy), NULL);
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 3);
    gtk_window_set_decorated (window, FALSE);

    /* create box for the buttons since the window could not store more than one button */
    buttonBox = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);

    /* initialize buttons */
    shutdownButton = gtk_button_new_with_label ("Shutdown");
    rebootButton = gtk_button_new_with_label ("Reboot");
    logoutButton = gtk_button_new_with_label ("Logout");


    /* Color the buttons */
    GdkRGBA red;
    GdkRGBA blue;
    GdkRGBA green;
    gdk_rgba_parse (&red, "red" );
    gdk_rgba_parse (&blue, "blue");
    gdk_rgba_parse (&green, "green");

    gtk_widget_override_color (rebootButton, GTK_STATE_NORMAL, &red);
    gtk_widget_override_color (shutdownButton, GTK_STATE_NORMAL, &blue);
    gtk_widget_override_color (logoutButton, GTK_STATE_NORMAL, &green);



    /* add callbacks for click events */
    g_signal_connect (shutdownButton, "clicked", G_CALLBACK (shutdown), NULL);
    g_signal_connect (rebootButton, "clicked", G_CALLBACK (reboot), NULL);
    g_signal_connect (logoutButton, "clicked", G_CALLBACK (logout), NULL);
    g_signal_connect_swapped (shutdownButton, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    g_signal_connect_swapped (rebootButton, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    g_signal_connect_swapped (logoutButton, "clicked", G_CALLBACK (gtk_widget_destroy), window);


    /* add buttons to the buttonBox and add the buttonBox to the window */
    gtk_container_add (GTK_CONTAINER (buttonBox), shutdownButton);
    gtk_container_add (GTK_CONTAINER (buttonBox), rebootButton);
    gtk_container_add (GTK_CONTAINER (buttonBox), logoutButton);
    gtk_container_add (GTK_CONTAINER (window), buttonBox);

    /* show all widgets */
    gtk_widget_show (shutdownButton);
    gtk_widget_show (rebootButton);
    gtk_widget_show (logoutButton);

    gtk_widget_show (buttonBox);

    gtk_widget_show (window);

//    gtk_widget_set_opacity (GTK_WIDGET (window), 0);

    /* Use a thread to set the window type to floating since it has to be executed after gtk_main() which blocks the main thread.
     * Floating mode is required because the window would look ugly with i3´s tiling
     */
    pthread_t thread_id;
    pthread_create (&thread_id, NULL, toggleFloating, NULL);

    gtk_main ();

    return 0;
}
