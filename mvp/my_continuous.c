#include "kift.h"

static void	write_little_endian(unsigned int word, int num_bytes, FILE *wav_file)
{
	unsigned int buf;
	
	while (num_bytes > 0)
	{
		buf = word & 0xff;
		fwrite(&buf, 1, 1, wav_file);
		num_bytes--;
		word >>= 8;
	}
}

static void	write_wav(char *filename, int32_t num_samples, int16_t *data)
{
	FILE		*wav_file;
	uint32_t	sample_rate = 16000;
	uint32_t	num_channels = 1;
	uint32_t	bytes_per_sample = 2;
	uint32_t	byte_rate = sample_rate * num_channels * bytes_per_sample;
	uint64_t	i;

	wav_file = fopen(filename, "w");
	assert(wav_file);

	/* write RIFF header */
	fwrite("RIFF", 1, 4, wav_file);
	write_little_endian(36 + bytes_per_sample * num_samples * num_channels,
			4, wav_file);
	fwrite("WAVE", 1, 4, wav_file);

	/* write fmt subchunk */
	fwrite("fmt ", 1, 4, wav_file);
	write_little_endian(16, 4, wav_file);
	write_little_endian(1, 2, wav_file);
	write_little_endian(num_channels, 2, wav_file);
	write_little_endian(sample_rate, 4, wav_file);
	write_little_endian(byte_rate, 4, wav_file);
	write_little_endian(num_channels*bytes_per_sample, 2, wav_file);
	write_little_endian(8 * bytes_per_sample, 2, wav_file);

	/* write data subchunk */
	fwrite("data", 1, 4, wav_file);
	write_little_endian(bytes_per_sample * num_samples * num_channels, 4, wav_file);
	for (i = 0; i < num_samples; i++)
		write_little_endian((unsigned int)(data[i]), bytes_per_sample, wav_file);
	fclose(wav_file);	
}

static void	sleep_msec(int32_t ms)
{
	struct timeval tmo;
	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;
	select(0, NULL, NULL, NULL, &tmo);
}

static void	recognize_from_microphone(ps_decoder_t *ps, cmd_ln_t *config)
{
	ad_rec_t		*ad;
	int16_t			adbuf[2048];
	uint8_t			utt_started;
	uint8_t			in_speech;
	uint8_t			key_detected;
	int32_t			k;
	char const		*hyp;

	ad = ad_open_dev(NULL, 16000);
	ad_start_rec(ad);
	ps_start_utt(ps);
	utt_started = FALSE;
	key_detected = FALSE;
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
					key_detected = TRUE;
					printf("KEY DETECTED\n");
					fflush(stdout);
				}
				if (key_detected && strcmp(hyp, "benjamin") && strlen(hyp) > 0) {
					key_detected = FALSE;
					printf("---------parsing---------\n");
					parse_init((char *)hyp);
					// printf("%s\n", hyp);
					fflush(stdout);
					/*
					write_wav("test.wav", k, adbuf);
					printf("wav written\n");
					fflush(stdout);
					*/
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

int			main(void)
{
	cmd_ln_t		*config;
	ps_decoder_t	*ps;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/en-us-adapt",
			"-lm", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/en-us.lm.bin",
			"-dict", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/cmudict-en-us.dict",
			"-mllr", "/nfs/2016/i/iiliuk/Midshipman/KIFT/my_KIFT/sphinx/share/mllr_matrix",
			"-logfn", "log.txt",
			"-keyphrase", "benjamin",
			"-kws_threshold", "1e-20",
			NULL);
	ps_default_search_args(config);
	ps = ps_init(config);
	recognize_from_microphone(ps, config);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (0);
}
