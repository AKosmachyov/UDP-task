//
//  Address.hpp
//  UDP
//
//  Created by Alexander Kosmachyov on 4/25/20.
//  Copyright © 2020 Alexander Kosmachyov. All rights reserved.
//

#ifndef Address_hpp
#define Address_hpp

class Address {
    
public:
    
    Address();
    Address( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port );
    Address( unsigned int address, unsigned short port );
    unsigned int getAddress() const;
    unsigned char getA() const;
    unsigned char getB() const;
    unsigned char getC() const;
    unsigned char getD() const;
    unsigned short getPort() const;
    //    bool operator == ( const Address & other ) const;
    //    bool operator != ( const Address & other ) const;
    
private:
    
    unsigned int address;
    unsigned short port;
    
};

#endif /* Address_hpp */
