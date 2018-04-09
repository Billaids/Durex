#include "durex.h"

char    *ft_itoa(unsigned long long int n)
{
 	char    *resstring;

	resstring = malloc(sizeof(char) * 26);
	bzero(resstring, 26);
	if (n > 1 && resstring)
	{
         	*--resstring = '0' + (n % 10);
		n /= 10;
		while (n != 0)
		{
                 	*--resstring = '0' + (n % 10);
			n /= 10;
		}
	}
        else if (resstring)
	{
         	*--resstring = '0' - (n % 10);
		n /= 10;
		while (n != 0)
		{
                 	*--resstring = '0' - (n % 10);
			n /= 10;
		}
                *--resstring = '-';
	}
        return (resstring);
}

void init_key(t_client *c)
{
  daemon_report(LOG_INFO, "Initalisation of keys...");
  srand(time(NULL));
  c->p = 0;
  c->shared_key = 0;
  c->g = 5;
  c->a = 0;
  c->x = 0;
  c->y = 0;
  c->is_key = FALSE;

}

int handle_keys(unsigned char *buf, t_client *c)
{

  char *x_str = NULL;
  char *s_str = NULL;
  char *p_str = NULL;
    char *ptr;
  char *str = NULL;
  uint64_t tmp = 0;
  /*
   * get Public key p from the client
   * set his private key a 
   * send the generated key x : g^x MOD p
   */
  if (!c->p)
    {
        daemon_report(LOG_INFO, "Recv public key P ...");
	// c->p  = (unsigned long long int)(buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)  );
      // check c->p return error if is nor prime
	str = (char *)buf;
	//c->p = (unsigned long long int)&str;
	tmp = strtoll((const char * restrict )str, &ptr, 10);
	c->p = tmp;
      daemon_report(LOG_INFO, "Getting public key P ...");
      p_str = ft_itoa(c->p);
      daemon_report(LOG_INFO, p_str);


      
      c->a = 77100074583237325;

      c->x = powmodp(c->g, c->a, c->p);
      
      x_str = ft_itoa(c->x);
      daemon_report(LOG_INFO, "Sending generated public key X ...");
      write (c->sock, x_str, strlen(x_str));
      //      if (x_str)
      //free(x_str);
      daemon_report(LOG_INFO, "Public key send.");
      //if write fail return error
    }
  
  /*
   * get the public key Y from the client 
   * generate a signature of public keys X and Y
   * the create the shared key 
   */
  else if (!c->y)
    {
      daemon_report(LOG_INFO, "Phase 2 : get Pkey Y from the client,generate signature of  Y + X to the client .");
      //      c->y  = (unsigned long long int)(buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
      str = (char *)buf;
      c->y = (unsigned long long int)&str;
  //need to genreate a singatue from Xand Y // here sign = 1234
      write (c->sock, "1234", 4);
      daemon_report(LOG_INFO, "Signature send.");


      /*
       * calcul of the sharedkey
       */
      
      c->shared_key = powmodp(c->y, c->a, c->p);
      daemon_report(LOG_INFO, "Shared key created :");
      s_str = ft_itoa(c->shared_key);
      
      daemon_report(LOG_INFO, s_str);
      
    }

  /*
   * if everything is ok ( P a X Y ) 
   * is_key is set to TRUE
   * else : stay FALSE
   */

       daemon_report(LOG_INFO, "test1");
  if (c->shared_key)
    {
      c->is_key = TRUE;
      return 1;
    }
  else
    return -1;
}
