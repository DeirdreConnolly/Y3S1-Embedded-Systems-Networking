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


// Global variables
linkaddr_t global_src;	// *dereferencing src
int dist_root = -1;	// Distance to the root
linkaddr_t pref_parent;	// Preferred parent 


struct ctimer reply_timer;	// Declare reply_timer


void tx_callback(void *ptr)	// Callback function
{
  LOG_INFO ("Callback\n");
  static uint8_t buffer[1];
  buffer[0] = dist_root;
  nullnet_buf = buffer;
  nullnet_len = 1;
  NETSTACK_NETWORK.output(NULL);	// To broadcast: NULL
  
  // Network output to the global variable that holds the source address
  // NETSTACK_NETWORK.output(src);	// Causes collisions, use callback instead
  // NETSTACK_NETWORK.output(&global_src);  
}


// Called when a packet is received
void nullnet_receive (const void *data, uint16_t len,
                      const linkaddr_t *src, const linkaddr_t *dest)
{


uint8_t *pktdata = (uint8_t*)data;
uint8_t pktValue = pktdata[0];
	
  
// Update distance, update parent
if (dist_root > pktValue + 1) {
	dist_root = pktValue + 1;
	pref_parent = *src;
		
	// Schedule callback for when timer expirs
  ctimer_set(&reply_timer, (random_rand()%(CLOCK_SECOND>>4)), tx_callback, NULL);
	}  
}


PROCESS_THREAD (n2ncomms, ev, data)
{
  // All of this executed every time a new event is received.
  // Also variables here will be visible to the entire thread.
  // Static variables maintain their value between function calls.
  static uint8_t buffer[10];

  PROCESS_BEGIN ();

  // Variables declared here will be visible to the whole thread
  // ONLY on first run

  // Setup the nullnet buffer (the packet buffer)
  nullnet_buf = buffer;
  nullnet_len = 10;  // Nullnet packet is 10B
  strcpy((char*)(buffer), "TSCHRulz"); // Some filler in the remainder
  buffer[8] = 0; // Null terminate the string
  // Setup a callback for receiving nullnet packets
  nullnet_set_input_callback (nullnet_receive);
  PROCESS_END ();
}
