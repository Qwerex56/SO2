#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

std::string fix_encoding(const std::string& text) {
    std::string fixed_text;
    for (const char c : text) {
        if (static_cast<unsigned char>(c) < 128) {
            fixed_text += c;  // ASCII znak poprawny
        }
    }
    return fixed_text;
}


void receive_messages(SOCKET client_socket, const std::string &username) {
    char buffer[1024];

    while (true) {
        const int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0); // Unikamy przepełnienia
        if (bytes_received <= 0) {
            std::cout << "Rozłączono z serwerem." << std::endl;
            break;
        }

        buffer[bytes_received] = '\0'; // Zapewniamy poprawne zakończenie
        std::string message(buffer);

        std::cout << message << std::endl;
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    if (connect(client_socket, (sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Nie udało się połączyć z serwerem!" << std::endl;
        return 1;
    }

    std::string username;
    std::cout << "Podaj nazwę użytkownika: ";
    std::getline(std::cin, username);

    username += '\0';

    send(client_socket, username.c_str(), username.size(), 0);

    std::cout << "Połączono z serwerem czatu!" << std::endl;

    std::thread receive_thread(receive_messages, client_socket, username);
    receive_thread.detach();

    while (true) {
        std::string message;
        std::getline(std::cin, message);

        if (message == "/exit") {
            break;
        }

        send(client_socket, message.c_str(), message.size(), 0);
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
