p (m=$<.map{|l|l.chomp.chars.map(&:to_i)}).each_with_index.map{|l,y|l.each_with_index.map{|t,x|(y-1).downto(0).inject([true,0]){|n,v|[n[0]&&m[v][x]<m[y][x],n[1]+(n[0]?1:0)]}[1]*(y+1...m.size).inject([true,0]){|n,v|[n[0]&&m[v][x]<m[y][x],n[1]+(n[0]?1:0)]}[1]*(x-1).downto(0).inject([true,0]){|n,v|[n[0]&&m[y][v]<m[y][x],n[1]+(n[0]?1:0)]}[1]*(x+1...l.size).inject([true,0]){|n,v|[n[0]&&m[y][v]<m[y][x],n[1]+(n[0]?1:0)]}[1]}}.flatten.max