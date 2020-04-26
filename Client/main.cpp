//
//  main.cpp
//  Client
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include "Socket.hpp"
#include "Address.hpp"
#include "Config.hpp"

std::mt19937 randomNumberEngine;

Address SERVER_ADDRESS = Address( 127, 0, 0, 1, 3000 );
Socket clientSocket;

int MAX_REQUEST_COUNT = 10;
int executedRequests = 0;

int MAX_BUFFER_SIZE = 256;

int getRandomNumber( int from, int to ) {
    std::uniform_int_distribution<int> uni( from, to);
    return uni( randomNumberEngine );
}

void waitForResponse( char *responseMessage ) {
    while ( true )
    {
        Address sender;
        int bytes_read = clientSocket.receive( sender, responseMessage, sizeof( responseMessage ) );
        
        if ( bytes_read )
            return;
    }
}

void sendRequests() {
    
    while ( executedRequests < MAX_REQUEST_COUNT ) {
        
        int numberForRequest = getRandomNumber( 1, 100 );
        char message[ sizeof( numberForRequest ) ];
        sprintf( message, "%d", numberForRequest );
        
        bool isSent = clientSocket.send( SERVER_ADDRESS, message, sizeof( message ) );
        
        if ( !isSent ) {
            exit( 1 );
        }
        
        char responseMessage[ MAX_BUFFER_SIZE ];
        waitForResponse( responseMessage );
        
        printf( "#%d Client number: %d. Server result: %s\n", executedRequests + 1, numberForRequest, responseMessage );
        
        int sec = getRandomNumber( 5, 15 );
        printf( "Wait %d s before next request\n", sec );
        auto delayTime = std::chrono::seconds( sec );
        std::this_thread::sleep_for( delayTime );
        
        executedRequests++;
    }
    
}

int main( int argc, const char * argv[] ) {
    std::random_device rd;
    randomNumberEngine = std::mt19937( rd() );
    
    // get port from dynamic port range
    unsigned short socketPort = getRandomNumber( 49152, 65535 );
    if ( !clientSocket.open( socketPort ) ) {
        exit( 1 );
    }
    
    sendRequests();
    
    clientSocket.closeSocket();
    
    return 0;
}
