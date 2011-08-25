import sys
import pystp

#   VC vc = vc_createValidityChecker();
vc = pystp.Stp()

#   vc_setFlags('n');
#   vc_setFlags('d');
#   vc_setFlags('p');
pystp.setFlags("ndp")

#   Expr nresp1 = vc_varExpr(vc, "nresp1", vc_bv32Type(vc));
nresp1 = vc.varExpr("nresp1", vc.createType(pystp.TYPE_BITVECTOR, 32))

#   Expr packet_get_int0 = vc_varExpr(vc, "packet_get_int0", vc_bv32Type(vc));
packet_get_int0 = vc.varExpr("packet_get_int0", vc.createType(pystp.TYPE_BITVECTOR, 32))

#   Expr exprs[] = {
#     // nresp1 == packet_get_int0
#     vc_eqExpr(vc, nresp1, packet_get_int0),
#     // nresp1 > 0
#     vc_bvGtExpr(vc, nresp1, vc_bv32ConstExprFromInt(vc, 0))
#   };
exprs = [ vc.eqExpr(nresp1, packet_get_int0),
          vc.bvGtExpr(nresp1, vc.bvConstExprFromInt(32, 0))]
  
#   Expr res = vc_andExprN(vc, exprs, sizeof(exprs)/sizeof(exprs[0]));
res = vc.andExpr(exprs)

#   vc_printExpr(vc, res);
print res
  
#   int x = vc_query(vc, res);
x = vc.query(res)

#   printf("vc_query result = %d\n", x);
if x == False: retval = 0
elif x == True: retval = 1
else:
    assert x == None
    x = 2
print "vc_query query = %d" % retval

#   vc_printCounterExample(vc);
vc.printCounterExample()
  
#   Expr cex = vc_getCounterExample(vc, res);
cex = vc.getCounterExample(res)
#   //vc_printExpr(vc, cex);
