// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "../common/mmo.h" // NAME_LENGTH,SEX_*
#include "../common/core.h" // CORE_ST_LAST

enum E_LOGINSERVER_ST
{
	LOGINSERVER_ST_RUNNING = CORE_ST_LAST,
	LOGINSERVER_ST_SHUTDOWN,
	LOGINSERVER_ST_LAST
};

#define LOGIN_CONF_NAME "conf/login_athena.conf"
#define LAN_CONF_NAME "conf/subnet_athena.conf"

// supported encryption types: 1- passwordencrypt, 2- passwordencrypt2, 3- both
#define PASSWORDENC 3

struct login_session_data {

	int account_id;
	long login_id1;
	long login_id2;
	char sex;// 'F','M','S'

	char userid[NAME_LENGTH];
	char passwd[32+1]; // 23+1 for plaintext, 32+1 for md5-ed passwords
	int passwdenc;
	char md5key[20];
	uint16 md5keylen;

	char lastlogin[24];
	uint8 level;
	uint8 clienttype;
	uint32 version;

	int fd;
};

struct mmo_char_server {

	char name[20];
	int fd;
	uint32 ip;
	uint16 port;
	uint16 users;       // user count on this server
	uint16 type;        // 0=normal, 1=maintenance, 2=over 18, 3=paying, 4=P2P
	uint16 new_;        // should display as 'new'?
};

struct Login_Config {

	uint32 login_ip;                                // the address to bind to
	uint16 login_port;                              // the port to bind to
	unsigned int ipban_cleanup_interval;            // interval (in seconds) to clean up expired IP bans
	unsigned int ip_sync_interval;                  // interval (in minutes) to execute a DNS/IP update (for dynamic IPs)
	bool log_login;                                 // whether to log login server actions or not
	char date_format[32];                           // date format used in messages
	bool console;                                   // console input system enabled?
	bool new_account_flag,new_acc_length_limit;     // autoregistration via _M/_F ? / if yes minimum length is 4?
	int start_limited_time;                         // new account expiration time (-1: unlimited)
	bool use_md5_passwds;                           // work with password hashes instead of plaintext passwords?
	int min_level_to_connect;                       // minimum level of player/GM (0: player, 1-99: GM) to connect
	bool check_client_version;                      // check the clientversion set in the clientinfo ?
	uint32 client_version_to_connect;               // the client version needed to connect (if checking is enabled)

	bool ipban;                                     // perform IP blocking (via contents of `ipbanlist`) ?
	bool dynamic_pass_failure_ban;                  // automatic IP blocking due to failed login attemps ?
	unsigned int dynamic_pass_failure_ban_interval; // how far to scan the loginlog for password failures
	unsigned int dynamic_pass_failure_ban_limit;    // number of failures needed to trigger the ipban
	unsigned int dynamic_pass_failure_ban_duration; // duration of the ipban
	bool use_dnsbl;                                 // dns blacklist blocking ?
	char dnsbl_servs[1024];                         // comma-separated list of dnsbl servers

	char account_engine[256];                       // name of the engine to use (defaults to auto, for the first available engine)
};

#define sex_num2str(num) ( (num ==  SEX_FEMALE  ) ? 'F' : (num ==  SEX_MALE  ) ? 'M' : 'S' )
#define sex_str2num(str) ( (str == 'F' ) ?  SEX_FEMALE  : (str == 'M' ) ?  SEX_MALE  :  SEX_SERVER  )

#define MAX_SERVERS 30
extern struct mmo_char_server server[MAX_SERVERS];
extern struct Login_Config login_config;


#endif /* _LOGIN_H_ */
