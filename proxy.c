#include <zmq.h>
#include <stdlib.h>

const char* sub_endpoint = "ipc:///tmp/xsub";
const char* pub_endpoint = "ipc:///tmp/xpub";

int main() {
	void* ctx = zmq_ctx_new();

	if(NULL == ctx) {
		perror("ctx");
		exit(EXIT_FAILURE);
	}

	void* sub = zmq_socket(ctx, ZMQ_XSUB);
	void* pub = zmq_socket(ctx, ZMQ_XPUB);

	if(NULL == sub) {
		perror("sub");
		exit(EXIT_FAILURE);
	}

	if(NULL == pub) {
		perror("pub");
		exit(EXIT_FAILURE);
	}

	if(0 != zmq_bind(sub, sub_endpoint)) {
		perror("bind sub");
		exit(EXIT_FAILURE);
	}

	if(0 != zmq_bind(pub, pub_endpoint)) {
		perror("bind pub");
		exit(EXIT_FAILURE);
	}

	zmq_proxy(sub, pub, NULL);
	return 0;
}
