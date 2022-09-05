#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"

void KEY_INIT(void)
{
    gpio_config config;

    /*IO复用GPIO1_IO18*/
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    
    /*配置IO属性*/
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    /*设置IO为输入*/
    config.direction = Gpio_Input;
    GPIO_INIT(GPIO1, 18, &config);
}

int KEY_SCAN(void)
{
    int ret = 0;
    static flag = 1;

    if(flag == 1 && GPIO_READ(GPIO1, 18) == 0)
    {
        delay(10);
        flag = 0;
        if(GPIO_READ(GPIO1, 18) == 0)
        {
            return 1;
        }
    }
    else if(GPIO_READ(GPIO1, 18) == 1)
    {
        ret = 0;
        flag = 1;
    }

    return ret;
}