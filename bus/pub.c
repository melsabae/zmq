#include <zmq.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
	void* ctx = zmq_ctx_new();
	void* pub_socket = zmq_socket(ctx, ZMQ_PUB);
	zmq_connect(pub_socket, "tcp://alarmpi:5001");

	while(1) {
		zmq_send(pub_socket, "ahoy, matey!", strlen("ahoy, matey!"), 0);
		sleep(2);
	}

	return 0;
}
