#include "weights.h"

#define INPUT 784
#define HIDDEN 16
#define OUTPUT 10

void inference(float input[INPUT], float output[OUTPUT])
{

    float hidden[HIDDEN];

    // -------- Layer 1 --------
    for(int j=0;j<HIDDEN;j++)
    {
        float sum = b1[j];

        for(int i=0;i<INPUT;i++)
        {
#pragma HLS PIPELINE II=1
            sum += W1[i][j] * input[i];
        }

        // ReLU
        if(sum < 0)
            hidden[j] = 0;
        else
            hidden[j] = sum;
    }

    // -------- Layer 2 --------
    for(int j=0;j<OUTPUT;j++)
    {
        float sum = b2[j];

        for(int i=0;i<HIDDEN;i++)
        {
#pragma HLS PIPELINE II=1
            sum += W2[i][j] * hidden[i];
        }

        output[j] = sum;
    }
}
