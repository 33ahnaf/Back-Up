#ifndef _LGFX_HELPER__H
#define _LGFX_HELPER__H

#include "globals.h"
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// Define a custom setup configuration class derived from LGFX_Device
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ILI9341 _panel_instance;
    lgfx::Bus_SPI       _bus_instance;

public:
    LGFX(void) {
        { // Configure the SPI Bus
            auto cfg = _bus_instance.config();

            cfg.spi_host = SPI2_HOST;     // ESP32-S3 uses SPI2_HOST (FSPI) or SPI3_HOST (HSPI)
            cfg.spi_mode = 0;             // SPI Mode 0
            cfg.freq_write = TFT_WRITE_FREQUENCY;    // Write clock speed (40MHz is highly stable for ILI9341)
            cfg.freq_read  = 16000000;    // Read clock speed
            cfg.spi_3wire = true;         // Use true if MISO is shared or not utilized
            cfg.use_lock = true;          // Protect transfers with transaction locks
            cfg.dma_channel = SPI_DMA_CH_AUTO; // Automatically allocate DMA channel
      
            // Pin assignments
            cfg.pin_sclk = TFT_SCLK;            // Clock
            cfg.pin_mosi = TFT_MOSI;            // MOSI
            cfg.pin_miso = TFT_MISO;            // MISO (set to -1 if unused)
            cfg.pin_dc   = TFT_DC;             // Data / Command Pin

            _bus_instance.config(cfg);    // Apply configurations to the bus
            _panel_instance.setBus(&_bus_instance); // Bind bus to panel
        }

        { // Configure the Display Panel
            auto cfg = _panel_instance.config();

            cfg.pin_cs           = TFT_CS;    // Chip Select pin
            cfg.pin_rst          = TFT_RST;     // Reset pin
            cfg.pin_busy         = -1;    // Not required for ILI9341
      
            cfg.memory_width     = LGFX_DEFINATION_WIDTH;   // Physical panel width
            cfg.memory_height    = LGFX_DEFINATION_HEIGHT;   // Physical panel height
            cfg.panel_width      = LGFX_DEFINATION_WIDTH;   // Display area width
            cfg.panel_height     = LGFX_DEFINATION_HEIGHT;   // Display area height
            cfg.offset_x         = 0;     // X axis shift adjustment
            cfg.offset_y         = 0;     // Y axis shift adjustment
      
            cfg.rgb_order        = false; // Set true if colors are swapped (BGR vs RGB)
            cfg.invert           = false; // Set true if colors appear inverted
            cfg.bus_shared       = true;  // Set true if sharing the SPI bus with an SD Card or Touch IC

            _panel_instance.config(cfg);  // Apply configurations to the panel
        }
        
        setPanel(&_panel_instance);     // Bind initialized panel to the main driver
    }
};

// Create an instance of your custom display
extern LGFX tft;

#endif