m = 0; reg = Hash.new(0); File.readlines("day08").each { |l| r,o,n,_,v1,o2,v2 = l.split; if reg[v1].send(o2, Integer(v2)); reg[r] += Integer(n) * (o == "dec" ? -1 : 1) ; end; m = [m, *reg.values].max }; p reg.values.max; p m

__END__

5946
6026
