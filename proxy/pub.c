#include <zmq.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

const char* pub_endpoint = "ipc:///tmp/xsub";

int main() {

	puts(GIT_VERSION);
	puts(GIT_HASH);
	exit(0);

	void* ctx = zmq_ctx_new();

	if(NULL == ctx) {
		perror("ctx");
		exit(EXIT_FAILURE);
	}

	void* pub = zmq_socket(ctx, ZMQ_PUB);

	if(NULL == pub) {
		perror("pub");
		exit(EXIT_FAILURE);
	}

	if(0 != zmq_connect(pub, pub_endpoint)) {
		perror("connect pub");
		exit(EXIT_FAILURE);
	}

	size_t counter = 0;
	char message[128] = { 0 };
	size_t len = 0;

	while(1) {
		len = snprintf(message, 128, "ahoy, matey!: %zu", counter);
		(void) zmq_send(pub, message, len, 0);
		++counter;

		usleep(2E6);
	}

	return 0;
}
