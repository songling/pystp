import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('c');
#   vc_setFlags('d');
#   vc_setFlags('p');
pystp.setFlags("ncdp")

#   Type bv8 = vc_bvType(vc, 8);
bv8 = vc.createType(pystp.TYPE_BITVECTOR, 8);

#   Expr a = vc_varExpr(vc, "a", bv8);
a = vc.varExpr("a", bv8);

#   Expr ct_0 = vc_bvConstExprFromInt(vc, 8, 0);
ct_0 = vc.bvConstExprFromInt(8, 0)

#   Expr a_eq_0 = vc_eqExpr(vc, a, ct_0);
a_eq_0 = vc.eqExpr(a, ct_0)

#   /* Query 1 */
#   vc_push(vc);
vc.push()

#   int query = vc_query(vc, a_eq_0);
query = vc.query(a_eq_0)

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    query = 2
print "query = %d" % retval

#   /* Query 2 */
#   Expr a_neq_0 = vc_notExpr(vc, a_eq_0);
a_neq_0 = vc.notExpr(a_eq_0)

#   vc_push(vc);
vc.push()

#   query = vc_query(vc, a_neq_0);
vc.query(a_neq_0)

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    query = 2
print "query = %d" % retval

