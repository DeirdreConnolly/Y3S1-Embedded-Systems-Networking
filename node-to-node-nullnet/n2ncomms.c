
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

//Global Variables
int dist_root = -1;	// Distance to the root
linkaddr_t pref_parent;	// Preferred parent 


static uint8_t received = 0;
void nullnet_receive (const void *data, uint16_t len,
                      const linkaddr_t *src, const linkaddr_t *dest)
{
//  LOG_INFO ("Received from");
//  LOG_INFO_LLADDR (src);
//  LOG_INFO (" %u ", ((uint8_t*)data)[0]);
//  LOG_INFO (" %s ", (char*)(data+1));
//  LOG_INFO ("\n");
//  received ++;

uint8_t dist_parent = ((uint8_t*)data[0]	// * casting, changing the type


 
LOG_INFO ("Callback"); 

buffer[0] = dist_root;

NETSTACK_NETWORK.output(NULL);

LOG_INFO (uint8_t)


 }





}

PROCESS_THREAD (n2ncomms, ev, data)
{
  // All of this executed every time a new event is received.
  // Also variables here will be visible to the entire thread.
  // Static variables maintain their value between function calls.
  static struct etimer periodic_timer;
  static uint8_t count = 0;
  //static linkaddr_t dest_addr;
  static uint8_t buffer[10];

  PROCESS_BEGIN ();

  // Variables declared here will be visible to the whole thread
  // ONLY on first run

  // We set the destination address to our address + 1
  //memcpy(&dest_addr, &linkaddr_node_addr, sizeof(linkaddr_t));
  //dest_addr.u8[0] += 1;
  //dest_addr.u8[1] += 1;
  //dest_addr.u8[2] += 1;
  //dest_addr.u8[4] += 1;
  // Setup the nullnet buffer (the packet buffer)
  nullnet_buf = buffer;
  nullnet_len = 1;  // Nullnet packet is 10B
  buffer[0] = dist_root; // First byte in packet will be the counter
  strcpy((char*)(buffer+1), "Alohomora"); // Some filler in the remainder
  // buffer[10] = 0; // Null terminate the string
  
  // Setup a callback for receiving nullnet packets
  nullnet_set_input_callback (nullnet_receive);

  if (linkaddr_node_addr.u8[0] == 1) {	// parent
  	dist_root = 0; // parent always 0

  
  
  
  

    // Same thing for all other instructions included here
      etimer_set(&periodic_timer,
          CLOCK_SECOND + (random_rand()%(CLOCK_SECOND>>3)));

    while (count < 100) { // Loop forever
      // Wait for the timer to expire and generate an event
      PROCESS_WAIT_EVENT_UNTIL (etimer_expired(&periodic_timer));

      // Send the nullnet buffer directly to MAC
      // Parameter is destination address
      NETSTACK_NETWORK.output(NULL);	// To broadcast: .output(NULL); To dest: (&dest_addr);
      LOG_INFO ("Sent to ");
      //LOG_INFO_LLADDR (&dest_addr);
      LOG_INFO ("\n");

      count ++;
      buffer[0] = count;
      etimer_reset(&periodic_timer);
    }
  }
  PROCESS_END ();
}
