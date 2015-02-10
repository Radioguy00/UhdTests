/*-------------------------------------------------------------------
 * @file clock_configuration.cpp
 *
 * Utility to test the different master clock settings of the hardware
 * -----------------------------------------------------------------*/

#define DEFINE_GLOBALS

#include "/usr/include/uhd/usrp/multi_usrp.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <fstream>
#include <cmath>

bool stop_signal_called = false;


void sig_int_handler(int) {stop_signal_called = true;}



int main(int argc, char ** argv)
{
	namespace radio = uhd::usrp;
	
	using namespace uhd;
	
	// Start of program
	printf("\n-----> Start of Test Program\n");


	// Set up the signal handler for CTRL+C
	std::signal(SIGINT, &sig_int_handler);
	
	//-----------------------------------------------
	// Create the USRP Hardware object
	//-----------------------------------------------
	size_t mboard = 0;

	uhd::device_addr_t args;
	std::cout << std::endl << "-----> Creating device" << std::endl;
	radio::multi_usrp::sptr usrp = radio::multi_usrp::make(args);
	
	// Master clock configuration
	
	double desired_clock_hz = 19660800;
	double clock_rate_before = usrp->get_master_clock_rate();
	usrp->set_master_clock_rate(desired_clock_hz);
	double clock_rate_after = usrp->get_master_clock_rate();
	
	std::cout << "Clock before modification: " << clock_rate_before << '\n';
	std::cout << "Clock after modification: " << clock_rate_after << '\n';
	
	// Sample rate configuration
	
	usrp->set_rx_rate(38400);
	std::cout << "Rx Sample rate: "  << usrp->get_rx_rate() << std::endl;

	// Receive frequency configuration
	{	
	tune_request_t tune_request(137.5e6, 55e3);
	tune_result_t tune_result = usrp->set_rx_freq(tune_request);
	std::cout << "Target RX RF frequency: " << tune_result.target_rf_freq << std::endl;
	std::cout << "Actual RX RF frequency: " << tune_result.actual_rf_freq << std::endl;
	std::cout << "Target RX DSP frequency: " << tune_result.target_dsp_freq << std::endl;
	std::cout << "Actual RX DSP frequency: " << tune_result.actual_dsp_freq << std::endl;
	}
	
	// Transmit frequency configuration
	{
	tune_request_t tune_request(149.05e6, 55e3);
	tune_result_t tune_result = usrp->set_tx_freq(tune_request);
	std::cout << "Target TX RF frequency: " << tune_result.target_rf_freq << std::endl;
	std::cout << "Actual TX RF frequency: " << tune_result.actual_rf_freq << std::endl;
	std::cout << "Target TX DSP frequency: " << tune_result.target_dsp_freq << std::endl;
	std::cout << "Actual TX DSP frequency: " << tune_result.actual_dsp_freq << std::endl;
	}

	return 0;
	
}



