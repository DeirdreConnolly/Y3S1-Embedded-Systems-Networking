#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"

#include "lib/random.h"
#include <string.h>
#include <stdio.h>

#include "sys/log.h"
#define LOG_MODULE "Test"
#define LOG_LEVEL LOG_LEVEL_INFO

PROCESS (n2ncomms, "N2N Comms");
AUTOSTART_PROCESSES (&n2ncomms);

static uint8_t received = 0;
void nullnet_receive (const void *data, uint16_t len,
                      const linkaddr_t *src, const linkaddr_t *dest)
{
  LOG_INFO ("Received from ");
  LOG_INFO_LLADDR (src);
  LOG_INFO (" %s ", (char*)(data));
  LOG_INFO ("\n");
  received ++;
}

PROCESS_THREAD (n2ncomms, ev, data)
{
  // All of this executed every time a new event is received.
  // Also variables here will be visible to the entire thread.
  // Static variables maintain their value between function calls.
  static struct etimer periodic_timer;
  static uint8_t count = 0;
  static linkaddr_t dest_addr;
  static uint8_t buffer[10];

  PROCESS_BEGIN ();

  // Setup the nullnet buffer (the packet buffer)
  nullnet_buf = buffer;
  nullnet_len = 10;  // Nullnet packet is 10B
  strcpy((char*)buffer, "TSCHRulz"); // Some filler in the remainder
  buffer[8] = 0; // Null terminate the string
  // Setup a callback for receiving nullnet packets
  nullnet_set_input_callback (nullnet_receive);

  // Same thing for all other instructions included here
  etimer_set(&periodic_timer,
      CLOCK_SECOND + (random_rand()%(CLOCK_SECOND>>3)));

  while (1) { // Loop forever
    // Wait for the timer to expire and generate an event
    PROCESS_WAIT_EVENT_UNTIL (etimer_expired(&periodic_timer));

    // Send the nullnet buffer directly to MAC
    // Parameter is destination address
    NETSTACK_NETWORK.output(NULL);

    etimer_reset(&periodic_timer);
  }
  PROCESS_END ();
}
