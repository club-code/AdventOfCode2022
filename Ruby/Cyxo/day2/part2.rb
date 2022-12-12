p $<.map(&:split).map{|h,m|(m.ord-88)*3+1+(h.ord+m.ord-154)%3}.sum

# Explanation:
# It uses ord just like part 1. Fixed values make A=0,B=1,C=2 and X=0,Y=1,Z=2 for easier maths
# Here, "XYZ" already gives the score which you have to multiply by 3.
# X means you played 1 sign inferior (i.e. Rock = 0 < Paper = 1), Y means equal, Z means 1 sign superior. Mod 3 to loop over the signs.
# So "ABC" gives what they played, "ABC"+"XYZ"-1 gives what you played (-1 is used so that X is -1, Y is 0 and Z is 1)
# -154 is just -"A".ord-"X".ord-1 (the -1 is the one mentioned above)