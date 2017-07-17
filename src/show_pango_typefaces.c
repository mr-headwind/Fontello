/*
**  This file is part of Fontello.
** 
**  Fontello is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**  
**  Fontello is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**  
**  You should have received a copy of the GNU General Public License
**  along with Fontello.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <glib.h>
#include <pango/pangocairo.h>

#include <gtk/gtk.h>


/* Typedefs */

typedef struct _main_ui
{
    GtkWidget *window;
    GtkWidget *f_grid;
    GtkWidget *scrollwin;
    GtkWidget *close_btn;
} MainUi;

/* Prototypes */

static void list_fonts(MainUi *);
static void main_ui(MainUi *);
void table_hdr(char *, char *, char *, MainUi *);
void set_label(GtkWidget *);
void show_sample(PangoFontFamily *, const char *, int, MainUi *);
void set_css();
void OnQuit(GtkWidget*, gpointer);


/* Globals */

static const gchar *css_data =
        "GtkLabel#col_hdr { font-weight: bold; }";



/* Main program control */

int main (int argc, char ** argv)
{
    MainUi m_ui;

    /* Initialise Gtk */
    gtk_init(&argc, &argv);

    /* Create main user interface */
    main_ui(&m_ui);

    list_fonts(&m_ui);

    /* Gtk main loop */
    set_css();
    gtk_widget_show_all(m_ui.window);
    gtk_main();

    return 0;
}


/* Create main user interface */

void main_ui(MainUi *m_ui)
{  
    /* Set up the UI window */
    m_ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  
    gtk_window_set_title(GTK_WINDOW(m_ui->window), "Pango Fonts Sampler");
    gtk_window_set_position(GTK_WINDOW(m_ui->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(m_ui->window), 450, 600);
    gtk_container_set_border_width(GTK_CONTAINER(m_ui->window), 10);

    /* Font box */
    m_ui->f_grid = gtk_grid_new();
    gtk_widget_set_halign(GTK_WIDGET (m_ui->f_grid), GTK_ALIGN_START);
    table_hdr("No.", "Font Family", "Sample", m_ui);

    /* Scroll window */
    m_ui->scrollwin = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (m_ui->scrollwin),
    				   GTK_POLICY_AUTOMATIC,
    				   GTK_POLICY_AUTOMATIC);

    gtk_container_add(GTK_CONTAINER(m_ui->scrollwin), m_ui->f_grid);

    /* Exit when window closed */
    g_signal_connect(m_ui->window, "destroy", G_CALLBACK(OnQuit), m_ui->window);

    /* Show window */
    gtk_container_add(GTK_CONTAINER(m_ui->window), m_ui->scrollwin);
    gtk_widget_show_all(m_ui->window);

    return;
}


/* Table headings */

void show_sample(PangoFontFamily * family, const char *family_nm, int row, MainUi *m_ui)
{  
    GtkWidget *lbl_font, *lbl_num, *lbl_sample;
    char s[10];
    PangoFontDescription *pf;

    sprintf(s, "%d", row);

    lbl_num = gtk_label_new(s);
    set_label(lbl_num);

    lbl_font = gtk_label_new(family_nm);
    set_label(lbl_font);

    lbl_sample = gtk_label_new(family_nm);
    pf = pango_font_description_from_string ("Sans");
    pango_font_description_set_family (pf, family_nm);
    gtk_widget_override_font (lbl_sample, pf);
    set_label(lbl_sample);

    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_num, 0, row + 1, 1, 1);
    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_font, 1, row + 1, 1, 1);
    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_sample, 2, row + 1, 1, 1);

    pango_font_description_free (pf);

    return;
}


/* Table headings */

void set_label(GtkWidget *lbl)
{  
    gtk_widget_set_margin_start(lbl, 10);
    gtk_widget_set_margin_end(lbl, 10);
    gtk_widget_set_margin_bottom(lbl, 5);
    gtk_widget_set_halign(lbl, GTK_ALIGN_START);
    gtk_widget_set_valign(lbl, GTK_ALIGN_CENTER);

    return;
}


/* Font list and samples */

void table_hdr(char *num, char *nm, char *sample, MainUi *m_ui)
{  
    GtkWidget *lbl_font, *lbl_num, *lbl_sample;

    lbl_num = gtk_label_new(num);
    gtk_widget_set_name (lbl_num, "col_hdr");
    gtk_widget_set_margin_bottom(lbl_num, 10);
    gtk_widget_set_halign(lbl_num, GTK_ALIGN_CENTER);

    lbl_font = gtk_label_new(nm);
    gtk_widget_set_name (lbl_font, "col_hdr");
    gtk_widget_set_margin_bottom(lbl_font, 10);
    gtk_widget_set_halign(lbl_font, GTK_ALIGN_CENTER);

    lbl_sample = gtk_label_new(sample);
    gtk_widget_set_name (lbl_sample, "col_hdr");
    gtk_widget_set_margin_bottom(lbl_sample, 10);
    gtk_widget_set_halign(lbl_sample, GTK_ALIGN_CENTER);

    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_num, 0, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_font, 1, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (m_ui->f_grid), lbl_sample, 2, 0, 1, 1);

    return;
}


/* Set up provider data and apply */

void set_css()
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
                                    css_data,
                                    -1,
                                    NULL);

    g_object_unref(provider);

    return;
}


/* Callback - Quit */

void OnQuit(GtkWidget *window, gpointer user_data)
{  
    /* Main quit */
    gtk_main_quit();

    return;
}  


/* Credit: https://www.lemoda.net/pango/list-fonts */

static void list_fonts (MainUi *m_ui)
{
    int i;
    PangoFontFamily ** families;
    int n_families;
    PangoFontMap * fontmap;

    fontmap = pango_cairo_font_map_get_default();
    pango_font_map_list_families (fontmap, & families, & n_families);
    printf ("There are %d families\n", n_families);
    for (i = 0; i < n_families; i++) {
        PangoFontFamily * family = families[i];
        const char * family_name;

        family_name = pango_font_family_get_name (family);
        printf ("Family %d: %s\n", i, family_name);

        show_sample(family, family_name, i, m_ui);
    }
    g_free (families);
}
