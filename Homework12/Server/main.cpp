#include <boost/asio.hpp>
#include <iostream>
#include <fstream>

using boost::asio::ip::tcp;

void receive_file(const std::string& filename, const std::string& port) {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoi(port)));
    tcp::socket socket(io_context);
    acceptor.accept(socket);

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    char buffer[1024];
    boost::system::error_code error;
    while (size_t len = socket.read_some(boost::asio::buffer(buffer), error)) {
        file.write(buffer, len);
    }

    if (error != boost::asio::error::eof) {
        std::cerr << "Receive failed: " << error.message() << std::endl;
    } else {
        std::cout << "File received successfully." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file> <port>" << std::endl;
        return 1;
    }

    try {
        receive_file(argv[1], argv[2]);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}