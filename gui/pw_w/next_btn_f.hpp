/*
 * next_btn_f - next_button_function
 */

void next_btn_f (Fl_Widget* w, void* p)
{
    void** vpa = (void**)p;

    const char* pw = ((Fl_Secret_Input*)vpa[0])->value();

    if( gui_state == GUI_STATE_DECRYPT ) {
        char* path = (char*)vpa[1];
        EncDecryptFileOut out = encDecryptFile(pw, path);
        switch ( out.r ) {
            case 0: fl_message("%s", NEXT_BTN_READING_ERROR); return;
            case -1: fl_message("%s", NEXT_BTN_VERIFICATION_ERROR); return;
        }
        switch ( out.enc_metadata ) {
            case ENC_METADATA_MESSAGE: em_btn_f(0, mdlUcaToStrNew(out.m, out.m_l)); break;
            case ENC_METADATA_FILE: gui_state = GUI_STATE_WRITE_FILE; vpa[0] = new EncDecryptFileOut{out}; next_btn_f(w->parent(), vpa);
                break;
        }
    } else {
        auto* fc = new Fl_Native_File_Chooser(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);

        const char* ext = gui_state == GUI_STATE_WRITE_FILE ? TXT_EXT : EXT;

        fc->filter(mdlStrCat("*", ext));
        switch ( fc->show() ) {
            case 1: return;
            case -1: fl_message("%s", fc->errmsg()); break;
        }

        const char* out_path = mdlStrCat(fc->filename(), ext);
        int r;
        if ( gui_state == GUI_STATE_WRITE_FILE ) {
            auto* out = (EncDecryptFileOut*) vpa[0];
            r = mdlIoToFile(out->m, out->m_l, out_path);
        } else {
            char* arg1;
            switch( gui_state ) {
                case GUI_STATE_ENCRYPT_FILE:
                    arg1 = (char*) vpa[1]; // in_path
                    r = ! encEncryptFile(pw, arg1, out_path);
                    break;
                case GUI_STATE_ENCRYPT_MESSAGE:
                    arg1 = ((Fl_Text_Buffer *) vpa[1])->text(); // message
                    r = ! encEncryptMessage(pw, arg1, out_path);
                    break;
            }
        }

        if ( r != 0 ) {
            fl_message("%s\ncode: %d", NEXT_BTN_WRITE_ERROR, r);
            return;
        };

        // todo: perform verification whether the content of the file saved are the same as the file in memory
        // todo: overwrite memory of objects which contained sensitive information (children of password_window, buf) with zeroes

        if ( gui_state == GUI_STATE_ENCRYPT_MESSAGE ) delete (Fl_Window*) vpa[2];
    }

    delete w->parent();
}
