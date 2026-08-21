#include "header.h"

/* choose the name of your password database (including its path) 
 * make sure you don't include the home path unless you've disabled use_home_dir_src */

const Bool use_home_dir_src = True;
const Bool use_home_dir_dst = True;

const Bool verbose = True;
const Bool testing = False;

/* the %s will be replaced by the time at which the backup takes place */ 
struct filebackup_data mfa_auth_backup =
{
	"export.2fa",
	"2fa/%s-2fa.2fa",
	"2fa",
	True,
	True,
	True
};
struct filebackup_data aegis_backup =
{
	"aegis.json",
	"2fa/%s-aegis.json",
	"2fa",
	True,
	True,
	True
};
struct filebackup_data passwords_files =
{
	"passwords.kdbx",
	"passwords/%s-passwords.kdbx",
	"passwords",
	True,
	True,
	True
};
struct filebackup_data bookmarks_files =
{
	"bookmarks.json",
	"bookmarks/%s-bookmarks.json",
	"bookmarks",
	True,
	True,
	True
};
struct filebackup_data gitconfig_files =
{
	".gitconfig",
	"git/.%s-gitconfig",
	"git",
	True,
	True,
	True
};
struct filebackup_data dns_logs_files =
{
	"logs/dns.log",
	"dns-logs/%s-dns.log",
	"dns-logs",
	True,
	True,
	True
};
struct filebackup_data wifi_logs_files =
{
	"logs/wifi_log.log",
	"logs/%s-wifi.log",
	"logs",
	True,
	True,
	True
};
struct filebackup_data nvim_conf_files =
{
	"~/.config/nvim/init.lua",
	"config/nvim/%s-init.lua",
	"config/nvim",
	True,
	False,
	True
};
struct filebackup_data sway_conf_files =
{
	"~/.config/sway/config",
	"config/sway/%s-config",
	"config/sway",
	True,
	False,
	True
};
