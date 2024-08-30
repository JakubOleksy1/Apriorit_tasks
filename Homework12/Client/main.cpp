#include <boost/asio.hpp>
#include <iostream>
#include <fstream>

using boost::asio::ip::tcp;

void send_file(const std::string& filename, const std::string& host, const std::string& port) {
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve(host, port);
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)).gcount() > 0) {
        boost::asio::write(socket, boost::asio::buffer(buffer, file.gcount()));
    }

    std::cout << "File sent successfully." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <file> <host> <port>" << std::endl;
        return 1;
    }

    try {
        send_file(argv[1], argv[2], argv[3]);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}