#include <syslog.h>


class Syslog { 
	public:
		Syslog




void openlog( char *ident, int option, int  facility)

void syslog( int priority, char *format, ...)

void closelog( void )
}
