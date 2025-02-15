
#ifndef MXNET_OPERATOR_NEW_FORWARD_H_
#define MXNET_OPERATOR_NEW_FORWARD_H_

#include <mxnet/base.h>

namespace mxnet
{
namespace op
{


template <typename cpu, typename DType>
void forward(mshadow::Tensor<cpu, 4, DType> &y, const mshadow::Tensor<cpu, 4, DType> &x, const mshadow::Tensor<cpu, 4, DType> &k)
{
    const int B = x.shape_[0];
    const int M = y.shape_[1];
    const int C = x.shape_[1];
    const int H = x.shape_[2];
    const int W = x.shape_[3];
    const int K = k.shape_[3];

    const int H_out = H - K + 1;
    const int W_out = W - K + 1;

    for (int b = 0; b < B; ++b) {
	    for(int m = 0; m < M; ++m) {
		    for(int h = 0; h < H_out; ++h) {
			    for(int w = 0; w < W_out; ++w) {
				    y[b][m][h][w] = 0;
				    for(int c = 0; c < C; ++c) {
					    for(int p = 0; p < K; ++p) {
					        for(int q = 0; q < K; ++q) {
                                y[b][m][h][w] += x[b][c][h + p][w + q] * k[m][c][p][q];
					        }
					    }
				    }
			    }
		    }
        }
    }    
}

}
}

#endif
