#include "../../include/minishell.h"
#include <fcntl.h>

void	std_save(t_ms *ms)
{
	ms->std[0] = dup(STDIN_FILENO);
	ms->std[1] = dup(STDOUT_FILENO);
}

void	std_reset(t_ms *ms)
{
	dup2(ms->std[0], STDIN_FILENO);
	dup2(ms->std[1], STDOUT_FILENO);
	close(ms->std[0]);
	close(ms->std[1]);
	ms->std[0] = -1;
	ms->std[1] = -1;
}
