#include "durex.h"

extern t_daemon		g_durex;

/*
** ***********************************************************************
** NAME
**		daemonize
**
** DESCRIPTION
**		Fork the parent process, request a new SID and close standard
**		inputs / outputs.
**
** RETURN VALUE
**		On success 0 is returned, -1 on error.
**
** ***********************************************************************
*/

void	daemonize(void)
{
	daemon_report(LOG_INFO, "Daemonizing Durex...");

	/*
	** The user must be root to launch Durex
	*/
	if (geteuid() != 0)
	{
		daemon_report(LOG_ERROR, "Unable to start daemon. Not root user.");
		exit(EXIT_FAILURE);
	}

	/*
	** Fork the main process and close the parent since we will
	** request a new session ID afterwards
	*/
	g_durex.pid = fork();
	if (g_durex.pid < 0)
	{
		daemon_report(LOG_ERROR, "Durex process fork failed.");
		exit(EXIT_FAILURE);
	}
	else if (g_durex.pid > 0)
		exit(EXIT_SUCCESS);

	/*
	** Calling setsid() makes this process the session leader for
	** a new process group.
	*/
	daemon_report(LOG_INFO, "Requesting new process group...");
	if (setsid() < 0)
	{
		daemon_report(LOG_ERROR, "Unable to get a new process group.");
		exit(EXIT_FAILURE);
	}
	else
		daemon_report(LOG_INFO, "New process group obtained.");

	/*
	** Reset master file umask in case it has been altered
	*/
	daemon_report(LOG_INFO, "Changing file mask to 0...");
	umask(0);
	daemon_report(LOG_INFO, "File mask changed.");

	/*
	** Change working directory to root to make sure to be into a
	** directory that is not likely to be removed from the FS
	*/
	daemon_report(LOG_INFO, "Changing working directory to root...");
	if (chdir("/") < 0)
	{
		daemon_report(LOG_ERROR, "Unable to move to root directory");
		exit(EXIT_FAILURE);
	}
	else
		daemon_report(LOG_INFO, "Working directory changed.");

	/*
	** Close standard I/O as the daemon is running in background
	*/
	daemon_report(LOG_INFO, "Closing standard I/O...");
	if (close(STDIN_FILENO) == -1)
	{
		daemon_report(LOG_ERROR, "Unable to close stdin.");
		exit(EXIT_FAILURE);
	}
	if (close(STDOUT_FILENO) == -1)
	{
		daemon_report(LOG_ERROR, "Unable to close stdout");
		exit(EXIT_FAILURE);
	}
	if (close(STDERR_FILENO) == -1)
	{
		daemon_report(LOG_ERROR, "Unable to close stderr");
		exit(EXIT_FAILURE);
	}
	daemon_report(LOG_INFO, "Standard I/O closed.");
	daemon_report(LOG_INFO, "Daemon running.");
}
