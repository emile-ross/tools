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
	"backup/2fa/%s-2fa.2fa",
	True,
	True,
	True
};
struct filebackup_data aegis_backup =
{
	"aegis.json",
	"%s-aegis.json",
	True,
	True,
	True
};
struct filebackup_data passwords_files =
{
	"passwords.kdbx",
	"backup/passwords/%s-passwords.kdbx",
	True,
	True,
	True
};
struct filebackup_data bookmarks_files =
{
	"bookmarks.json",
	"backup/bookmarks/%s-bookmarks.json",
	True,
	True,
	True
};
struct filebackup_data gitconfig_files =
{
	".gitconfig",
	"backup/git/.%s-gitconfig",
	True,
	True,
	True
};
struct filebackup_data dns_logs_files =
{
	"logs/dns.log",
	"backup/dns-logs/%s-dns.log",
	True,
	True,
	True
};
struct filebackup_data wifi_logs_files =
{
	"logs/wifi_log.log",
	"backup/logs/%s-wifi.log",
	True,
	True,
	True
};

