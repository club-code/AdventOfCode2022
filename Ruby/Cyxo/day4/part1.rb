p $<.map{|p|p.split(",").map{|g|Range.new(*g.split("-").map(&:to_i))}.map(&:to_a).reduce{|a,b|(a&b==b||a&b==a)}}.count(true)