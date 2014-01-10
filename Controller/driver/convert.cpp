#define __STDC_FORMAT_MACROS
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoull */
#include <inttypes.h>

int main ()
{
  char szNumbers[] = "F0F0F0F002";
 char szNumbers2[10];



unsigned long long int ulli1, ulli2;
  ulli1 = strtoull (szNumbers, NULL, 16);
sprintf(szNumbers2,"%" PRIx64, ulli1);

printf ("The decimal equivalents are: %llu.\n %i\n", ulli1,sizeof(szNumbers));
	for(int i = 0; i < 11; i++){
		printf("%x %c\n", szNumbers2[i],szNumbers2[i]);
	}
ulli2 = strtoull (szNumbers2, NULL, 16);
printf ("The decimal equivalents are: %llu.\n %i\n", ulli2,sizeof(szNumbers2));


 

return 0;
}



