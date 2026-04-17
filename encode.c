#include <stdint.h>
#include <string.h>

/**
 * @brief  255进制编码（输出无 0x00）
 * @param  in      原始数据
 * @param  in_len  原始长度
 * @param  out     输出缓冲区
 * @return 输出长度
 */
int encode_no_zero(const uint8_t *in, int in_len, uint8_t *out)
{
    if (in_len <= 0) return 0;

    memset(out, 0, 512);
    int out_len = 0;

    for (int i = 0; i < in_len; i++)
    {
        uint16_t carry = in[i];
        for (int j = 0; j < out_len; j++)
        {
            carry += (uint16_t)out[j] * 256;
            out[j] = carry % 255;
            carry /= 255;
        }
        while (carry > 0)
        {
            out[out_len++] = carry % 255;
            carry /= 255;
        }
    }

    // +1 保证没有 0x00
    for (int i = 0; i < out_len; i++)
        out[i] += 1;

    return out_len;
}

/**
 * @brief  255进制解码（还原原始数据）
 * @param  in      编码后数据（无 0x00）
 * @param  in_len  编码长度
 * @param  out     原始数据输出
 * @return 解码长度，-1=错误
 */
int decode_no_zero(const uint8_t *in, int in_len, uint8_t *out)
{
    if (in_len <= 0) return 0;

    memset(out, 0, 512);
    int out_len = 0;

    for (int i = 0; i < in_len; i++)
    {
        if (in[i] == 0) return -1;  // 非法数据

        uint16_t carry = in[i] - 1;  // 先 -1 还原
        for (int j = 0; j < out_len; j++)
        {
            carry += (uint16_t)out[j] * 255;
            out[j] = carry % 256;
            carry /= 256;
        }
        while (carry > 0)
        {
            out[out_len++] = carry % 256;
            carry /= 256;
        }
    }

    return out_len;
}
