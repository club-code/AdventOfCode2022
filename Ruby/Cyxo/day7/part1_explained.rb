p $<.inject({:path => [], :sizes => {}}){				   # prepare a dict with cur_path and {path=>size}
	|memo, elem| {                                  	   # then loop over the input lines

		:path => elem =~ /cd .*/ ? (    		           # if line matches /cd .*/
			(d = elem.scan(/cd (.*)/)[0][0]) == ".." ?	   # get folder name
			memo[:path][0...-1] :						   # if it's "..", remove last from cur_path
			memo[:path]+[d.sub("/","")]         	       # else add name (and rename "/" to "")
		) : memo[:path],                    	           # if it doesn't match "cd", don't change cur_path

		:sizes => elem =~ /\d+ .*/ ?					   # if it matches /\d+ .*/ (size + file_name)
		memo[:sizes].merge({							   # add new size to {cur_path=>size}
			[memo[:path],(e=elem.scan(/(\d+) (.*)/)[0])[1]].join("/") => e[0].to_i
		}) : memo[:sizes]           		               # otherwise, don't change {path=>size}
	}
}[:sizes].inject({"/" => 0}){
	|memo, (path,size)|
	path.split("/")[0...-1].inject([]){					   # generate all parent folder paths of a folder
		|a,f|a+=[(a.last||"")+f+"/"]
	}.inject(memo){
		|m,fp|m.merge({fp => (m[fp]||0) + size})		   # add size of file to a folder and its parents
	}
}.map{|(k,v)|v > 1e5 ? 0 : v}.sum						   # filter < 100000 and sum