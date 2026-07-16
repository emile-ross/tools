#include "header.h"

/* choose the name of your password database (including its path) 
 * make sure you don't include the home path unless you've disabled use_home_dir_src */
const char passwords_src[16] = "passwords.kdbx";
const char passwords_dst[48] = "backup/passwords/%s-passwords.kdbx";

const char bookmarks_src[16] = "bookmarks.json";
const char bookmarks_dst[32] = "backup/%s-bookmarks.json";

const char gitconfig_src[16] = ".gitconfig";
const char gitconfig_dst[32] = "backup/git/.%s-gitconfig";

const char wifi_logs_src[24] = "logs/wifi_log.log";
const char wifi_logs_dst[24] = "backup/logs/%s-wifi.log";

const Bool use_home_dir_src = True;
const Bool use_home_dir_dst = True;

const Bool verbose = True;
const Bool testing = False;

