# PPM Reader

This library reads and decodes PPM (CPPM) RC signal from a radio receiver. 

* Processing is `loop` independent
* Allows to use `delay` in `loop`
* Does not conflicts with **Servo** library, that means you can not only passthrough decoded channels to servos, but also to process it in an easy way. For example to write a mixer

## Limitations

* Requires a pin with hardware interrupt avaliable. That mean, on majority of Arduino boards, it will be limitet to either Pin2/Interrupt0 or Pin3/Interrupt1
* It uses `micros`, so any code that alters `Timer0` and breaks `micros` function, will also break this code

## Usage

On Arduino UNO/Pro Mini with PPM signal attached to pin 2 (interrupt 0), example usage that prints PPM channel 1 over serial port will look like this:

```
#include "PPMReader.h"

// PPMReader(pin, interrupt)
PPMReader ppmReader(2, 0);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  static int count;
  while (ppmReader.get(count) != 0) { //print out the servo values
      rcCommand[count] = ppmReader.get(count) - 1500;
      Serial.print(ppmReader.get(count));
      Serial.print("  ");
      count++;
  }
  count = 0;
  delay(500);
}
```

## License

This code is licensed under _GNU GENERAL PUBLIC LICENSE Version 3_ and is based on [https://github.com/Hasi123/read-any-ppm](https://github.com/Hasi123/read-any-ppm) and [https://code.google.com/archive/p/read-any-ppm/](https://code.google.com/archive/p/read-any-ppm/) 