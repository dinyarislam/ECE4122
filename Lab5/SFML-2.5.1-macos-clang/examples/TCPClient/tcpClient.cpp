/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 10 November 2022

Description: Lab 5

What is the purpose of this file?
Client console program that takes as a command line argument the IP Address and port number of the server
*/
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>
#include <string> 

/*
The main() function: Create a client, connect it to a server and send text messages.
@param argc number of args
@param argv pointer to array of args
*/

void main(int argc, char *argv[])
{
    int invalid_bit = 0;
    // Validation check for number of args
    if (argc != 3)
    {
        std::cout << "Invalid command line argument detected: Incorrect number of arguments(" << argc << ")." << std::endl;
        std::cout << "Please check your values and press any key to end the program!" << std::endl;
        // Wait until the user presses 'enter' key
        std::cout << "Press enter to exit..." << std::endl;
        std::cin.ignore(10000, '\n');
        std::cin.ignore(10000, '\n');
        return;
    }

    // validation check for argument non integer values
    std::string argStr_ip = argv[1];
    std::string argStr_port = argv[2];
    // validation check for argument values
    for (int j = 0; j < argStr_port.length(); j++)
    {
        if (!isdigit(argStr_port[j])) //check if input has ASCII characters other than digits
        {
            std::cout << "Invalid command line argument detected: " << argStr_port << "." << std::endl;
            std::cout << "Please check your values and press any key to end the program!" << std::endl;
            invalid_bit = 1;
        }
    }

    // validation check for port range
    int port_int = std::stoi(argStr_port);
    if (!invalid_bit)
    {
        if (port_int < 61000 || port_int > 65535)
        {
            std::cout << "Invalid command line argument detected: " << port_int << "." << std::endl;
            std::cout << "Please check your values and press any key to end the program!" << std::endl;
            invalid_bit = 1;
        }
    }

    unsigned short port = (unsigned short)(port_int);
    // extract server address from cmd line
    sf::IpAddress server = argStr_ip;

    
    // Create a socket for communicating with the server
    sf::TcpSocket socket;
    //std::cout << "Still here" << std::endl;
    sf::Uint16 x = 10;
    std::string s;
    double d = 0.6;

    sf::Packet packet;
    // Connect to the server
    if (!invalid_bit)
    {
        if (socket.connect(server, port) != sf::Socket::Done || port_int < 61000 || port_int > 65535)
        {
            std::cout << "Failed to connect to the server at " << server << " on " << port << "." << std::endl;
            std::cout << "Please check your values and press any key to end program!" << std::endl;
            invalid_bit = 1;
        }   
    }

    if (invalid_bit)
    {
        // Wait until the user presses 'enter' key
        std::cout << "Press enter to exit..." << std::endl;
        std::cin.ignore(10000, '\n');
        std::cin.ignore(10000, '\n');
        return;
    }
    // current date/time based on current system
    time_t now = time(0);
    
    // convert now to string form
    std::string dt = ctime(&now);
    s = dt.substr(0,dt.length()-1) + " :: " + argStr_ip + " :: " + "Connected";
    packet << s;
    socket.send(packet);
    packet.clear();

    do
    {
        std::cout << "Please enter a message: ";

        // Send an answer to the server
        std::getline (std::cin,s);
        if (s == "quit")
        {
            s = "Disconnected";
        }
        // current date/time based on current system
        time_t now = time(0);
        
        // convert now to string form
        std::string dt = ctime(&now);
        packet << (dt.substr(0,dt.length()-1) + " :: " + socket.getRemoteAddress().toString() + " :: " + s);
        if (socket.send(packet) == sf::Socket::Done)
        {
            //std::cout << "Packet sent" << std::endl;
            packet.clear();
            //return;
        }
    } while (s != "Disconnected");

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');
}