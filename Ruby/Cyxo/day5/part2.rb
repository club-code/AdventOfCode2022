p ($<.to_a*'').split(/(?: \d  ?)+\n\n/).map{|g|g.split("\n")}.reduce{|a,b|[(1...a[0].size).step(4).map{|i|a.map{|l|l[i]}.join.strip.reverse},b]}.reduce{|a,b|[b.map{|l|/move (\d+) from (\d+) to (\d+)/.match(l).captures.map(&:to_i)}.each{|n,f,t|a[t-1],a[f-1]=a[t-1]+a[f-1][-n..-1],a[f-1][0...-n]},a]}.reduce{|b,a|a.map{|l|l[-1]}.join}