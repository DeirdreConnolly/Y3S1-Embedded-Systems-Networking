#include "contiki.h"
#include <stdio.h>

PROCESS (helloworld, "Hello");
AUTOSTART_PROCESSES (&helloworld);

PROCESS_THREAD (helloworld, ev, data)
{
	PROCESS_BEGIN();

	printf ("Hello world\n");

	PROCESS_END();
}
