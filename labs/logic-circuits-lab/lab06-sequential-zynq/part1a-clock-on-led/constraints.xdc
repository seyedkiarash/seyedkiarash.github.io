## lab06-sequential-zynq/part1a-clock-on-led  -  top module: clk_led
## Board: Zynq-7010 (XC7Z010-CLG400-1) + extension board, all I/O LVCMOS33

set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports {clk}]
set_property -dict {PACKAGE_PIN V20 IOSTANDARD LVCMOS33} [get_ports {LED[0]}]

create_clock -name sys_clk_pin -period 20.000 -waveform {0.000 10.000} [get_ports clk]
