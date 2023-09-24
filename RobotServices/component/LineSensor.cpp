#include "component/LineSensor.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

LineSensor::LineSensor()
{
    const char* socket_file = "/tmp/lineSensor.s";
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        std::cerr << "Error socket creation" << std::endl;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/lineSensor.s", sizeof(addr.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
    {
        std::cerr << "Error connecting to server" << std::endl;
        close(sockfd);
    }    
}


LineSensor::~LineSensor()
{
    close(sockfd);
}


bool LineSensor::convertToBool(char s) const
{
     return true;//s != "0";
}


LineState LineSensor::readLineState()
{
    char buffer[1024];
    std::cout << "sockfd: " << sockfd << std::endl;
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) 
    {
        std::cerr << "Error reading sensor line state: " << strerror(errno) << std::endl;
        perror("recv");
        close(sockfd);
    } 
    else if (bytesRead == 0) 
    {
        std::cerr << "Connection closed by the other end" << std::endl;
        close(sockfd);
    } 
    else 
    {
        buffer[bytesRead] = '\0';
        std::cout << "SensorLine state: " << buffer << std::endl;
    }

    std::cout.write(buffer, bytesRead);

    return LineState{convertToBool(buffer[0]), convertToBool(buffer[1]), convertToBool(buffer[2])};
}
