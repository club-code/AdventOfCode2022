p (m=$<.map{|l|l.chomp.chars.map(&:to_i)}).each_with_index.map{                 # parse input into int matrix
    |l,y| l.each_with_index.map{                                                # loop through matrix
        |t,x|
        (y-1).downto(0).inject([true, 0]){|memo,v|[                                                         # count on top
                memo[0] && m[v][x]<m[y][x],                                                                 # memo[0] remembers if we still need to count
                memo[1]+(memo[0]?1:0)                                                                       # memo[1] counts if we need to
        ]}[1] *                                                                                             # get the count and multiply
        (y+1...m.size).inject([true, 0]){|memo,v|[memo[0]&&m[v][x]<m[y][x],memo[1]+(memo[0]?1:0)]}[1] *     # count on bot
        (x-1).downto(0).inject([true, 0]){|memo,v|[memo[0]&&m[y][v]<m[y][x],memo[1]+(memo[0]?1:0)]}[1] *    # count on left
        (x+1...l.size).inject([true, 0]){|memo,v|[memo[0]&&m[y][v]<m[y][x],memo[1]+(memo[0]?1:0)]}[1]       # count on right
    }
}.flatten.max