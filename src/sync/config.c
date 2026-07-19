#include "header.h"

/* choose the name of your password database (including its path) 
 * make sure you don't include the home path unless you've disabled use_home_dir_src */
char *passwords_src = "passwords.kdbx";
char *passwords_dst = "backup/passwords/%s-passwords.kdbx";

char *bookmarks_src = "bookmarks.json";
char *bookmarks_dst = "backup/bookmarks/%s-bookmarks.json";

char *gitconfig_src = ".gitconfig";
char *gitconfig_dst = "backup/git/.%s-gitconfig";

char *wifi_logs_src = "logs/wifi_log.log";
char *wifi_logs_dst = "backup/logs/%s-wifi.log";

const Bool use_home_dir_src = True;
const Bool use_home_dir_dst = True;

const Bool verbose = True;
const Bool testing = False;
