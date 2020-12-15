/*
 * loc - localization
 */

/*
 * LOC_EN
 */
#ifdef LOC_EN
/*
 * gui.cpp: main_window()
 */
#define MAIN_WINDOW_LABEL "Safe - Crypto tool"
#define D_BTN_LABEL "Decrypt"
#define EM_BTN_LABEL "Encrypt message"
#define EF_BTN_LABEL "Encrypt file"

/*
 * gui.cpp: d_btn_f()
 */
#define D_WINDOW_LABEL "Safe - Decrypt"

/*
 * gui.cpp: ef_btn_f()
 */
#define EF_WINDOW_LABEL "Safe - Encrypt file"

/*
 * em_btn_f.hpp: em_btn_f()
 */
#define EM_WINDOW_LABEL "Safe - Encrypt message"
#define EM_PASTE_BTN_LABEL "Paste"
#define EM_ENCRYPT_BTN_LABEL "Encrypt"

/*
 * pf_w.hpp: pf_w()
 */
#define PF_DRAG_AND_DROP_LABEL "Drag and drop a file"
#define PF_PICK_FILE_BTN_LABEL "Pick a file"

/*
 * pw_w/e_pw_w.hpp: e_pw_w()
 */
#define E_PW_WINDOW_LABEL "Safe - Password Window"
#define E_PW_INPUT1_LABEL "Password:"
#define E_PW_INPUT2_LABEL "Confirm the password:"
#define E_PW_NEXT_BTN_LABEL "Save"
#define E_PW_FEEDBACK_LABEL_NO_MATCH "Passwords do not match. ✗"
#define E_PW_W_FEEDBACK_LABEL_BLANK "Password can't be blank. ✗"
#define E_PW_FEEDBACK_LABEL_MATCH "Passwords match. ✓"
#define E_PW_EMPTY_MESSAGE_ERROR "Cannot encrypt an empty message!"

/*
 * pw_w/d_pw_w.hpp: d_pw_w()
 */
#define D_PW_WINDOW_LABEL E_PW_WINDOW_LABEL
#define D_PW_NEXT_BTN_LABEL "Decrypt"
#define D_PW_FILE_LABEL "File: "
#define D_PW_INPUT_LABEL "Password for the file:"

/*
 * pw_w/next_btn_f.hpp: next_btn_f()
 */
#define NEXT_BTN_WRITE_ERROR "Write error. Check directory permissions and available space."
#define NEXT_BTN_VERIFICATION_ERROR "Verification failed.\nMost likely due to wrong password or mistake in choosing the file.\nIn the worst case file could have been damaged."
#define NEXT_BTN_READING_ERROR "Reading failed."
#endif

/*
 * LOC_PL
 */
#ifdef LOC_PL
/*
 * gui.cpp: main_window()
 */
#define MAIN_WINDOW_LABEL "Sejf - Narzędzie do szyfrowania"
#define D_BTN_LABEL "Odszyfruj"
#define EM_BTN_LABEL "Szyfruj wiadomość"
#define EF_BTN_LABEL "Szyfruj plik"

/*
 * gui.cpp: d_btn_f()
 */
#define D_WINDOW_LABEL "Sejf - Odszyfruj"

/*
 * gui.cpp: ef_btn_f()
 */
#define EF_WINDOW_LABEL "Sejf - Szyfruj plik"

/*
 * em_btn_f.hpp: em_btn_f()
 */
#define EM_WINDOW_LABEL "Sejf - Szyfruj wiadomość"
#define EM_PASTE_BTN_LABEL "Wklej"
#define EM_ENCRYPT_BTN_LABEL "Szyfruj"

/*
 * pf_w.hpp: pf_w()
 */
#define PF_DRAG_AND_DROP_LABEL "Przeciągnij plik"
#define PF_PICK_FILE_BTN_LABEL "Wybierz plik"

/*
 * pw_w/e_pw_w.hpp: e_pw_w()
 */
#define E_PW_WINDOW_LABEL "Sejf - Wpisz hasło"
#define E_PW_INPUT1_LABEL "Hasło:"
#define E_PW_INPUT2_LABEL "Potwierdź hasło:"
#define E_PW_NEXT_BTN_LABEL "Zapisz"
#define E_PW_FEEDBACK_LABEL_NO_MATCH "Hasła nie są takie same. ✗"
#define E_PW_W_FEEDBACK_LABEL_BLANK "Hasło nie może być puste. ✗"
#define E_PW_FEEDBACK_LABEL_MATCH "Hasła są takie same. ✓"
#define E_PW_EMPTY_MESSAGE_ERROR "Nie da się zaszyfrować pustej wiadomości!"

/*
 * pw_w/d_pw_w.hpp: d_pw_w()
 */
#define D_PW_WINDOW_LABEL E_PW_WINDOW_LABEL
#define D_PW_NEXT_BTN_LABEL "Odszyfruj"
#define D_PW_FILE_LABEL "Plik: "
#define D_PW_INPUT_LABEL "Hasło do pliku:"

/*
 * pw_w/next_btn_f.hpp: next_btn_f()
 */
#define NEXT_BTN_WRITE_ERROR "Write error. Check directory permissions and available space."
#define NEXT_BTN_VERIFICATION_ERROR "Weryfikacja nie powiodła się.\nNajprawdopodobniej błędne hasło lub pomyłka co do pliku.\nW najgorszym wypadku plik był wcześniej uszkodzony."
#define NEXT_BTN_READING_ERROR "Wczytanie pliku się nie powiodło."
#endif
