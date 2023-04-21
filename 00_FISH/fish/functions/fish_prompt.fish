function fish_prompt

	set -l last_status $status	
	
	# Configure colors for prompt
	set -l normal (set_color normal)
	set -l white (set_color FFFFFF)

	set -l yellow (set_color f1fa8c)
	set -l orange (set_color ffb86c)
	set -l hotpink (set_color ff79c6)
	set -l purple (set_color bd93f9)

	set -l limegreen (set_color 50fa7b)
	set -l turquoise (set_color 8be9fd)
	set -l blue (set_color 8be9fd)
	
	# Configure fish colors
	set -g fish_color_error ff5555 --bold

	echo

	# User
	echo -n $turquoise(whoami)
	
	# Host
	echo -n $limegreen'@'
	echo -n (prompt_hostname | string split '-')[1]

	# fish version	
	echo -n $hotpink (fish -v | sed -e 's/, version /:/g')

	# PWD
	echo -n $yellow (dirs)
	
	set_color normal

	__terlar_git_prompt
	__fish_hg_prompt
	echo

	if not test $last_status -eq 0
		set_color $fish_color_error
	end

	echo -n '$ '
	set_color normal

end
