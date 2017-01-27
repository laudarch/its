# include "c/c.defs"
# include "c/stdio.h"

/**********************************************************************

	STDIO.C	- 'Standard I/O' Simulator

	Note: Must call	STDIO to initialize.
	Note: Must #include "c/stdio.h".
	** Not complete. **

	Routines implemented, either here, by redefinition (in STDIO.H),
	or in the default ITS library:

	fileptr	= fopen	(name, mode)
	fileptr	= freopen (name, mode, fileptr)
	c = getc (fileptr)
	c = fgetc (fileptr)
	c = putc (c, fileptr)
	c = fputc (f, fileptr)
	fclose (fileptr)
	fflush (fileptr)
	exit (errcode)
	b = feof (fileptr)
	c = getchar ()
	putchar	(c)
	s = gets (s)
	s = fgets (s, n, fileptr)
	puts (s)
	fputs (s, fileptr)
	ungetc (c, fileptr)
	printf (format,	a1, ...)
		NOTE: restricted formats (see below)
	fprintf	(fileptr, format, a1, ...)
	sprintf	(buf, format, a1, ...)
	fread (ptr, itemsize, nitems, fileptr)
		NOTE: reads characters,	not words
	fwrite (ptr, itemsize, nitems, fileptr)
		NOTE: reads characters,	not words
	rewind (fileptr)
	unlink (s)
	i = strcmp (s1,	s2)
	strcpy (dest, source)
	strcat (dest, source)
	i = strlen (s)
	b = isalpha (c)
	b = isupper (c)
	b = islower (c)
	b = isdigit (c)
	b = isspace (c)
	c = toupper (c)
	c = tolower (c)
	uid = getuid ()
	buf = getpw (uid, buf)
		- writes user name into	buf
	time (int[2])
		- write	current	time into array
	s = ctime (int[2])
		- convert time to string format
	p = calloc (num, size)

	See <C.LIB>CPRINT.C for information about PRINTF formats.

**********************************************************************/

int *stdin, *stdout, *stderr;
extern int cin,	cout, cerr;

stdio ()

	{stdin = cin; stdout = cout; stderr = cerr;
	on (ctrlg_interrupt, INT_IGNORE);
	}

fopen (name, mode) /* this is renamed */
	char *name, *mode;

	{int f;
	f = copen (name, mode[0]);
	if (f == OPENLOSS) return (NULL);
	return (f);
	}

int fgetc (f)

	{int c;
	c = cgetc (f);
	if (c <	0) return (EOF);
	if (c == 0 && ceof (f))	return (EOF);
	return (c);
	}

int getchar () /* this is renamed */

	{return	(fgetc (cin));}

int peekc (f)

	{int c;
	c = cgetc (f);
	if (c <	0) return (EOF);
	if (c == 0 && ceof (f))	return (EOF);
	ungetc (c, f);
	return (c);
	}

int pkchar ()

	{return	(peekc (cin));}

char *fgets (s,	n, f)
	char *s;
	FILE *f;

	{char *sp; int c;
	sp = s;
	while (--n > 0 && (c = fgetc(f)) != EOF)
		if ((*sp++ = c)	== '\n') break;
	*sp = 0;
	if (c == EOF &&	sp == s) return	(NULL);
	return (s);
	}

fputs (s, f)
	char *s;
	FILE *f;

	{int c;
	while (c = *s++) fputc (c, f);
	}

printf (a, b, c, d, e, f, g)
	{cprint	(cout, a, b, c,	d, e, f, g);}

fprintf	(a, b, c, d, e,	f, g) /* this is renamed */
	{cprint	(a, b, c, d, e,	f, g);}

sprintf	(s, a, b, c, d,	e, f, g)
	char *s;
	{int fp;
	fp = copen (s, 'w', "s");
	cprint (fp, a, b, c, d,	e, f, g);
	cclose (fp);
	}

fclose (f) {cclose (f);}

fread (buf, size, number, f) char buf[]; FILE *f;

	{int n;
	n = size * number;
	while (--n >= 0) *buf++	= cgetc	(f);
	}

fwrite (buf, size, number, f) char buf[]; FILE *f;

	{int n;
	n = size * number;
	while (--n >= 0) cputc (*buf++,	f);
	}

freopen	(name, mode, f)	char *name, *mode;

	{int i;
	cclose (f);
	i = copen (name, *mode);
	if (i == OPENLOSS) return (NULL);
	return (i);
	}

/**********************************************************************

	STRING ROUTINES

**********************************************************************/

strcmp (s1, s2)
	char *s1, *s2;

	{int c1, c2;
	while (TRUE)
		{c1 = *s1++;
		c2 = *s2++;
		if (c1 < c2) return (-1);
		if (c1 > c2) return (1);
		if (c1 == 0) return (0);
		}
	}

strcpy (dest, source)
	char *dest, *source;

	{stcpy (source,	dest);}

strcat (dest, source)
	char *dest, *source;

	{while (*dest) ++dest;
	stcpy (source, dest);
	}

int strlen (s)
	char *s;

	{char *e;
	e = s;
	while (*e) ++e;
	return (e - s);
	}

/**********************************************************************

	CHARACTER ROUTINES

**********************************************************************/

int isalpha (c)
	char c;

	{return	((c >= 'a' && c	<= 'z')	|| (c >= 'A' &&	c <= 'Z'));}

int isupper (c)
	char c;

	{return	(c >= 'A' && c <= 'Z');}

int islower (c)
	char c;

	{return	(c >= 'a' && c <= 'z');}

int isdigit (c)
	char c;

	{return	(c >= '0' && c <= '9');}

int isspace (c)
	char c;

	{return	(c == '	' || c == '\t' || c == '\n' || c == '\p');}

int tolower (c)
	char c;

	{if (c >= 'A' && c <= 'Z') return (c + 32);
	return (c);
	}

int toupper (c)
	char c;

	{if (c >= 'a' && c <= 'z') return (c - 32);
	return (c);
	}

/**********************************************************************

	OBSCURE	ROUTINES

**********************************************************************/

int getuid ()
	{return (rsuset (074));}

char *getpw (w, buf) char *buf;
	{c6tos (w, buf);}

nowtime	(tv) int tv[];
	{cal foo;
	now (&foo);
	tv[0] =	tv[1] =	cal2f (&foo);
	}

char *ctime (tv) int tv[];
	{static	char buf[100];
	cal foo;
	int f;
	f2cal (tv[0], &foo);
	f = copen (buf,	'w', "s");
	prcal (&foo, f);
	cputc ('\n', f);
	cclose (f);
	return (buf);
	}

unlink (s) {delete (s);}
exit (cc) {cexit (cc);}
fflush (f) {cflush (f);}
rewind (f) {rew(f);}
char *calloc (num, size) {return (salloc (num*size));}
