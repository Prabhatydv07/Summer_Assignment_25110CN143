#include <stdio.h>

long long reverse(long long n, long long rev) {
    if (n == 0) return rev;           // base case
    return reverse(n / 10, rev * 10 + n % 10);  // pass rev as parameter
}

int main() {
    long long n;
    printf("Enter the number : ");
    scanf("%lld", &n);

    long long org = n;
    if (n < 0) n = -n;

    long long result = reverse(n, 0);  // start with rev=0

    if (org < 0)
        printf("Reversed number : -%lld\n", result);
    else
        printf("Reversed number : %lld\n", result);

    return 0;
}