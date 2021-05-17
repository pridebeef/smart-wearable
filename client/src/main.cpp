#include <ESP8266WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFiUdp.h>
#include "wifi_config.h"
 
#include "images/chains.h"
#include "images/droplets.h"
#include "images/fox.h"
#include "images/lock.h"
#include "images/stars.h"

TFT_eSPI tft = TFT_eSPI();
WiFiUDP UDP;
char udp_buf[255];

#define d2r    0.0174532925 // degrees to radians
#define WIDTH  240
#define HEIGHT 135

const uint8_t cx = WIDTH  / 2;
const uint8_t cy = HEIGHT / 2;

// global state
uint8_t pause = 0;
uint8_t mode = 0;
uint8_t modecontext = 0;
uint8_t draw_flag = 0;

void     set_mode_from_udp();
void     draw_modes();
int      conc_ring(int width, int frequency, int offset);
void     draw_once(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *data);
void     draw_once_centered(int16_t w, int16_t h, const uint16_t *data);

void setup(void) 
{
	tft.begin();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);
	tft.setSwapBytes(true);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.setTextSize(3);

	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	WiFi.begin(WIFI_N_SSID, WIFI_N_PASS);
	WiFi.mode(WIFI_STA);

	// loading dots
	int n_dots = 1;
	char message[15]; // connecting...\0 at most
	sprintf(message, "connecting   ");
	while (WiFi.status() != WL_CONNECTED) {
		for (int i = 0; i < 3; i++) {
			if (i <= n_dots) {
				message[i + 10] = '.';
			} else {
				message[i + 10] = ' ';
			}
		}
		tft.drawString(message, 10, 40);
		n_dots = (n_dots + 1) % 3;
		delay(200);
	}

	UDP.begin(RECV_PORT);
	tft.fillScreen(TFT_BLACK);
}

void loop() 
{	
	uint8_t oldmode = mode;
	set_mode_from_udp();

	if (!pause) {
		draw_modes();
	}

	if (oldmode != mode) {
		tft.fillScreen(TFT_BLACK);
		pause = 0;
		draw_flag = 0;
	}
}

void set_mode_from_udp()
{
	int packet_size = UDP.parsePacket();
	if (packet_size) {
		int len = UDP.read(udp_buf, 255);
		if (len > 0)
  		{
    		udp_buf[len] = '\0';
  		}
  		mode = udp_buf[0] - 1;
	}
}

void draw_modes()
{
	if (mode == 0) {
		tft.setTextSize(3);
		tft.drawString(WiFi.localIP().toString(), 10, 40);
		char portstr[10];
		sprintf(portstr, "port: %d", RECV_PORT);
		tft.drawString(portstr, 10, 80);
	}
	if (mode == 1) {
		draw_once_centered(stars_width, stars_height, (const uint16_t*)stars);
	}
	if (mode == 2) {
		modecontext = conc_ring(20, 30, modecontext);
	}
	if (mode == 3) {
		modecontext = conc_ring(20, 40, modecontext);
	}
	if (mode == 4) {
		draw_once_centered(lock_width, lock_height, (const uint16_t*)lock);
	}
	if (mode == 5) {
		draw_once_centered(chains_width, chains_height, (const uint16_t*)chains);
	}
	if (mode == 6) {
		draw_once_centered(droplets_width, droplets_height, (const uint16_t*)droplets);
	}
	if (mode == 7) {

	}
	if (mode == 8) {
		draw_once_centered(fox_width, fox_height, (const uint16_t*)fox);
	}
}

int conc_ring(int width, int frequency, int offset) 
{
	for (int r = -width; r < 140; r += frequency){
	tft.drawEllipse(
		cx,
		cy,
		max(r + offset, 0),
		max(r + offset, 0),
		TFT_WHITE
		);
	tft.drawEllipse(
		cx,
		cy,
		r + offset + width,
		r + offset + width,
		TFT_BLACK
		);
	}
	offset += 1;
	offset = offset % frequency;
	return offset;
}

void draw_once_centered(int16_t w, int16_t h, const uint16_t *data)
{
	int16_t x = (WIDTH  - w) / 2;
	int16_t y = (HEIGHT - h) / 2;
	draw_once(x, y, w, h, data);
}

void draw_once(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t *data)
{
	if (!draw_flag) {
		tft.pushImage(x, y, w, h, data);
		draw_flag = 1;
	}
}