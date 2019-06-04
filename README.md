# Durex

## Fonctionality

### Run
- [X] Run as a daemon  
- [x] Run under root user only  
- [x] Replicate into /usr/sbin as Durex  
- [x] Automatically (re)start at OS startup (cron)  

### Network
- [x] Listen for connections on port 4242  
- [x] Handle up to 3 simultaneous connections  

### Events
- [x] Ask for a password on client connection  
- [x] Spawn a root shell on "shell" command  

### Extra
- [x] Advanced encryption data flow between client/server 


## Usage

### Server

```
./ft_durex
```

### Client

Default launch on host 127.0.0.1 an port 4242

```
./ft_manix [<host> <port>]
```

Commands (in-app)

```
help
	Display usage

shell
	Spawn an encrypted remote shell connection on daemon server

exit
	Terminate the remote shell connection

quit
	Stop the daemon server and terminate all client(s) connection(s)

bye
	Exit the client without stopping the daemon server
```

## Running

On startup the daemon server sets himself as a UNIX daemon.
It creates two files ; one for logging at /var/log/durex/durex.log and another one for lock at /var/lock/durex.lock
