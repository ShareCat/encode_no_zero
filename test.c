#include <stdio.h>

void print_hex(const char *name, const uint8_t *data, int len)
{
    printf("%-15s", name);
    for (int i = 0; i < len; i++)
        printf("%02X ", data[i]);
    printf("\n");
}

int main()
{
    // 测试数据（包含大量 0x00）
    uint8_t raw[] = { 0x00, 0x12, 0x00, 0x34, 0x56, 0x00 };
    int raw_len = sizeof(raw);

    uint8_t enc[256];
    uint8_t dec[256];

    int enc_len = encode_no_zero(raw, raw_len, enc);
    int dec_len = decode_no_zero(enc, enc_len, dec);

    print_hex("原始数据:", raw, raw_len);
    print_hex("编码后(无00):", enc, enc_len);
    print_hex("解码数据:", dec, dec_len);

    return 0;
}
