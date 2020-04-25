//
//  Socket.hpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#ifndef Socket_hpp
#define Socket_hpp

#include "Address.hpp"

class Socket {
    
public:
    
    Socket();
    ~Socket();
    bool open( unsigned short port = 0 ); // "0" auto port configuration
    void closeSocket();
    bool isOpen() const;
    bool send( const Address &destination, const void *data, int packetSize );
    int receive( Address &sender, void *data, int size );
    
private:
    
    int socketId;
};

#endif /* Socket_hpp */
