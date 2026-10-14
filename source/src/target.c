#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <err.h>

#define BUF_SIZE 0x470
#define FLAG_SIZE 0x410

void print_key(char *input) {
    char command[20];
    sprintf(command, "cat /%s", input);
    system(command);
}

void lower_toupper(char *c) {
    c[0] += 'A' - 'a'; 
}

void num_toupper(char *c) {
    c[0] += 'A' - '0';
}

void memcpy_toupper(void *dst, const void *src, size_t n) {
    char *d = (char *)dst;
    const char *s = (const char *)src;
    
    for (size_t i = 0; i < n - 1; i++) {
        d[i] = s[i];
        if (d[i] >= 'a' && d[i] <= 'z') {
            lower_toupper(d + i);
        } else if (d[i] >= '0' && d[i] <= '9'){
            num_toupper(d + i);
        }
    }

    d[n - 1] = '\0';
}

void vuln(char *fake_data) {
    if (strlen(fake_data) != FLAG_SIZE) {
        return;
    }
    
    char size_buf[20];

    char output[BUF_SIZE];
    memset(output, 0, BUF_SIZE);

    char input[BUF_SIZE];
    memset(input, 0, BUF_SIZE);

    printf("Give me the size:\n");
    fgets(size_buf, sizeof(size_buf), stdin);

    int size = atoi(size_buf);

    printf("Give me the input:\n");
    fgets(input, size, stdin);

    memcpy_toupper(output, input, size);

    printf("The output:\n");
    printf(output);
    printf("\n");

    char FLAG[] = "FLAG";

    if (strstr(output, FLAG) != NULL) {
        printf("You get the FAKE one:\n");
        fwrite(fake_data, 1, strlen(fake_data), stdout);
        return;
    }

    unsigned char encoded[] = {0x66^0x33, 0x6c^0x33, 0x61^0x33, 0x67^0x33};
    char lower_FLAG[5];
    int key = 0x33;
    
    for (int i = 0; i < 4; i++) {
        lower_FLAG[i] = encoded[i] ^ key;
    }
    lower_FLAG[4] = '\0';

    if (strstr(output, lower_FLAG) != NULL) {
        printf("You get the REAL one:\n");
        print_key(lower_FLAG);
    }
}

int main() {
    char fake_data[FLAG_SIZE];
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = 36;
    
    srand(time(NULL));
    
    int pos = 0;
    for (int line = 0; line < 16; line++) {
        for (int col = 0; col < 64; col++) {
            fake_data[pos++] = charset[rand() % charset_size];
        }
        fake_data[pos++] = '\n';
    }
    fake_data[pos] = '\0';

    vuln(fake_data);

    return 0;
}
