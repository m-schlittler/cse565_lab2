Vector Addition With RTL Kernel (RTL)
======================

Simple example of vector addition using RTL Kernel

***KEY CONCEPTS:*** RTL Kernel

## SUPPORTED PLATFORMS
Platform | Board             | Software Version
---------|-------------------|-----------------
xilinx_u200_qdma|Xilinx Alveo U200|SCOUT 2019.2
xilinx_u280_xdma|Xilinx Alveo U280|SCOUT 2019.2
xilinx_u250_qdma|Xilinx Alveo U250|SCOUT 2019.2
xilinx_u200_xdma|Xilinx Alveo U200|SCOUT 2019.2
xilinx_u250_xdma|Xilinx Alveo U250|SCOUT 2019.2
xilinx_u280-es1_xdma|Xilinx Alveo U280|SCOUT 2019.2


##  DESIGN FILES
Application code is located in the src directory. Accelerator binary files will be compiled to the xclbin directory. The xclbin directory is required by the Makefile and its contents will be filled during compilation. A listing of all the files in this example is shown below

```
src/hdl/krnl_vadd_rtl.v
src/hdl/krnl_vadd_rtl_adder.sv
src/hdl/krnl_vadd_rtl_axi_read_master.sv
src/hdl/krnl_vadd_rtl_axi_write_master.sv
src/hdl/krnl_vadd_rtl_control_s_axi.v
src/hdl/krnl_vadd_rtl_counter.sv
src/hdl/krnl_vadd_rtl_int.sv
src/host.cpp
src/kernel.xml
```

##  COMMAND LINE ARGUMENTS
Once the environment has been configured, the application can be executed by
```
./host <vadd XCLBIN>
```
