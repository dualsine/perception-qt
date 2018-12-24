#!/bin/bash

SIGNALS_FILES=()
ZMQ_FILES=()

compile_signals() {
  path=$1
  dir=$(dirname "$path")
  filename_ext=$(basename "$path")
  filename="${filename_ext%.*}"
  echo "compiling - $path"
  mkdir -p temp_build/"$dir"
  ccache g++ -c "$dir"/"$filename".cc -o temp_build/"$dir"/"$filename".o -static -Lzmq/lib -lzmq -lpthread -std=c++17 || { exit 0; }
  SIGNALS_FILES+=(temp_build/"$dir"/"$filename".o)
}

compile_zmq() {
  path=$1
  dir=$(dirname "$path")
  filename_ext=$(basename "$path")
  filename="${filename_ext%.*}"
  echo "compiling - $path"
  mkdir -p temp_build/"$dir"
  ccache g++ -c "$dir"/"$filename".cpp -o temp_build/"$dir"/"$filename".o -static -lpthread || { exit 0; }
  ZMQ_FILES+=(temp_build/"$dir"/"$filename".o)
}

compile_zmq_c() {
  path=$1
  dir=$(dirname "$path")
  filename_ext=$(basename "$path")
  filename="${filename_ext%.*}"
  echo "compiling - $path"
  mkdir -p temp_build/"$dir"
  ccache gcc -c "$dir"/"$filename".c -o temp_build/"$dir"/"$filename".o -static -lpthread || { exit 0; }  
  ZMQ_FILES+=(temp_build/"$dir"/"$filename".o)
}

compile_signals server.cc
compile_signals observer.cc
compile_signals base.cc
compile_signals server_api.cc

compile_zmq_c zmq/src/tweetnacl.c

compile_zmq zmq/src/timers.cpp
compile_zmq zmq/src/mailbox_safe.cpp
compile_zmq zmq/src/lb.cpp
compile_zmq zmq/src/v1_encoder.cpp
compile_zmq zmq/src/sub.cpp
compile_zmq zmq/src/own.cpp
compile_zmq zmq/src/dish.cpp
compile_zmq zmq/src/curve_server.cpp
compile_zmq zmq/src/io_thread.cpp
compile_zmq zmq/src/devpoll.cpp
compile_zmq zmq/src/dist.cpp
compile_zmq zmq/src/pgm_socket.cpp
compile_zmq zmq/src/pub.cpp
compile_zmq zmq/src/scatter.cpp
compile_zmq zmq/src/pipe.cpp
compile_zmq zmq/src/io_object.cpp
compile_zmq zmq/src/raw_encoder.cpp
compile_zmq zmq/src/rep.cpp
compile_zmq zmq/src/clock.cpp
compile_zmq zmq/src/socket_poller.cpp
compile_zmq zmq/src/err.cpp
compile_zmq zmq/src/server.cpp
compile_zmq zmq/src/ipc_listener.cpp
compile_zmq zmq/src/proxy.cpp
compile_zmq zmq/src/stream_engine.cpp
compile_zmq zmq/src/pair.cpp
compile_zmq zmq/src/raw_decoder.cpp
compile_zmq zmq/src/tipc_listener.cpp
compile_zmq zmq/src/address.cpp
compile_zmq zmq/src/ipc_connecter.cpp
compile_zmq zmq/src/dgram.cpp
compile_zmq zmq/src/dealer.cpp
compile_zmq zmq/src/random.cpp
compile_zmq zmq/src/zap_client.cpp
compile_zmq zmq/src/curve_client.cpp
compile_zmq zmq/src/push.cpp
compile_zmq zmq/src/zmq.cpp
compile_zmq zmq/src/poll.cpp
compile_zmq zmq/src/udp_engine.cpp
compile_zmq zmq/src/radio.cpp
compile_zmq zmq/src/epoll.cpp
compile_zmq zmq/src/socks.cpp
compile_zmq zmq/src/vmci.cpp
compile_zmq zmq/src/udp_address.cpp
compile_zmq zmq/src/socket_base.cpp
compile_zmq zmq/src/signaler.cpp
compile_zmq zmq/src/poller_base.cpp
compile_zmq zmq/src/ipc_address.cpp
compile_zmq zmq/src/pgm_receiver.cpp
compile_zmq zmq/src/tcp_listener.cpp
compile_zmq zmq/src/gssapi_client.cpp
compile_zmq zmq/src/vmci_address.cpp
compile_zmq zmq/src/fq.cpp
compile_zmq zmq/src/gssapi_server.cpp
compile_zmq zmq/src/plain_client.cpp
compile_zmq zmq/src/router.cpp
compile_zmq zmq/src/pgm_sender.cpp
compile_zmq zmq/src/plain_server.cpp
compile_zmq zmq/src/mechanism.cpp
compile_zmq zmq/src/gather.cpp
compile_zmq zmq/src/socks_connecter.cpp
compile_zmq zmq/src/metadata.cpp
compile_zmq zmq/src/decoder_allocators.cpp
compile_zmq zmq/src/xpub.cpp
compile_zmq zmq/src/session_base.cpp
compile_zmq zmq/src/ctx.cpp
compile_zmq zmq/src/xsub.cpp
compile_zmq zmq/src/req.cpp
compile_zmq zmq/src/mtrie.cpp
compile_zmq zmq/src/tcp_connecter.cpp
compile_zmq zmq/src/object.cpp
compile_zmq zmq/src/client.cpp
compile_zmq zmq/src/stream.cpp
compile_zmq zmq/src/reaper.cpp
compile_zmq zmq/src/curve_mechanism_base.cpp
compile_zmq zmq/src/mailbox.cpp
compile_zmq zmq/src/null_mechanism.cpp
compile_zmq zmq/src/thread.cpp
compile_zmq zmq/src/precompiled.cpp
compile_zmq zmq/src/options.cpp
compile_zmq zmq/src/tipc_address.cpp
compile_zmq zmq/src/pollset.cpp
compile_zmq zmq/src/msg.cpp
compile_zmq zmq/src/ip.cpp
compile_zmq zmq/src/vmci_listener.cpp
compile_zmq zmq/src/pull.cpp
compile_zmq zmq/src/tcp.cpp
compile_zmq zmq/src/mechanism_base.cpp
compile_zmq zmq/src/select.cpp
compile_zmq zmq/src/norm_engine.cpp
compile_zmq zmq/src/kqueue.cpp
compile_zmq zmq/src/vmci_connecter.cpp
compile_zmq zmq/src/v1_decoder.cpp
compile_zmq zmq/src/v2_encoder.cpp
compile_zmq zmq/src/v2_decoder.cpp
compile_zmq zmq/src/tipc_connecter.cpp
compile_zmq zmq/src/gssapi_mechanism_base.cpp
compile_zmq zmq/src/trie.cpp
compile_zmq zmq/src/zmq_utils.cpp
compile_zmq zmq/src/tcp_address.cpp

rm libsignals_server.a
ar rvcs libsignals_server.a || { exit 0; }
for item in ${SIGNALS_FILES[*]}
do
  ar rvcs libsignals_server.a $item || { exit 0; }
done

rm libzmq.a
ar rvcs libzmq.a || { exit 0; }
for item in ${ZMQ_FILES[*]}
do
  ar rvcs libzmq.a $item || { exit 0; }
done

rm -rf temp_build || { exit 0; }
