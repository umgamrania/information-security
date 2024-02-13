#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <stdint.h>

bool RANDOM_SEED_SET = false;

uint64_t power(int64_t base, uint64_t exp) {
    // getting no. of bits in exp before making any changes to exp
    int64_t bits = (int64_t)log2(exp)+1;

    // taking all the bits and right-aligning them
    exp = exp << __builtin_clzll(exp);

    // the number already has exponent of 1, so the msb needs to be ignored
    exp = exp << 1;

    uint64_t filter = (uint64_t)(1) << (sizeof(uint64_t) * 8 - 1);
    uint64_t ans = base;

    for(uint64_t i = 0; i < bits - 1; i++){
        uint64_t bit = (exp & filter) == filter;
        ans = ans * ans;
        if(bit)
            ans = ans * base;
        exp = exp << 1;
    }

    return ans;
}

int64_t power_mod(int64_t base, uint64_t exp, int64_t mod) {
    // getting no. of bits in exp before making any changes to exp
    int64_t bits = (int64_t)log2(exp)+1;

    // taking all the bits and right-aligning them
    exp = exp << __builtin_clzll(exp);

    // the number already has exponent of 1, so the msb needs to be ignored
    exp = exp << 1;

    uint64_t filter = (uint64_t)(1) << (sizeof(uint64_t) * 8 - 1);
    uint64_t ans = base;

    for(uint64_t i = 0; i < bits - 1; i++){
        uint64_t bit = (exp & filter) == filter;
        ans = (ans * ans) % mod;
        if(bit)
            ans = (ans * base) % mod;
        exp = exp << 1;
    }

    return ans;
}

int64_t gcd(int64_t a, int64_t b) {
    while(a!=b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }
}

int64_t is_prime(int64_t n) {
    for(int64_t i = 2; i < (int64_t)(n/2); i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}

void set_rand_seed() {
    srand(time(NULL));
    RANDOM_SEED_SET = true;
}

uint64_t random_num(int64_t digits) {
    if(!RANDOM_SEED_SET)
        set_rand_seed();

    // generating a 64 bit random number
    // rand() by default, returns int (32 bits)
    uint64_t big_random = (uint64_t)rand() << 32;
    big_random += (uint64_t)rand();
    uint64_t num = (big_random * (uint64_t)rand()) % power(10, digits);
    return num;
}

uint64_t random_prime(int64_t digits) {
    uint64_t num = random_num(digits);

    while(!is_prime(num))
        num++;

    return num;
}

uint64_t compute_e(uint64_t p, uint64_t q) {
    uint64_t phi = (p - 1) * (q - 1);

    if(phi > 65537) {
        return 65537;
    }
    else {
        // starting from reverse to avoid small numbers
        for(uint64_t i = phi - 1; i > 2; i--) {
            if(gcd(i, phi) == 1) {
                return i;
            }
        }
    }
}

uint64_t compute_d(uint64_t e, uint64_t p, uint64_t q) {
    uint64_t k = 2;
    uint64_t phi = (p - 1) * (q - 1);

    while(1) {
        uint64_t temp = (1 + k * phi);
        if(temp % e == 0) {
            return (int)(temp / e);
        }
        k++;
    }
}

int64_t main() {
    uint64_t p = random_prime(5);
    printf("p %ld\n", p);
    uint64_t q = random_prime(5);
    printf("q %ld\n", q);
    uint64_t n = p * q;
    uint64_t e = compute_e(p, q);
    printf("e %ld\n", e);
    uint64_t d = compute_d(e, p, q);
    printf("d %ld\n", d);

    uint64_t pt = 16;
    uint64_t ct = power_mod(pt, e, n);
    printf("%ld\n", ct);
    uint64_t dt = power_mod(ct, d, n);
    printf("%ld\n", dt);
    return 0;
}