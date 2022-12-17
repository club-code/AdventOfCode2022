p ($<.to_a*'') # read all stdin into a string
.split(/(?: \d  ?)+\n\n/) # split input between piles (a) and orders (b)
.map{|g|g.split("\n")}
.reduce{
	|a,b|[(1...a[0].size).step(4).map{
		# i is the index of each column
		|i|a.map{|l|l[i]} # get the ith element of the line and add it to the column
		.join.strip.reverse # now we have strings that represent the pile (i.e. "CZNBMWQV" for n°1)
	}, b] # return parsed a and b
}.reduce{
	|a,b|[b.map{
		|l|/move (\d+) from (\d+) to (\d+)/.match(l).captures.map(&:to_i) # extract numbers
	}.each{
		# loop through tuples "number","from","to"
		|n,f,t| a[t-1],a[f-1]=a[t-1]+a[f-1][-n..-1],a[f-1][0...-n] # remove last n chars from "from", add them to "to"
	}, a] # return parsed b and modified a
}.reduce{
	|b,a|a.map{|l|l[-1]}.join # get last char of each pile and concatenate
}