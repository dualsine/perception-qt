#include "client.h"
#include <sstream>
#include <thread>

#define CHECK(x, y) if (x) printf("\nPERCEPTION SIGNALS (CLIENT) ASSERT FAILED: %s\n", y);

namespace Perception {
  namespace Signals {

    namespace {
      Client* instance_;
    }

    std::vector<char*> Client::msg_queue_;
 
    Client::Client() : Base() {
      assert(!instance_);
      instance_ = this;

      // client loop
      pthread_create(&thread_, NULL, Client::client_loop_, nullptr);
    }

    void Client::createInstance() {
      assert(!instance_);
      instance_ = new Client();
    }

    void* Client::client_loop_(void*) {
      context_ = zmq_ctx_new();
      socket_ = zmq_socket(context_, ZMQ_DEALER);
      
      // use thread_id as client identifier
      std::stringstream ss;
      ss << std::this_thread::get_id();
      const char* thread_id = ss.str().c_str();
      zmq_setsockopt(socket_, ZMQ_IDENTITY, thread_id, strlen(thread_id));

      // connect to server
      const char* client_address = std::string("tcp://127.0.0.1:"+port_).c_str();
      int code = zmq_connect(socket_, client_address); CHECK(code != 0, "client connect error")

      while (loop_active_) {
        // init messages
        zmq_msg_t empty_frame, message_frame;
        code = zmq_msg_init(&empty_frame); CHECK(code != 0, "client empty_frame init error")
        code = zmq_msg_init(&message_frame); CHECK(code != 0, "client message init error")
      
        /* Block until a empty frame is available to be received from socket */
        int msg_size = zmq_msg_recv (&empty_frame, socket_, 0); CHECK(msg_size == -1, "client empty frame recv error")
        zmq_msg_close( &empty_frame );

        // receive main message
        msg_size = zmq_msg_recv (&message_frame, socket_, 0); CHECK(msg_size == -1, "client msg recv error")
        if (msg_size != -1) {
          // extract message from message_frame
          std::string message;
          message.resize(msg_size + 1);
          memcpy(&message[0], zmq_msg_data(&message_frame), msg_size);

          // handle message
        }
        zmq_msg_close( &message_frame );
      }

      zmq_close(socket_);
      zmq_ctx_destroy(context_);
      pthread_exit(nullptr);
    }

    void Client::sendMessage(std::string text) {
      s_sendmore(socket_, (char*) "");
      CHECK(s_send(socket_, (char*)text.c_str()) < 0, "sending error") 
    }

  } // namespace Signals
} // namespace Perception