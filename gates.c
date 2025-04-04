#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

// OR gate
float train[][3] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}, 
};

// AND gate
// float train[][3] = {
//     {0, 0, 0},
//     {1, 0, 0},
//     {0, 1, 0},
//     {1, 1, 1},
// };

#define train_count sizeof(train) / sizeof(train[0])

float rand_float()
{
    // srand(time(0));
    srand(time(0));
    return (float) rand() / (float) RAND_MAX; // return random float from 0 to 1
}

float loss(float w1, float w2, float b)
{
    float result = 0.0f;
    for (int i = 0; i < train_count; i++)
    {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf((w1 * x1) + (w2 * x2) + b);
        float d = y - train[i][2];
        result += d*d;
        // printf("actual: %f, expected: %f \n", y, train[i][1]);
    }
    result /= train_count; // Mean Square Error 
    return result;
}

int main()
{
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-1;
    float rate = 1e-1;

    for (int i = 0; i < 100000; i++)
    {
        float c = loss(w1, w2, b);

        float dw1 = (loss(w1 + eps, w2, b) - c)/eps;
        float dw2 = (loss(w1, w2 + eps, b) - c)/eps;
        float db = (loss(w1, w2, b + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b -= rate*db;
    }

    printf("w1 = %f, w2 = %f, b = %f, c = %f \n", w1, w2, b, loss(w1, w2, b));

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d | %d = %f \n", i, j, sigmoidf(i*w1 + j*w2 + b));
        }
    }

    return 0;
}
