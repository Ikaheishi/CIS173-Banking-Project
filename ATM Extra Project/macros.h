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
#define ANSI_CSI "\033["

#define CSI ANSI_CSI
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

//CUrsor Position (ANSI escape sequence H)
#define ANSI_CUP(row,col) CSI #row ";" #col "H"

//Move CuRsoR 
#define MCR(row,col) ANSI_CUP(#row,#col)

//Cursor Horizontal Absloute (ANSI escape sequence G)
#define ANSI_CHA(col) CSI #col "G"

#define ANSI_CODE_CHA "G"

//CUrsor Up (ANSI escape sequence A)
#define ANSI_CUU(col) CSI #col "A"

#define ANSI_CODE_CUU "A"

//CUrsor Down (ANSI escape sequence B)
#define ANSI_CUD(col) CSI #col "B"

#define ANSI_CODE_CUD "B"

//CUrsor Forward (ANSI escape sequence C)
#define ANSI_CUF(col) CSI #col "C"

#define ANSI_CODE_CUF "C"

//CUrsor Back (ANSI escape sequence D)
#define ANSI_CUB(col) CSI #col "D"

#define ANSI_CODE_CUB "D"

//============================================
//	Non-ASCII characters
//============================================

//Terminal borders
#if _UNICODE
#define CHR_BORDER_TOP			"═"
#define CHR_BORDER_BOTTOM		"═"
#define CHR_BORDER_LEFT			"║"
#define CHR_BORDER_RIGHT		"║"
#define CHR_BORDER_CORNER_TR	"╗"
#define CHR_BORDER_CORNER_TL	"╔"
#define CHR_BORDER_CORNER_BR	"╝"
#define CHR_BORDER_CORNER_BL	"╚"
#define CHR_BORDER_TEE_UP		" "
#define CHR_BORDER_TEE_LEFT		" "
#define CHR_BORDER_TEE_RIGHT	" "
#define CHR_BORDER_TEE_DOWN		" "
#else
#define CHR_BORDER_TOP			"-"
#define CHR_BORDER_BOTTOM		"-"
#define CHR_BORDER_LEFT			"|"
#define CHR_BORDER_RIGHT		"|"
#define CHR_BORDER_CORNER_TR	"\\"
#define CHR_BORDER_CORNER_TL	"/"
#define CHR_BORDER_CORNER_BR	"/"
#define CHR_BORDER_CORNER_BL	"\\"
#define CHR_BORDER_TEE_UP		"+"
#define CHR_BORDER_TEE_LEFT		"+"
#define CHR_BORDER_TEE_RIGHT	"+"
#define CHR_BORDER_TEE_DOWN		"+"
#endif // _UNICODE
