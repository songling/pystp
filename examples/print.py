import sys
import pystp

#   VC vc = vc_createValidityChecker();
o = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('d');
#   vc_setFlags('p');
pystp.setFlags("ndp")

#   Expr ct_3 = vc_bvConstExprFromStr(vc, "00000000000000000000000000000011");
ct_3 = o.bvConstExprFromStr("00000000000000000000000000000011");

#   vc_printExpr(vc, ct_3);  printf("\n");
print ct_3

#   ct_3 = vc_bvConstExprFromInt(vc, 32, 5);
ct_3 = o.bvConstExprFromInt(32, 5);

#   vc_printExpr(vc, ct_3);  printf("\n");
print ct_3
