#define __STDC_FORMAT_MACROS
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoull */
#include <inttypes.h>

int main ()
{
  char szNumbers[] = "F0F0F0F001";
 char szNumbers2[11];



unsigned long long int ulli1, ulli2;
  ulli1 = strtoull (szNumbers, NULL, 16);
sprintf(szNumbers2,"%" PRIx64, ulli1);

printf ("The decimal equivalents are: %llu.\n %i\n", ulli1,sizeof(szNumbers));
	for(int i = 0; i < 10; i++){
		printf("%c\n", szNumbers2[i]);
	}
ulli2 = strtoull (szNumbers2, NULL, 16);
printf ("The decimal equivalents are: %llu.\n %i\n", ulli2,sizeof(szNumbers2));


 

return 0;
}




/*#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include "./librf24/RF24.h"
#include <inttypes.h>


uint64_t pipe1 = 0xF0F0F0F001LL;
uint64_t pipe2 = 0xF0F0F0F002LL;

char test[10];
char *out=&test[0];

int main(int argc, char* argv[])
{
	sprintf(out,"%" PRIx64, pipe1);
	pipe2 = strtoull(out, NULL, 0);
	printf ("%llu\n",pipe1);
	printf ("%llu\n",pipe2);

	return 0;


}
*/
