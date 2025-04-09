module {
  func.func @main(%arg0: tensor<1x128x768xf32>, %arg1: tensor<1x1x1x128xf32>) -> tensor<1x128x768xf32> {
    %0 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32_5> : tensor<768xf32>}> : () -> tensor<768xf32>  # LN2_b
    %1 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32_4> : tensor<768xf32>}> : () -> tensor<768xf32>  # LN2_w
    %2 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32_3> : tensor<768xf32>}> : () -> tensor<768xf32>  # Linear-bias
    %3 = "tosa.const"() <{value = dense_resource<torch_tensor_768_3072_torch.float32> : tensor<768x3072xf32>}> : () -> tensor<768x3072xf32>  # Linear-weight
    %4 = "tosa.const"() <{value = dense_resource<torch_tensor_3072_torch.float32> : tensor<3072xf32>}> : () -> tensor<3072xf32>  # Linear-bias
    %5 = "tosa.const"() <{value = dense_resource<torch_tensor_3072_768_torch.float32> : tensor<3072x768xf32>}> : () -> tensor<3072x768xf32>  # Linear-weight
    %6 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32_2> : tensor<768xf32>}> : () -> tensor<768xf32>  # LN1_b
    %7 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32_1> : tensor<768xf32>}> : () -> tensor<768xf32>  # LN1_w
    %8 = "tosa.const"() <{value = dense_resource<torch_tensor_768_torch.float32> : tensor<768xf32>}> : () -> tensor<768xf32>  # Linear-bias
    %9 = "tosa.const"() <{value = dense_resource<torch_tensor_768_768_torch.float32> : tensor<768x768xf32>}> : () -> tensor<768x768xf32>  # Linear-weight
    %10 = "tosa.const"() <{value = dense_resource<torch_tensor_2304_768_torch.float32> : tensor<2304x768xf32>}> : () -> tensor<2304x768xf32>  # Linear-weight
    %11 = "tosa.const"() <{value = dense_resource<torch_tensor_2304_torch.float32> : tensor<2304xf32>}> : () -> tensor<2304xf32>  # Linear-bias
    %12 = "tosa.const"() <{value = dense<[1, 0]> : tensor<2xi32>}> : () -> tensor<2xi32>  # transpose
    %13 = "tosa.const"() <{value = dense<[0, 2, 1, 3]> : tensor<4xi32>}> : () -> tensor<4xi32>  # transpose
    %14 = "tosa.const"() <{value = dense<[0, 2, 3, 1]> : tensor<4xi32>}> : () -> tensor<4xi32>  # transpose
    %15 = "tosa.const"() <{value = dense<1.250000e-01> : tensor<1x1x1x1xf32>}> : () -> tensor<1x1x1x1xf32>  # 1/sqrt(dk), dk = 64
    %16 = "tosa.const"() <{value = dense<0.00130208337> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # 1/n, n = 768
    %17 = "tosa.const"() <{value = dense<9.99999996E-13> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # eps = 1e-12
    %18 = "tosa.const"() <{value = dense<0.707106769> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a = 1/sqrt(2)
    %19 = "tosa.const"() <{value = dense<2.783930e-01> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a1 = 0.278393
    %20 = "tosa.const"() <{value = dense<1.000000e+00> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a0 = 1
    %21 = "tosa.const"() <{value = dense<2.303890e-01> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a2 = 0.230389
    %22 = "tosa.const"() <{value = dense<9.720000e-04> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a3 = 9.72e-4
    %23 = "tosa.const"() <{value = dense<7.810800e-02> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # a4 = 0.078108
    %24 = "tosa.const"() <{value = dense<0.000000e+00> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # 0
    %25 = "tosa.const"() <{value = dense<5.000000e-01> : tensor<1x1x1xf32>}> : () -> tensor<1x1x1xf32>  # 0.5
    %26 = "tosa.const"() <{value = dense<""> : tensor<1x98304xi32>}> : () -> tensor<1x98304xi32>  select-Q
    %27 = "tosa.const"() <{value = dense<""> : tensor<1x98304xi32>}> : () -> tensor<1x98304xi32>  select-K
    %28 = "tosa.const"() <{value = dense<""> : tensor<1x98304xi32>}> : () -> tensor<1x98304xi32>  select-V
Attn┍ Linear┍     %29 = tosa.transpose %10, %12 : (tensor<2304x768xf32>, tensor<2xi32>) -> tensor<768x2304xf32>
    |       |     %30 = tosa.reshape %29 {new_shape = array<i64: 1, 768, 2304>} : (tensor<768x2304xf32>) -> tensor<1x768x2304xf32>
    |       |     %31 = tosa.matmul %arg0, %30 : (tensor<1x128x768xf32>, tensor<1x768x2304xf32>) -> tensor<1x128x2304xf32>
    |       |     %32 = tosa.reshape %11 {new_shape = array<i64: 1, 1, 2304>} : (tensor<2304xf32>) -> tensor<1x1x2304xf32>
    | Linear└     %33 = tosa.add %31, %32 : (tensor<1x128x2304xf32>, tensor<1x1x2304xf32>) -> tensor<1x128x2304xf32>
    | fatten-QKV  %34 = tosa.reshape %33 {new_shape = array<i64: 1, 294912, 1>} : (tensor<1x128x2304xf32>) -> tensor<1x294912x1xf32>
    | Q(chunk)    %35 = tosa.gather %34, %26 : (tensor<1x294912x1xf32>, tensor<1x98304xi32>) -> tensor<1x98304x1xf32>
    | K(chunk)    %36 = tosa.gather %34, %27 : (tensor<1x294912x1xf32>, tensor<1x98304xi32>) -> tensor<1x98304x1xf32>
    | V(chunk)    %37 = tosa.gather %34, %28 : (tensor<1x294912x1xf32>, tensor<1x98304xi32>) -> tensor<1x98304x1xf32>
    | Q_head┍     %38 = tosa.reshape %35 {new_shape = array<i64: 1, 128, 12, 64>} : (tensor<1x98304x1xf32>) -> tensor<1x128x12x64xf32>
    | Q_head└     %39 = tosa.transpose %38, %13 : (tensor<1x128x12x64xf32>, tensor<4xi32>) -> tensor<1x12x128x64xf32>
    | K_head┍     %40 = tosa.reshape %36 {new_shape = array<i64: 1, 128, 12, 64>} : (tensor<1x98304x1xf32>) -> tensor<1x128x12x64xf32>
    | K_head└     %41 = tosa.transpose %40, %14 : (tensor<1x128x12x64xf32>, tensor<4xi32>) -> tensor<1x12x64x128xf32>
    | V_head┍     %42 = tosa.reshape %37 {new_shape = array<i64: 1, 128, 12, 64>} : (tensor<1x98304x1xf32>) -> tensor<1x128x12x64xf32>
    | V_head└     %43 = tosa.transpose %42, %13 : (tensor<1x128x12x64xf32>, tensor<4xi32>) -> tensor<1x12x128x64xf32>
    | QK┍         %44 = tosa.reshape %39 {new_shape = array<i64: 12, 128, 64>} : (tensor<1x12x128x64xf32>) -> tensor<12x128x64xf32>
    |   |         %45 = tosa.reshape %41 {new_shape = array<i64: 12, 64, 128>} : (tensor<1x12x64x128xf32>) -> tensor<12x64x128xf32>
    |   |         %46 = tosa.matmul %44, %45 : (tensor<12x128x64xf32>, tensor<12x64x128xf32>) -> tensor<12x128x128xf32>
    | QK└         %47 = tosa.reshape %46 {new_shape = array<i64: 1, 12, 128, 128>} : (tensor<12x128x128xf32>) -> tensor<1x12x128x128xf32>
    | QK/sqrt(dk) %48 = tosa.mul %47, %15 {shift = 0 : i8} : (tensor<1x12x128x128xf32>, tensor<1x1x1x1xf32>) -> tensor<1x12x128x128xf32>
    | score+mask  %49 = tosa.add %48, %arg1 : (tensor<1x12x128x128xf32>, tensor<1x1x1x128xf32>) -> tensor<1x12x128x128xf32>  # attention_mask
    | SoftMax┍    %50 = tosa.reduce_max %49 {axis = 3 : i32} : (tensor<1x12x128x128xf32>) -> tensor<1x12x128x1xf32>
    |        |    %51 = tosa.sub %49, %50 : (tensor<1x12x128x128xf32>, tensor<1x12x128x1xf32>) -> tensor<1x12x128x128xf32>
    |        |    %52 = tosa.exp %51 : (tensor<1x12x128x128xf32>) -> tensor<1x12x128x128xf32>
    |        |    %53 = tosa.reduce_sum %52 {axis = 3 : i32} : (tensor<1x12x128x128xf32>) -> tensor<1x12x128x1xf32>
    |        |    %54 = tosa.reciprocal %53 : (tensor<1x12x128x1xf32>) -> tensor<1x12x128x1xf32>
    | SoftMax└    %55 = tosa.mul %52, %54 {shift = 0 : i8} : (tensor<1x12x128x128xf32>, tensor<1x12x128x1xf32>) -> tensor<1x12x128x128xf32>
    | score*V┍    %56 = tosa.reshape %55 {new_shape = array<i64: 12, 128, 128>} : (tensor<1x12x128x128xf32>) -> tensor<12x128x128xf32>
    |        |    %57 = tosa.reshape %43 {new_shape = array<i64: 12, 128, 64>} : (tensor<1x12x128x64xf32>) -> tensor<12x128x64xf32>
    | score*V└    %58 = tosa.matmul %56, %57 : (tensor<12x128x128xf32>, tensor<12x128x64xf32>) -> tensor<12x128x64xf32>
    | concat┍     %59 = tosa.reshape %58 {new_shape = array<i64: 1, 12, 128, 64>} : (tensor<12x128x64xf32>) -> tensor<1x12x128x64xf32>
    |       |     %60 = tosa.transpose %59, %13 : (tensor<1x12x128x64xf32>, tensor<4xi32>) -> tensor<1x128x12x64xf32>
    | concat└     %61 = tosa.reshape %60 {new_shape = array<i64: 1, 128, 768>} : (tensor<1x128x12x64xf32>) -> tensor<1x128x768xf32>
    | Linear┍     %62 = tosa.transpose %9, %12 : (tensor<768x768xf32>, tensor<2xi32>) -> tensor<768x768xf32>
    |       |     %63 = tosa.reshape %62 {new_shape = array<i64: 1, 768, 768>} : (tensor<768x768xf32>) -> tensor<1x768x768xf32>
    |       |     %64 = tosa.matmul %61, %63 : (tensor<1x128x768xf32>, tensor<1x768x768xf32>) -> tensor<1x128x768xf32>
    |       |     %65 = tosa.reshape %8 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
Attn└ Linear└     %66 = tosa.add %64, %65 : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
LN┍ input+x       %67 = tosa.add %66, %arg0 : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  | μ┍            %68 = tosa.reduce_sum %67 {axis = 2 : i32} : (tensor<1x128x768xf32>) -> tensor<1x128x1xf32>
  | μ└            %69 = tosa.mul %68, %16 {shift = 0 : i8} : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  | extend μ      %70 = tosa.tile %69 {multiples = array<i64: 1, 1, 768>} : (tensor<1x128x1xf32>) -> tensor<1x128x768xf32>
  | x-μ           %71 = tosa.sub %67, %70 : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  | σ^2┍          %72 = tosa.mul %71, %71 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  |    |          %73 = tosa.reduce_sum %72 {axis = 2 : i32} : (tensor<1x128x768xf32>) -> tensor<1x128x1xf32>
  | σ^2└          %74 = tosa.mul %73, %16 {shift = 0 : i8} : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  | σ^2+eps       %75 = tosa.add %74, %17 : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  | 1/σ           %76 = tosa.rsqrt %75 : (tensor<1x128x1xf32>) -> tensor<1x128x1xf32>
  | extend 1/σ    %77 = tosa.tile %76 {multiples = array<i64: 1, 1, 768>} : (tensor<1x128x1xf32>) -> tensor<1x128x768xf32>
  | (x-μ)/σ       %78 = tosa.mul %71, %77 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  | w*x+b┍        %79 = tosa.reshape %7 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
  |      |        %80 = tosa.mul %78, %79 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
  |      |        %81 = tosa.reshape %6 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
LN└ w*x+b└        %82 = tosa.add %80, %81 : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
FFN┍ Linear┍      %83 = tosa.transpose %5, %12 : (tensor<3072x768xf32>, tensor<2xi32>) -> tensor<768x3072xf32>
   |       |      %84 = tosa.reshape %83 {new_shape = array<i64: 1, 768, 3072>} : (tensor<768x3072xf32>) -> tensor<1x768x3072xf32>
   |       |      %85 = tosa.matmul %82, %84 : (tensor<1x128x768xf32>, tensor<1x768x3072xf32>) -> tensor<1x128x3072xf32>
   |       |      %86 = tosa.reshape %4 {new_shape = array<i64: 1, 1, 3072>} : (tensor<3072xf32>) -> tensor<1x1x3072xf32>
   | Linear└      %87 = tosa.add %85, %86 : (tensor<1x128x3072xf32>, tensor<1x1x3072xf32>) -> tensor<1x128x3072xf32>
   | GELU┍ f┍     %88 = tosa.mul %87, %18 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %89 = tosa.abs %88 : (tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %90 = tosa.mul %89, %19 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %91 = tosa.add %90, %20 : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %92 = tosa.mul %89, %89 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %93 = tosa.mul %92, %21 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %94 = tosa.add %91, %93 : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %95 = tosa.mul %92, %89 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %96 = tosa.mul %95, %22 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %97 = tosa.add %94, %96 : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %98 = tosa.mul %95, %89 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     |  |     %99 = tosa.mul %98, %23 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>
   |     | f└     %100 = tosa.add %97, %99 : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # f = a4(|ax|)^4+a3(|ax|)^3+a2(|ax|)^2+a1(|ax|)^1+a0
   |     | 1/f    %101 = tosa.reciprocal %100 : (tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>
   |     | erf┍   %102 = tosa.mul %101, %101 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # 1/f^2
   |     |    |   %103 = tosa.mul %102, %102 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # 1/f^4
   |     |    |   %104 = tosa.sub %20, %103 : (tensor<1x1x1xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # 1-1/f^4, erf(x/sqrt(2))(x>0)
   |     |    |   %105 = tosa.greater_equal %88, %24 : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xi1>
   |     |    |   %106 = tosa.negate %104 : (tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # 1/f^4 - 1, erf(x/sqrt(2))(x<0)
   |     | erf└   %107 = tosa.select %105, %104, %106 : (tensor<1x128x3072xi1>, tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # erf
   |     | gelu┍  %108 = tosa.add %107, %20 : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>  # 1 + erf(x/sqrt(2))
   |     |     |  %109 = tosa.mul %108, %25 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x1x1xf32>) -> tensor<1x128x3072xf32>  # 0.5(1 + erf(x/sqrt(2)))
   | GELU└ gelu└  %110 = tosa.mul %87, %109 {shift = 0 : i8} : (tensor<1x128x3072xf32>, tensor<1x128x3072xf32>) -> tensor<1x128x3072xf32>  # 0.5x(1 + erf(x/sqrt(2)))  
   | Linear┍      %111 = tosa.transpose %3, %12 : (tensor<768x3072xf32>, tensor<2xi32>) -> tensor<3072x768xf32>
   |       |      %112 = tosa.reshape %111 {new_shape = array<i64: 1, 3072, 768>} : (tensor<3072x768xf32>) -> tensor<1x3072x768xf32>
   |       |      %113 = tosa.matmul %110, %112 : (tensor<1x128x3072xf32>, tensor<1x3072x768xf32>) -> tensor<1x128x768xf32>
   |       |      %114 = tosa.reshape %2 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
   └ Linear└      %115 = tosa.add %113, %114 : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
LN┍               %116 = tosa.add %115, %82 : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  |               %117 = tosa.reduce_sum %116 {axis = 2 : i32} : (tensor<1x128x768xf32>) -> tensor<1x128x1xf32>
  |               %118 = tosa.mul %117, %16 {shift = 0 : i8} : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  |               %119 = tosa.tile %118 {multiples = array<i64: 1, 1, 768>} : (tensor<1x128x1xf32>) -> tensor<1x128x768xf32>
  |               %120 = tosa.sub %116, %119 : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  |               %121 = tosa.mul %120, %120 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  |               %122 = tosa.reduce_sum %121 {axis = 2 : i32} : (tensor<1x128x768xf32>) -> tensor<1x128x1xf32>
  |               %123 = tosa.mul %122, %16 {shift = 0 : i8} : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  |               %124 = tosa.add %123, %17 : (tensor<1x128x1xf32>, tensor<1x1x1xf32>) -> tensor<1x128x1xf32>
  |               %125 = tosa.rsqrt %124 : (tensor<1x128x1xf32>) -> tensor<1x128x1xf32>
  |               %126 = tosa.tile %125 {multiples = array<i64: 1, 1, 768>} : (tensor<1x128x1xf32>) -> tensor<1x128x768xf32>
  |               %127 = tosa.mul %120, %126 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x128x768xf32>) -> tensor<1x128x768xf32>
  |               %128 = tosa.reshape %1 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
  |               %129 = tosa.mul %127, %128 {shift = 0 : i8} : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
  |               %130 = tosa.reshape %0 {new_shape = array<i64: 1, 1, 768>} : (tensor<768xf32>) -> tensor<1x1x768xf32>
LN└               %131 = tosa.add %129, %130 : (tensor<1x128x768xf32>, tensor<1x1x768xf32>) -> tensor<1x128x768xf32>
    return %131 : tensor<1x128x768xf32>
  }
}

{-#
  dialect_resources: {
    builtin: {
      torch_tensor_768_torch.float32_5: "",
      torch_tensor_768_torch.float32_4: "",
      torch_tensor_768_torch.float32_3: "",
      torch_tensor_768_3072_torch.float32: "",
      torch_tensor_3072_torch.float32: "",
      torch_tensor_3072_768_torch.float32: "",
      torch_tensor_768_torch.float32_2: "",
      torch_tensor_768_torch.float32_1: "",
      torch_tensor_768_torch.float32: "",
      torch_tensor_768_768_torch.float32: "",
      torch_tensor_2304_768_torch.float32: "",
      torch_tensor_2304_torch.float32: ""
    }
  }
#-}
