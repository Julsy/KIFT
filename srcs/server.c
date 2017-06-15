/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 12:16:25 by elee              #+#    #+#             */
/*   Updated: 2017/06/12 17:26:02 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "kift.h"

t_socket    setup_server_socket(int port)
{
	t_socket    sin;
	int         optval;

	memset(&sin.addr, 0, sizeof(sin.addr));
	sin.addrlen = sizeof(struct sockaddr_storage);
	sin.addr.sin_family = AF_INET;
	sin.addr.sin_port = htons(port);
	sin.addr.sin_addr.s_addr = INADDR_ANY;
	if ((sin.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		dprintf(2, "Creating the server socket failed with code: %d\n", errno);
		exit(1);
	}
	optval = 1;
	setsockopt(sin.fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (bind(sin.fd, (struct sockaddr *)&sin.addr, sizeof(sin.addr)) < 0)
	{
		dprintf(2, "Binding the server socket failed with code: %d\n", errno);
		exit(1);
	}
	if (listen(sin.fd, 3) < 0)
	{
		dprintf(2, "Listening on server socket failed with the code: %d\n", errno);
		exit(1);
	}
	return (sin);
}

void		*handle_data(void *params)
{
	t_server	*server;
	t_worker	*worker;
	int			recv_bytes;
	char		*msg;

	msg = (char*)malloc(sizeof(char) * 1024);
	server = ((t_thread_handler*)params)->server;
	worker = ((t_thread_handler*)params)->worker;
	while ((recv_bytes = recv(worker->socket.fd, msg, 1024, 0)) > 0)
	{
		parse_init(msg);
		write(1, msg, strlen(msg));
		write(1, "\n", 1);
		memset(msg, 0, 1024);
	}
	return (NULL);
}

void		launch_thread(t_server *server, t_worker *worker)
{
	t_thread_handler *params;

	params = (t_thread_handler*)calloc(1, sizeof(t_thread_handler));
	params->server = server;
	params->worker = worker;
	worker->tid = calloc(1, sizeof(pthread_t));
	pthread_create(worker->tid, NULL, handle_data, params);
}

void		connect_worker(void *param)
{
	t_server	*server;
	int			fd;
	t_worker	*worker;

	server = (t_server*)param;
	while (server->is_connect)
	{
		fd = accept(server->sin.fd, (struct sockaddr *)&(server->sin.addr.sin_addr)
				, &(server->sin.addrlen));
		if (fd == -1)
		{
			dprintf(2, "Worker couldn't be accepted with the code: %d\n", errno);
			exit(1);
		}
		printf("%d worker is connected\n", server->worker_cnt + 1);
		server->worker_cnt++;
		worker = (t_worker*)calloc(1, sizeof(t_worker));
		worker->socket.fd = fd;
		worker->tid = NULL;
		launch_thread(server, worker);
	}
}

int			main(void)
{
	t_server	*server;

	server = (t_server*)calloc(1, sizeof(t_server));
	server->sin = setup_server_socket(PORT);
	server->is_connect = 1;
	connect_worker(server);
	return (0);
}
