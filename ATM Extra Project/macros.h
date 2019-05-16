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

#include <ANSI_Escapes.h>

//[LEGACY] Control Sequence Introducer
#define CSI ANSI_CSI

//[LEGACY] ReSeT text formatting
#define RST ANSI_SGR()

//[LEGACY] BoLD face
#define BLD ANSI_SGR(1)

//[LEGACY] REVerse video
#define REV ANSI_SGR(7)

//[LEGACY] BliNKing text
#define BNK ANSI_SGR(5)

//[LEGACY] RED coloured text
#define RED ANSI_SGR(ANSI_SGR_COLOUR(1))

//[LEGACY] Clear LiNe
#define CLN ANSI_EL(2)

//[LEGACY] CLear Down
#define CLD ANSI_ED(0)

//[LEGACY] Move CuRsoR 
#define MCR(row,col) ANSI_CUP(row,col)

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
