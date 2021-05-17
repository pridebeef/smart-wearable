/*
 * wifi configuration:
 * this is an ugly solution and should probably be rewritten to use
 * https://github.com/tzapu/WiFiManager
 * or something that doesn't bake it into the device to where you could
 * easily pull the memory and check the strings
 * (or put it in the build flags but that's also pullable from strings)
 * 
 */

#define WIFI_N_SSID "YOUR SSID HERE"
#define WIFI_N_PASS "YOUR PASS HERE"
#define RECV_PORT   3000