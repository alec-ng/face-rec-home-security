/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_qsys_0' in SOPC Builder design 'top_level'
 * SOPC Builder design path: C:/Users/Alec/Documents/GitHub/Home-Security/DE2/top_level.sopcinfo
 *
 * Generated: Wed Apr 08 10:07:30 PDT 2015
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * Button_3 configuration
 *
 */

#define ALT_MODULE_CLASS_Button_3 altera_avalon_pio
#define BUTTON_3_BASE 0x1081050
#define BUTTON_3_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_3_CAPTURE 0
#define BUTTON_3_DATA_WIDTH 1
#define BUTTON_3_DO_TEST_BENCH_WIRING 0
#define BUTTON_3_DRIVEN_SIM_VALUE 0
#define BUTTON_3_EDGE_TYPE "NONE"
#define BUTTON_3_FREQ 50000000
#define BUTTON_3_HAS_IN 1
#define BUTTON_3_HAS_OUT 0
#define BUTTON_3_HAS_TRI 0
#define BUTTON_3_IRQ -1
#define BUTTON_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BUTTON_3_IRQ_TYPE "NONE"
#define BUTTON_3_NAME "/dev/Button_3"
#define BUTTON_3_RESET_VALUE 0
#define BUTTON_3_SPAN 16
#define BUTTON_3_TYPE "altera_avalon_pio"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x1080820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x19
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x800020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 0x19
#define ALT_CPU_NAME "nios2_qsys_0"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x800000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x1080820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x19
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x800020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 0x19
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x800000


/*
 * DMA_Controller configuration
 *
 */

#define ALT_MODULE_CLASS_DMA_Controller altera_up_avalon_video_dma_controller
#define DMA_CONTROLLER_BASE 0x1081070
#define DMA_CONTROLLER_IRQ -1
#define DMA_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_CONTROLLER_NAME "/dev/DMA_Controller"
#define DMA_CONTROLLER_SPAN 16
#define DMA_CONTROLLER_TYPE "altera_up_avalon_video_dma_controller"


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_DMA
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_UP_AVALON_AUDIO_AND_VIDEO_CONFIG
#define __ALTERA_UP_AVALON_CHARACTER_LCD
#define __ALTERA_UP_AVALON_SRAM
#define __ALTERA_UP_AVALON_VIDEO_DMA_CONTROLLER
#define __ALTERA_UP_AVALON_VIDEO_PIXEL_BUFFER_DMA


/*
 * Frame_Save_DMA configuration
 *
 */

#define ALT_MODULE_CLASS_Frame_Save_DMA altera_avalon_dma
#define FRAME_SAVE_DMA_ALLOW_BYTE_TRANSACTIONS 1
#define FRAME_SAVE_DMA_ALLOW_DOUBLEWORD_TRANSACTIONS 1
#define FRAME_SAVE_DMA_ALLOW_HW_TRANSACTIONS 1
#define FRAME_SAVE_DMA_ALLOW_QUADWORD_TRANSACTIONS 1
#define FRAME_SAVE_DMA_ALLOW_WORD_TRANSACTIONS 1
#define FRAME_SAVE_DMA_BASE 0x1081000
#define FRAME_SAVE_DMA_IRQ 7
#define FRAME_SAVE_DMA_IRQ_INTERRUPT_CONTROLLER_ID 0
#define FRAME_SAVE_DMA_LENGTHWIDTH 32
#define FRAME_SAVE_DMA_MAX_BURST_SIZE 128
#define FRAME_SAVE_DMA_NAME "/dev/Frame_Save_DMA"
#define FRAME_SAVE_DMA_SPAN 32
#define FRAME_SAVE_DMA_TYPE "altera_avalon_dma"


/*
 * Keypad_Cols configuration
 *
 */

#define ALT_MODULE_CLASS_Keypad_Cols altera_avalon_pio
#define KEYPAD_COLS_BASE 0x10
#define KEYPAD_COLS_BIT_CLEARING_EDGE_REGISTER 0
#define KEYPAD_COLS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYPAD_COLS_CAPTURE 0
#define KEYPAD_COLS_DATA_WIDTH 3
#define KEYPAD_COLS_DO_TEST_BENCH_WIRING 0
#define KEYPAD_COLS_DRIVEN_SIM_VALUE 0
#define KEYPAD_COLS_EDGE_TYPE "NONE"
#define KEYPAD_COLS_FREQ 50000000
#define KEYPAD_COLS_HAS_IN 0
#define KEYPAD_COLS_HAS_OUT 1
#define KEYPAD_COLS_HAS_TRI 0
#define KEYPAD_COLS_IRQ -1
#define KEYPAD_COLS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEYPAD_COLS_IRQ_TYPE "NONE"
#define KEYPAD_COLS_NAME "/dev/Keypad_Cols"
#define KEYPAD_COLS_RESET_VALUE 0
#define KEYPAD_COLS_SPAN 16
#define KEYPAD_COLS_TYPE "altera_avalon_pio"


/*
 * Keypad_Rows configuration
 *
 */

#define ALT_MODULE_CLASS_Keypad_Rows altera_avalon_pio
#define KEYPAD_ROWS_BASE 0x20
#define KEYPAD_ROWS_BIT_CLEARING_EDGE_REGISTER 0
#define KEYPAD_ROWS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYPAD_ROWS_CAPTURE 0
#define KEYPAD_ROWS_DATA_WIDTH 4
#define KEYPAD_ROWS_DO_TEST_BENCH_WIRING 0
#define KEYPAD_ROWS_DRIVEN_SIM_VALUE 0
#define KEYPAD_ROWS_EDGE_TYPE "NONE"
#define KEYPAD_ROWS_FREQ 50000000
#define KEYPAD_ROWS_HAS_IN 1
#define KEYPAD_ROWS_HAS_OUT 0
#define KEYPAD_ROWS_HAS_TRI 0
#define KEYPAD_ROWS_IRQ -1
#define KEYPAD_ROWS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEYPAD_ROWS_IRQ_TYPE "NONE"
#define KEYPAD_ROWS_NAME "/dev/Keypad_Rows"
#define KEYPAD_ROWS_RESET_VALUE 0
#define KEYPAD_ROWS_SPAN 16
#define KEYPAD_ROWS_TYPE "altera_avalon_pio"


/*
 * Pixel_Buffer configuration
 *
 */

#define ALT_MODULE_CLASS_Pixel_Buffer altera_up_avalon_sram
#define PIXEL_BUFFER_BASE 0x1000000
#define PIXEL_BUFFER_IRQ -1
#define PIXEL_BUFFER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PIXEL_BUFFER_NAME "/dev/Pixel_Buffer"
#define PIXEL_BUFFER_SPAN 524288
#define PIXEL_BUFFER_TYPE "altera_up_avalon_sram"


/*
 * Pixel_Buffer configuration as viewed by Frame_Save_DMA_read_master
 *
 */

#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_BASE 0x1000000
#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_IRQ -1
#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_NAME "/dev/Pixel_Buffer"
#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_SPAN 524288
#define FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_TYPE "altera_up_avalon_sram"


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x800000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x16
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 8
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 12
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 8388608
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * SDRAM configuration as viewed by Frame_Save_DMA_write_master
 *
 */

#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_BASE 0x800000
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_CAS_LATENCY 3
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_CONTENTS_INFO
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_INIT_NOP_DELAY 0.0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_INIT_REFRESH_COMMANDS 2
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_IRQ -1
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_IS_INITIALIZED 1
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_NAME "/dev/SDRAM"
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_POWERUP_DELAY 100.0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_REFRESH_PERIOD 15.625
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_REGISTER_DATA_IN 1
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_ADDR_WIDTH 0x16
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_BANK_WIDTH 2
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_COL_WIDTH 8
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_DATA_WIDTH 16
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_NUM_BANKS 4
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SDRAM_ROW_WIDTH 12
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SHARED_DATA 0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SIM_MODEL_BASE 0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_SPAN 8388608
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_STARVATION_INDICATOR 0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_AC 5.5
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_MRD 3
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_RCD 20.0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_RFC 70.0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_RP 20.0
#define FRAME_SAVE_DMA_WRITE_MASTER_SDRAM_T_WR 14.0


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1081090
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1081090
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1081090
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "top_level"


/*
 * audio_and_video_config_0 configuration
 *
 */

#define ALT_MODULE_CLASS_audio_and_video_config_0 altera_up_avalon_audio_and_video_config
#define AUDIO_AND_VIDEO_CONFIG_0_BASE 0x1081080
#define AUDIO_AND_VIDEO_CONFIG_0_IRQ -1
#define AUDIO_AND_VIDEO_CONFIG_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define AUDIO_AND_VIDEO_CONFIG_0_NAME "/dev/audio_and_video_config_0"
#define AUDIO_AND_VIDEO_CONFIG_0_SPAN 16
#define AUDIO_AND_VIDEO_CONFIG_0_TYPE "altera_up_avalon_audio_and_video_config"


/*
 * character_lcd_0 configuration
 *
 */

#define ALT_MODULE_CLASS_character_lcd_0 altera_up_avalon_character_lcd
#define CHARACTER_LCD_0_BASE 0x140
#define CHARACTER_LCD_0_IRQ -1
#define CHARACTER_LCD_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHARACTER_LCD_0_NAME "/dev/character_lcd_0"
#define CHARACTER_LCD_0_SPAN 2
#define CHARACTER_LCD_0_TYPE "altera_up_avalon_character_lcd"


/*
 * green_LED configuration
 *
 */

#define ALT_MODULE_CLASS_green_LED altera_avalon_pio
#define GREEN_LED_BASE 0x80
#define GREEN_LED_BIT_CLEARING_EDGE_REGISTER 0
#define GREEN_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define GREEN_LED_CAPTURE 0
#define GREEN_LED_DATA_WIDTH 8
#define GREEN_LED_DO_TEST_BENCH_WIRING 0
#define GREEN_LED_DRIVEN_SIM_VALUE 0
#define GREEN_LED_EDGE_TYPE "NONE"
#define GREEN_LED_FREQ 50000000
#define GREEN_LED_HAS_IN 0
#define GREEN_LED_HAS_OUT 1
#define GREEN_LED_HAS_TRI 0
#define GREEN_LED_IRQ -1
#define GREEN_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define GREEN_LED_IRQ_TYPE "NONE"
#define GREEN_LED_NAME "/dev/green_LED"
#define GREEN_LED_RESET_VALUE 0
#define GREEN_LED_SPAN 16
#define GREEN_LED_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1081090
#define JTAG_UART_0_IRQ 5
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * mode_switch configuration
 *
 */

#define ALT_MODULE_CLASS_mode_switch altera_avalon_pio
#define MODE_SWITCH_BASE 0x120
#define MODE_SWITCH_BIT_CLEARING_EDGE_REGISTER 0
#define MODE_SWITCH_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MODE_SWITCH_CAPTURE 0
#define MODE_SWITCH_DATA_WIDTH 1
#define MODE_SWITCH_DO_TEST_BENCH_WIRING 0
#define MODE_SWITCH_DRIVEN_SIM_VALUE 0
#define MODE_SWITCH_EDGE_TYPE "NONE"
#define MODE_SWITCH_FREQ 50000000
#define MODE_SWITCH_HAS_IN 1
#define MODE_SWITCH_HAS_OUT 0
#define MODE_SWITCH_HAS_TRI 0
#define MODE_SWITCH_IRQ -1
#define MODE_SWITCH_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MODE_SWITCH_IRQ_TYPE "NONE"
#define MODE_SWITCH_NAME "/dev/mode_switch"
#define MODE_SWITCH_RESET_VALUE 0
#define MODE_SWITCH_SPAN 16
#define MODE_SWITCH_TYPE "altera_avalon_pio"


/*
 * p_accept configuration
 *
 */

#define ALT_MODULE_CLASS_p_accept altera_avalon_pio
#define P_ACCEPT_BASE 0x50
#define P_ACCEPT_BIT_CLEARING_EDGE_REGISTER 0
#define P_ACCEPT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define P_ACCEPT_CAPTURE 0
#define P_ACCEPT_DATA_WIDTH 1
#define P_ACCEPT_DO_TEST_BENCH_WIRING 0
#define P_ACCEPT_DRIVEN_SIM_VALUE 0
#define P_ACCEPT_EDGE_TYPE "NONE"
#define P_ACCEPT_FREQ 50000000
#define P_ACCEPT_HAS_IN 1
#define P_ACCEPT_HAS_OUT 0
#define P_ACCEPT_HAS_TRI 0
#define P_ACCEPT_IRQ -1
#define P_ACCEPT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define P_ACCEPT_IRQ_TYPE "NONE"
#define P_ACCEPT_NAME "/dev/p_accept"
#define P_ACCEPT_RESET_VALUE 0
#define P_ACCEPT_SPAN 16
#define P_ACCEPT_TYPE "altera_avalon_pio"


/*
 * p_data configuration
 *
 */

#define ALT_MODULE_CLASS_p_data altera_avalon_pio
#define P_DATA_BASE 0x1081040
#define P_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define P_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define P_DATA_CAPTURE 0
#define P_DATA_DATA_WIDTH 8
#define P_DATA_DO_TEST_BENCH_WIRING 0
#define P_DATA_DRIVEN_SIM_VALUE 0
#define P_DATA_EDGE_TYPE "NONE"
#define P_DATA_FREQ 50000000
#define P_DATA_HAS_IN 0
#define P_DATA_HAS_OUT 1
#define P_DATA_HAS_TRI 0
#define P_DATA_IRQ -1
#define P_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define P_DATA_IRQ_TYPE "NONE"
#define P_DATA_NAME "/dev/p_data"
#define P_DATA_RESET_VALUE 0
#define P_DATA_SPAN 16
#define P_DATA_TYPE "altera_avalon_pio"


/*
 * p_input configuration
 *
 */

#define ALT_MODULE_CLASS_p_input altera_avalon_pio
#define P_INPUT_BASE 0x1081030
#define P_INPUT_BIT_CLEARING_EDGE_REGISTER 0
#define P_INPUT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define P_INPUT_CAPTURE 0
#define P_INPUT_DATA_WIDTH 2
#define P_INPUT_DO_TEST_BENCH_WIRING 0
#define P_INPUT_DRIVEN_SIM_VALUE 0
#define P_INPUT_EDGE_TYPE "NONE"
#define P_INPUT_FREQ 50000000
#define P_INPUT_HAS_IN 1
#define P_INPUT_HAS_OUT 0
#define P_INPUT_HAS_TRI 0
#define P_INPUT_IRQ -1
#define P_INPUT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define P_INPUT_IRQ_TYPE "NONE"
#define P_INPUT_NAME "/dev/p_input"
#define P_INPUT_RESET_VALUE 0
#define P_INPUT_SPAN 16
#define P_INPUT_TYPE "altera_avalon_pio"


/*
 * p_reject configuration
 *
 */

#define ALT_MODULE_CLASS_p_reject altera_avalon_pio
#define P_REJECT_BASE 0x60
#define P_REJECT_BIT_CLEARING_EDGE_REGISTER 0
#define P_REJECT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define P_REJECT_CAPTURE 0
#define P_REJECT_DATA_WIDTH 1
#define P_REJECT_DO_TEST_BENCH_WIRING 0
#define P_REJECT_DRIVEN_SIM_VALUE 0
#define P_REJECT_EDGE_TYPE "NONE"
#define P_REJECT_FREQ 50000000
#define P_REJECT_HAS_IN 1
#define P_REJECT_HAS_OUT 0
#define P_REJECT_HAS_TRI 0
#define P_REJECT_IRQ -1
#define P_REJECT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define P_REJECT_IRQ_TYPE "NONE"
#define P_REJECT_NAME "/dev/p_reject"
#define P_REJECT_RESET_VALUE 0
#define P_REJECT_SPAN 16
#define P_REJECT_TYPE "altera_avalon_pio"


/*
 * p_signal configuration
 *
 */

#define ALT_MODULE_CLASS_p_signal altera_avalon_pio
#define P_SIGNAL_BASE 0x1081020
#define P_SIGNAL_BIT_CLEARING_EDGE_REGISTER 0
#define P_SIGNAL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define P_SIGNAL_CAPTURE 0
#define P_SIGNAL_DATA_WIDTH 2
#define P_SIGNAL_DO_TEST_BENCH_WIRING 0
#define P_SIGNAL_DRIVEN_SIM_VALUE 0
#define P_SIGNAL_EDGE_TYPE "NONE"
#define P_SIGNAL_FREQ 50000000
#define P_SIGNAL_HAS_IN 0
#define P_SIGNAL_HAS_OUT 1
#define P_SIGNAL_HAS_TRI 0
#define P_SIGNAL_IRQ -1
#define P_SIGNAL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define P_SIGNAL_IRQ_TYPE "NONE"
#define P_SIGNAL_NAME "/dev/p_signal"
#define P_SIGNAL_RESET_VALUE 0
#define P_SIGNAL_SPAN 16
#define P_SIGNAL_TYPE "altera_avalon_pio"


/*
 * red_LED configuration
 *
 */

#define ALT_MODULE_CLASS_red_LED altera_avalon_pio
#define RED_LED_BASE 0x90
#define RED_LED_BIT_CLEARING_EDGE_REGISTER 0
#define RED_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define RED_LED_CAPTURE 0
#define RED_LED_DATA_WIDTH 18
#define RED_LED_DO_TEST_BENCH_WIRING 0
#define RED_LED_DRIVEN_SIM_VALUE 0
#define RED_LED_EDGE_TYPE "NONE"
#define RED_LED_FREQ 50000000
#define RED_LED_HAS_IN 0
#define RED_LED_HAS_OUT 1
#define RED_LED_HAS_TRI 0
#define RED_LED_IRQ -1
#define RED_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RED_LED_IRQ_TYPE "NONE"
#define RED_LED_NAME "/dev/red_LED"
#define RED_LED_RESET_VALUE 0
#define RED_LED_SPAN 16
#define RED_LED_TYPE "altera_avalon_pio"


/*
 * servo_controller configuration
 *
 */

#define ALT_MODULE_CLASS_servo_controller altera_avalon_pio
#define SERVO_CONTROLLER_BASE 0x0
#define SERVO_CONTROLLER_BIT_CLEARING_EDGE_REGISTER 0
#define SERVO_CONTROLLER_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SERVO_CONTROLLER_CAPTURE 0
#define SERVO_CONTROLLER_DATA_WIDTH 1
#define SERVO_CONTROLLER_DO_TEST_BENCH_WIRING 0
#define SERVO_CONTROLLER_DRIVEN_SIM_VALUE 0
#define SERVO_CONTROLLER_EDGE_TYPE "NONE"
#define SERVO_CONTROLLER_FREQ 50000000
#define SERVO_CONTROLLER_HAS_IN 0
#define SERVO_CONTROLLER_HAS_OUT 1
#define SERVO_CONTROLLER_HAS_TRI 0
#define SERVO_CONTROLLER_IRQ -1
#define SERVO_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SERVO_CONTROLLER_IRQ_TYPE "NONE"
#define SERVO_CONTROLLER_NAME "/dev/servo_controller"
#define SERVO_CONTROLLER_RESET_VALUE 0
#define SERVO_CONTROLLER_SPAN 16
#define SERVO_CONTROLLER_TYPE "altera_avalon_pio"


/*
 * video_pixel_buffer_dma_0 configuration
 *
 */

#define ALT_MODULE_CLASS_video_pixel_buffer_dma_0 altera_up_avalon_video_pixel_buffer_dma
#define VIDEO_PIXEL_BUFFER_DMA_0_BASE 0x1081060
#define VIDEO_PIXEL_BUFFER_DMA_0_IRQ -1
#define VIDEO_PIXEL_BUFFER_DMA_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VIDEO_PIXEL_BUFFER_DMA_0_NAME "/dev/video_pixel_buffer_dma_0"
#define VIDEO_PIXEL_BUFFER_DMA_0_SPAN 16
#define VIDEO_PIXEL_BUFFER_DMA_0_TYPE "altera_up_avalon_video_pixel_buffer_dma"

#endif /* __SYSTEM_H_ */
