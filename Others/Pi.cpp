int main() {
    srand((unsigned)time(0)); // time(0)表示从1970到现在的秒数
    int N = (int)1e7, cnt = 0;
    for (int i = 0; i < N; i++) {
        double a = (1.0 * rand() / RAND_MAX); // 除以RAND_MAX归一化0~1
        double b = (1.0 * rand() / RAND_MAX);
        if (a * a + b * b < 1.0) cnt++; // 落入1/4圆则加一
    }
    printf("%lf", (4.0 * cnt) / N);
    return 0;
}
