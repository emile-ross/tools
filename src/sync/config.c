#include "header.h"

/* choose the name of your password database (including its path) 
 * make sure you don't include the home path unless you've disabled use_home_dir_src */
char passwords_src[16] = "passwords.kdbx";
char passwords_dst[48] = "backup/passwords/%s-passwords.kdbx";

char bookmarks_src[16] = "bookmarks.json";
char bookmarks_dst[32] = "backup/%s-bookmarks.json";

char gitconfig_src[16] = ".gitconfig";
char gitconfig_dst[32] = "backup/git/.%s-gitconfig";

char wifi_logs_src[24] = "logs/wifi_log.log";
char wifi_logs_dst[24] = "backup/logs/%s-wifi.log";

const Bool use_home_dir_src = True;
const Bool use_home_dir_dst = True;

const Bool verbose = True;
const Bool testing = False;

