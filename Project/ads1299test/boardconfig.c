#include "boardconfig.h"
#include "ads1299.h"

void ads1299GpioInit()
{
	bcm2835_gpio_fsel(ADS1299_CS_PIN, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(ADS1299_RST_PIN, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(ADS1299_DRDY_PIN, BCM2835_GPIO_FSEL_INPT);

	ADS1299_CS_HIGH();
	ADS1299_RST_HIGH();

	//  with a pullup
	bcm2835_gpio_set_pud(ADS1299_DRDY_PIN, BCM2835_GPIO_PUD_UP);
	// And a falling edge enable
	bcm2835_gpio_fen(ADS1299_DRDY_PIN);
}

