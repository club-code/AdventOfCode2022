p $<.map(&:split).map{|h,m|((m.ord-h.ord-22)%3)*3+m.ord-87}.sum

# Explanation:
# `char.ord - fixed_value` is a bit like `"ABC".index(char)`
# For the first part, the fixed value is the same for both so it subtracts itself. Only the difference between "A" and "X" (22) matters.
# The rest is just basic Rock Paper Scizors maths to determine which sign wins when they are numbered 0 1 2.
# For the second part, `"X".ord = 88` so `"X".ord - 87` gives 1, `"Y".ord - 87` gives 2 etc.