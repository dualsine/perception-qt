#include "server.h"
#include "observer.h"
#include "events.h"
#include "deserializator.h"

#include <vector>

#define CHECK(x, y) if (x) printf("\nPERCEPTION SIGNALS (SERVER) ASSERT FAILED: %s\n", y);


#include <iostream>
using namespace std;
#include <thread>


namespace Perception {
  namespace Signals {

    Server::Server() {
      context_ = zmq_ctx_new();
      socket_ = zmq_socket(context_, ZMQ_ROUTER);
      zmq_setsockopt(socket_, ZMQ_IDENTITY, "server", 6);

      const char* server_address = std::string("tcp://*:"+port_).c_str();
      int code = zmq_bind(socket_, server_address);
      CHECK(code != 0, "could not bind address")
    }

    void Server::tick() {
      // initialize messages and wait for message
      std::string encrypted_message, remote_identity;
      getMessage(encrypted_message, remote_identity);
      if (!encrypted_message.empty()) {
        Deserializator des(encrypted_message);
        int event_id = des.eventId();
        switch (event_id) {
        case Events::MouseClick:
          float x = std::stof(des.next());
          float y = std::stof(des.next());
          std::vector<Observer*> observers = Observer::getObservers();
          for (int i=0; i<(int)observers.size(); i++) {
            observers.at(i)->OnMouseClick(x, y);
          }
        }
      }
    }

    void Server::close() {
      zmq_close (socket_);
      zmq_ctx_destroy (context_);
    }

    void Server::sendMessage(std::string text, std::string remote_identity) {
      s_sendmore(socket_, (char*) remote_identity.c_str());
      s_sendmore(socket_, (char*) "");
      s_send(socket_, (char*) text.c_str());
    }

    void Server::getMessage(std::string &message, std::string &remote_identity) {
      remote_identity = socketRecvAsync(socket_); // remote_identity
      socketRecvAsync(socket_); // empty frame
      message = socketRecvAsync(socket_); // main message
    }

    std::string Server::socketRecvAsync(void* socket) {
      zmq_msg_t message;
      zmq_msg_init(&message);
      int size = zmq_msg_recv(&message, socket, ZMQ_DONTWAIT);
      if (size == -1) return std::string();
      std::string str;
      str.resize(size + 1);
      memcpy(&str[0], zmq_msg_data(&message), size);
      zmq_msg_close(&message);
      return str;
    }

  } // namespace Signals
} // namespace Perception
