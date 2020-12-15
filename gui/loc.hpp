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
static const char* MAIN_WINDOW_LABEL = "Safe - Crypto tool";
static const char* D_BTN_LABEL = "Decrypt";
static const char* EM_BTN_LABEL = "Encrypt message";
static const char* EF_BTN_LABEL = "Encrypt file";

/*
 * gui.cpp: d_btn_f()
 */
static const char* D_WINDOW_LABEL = "Safe - Decrypt";

/*
 * gui.cpp: ef_btn_f()
 */
static const char* EF_WINDOW_LABEL = "Safe - Encrypt file";

/*
 * em_btn_f.hpp: em_btn_f()
 */
static const char* EM_WINDOW_LABEL = "Safe - Encrypt message";
static const char* EM_PASTE_BTN_LABEL = "Paste";
static const char* EM_ENCRYPT_BTN_LABEL = "Encrypt";

/*
 * pf_w.hpp: pf_w()
 */
static const char* PF_DRAG_AND_DROP_LABEL = "Drag and drop a file";
static const char* PF_PICK_FILE_BTN_LABEL = "Pick a file";

/*
 * pw_w/e_pw_w.hpp: e_pw_w()
 */
static const char* E_PW_WINDOW_LABEL = "Safe - Password Window";
static const char* E_PW_INPUT1_LABEL = "Password:";
static const char* E_PW_INPUT2_LABEL = "Confirm the password:";
static const char* E_PW_NEXT_BTN_LABEL = "Save";
static const char* E_PW_FEEDBACK_LABEL_NO_MATCH = "Passwords do not match. ✗";
static const char* E_PW_W_FEEDBACK_LABEL_BLANK = "Password can't be blank. ✗";
static const char* E_PW_FEEDBACK_LABEL_MATCH = "Passwords match. ✓";
static const char* E_PW_EMPTY_MESSAGE_ERROR = "Cannot encrypt an empty message!";

/*
 * pw_w/d_pw_w.hpp: d_pw_w()
 */
static const char* D_PW_WINDOW_LABEL = E_PW_WINDOW_LABEL;
static const char* D_PW_NEXT_BTN_LABEL = "Decrypt";
static const char* D_PW_FILE_LABEL = "File: ";
static const char* D_PW_INPUT_LABEL = "Password for the file:";

/*
 * pw_w/next_btn_f.hpp: next_btn_f()
 */
static const char* NEXT_BTN_WRITE_ERROR = "Write error. Check directory permissions and available space.";
static const char* NEXT_BTN_VERIFICATION_ERROR = "Verification failed.\nMost likely due to wrong password or mistake in choosing the file.\nIn the worst case file could have been damaged.";
static const char* NEXT_BTN_READING_ERROR = "Reading failed.";
#endif

/*
 * LOC_PL
 */
#ifdef LOC_PL
/*
 * gui.cpp: main_window()
 */
static const char* MAIN_WINDOW_LABEL = "Sejf - Narzędzie do szyfrowania";
static const char* D_BTN_LABEL = "Odszyfruj";
static const char* EM_BTN_LABEL = "Szyfruj wiadomość";
static const char* EF_BTN_LABEL = "Szyfruj plik";

/*
 * gui.cpp: d_btn_f()
 */
static const char* D_WINDOW_LABEL = "Sejf - Odszyfruj";

/*
 * gui.cpp: ef_btn_f()
 */
static const char* EF_WINDOW_LABEL = "Sejf - Szyfruj plik";

/*
 * em_btn_f.hpp: em_btn_f()
 */
static const char* EM_WINDOW_LABEL = "Sejf - Szyfruj wiadomość";
static const char* EM_PASTE_BTN_LABEL = "Wklej";
static const char* EM_ENCRYPT_BTN_LABEL = "Szyfruj";

/*
 * pf_w.hpp: pf_w()
 */
static const char* PF_DRAG_AND_DROP_LABEL = "Przeciągnij plik";
static const char* PF_PICK_FILE_BTN_LABEL = "Wybierz plik";

/*
 * pw_w/e_pw_w.hpp: e_pw_w()
 */
static const char* E_PW_WINDOW_LABEL = "Sejf - Wpisz hasło";
static const char* E_PW_INPUT1_LABEL = "Hasło:";
static const char* E_PW_INPUT2_LABEL = "Potwierdź hasło:";
static const char* E_PW_NEXT_BTN_LABEL = "Zapisz";
static const char* E_PW_FEEDBACK_LABEL_NO_MATCH = "Hasła nie są takie same. ✗";
static const char* E_PW_W_FEEDBACK_LABEL_BLANK = "Hasło nie może być puste. ✗";
static const char* E_PW_FEEDBACK_LABEL_MATCH = "Hasła są takie same. ✓";
static const char* E_PW_EMPTY_MESSAGE_ERROR = "Nie da się zaszyfrować pustej wiadomości!";

/*
 * pw_w/d_pw_w.hpp: d_pw_w()
 */
static const char* D_PW_WINDOW_LABEL = E_PW_WINDOW_LABEL;
static const char* D_PW_NEXT_BTN_LABEL = "Odszyfruj";
static const char* D_PW_FILE_LABEL = "Plik: ";
static const char* D_PW_INPUT_LABEL = "Hasło do pliku:";

/*
 * pw_w/next_btn_f.hpp: next_btn_f()
 */
static const char* NEXT_BTN_WRITE_ERROR = "Write error. Check directory permissions and available space.";
static const char* NEXT_BTN_VERIFICATION_ERROR = "Weryfikacja nie powiodła się.\nNajprawdopodobniej błędne hasło lub pomyłka co do pliku.\nW najgorszym wypadku plik był wcześniej uszkodzony.";
static const char* NEXT_BTN_READING_ERROR = "Wczytanie pliku się nie powiodło.";
#endif
