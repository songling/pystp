import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('d');
#   vc_setFlags('p');
vc.setFlags("ndp")

#   Type bv8 = vc_bvType(vc, 8);
bv8 = vc.createType(pystp.TYPE_BITVECTOR, 8);

#   Expr a = vc_varExpr(vc, "a", bv8);
a = vc.varExpr("a", bv8)

#   Expr ct_0 = vc_bvConstExprFromInt(vc, 8, 0);
ct_0 = vc.bvConstExprFromInt(8, 0)

#   Expr a_eq_0 = vc_eqExpr(vc, a, ct_0);
a_eq_0 = vc.eqExpr(a, ct_0)

#   int query = vc_query(vc, a_eq_0);
query = vc.query(a_eq_0);

#   printf("query = %d\n", query);
if   query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    retval = 2
print "query = %d" % retval

#   vc_push(vc);
vc.push()

#   query = vc_query(vc, a_eq_0);
query = vc.query(a_eq_0)

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if   query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    retval = 2
print "query = %d" % retval
