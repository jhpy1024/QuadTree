#include "Application.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        std::string args(argv[1]);
        
        Application application(args);
        application.run();
    }
    else
    {
        Application application(500, 500);
        application.run();
    }

    return 0;
}
