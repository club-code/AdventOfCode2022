p (m=$<.map{|l|l.chomp.chars.map(&:to_i)}).each_with_index.map{					# parse input into int matrix
	|l,y| l.each_with_index.map{												# loop through matrix
		|t,x| y==0 || y==m.size-1 || x==0 || x==l.size-1 ||						# if tree is on an edge
		(0...y).map{|v|m[v][x] < m[y][x]}.all? ||								# all trees shorter on top
		(y+1...m.size).map{|v|m[v][x] < m[y][x]}.all? ||						# all trees shorter on bot
		(0...x).map{|v|l[v] < l[x]}.all? ||										# all trees shorter on left
		(x+1...l.size).map{|v|l[v] < l[x]}.all?									# all trees shorter on right
	}
}.flatten.count(true)