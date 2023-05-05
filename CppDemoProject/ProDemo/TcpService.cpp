#include <iostream>
#include <winsock2.h>
#include <iostream>
#include <string>
using namespace std;

int main() {
    WSADATA wsaData;
    SOCKET listenSocket, clientSocket;
    SOCKADDR_IN serverAddr, clientAddr;
    int ret, addrLen = sizeof(SOCKADDR_IN);
    char buffer[256] = { 0 };
    const int port = 5001;

    // ��ʼ��Winsock��
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize Winsock" << endl;
        return 1;
    }

    // ���������׽���
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        cout << "Failed to create socket" << endl;
        WSACleanup();
        return 1;
    }

    // �󶨵�ַ
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    ret = bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (ret == SOCKET_ERROR) {
        cout << "Failed to bind address" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // �����˿�
    ret = listen(listenSocket, SOMAXCONN);
    if (ret == SOCKET_ERROR) {
        cout << "Failed to listen on port " << port << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // ��������
    clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Failed to accept connection" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    } else {
        cout << "Success to connect to client" << endl;
    }

    // ��ȡ����
    ret = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (ret == SOCKET_ERROR) {
        cout << "Failed to receive data" << endl;
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    cout << "Received message: " << buffer << endl;

    
    std::string input;
    std::cout << "Please enter a string: ";
    std::getline(std::cin, input);

    // ������Ӧ
    ret = send(clientSocket, input.c_str(), input.length(), 0);
    if (ret == SOCKET_ERROR) {
        cout << "Failed to send response" << endl;
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // �ر�����
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
