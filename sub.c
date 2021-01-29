#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char* sub_endpoint = "ipc:///tmp/xpub";

int main() {
	void* ctx = zmq_ctx_new();

	if(NULL == ctx) {
		perror("ctx");
		exit(EXIT_FAILURE);
	}

	void* sub = zmq_socket(ctx, ZMQ_SUB);

	if(NULL == sub) {
		perror("sub");
		exit(EXIT_FAILURE);
	}

	if(0 != zmq_setsockopt(sub, ZMQ_SUBSCRIBE, "", 0)) {
		perror("subscribe");
		exit(EXIT_FAILURE);
	}

	if(0 != zmq_connect(sub, sub_endpoint)) {
		perror("connect sub");
		exit(EXIT_FAILURE);
	}

	char message[128] = { 0 };

	while(1) {
		(void) zmq_recv(sub, message, 128, 0);
		puts(message);
		memset(message, 0, 128);
	}

	return 0;
}
