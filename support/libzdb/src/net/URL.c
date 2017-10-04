/* Generated by re2c 0.13.6 on Wed May 28 06:12:03 2014 */
#line 1 "src/net/URL.re"
/*
 * Copyright (C) Tildeslash Ltd. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 *
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.
 */


#include "Config.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "URL.h"


/**
 * Implementation of the URL interface. The scanner handle 
 * ISO Latin 1 or UTF-8 encoded url's transparently. 
 *
 * @file
 */


/* ----------------------------------------------------------- Definitions */


typedef struct param_t {
        char *name;
        char *value;
        struct param_t *next;
} *param_t;

#define T URL_T
struct URL_S {
        int ip6;
	int port;
       	char *ref;
	char *path;
	char *host;
	char *user;
        char *qptr;
	char *query;
	char *portStr;
	char *protocol;
	char *password;
	char *toString;
        param_t params;
        char **paramNames;
	uchar_t *data;
	uchar_t *buffer;
	uchar_t *marker, *ctx, *limit, *token;
        /* Keep the above align with zild URL_T */
};

/* Unsafe URL characters: [00-1F, 7F-FF] <>\"#%}{|\\^[] ` */
static const uchar_t urlunsafe[256] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

#define UNKNOWN_PORT -1
#define YYCURSOR     U->buffer
#define YYLIMIT      U->limit
#define YYTOKEN      U->token
#define SET_PROTOCOL(PORT) *(YYCURSOR-3)=0; U->protocol=U->token; U->port=PORT; goto authority


/* ------------------------------------------------------- Private methods */


static int _parseURL(T U) {
        param_t param = NULL;
	#line 127 "src/net/URL.re"

proto:
	if (YYCURSOR >= YYLIMIT)
		return false;
	YYTOKEN = YYCURSOR;
	
#line 118 "<stdout>"
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};

	yych = *U->buffer;
	if (yych <= '@') {
		if (yych <= '\r') {
			if (yych <= 0x08) goto yy9;
			if (yych <= '\n') goto yy2;
			if (yych <= '\f') goto yy9;
		} else {
			if (yych <= ' ') {
				if (yych <= 0x1F) goto yy9;
			} else {
				if (yych <= '/') goto yy9;
				if (yych <= '9') goto yy8;
				goto yy9;
			}
		}
	} else {
		if (yych <= 'm') {
			if (yych <= 'Z') goto yy8;
			if (yych <= '`') goto yy9;
			if (yych <= 'l') goto yy8;
			goto yy4;
		} else {
			if (yych <= 'o') {
				if (yych <= 'n') goto yy8;
				goto yy7;
			} else {
				if (yych <= 'p') goto yy6;
				if (yych <= 'z') goto yy8;
				goto yy9;
			}
		}
	}
yy2:
	++U->buffer;
#line 134 "src/net/URL.re"
	{
                goto proto;
         }
#line 194 "<stdout>"
yy4:
	yych = *(U->marker = ++U->buffer);
	if (yych <= 'Z') {
		if (yych <= '/') goto yy5;
		if (yych <= ':') goto yy13;
		if (yych >= 'A') goto yy13;
	} else {
		if (yych <= 'x') {
			if (yych >= 'a') goto yy13;
		} else {
			if (yych <= 'y') goto yy39;
			if (yych <= 'z') goto yy13;
		}
	}
yy5:
#line 154 "src/net/URL.re"
	{
                goto proto;
         }
#line 214 "<stdout>"
yy6:
	yych = *(U->marker = ++U->buffer);
	if (yych <= 'Z') {
		if (yych <= '/') goto yy5;
		if (yych <= ':') goto yy13;
		if (yych <= '@') goto yy5;
		goto yy13;
	} else {
		if (yych <= 'n') {
			if (yych <= '`') goto yy5;
			goto yy13;
		} else {
			if (yych <= 'o') goto yy26;
			if (yych <= 'z') goto yy13;
			goto yy5;
		}
	}
yy7:
	yych = *(U->marker = ++U->buffer);
	if (yych <= 'Z') {
		if (yych <= '/') goto yy5;
		if (yych <= ':') goto yy13;
		if (yych <= '@') goto yy5;
		goto yy13;
	} else {
		if (yych <= 'q') {
			if (yych <= '`') goto yy5;
			goto yy13;
		} else {
			if (yych <= 'r') goto yy17;
			if (yych <= 'z') goto yy13;
			goto yy5;
		}
	}
yy8:
	yych = *(U->marker = ++U->buffer);
	if (yych <= '@') {
		if (yych <= '/') goto yy5;
		if (yych <= ':') goto yy13;
		goto yy5;
	} else {
		if (yych <= 'Z') goto yy13;
		if (yych <= '`') goto yy5;
		if (yych <= 'z') goto yy13;
		goto yy5;
	}
yy9:
	yych = *++U->buffer;
	goto yy5;
yy10:
	yych = *++U->buffer;
	if (yych == '/') goto yy14;
yy11:
	U->buffer = U->marker;
	goto yy5;
yy12:
	++U->buffer;
	yych = *U->buffer;
yy13:
	if (yybm[0+yych] & 128) {
		goto yy12;
	}
	if (yych == ':') goto yy10;
	goto yy11;
yy14:
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	++U->buffer;
#line 150 "src/net/URL.re"
	{
                SET_PROTOCOL(UNKNOWN_PORT);
         }
#line 287 "<stdout>"
yy17:
	yych = *++U->buffer;
	if (yych != 'a') goto yy13;
	yych = *++U->buffer;
	if (yych != 'c') goto yy13;
	yych = *++U->buffer;
	if (yych != 'l') goto yy13;
	yych = *++U->buffer;
	if (yych != 'e') goto yy13;
	yych = *++U->buffer;
	if (yych != ':') goto yy13;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	++U->buffer;
#line 146 "src/net/URL.re"
	{
                SET_PROTOCOL(ORACLE_DEFAULT_PORT);
         }
#line 308 "<stdout>"
yy26:
	yych = *++U->buffer;
	if (yych != 's') goto yy13;
	yych = *++U->buffer;
	if (yych != 't') goto yy13;
	yych = *++U->buffer;
	if (yych != 'g') goto yy13;
	yych = *++U->buffer;
	if (yych != 'r') goto yy13;
	yych = *++U->buffer;
	if (yych != 'e') goto yy13;
	yych = *++U->buffer;
	if (yych != 's') goto yy13;
	yych = *++U->buffer;
	if (yych != 'q') goto yy13;
	yych = *++U->buffer;
	if (yych != 'l') goto yy13;
	yych = *++U->buffer;
	if (yych != ':') goto yy13;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	++U->buffer;
#line 142 "src/net/URL.re"
	{
                SET_PROTOCOL(POSTGRESQL_DEFAULT_PORT);
         }
#line 337 "<stdout>"
yy39:
	yych = *++U->buffer;
	if (yych != 's') goto yy13;
	yych = *++U->buffer;
	if (yych != 'q') goto yy13;
	yych = *++U->buffer;
	if (yych != 'l') goto yy13;
	yych = *++U->buffer;
	if (yych != ':') goto yy13;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	yych = *++U->buffer;
	if (yych != '/') goto yy11;
	++U->buffer;
#line 138 "src/net/URL.re"
	{
                SET_PROTOCOL(MYSQL_DEFAULT_PORT);
         }
#line 356 "<stdout>"
}
#line 157 "src/net/URL.re"

authority:
	if (YYCURSOR >= YYLIMIT)
		return true;
	YYTOKEN = YYCURSOR;
	
#line 365 "<stdout>"
{
	unsigned char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		 16, 112, 112,  16, 112, 116, 112, 112, 
		112, 112, 112, 112, 112, 240, 112, 112, 
		252, 252, 252, 252, 252, 252, 252, 252, 
		252, 252, 116,  16, 112, 112, 112,  16, 
		 64, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244,  64, 112,  64, 112, 112, 
		112, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244, 244, 244, 244, 244, 244, 
		244, 244, 244, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
		112, 112, 112, 112, 112, 112, 112, 112, 
	};
	yych = *U->buffer;
	if (yych <= '/') {
		if (yych <= 0x1F) {
			if (yych <= '\n') {
				if (yych <= 0x08) goto yy60;
			} else {
				if (yych != '\r') goto yy60;
			}
		} else {
			if (yych <= ',') {
				if (yych <= ' ') goto yy51;
				goto yy52;
			} else {
				if (yych <= '-') goto yy54;
				if (yych <= '.') goto yy52;
				goto yy56;
			}
		}
	} else {
		if (yych <= 'Z') {
			if (yych <= ':') {
				if (yych <= '9') goto yy54;
				goto yy58;
			} else {
				if (yych <= '?') goto yy52;
				if (yych <= '@') goto yy60;
				goto yy54;
			}
		} else {
			if (yych <= ']') {
				if (yych <= '[') goto yy59;
				if (yych <= '\\') goto yy52;
				goto yy60;
			} else {
				if (yych <= '`') goto yy52;
				if (yych <= 'z') goto yy54;
				goto yy52;
			}
		}
	}
	++U->buffer;
yy50:
#line 164 "src/net/URL.re"
	{
                goto authority;
         }
#line 449 "<stdout>"
yy51:
	yyaccept = 0;
	yych = *(U->marker = ++U->buffer);
	if (yych <= '[') {
		if (yych <= 0x1F) goto yy50;
		if (yych <= 'Z') goto yy72;
		goto yy50;
	} else {
		if (yych == ']') goto yy50;
		goto yy72;
	}
yy52:
	yyaccept = 1;
	yych = *(U->marker = ++U->buffer);
	if (yych <= '[') {
		if (yych <= 0x1F) goto yy53;
		if (yych <= 'Z') goto yy72;
	} else {
		if (yych != ']') goto yy72;
	}
yy53:
#line 209 "src/net/URL.re"
	{
                return true;
         }
#line 475 "<stdout>"
yy54:
	yyaccept = 2;
	yych = *(U->marker = ++U->buffer);
	if (yybm[0+yych] & 128) {
		goto yy82;
	}
	if (yych <= 'Z') {
		if (yych <= 0x1F) goto yy55;
		if (yych == '.') goto yy81;
		goto yy72;
	} else {
		if (yych == '\\') goto yy72;
		if (yych >= '^') goto yy72;
	}
yy55:
#line 186 "src/net/URL.re"
	{
                U->host = Str_ndup(YYTOKEN, (int)(YYCURSOR - YYTOKEN));
                goto authority;
         }
#line 496 "<stdout>"
yy56:
	yyaccept = 3;
	yych = *(U->marker = ++U->buffer);
	if (yybm[0+yych] & 32) {
		goto yy73;
	}
	if (yych <= 0x1F) goto yy57;
	if (yych <= '>') goto yy71;
	if (yych <= '?') goto yy78;
	if (yych <= '@') goto yy75;
	goto yy76;
yy57:
#line 197 "src/net/URL.re"
	{
                *YYCURSOR = 0;
                U->path = URL_unescape(YYTOKEN);
                return true;
         }
#line 515 "<stdout>"
yy58:
	yyaccept = 1;
	yych = *(U->marker = ++U->buffer);
	if (yybm[0+yych] & 8) {
		goto yy66;
	}
	if (yych <= '[') {
		if (yych <= 0x1F) goto yy53;
		if (yych <= 'Z') goto yy72;
		goto yy53;
	} else {
		if (yych == ']') goto yy53;
		goto yy72;
	}
yy59:
	yyaccept = 1;
	yych = *(U->marker = ++U->buffer);
	if (yybm[0+yych] & 4) {
		goto yy61;
	}
	goto yy53;
yy60:
	yych = *++U->buffer;
	goto yy53;
yy61:
	++U->buffer;
	yych = *U->buffer;
	if (yybm[0+yych] & 4) {
		goto yy61;
	}
	if (yych == ']') goto yy64;
yy63:
	U->buffer = U->marker;
	if (yyaccept <= 2) {
		if (yyaccept <= 1) {
			if (yyaccept == 0) {
				goto yy50;
			} else {
				goto yy53;
			}
		} else {
			goto yy55;
		}
	} else {
		if (yyaccept <= 4) {
			if (yyaccept == 3) {
				goto yy57;
			} else {
				goto yy68;
			}
		} else {
			goto yy79;
		}
	}
yy64:
	++U->buffer;
#line 180 "src/net/URL.re"
	{
                U->ip6 = true;
                U->host = Str_ndup(YYTOKEN + 1, (int)(YYCURSOR - YYTOKEN - 2));
                goto authority;
         }
#line 578 "<stdout>"
yy66:
	yyaccept = 4;
	U->marker = ++U->buffer;
	yych = *U->buffer;
	if (yybm[0+yych] & 8) {
		goto yy66;
	}
	if (yych <= 'Z') {
		if (yych <= 0x1F) goto yy68;
		if (yych == '@') goto yy69;
		goto yy71;
	} else {
		if (yych == '\\') goto yy71;
		if (yych >= '^') goto yy71;
	}
yy68:
#line 191 "src/net/URL.re"
	{
                U->portStr = YYTOKEN + 1; // read past ':'
                U->port = Str_parseInt(U->portStr);
                goto authority;
         }
#line 601 "<stdout>"
yy69:
	++U->buffer;
yy70:
#line 168 "src/net/URL.re"
	{
                *(YYCURSOR - 1) = 0;
                U->user = YYTOKEN;
                char *p = strchr(U->user, ':');
                if (p) {
                        *(p++) = 0;
                        U->password = URL_unescape(p);
                }
                URL_unescape(U->user);
                goto authority;
         }
#line 617 "<stdout>"
yy71:
	++U->buffer;
	yych = *U->buffer;
yy72:
	if (yybm[0+yych] & 16) {
		goto yy71;
	}
	if (yych == '@') goto yy69;
	goto yy63;
yy73:
	yyaccept = 3;
	U->marker = ++U->buffer;
	yych = *U->buffer;
	if (yybm[0+yych] & 32) {
		goto yy73;
	}
	if (yych <= 0x1F) goto yy57;
	if (yych <= '>') goto yy71;
	if (yych <= '?') goto yy78;
	if (yych >= 'A') goto yy76;
yy75:
	yych = *++U->buffer;
	if (yych <= '#') {
		if (yych <= ' ') goto yy70;
		if (yych <= '"') goto yy77;
		goto yy70;
	} else {
		if (yych == ';') goto yy70;
		goto yy77;
	}
yy76:
	++U->buffer;
	yych = *U->buffer;
yy77:
	if (yybm[0+yych] & 64) {
		goto yy76;
	}
	if (yych <= '>') goto yy57;
	goto yy80;
yy78:
	yyaccept = 5;
	yych = *(U->marker = ++U->buffer);
	if (yych <= '[') {
		if (yych <= 0x1F) goto yy79;
		if (yych <= 'Z') goto yy72;
	} else {
		if (yych != ']') goto yy72;
	}
yy79:
#line 203 "src/net/URL.re"
	{
                *(YYCURSOR-1) = 0;
                U->path = URL_unescape(YYTOKEN);
                goto query;
         }
#line 673 "<stdout>"
yy80:
	yych = *++U->buffer;
	goto yy79;
yy81:
	++U->buffer;
	yych = *U->buffer;
	if (yych <= '@') {
		if (yych <= '-') {
			if (yych <= 0x1F) goto yy63;
			if (yych <= ',') goto yy71;
			goto yy84;
		} else {
			if (yych <= '/') goto yy71;
			if (yych <= '9') goto yy84;
			if (yych <= '?') goto yy71;
			goto yy69;
		}
	} else {
		if (yych <= '\\') {
			if (yych <= 'Z') goto yy84;
			if (yych <= '[') goto yy63;
			goto yy71;
		} else {
			if (yych <= ']') goto yy63;
			if (yych <= '`') goto yy71;
			if (yych <= 'z') goto yy84;
			goto yy71;
		}
	}
yy82:
	yyaccept = 2;
	U->marker = ++U->buffer;
	yych = *U->buffer;
	if (yybm[0+yych] & 128) {
		goto yy82;
	}
	if (yych <= '?') {
		if (yych <= 0x1F) goto yy55;
		if (yych == '.') goto yy81;
		goto yy71;
	} else {
		if (yych <= '[') {
			if (yych <= '@') goto yy69;
			goto yy55;
		} else {
			if (yych == ']') goto yy55;
			goto yy71;
		}
	}
yy84:
	yyaccept = 2;
	U->marker = ++U->buffer;
	yych = *U->buffer;
	if (yych <= '?') {
		if (yych <= '-') {
			if (yych <= 0x1F) goto yy55;
			if (yych <= ',') goto yy71;
			goto yy84;
		} else {
			if (yych <= '.') goto yy81;
			if (yych <= '/') goto yy71;
			if (yych <= '9') goto yy84;
			goto yy71;
		}
	} else {
		if (yych <= '\\') {
			if (yych <= '@') goto yy69;
			if (yych <= 'Z') goto yy84;
			if (yych <= '[') goto yy55;
			goto yy71;
		} else {
			if (yych <= ']') goto yy55;
			if (yych <= '`') goto yy71;
			if (yych <= 'z') goto yy84;
			goto yy71;
		}
	}
}
#line 212 "src/net/URL.re"

query:
        if (YYCURSOR >= YYLIMIT)
		return true;
	YYTOKEN =  YYCURSOR;
	
#line 759 "<stdout>"
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128,   0, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	yych = *U->buffer;
	if (yych <= 0x1F) goto yy90;
	if (yych == '#') goto yy90;
	goto yy89;
yy88:
#line 219 "src/net/URL.re"
	{
                *YYCURSOR = 0;
                U->query = Str_ndup(YYTOKEN, (int)(YYCURSOR - YYTOKEN));
                YYCURSOR = YYTOKEN; // backtrack to start of query string after terminating it and
                goto params;
         }
#line 808 "<stdout>"
yy89:
	yych = *++U->buffer;
	goto yy93;
yy90:
	++U->buffer;
#line 226 "src/net/URL.re"
	{
                return true;
         }
#line 818 "<stdout>"
yy92:
	++U->buffer;
	yych = *U->buffer;
yy93:
	if (yybm[0+yych] & 128) {
		goto yy92;
	}
	goto yy88;
}
#line 229 "src/net/URL.re"

params:
	if (YYCURSOR >= YYLIMIT)
		return true;
	YYTOKEN =  YYCURSOR;
	
#line 835 "<stdout>"
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		 64, 192, 192, 192, 192, 192, 128, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192,  64, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
	};
	yych = *U->buffer;
	if (yych <= ' ') goto yy100;
	if (yych == '=') goto yy98;
	U->ctx = U->buffer + 1;
	yych = *(U->marker = ++U->buffer);
	if (yych >= '!') goto yy107;
yy97:
#line 254 "src/net/URL.re"
	{
                return true;
         }
#line 883 "<stdout>"
yy98:
	++U->buffer;
	yych = *U->buffer;
	goto yy102;
yy99:
#line 244 "src/net/URL.re"
	{
                *YYTOKEN++ = 0;
                if (*(YYCURSOR - 1) == '&')
                        *(YYCURSOR - 1) = 0;
                if (! param) // format error
                        return true; 
                param->value = URL_unescape(YYTOKEN);
                goto params;
         }
#line 899 "<stdout>"
yy100:
	yych = *++U->buffer;
	goto yy97;
yy101:
	++U->buffer;
	yych = *U->buffer;
yy102:
	if (yybm[0+yych] & 64) {
		goto yy101;
	}
	if (yych <= '%') goto yy99;
	yych = *++U->buffer;
	goto yy99;
yy104:
	++U->buffer;
	U->buffer = U->ctx;
#line 236 "src/net/URL.re"
	{
                NEW(param);
                param->name = YYTOKEN;
                param->next = U->params;
                U->params = param;
                goto params;
         }
#line 924 "<stdout>"
yy106:
	U->ctx = U->buffer + 1;
	++U->buffer;
	yych = *U->buffer;
yy107:
	if (yybm[0+yych] & 128) {
		goto yy106;
	}
	if (yych >= '=') goto yy104;
	U->buffer = U->marker;
	goto yy97;
}
#line 257 "src/net/URL.re"

        return false;
}


static inline int _x2b(uchar_t *x) {
	register int b;
	b = ((x[0] >= 'A') ? ((x[0] & 0xdf) - 'A')+10 : (x[0] - '0'));
	b *= 16;
	b += (x[1] >= 'A' ? ((x[1] & 0xdf) - 'A')+10 : (x[1] - '0'));
	return b;
}


static inline uchar_t *_b2x(uchar_t b, uchar_t *x) {
        static const char _b2x_table[] = "0123456789ABCDEF";
        *x++ = '%';
        *x++ = _b2x_table[b >> 4];
        *x = _b2x_table[b & 0xf];
        return x;
}


static void _freeParams(param_t p) {
        for (param_t q = NULL; p; p = q) {
                q = p->next;
                FREE(p);
        }
}


static T _ctor(uchar_t *data) {
        T U;
	NEW(U);
	U->data = data;
	YYCURSOR = U->data;
	U->port = UNKNOWN_PORT;
	YYLIMIT = U->data + strlen(U->data);
	if (! _parseURL(U))
                URL_free(&U);
	return U;
}


/* -------------------------------------------------------- Public methods */


T URL_new(const char *url) {
        if (STR_UNDEF(url))
                return NULL;
        Exception_init();
        return _ctor((uchar_t*)Str_dup(url));
}


T URL_create(const char *url, ...) {
        if (STR_UNDEF(url))
                return NULL;
        Exception_init();
	va_list ap;
        va_start(ap, url);
	T U = _ctor((uchar_t*)Str_vcat(url, ap));
  	va_end(ap);
        return U;
}

void URL_free(T *U) {
	assert(U && *U);
        _freeParams((*U)->params);
        FREE((*U)->paramNames);
	FREE((*U)->toString);
	FREE((*U)->query);
	FREE((*U)->data);
	FREE((*U)->host);
	FREE(*U);
}


/* ------------------------------------------------------------ Properties */


const char *URL_getProtocol(T U) {
	assert(U);
	return U->protocol;
}


const char *URL_getUser(T U) {
	assert(U);
	return U->user;
}


const char *URL_getPassword(T U) {
	assert(U);
	return U->password;
}


const char *URL_getHost(T U) {
	assert(U);
	return U->host;
}


int URL_getPort(T U) {
	assert(U);
	return U->port;
}


const char *URL_getPath(T U) {
	assert(U);
	return U->path;
}


const char *URL_getQueryString(T U) {
	assert(U);
	return U->query;
}


const char **URL_getParameterNames(T U) {
        assert(U);
        if (U->params && (U->paramNames == NULL)) {
                param_t p;
                int i = 0, len = 0;
                for (p = U->params; p; p = p->next) len++;
                U->paramNames = ALLOC((len + 1) * sizeof *(U->paramNames));
                for (p = U->params; p; p = p->next)
                        U->paramNames[i++] = p->name;
                U->paramNames[i] = NULL;
        }
	return (const char **)U->paramNames;
}


const char *URL_getParameter(T U, const char *name) {
	assert(U);
        assert(name);
        for (param_t p = U->params; p; p = p->next) {
                if (Str_isByteEqual(p->name, name))
                        return p->value;
        }
        return NULL;
}


/* ---------------------------------------------------------------- Public */


const char *URL_toString(T U) {
	assert(U);
	if (! U->toString) {
                uchar_t port[11] = {};
                if (U->portStr) // port seen in URL
                        snprintf(port, 10, ":%d", U->port);
		U->toString = Str_cat("%s://%s%s%s%s%s%s%s%s%s%s%s",
                                      U->protocol,
                                      U->user ? U->user : "",
                                      U->password ? ":" : "",
                                      U->password ? U->password : "",
                                      U->user ? "@" : "",
                                      U->ip6 ? "[" : "",
                                      U->host ? U->host : "",
                                      U->ip6 ? "]" : "",
                                      port,
                                      U->path ? U->path : "",
                                      U->query ? "?" : "",
                                      U->query ? U->query : ""); 
	}
	return U->toString;
}


/* --------------------------------------------------------- Class methods */


char *URL_unescape(char *url) {
	if (STR_DEF(url)) {
                register int x, y;
                for (x = 0, y = 0; url[y]; x++, y++) {
                        if ((url[x] = url[y]) == '+')
                                url[x] = ' ';
                        else if (url[x] == '%') {
                                if (! (url[x + 1] && url[x + 2]))
                                        break;
                                url[x] = _x2b(url + y + 1);
                                y += 2;
                        }
                }
                url[x] = 0;
        }
	return url;
}


char *URL_escape(const char *url) {
        char *escaped = 0;
        if (url) {
                char *p;
                int i, n;
                for (n = i = 0; url[i]; i++) 
                        if (urlunsafe[(unsigned char)(url[i])]) 
                                n += 2;
                p = escaped = ALLOC(i + n + 1);
                for (; *url; url++, p++) {
                        if (urlunsafe[(unsigned char)(*p = *url)])
                                p = _b2x(*url, p);
                }
                *p = 0;
        }
        return escaped;
}

