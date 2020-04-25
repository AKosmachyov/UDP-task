//
//  main.cpp
//  Client
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include <iostream>
#include "Socket.hpp"
#include "Address.hpp"

int main(int argc, const char * argv[]) {
    const int port = 30000;
    Address adress = Address( 127, 0, 0, 1, port);
    
    Socket socket;
    
    if ( !socket.open( port ) ) {
        exit( 1 );
    }
    
    // send a packet
    
    const char data[] = "hello world!";
    
    bool isSent = socket.send( adress, data, sizeof( data ) );
    
    if ( !isSent ) {
        exit( 1 );
    }
    
    printf("Message has been sent\n");
    
    return 0;
}

