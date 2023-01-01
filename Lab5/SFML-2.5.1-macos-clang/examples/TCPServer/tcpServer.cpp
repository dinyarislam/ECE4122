/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 10 November 2022

Description: Lab 5

What is the purpose of this file?
Console program that takes as a single command line argument the port number on which the TCP Server will listen for connection requests.
*/
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

/*
The main() function: Launch a server, wait for an incoming connection, and wait for the answer from clients.
@param argc number of args
@param argv pointer to array of args
*/
void main(int argc, char *argv[])
{
    //
    int invalid_bit = 0;
    // Validation check for number of args
    if (argc != 2)
    {
        std::cout << "Invalid command line argument detected: Incorrect number of arguments(" << argc << ")." << std::endl;
        std::cout << "Please check your values and press any key to end the program!" << std::endl;
        // Wait until the user presses 'enter' key
        std::cout << "Press enter to exit..." << std::endl;
        std::cin.ignore(10000, '\n');
        std::cin.ignore(10000, '\n');
        return;
    }

    std::string argStr_port = argv[1];
    // validation check for argument non integer values
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

    if (invalid_bit)
    {
        // Wait until the user presses 'enter' key
        std::cout << "Press enter to exit..." << std::endl;
        std::cin.ignore(10000, '\n');
        std::cin.ignore(10000, '\n');
        return;
    }
    unsigned short port = (unsigned short)(port_int);
    // Create a server socket to accept new connections
    sf::TcpListener listener;
    // socket vector
    std::vector<sf::TcpSocket*> clients;
    // selector for sockets
    sf::SocketSelector selector;
    sf::Packet packet;
    sf::Uint16 x;
    std::string s;

    // Listen to the given port for incoming connections
    if (listener.listen(port) != sf::Socket::Done)
    {
        return;
    }
    selector.add(listener);
    std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;
    
    // log file
    std::fstream fout;
    fout.open("server.log", (std::ios::out | std::ios::app));

    // Wait to see if any socket is ready to use
    while(true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket* socket = new sf::TcpSocket;
                listener.accept(*socket);
                if ((*socket).receive(packet) == sf::Socket::Done)
                {
                    packet >> s;
                    std::cout << s << std::endl;
                    fout << s << std::endl;
                    packet.clear();
                }
                clients.push_back(socket);
                selector.add(*socket);
                //std::cout << socket << std::endl;
            }
            for (int i = 0; i < clients.size(); i++)
            {
                //std::cout << (clients[i]) << std::endl;
                if (selector.isReady(*clients[i]))
                {
                    if ((*clients[i]).receive(packet) == sf::Socket::Done)
                    {
                        packet >> s;
                        std::cout << s << std::endl;
                        fout << s << std::endl;
                        packet.clear();
                        //return;
                    }
                    if (s.substr(s.length() - 12,12) == "Disconnected")
                    {
                        clients.erase(clients.begin()+i);
                    }
                }
            }
        }
    }

    // free memory
    for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
    {
        delete *it;
    }

    fout.close();

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
    std::cin.ignore(10000, '\n');
}
