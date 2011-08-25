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

#   Expr sz = vc_varExpr(vc, "sz", vc_bv32Type(vc));
sz = vc.varExpr("sz", vc.createType(pystp.TYPE_BITVECTOR, 32))

#   Expr exprs[] = {
#     // nresp1 == packet_get_int0
#     vc_eqExpr(vc, nresp1, packet_get_int0),
    
#     // nresp1 > 0
#     vc_bvGtExpr(vc, nresp1, vc_bv32ConstExprFromInt(vc, 0)),
    
#     // sz == nresp1 * 4
#     vc_eqExpr(vc, sz, vc_bv32MultExpr(vc, nresp1, vc_bv32ConstExprFromInt(vc, 4))),
    
#     // sz > nresp1 || sz < 0
#     vc_orExpr(vc, vc_sbvGeExpr(vc, sz, nresp1), vc_sbvLtExpr(vc, sz, vc_bv32ConstExprFromInt(vc, 0))),
#   };
exprs = [vc.eqExpr(nresp1, packet_get_int0), vc.bvGtExpr(nresp1, vc.bv32ConstExprFromInt(0)),
         vc.eqExpr(sz, vc.bv32MultExpr(nresp1, vc.bv32ConstExprFromInt(4))),
         vc.orExpr([vc.sbvGeExpr(sz, nresp1), vc.sbvLtExpr(sz, vc.bv32ConstExprFromInt(0))])]

#   Expr res = vc_andExprN(vc, exprs, sizeof(exprs)/sizeof(exprs[0]));
res = vc.andExpr(exprs)

#   //vc_printExpr(vc, res);
#   vc_query(vc,res);
vc.query(res)

#   return 0;
sys.exit(0)
