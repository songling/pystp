import sys
import pystp

# preliminary
print >> sys.stderr, " * creating Stp object"
o = pystp.Stp()
print "-"*25, "\n"

# types
print >> sys.stderr, " * creating StpType Bool object (t1)"
t1 = o.createType(pystp.TYPE_BOOL)
print >> sys.stderr, "  - printing it: '%s'" % t1
assert t1.isBool() and not t1.isBitVector() and not t1.isArray()

print >> sys.stderr, " * creating StpType BitVector object (t2)"
t2 = o.createType(pystp.TYPE_BITVECTOR)
print >> sys.stderr, "  - printing it: '%s'" % t2
assert not t2.isBool() and t2.isBitVector() and not t2.isArray()

print >> sys.stderr, " * creating StpType BitVector(24) object (t3)"
t3 = o.createType(pystp.TYPE_BITVECTOR, 24)
print >> sys.stderr, "  - printing it: '%s'" % t3
assert not t3.isBool() and t3.isBitVector() and not t3.isArray()
print "-"*25, "\n"

# expressions
print >> sys.stderr, " * creating StpExpr variable 'pippo', with type 't1' (v1)"
v1 = o.varExpr("pippo", t1)
print >> sys.stderr, "  - printing it: '%s'" % v1
tmp = v1.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

print >> sys.stderr, " * creating StpExpr variable 'pluto', with type 't1' (v2)"
v2 = o.varExpr("pluto", t1)
print >> sys.stderr, "  - printing it: '%s'" % v2
tmp = v2.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

print >> sys.stderr, " * creating StpExpr equality 'v1 == v2' (v3)"
v3 = o.eqExpr(v1, v2)
print >> sys.stderr, "  - printing it: '%s'" % v3

print >> sys.stderr, " * creating StpExpr \"true\" boolean expression (v4)"
v4 = o.trueExpr()
print >> sys.stderr, "  - printing it: '%s'" % v4
tmp = v4.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

print >> sys.stderr, " * creating StpExpr \"false\" boolean expression (v5)"
v5 = o.falseExpr()
print >> sys.stderr, "  - printing it: '%s'" % v5
tmp = v5.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

print >> sys.stderr, " * creating StpExpr boolean expression \"!v5\" (v6)"
v6 = o.notExpr(v5)
print >> sys.stderr, "  - printing it: '%s'" % v6
tmp = v6.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

# testing 'and' expressions
print >> sys.stderr, " * creating StpExpr boolean expression \"v1 && v2 && v5 && v6\" (v7)"
v7 = o.andExpr([v1, v2, v5, v6])
print >> sys.stderr, "  - printing it: '%s'" % v7
tmp = v7.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

# testing 'or' expressions
print >> sys.stderr, " * creating StpExpr boolean expression \"v1 | v2 | v5 | v6\" (v8)"
v8 = o.orExpr([v1, v2, v5, v6])
print >> sys.stderr, "  - printing it: '%s'" % v8
tmp = v8.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()

# testing 'implies' expressions
print >> sys.stderr, " * creating StpExpr boolean expression \"v5 => v6\" (v9)"
v9 = o.impliesExpr(v5, v6)
print >> sys.stderr, "  - printing it: '%s'" % v9
tmp = v9.getType()
assert tmp.isBool() and not tmp.isBitVector() and not tmp.isArray()
