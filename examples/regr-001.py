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
 
#   Expr index_3 = vc_bvConstExprFromInt(vc, 32, 3);
index_3 = vc.bvConstExprFromInt(32, 3)

#   Expr a_of_0 = vc_readExpr(vc, a, index_3);
a_of_0 = vc.readExpr(a, index_3)

#   int i;
#   for (i = 2; i >= 0; i--)
for i in range(3)[::-1]:
    #     a_of_0 = vc_bvConcatExpr(vc,
    # 			     a_of_0,
    # 			     vc_readExpr(vc, a, 
    # 					 vc_bvConstExprFromInt(vc, 32, i)));
    a_of_0 = vc.bvConcatExpr(a_of_0, vc.readExpr(a, vc.bvConstExprFromInt(32, i)))
  
 
#   Expr ct_100 = vc_bvConstExprFromInt(vc, 32, 100);
ct_100 = vc.bvConstExprFromInt(32, 100)
#   Expr a_of_1_sgt_100 = vc_sbvGtExpr(vc, a_of_0, ct_100);
a_of_1_sgt_100 = vc.sbvGtExpr(a_of_0, ct_100)

#   /* Query 1 */  
#   vc_push(vc);
vc.push()
#   int query = vc_query(vc, a_of_1_sgt_100);
query = vc.query(a_of_1_sgt_100)
#   vc_pop(vc);
vc.pop()
#   printf("query = %d\n", query);
if query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    query = 2
print "query = %d" % retval

#   vc_assertFormula(vc, a_of_1_sgt_100);
vc.assertFormula(a_of_1_sgt_100)
#   vc_printExpr(vc, a_of_1_sgt_100);
print a_of_1_sgt_100
  
#   /* query(false) */
#   vc_push(vc);
vc.push()
#   query = vc_query(vc, vc_falseExpr(vc));
query = vc.query(vc.falseExpr())
#   vc_pop(vc);
vc.pop()
#   printf("query = %d\n", query);
if query == False: retval = 0
elif query == True: retval = 1
else:
    assert query == None
    query = 2
print "query = %d" % retval

#   assert(!query);
assert not query
#   assert(vc_counterexample_size(vc));
assert vc.counterExample_size() > 0
  
#   int* a_val = (int*) malloc(sizeof *a_val);
#   char *p = (char*) a_val;
#   //a_of_1 = vc_simplify(vc, a_of_1);  // BUG here
a_val = [None, None, None, None]

#   for (i=0; i<=3; i++) {
for i in range(4):
    #     Expr elem = vc_readExpr(vc, a, vc_bvConstExprFromInt(vc, 32, i));
    elem = vc.readExpr(a, vc.bvConstExprFromInt(32, i))
    #     Expr ce = vc_getCounterExample(vc, elem);
    ce = vc.getCounterExample(elem)
    #     unsigned long long v = getBVUnsigned(ce);
    v = ce.getBVUnsigned()
    #     fprintf(stderr, "a[%d] = %ld\n", i, v);
    print >> sys.stderr, "a[%d] = %u" % (i, v)
    #     *p = v; p++;
    a_val[i] = v
#   }

# repack value
tmp = 0
for i in range(4):
    tmp += a_val[i] * (2**(8*i))

#   printf("a = %d\n", *a_val);
print "a = %d" % tmp
#   assert(*a_val > 100);
assert tmp > 100
