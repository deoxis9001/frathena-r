
COMMON_OBJ = ../common/obj_all/core.o ../common/obj_all/socket.o ../common/obj_all/timer.o \
	../common/obj_all/db.o ../common/obj_all/plugins.o ../common/obj_all/lock.o \
	../common/obj_all/malloc.o ../common/obj_all/showmsg.o ../common/obj_all/utils.o \
	../common/obj_all/strlib.o ../common/obj_all/grfio.o ../common/obj_all/mapindex.o \
	../common/obj_all/ers.o ../common/obj_all/md5calc.o ../common/obj_all/random.o
COMMON_H = ../common/core.h ../common/socket.h ../common/timer.h ../common/mmo.h \
	../common/version.h ../common/db.h ../common/plugins.h ../common/lock.h \
	../common/malloc.h ../common/showmsg.h ../common/utils.h ../common/strlib.h \
	../common/grfio.h ../common/mapindex.h \
	../common/ers.h ../common/md5calc.h ../common/random.h

COMMON_SQL_OBJ = ../common/obj_sql/sql.o
COMMON_SQL_H = ../common/sql.h

MT19937AR_OBJ = ../../3rdparty/mt19937ar/mt19937ar.o
MT19937AR_H = ../../3rdparty/mt19937ar/mt19937ar.h
MT19937AR_INCLUDE = -I../../3rdparty/mt19937ar

LOGIN_OBJ = login.o
LOGIN_SQL_OBJ = $(LOGIN_OBJ:%=obj_sql/%) \
	obj_sql/account.o obj_sql/ipban.o obj_sql/loginlog.o
LOGIN_H = login.h account.h ipban.h loginlog.h

HAVE_MYSQL=yes
ifeq ($(HAVE_MYSQL),yes)
	LOGIN_SERVER_SQL_DEPENDS=obj_sql $(LOGIN_SQL_OBJ) $(COMMON_OBJ) $(COMMON_SQL_OBJ) $(MT19937AR_OBJ)
else
	LOGIN_SERVER_SQL_DEPENDS=needs_mysql
endif



#####################################################################
.PHONY :all sql clean help

all: sql

sql: obj_sql login-server_sql

clean:
	rm -rf *.o obj_sql ../../login-server_sql

help:
	@echo "possible targets are 'sql' 'all' 'clean' 'help'"
	@echo "'sql'       - login server (SQL version)"
	@echo "'all'       - builds all above targets"
	@echo "'clean'     - cleans builds and objects"
	@echo "'help'      - outputs this message"

#####################################################################

needs_mysql:
	@echo "MySQL not found or disabled by the configure script"
	@exit 1

# object directories
obj_sql:
	test -d obj_sql || mkdir obj_sql

#executables
login-server_sql: $(LOGIN_SERVER_SQL_DEPENDS)
	gcc  -L/usr/lib -o ../../login-server_sql $(LOGIN_SQL_OBJ) $(COMMON_OBJ) $(COMMON_SQL_OBJ) $(MT19937AR_OBJ) -lrt -lm -lz  -ldl -L/usr/lib/mysql -lmysqlclient

# login object files
obj_sql/%.o: %.c $(LOGIN_H) $(COMMON_H) $(MT19937AR_H)
	gcc -g -O2 -pipe -ffast-math -Wall -Wno-sign-compare -Wno-unused-parameter -Wno-pointer-sign -Wno-switch -fno-strict-aliasing -DHAVE_SETRLIMIT -DHAVE_STRNLEN -Wno-unused -Wno-parentheses -DHAVE_MONOTONIC_CLOCK $(MT19937AR_INCLUDE) -DWITH_SQL -I/usr/include/mysql  -I../common -I/usr/include -c -fno-strict-aliasing $(OUTPUT_OPTION) $<

# missing object files
../common/obj_all/%.o:
	@$(MAKE) -C ../common sql

MT19937AR_OBJ:
	@$(MAKE) -C ../../3rdparty/mt19937ar
