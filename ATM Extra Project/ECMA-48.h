/** ANSI_Escapes.h
 *	Preprocessor macro definitions for escapes and control sequences
 *	originally defined by the former ANSI X3.64 standard. They are currently
 *	defined by ISO/IEC 6429 after the 1994 withdrawl of X3.64, in favour of
 *	the ISO definition based on ECMA-48 (5th ed, 1991).
 */

#ifdef ANSI_USE_C1_SET
/*	CSI – Command Sequence Introducer

	The first character of a command sequence.

	• Per ECMA-48 8.3.16, CSI is in the C1 control set and as such represented
	by `09/11` (0x9B) or `ESC 05/11` (0x1B5B). This macro is currently
	defined with the direct CSI character value (i.e. for Unicode encodings).

	• To instead revert to the default ASCII-compatible definition, please
	undefine the ANSI_USE_C1_SET macro before including this header.
*/
#define ANSI_CSI "\0x9B"
#else
/*	CSI – Command Sequence Introducer

	The first character of a command sequence.

	• Per ECMA-48 8.3.16, CSI is in the C1 control set and as such represented
	by `09/11` (0x9B) or `ESC 05/11` (0x1B5B). The ANSI_CSI macro provided
	uses the Escape-[ format by default.
	
	• To instead use direct C1 control set representation (i.e. for use with a
	Unicode capable character encoding), simply define the macro
	ANSI_USE_C1_SET before including this header.
*/
#define ANSI_CSI "\033["
#endif // ANSI_USE_C1_SET


#define ANSI_CSFB_CUU "A"
/*	CUU – Cursor Up (CSI Pn A)

	Default: 1

	Moves the cursor Pn cells up.

	Behaviour is undefined if cursor is already at screen edge.
*/
#define ANSI_CUU(rows) ANSI_CSI #rows "A"


#define ANSI_CSFB_CUD "B"
/*	CUD – Cursor Down (CSI Pn B)

	Default: 1

	Moves the cursor Pn cells down.

	Behaviour is undefined if cursor is already at screen edge.
*/
#define ANSI_CUD(rows) ANSI_CSI #rows "B"


#define ANSI_CSFB_CUF "C"
/*	CUF – Cursor Forward (CSI Pn C)

	Default: 1

	Moves the cursor Pn cells to the right.

	Behaviour is undefined if cursor is already at screen edge.
*/
#define ANSI_CUF(cols) ANSI_CSI #cols "C"


#define ANSI_CSFB_CUB "D"
/*	CUB – Cursor Back (CSI Pn D)

	Default: 1

	Moves the cursor Pn cells to the left.

	Behaviour is undefined if cursor is already at the screen edge.
*/
#define ANSI_CUB(cols) ANSI_CSI #cols "D"


#define ANSI_CSFB_CNL "E"
/*	CNL – Cursor Next Line (CSI Pn E)

	Default: 1

	Move cursor to beginning of the line Pn rows downward.

	Note: Not supported by ANSI.SYS
*/
#define ANSI_CNL(lines) ANSI_CSI #lines "E"


#define ANSI_CSFB_CPL "F"
/*	CPL – Cursor Previous Line (CSI Pn F)

	Default: 1

	Move cursor to beginning of the line Pn rows upward.

	Note: Not supported by ANSI.SYS
*/
#define ANSI_CPL(lines) ANSI_CSI #lines "F"


#define ANSI_CSFB_CHA "G"
/*	CHA – Cursor Horizontal Absolute (CSI Pn G)

	Default: 1

	Moves the cursor to the column Pn.
	
	Note: Not supported by ANSI.SYS
*/
#define ANSI_CHA(cols) ANSI_CSI #cols "G"


#define ANSI_CSFB_CUP "H"
/*	CUP – Cursor Position (CSI Pn1; Pn2 H)
	Default: 1;1 (top left corner).

	Moves cursor to row Pn1, column Pn2.
	Either one (or both) of the parameters may be omitted.

	(ex: `CSI; 8H` is equivalent `CSI 1; 8H`,
	`CSI 24 ; H` is equivalent `CSI 24 ; 1 H`)
*/
#define ANSI_CUP(row,col) ANSI_CSI #row ";" #col "H"


#define ANSI_CSFB_ED "J"
/*	ED – Erase in Display (CSI Ps J)

	Default: 0

	Clear all or part of the screen.

	0 — Clear from cursor to bottom of screen.
	1 — Clear from cursor to top of screen.
	2 — Clear entire screen. (ANSI.SYS: Also moves cursor to 1,1).
	3 — [xterm] Clear entire screen and the scrollback buffer.
*/
#define ANSI_ED(mode) ANSI_CSI #mode "J" 


#define ANSI_CSFB_EL "K"
/*	EL – Erase in Line (CSI Ps K)

	Default: 0

	Clear a given portion of the current line.

	0 — Clear from cursor to end of line.
	1 — Clear from cursor to beginning of line.
	2 — Clear entire line.
*/
#define ANSI_EL(mode) ANSI_CSI #mode "K"


#define ANSI_CSFB_SU "S"
/*	SU – Scroll Up (CSI Pn S)

	Default: 1

	Scroll the entire page up by Pn lines.
	(New lines are added at the bottom.)

	Note: Not supported by ANSI.SYS
*/
#define ANSI_SU(lines) ANSI_CSI #lines "S"


#define ANSI_CSFB_SD "T"
/*	SD – Scroll Down (CSI Pn T)
	
	Default: 1
	
	Scroll the entire page down by Pn lines.
	(New lines are added at the top.)
	
	Note: Not supported by ANSI.SYS
*/
#define ANSI_SD(lines) ANSI_CSI #lines "T"


#define ANSI_CSFB_SGR "m"
/*	SGR – Select Graphic Rendition (CSI Ps… m)

	Default: 0

	Set parameters for the appearance of the following characters.

	(See ANSI_SGR_* macros.)
*/
#define ANSI_SGR(params) ANSI_CSI #params "m"

// Reset —
#define ANSI_SGR_RESET 0
// Bold —
#define ANSI_SGR_BOLD 1
// Faint —
#define ANSI_SGR_FAINT 2
// Italic —
#define ANSI_SGR_ITALIC 3
// Underline —
#define ANSI_SGR_UNDERLINE 4
// (Slow) Blink —
#define ANSI_SGR_BLINK 5
// Fast Blink —
#define ANSI_SGR_BLINK_FAST 6
// Negative (Reverse Video) —
#define ANSI_SGR_NEGATIVE 7
// Consealed —
#define ANSI_SGR_CONCEAL 8
// Crossed-Out —
#define ANSI_SGR_STRIKE 9
// Foreground Colour —
#define ANSI_SGR_COLOUR(colour_id) 3 colour_id
// Background Colour —
#define ANSI_SGR_COLOUR_BG(colour_id) 4 colour_id
