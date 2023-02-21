#include "server.h"
#include <argh.h>

using namespace revyv;

int main(int argc, char** argv)
{
    try {
        argh::parser cmdl({ "-w", "--width", "-h", "--height" });
        cmdl.parse(argc, argv);
        auto screen_size = make_size(1920, 1080);
        if (!cmdl("width").str().empty()) {
            screen_size.width = std::atoi(cmdl("width").str().c_str());
        }
        if (!cmdl("height").str().empty()) {
            screen_size.height = std::atoi(cmdl("height").str().c_str());
        }
        Server::get_shared_instance()->run(screen_size);
        return 0;
    } catch (std::exception&) {
        return -1;
    }
}
