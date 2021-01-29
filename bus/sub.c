#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


float get_f(const uint8_t* buffer)
{
  float r;
  memcpy(&r, buffer, sizeof(r));
  return r;
}


uint64_t get_u8(const uint8_t* buffer)
{
  uint64_t r;
  memcpy(&r, buffer, sizeof(r));
  return r;
}


uint32_t get_u4(const uint8_t* buffer)
{
  uint32_t r;
  memcpy(&r, buffer, sizeof(r));
  return r;
}


int main(int argc, char** argv) {
	void* ctx = zmq_ctx_new();
	void* sub_socket = zmq_socket(ctx, ZMQ_SUB);

	zmq_setsockopt(sub_socket, ZMQ_SUBSCRIBE, "", 0);
	zmq_connect(sub_socket, "tcp://alarmpi:5010");

	char message[1024] = { 0 };

  //MPU_9250_Thing thing;

	while(1) {
		ssize_t _len = zmq_recv(sub_socket, message, 1024, 0);
		//ssize_t _len = zmq_recv(sub_socket, &thing, 1024, 0);

    //const uint64_t _ = get_u8(message);
    //const uint32_t __ = get_u4(message);

    //printf("%lu,%u,%lu,%u\n", _, _, __, __);

    const uint64_t bs = get_u4(message);
    const uint32_t bu = get_u4(message + 4);
    const uint64_t es = get_u4(message + 8);
    const uint32_t eu = get_u4(message + 12);

    const float ax = get_f(message + 16);
    const float ay = get_f(message + 20);
    const float az = get_f(message + 24);

    const float gx = get_f(message + 28);
    const float gy = get_f(message + 32);
    const float gz = get_f(message + 36);

    printf(
        "%lu.%.9u,%lu.%.9u,%3.8f,%3.8f,%3.8f,%5.8f,%5.8f,%5.8f\n", bs, bu, es, eu, ax, ay, az, gx, gy, gz);

//    struct timespec ts;
//
//    clock_gettime(CLOCK_REALTIME, &ts);
//
//    printf("%lu.%u\n", ts.tv_sec, ts.tv_nsec);



    //for(ssize_t i = 0; i < _len; i++)
    //{
    //  printf("%.2X,", message[i] & 0xff);
    //}
    //puts("");
	}

	return 0;
}
