import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()


#   vc_setFlags('n');
#   vc_setFlags('d');
#   vc_setFlags('p');
#   vc_setFlags('v');
#   vc_setFlags('s');
#   vc_setFlags('c');
#   vc_push(vc);
vc.setFlags("ndpvsc")

#   Type bv8 = vc_bvType(vc, 8);
bv8 = vc.createType(pystp.TYPE_BITVECTOR, 8)

#   Expr a = vc_varExpr(vc, "a", bv8);
a = vc.varExpr("a", bv8)

#   Expr ct_0 = vc_bvConstExprFromInt(vc, 8, 0);
ct_0 = vc.bvConstExprFromInt(8, 0)

#   Expr a_eq_0 = vc_eqExpr(vc, a, ct_0);
a_eq_0 = vc.eqExpr(a, ct_0)

#   int query;
#   //query = vc_query(vc, a_eq_0);
#   //printf("query = %d\n", query);
#   Expr a_neq_0 = vc_notExpr(vc,a_eq_0);
a_neq_0 = vc.notExpr(a_eq_0)

#   vc_assertFormula(vc,a_eq_0);
vc.assertFormula(a_eq_0)

#   vc_printAsserts(vc);
vc.printAsserts()

#   vc_push(vc);
vc.push()

#   Expr queryexp = vc_eqExpr(vc, a, vc_bvConstExprFromInt(vc, 8, 0));
queryexp = vc.eqExpr(a, vc.bvConstExprFromInt(8, 0))

#   vc_printExpr(vc, queryexp);
print queryexp
  
#   query = vc_query(vc, queryexp);
query = vc.query(queryexp)

#   vc_printCounterExample(vc);
vc.printCounterExample()

#   vc_pop(vc);
vc.pop()

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    query = 2
print "query = %d" % retval
