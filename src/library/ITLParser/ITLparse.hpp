/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     UINT = 259,
     FLOAT = 260,
     IDENTIFIER = 261,
     EQUAL = 262,
     REGEXP = 263,
     PATHSEP = 264,
     STRING = 265,
     QUOTEDSTRING = 266,
     WATCH = 267,
     EVAL = 268,
     ERR = 269,
     ENDEXPR = 270,
     ENDSCRIPT = 271,
     VARSTART = 272,
     LEFTPAR = 273,
     RIGHTPAR = 274,
     COLON = 275,
     COMMA = 276,
     POINT = 277,
     HOSTNAME = 278,
     IPNUM = 279,
     LUASCRIPT = 280,
     JSCRIPT = 281
   };
#endif
/* Tokens.  */
#define INT 258
#define UINT 259
#define FLOAT 260
#define IDENTIFIER 261
#define EQUAL 262
#define REGEXP 263
#define PATHSEP 264
#define STRING 265
#define QUOTEDSTRING 266
#define WATCH 267
#define EVAL 268
#define ERR 269
#define ENDEXPR 270
#define ENDSCRIPT 271
#define VARSTART 272
#define LEFTPAR 273
#define RIGHTPAR 274
#define COLON 275
#define COMMA 276
#define POINT 277
#define HOSTNAME 278
#define IPNUM 279
#define LUASCRIPT 280
#define JSCRIPT 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 25 "ITL.y"
{
	int		num;
	float	real;
	std::string* str;
	inscore::ITLparser::address*	addr;
	inscore::Sbaseparam *			p;
	inscore::IMessage::argslist*	plist;
	inscore::IMessage::TUrl*		url;
	inscore::SIMessage*				msg;
	inscore::SIMessageList*			msgList;
}
/* Line 1529 of yacc.c.  */
#line 113 "ITLparse.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

