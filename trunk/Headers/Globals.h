#ifndef _GLOBALS

    #define _GLOBALS

// Application constants
    #if defined(Q_OS_LINUX)
        const char eol = '\n';
    #endif

    #if defined(Q_OS_WIN)
        const char eol = '\n';
    #endif

    #if defined(Q_OS_MAC)
        const char eol = '\r';
    #endif

    const QString _PROGRAMDOI_          = "doi:10.1594/PANGAEA.758968";
    const QString _PROGRAMREADME_       = "https://wiki.pangaea.de/wiki/MultibeamConverter";

    const QString _VERSION_	            = "2.2";	// Version number, 2015-12-28
    const QChar	  _PSEPARATOR_			= '|';

    const int	_NOERROR_				= 0;
    const int	_ERROR_					= 1;
    const int	_APPBREAK_				= 2;
    const int	_NODATAFOUND_			= 3;
    const int	_DATAFOUND_				= 4;
    const int   _CHOOSEABORTED_         = 5;
    const int   _FILENOTEXISTS_         = 6;

    const int	_ZIP_					= 1;
    const int	_GZIP_					= 2;

// EOL
    const int   _UNIX_                  = 0;    // LF
    const int   _MACOS_                 = 1;    // CR
    const int   _WIN_                   = 2;    // CR+LF

// Encoding
    const int   _SYSTEM_                = -1;   // System
    const int   _UTF8_                  = 0;    // UTF-8
    const int   _APPLEROMAN_            = 1;    // Apple Roman
    const int   _LATIN1_                = 2;    // Latin-1 = ISO 8859-1

// Extension
    const int   _TXT_                   = 0;
    const int   _CSV_                   = 1;

#endif
