#ifndef IO_CHANNEL_H__
#define IO_CHANNEL_H__
#include "block.h"
#include "group.h"
namespace nisl
{
    template <typename T>
    class IOChannel
    {
    public:
        void send_data(const void *data, int nbyte)
        {
            derived().send_data(data, nbyte);
        }
        void recv_data(void *data, int nbyte) { derived().recv_data(data, nbyte); }

        void send_block(const block128 *data, int nblock)
        {
            send_data(data, nblock * sizeof(block128));
        }

        void send_block(const block256 *data, int nblock)
        {
            send_data(data, nblock * sizeof(block256));
        }

        void recv_block(block128 *data, int nblock)
        {
            recv_data(data, nblock * sizeof(block128));
        }

        void send_pt(emp::Point *A, int num_pts = 1)
        {
            for (int i = 0; i < num_pts; ++i)
            {
                size_t len = A[i].size();
                A[i].group->resize_scratch(len);
                unsigned char *tmp = A[i].group->scratch;
                send_data(&len, 4);
                A[i].to_bin(tmp, len);
                send_data(tmp, len);
            }
        }

        void recv_pt(emp::Group *g, emp::Point *A, int num_pts = 1)
        {
            size_t len = 0;
            for (int i = 0; i < num_pts; ++i)
            {
                recv_data(&len, 4);
                g->resize_scratch(len);
                unsigned char *tmp = g->scratch;
                recv_data(tmp, len);
                A[i].from_bin(g, tmp, len);
            }
        }

    private:
        T &derived() { return *static_cast<T *>(this); }
    };
} // namespace privsphere
#endif // IO_CHANNEL_H__