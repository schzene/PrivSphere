#ifndef NETWORK_IO_CHANNEL
#define NETWORK_IO_CHANNEL

#include "io_channel.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

enum class LastCall
{
    None,
    Send,
    Recv
};

namespace nisl
{
    class NetIO : public IOChannel<NetIO>
    {
    public:
        bool is_server;
        int mysocket = -1;
        int consocket = -1;
        FILE *stream = nullptr;
        char *buffer = nullptr;
        bool has_sent = false;
        string addr;
        int port;
        uint64_t counter = 0;
        uint64_t num_rounds = 0;
        bool FBF_mode;
        LastCall last_call = LastCall::None;
        NetIO(const char *address, int port, bool full_buffer = false,
              bool quiet = false)
        {
            this->port = port;
            is_server = (address == nullptr);
            if (address == nullptr)
            {
                struct sockaddr_in dest;
                struct sockaddr_in serv;
                socklen_t socksize = sizeof(struct sockaddr_in);
                memset(&serv, 0, sizeof(serv));
                serv.sin_family = AF_INET;
                serv.sin_addr.s_addr =
                    htonl(INADDR_ANY);       /* set our address to any interface */
                serv.sin_port = htons(port); /* set the server port number */
                mysocket = socket(AF_INET, SOCK_STREAM, 0);
                int reuse = 1;
                setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse,
                           sizeof(reuse));
                if (::bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr)) <
                    0)
                {
                    perror("error: bind");
                    exit(1);
                }
                if (listen(mysocket, 1) < 0)
                {
                    perror("error: listen");
                    exit(1);
                }
                consocket = accept(mysocket, (struct sockaddr *)&dest, &socksize);
                close(mysocket);
            }
            else
            {
                addr = string(address);

                struct sockaddr_in dest;
                memset(&dest, 0, sizeof(dest));
                dest.sin_family = AF_INET;
                dest.sin_addr.s_addr = inet_addr(address);
                dest.sin_port = htons(port);

                while (1)
                {
                    consocket = socket(AF_INET, SOCK_STREAM, 0);

                    if (connect(consocket, (struct sockaddr *)&dest,
                                sizeof(struct sockaddr)) == 0)
                    {
                        break;
                    }

                    close(consocket);
                    usleep(1000);
                }
            }
            set_nodelay();
            stream = fdopen(consocket, "wb+");
            buffer = new char[NETWORK_BUFFER_SIZE];
            memset(buffer, 0, NETWORK_BUFFER_SIZE);
            if (full_buffer)
            {
                setvbuf(stream, buffer, _IOFBF, NETWORK_BUFFER_SIZE);
            }
            else
            {
                setvbuf(stream, buffer, _IONBF, NETWORK_BUFFER_SIZE);
            }
            this->FBF_mode = full_buffer;
            // if (!quiet)
            //   std::cout << "connected\n";
        }

        void sync()
        {
            int tmp = 0;
            if (is_server)
            {
                send_data(&tmp, 1);
                recv_data(&tmp, 1);
            }
            else
            {
                recv_data(&tmp, 1);
                send_data(&tmp, 1);
                flush();
            }
        }

        ~NetIO()
        {
            fflush(stream);
            close(consocket);
            delete[] buffer;
        }

        void set_FBF()
        {
            flush();
            setvbuf(stream, buffer, _IOFBF, NETWORK_BUFFER_SIZE);
        }

        void set_NBF()
        {
            flush();
            setvbuf(stream, buffer, _IONBF, NETWORK_BUFFER_SIZE);
        }

        void set_nodelay()
        {
            const int one = 1;
            setsockopt(consocket, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
        }

        void set_delay()
        {
            const int zero = 0;
            setsockopt(consocket, IPPROTO_TCP, TCP_NODELAY, &zero, sizeof(zero));
        }

        void flush() { fflush(stream); }

        void send_data(const void *data, int len, bool count_comm = true)
        {
            if (count_comm)
            {
                if (last_call != LastCall::Send)
                {
                    num_rounds++;
                    last_call = LastCall::Send;
                }
                counter += len;
            }
            int sent = 0;
            while (sent < len)
            {
                int res = fwrite(sent + (char *)data, 1, len - sent, stream);
                if (res >= 0)
                    sent += res;
                else
                    fprintf(stderr, "error: net_send_data %d\n", res);
            }
            has_sent = true;
        }

        void recv_data(void *data, int len, bool count_comm = true)
        {
            if (count_comm)
            {
                if (last_call != LastCall::Recv)
                {
                    num_rounds++;
                    last_call = LastCall::Recv;
                }
            }
            if (has_sent)
                fflush(stream);
            has_sent = false;
            int sent = 0;
            while (sent < len)
            {
                int res = fread(sent + (char *)data, 1, len - sent, stream);
                if (res >= 0)
                    sent += res;
                else
                    fprintf(stderr, "error: net_send_data %d\n", res);
            }
        }
    };
    /**@}*/

} // psphere::cryptools::comm
#endif // NETWORK_IO_CHANNEL