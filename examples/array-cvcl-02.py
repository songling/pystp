import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('d');
#   vc_setFlags('p');
vc.setFlags("ndp")

#   Expr cvcl_array = vc_varExpr1(vc, "a",32,32);
cvcl_array = vc.varExpr1("a", 32, 32)

#   Expr i = vc_varExpr1(vc, "i", 0, 8);
i = vc.varExpr1("i", 0, 8)

#   Expr i32 = vc_bvConcatExpr(vc,
#  			     vc_bvConstExprFromStr(vc,
#  						   "000000000000000000000000"),
#  			     i);
i32 = vc.bvConcatExpr(vc.bvConstExprFromStr("000000000000000000000000"), i)

#   Expr no_underflow = vc_bvLeExpr(vc,
# 				  vc_bvConstExprFromInt(vc, 32, 0),
# 				  i32);
no_underflow = vc.bvLeExpr(vc.bvConstExprFromInt(32, 0), i32)

#   Expr no_overflow = vc_bvLeExpr(vc,
# 				 i32,
# 				 vc_bvConstExprFromInt(vc, 32, 9));
no_overflow = vc.bvLeExpr(i32, vc.bvConstExprFromInt(32, 9))

#   Expr in_bounds = vc_andExpr(vc, no_underflow, no_overflow);
in_bounds = vc.andExpr([no_underflow, no_overflow])

#   Expr a_of_i = vc_bvSignExtend(vc,
# 				vc_readExpr(vc,cvcl_array,i32),
# 				32);
a_of_i = vc.bvSignExtend(vc.readExpr(cvcl_array, i32), 32)

#   Expr a_of_i_eq_11 = vc_eqExpr(vc, a_of_i,
# 				vc_bvConstExprFromInt(vc, 32, 11));
a_of_i_eq_11 = vc.eqExpr(a_of_i, vc.bvConstExprFromInt(32, 11))
 
#   vc_assertFormula(vc, in_bounds);
vc.assertFormula(in_bounds)

#   vc_assertFormula(vc, a_of_i_eq_11);
vc.assertFormula(a_of_i_eq_11)

#   vc_query(vc, vc_falseExpr(vc));
vc.query(vc.falseExpr())

#   long long v; 
#   Expr pre = vc_bvConstExprFromInt(vc,24,0);
pre = vc.bvConstExprFromInt(24, 0)

#   for(int j=0;j<10;j++) {
for j in range(10):
    #     Expr exprj = vc_bvConstExprFromInt(vc,8,j);
    exprj = vc.bvConstExprFromInt(8, j)
    #     Expr index = vc_bvConcatExpr(vc, pre, exprj);
    index = vc.bvConcatExpr(pre, exprj)
    #     index = vc_simplify(vc,index);
    index = vc.simplify(index)
    #     Expr a_of_j = vc_readExpr(vc, cvcl_array, index);
    a_of_j = vc.readExpr(cvcl_array, index)
    #     Expr ce = vc_getCounterExample(vc,a_of_j);
    ce = vc.getCounterExample(a_of_j)
#   }

#   //vc_printCounterExample(vc);
