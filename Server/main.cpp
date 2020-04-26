//
//  main.cpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Socket.hpp"
#include "Address.hpp"
#include "Config.hpp"

int MAX_BUFFER_SIZE = 256;
Socket serverSocket;

void sendResult( Address &address, int result ) {
    char message[ sizeof( result ) ];
    sprintf( message, "%d", result );
    
    serverSocket.send( address, message, sizeof( message ) );
}

int main( int argc, const char * argv[] ) {
    
    if ( !serverSocket.open( SERVER_PORT ) ) {
        exit( 1 );
    }
    
    printf( "Server started\n" );
    
    // receive packets
    
    while ( true ) {
        Address sender;
        char buffer[ MAX_BUFFER_SIZE ];
        int isBytesRead = serverSocket.receive( sender, buffer, sizeof( buffer ) );
        
        if ( !isBytesRead )
            continue;
        
        // process packet
        
        printf( "Log message: %s, from: %d\n", buffer, sender.getAddress() );
        
        try {
            int clientNumber;
            sscanf( buffer, "%d", &clientNumber );
            sendResult( sender, pow( clientNumber, 2 ) );
        } catch ( std::exception const &e ) {
            printf( "Wrong request data: %s", buffer );
        }
    }
    
    return 0;
}
