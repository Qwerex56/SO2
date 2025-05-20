#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

std::vector<std::string> chat_history;
std::unordered_map<SOCKET, std::string> users;
std::mutex mtx;

std::string current_time() {
    time_t now = time(0);
    tm *local_time = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", local_time);
    return std::string(buffer);
}

void handle_client(SOCKET client_socket) {
    char buffer[1024];

    recv(client_socket, buffer, sizeof(buffer), 0);
    std::string username(buffer);

    {
        std::lock_guard<std::mutex> lock(mtx);
        users[client_socket] = username;

        for (const std::string &message: chat_history) {

            std::string formatted_message = message + "\n"; // Dodajemy znak nowej linii
            send(client_socket, formatted_message.c_str(), formatted_message.size(), 0);
        }
    }

    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
            break;

        buffer[bytes_received] = '\0';
        std::string message = "[" + current_time() + "] " + username + ": " + buffer + "\0";

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << message << std::endl;
            chat_history.push_back(message);
        }
        for (const auto &[sock, user]: users) {
            if (username == user) {
                continue;
            }
            send(sock, message.c_str(), message.size(), 0);
        }
    }
    closesocket(client_socket);
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_socket, (sockaddr *) &server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    std::cout << "Serwer czatu uruchomiony na porcie 8080..." << std::endl;

    while (true) {
        SOCKET client_socket = accept(server_socket, nullptr, nullptr);
        std::thread(handle_client, client_socket).detach();
    }

    closesocket(server_socket);
    WSACleanup();

    return 0;
}
