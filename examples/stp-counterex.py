import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('d');
#   //vc_setFlags('p');
pystp.setFlags("nd")
  
#   Type bv8 = vc_bvType(vc, 8);
bv8 = vc.createType(pystp.TYPE_BITVECTOR, 8)

#   Expr a =  vc_bvCreateMemoryArray(vc, "a");
a = vc.bvCreateMemoryArray("a")
 
#   Expr index_1 = vc_bvConstExprFromInt(vc, 32, 1);
index_1 = vc.bvConstExprFromInt(32, 1)

#   Expr a_of_1 = vc_readExpr(vc, a, index_1);
a_of_1 = vc.readExpr(a, index_1)
 
#   Expr ct_100 = vc_bvConstExprFromInt(vc, 8, 100);
ct_100 = vc.bvConstExprFromInt(8, 100)

#   Expr a_of_1_eq_100 = vc_eqExpr(vc, a_of_1, ct_100);
a_of_1_eq_100 = vc.eqExpr(a_of_1, ct_100)

#   /* Query 1 */  
#   vc_push(vc);
vc.push()

#   int query = vc_query(vc, a_of_1_eq_100);
query = vc.query(a_of_1_eq_100)

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if   query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    retval = 2
print "query = %d" % retval

#   vc_assertFormula(vc, a_of_1_eq_100);
vc.assertFormula(a_of_1_eq_100)
  
#   /* query(false) */
#   vc_push(vc);
vc.push()

#   query = vc_query(vc, vc_falseExpr(vc));
query = vc.query(vc.falseExpr())

#   vc_pop(vc);
vc.pop()

#   printf("query = %d\n", query);
if   query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    retval = 2
print "query = %d" % retval

#   if (vc_counterexample_size(vc) == 0) {
#     printf("Counterexample size is 0\n");
#     exit(1);
#   }
if vc.counterExample_size() == 0:
    print "Counterexample size is 0"
    sys.exit(1)
      
#   a_of_1 = vc_simplify(vc, a_of_1);
a_of_1 = vc.simplify(a_of_1)

#   //vc_printExpr(vc, a_of_1);
#   Expr ce = vc_getCounterExample(vc, a_of_1);
ce = vc.getCounterExample(a_of_1)

#   unsigned long long v = getBVUnsigned(ce);
v = ce.getBVUnsigned()
  
#   fprintf(stderr, "a[1] = %ld\n", v);
print >> sys.stderr, "a[1] = %u" % v
