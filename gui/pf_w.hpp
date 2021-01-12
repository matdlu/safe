/*
 * pf_w - pick_file_window
 */

static const int PF_OFF = GUI_OFF;
static const int PF_WIDGET_HEIGHT = 60;
static const int PF_WIDGET_WIDTH = 200;

static const int PF_WINDOW_WIDTH = PF_WIDGET_WIDTH + 2 * PF_OFF;
static const int PF_WINDOW_HEIGHT = 7 * PF_OFF + PF_WIDGET_HEIGHT;

class MyDndBox : public Fl_Box {
public:
    using Fl_Box::Fl_Box;
    int handle(int event) {
        switch ( event ) {
            case FL_DND_ENTER: case FL_DND_DRAG: case FL_DND_RELEASE:
                return 1;
            case FL_PASTE:
                char* url = new char[Fl::event_length()];
                strcpy(url, Fl::event_text());
                this->do_callback(this, (void*)url);
                return 1;
        }
        return Fl_Box::handle(event);
    }
};

static void pick_file_btn_f(Fl_Widget* w, void* vp_arg);
void pf_w(const char* window_label)
{
    Fl_Window* ef_w = myWindowNew(window_label, PF_WINDOW_WIDTH, PF_WINDOW_HEIGHT);

    MyDndBox* dnd_box = new MyDndBox(PF_OFF, PF_OFF, PF_WIDGET_WIDTH, PF_WIDGET_HEIGHT);
    myBoxLabelCfg(dnd_box, PF_DRAG_AND_DROP_LABEL);
    dnd_box->callback(pick_file_btn_f);

    // todo: drag and drop a file to encrypt

    Fl_Button* pick_file_btn = new Fl_Button(PF_OFF, 2 * PF_OFF + PF_WIDGET_HEIGHT, PF_WIDGET_WIDTH, PF_WIDGET_HEIGHT);
    myBtnCfg(pick_file_btn, PF_PICK_FILE_BTN_LABEL, 's', pick_file_btn_f, 0);

    ef_w->show();
}

static void pick_file_btn_f(Fl_Widget* w, void* vp)
{
    char* url = (char*) vp;
    if ( url != 0 ) {
        printf("URL: %s\n", url);
        if ( gui_state == GUI_STATE_DECRYPT ) {
            d_pw_w(w, url);
        } else {
            void** vpa = new void*[2] { url, 0 };
            e_pw_w(w, vpa);
        }
    } else {
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
    }

    delete w->parent();
}
