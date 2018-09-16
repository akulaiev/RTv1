
#include "rtv1.h"
#include <stdio.h>

static char		**ft_realloc_2d(char **lines, int num_lines)
{
	char	**new_mem;
	int		i;

	if (!lines || !num_lines)
		return ((char**)ft_memalloc(sizeof(char*)));
	new_mem = (char**)ft_memalloc(sizeof(char*) * num_lines + 1);
	i = -1;
	while (++i < num_lines)
		new_mem[i] = lines[i];
	free(lines);
	return (new_mem);
}

static char		**get_all_data(int fd)
{
	char	*tmp_line;
	int		num_lines;
	char	**full_file;

	tmp_line = NULL;
	num_lines = 0;
	while (get_next_line(fd, &tmp_line))
	{
		full_file = ft_realloc_2d(full_file, num_lines);
		full_file[num_lines] = tmp_line;
		num_lines++;
	}
	return (full_file);
}

void		parser(int fd)
{
	char	**full_file;

	full_file = NULL;
	full_file = get_all_data(fd);
	int i = -1;
	while (++i < 80)
		printf("%s\n", full_file[i]);
	ft_double_free((void**)full_file, 80);
}