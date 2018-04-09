/*This package is sent by the client. The package contains the public key, P, according to the Diffie-Hellman (D-H) key exchange protocol (section 5.4). When the server receives this package, it saves the public key, and generates a 512 bit private key, and computes and sends the public key, B, by ComputeAndSendPublicKeyA(..).

PKG_PUBLIC_KEYA

Encapsulated in structure 2 (Table 1)

 	
This package is sent by the server, and contains the public key, A, according to the Diffie-Hellman (D-H) key exchange protocol (section 5.4). This package is received by the client, which generates a private key, and computes the session key (ComputeAndSetSessionKey(..)), and computes and sends the public key, B (of type PKG_PUBLIC_KEYB), with the function ComputeAndSendPublicKeyB(..).

PKG_PUBLIC_KEYB

Encapsulated in structure 2 (Table 1)

 	
This package is sent by the client to the server (see PKG_PUBLIC_KEYA). The session key is computed, and a signature is computed and sent to the client (ComputeAndSendSignature(…)) which signs the public keys, A and B, if we have defined #define USE_SIGNATURE to protect the client against “Man in the Middle” attacks (section 3.4 and 4).

PKG_SIGNATURE

Encapsulated in structure 2 (Table 1)

 	
This package is sent by the server, and contains a signature that confirms the packages PKG_PUBLIC_KEYA and PKG_PUBLIC_KEYB. The client receives the package, and validates the server using the trusted static key SecureChatIOCP::m_PubN that is hard-coded into the client. If everything is fine, a PKG_USERNAME_PASSWORD is sent to server, otherwise a PKG_ERRORMSG, that also terminates the connection.

PKG_TEXT_TO_ALL

Encapsulated in structure 1 (Table 1)

 	
This package is always sent after the key exchange procedure, and is encapsulated inside a PKG_ENCRYPTED package.

When received by the client, the content is shown in the text box of the chatting client. However, if it is received by the server, it is sent to everybody.

PKG_USERNAME_PASSWORD

Encapsulated in structure 3 (Table 1)

 	
This package is always sent as a response from the client that the client accepted the signature. This package is encapsulated inside a PKG_ENCRYPTED package.

PKG_ENCRYPTED

 	
This package is sent after the key exchange procedure, and is handled inside NotifyReceivedPackage(..). The contents of the package are decrypted and processed according to the defined packages in this table.

*/

#include "manix.h"
char	*ft_itoa(unsigned long long int n)
{
	char	*resstring;

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
  srand(time(NULL));
  c->p = 0;
  c->g = 5;
  c->b = 0;
  c->x = 0;
  c->y = 0;
  c->shared_key = 0;
  c->is_key = FALSE;
}

int key_exchange(t_client *c, unsigned char *buf)
{
  char *p_char = NULL;
  char *y_char = NULL;
  char *str = NULL;
  

  /*
   *
   *
   */
  if (!c->p)
    {
      while (!is_prime(rand_uint64()))
	c->p = rand_uint64();

      p_char = ft_itoa(c->p);
      // check !!!!!!!!!!! c-p could be zero return error
      
      // if p_char != NULL
      printf("sending -%s- = %lu  %llu\n", p_char, strlen(p_char), c->p);
      write(c->sockfd, p_char, strlen((const char *)p_char) );
      	    printf("\n>>%s<<\n", p_char);
	    printf("\n>>%llu<<\n", strtoll((const char * restrict)buf, &str, 10));

      //check write return if fail
    }
  else if (!c->x)
    {
            printf("2nd step : geting Pkey A from serv, create private key c->b and send compute pkey B to the serv ..\n");
	    //c->x  =(unsigned long long int)( buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
	    str = (char *)buf;
	    c->x = (unsigned long long int)&str; 
	    c->b = rand_uint64();
	    
	    c->y = powmodp(c->g, c->b, c->p);
	    if (c->y == 0 )
	      printf("ERROR y = 0\n" );
	    y_char = ft_itoa(c->y);
	    write (c->sockfd, y_char, strlen(y_char));
	    // free y_char && check write
      
    }
  else if (!c->shared_key)
    {
      printf("last step rcve compute sign and check it \n");
      
      if (!strcmp((const char *)buf, "1234"))
	printf("signature equal\n");
      else
	printf("signature diff\n");
      c->shared_key = powmodp(c->x, c->b, c->p);
      printf("%llu__OK\n",c->shared_key);
      
    }
  

    if (!c->shared_key)
      return (-1);
    else
      {
	c->is_key = TRUE;
	return (1);
      }
  
}
