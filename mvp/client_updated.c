/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 14:50:18 by elee              #+#    #+#             */
/*   Updated: 2017/06/14 05:37:42 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/select.h>
#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <pocketsphinx.h>
#include <fcntl.h>
#include <unistd.h>

static void sleep_msec(int32_t ms)
{
	struct timeval tmo;
	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;
	select(0, NULL, NULL, NULL, &tmo);
}

t_socket	setup_client_socket(char *addr, int port)
{
	t_socket	sin;

	memset(&sin.addr, 0, sizeof(sin.addr));
	sin.addrlen = sizeof(struct sockaddr_storage);
	sin.addr.sin_family = AF_INET;
	sin.addr.sin_port = htons(port);
	if ((sin.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		dprintf(2, "Creating the client socket failed with code: %d\n", errno);
		exit(1);
	}
	if (inet_pton(AF_INET, addr, &sin.addr.sin_addr) <= 0)
	{
		dprintf(2, "Invalid Address given\n");
		exit(1);
	}
	if (connect(sin.fd, (struct sockaddr*)(&sin.addr), sizeof(sin.addr)) < 0)
	{
		dprintf(2, "Connection Failed\n");
		exit(1);
	}
	printf("Successfully connected to %s\n", addr);
	return (sin);
}

void		record_command()
{
	char	command[128] = "rec -c 1 -b 16 -r 16000 tmp.wav silence 1 0.1 3% 1 3.0 3%";
	system(command);
}


static char	*recognize_from_file(cmd_ln_t *config)
{
	ps_decoder_t	*ps;
	FILE			*fh;
	char const			*hyp;
	int16_t			adbuf[512];
	int32_t			score;
	size_t			nsamp;
	char			*return_msg;

	ps = ps_init(config);
	fh = fopen("tmp.wav", "rb");
	ps_start_utt(ps);
	while (!feof(fh))
	{
		nsamp = fread(adbuf, 2, 512, fh);
		ps_process_raw(ps, adbuf, nsamp, FALSE, FALSE);
	}
	ps_end_utt(ps);
	hyp = ps_get_hyp(ps, &score);
	fclose(fh);
	return_msg = strdup(hyp);
	ps_free(ps);
	return (return_msg);
}

static void recognize_from_microphone(ps_decoder_t *ps, cmd_ln_t *config,
		t_socket sin)
{
	ad_rec_t        *ad;
	int16_t         adbuf[2048];
	uint8_t         utt_started;
	uint8_t         in_speech;
	int32_t         k;
	char const		*hyp;
	int				counter;
	char			*send_data;

	ad = ad_open_dev(NULL, 16000);
	ad_start_rec(ad);
	ps_start_utt(ps);
	utt_started = FALSE;
	counter = 0;
	while (1)
	{
		k = ad_read(ad, adbuf, 2048);
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started) {
			utt_started = TRUE;
			E_INFO("Listening...\n");
		}
		if (!in_speech && utt_started) {
			ps_end_utt(ps);
			hyp = ps_get_hyp(ps, NULL);
			if (hyp != NULL) {
				if (!strcmp(hyp, "benjamin")) {
					printf("KEYWORD DETECTED\n");
					ad_stop_rec(ad);
					ad_close(ad);
					record_command();
					send_data = recognize_from_file(config);
					system("rm tmp.wav");
					printf("%s\n", send_data);
					free(send_data);
					ad = ad_open_dev(NULL, 16000);
					ad_start_rec(ad);
				}
			}
			ps_start_utt(ps);
			utt_started = FALSE;
			E_INFO("Ready...\n");
		}
		sleep_msec(100);
	}
	ad_stop_rec(ad);
	ad_close(ad);
}

int		main(int argc, char **argv)
{
	cmd_ln_t		*config;
	ps_decoder_t	*ps;
	t_socket		sin;
	char			*buf;

	if (argc == 1)
	{
		printf("Usage: %s [IP Address]\n", argv[0]);
		exit(1);
	}
	sin = setup_client_socket(argv[1], PORT);
	buf = (char*)malloc(sizeof(char) * 1024);
	config = cmd_ln_init(NULL, ps_args(), TRUE,
						"-hmm", MODELDIR "/en-us/en-us",
						"-lm", MODELDIR "/en-us/en-us.lm.bin",
						"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
						"-logfn", "log.txt",
						NULL);
	ps_default_search_args(config);
	ps = ps_init(config);
	recognize_from_microphone(ps, config, sin);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (0);
}
