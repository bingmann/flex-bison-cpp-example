// $Id$

#include <iostream>

#include "driver.h"

int main(int argc, char *argv[])
{
    example::Driver driver;

    for (++argv; argv[0]; ++argv)
    {
	if (*argv == std::string ("-p")) {
	    driver.trace_parsing = true;
	}
	else if (*argv == std::string ("-s")) {
	    driver.trace_scanning = true;
	}
	else
	{
	    bool result = driver.parse_file(*argv);
	    std::cout << result << std::endl;
	}
    }
}
