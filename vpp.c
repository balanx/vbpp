/* Copyright (C) 1996 Himanshu M. Thaker

This file is part of vpp.

Vpp is distributed in the hope that it will be useful,
but without any warranty.  No author or distributor
accepts responsibility to anyone for the consequences of using it
or for whether it serves any particular purpose or works at all,
unless he says so in writing.

Everyone is granted permission to copy, modify and redistribute
vpp, but only under the conditions described in the
document "vpp copying permission notice".   An exact copy
of the document is supposed to have been given to you along with
vpp so that you can know how you may redistribute it all.
It should be in a file named COPYING.  Among other things, the
copyright notice and this notice must be preserved on all copies.  */

/*
 * Program : vpp
 * Author : Himanshu M. Thaker
 * Date : Apr. 16, 1995
 * Description :
 */

#include "common.h"
#include "yacc_stuff.h"
#include "proto.h"
#include <string.h>
#include <stdio.h>

struct vpp_filename
	{
	struct vpp_filename *next;   
	char *name;
	};
struct vpp_filename *vpp_incdir;
int output_quite;

int
main(int argc, char *argv[])
	{
	int i, arglen;
	struct vpp_filename *t, *filehead, *filecurr, *idcurr;

#ifdef YYDEBUG
	yydebug = TRUE;
#endif

	/* Default to old behavior. */
	output_line_directive = FALSE;
	output_ifdef_directive = TRUE;

	filehead = filecurr = idcurr = NULL;
	for (i = 1; i < argc; ++i)
		{
		arglen = strlen(argv[i]);
		if (arglen >= 8 && !strncmp(argv[i],"+incdir+",8))
			{
			if (arglen == 8)
				{
				/* Perhaps we don't even need to notify user. */
				fprintf(stderr, "** No path for +incdir+ in argument %d.\n", i);
				}
			else
				{   
				char *lname, *tok;

				lname = (char *)NMALLOC(arglen-8+1, char);
				strcpy(lname, argv[i]+8);
				tok = strtok(lname, "+");
				while (tok)
					{
					int toklen = strlen(tok);
					t = CALLOC(1, struct vpp_filename);
					t->name = NMALLOC(toklen+1, char);
					strcpy(t->name, tok);
					if (!vpp_incdir)
						vpp_incdir = t;
					else
						idcurr->next = t;
					idcurr = t;
					tok = strtok(NULL, "+");
					}
				free(lname);
				}
			}
		else if (arglen >= 2 && !strncmp(argv[i], "-D", 2))
			{
			if (arglen == 2)
				{
				/* Perhaps we don't even need to notify user. */
				fprintf(stderr, "** No define for -D in argument %d.\n", i);
				}
			else
				{
				char *dname, *pnt;

				dname = NMALLOC(arglen+8, char);
				sprintf(dname, "`define %s", argv[i]+2);
				pnt = dname+8;
				while (*pnt)
					{
					if (*pnt == '=')
						{
						*pnt = ' ';
						break;
						}
					pnt++;
					}
				store_define(dname);
				free(dname);
				}
			}
		else if (arglen >= 2 && !strncmp(argv[i], "-E", 2))
			{
			/* Enable C style preprocessing of ifdef and friends. */
			output_ifdef_directive = FALSE;
			}
		else if (arglen >= 2 && !strncmp(argv[i], "-L", 2))
			{
			/* Write out `line directives for debugging. */
			output_line_directive = TRUE;
			}
		else if (arglen >= 2 && !strncmp(argv[i], "-h", 2))
			{
			printf("syntax: %s [options] filename\n", argv[0]);
			printf("options:\n");
			printf("  +incdir+...+ Search directory for `include files.\n");
			printf("  -D           Define macro.\n");
			printf("  -E           Perform C style preprocessing.\n");
			printf("  -L           Output `line directive.\n");
			printf("  -h           Print help message and exit.\n");
			printf("  -q           Suppress status message.\n");
			return 0;
			}
		else if (arglen >= 2 && !strncmp(argv[i], "-q", 2))
			{
			/* Quite, take out unnecessary output. */
			output_quite = TRUE;
			}
		else /* filename only.. */
			{
			t = CALLOC(1,struct vpp_filename);
			t->name = NMALLOC(strlen(argv[i])+1, char);
			strcpy(t->name, argv[i]);
			if (!filehead)
				filehead = t;
			else
				filecurr->next = t;
			filecurr = t;
			}
        }

	/*
	 * check to see if the file can be opened for reading...
	 */
	if (!filehead)
		{
		yyin = stdin;
		current_file = NMALLOC(strlen("<stdin>")+1, char);
		strcpy(current_file, "<stdin>");

		nl_count = 1;
		if (!output_quite)
			fprintf(stderr, "Preprocessing '%s'\n", current_file);
		do_comment_count(TRUE, nl_count);
		yyparse();
		fclose(yyin);
		free(current_file);
		}
	else
		{
		filecurr = filehead;
		while (filecurr)
			{
			yyin = fopen(filecurr->name, "r");
      		if (yyin == NULL)
				{
        		fprintf(stderr, "** %s: open failed\n", filecurr->name);
				++yyerror_count;
				}
			else
				{
      			current_file = NMALLOC(strlen(filecurr->name)+1, char);
      			strcpy(current_file, filecurr->name);

				nl_count = 1;
				if (!output_quite)
					fprintf(stderr, "Preprocessing '%s'\n", current_file);
				do_comment_count(TRUE, nl_count);
				yyparse();
				fclose(yyin);
				free(current_file);
				}

			t = filecurr;
			filecurr = filecurr->next;
			free(t->name);
			free(t);
			}

		filehead = NULL;
		}

	return yyerror_count;
	}

FILE *
incdir_fopen(char *name)
	{
	int len;
	struct vpp_filename *l;  
	char *path;
	FILE *fp = NULL;

	len = strlen(name);
	l = vpp_incdir;
	while (l)
        {
        path = (char *)malloc(strlen(l->name) + 1 + len + 1);
        sprintf(path, "%s/%s", l->name, name);
        fp = fopen(path, "r");
        free(path);
        if (fp)
			break;
		l = l->next;
        }

	if (!fp)
		fp = fopen(name, "r");
	return(fp);
	}
