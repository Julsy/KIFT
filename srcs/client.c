/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 14:50:18 by elee              #+#    #+#             */
/*   Updated: 2017/06/12 17:42:08 by elee             ###   ########.fr       */
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

static void recognize_from_microphone(ps_decoder_t *ps, cmd_ln_t *config,
		t_socket sin)
{
	ad_rec_t        *ad;
	int16_t         adbuf[2048];
	uint8_t         utt_started;
	uint8_t         in_speech;
	//uint8_t         key_detected;
	int32_t         k;
	char const      *hyp;

	ad = ad_open_dev(NULL, 16000);
	ad_start_rec(ad);
	ps_start_utt(ps);
	utt_started = FALSE;
	//key_detected = FALSE;
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
				send(sin.fd, hyp, strlen(hyp), 0);
				printf("%s\n", hyp);
				fflush(stdout);
				/*
				if (!strcmp(hyp, "benjamin")) {
					key_detected = TRUE;
					printf("KEY DETECTED\n");
					fflush(stdout);
				}
				if (key_detected && strcmp(hyp, "benjamin") && strlen(hyp) > 0) {
					key_detected = FALSE;
					parse_init((char*)hyp);
					send(sin.fd, hyp, strlen(hyp), 0);
					fflush(stdout);
				}
				*/
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

	if (argc == 1)
	{
		printf("Usage: %s [IP Address]\n", argv[0]);
		exit(1);
	}
	sin = setup_client_socket(argv[1], PORT);
	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/en-us",
			"-lm", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/en-us.lm.bin",
			"-dict", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/cmudict-en-us.dict",
			"-mllr", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/mllr_matrix",
			"-logfn", "log.txt",
			"-kws", "keyword.list",
			/*
			"-keyphrase", "benjamin",
			"-kws_threshold", "1e-20",
			*/
			NULL);
	ps_default_search_args(config);
	ps = ps_init(config);
	recognize_from_microphone(ps, config, sin);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (0);
}
