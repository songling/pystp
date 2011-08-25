import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   //  vc_setFlags ('n');
#   vc_setFlags ('d');
#   vc_setFlags ('p');
pystp.setFlags("dp")

#   // 32-bit variable
#   Expr i = vc_varExpr1(vc, "i", 0, 32);
i = vc.varExpr1("i", 0, 32)

#   // 32-bit constant, value is 7.
#   Expr c7 = vc_bvConstExprFromInt(vc, 32, 7);
c7 = vc.bvConstExprFromInt(32, 7)

#   // assert that both (i < 7) AND (i > 7) are true.
#   Expr ilt7 = vc_bvLtExpr (vc, i, c7);
ilt7 = vc.bvLtExpr(i, c7)

#   Expr igt7 = vc_bvGtExpr (vc, i, c7);
igt7 = vc.bvGtExpr(i, c7)

#   vc_assertFormula (vc, ilt7);
vc.assertFormula(ilt7)

#   vc_assertFormula (vc, igt7);
vc.assertFormula(igt7)

#   // check if constraint set is satisifable.
#   Expr falsee = vc_falseExpr(vc);
falsee = vc.falseExpr()

#   r = vc_query (vc, falsee);
r = vc.query(falsee)
if r == False: retval = 0
elif r == True: retval = 1
else:
    assert r == None
    r = 2

#   if (r == 0)
#     printf ("cs is satisfiable\n");
#   else
#     printf ("cs is not satisfiable\n");
if retval == 0: print "cs is satisfiable"
else: print "cs is not satisfiable"

#   vc_DeleteExpr(i);
vc.deleteExpr(i)

#   vc_DeleteExpr(c7);
vc.deleteExpr(c7)

#   vc_DeleteExpr(ilt7);
vc.deleteExpr(ilt7)

#   vc_DeleteExpr(igt7);
vc.deleteExpr(igt7)

#   vc_DeleteExpr(falsee);
vc.deleteExpr(falsee)

#   vc_Destroy(vc);
vc.destroy()
