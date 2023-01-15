This Arduino Library reads a CPPM (aka. PPM SUM) signal from any pin using hardware interrupts.

Reading of only 1 signal is supported at the moment. Do not try to call attachCPPM() more than once!

If you need higher resolution than what micros() provides, uncomment #define CPPM_USE_TIMER1 in the header file.

## Changelog
- V0.2 now out. increased resolution to 0.5us on 16MHz & to 1us on 8MHz by using timer1 instead of micros()
- V0.3 Bugfixes
- V0.4 Immediate Servo output beta
- V0.5 Small bugfixes & sync pulses raised to 710us
- V1.1.0 Changed to using PCINT, made a library out of it


## Issues
Please report any issues using GitHubs Issues page

## Donate
<a href="https://paypal.me/davidhasko1/"><img src="https://www.paypalobjects.com/en_US/i/btn/btn_donate_LG.gif"></a>
If you enjoyed this project — or just feeling generous, consider buying me a beer. Cheers! :beers:
