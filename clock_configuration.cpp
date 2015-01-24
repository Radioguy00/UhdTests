
#define DEFINE_GLOBALS

#include "/usr/include/uhd/usrp/multi_usrp.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <csignal>
#include <fstream>
#include <cmath>
#include "uhd_utilities.h"
#include <pthread.h>
#include "task_sampling.h"

bool stop_signal_called = false;


void sig_int_handler(int) {stop_signal_called = true;}


#define MAIN_ERROR_SAMPLING_TASK_NOT_CREATED 1 ;
#define MAIN_ERROR_DEMOD_TASK_NOT_CREATED 2;


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
	
	// Configure the board as desired
	// Master clock
	
	double desired_clock_hz = 19660800;
	double clock_rate_before = usrp->get_master_clock_rate();
	usrp->set_master_clock_rate(desired_clock_hz);
	double clock_rate_after = usrp->get_master_clock_rate();
	
	std::cout << "Clock before modification: " << clock_rate_before << '\n';
	std::cout << "Clock after modification: " << clock_rate_after << '\n';
	
	
	
	// Sample rate
	usrp->set_rx_rate(38400);
	std::cout << "Rx Sample rate: "  << usrp->get_rx_rate() << std::endl;
	// Initial receive frequency
	tune_request_t tune_request(135e6, 55e3);
	tune_result_t tune_result = usrp->set_rx_freq(tune_request);
	std::cout << "Target RF frequency: " << tune_result.target_rf_freq << std::endl;
	std::cout << "Actual RF frequency: " << tune_result.actual_rf_freq << std::endl;
	std::cout << "Target DSP frequency: " << tune_result.target_dsp_freq << std::endl;
	std::cout << "Actual DSP frequency: " << tune_result.actual_dsp_freq << std::endl;
	// Display the board configuration
	//get_rx_parameters(usrp, 0, std::cout);	

	
	return 0;
	
}



