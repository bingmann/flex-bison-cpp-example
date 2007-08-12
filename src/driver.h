// $Id$ 	

#ifndef EXAMPLE_DRIVER_HH
#define EXAMPLE_DRIVER_HH

#include <string>
#include <vector>

namespace example {

class Driver
{
public:
    /// construct a new parser driver context
    Driver();

    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    /// stream name (file or input stream) used for error messages.
    std::string streamname;

    /// invoke the parser for a stream
    bool parse_stream(std::istream& s, const std::string& sname = "stream input");

    /// invoke the parser on an input string
    bool parse_string(const std::string& input, const std::string& sname = "string stream");

    /// invoke the parser on a file
    bool parse_file(const std::string& filename);

    // To demonstrate pure handling of parse errors, instead of
    // simply dumping them on the standard error output, we will pass
    // them to the driver using the following two member functions.

    /// error handling with associated line number
    void error(const class location& l, const std::string& m);

    /// general error handling
    void error(const std::string& m);

    /// pointer to the current lexer instance, this is used to connect the
    /// parser to the scanner.
    class Scanner* lexer;
};

} // namespace example

#endif // TRACK_DRIVER_HH
