			case 'I':
				std::cout
					<< "ATMEXTRA.CPP" << std::endl
					<< "COMPILED ON " __DATE__ " AT " __TIME__ << std::endl
					<< "USING STANDARD " << __cplusplus
					<< " AS PROVIDED BY:" << std::endl
					<< //CONCAT WITH ONE OF THE FOLLOWING:
#ifdef __MINGW32__
	"Minimalist GNU for Windows "
	#ifdef __MINGW64__
		" (x86-64) "
	#endif
	__MINGW32__
#else
	#ifdef __GNUC__
		#ifdef __clang__
			"Clang " __clang_version__
		#else
			"GNU C Compiler " __GNUC__ "." __GNUC_MINOR__ "." __GNUC_PATCHLEVEL__
		#endif
	#else
		#ifdef _MSC_VER
			#ifdef __WATCOMC__
				"Watcom " __WATCOMC__
			#else
				"Microsoft C/C++ " << _MSC_VER <<
			#endif
		#endif
	#endif
#endif
					CSI "4F" CSI "2K";
				goto imenu_prompt;
