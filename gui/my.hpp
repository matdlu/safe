/*
 * my - helper functions
 */
Fl_Box* myBoxLabelCfg(Fl_Box* w, const char* label_str) {
    w->align(FL_ALIGN_CENTER);
    w->label(label_str);
    return w;
}

void myBtnCfg(Fl_Button* btn, const char* label_str, int shortcut, Fl_Callback cb, void* p) {
    btn->label(label_str);
    btn->shortcut(shortcut);
    btn->callback(cb, p);
}

void mySecretInputCfg(Fl_Secret_Input* si, const char* label_str, Fl_Callback* cb, void* p)
{
    si->label(label_str);
    si->align(FL_ALIGN_TOP_LEFT);
    si->when(FL_WHEN_CHANGED);
    si->callback(cb, p);
}

Fl_Window* myWindowNew(const char* label_str, int width, int height) {
    auto* w = new Fl_Window(width, height);
    w->label(label_str);
    w->resizable(w);
    return w;
}
