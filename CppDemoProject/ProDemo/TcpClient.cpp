#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <iostream>
#include <string>


using namespace std;

int main() {
    std::string input;
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddr;
    int ret;
    char buffer[256] = { 0 };
    const int port = 5001;
    const char* serverIp = "127.0.0.1";

    // 初始化Winsock库
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize Winsock" << endl;
        return 1;
    }

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Failed to create socket" << endl;
        WSACleanup();
        return 1;
    }

    // 连接服务器
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);
    ret = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (ret == SOCKET_ERROR) {
        cout << "Failed to connect to server" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "Success to connect to server" << endl;
    }


    std::cout << "Please enter a string: ";
    std::getline(std::cin, input);


    // 发送请求
    ret = send(clientSocket, input.c_str(), input.length(), 0);
    if (ret == SOCKET_ERROR) {
        cout << "Failed to send request" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // 接收响应
    ret = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (ret == SOCKET_ERROR) {
        cout << "Failed to receive response" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    cout << "Received message: " << buffer << endl;

    // 关闭连接
    closesocket(clientSocket);
    WSACleanup();
    std::cin.get();
    return 0;
}
