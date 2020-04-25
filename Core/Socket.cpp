//
//  Socket.cpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include <iostream> // for printf
#include <sys/socket.h> // for AF_INET, SOCK_DGRAM
#include <netinet/in.h> // for IPPROTO_UDP
#include <unistd.h> // for close socket
#include <fcntl.h> // for F_SETFL, O_NONBLOCK

#include "Socket.hpp"
#include "Address.hpp"

Socket::Socket() {
    socketId = 0;
}

Socket::~Socket() {
    closeSocket();
}

bool Socket::open( unsigned short port) {
    int socketId = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    
    if ( isOpen() ) {
        socketId = 0;
        printf( "failed to create socket\n" );
        return false;
    }
    
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( (unsigned short) port );
    
    int bindedStatus = bind( socketId, (const sockaddr*) &address, sizeof( sockaddr_in ) );
    if ( bindedStatus < 0 ) {
        socketId = 0;
        printf( "failed to bind socket\n" );
        return false;
    }
    
    int nonBlocking = 1;
    int nonBlockingStatus = fcntl( socketId, F_SETFL, O_NONBLOCK, nonBlocking );
    if ( nonBlockingStatus == -1 ) {
        socketId = 0;
        printf( "failed to set non-blocking socket\n" );
        return false;
    }
    
    return true;
}

void Socket::closeSocket() {
    if ( isOpen() ) {
        close( socketId );
    }
}

bool Socket::isOpen() const {
    return socketId < 1;
}

bool Socket::send( const Address &destination, const void *data, int packetSize ) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl( destination.getAddress() );
    address.sin_port = htons( destination.getPort() );
    
    int sentBytes = sendto( socketId, (const char*)data, packetSize, 0, (sockaddr*)&address, sizeof(sockaddr_in) );
    
    return sentBytes == packetSize;
}

int Socket::receive( Address &sender, void *data, int size ) {
    unsigned char packetData[size];
    unsigned int maximumPacketSize = sizeof( packetData );

    sockaddr_in from;
    socklen_t fromLength = sizeof( from );
    
    int receivedBytes = recvfrom( socketId, data, maximumPacketSize, 0, (sockaddr*)&from, &fromLength );
    
    if ( receivedBytes <= 0 ) {
        return 0;
    }

    unsigned int fromAddress = ntohl( from.sin_addr.s_addr );
    unsigned int fromPort = ntohs( from.sin_port );

    sender = Address( fromAddress, fromPort );

    return receivedBytes;
}
