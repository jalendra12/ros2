#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

int main() {
    try {
        asio::io_context ioc;

        // Resolve the server
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve("localhost", "8765");

        // Connect to the server
        websocket::stream<tcp::socket> ws(ioc);
        asio::connect(ws.next_layer(), results.begin(), results.end());

        // Perform the WebSocket handshake
        ws.handshake("localhost", "/");

        std::cout << "Connected to ws://localhost:8765\n";

        // ✅ Send a message to the server
        ws.write(asio::buffer(std::string("Hello from C++ client")));

        // 🧾 Read loop (optional)
        for (;;) {
            beast::flat_buffer buffer;
            ws.read(buffer);
            std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
