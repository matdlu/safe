/*
 * pf_w - pick_file_window
 */

static const int PF_OFF = GUI_OFF;
static const int PF_WIDGET_HEIGHT = 60;
static const int PF_WIDGET_WIDTH = 200;

static const int PF_WINDOW_WIDTH = PF_WIDGET_WIDTH + 2 * PF_OFF;
static const int PF_WINDOW_HEIGHT = 7 * PF_OFF + PF_WIDGET_HEIGHT;

static void pick_file_btn_f(Fl_Widget* w, void* vp_arg);
void pf_w(const char* window_label)
{
    Fl_Window* ef_w = myWindowNew(window_label, PF_WINDOW_WIDTH, PF_WINDOW_HEIGHT);

    Fl_Box* dnd_box = new Fl_Box(PF_OFF, PF_OFF, PF_WIDGET_WIDTH, PF_WIDGET_HEIGHT);
    myBoxLabelCfg(dnd_box, PF_DRAG_AND_DROP_LABEL);

    // todo: drag and drop a file to encrypt

    Fl_Button* pick_file_btn = new Fl_Button(PF_OFF, 2 * PF_OFF + PF_WIDGET_HEIGHT, PF_WIDGET_WIDTH, PF_WIDGET_HEIGHT);
    myBtnCfg(pick_file_btn, PF_PICK_FILE_BTN_LABEL, 's', pick_file_btn_f, 0);

    ef_w->show();
}

static void pick_file_btn_f(Fl_Widget* w, void* vp_arg)
{
    auto* fc = new Fl_Native_File_Chooser(Fl_Native_File_Chooser::BROWSE_FILE);

    if ( gui_state == GUI_STATE_DECRYPT ) fc->filter(mdlStrCat("*", EXT));
    switch ( fc->show() ) {
        case 1: return;
        case -1: fl_message("%s", fc->errmsg()); break;
    }

    char* path = (char*)fc->filename();

    if ( gui_state == GUI_STATE_DECRYPT ) {
        d_pw_w(w, path);
    } else {
        void** vpa = new void*[2] { path, 0 };
        e_pw_w(w, vpa);
    }

    delete w->parent();
}
