//
//  main.cpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include <iostream>
#include "Socket.hpp"
#include "Address.hpp"

int main( int argc, const char * argv[] ) {
    const int port = 3000;
    
    Socket socket;
    
    if ( !socket.open( port ) ) {
        exit( 1 );
    }
    
    // receive packets
    
    while ( true )
    {
        Address sender;
        unsigned char buffer[256];
        int bytes_read = socket.receive( sender, buffer, sizeof( buffer ) );
        
        if ( !bytes_read )
            continue;
        
        // process packet
        
        printf("Recieve %s", buffer);
    }
    
    return 0;
}
