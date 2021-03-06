import sys
import pystp

#   for(int j=0;j < 3; j++) {
for j in range(3):
    #     VC vc = vc_createValidityChecker();
    vc = pystp.Stp()
    #     vc_setFlags('n');
    #     vc_setFlags('d');
    #     vc_setFlags('p');
    #     vc_setFlags('x');
    vc.setFlags("ndpx")
    
    #     Type bv8 = vc_bvType(vc, 8);
    bv8 = vc.createType(pystp.TYPE_BITVECTOR, 8)
    
    #     Expr a =  vc_bvCreateMemoryArray(vc, "a");
    a = vc.bvCreateMemoryArray("a")
    
    #     Expr index_3 = vc_bvConstExprFromInt(vc, 32, 3);
    index_3 = vc.bvConstExprFromInt(32, 3)
    
    #     Expr a_of_0 = vc_readExpr(vc, a, index_3);
    a_of_0 = vc.readExpr(a, index_3)
    
    #   int i;
    #   for (i = 2; i >= 0; i--)
    #     a_of_0 = vc_bvConcatExpr(vc,
    # 			     a_of_0,
    # 			     vc_readExpr(vc, a,
    # 					 vc_bvConstExprFromInt(vc, 32, i)));
    for i in range(3)[::-1]:
        a_of_0 = vc.bvConcatExpr(a_of_0,
                                 vc.readExpr(a, vc.bvConstExprFromInt(32, i)))
    
    #   Expr cast_32_to_8 = vc_bvExtract(vc, a_of_0, 7, 0);
    cast_32_to_8 = vc.bvExtract(a_of_0, 7, 0)
    
    #   Expr cast_8_to_32 = vc_bvSignExtend(vc, cast_32_to_8, 32);
    cast_8_to_32 = vc.bvSignExtend(cast_32_to_8, 32)
    
    #   vc_printExpr(vc, cast_8_to_32);
    print cast_8_to_32
    
    #   cast_8_to_32 = vc_simplify(vc, cast_8_to_32);
    cast_8_to_32 = vc.simplify(cast_8_to_32)
    
    #   vc_Destroy(vc);
    vc.destroy()
    
#   }

