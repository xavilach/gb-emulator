#include "application.hh"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    try
    {
        Application app(argc, argv);

        app.run();
    }
    catch (std::runtime_error e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
