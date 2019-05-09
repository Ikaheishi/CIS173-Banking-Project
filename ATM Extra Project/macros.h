/** macros.h
 *	Preprocessor macro definitions that are (more) commonly used throughout the program.
 */

 //Name of the program
#define APPNAME "ATMEXTRA"

//Width of the terminal (TODO: swap this for adaptive implemention)
#define TERM_WIDTH 80

//Height of the terminal (TODO: swap this for adaptive implemention)
#define TERM_HEIGHT 24

//============================================
//	ANSI escape Sequences
//============================================

//Command Sequence Inducer
#define CSI "\033["
//#define CSI "\e["

//ReSeT text formatting
#define RST CSI "0m"

//BoLD face
#define BLD CSI "1m"

//REVerse video
#define REV CSI "7m"

//BliNKing text
#define BNK CSI "5m"

//RED coloured text
#define RED CSI "31m"

//Clear LiNe
#define CLN CSI "2K"

//CLear Down
#define CLD CSI "0J"

//Move CuRsoR
#define MCR(row,col) CSI #row ";" #col "H"
