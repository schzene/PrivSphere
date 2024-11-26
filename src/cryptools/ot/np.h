

#ifndef OT_NP_H__
#define OT_NP_H__

#include "ot.h"
/** @addtogroup OT
        @{
*/
namespace nisl
{
  template <typename IO>
  class OTNP : public OT<OTNP<IO>>
  {
  public:
    IO *io;
    emp::Group *G = nullptr;
    bool delete_G = true;
    OTNP(IO *io, emp::Group *_G = nullptr)
    {
      this->io = io;
      if (_G == nullptr)
        G = new emp::Group();
      else
      {
        G = _G;
        delete_G = false;
      }
    }
    ~OTNP()
    {
      if (delete_G)
        delete G;
    }

    void send_impl(const block128 *data0, const block128 *data1, int length)
    {
      emp::BigInt d;
      G->get_rand_bn(d);
      emp::Point C = G->mul_gen(d);
      io->send_pt(&C);
      io->flush();

      emp::BigInt *r = new emp::BigInt[length];
      emp::BigInt *rc = new emp::BigInt[length];
      emp::Point *pk0 = new emp::Point[length], pk1, *gr = new emp::Point[length],
                 *Cr = new emp::Point[length];
      for (int i = 0; i < length; ++i)
      {
        G->get_rand_bn(r[i]);
        gr[i] = G->mul_gen(r[i]);
        rc[i] = r[i].mul(d, G->bn_ctx);
        rc[i] = rc[i].mod(G->order, G->bn_ctx);
        Cr[i] = G->mul_gen(rc[i]);
      }

      for (int i = 0; i < length; ++i)
      {
        io->recv_pt(G, &pk0[i]);
      }
      for (int i = 0; i < length; ++i)
      {
        io->send_pt(&gr[i]);
      }
      io->flush();

      block128 m[2];
      for (int i = 0; i < length; ++i)
      {
        pk0[i] = pk0[i].mul(r[i]);
        emp::Point inv = pk0[i].inv();
        pk1 = Cr[i].add(inv);
        m[0] = Hash::KDF128(pk0[i]);
        m[0] = xorBlocks(data0[i], m[0]);
        m[1] = Hash::KDF128(pk1);
        m[1] = xorBlocks(data1[i], m[1]);
        io->send_data(m, 2 * sizeof(block128));
      }

      delete[] r;
      delete[] gr;
      delete[] Cr;
      delete[] rc;
      delete[] pk0;
    }

    void send_impl(const block256 *data0, const block256 *data1, int length)
    {
      emp::BigInt d;
      G->get_rand_bn(d);
      emp::Point C = G->mul_gen(d);
      io->send_pt(&C);
      io->flush();

      emp::BigInt *r = new emp::BigInt[length];
      emp::BigInt *rc = new emp::BigInt[length];
      emp::Point *pk0 = new emp::Point[length], pk1, *gr = new emp::Point[length],
                 *Cr = new emp::Point[length];
      for (int i = 0; i < length; ++i)
      {
        G->get_rand_bn(r[i]);
        gr[i] = G->mul_gen(r[i]);
        rc[i] = r[i].mul(d, G->bn_ctx);
        rc[i] = rc[i].mod(G->order, G->bn_ctx);
        Cr[i] = G->mul_gen(rc[i]);
      }

      for (int i = 0; i < length; ++i)
      {
        io->recv_pt(G, &pk0[i]);
      }
      for (int i = 0; i < length; ++i)
      {
        io->send_pt(&gr[i]);
      }
      io->flush();

      alignas(32) block256 m[2];
      for (int i = 0; i < length; ++i)
      {
        pk0[i] = pk0[i].mul(r[i]);
        emp::Point inv = pk0[i].inv();
        pk1 = Cr[i].add(inv);
        m[0] = Hash::KDF256(pk0[i]);
        m[0] = xorBlocks(data0[i], m[0]);
        m[1] = Hash::KDF256(pk1);
        m[1] = xorBlocks(data1[i], m[1]);
        io->send_data(m, 2 * sizeof(block256));
      }

      delete[] r;
      delete[] gr;
      delete[] Cr;
      delete[] rc;
      delete[] pk0;
    }

    void recv_impl(block128 *data, const bool *b, int length)
    {
      emp::BigInt *k = new emp::BigInt[length];
      emp::Point *gr = new emp::Point[length];
      emp::Point pk[2];
      block128 m[2];
      emp::Point C;
      for (int i = 0; i < length; ++i)
        G->get_rand_bn(k[i]);

      io->recv_pt(G, &C);

      for (int i = 0; i < length; ++i)
      {
        if (b[i])
        {
          pk[1] = G->mul_gen(k[i]);
          emp::Point inv = pk[1].inv();
          pk[0] = C.add(inv);
        }
        else
        {
          pk[0] = G->mul_gen(k[i]);
        }
        io->send_pt(&pk[0]);
      }

      for (int i = 0; i < length; ++i)
      {
        io->recv_pt(G, &gr[i]);
        gr[i] = gr[i].mul(k[i]);
      }
      for (int i = 0; i < length; ++i)
      {
        int ind = b[i] ? 1 : 0;
        io->recv_data(m, 2 * sizeof(block128));
        data[i] = xorBlocks(m[ind], Hash::KDF128(gr[i]));
      }
      delete[] k;
      delete[] gr;
    }

    void recv_impl(block256 *data, const bool *b, int length)
    {
      emp::BigInt *k = new emp::BigInt[length];
      emp::Point *gr = new emp::Point[length];
      emp::Point pk[2];
      alignas(32) block256 m[2];
      emp::Point C;
      for (int i = 0; i < length; ++i)
        G->get_rand_bn(k[i]);

      io->recv_pt(G, &C);

      for (int i = 0; i < length; ++i)
      {
        if (b[i])
        {
          pk[1] = G->mul_gen(k[i]);
          emp::Point inv = pk[1].inv();
          pk[0] = C.add(inv);
        }
        else
        {
          pk[0] = G->mul_gen(k[i]);
        }
        io->send_pt(&pk[0]);
      }

      for (int i = 0; i < length; ++i)
      {
        io->recv_pt(G, &gr[i]);
        gr[i] = gr[i].mul(k[i]);
      }
      for (int i = 0; i < length; ++i)
      {
        int ind = b[i] ? 1 : 0;
        io->recv_data(m, 2 * sizeof(block256));
        data[i] = xorBlocks(m[ind], Hash::KDF256(gr[i]));
      }
      delete[] k;
      delete[] gr;
    }
  };
  /**@}*/
} // namespace nisl
#endif // OT_NP_H__
