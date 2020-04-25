//
//  Address.cpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#include "Address.hpp"

Address::Address() {
    address = 0;
    port = 0;
}

Address::Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port ) {
    this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
    this->port = port;
}

Address::Address( unsigned int address, unsigned short port ) {
    this->address = address;
    this->port = port;
}

unsigned int Address::getAddress() const {
    return address;
}

unsigned char Address::getA() const {
    return ( unsigned char ) ( address >> 24 );
}

unsigned char Address::getB() const {
    return ( unsigned char ) ( address >> 16 );
}

unsigned char Address::getC() const {
    return ( unsigned char ) ( address >> 8 );
}

unsigned char Address::getD() const {
    return ( unsigned char ) ( address );
}

unsigned short Address::getPort() const {
    return port;
}
