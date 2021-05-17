# ESP8266 Apparel Attachment
Too small for a smartwatch, perfect size for a funny form of necklace.

## Dependencies (Hardware)
* Any ESP8266 board
    - I used [one of these](https://www.adafruit.com/product/2821) so the pins in the code are set for that, but it's easy to change. Wiring instructions definitely assume you're using one of those, since that's all I've tested on -- if you have a different one it shouldn't be too bad.
* Some form of TFT that communicates over SPI
    - I used [this one](https://www.adafruit.com/product/4383).
    - If you use a different one there's some stuff to change with the internal SPI library.
* Soldering tools and wire
* Some way to attach it to the apparel of choice (I sewed it through the holes on the breakout board but you can get creative)

## Build Instructions (Hardware)
Working on it, should be more detailed soon. Gotta make neat images and stuff.
Wiring is following the SPI pins as shown on the board after getting power and ground in / TX to TFTCS and RX to DC. 

## Dependencies (Software)
* Rust (nightly)
* PlatformIO

## Build Instructions (Software)
Should be pretty easy.  Hopefully.  
  
**Client:**  
Change `client/wifi_config.h` to have your SSID and password in it.  
`pio run -t upload` with your board plugged into the computer, or however the non-CLI PlatformIO tools work.  
  
**Server:**
`cd` into the server folder and `rustup set override nightly` as per Rocket's requirements for the web server, then `cargo run` and visit the URL in the browser. The Rocket config should run it on `0.0.0.0` so it will be accessible on the local network.  
  
## Usage
After uploading the client code to the board and getting the webserver built, just visit the URL for the webserver on any device on the same network and enter the client IP in the box. Then the mode buttons should work.  
  
## Troubleshooting
Ensure that all the devices are on the same local network. 