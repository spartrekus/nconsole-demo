

// libs for more
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <ncurses.h>
#include <time.h>


int rows, cols;  

////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}


////////////////////////////////
void nruncmd( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}


////////////////////////
char *strninput( char *myinitstring )
{
   int strninput_gameover = 0; 
   char strmsg[PATH_MAX];
   char charo[PATH_MAX];
   strncpy( strmsg, myinitstring , PATH_MAX );
   int ch ;  int foo ; 
   int fooj; 
   while ( strninput_gameover == 0 )
   {
                  getmaxyx( stdscr, rows, cols);
                  attroff( A_REVERSE );
                  for ( fooj = 0 ; fooj <= cols-1;  fooj++)
                  {
                    mvaddch( rows-2, fooj , ' ' );
                    mvaddch( rows-1, fooj , ' ' );
                  }
                  mvprintw( rows-1, 0, ":> %s" , strrlf( strmsg ) );
                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  refresh() ; ch = getch();
		  if ( ch == 127  ) 
		  {
			   strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
		  }
		  else if ( ch == 4  ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
		  else if ( ch == 27  ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  else if ( ch == 10 ) 
		  {
                        strninput_gameover = 1;
		  }
     }
     char ptr[PATH_MAX];
     strncpy( ptr, strmsg, PATH_MAX );
     size_t siz = sizeof ptr ; 
     char *r = malloc( sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}



void drawit()
{
        getmaxyx( stdscr, rows, cols);
        erase();
        mvprintw( 0, 0, "|CONSOLE DEMO|" );
}


void makro_create_slides()
{
   FILE *fp;
   fp = fopen( "slides.bmr" , "ab+" );
         fputs( "!include{beamer.mrk}\n" , fp );
         fputs( "!beamer\n" , fp );
         fputs( "!title Slides\n" , fp );
         fputs( "!author Username\n" , fp );
         fputs( "!gpath{figs/}\n" , fp );
         fputs( "!begin\n" , fp );
         fputs( "!cover\n" , fp );
         fputs( "!clr\n" , fp );
         fputs( "= Header\n" , fp );
         fputs( "> line1\n" , fp );
         fputs( "- item1\n" , fp );
         fputs( "- item2\n" , fp );
         fputs( "\n" , fp );
         fputs( "!enddoc\n" , fp );
   fclose( fp );
}




///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
   initscr();			
   curs_set( 0 );
   start_color();
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
   init_pair(4, COLOR_CYAN, COLOR_BLACK);
   color_set( 2, NULL );

   int ch ; 
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   char userinp[PATH_MAX];
   int gameover_nsc = 0;
   while ( gameover_nsc == 0)
   {
           drawit();
	   refresh();			/* Print it on to the real screen */
           ch = getch();

           if ( ch == 'q' ) gameover_nsc =1 ;
           else if ( ch == ':' ) 
           {
                strncpy( userinp, strninput( "" ), PATH_MAX );
                if ( strcmp( userinp, "create slides" ) == 0 )
                     makro_create_slides();
                else if ( strcmp( userinp, "quit" ) == 0 )
                     gameover_nsc =1 ;
                else if ( strcmp( userinp, "exit" ) == 0 )
                     gameover_nsc =1 ;
                else if ( strcmp( userinp, "edit slides" ) == 0 )
                     nruncmd( " vim slides.bmr" );
                else if ( strcmp( userinp, "make slides" ) == 0 )
                     nruncmd( " unibeam slides.bmr slides.tex ; pdflatex -shell-escape slides.tex ; mupdf slides.pdf " );
           }
 
    }

    curs_set( 1 );
    endwin();			/* End curses mode		  */
    return 0;
}



