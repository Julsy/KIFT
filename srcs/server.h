/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 12:20:44 by elee              #+#    #+#             */
/*   Updated: 2017/06/12 17:17:27 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <netdb.h>
# include <errno.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <semaphore.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <arpa/inet.h>

# define PORT 4242

typedef struct			s_socket
{
	int					fd;
	struct sockaddr_in	addr;
	socklen_t			addrlen;
}						t_socket;

typedef struct			s_worker
{
	char				active;
	pthread_t			*tid;
	char				*input_msg;
	char				*output_msg;
	t_socket			socket;
}						t_worker;

typedef struct			s_server
{
	t_socket			sin;
	char				is_connect;
	char				is_running;
	int					worker_cnt;
}						t_server;

typedef struct			s_thread_handler
{
	t_server			*server;
	t_worker			*worker;
}						t_thread_handler;

#endif
