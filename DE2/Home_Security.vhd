LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;

ENTITY Home_Security IS
	PORT( KEY : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
			CLOCK_50 : IN STD_LOGIC;
			
			--SDRAM
			DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
			DRAM_ADDR : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
			DRAM_BA_0, DRAM_BA_1 : BUFFER STD_LOGIC;
			DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
			DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			DRAM_UDQM, DRAM_LDQM : BUFFER STD_LOGIC;
			
			--AV Config
			I2C_SDAT : INOUT STD_LOGIC;
			I2C_SCLK : OUT STD_LOGIC;
			
			--Video Decoder
			CLOCK_27 : IN STD_LOGIC; --TODO: Which clock?
			TD_CLK27 : IN STD_LOGIC;
			TD_DATA  : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
			TD_HS : IN STD_LOGIC;
			TD_VS : IN STD_LOGIC;
			--TODO: Clock 27 reset?
			TD_RESET : OUT STD_LOGIC;
			
			--Pixel Buffer
			SRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
			SRAM_ADDR : OUT STD_LOGIC_VECTOR(17 DOWNTO 0);
			SRAM_LB_N : OUT STD_LOGIC;
			SRAM_UB_N : OUT STD_LOGIC;
			SRAM_CE_N : OUT STD_LOGIC;
			SRAM_OE_N : OUT STD_LOGIC;
			SRAM_WE_N : OUT STD_LOGIC;
			
			--VGAController
			VGA_R: OUT STD_LOGIC_VECTOR(9 downto 0);
			VGA_G: OUT STD_LOGIC_VECTOR(9 downto 0);
			VGA_B: OUT STD_LOGIC_VECTOR(9 downto 0);
			VGA_CLK: OUT STD_LOGIC;
			VGA_BLANK: OUT STD_LOGIC;
			VGA_HS: OUT STD_LOGIC;
			VGA_VS: OUT STD_LOGIC;
			VGA_SYNC: OUT STD_LOGIC;
			
			--IO
			GPIO_1 : INOUT STD_LOGIC_VECTOR( 35 DOWNTO 0 );
			
			--LCD SCREEN
			lcd_ON, lcd_BLON, lcd_EN, lcd_RS, lcd_RW : out std_Logic;
			lcd_DATA : inout std_LOGIC_VECTOR(7 downto 0);
			
			--Servo and Keypad
			GPIO_0 : INOUT STD_LOGIC_VECTOR( 35 DOWNTO 0 );
			
			LEDG	: OUT STD_LOGIC_VECTOR(7 downto 0);
			LEDR	: OUT STD_LOGIC_VECTOR(17 downto 0);
			
			SW		: IN STD_LOGIC_VECTOR(17 downto 0)
			
			);
	
END Home_Security;

ARCHITECTURE BEHAVIOURAL OF Home_Security IS

    component top_level is
        port (
            clk_clk                          : in    std_logic                     := 'X';             -- clk
            reset_reset_n                    : in    std_logic                     := 'X';             -- reset_n
            sdram_wire_addr                  : out   std_logic_vector(11 downto 0);                    -- addr
            sdram_wire_ba                    : out   std_logic_vector(1 downto 0);                     -- ba
            sdram_wire_cas_n                 : out   std_logic;                                        -- cas_n
            sdram_wire_cke                   : out   std_logic;                                        -- cke
            sdram_wire_cs_n                  : out   std_logic;                                        -- cs_n
            sdram_wire_dq                    : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
            sdram_wire_dqm                   : out   std_logic_vector(1 downto 0);                     -- dqm
            sdram_wire_ras_n                 : out   std_logic;                                        -- ras_n
            sdram_wire_we_n                  : out   std_logic;                                        -- we_n
            av_config_wire_SDAT              : inout std_logic                     := 'X';             -- SDAT
            av_config_wire_SCLK              : out   std_logic;                                        -- SCLK
            video_decoder_wire_TD_CLK27      : in    std_logic                     := 'X';             -- TD_CLK27
            video_decoder_wire_TD_DATA       : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- TD_DATA
            video_decoder_wire_TD_HS         : in    std_logic                     := 'X';             -- TD_HS
            video_decoder_wire_TD_VS         : in    std_logic                     := 'X';             -- TD_VS
            video_decoder_wire_clk27_reset   : in    std_logic                     := 'X';             -- clk27_reset
            video_decoder_wire_TD_RESET      : out   std_logic;                                        -- TD_RESET
            video_decoder_wire_overflow_flag : out   std_logic;                                        -- overflow_flag
            pixel_buffer_wire_DQ             : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DQ
            pixel_buffer_wire_ADDR           : out   std_logic_vector(17 downto 0);                    -- ADDR
            pixel_buffer_wire_LB_N           : out   std_logic;                                        -- LB_N
            pixel_buffer_wire_UB_N           : out   std_logic;                                        -- UB_N
            pixel_buffer_wire_CE_N           : out   std_logic;                                        -- CE_N
            pixel_buffer_wire_OE_N           : out   std_logic;                                        -- OE_N
            pixel_buffer_wire_WE_N           : out   std_logic;                                        -- WE_N
            vga_controller_wire_CLK          : out   std_logic;                                        -- CLK
            vga_controller_wire_HS           : out   std_logic;                                        -- HS
            vga_controller_wire_VS           : out   std_logic;                                        -- VS
            vga_controller_wire_BLANK        : out   std_logic;                                        -- BLANK
            vga_controller_wire_SYNC         : out   std_logic;                                        -- SYNC
            vga_controller_wire_R            : out   std_logic_vector(9 downto 0);                     -- R
            vga_controller_wire_G            : out   std_logic_vector(9 downto 0);                     -- G
            vga_controller_wire_B            : out   std_logic_vector(9 downto 0);                      -- B
				sdram_clk_clk                    : out   std_logic; 													-- clk
				gpio_in_export 						: IN 	  STD_LOGIC_VECTOR(1 DOWNTO 0);							-- export
				gpio_signal_export 					: OUT   STD_LOGIC_VECTOR(1 DOWNTO 0);							-- export
				gpio_data_export 						: OUT   STD_LOGIC_VECTOR(7 DOWNTO 0);							-- export
				button_3_wire_export             : in    std_logic                     := 'X';              -- export
				keypad_cols_wire_export          : out   std_logic_vector(2 downto 0);                     -- export
            keypad_rows_wire_export          : in    std_logic_vector(3 downto 0)  := (others => 'X');  -- export
				servo_wire_export                : out   std_logic;
				accept_signal_export             : in    std_logic                     := 'X';             -- export
            reject_signal_export             : in    std_logic                     := 'X';              -- export
				green_led_wire_export            : out   std_logic_vector(7 downto 0);                     -- export
            red_led_wire_export              : out   std_logic_vector(17 downto 0);                    -- export
				lcd_data_DATA: inout STD_LOGIC_VECTOR(7 Downto 0);
				lcd_data_ON : out Std_LOGIC;
				lcd_data_BLON: out STD_LOGIC;
				lcd_data_EN: out StD_LOGIC;
				lcd_data_RS: out STd_LOGIC;
				lcd_data_RW: out Std_LOGIC;
            mode_switch_wire_export          : in    std_logic                     := 'X'              -- export	
        );
    end component top_level;
	 
	SIGNAL DQM : STD_LOGIC_VECTOR(1 DOWNTO 0);
	SIGNAL BA : STD_LOGIC_VECTOR(1 DOWNTO 0);	
	SIGNAL Overflow_Flag : STD_LOGIC; --TODO: CHECK THIS
	
BEGIN
	DRAM_BA_0 <= BA(0);
	DRAM_BA_1 <= BA(1);
	DRAM_UDQM <= DQM(1);
	DRAM_LDQM <= DQM(0);
	
	--TD_RESET <= '1';
	
	    u0 : component top_level
        port map (
            clk_clk                          => CLOCK_50,                         --                 clk.clk
            reset_reset_n                    => KEY(0),                    --               reset.reset_n
            sdram_wire_addr                  => DRAM_ADDR,                  --          sdram_wire.addr
            sdram_wire_ba                    => BA,                    --                    .ba
            sdram_wire_cas_n                 => DRAM_CAS_N,                 --                    .cas_n
            sdram_wire_cke                   => DRAM_CKE,                   --                    .cke
            sdram_wire_cs_n                  => DRAM_CS_N,                  --                    .cs_n
            sdram_wire_dq                    => DRAM_DQ,                    --                    .dq
            sdram_wire_dqm                   => DQM,                   --                    .dqm
            sdram_wire_ras_n                 => DRAM_RAS_N,                 --                    .ras_n
            sdram_wire_we_n                  => DRAM_WE_N,                  --                    .we_n
            av_config_wire_SDAT              => I2C_SDAT,              --      av_config_wire.SDAT
            av_config_wire_SCLK              => I2C_SCLK,              --                    .SCLK
            video_decoder_wire_TD_CLK27      => CLOCK_27,      --  video_decoder_wire.TD_CLK27
            video_decoder_wire_TD_DATA       => TD_DATA,       --                    .TD_DATA
            video_decoder_wire_TD_HS         => TD_HS,         --                    .TD_HS
            video_decoder_wire_TD_VS         => TD_VS,         --                    .TD_VS
            video_decoder_wire_clk27_reset   => '0',   --                    .clk27_reset
            video_decoder_wire_TD_RESET      => TD_RESET,      --                    .TD_RESET
            video_decoder_wire_overflow_flag => Overflow_Flag, --                    .overflow_flag
            pixel_buffer_wire_DQ             => SRAM_DQ,             --   pixel_buffer_wire.DQ
            pixel_buffer_wire_ADDR           => SRAM_ADDR,           --                    .ADDR
            pixel_buffer_wire_LB_N           => SRAM_LB_N,           --                    .LB_N
            pixel_buffer_wire_UB_N           => SRAM_UB_N,           --                    .UB_N
            pixel_buffer_wire_CE_N           => SRAM_CE_N,           --                    .CE_N
            pixel_buffer_wire_OE_N           => SRAM_OE_N,           --                    .OE_N
            pixel_buffer_wire_WE_N           => SRAM_WE_N,           --                    .WE_N
            vga_controller_wire_CLK          => VGA_CLK,          -- vga_controller_wire.CLK
            vga_controller_wire_HS           => VGA_HS,           --                    .HS
            vga_controller_wire_VS           => VGA_VS,           --                    .VS
            vga_controller_wire_BLANK        => VGA_BLANK,        --                    .BLANK
            vga_controller_wire_SYNC         => VGA_SYNC,         --                    .SYNC
            vga_controller_wire_R            => VGA_R,            --                    .R
            vga_controller_wire_G            => VGA_G,            --                    .G
            vga_controller_wire_B            => VGA_B,             --                    .B
				sdram_clk_clk                    => DRAM_CLK,				--           sdram_clk.clk
				gpio_in_export 						=> GPIO_1( 11 DOWNTO 10 ),
				gpio_signal_export 					=> GPIO_1( 9 DOWNTO 8 ),
				gpio_data_export 						=> GPIO_1( 7 DOWNTO 0 ),
				button_3_wire_export             => KEY(3),              --       button_3_wire.export
				keypad_cols_wire_export          => GPIO_0(3 downto 1),
            keypad_rows_wire_export          => GPIO_0(7 downto 4),
				servo_wire_export                => GPIO_0(0),
				accept_signal_export             => GPIO_1(15),
            reject_signal_export             => GPIO_1(17),
				green_led_wire_export            => LEDG,
            red_led_wire_export              => LEDR,
				lcd_data_DATA 							=> LCD_DATA,
				lcd_data_ON 							=> LCD_ON,
				lcd_data_BLON 							=> LCD_BLON,
				lcd_data_EN 							=> LCD_EN,
				lcd_data_RS 							=> LCD_RS,
				lcd_data_RW 							=> LCD_RW,
            mode_switch_wire_export          => SW(0)
        );
		  
END BEHAVIOURAL;