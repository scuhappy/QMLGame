#include "Server.h"
#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<boost/bind.hpp>
#include<QDebug>
using boost::asio::ip::tcp;
using boost::asio::io_service;
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
io_service service;
boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), 777); // listen on 2001
boost::asio::ip::tcp::acceptor acc(service, ep);

void client_session(socket_ptr sock);
Server::Server(QObject *parent) :
    QThread(parent)
{
}
void Server::run()
{
    qDebug()<<"running server ,listen on 777";
    while ( true) {
        socket_ptr sock(new boost::asio::ip::tcp::socket(service));
        acc.accept(*sock);
        boost::thread( boost::bind(client_session, sock));
    }
}


void client_session(socket_ptr sock) {
    while ( true) {
        char data[512];
        size_t len = sock->read_some(boost::asio::buffer(data));
        if ( len > 0)
        {
            sock->write_some(boost::asio::buffer("ok", 2));
        }
        QThread::msleep(100);
    }
}
