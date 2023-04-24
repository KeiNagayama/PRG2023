#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;

    std::string msg = "Hello World!";
    std::string exe = argv[0];
    int i = std::stoi(argv[1]);
    double d = std::stod(argv[2]);

    return 0;
}