#include "contiki.h"
#include <stdio.h>

PROCESS (helloworld, "Hello");
AUTOSTART_PROCESSES (&helloworld);

/**
 * Setting a timer: etimer_set (struct etimer *timer, timelength)
 * Reset a timer:   etimer_reset (struct etimer *timer);
 * Has a timer expired? etimer_expired (struct etimer *timer);
 */
struct etimer timer;

PROCESS_THREAD (helloworld, ev, data)
{
	PROCESS_BEGIN();

	etimer_set (&timer, CLOCK_SECOND);

	printf ("Hello world\n");

	while (1){
		PROCESS_WAIT_UNTIL (etimer_expired(&timer));
		printf ("Timers\n");
		etimer_reset(&timer);
	}

	PROCESS_END();
}
