
#ifndef SIGNALS_H
# define SIGNALS_H

enum
{
	SIGNALS_PARENT,
	SIGNALS_HEREDOC,
	SIGNALS_DEFAULT
};
int		set_signals(t_ms *ms, int type);

#endif
