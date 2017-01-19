/*
 * escposf - send or embed printing control data for an ESC/POS format thermal printer.
 *
 * (c)2016 by bball@tux.org for his Raspberry Pi 3 computer's thermal printer
 * Distributed under GNU GPLV3. Get it, read it, use it, love it.
 *
 * note that not all ESC/POS-compatible printers share the same ESC/POS codes!
 *
 * the primary use of this command is to set the printing mode or embed ESC/POS codes
 * into a text stream or file for printing
 * 
 * version 0.1 - working bold, underline, alignment, reverse, and 4 types of text types
 * version 0.2 - changed name from escpos_util to escposf (ESC/POS filter)
 *               added font a/b selection, overstrike
 * version 0.3 - added printer initialization (clear buffer, reset to 'standard' mode)
 * version 0.4 - added code cleanup, printer_test shell script to package
 * version 0.5 - removed non-working options (boldface, double-strike)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* additions for command-line processing */
#include <getopt.h>
/* #include <argp.h> */  /* <-- comment out header to build for Mac OS X */

/* command-line help */
const char *version="escposf 0.5";
const char *bug_address="<bball@tux.org>";
static char doc[]="ESC/POS thermal printer command";

void usage() {
printf("%s - %s\n",version,doc);
printf("Control ESC/POS thermal printer output.\n");
printf("Typical usage:\n");
printf("escposf --a 1 | lpr -P lpname -o raw (set text centering)\n");
printf("escposf --f 1 >filename.txt          (embed font selection)\n");
printf("Command-line options are:\n");
printf("[--align n]  [--a n] - align text (0-left, 1-ctr, 2-rght)\n");
printf("[--font n]   [--f n] - select font (0-normal, 1-condensed)\n");
printf("[--init]     [--i]   - reset [initialize] printer\n");
printf("[--rev n]    [--r n] - reverse text (0-off, 1-on)\n");
printf("[--text n]   [--t n] - set text (0-norm, 1-2Xh, 2-2Xw, 3-large)\n");
printf("[--underl n] [--u n] - underline (0-off, 1-1 dot, 2-2 dots)\n");
printf("[--help]     [--h]   - display this message \n");
printf("[--version]  [--v]   - display program version \n");
printf("bug reports, fixes to: %s\n",bug_address);
}

/* control alignment */
int align(int option)
{
    switch (option) {
        case 0: putchar(0x1b); putchar(0x61); putchar(0x00); exit(0); break; 
        case 1: putchar(0x1b); putchar(0x61); putchar(0x01); exit(0); break;
        case 2: putchar(0x1b); putchar(0x61); putchar(0x02); exit(0); break;
    }
    printf("ERROR: align option out of range (0-2).\n");
    exit(0);  
}

/* reset, initialize printer */
void init() { putchar(0x1b); putchar(0x40); }

/* control font type (normal, condensed) */
int font(int option)
{
    switch (option) {
        case 0: putchar(0x1b); putchar(0x4d); putchar(0x00); exit(0); break; 
        case 1: putchar(0x1b); putchar(0x4d); putchar(0x01); exit(0); break;
    }
    printf("ERROR: font-selection option out of range (0 or 1).\n");
    exit(0);  
}

/* control reverse text */
int reverse(int option)
{
    switch (option) {
        case 0: putchar(0x1d); putchar(0x42); putchar(0x00); exit(0); break; 
        case 1: putchar(0x1d); putchar(0x42); putchar(0x01); exit(0); break;
    }
    printf("ERROR: reverse text option out of range (0 or 1).\n");
    exit(0);  
}

/* control underlining */
int underline(int option)
{
    switch (option) {
        case 0: putchar(0x1b); putchar(0x2d); putchar(0x00); exit(0); break; 
        case 1: putchar(0x1b); putchar(0x2d); putchar(0x01); exit(0); break;
        case 2: putchar(0x1b); putchar(0x2d); putchar(0x02); exit(0); break;
    }
    printf("ERROR: underline option out of range (0-2).\n");
    exit(0);  
}

/* control text type */
int text(int option)
{
    switch (option) {
        case 0: putchar(0x1b); putchar(0x21); putchar(0x00); exit(0); break; 
        case 1: putchar(0x1b); putchar(0x21); putchar(0x10); exit(0); break;
        case 2: putchar(0x1b); putchar(0x21); putchar(0x20); exit(0); break;
        case 3: putchar(0x1b); putchar(0x21); putchar(0x30); exit(0); break; 
    }
    printf("ERROR: text option out of range (0-3).\n");
    exit(0);  
}

int main(int argc, char *argv[]) {

    int c = 0;
        static struct option long_options[] = {
            {"align", 1, 0, 'a'},
            {"font", 1, 0, 'f'},
            {"help", 0, 0, 'h'},
            {"init", 0, 0, 'i'},
        {"rev", 1,0, 'r'},
            {"text", 1, 0, 't'},
            {"underl", 1, 0, 'u'},
            {"version", 0, 0, 'v'}
    }; /* end of long options structure */

    while (1) {
        c = getopt_long(argc, argv, "?:a:f:h:i:r:t:u:v:", long_options, 0);
        if (c == -1) {  usage();  break; }
        switch(c) {
            case 'a': align(atoi(optarg)); break;
            case 'f': font(atoi(optarg)); break;
            case 'h': usage(); exit(0); break;
            case 'i': init(); exit(0); break;
            case 'r': reverse(atoi(optarg)); break;
            case 't': text(atoi(optarg)); break;
            case 'u': underline(atoi(optarg)); break;
            case 'v': printf("%s - %s\n",version,doc); exit(0); break;
        case ':': fprintf(stderr, "missing arg\n"); exit(-1); break;
             default: usage(); exit(0); 
        } /* end switch */
    } /* end while loop */
  return 0;
}
