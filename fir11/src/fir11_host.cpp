/**
* Copyright (C) 2019-2021 Xilinx, Inc
*
* Licensed under the Apache License, Version 2.0 (the "License"). You may
* not use this file except in compliance with the License. A copy of the
* License is located at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
* License for the specific language governing permissions and limitations
* under the License.
*/

#include "cmdlineparser.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h> // for system()
#include <cstdio>
#include "fir11_kernel.h"

// XRT includes
#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

#define DATA_SIZE 4096

int main(int argc, char** argv) {
    //const int SAMPLES=600;
    const int SAMPLES=20;
    
    // Command Line Parser
    sda::utils::CmdLineParser parser;

    // Switches
    //**************//"<Full Arg>",  "<Short Arg>", "<Description>", "<Default>"
    parser.addSwitch("--xclbin_file", "-x", "input binary file string", "");
    parser.addSwitch("--device_id", "-d", "device index", "0");
    parser.parse(argc, argv);

    // Read settings
    std::string binaryFile = parser.value("xclbin_file");
    int device_index = stoi(parser.value("device_id"));

    if (argc < 3) {
        parser.printHelp();
        return EXIT_FAILURE;
    }

    std::cout << "Open the device" << device_index << std::endl;
    auto device = xrt::device(device_index);
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    auto krnl = xrt::kernel(device, uuid, "fir");

    std::cout << "Allocate Small Buffer For Input in Device Memory\n";
    auto bo_out = xrt::bo(device, 128, krnl.group_id(0));

    // Map the contents of the buffer object into host memory
    auto bo_out_map = bo_out.map<int*>();

    std::ifstream file_in;
    std::ofstream file_out;
    file_in.open("input.dat");
    file_out.open("out.dat");

    data_t signal;
    signal = 0;
    std::cout << "Execution of the kernel\n";
    for (int i = 0; i < SAMPLES; ++i) {
	file_in >> signal;
    	std::cout << "Iteration " << i << std::endl;
    	auto run = krnl(bo_out, signal);
    	run.wait();
        bo_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
	    file_out << bo_out_map[0] << std::endl;
    }


    file_in.close();
    file_out.close();


    //Comparing results with the golden output.
    printf ("Comparing observed against expected data \n");

    std::ifstream file_obs, file_exp;
    file_obs.open("out.dat");
    file_exp.open("out.gold.fir11.dat");

    data_t observed, expected;
    for (int i = 0; i < 20; ++i) {
      // start at 11 to account for garbage data before shift reg is fully populated
      if (i > 10) {
        file_obs >> observed;
        file_exp >> expected;
        if (observed != expected) {
          std::cout << "*******************************************" << std::endl;
          std::cout << "FAIL: Output DOES NOT match the golden output" << std::endl;
          std::cout << "*******************************************" << std::endl;
          return 1;
        }
      }
    }
    std::cout << "*******************************************" << std::endl;
    std::cout << "PASS: The output matches the golden output" << std::endl;
    std::cout << "*******************************************" << std::endl;

    return 0;
}
