#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# g++ -L /usr/lib -l uhd -o e100test test_routines.cpp
# g++ -g -L /usr/lib -l uhd -o rxtest  receiver_test.cpp uhd_utilities.cpp
# g++ -g -L /usr/lib -l uhd -o serial_port_test serial_port_test.cpp
# g++ -pthread -o thread_test thread_test.cpp

# g : Indicates debug mode
# c : Indicates compilation only



samples2file:rx_samples_to_file.o
	g++ -L /usr/lib -l uhd -o samples2file rx_samples_to_file.cpp

device_test: test_routines.o
	g++ -L /usr/lib -l uhd -o device_test test_routines.cpp

setclock: clock_configuration.o
	g++ -L /usr/lib -l uhd -o clock_configuration clock_configuration.cpp

clean:
	rm *.o
