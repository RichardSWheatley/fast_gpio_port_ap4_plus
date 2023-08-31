//*****************************************************************************
//
//! @file main.c
//!
//! @brief Example demonstrating Fast GPIO
//!
//! Purpose: This example demonstrates how to use Fast GPIO on Apollo4. The
//! example updates the LEDs with waveforms that can be observed with a logic
//! analyzer.
//!
//! Printing takes place over the ITM at 1M Baud.
//!
//! @author Mariusz Lacina, Ambiq
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "apollo4p.h"
#include "am_bsp.h"
#include "am_util.h"

//=============================================================================
//
//  FAST GPIO PORT
//
//=============================================================================
#define GPIO_FGPIO_0    0
#define GPIO_FGPIO_1    1
#define GPIO_FGPIO_2    2
#define GPIO_FGPIO_3    3
#define GPIO_FGPIO_4    4
#define GPIO_FGPIO_5    5
#define GPIO_FGPIO_6    6
#define GPIO_FGPIO_7    7
#define GPIO_FGPIO_8    8
#define GPIO_FGPIO_9    9
#define GPIO_FGPIO_10    10
#define GPIO_FGPIO_11    11
#define GPIO_FGPIO_12    12
#define GPIO_FGPIO_13    13
#define GPIO_FGPIO_14    14
#define GPIO_FGPIO_15    15

const am_hal_gpio_pincfg_t g_GPIO_FGPIO_OUTPUT =
{
    .GP.cfg_b.uFuncSel        = 11,
    .GP.cfg_b.eGPInput        = AM_HAL_GPIO_PIN_INPUT_ENABLE, //can be disbled in output mode
    .GP.cfg_b.eGPOutCfg       = AM_HAL_GPIO_PIN_OUTCFG_PUSHPULL,
    .GP.cfg_b.eDriveStrength  = AM_HAL_GPIO_PIN_DRIVESTRENGTH_0P1X,
    .GP.cfg_b.ePullup         = AM_HAL_GPIO_PIN_PULLUP_NONE, 
    .GP.cfg_b.eGPRdZero       = false,
};

const am_hal_gpio_pincfg_t g_GPIO_FGPIO_INPUT =
{
    .GP.cfg_b.uFuncSel        = 11,
    .GP.cfg_b.eGPInput        = AM_HAL_GPIO_PIN_INPUT_ENABLE,
    .GP.cfg_b.eGPOutCfg       = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
    .GP.cfg_b.eDriveStrength  = AM_HAL_GPIO_PIN_DRIVESTRENGTH_0P1X,
    .GP.cfg_b.ePullup         = AM_HAL_GPIO_PIN_PULLUP_6K,//AM_HAL_GPIO_PIN_PULLDOWN_50K
    .GP.cfg_b.eGPRdZero       = false,
};

//=============================================================================
//  GPIO CONFIG
//=============================================================================
void
gpio_config ( bool output )
{
    if ( output )
    {
        am_hal_gpio_pinconfig(GPIO_FGPIO_0, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_1, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_2, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_3, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_4, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_5, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_6, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_7, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_8, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_9, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_10, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_11, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_12, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_13, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_14, g_GPIO_FGPIO_OUTPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_15, g_GPIO_FGPIO_OUTPUT);
    }
    else
    {
        am_hal_gpio_pinconfig(GPIO_FGPIO_0, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_1, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_2, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_3, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_4, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_5, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_6, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_7, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_8, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_9, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_10, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_11, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_12, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_13, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_14, g_GPIO_FGPIO_INPUT);
        am_hal_gpio_pinconfig(GPIO_FGPIO_15, g_GPIO_FGPIO_INPUT);
    }
}

//=============================================================================
//
// Fast write
//
//=============================================================================
void
fgpio_write ( uint32_t data )
{
    FPIO->WT0 = data;
}

//=============================================================================
//
// Fast read
//
//=============================================================================
uint32_t
fgpio_read ( void )
{
    return(FPIO->RD0);
}

//=============================================================================
//
// Memory config
//
//=============================================================================
void
memory_config ( void )
{
    const am_hal_pwrctrl_mcu_memory_config_t McuMemCfg =
    {
        .eCacheCfg    = AM_HAL_PWRCTRL_CACHE_ALL,
        .bRetainCache = true,
        .eDTCMCfg     = AM_HAL_PWRCTRL_DTCM_384K,
        .eRetainDTCM  = AM_HAL_PWRCTRL_DTCM_384K,
        .bEnableNVM0  = true,
        .bRetainNVM0  = false
    };

    const am_hal_pwrctrl_sram_memcfg_t SRAMMemCfg =
    {
        .eSRAMCfg         = AM_HAL_PWRCTRL_SRAM_ALL,
        .eActiveWithMCU   = AM_HAL_PWRCTRL_SRAM_NONE,
        .eActiveWithDSP   = AM_HAL_PWRCTRL_SRAM_NONE,
        .eSRAMRetain      = AM_HAL_PWRCTRL_SRAM_ALL
    };

    const am_hal_pwrctrl_dsp_memory_config_t ExtSRAMMemCfg =
    {
        .bEnableICache      = false,  //Should always be "false"
        .bRetainCache       = false,  //Should always be "false"
        .bEnableRAM         = false,  //Controls Extended RAM power when MCU awake
        .bActiveRAM         = false,  //Should be "false"
        .bRetainRAM         = false   //true configures Extended RAM to be retained in deep sleep
    };

    am_hal_pwrctrl_mcu_memory_config(&McuMemCfg);
    am_hal_pwrctrl_sram_config(&SRAMMemCfg);
    am_hal_pwrctrl_dsp_memory_config(AM_HAL_DSP0, &ExtSRAMMemCfg);
    am_hal_pwrctrl_dsp_memory_config(AM_HAL_DSP1, &ExtSRAMMemCfg);
}

//=============================================================================
//
// Main function.
//
//=============================================================================
int
main ( void )
{
    uint32_t wr_data = 0XAAAA, rd_data;

    //
    // Set the default cache configuration
    //
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();

    //
    // Configure the board for low power operation.
    //
    am_bsp_low_power_init();

    //
    // Configure the memory 
    //
    memory_config();

    //
    // Enable printing to the console.
    //
    am_bsp_debug_printf_enable();
    am_util_stdio_printf("\nApollo4 Plus fast GPIO demo!\r\n");

    //
    // GPIO config
    //
    gpio_config(true);

#if SPEED_TEST
	//
	// Speed test loop
	//
    while(1)
    {
        fgpio_write(0xaaaa);
        __NOP();

        fgpio_write(0x5555);
        __NOP();
    }
#else
    //
    // Loop forever.
    //
    while (1)
    {
        fgpio_write(wr_data);  //write to output
        if(wr_data == 0XAAAA)
        {
            wr_data=0X5555;
        }

        gpio_config(false);  //switch off output drivers, pull-ups or pull-down can be active
        rd_data = fgpio_read();

        gpio_config(true);  //switch on output drivers, pull-ups or pull-down can be active
        rd_data = fgpio_read();

        am_util_delay_ms(100);
    }
#endif
} // main()
